/*-----------------------------------------------------------------------------
 * Umicom Foundation / Bits2Banking
 * File: tests/content_integrity/test_content_inventory.c
 *
 * PURPOSE:
 *   Read-only TEST to verify expected course-file inventory, ordering and
 *   the safe relocation of four authored Markdown manuscripts. The reusable
 *   production path/retrieval services remain owned by Umicom Framework.
 *
 * SCOPE:
 *   Verifies file presence, shape and selected relationships. It does NOT
 *   validate HTML semantics, source licences, human editorial quality or
 *   authority to use any source for model training. No files are mutated.
 *
 * AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BTB_PATH_MAX 4096U
#define BTB_ROW_MAX 1024U

static int IsSafeRelative(const char *path)
{
    size_t length;
    size_t index;
    const char *segment = path;
    if (path == NULL || path[0] == '\0' || path[0] == '/' ||
        path[0] == '\\') return 0;
    length = strlen(path);
    if (length == 0U || length >= BTB_PATH_MAX) return 0;
    for (index = 0U; index < length; ++index) {
        const char ch = path[index];
        if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
              (ch >= '0' && ch <= '9') || ch == '-' || ch == '_' ||
              ch == '.' || ch == '/')) return 0;
        if (ch == '/') {
            if (&path[index] == segment ||
                (&path[index] == segment + 1 && segment[0] == '.') ||
                (&path[index] == segment + 2 && segment[0] == '.' &&
                 segment[1] == '.')) return 0;
            segment = &path[index] + 1;
        }
    }
    if (*segment == '\0' || strcmp(segment, ".") == 0 ||
        strcmp(segment, "..") == 0) return 0;
    return 1;
}

static int Join(char *output, size_t capacity, const char *root,
                const char *relative)
{
    int result;
    if (output == NULL || root == NULL || !IsSafeRelative(relative))
        return 0;
    result = snprintf(output, capacity, "%s/%s", root, relative);
    return result > 0 && (size_t)result < capacity;
}

static int ExistsFile(const char *root, const char *relative)
{
    char fullPath[BTB_PATH_MAX];
    FILE *file;
    long length;
    if (!Join(fullPath, sizeof(fullPath), root, relative)) return 0;
    file = fopen(fullPath, "rb");
    if (file == NULL) return 0;
    if (fseek(file, 0L, SEEK_END) != 0) {
        (void)fclose(file);
        return 0;
    }
    length = ftell(file);
    (void)fclose(file);
    return length > 0L;
}

static int MissingFile(const char *root, const char *relative)
{
    char fullPath[BTB_PATH_MAX];
    FILE *file;
    if (!Join(fullPath, sizeof(fullPath), root, relative)) return 0;
    file = fopen(fullPath, "rb");
    if (file != NULL) {
        (void)fclose(file);
        return 0;
    }
    /* A missing file and an unreadable file look alike to fopen(). This is
     * a structural smoke gate, not a security assertion about permissions. */
    return errno == ENOENT;
}

static int ValidateRecord(const char *course, const char *number,
                          const char *path, unsigned expectedLlm,
                          unsigned expectedMaths)
{
    char *end = NULL;
    unsigned long ordinal;
    const char *prefix;
    size_t prefixLength;
    size_t pathLength;
    if (course == NULL || number == NULL || path == NULL ||
        !IsSafeRelative(path)) return 0;
    if (strcmp(course, "llm") == 0) {
        prefix = "content/courses/llm-from-scratch/lessons/";
    } else if (strcmp(course, "maths") == 0) {
        prefix = "content/courses/maths-for-ai/lessons/";
    } else return 0;
    prefixLength = strlen(prefix);
    pathLength = strlen(path);
    if (pathLength <= prefixLength + 5U ||
        strncmp(path, prefix, prefixLength) != 0 ||
        strcmp(path + pathLength - 5U, ".html") != 0) return 0;
    if (!isdigit((unsigned char)number[0])) return 0;
    errno = 0;
    ordinal = strtoul(number, &end, 10);
    if (errno != 0 || end == number || *end != '\0' ||
        ordinal > UINT_MAX) return 0;
    if (course[0] == 'l' ? ordinal != expectedLlm :
        ordinal != expectedMaths) return 0;
    /* A two-digit lesson prefix must agree with the record's ordinal. */
    {
        char pattern[16];
        int n = snprintf(pattern, sizeof(pattern), "%02lu-", ordinal);
        if (n <= 0 || (size_t)n >= sizeof(pattern) ||
            strncmp(path + prefixLength, pattern, (size_t)n) != 0)
            return 0;
    }
    return 1;
}

static int CheckInventory(const char *root)
{
    const char *inventory = "knowledge/inventories/course-html-pages.tsv";
    char full[BTB_PATH_MAX];
    char row[BTB_ROW_MAX];
    char *first;
    char *second;
    char *last;
    FILE *file;
    unsigned llm = 0U, maths = 0U, line = 0U;
    int success = 1;
    if (!Join(full, sizeof(full), root, inventory)) return 0;
    file = fopen(full, "rb");
    if (file == NULL) {
        fprintf(stderr, "Missing reviewed inventory: %s\n", full);
        return 0;
    }
    while (fgets(row, sizeof(row), file) != NULL) {
        const size_t length = strlen(row);
        ++line;
        if (length == 0U) continue;
        if (row[length - 1U] != '\n' && !feof(file)) {
            fprintf(stderr, "Oversized inventory row at line %u\n", line);
            success = 0;
            break;
        }
        if (row[0] == '#') continue;
        row[strcspn(row, "\r\n")] = '\0';
        if (row[0] == '\0') continue;
        first = row;
        second = strchr(first, '\t');
        if (second == NULL) { success = 0; break; }
        *second++ = '\0';
        last = strchr(second, '\t');
        if (last == NULL) { success = 0; break; }
        *last++ = '\0';
        if (strchr(last, '\t') != NULL) { success = 0; break; }
        if (!ValidateRecord(first, second, last,
                            llm + 1U, maths + 1U)) {
            fprintf(stderr, "Invalid or unordered inventory record: line %u\n", line);
            success = 0;
            break;
        }
        if (!ExistsFile(root, last)) {
            fprintf(stderr, "Missing or empty HTML lesson: %s\n", last);
            success = 0;
            break;
        }
        if (strcmp(first, "llm") == 0) ++llm;
        else ++maths;
    }
    if (ferror(file)) success = 0;
    (void)fclose(file);
    if (!success || llm != 94U || maths != 20U) {
        fprintf(stderr, "Incomplete course catalogue: LLM=%u/94, maths=%u/20\n",
                llm, maths);
        return 0;
    }
    return 1;
}

static int CheckMigration(const char *root)
{
    static const char *const expected[] = {
        "content/lessons/10-native-ai/93-check-real-tape-evidence.md",
        "content/lessons/10-native-ai/94-plan-a-fused-rotary-tape-operator.md",
        "content/lessons/11-maths-for-ai/19-evidence-thresholds-and-uncertainty.md",
        "content/lessons/11-maths-for-ai/20-matrix-chain-rule-and-computation-graphs.md",
        "content/videos/scripts/llm-from-scratch/93-check-real-tape-evidence.md",
        "content/videos/scripts/llm-from-scratch/94-plan-a-fused-rotary-tape-operator.md",
        "content/videos/scripts/maths-for-ai/19-evidence-thresholds-and-uncertainty.md",
        "content/videos/scripts/maths-for-ai/20-matrix-chain-rule-and-computation-graphs.md",
        "content/courses/llm-from-scratch/all-lessons.html"
    };
    static const char *const superseded[] = {
        "content/courses/llm-from-scratch/lessons/93-check-real-tape-evidence.md",
        "content/courses/llm-from-scratch/lessons/94-plan-a-fused-rotary-tape-operator.md",
        "content/courses/maths-for-ai/lessons/19-evidence-thresholds-and-uncertainty.md",
        "content/courses/maths-for-ai/lessons/20-matrix-chain-rule-and-computation-graphs.md"
    };
    size_t i;
    for (i=0U; i<sizeof(expected)/sizeof(expected[0]); ++i) {
        if (!ExistsFile(root, expected[i])) {
            fprintf(stderr, "Expected relocated or supporting file missing: %s\n",
                    expected[i]);
            return 0;
        }
    }
    for (i=0U; i<sizeof(superseded)/sizeof(superseded[0]); ++i) {
        if (!MissingFile(root, superseded[i])) {
            fprintf(stderr, "Superseded lesson still present or unreadable: %s\n",
                    superseded[i]);
            return 0;
        }
    }
    return 1;
}

static int SelfTest(void)
{
    if (IsSafeRelative("") || IsSafeRelative("/root/thing") ||
        IsSafeRelative("../private") || IsSafeRelative("a/../private") ||
        IsSafeRelative("a//b") || IsSafeRelative("a\\b") ||
        !IsSafeRelative("content/courses/llm-from-scratch/index.html"))
        return 0;
    if (!ValidateRecord("llm", "93",
                        "content/courses/llm-from-scratch/lessons/93-check-real-tape-evidence.html",
                        93U, 1U)) return 0;
    if (ValidateRecord("llm", "93",
                       "content/courses/llm-from-scratch/lessons/94-plan-a-fused-rotary-tape-operator.html",
                       93U, 1U)) return 0;
    if (ValidateRecord("maths", "20",
                       "content/courses/maths-for-ai/lessons/20-matrix-chain-rule-and-computation-graphs.md",
                       1U, 20U)) return 0;
    return 1;
}

int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--self-test") == 0) {
        if (!SelfTest()) {
            fputs("FAIL: inventory validator self-test\n", stderr);
            return EXIT_FAILURE;
        }
        puts("PASS: safe path, sequence and rejection examples");
        return EXIT_SUCCESS;
    }
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Bits2Banking repository root>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (!CheckInventory(argv[1]) || !CheckMigration(argv[1])) {
        fputs("FAIL: structural inventory or migration gate\n", stderr);
        return EXIT_FAILURE;
    }
    puts("PASS: 94 LLM HTML pages, 20 maths HTML units; four relocations; no old duplicates");
    return EXIT_SUCCESS;
}
