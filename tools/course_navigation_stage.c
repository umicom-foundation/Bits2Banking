/*
 * Umicom Foundation — Bits2Banking
 * Owner / Author: Sammy Hegab / Umicom Foundation
 * Licence: MIT
 *
 * Source-preserving, test-only HTML course navigation staging tool (C23).
 *
 * Architecture:
 * - READS existing, human-authored course pages and the 94-item catalogue.
 * - WRITES complete derived files ONLY to an explicit external staging folder.
 * - Does not implement a separate course runtime, LLM, RAG or data ingestion.
 * - Reuses the canonical HTML catalogue and HTML path inventory rather than
 *   maintaining a second hard-coded list of 94 page names.
 * - Never edits, removes or overwrites files in the source repository.
 * - Only adds labelled HTML; all preceding source bytes are retained.
 *
 * CLI:
 *   btb-lesson-navigation --stage <repository-root> <staging-parent>
 *   btb-lesson-navigation --verify <repository-root>
 *   btb-lesson-navigation --self-test
 *
 * A future Framework-owned publishing API may replace this standalone,
 * education-only staging step. Preserve this implementation for review until
 * that migration is approved.
 */

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#define BTB_MKDIR(path) _mkdir(path)
#else
#define BTB_MKDIR(path) mkdir((path), 0777)
#endif

#define BTB_MAX_PATH 4096U
#define BTB_MAX_SOURCE (4U * 1024U * 1024U)
#define BTB_NAV_CAPACITY 32768U
#define BTB_FIRST_NEW_LESSON 69
#define BTB_LAST_LESSON 94
#define BTB_ALL_LESSONS 94
#define BTB_ALL_MATHS 20

#define BTB_BEGIN "<!-- BEGIN UMICOM_BTB_LESSON_69_94_NAV: append-only course navigation -->"
#define BTB_END "<!-- END UMICOM_BTB_LESSON_69_94_NAV -->"

static const char *const kIndexPath =
    "content/courses/llm-from-scratch/index.html";
static const char *const kMapPath =
    "content/courses/llm-from-scratch/course-map.html";
static const char *const kCataloguePath =
    "content/courses/llm-from-scratch/all-lessons.html";
static const char *const kInventoryPath =
    "knowledge/inventories/course-html-pages.tsv";
static const char *const kRelationsPath =
    "knowledge/relationships/lesson-source-coverage.tsv";

/* All sizes and paths are bounded; return an error rather than truncating. */
static bool PathJoin(char *out, size_t capacity, const char *left,
                     const char *right)
{
    const size_t n = strlen(left);
    const bool trailing = n > 0U && (left[n - 1U] == '/' || left[n - 1U] == '\\');
    int len = snprintf(out, capacity, "%s%s%s", left, trailing ? "" : "/", right);
    return len > 0 && (size_t)len < capacity;
}

/* Guard against an output path that would place staged files in the repo.
 * This is intentionally a narrow pathname check, not a security sandbox.
 * Absolute source/staging paths should be used (see the merge guide).
 */
static bool NormalizePath(const char *input, char *output, size_t capacity)
{
    size_t length = strlen(input);
    if (length == 0U || length >= capacity || strstr(input, "..") != NULL) {
        return false;
    }
    for (size_t i = 0U; i < length; ++i) {
        unsigned char c = (unsigned char)input[i];
        if (c == '\\') {
            c = '/';
        }
#ifdef _WIN32
        c = (unsigned char)tolower(c);
#endif
        output[i] = (char)c;
    }
    while (length > 1U && output[length - 1U] == '/') {
        --length;
    }
    output[length] = '\0';
    return true;
}

static bool StagingOutsideRepository(const char *sourceRoot, const char *stageRoot)
{
    char source[BTB_MAX_PATH];
    char stage[BTB_MAX_PATH];
    if (!NormalizePath(sourceRoot, source, sizeof(source)) ||
        !NormalizePath(stageRoot, stage, sizeof(stage))) {
        return false;
    }
    /* Resolve only absolute caller-supplied paths; no dot/cwd ambiguity. */
    bool sourceAbsolute = source[0] == '/' ||
        (isalpha((unsigned char)source[0]) != 0 && source[1] == ':' &&
         source[2] == '/');
    bool stageAbsolute = stage[0] == '/' ||
        (isalpha((unsigned char)stage[0]) != 0 && stage[1] == ':' &&
         stage[2] == '/');
    if (!sourceAbsolute || !stageAbsolute) {
        return false;
    }
    size_t length = strlen(source);
    return !(strncmp(source, stage, length) == 0 &&
             (stage[length] == '/' || stage[length] == '\0'));
}

static bool FileExists(const char *path)
{
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        return false;
    }
    (void)fclose(file);
    return true;
}

static char *ReadFile(const char *path)
{
    FILE *in = fopen(path, "rb");
    if (in == NULL) {
        fprintf(stderr, "Cannot read %s: %s\n", path, strerror(errno));
        return NULL;
    }
    if (fseek(in, 0L, SEEK_END) != 0) {
        (void)fclose(in);
        return NULL;
    }
    long length = ftell(in);
    if (length < 0L || (unsigned long)length > BTB_MAX_SOURCE ||
        fseek(in, 0L, SEEK_SET) != 0) {
        fprintf(stderr, "Unacceptable source length: %s\n", path);
        (void)fclose(in);
        return NULL;
    }
    size_t count = (size_t)length;
    char *data = malloc(count + 1U);
    if (data == NULL) {
        (void)fclose(in);
        return NULL;
    }
    if (fread(data, 1U, count, in) != count) {
        fprintf(stderr, "Short read: %s\n", path);
        free(data);
        (void)fclose(in);
        return NULL;
    }
    data[count] = '\0';
    (void)fclose(in);
    if (strlen(data) != count) {
        fprintf(stderr, "Embedded NUL found: %s\n", path);
        free(data);
        return NULL;
    }
    return data;
}

static char *ReadRepositoryFile(const char *root, const char *relative)
{
    char path[BTB_MAX_PATH];
    if (!PathJoin(path, sizeof(path), root, relative)) {
        return NULL;
    }
    return ReadFile(path);
}

/* Create only the directories needed for the explicit staging output. */
static bool CreateParents(const char *filePath)
{
    char path[BTB_MAX_PATH];
    size_t length = strlen(filePath);
    if (length == 0U || length >= sizeof(path)) {
        return false;
    }
    memcpy(path, filePath, length + 1U);
    for (size_t i = 1U; i < length; ++i) {
        if (path[i] != '/' && path[i] != '\\') {
            continue;
        }
        /* Do not try to mkdir drive roots (C:\\) or POSIX root (/). */
        if (i == 2U && path[1] == ':') {
            continue;
        }
        char separator = path[i];
        path[i] = '\0';
        if (BTB_MKDIR(path) != 0 && errno != EEXIST) {
            fprintf(stderr, "Cannot create %s: %s\n", path, strerror(errno));
            return false;
        }
        path[i] = separator;
    }
    return true;
}

static bool Append(char *buffer, size_t capacity, size_t *used,
                   const char *format, ...)
{
    if (*used >= capacity) {
        return false;
    }
    va_list ap;
    va_start(ap, format);
    int length = vsnprintf(buffer + *used, capacity - *used, format, ap);
    va_end(ap);
    if (length < 0 || (size_t)length >= capacity - *used) {
        return false;
    }
    *used += (size_t)length;
    return true;
}

static int CountToken(const char *text, const char *token)
{
    int count = 0;
    size_t width = strlen(token);
    if (width == 0U) {
        return -1;
    }
    for (const char *cursor = text; (cursor = strstr(cursor, token)) != NULL;
         cursor += width) {
        ++count;
    }
    return count;
}

/* Match each lesson against the existing catalogue, without rewriting it. */
static bool ParseLesson(const char *catalogue, int lesson,
                        char *href, size_t hrefCapacity,
                        char *title, size_t titleCapacity)
{
    char needle[32];
    int written = snprintf(needle, sizeof(needle), "<li value=\"%d\">", lesson);
    if (written < 0 || (size_t)written >= sizeof(needle)) {
        return false;
    }
    const char *record = strstr(catalogue, needle);
    if (record == NULL || CountToken(catalogue, needle) != 1) {
        fprintf(stderr, "Catalogue must contain lesson %d exactly once\n", lesson);
        return false;
    }
    const char *end = strstr(record, "</li>");
    const char *anchor = strstr(record, "<a href=\"");
    if (end == NULL || anchor == NULL || anchor >= end) {
        return false;
    }
    const char *start = anchor + strlen("<a href=\"");
    const char *stop = strchr(start, '"');
    const char *labelStart = stop != NULL ? strchr(stop, '>') : NULL;
    const char *labelEnd = labelStart != NULL ? strstr(labelStart, "</a>") : NULL;
    if (stop == NULL || stop >= end || labelStart == NULL || labelEnd == NULL ||
        labelEnd > end || labelStart >= labelEnd) {
        return false;
    }
    ++labelStart;
    size_t hrefLength = (size_t)(stop - start);
    size_t titleLength = (size_t)(labelEnd - labelStart);
    if (hrefLength == 0U || hrefLength >= hrefCapacity || titleLength == 0U ||
        titleLength >= titleCapacity) {
        return false;
    }
    memcpy(href, start, hrefLength);
    href[hrefLength] = '\0';
    memcpy(title, labelStart, titleLength);
    title[titleLength] = '\0';
    /* Safe, static relative HTML references only: no schemes or traversal. */
    if (strncmp(href, "lessons/", 8U) != 0 || strstr(href, "..") != NULL ||
        strstr(href, ".html") == NULL) {
        return false;
    }
    for (size_t i = 0U; i < hrefLength; ++i) {
        char c = href[i];
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') ||
              c == '/' || c == '-' || c == '.')) {
            return false;
        }
    }
    char prefix[24];
    (void)snprintf(prefix, sizeof(prefix), "lessons/%02d-", lesson);
    return strncmp(href, prefix, strlen(prefix)) == 0;
}

static bool BuildNavigation(const char *catalogue, char *navigation,
                            size_t capacity)
{
    size_t used = 0U;
    navigation[0] = '\0';
    if (!Append(navigation, capacity, &used, "\n%s\n", BTB_BEGIN)) {
        return false;
    }
    for (int group = 0; group < 2; ++group) {
        int first = group == 0 ? 69 : 81;
        int last = group == 0 ? 80 : BTB_LAST_LESSON;
        const char *heading = group == 0
            ? "Efficient native inference and checkpoint evidence"
            : "Rotary attention, training tape and acceptance evidence";
        if (!Append(navigation, capacity, &used,
                    "<section class=\"module\" aria-label=\"Lessons %d–%d\">"
                    "<span class=\"micro\">Lessons %d–%d · %d lessons</span>"
                    "<h3>%s</h3><ul class=\"lesson-links\">\n",
                    first, last, first, last, last - first + 1, heading)) {
            return false;
        }
        for (int lesson = first; lesson <= last; ++lesson) {
            char href[256];
            char title[512];
            if (!ParseLesson(catalogue, lesson, href, sizeof(href), title,
                             sizeof(title))) {
                return false;
            }
            if (!Append(navigation, capacity, &used,
                        "<li><a href=\"%s\"><span class=\"n\">%02d</span>"
                        "<span>%s</span></a></li>\n", href, lesson, title)) {
                return false;
            }
        }
        if (!Append(navigation, capacity, &used, "</ul></section>\n")) {
            return false;
        }
    }
    return Append(navigation, capacity, &used,
                  "<p class=\"btb-complete-catalogue\">"
                  "<a href=\"all-lessons.html\">"
                  "Browse the complete 94-lesson catalogue →</a></p>\n%s\n",
                  BTB_END);
}

static const char *FindLast(const char *text, const char *needle)
{
    const char *last = NULL;
    const char *cursor = text;
    size_t width = strlen(needle);
    if (width == 0U) {
        return NULL;
    }
    while ((cursor = strstr(cursor, needle)) != NULL) {
        last = cursor;
        cursor += width;
    }
    return last;
}

/* Stages an exact copy of original bytes with precisely one additive block. */
static bool StagePage(const char *sourceRoot, const char *stageRoot,
                      const char *relative, const char *navigation,
                      bool isMap)
{
    char *original = ReadRepositoryFile(sourceRoot, relative);
    if (original == NULL) {
        return false;
    }
    if (strstr(original, BTB_BEGIN) != NULL || strstr(original, BTB_END) != NULL) {
        fprintf(stderr, "Already integrated; refusing double insertion: %s\n", relative);
        free(original);
        return false;
    }
    for (int n = 1; n <= 68; ++n) {
        char key[32];
        (void)snprintf(key, sizeof(key), "href=\"lessons/%02d-", n);
        if (CountToken(original, key) != 1) {
            fprintf(stderr, "Expected one existing link to lesson %02d in %s\n",
                    n, relative);
            free(original);
            return false;
        }
    }
    const char *marker = isMap ? "</div></main>" : "</main>";
    const char *position = FindLast(original, marker);
    if (position == NULL || strstr(position, "<footer") == NULL) {
        fprintf(stderr, "Unrecognised page layout; no file staged: %s\n", relative);
        free(original);
        return false;
    }
    char target[BTB_MAX_PATH];
    if (!PathJoin(target, sizeof(target), stageRoot, relative) ||
        !CreateParents(target) || FileExists(target)) {
        fprintf(stderr, "Unsafe/colliding staging destination: %s\n", relative);
        free(original);
        return false;
    }
    FILE *out = fopen(target, "wb");
    if (out == NULL) {
        fprintf(stderr, "Cannot write staging file %s\n", target);
        free(original);
        return false;
    }
    size_t prefix = (size_t)(position - original);
    size_t suffix = strlen(position);
    size_t newLength = strlen(navigation);
    bool ok = fwrite(original, 1U, prefix, out) == prefix &&
              fwrite(navigation, 1U, newLength, out) == newLength &&
              fwrite(position, 1U, suffix, out) == suffix;
    if (fclose(out) != 0) {
        ok = false;
    }
    if (!ok) {
        fprintf(stderr, "Cannot complete staged page: %s\n", target);
        (void)remove(target);
    }
    free(original);
    return ok;
}

/* TSV is a candidate-coverage register, not a source-approval decision. */
static bool StageCoverage(const char *sourceRoot, const char *stageRoot,
                          int *present, int *missing)
{
    *present = 0;
    *missing = 0;
    char *inventory = ReadRepositoryFile(sourceRoot, kInventoryPath);
    if (inventory == NULL) {
        return false;
    }
    char target[BTB_MAX_PATH];
    if (!PathJoin(target, sizeof(target), stageRoot, kRelationsPath) ||
        !CreateParents(target) || FileExists(target)) {
        fprintf(stderr, "Unsafe/colliding coverage staging destination\n");
        free(inventory);
        return false;
    }
    FILE *out = fopen(target, "wb");
    if (out == NULL) {
        free(inventory);
        return false;
    }
    bool ok = fputs("# Derived from knowledge/inventories/course-html-pages.tsv; "
                    "not a publication or training approval.\n"
                    "# Canonical Markdown is linked only if the file exists "
                    "in the local source checkout.\n"
                    "content_id\tcourse\tlesson_number\tcourse_html\t"
                    "canonical_markdown\tsource_coverage\t"
                    "editorial_review\ttraining_permission\n", out) >= 0;
    int lastLLM = 0;
    int lastMaths = 0;
    char *cursor = inventory;
    while (ok && *cursor != '\0') {
        char *newline = strchr(cursor, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        size_t lineLength = strlen(cursor);
        if (lineLength > 0U && cursor[lineLength - 1U] == '\r') {
            cursor[lineLength - 1U] = '\0';
        }
        if (*cursor != '\0' && *cursor != '#') {
            char *tab1 = strchr(cursor, '\t');
            char *tab2 = tab1 != NULL ? strchr(tab1 + 1, '\t') : NULL;
            if (tab1 == NULL || tab2 == NULL) {
                ok = false;
                break;
            }
            *tab1 = '\0';
            *tab2 = '\0';
            const char *course = cursor;
            const char *ordinal = tab1 + 1;
            const char *html = tab2 + 1;
            bool llm = strcmp(course, "llm") == 0;
            bool maths = strcmp(course, "maths") == 0;
            char *end = NULL;
            long number = strtol(ordinal, &end, 10);
            int *last = llm ? &lastLLM : &lastMaths;
            int limit = llm ? BTB_ALL_LESSONS : BTB_ALL_MATHS;
            if ((!llm && !maths) || end == ordinal || *end != '\0' ||
                number != (long)(*last + 1) || number > limit ||
                strchr(html, '\t') != NULL || strstr(html, "..") != NULL) {
                fprintf(stderr, "Bad/out-of-order inventory record: %s %s\n",
                        course, ordinal);
                ok = false;
                break;
            }
            ++*last;
            const char *stem = strrchr(html, '/');
            stem = stem == NULL ? html : stem + 1;
            size_t stemLength = strlen(stem);
            if (stemLength <= 5U || strcmp(stem + stemLength - 5U, ".html") != 0 ||
                strncmp(html, llm ? "content/courses/llm-from-scratch/lessons/"
                                   : "content/courses/maths-for-ai/lessons/",
                        llm ? strlen("content/courses/llm-from-scratch/lessons/")
                            : strlen("content/courses/maths-for-ai/lessons/")) != 0) {
                ok = false;
                break;
            }
            char slug[256];
            if (stemLength - 5U >= sizeof(slug)) {
                ok = false;
                break;
            }
            memcpy(slug, stem, stemLength - 5U);
            slug[stemLength - 5U] = '\0';
            /* HTML lesson 61 has a longer presentation filename than its MD. */
            if (llm && number == 61) {
                (void)snprintf(slug, sizeof(slug), "61-top-p-nucleus-sampling");
            }
            char relativeMD[BTB_MAX_PATH];
            char absoluteMD[BTB_MAX_PATH];
            char absoluteHTML[BTB_MAX_PATH];
            int result = snprintf(relativeMD, sizeof(relativeMD),
                                  "content/lessons/%s/%s.md",
                                  llm ? "10-native-ai" : "11-maths-for-ai", slug);
            if (result < 0 || (size_t)result >= sizeof(relativeMD) ||
                !PathJoin(absoluteMD, sizeof(absoluteMD), sourceRoot, relativeMD) ||
                !PathJoin(absoluteHTML, sizeof(absoluteHTML), sourceRoot, html) ||
                !FileExists(absoluteHTML)) {
                ok = false;
                break;
            }
            bool found = FileExists(absoluteMD);
            *present += found ? 1 : 0;
            *missing += found ? 0 : 1;
            if (fprintf(out, "btb:%s:%03ld\t%s\t%ld\t%s\t%s\t%s\t"
                             "human_review_required\tnot_assessed\n",
                        llm ? "llm" : "maths", number, course, number,
                        html, found ? relativeMD : "",
                        found ? "path_present_unreviewed" : "markdown_not_found") < 0) {
                ok = false;
                break;
            }
        }
        if (newline == NULL) {
            break;
        }
        cursor = newline + 1;
    }
    if (lastLLM != BTB_ALL_LESSONS || lastMaths != BTB_ALL_MATHS) {
        fprintf(stderr, "Inventory does not contain all 94 + 20 lessons\n");
        ok = false;
    }
    if (fclose(out) != 0) {
        ok = false;
    }
    if (!ok) {
        (void)remove(target);
    }
    free(inventory);
    return ok;
}

static bool VerifyPage(const char *root, const char *relative)
{
    char *html = ReadRepositoryFile(root, relative);
    if (html == NULL) {
        return false;
    }
    bool ok = CountToken(html, BTB_BEGIN) == 1 &&
              CountToken(html, BTB_END) == 1 &&
              CountToken(html, "href=\"all-lessons.html\"") >= 1;
    for (int n = 1; n <= BTB_LAST_LESSON; ++n) {
        char needle[32];
        (void)snprintf(needle, sizeof(needle), "href=\"lessons/%02d-", n);
        int count = CountToken(html, needle);
        if (count != 1) {
            fprintf(stderr, "%s: lesson %02d has %d links (expected 1)\n",
                    relative, n, count);
            ok = false;
        }
    }
    if (!ok) {
        fprintf(stderr, "Course navigation failed: %s\n", relative);
    }
    free(html);
    return ok;
}

static bool VerifyCoverage(const char *root)
{
    char *records = ReadRepositoryFile(root, kRelationsPath);
    if (records == NULL) {
        return false;
    }
    int rows = 0;
    for (char *p = records; *p != '\0';) {
        char *next = strchr(p, '\n');
        if (*p != '#' && strncmp(p, "content_id\t", 11U) != 0 && *p != '\0') {
            if (strncmp(p, "btb:", 4U) != 0 ||
                strstr(p, "\thuman_review_required\tnot_assessed") == NULL) {
                free(records);
                return false;
            }
            ++rows;
        }
        if (next == NULL) {
            break;
        }
        p = next + 1;
    }
    free(records);
    return rows == BTB_ALL_LESSONS + BTB_ALL_MATHS;
}

static bool SelfTest(void)
{
    /* Parser and additive placement basic regression (no repository writes). */
    const char *fixture =
        "<ol><li value=\"69\"><a href=\"lessons/69-native.html\">" 
        "Native &amp; checked</a></li></ol>";
    char href[128];
    char title[128];
    const char *page = "<main><div class=\"path-grid\">x</div></main><footer>y";
    return ParseLesson(fixture, 69, href, sizeof(href), title, sizeof(title)) &&
           strcmp(href, "lessons/69-native.html") == 0 &&
           strcmp(title, "Native &amp; checked") == 0 &&
           FindLast(page, "</div></main>") != NULL &&
           CountToken(page, BTB_BEGIN) == 0 &&
           !ParseLesson("<li value=\"69\"><a href=\"../evil.html\">x</a></li>",
                        69, href, sizeof(href), title, sizeof(title));
}

static void PrintUsage(const char *program)
{
    fprintf(stderr,
            "Usage:\n  %s --stage <repository-root> <staging-parent>\n"
            "  %s --verify <repository-root>\n  %s --self-test\n",
            program, program, program);
}

int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--self-test") == 0) {
        bool passed = SelfTest();
        printf("Native C23 source-preserving staging self-test: %s\n",
               passed ? "PASS" : "FAIL");
        return passed ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    if (argc == 3 && strcmp(argv[1], "--verify") == 0) {
        bool indexOK = VerifyPage(argv[2], kIndexPath);
        bool mapOK = VerifyPage(argv[2], kMapPath);
        bool coverageOK = VerifyCoverage(argv[2]);
        printf("Full LLM navigation (1–94) / source coverage (114): %s\n",
               indexOK && mapOK && coverageOK ? "PASS" : "FAIL");
        return indexOK && mapOK && coverageOK ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    if (argc != 4 || strcmp(argv[1], "--stage") != 0) {
        PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }
    char stageRoot[BTB_MAX_PATH];
    if (!PathJoin(stageRoot, sizeof(stageRoot), argv[3], "Umicom-Bits2Banking") ||
        !StagingOutsideRepository(argv[2], stageRoot)) {
        fprintf(stderr, "Staging root must be external to the source repository.\n");
        return EXIT_FAILURE;
    }
    char *catalogue = ReadRepositoryFile(argv[2], kCataloguePath);
    if (catalogue == NULL) {
        return EXIT_FAILURE;
    }
    char nav[BTB_NAV_CAPACITY];
    bool built = BuildNavigation(catalogue, nav, sizeof(nav));
    free(catalogue);
    if (!built) {
        fprintf(stderr, "Cannot derive all 26 new links from existing catalogue\n");
        return EXIT_FAILURE;
    }
    /* Each output is a complete file; existing repository pages are untouched. */
    bool indexOK = StagePage(argv[2], stageRoot, kIndexPath, nav, false);
    if (!indexOK) {
        return EXIT_FAILURE;
    }
    bool mapOK = StagePage(argv[2], stageRoot, kMapPath, nav, true);
    if (!mapOK) {
        return EXIT_FAILURE;
    }
    int present = 0;
    int missing = 0;
    if (!StageCoverage(argv[2], stageRoot, &present, &missing)) {
        return EXIT_FAILURE;
    }
    printf("Staged full course home + map under: %s\n", stageRoot);
    printf("New lesson links: 69–94 in both pages; existing 1–68 retained.\n");
    printf("Knowledge coverage: %d canonical Markdown paths exist, %d absent "
           "(114 HTML pages total).\n", present, missing);
    printf("No repository source files were changed. Compare and merge manually.\n");
    return EXIT_SUCCESS;
}
