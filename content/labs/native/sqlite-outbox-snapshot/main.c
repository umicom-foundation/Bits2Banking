/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/sqlite-outbox-snapshot/main.c
 *
 * PURPOSE:
 *   Observe a consistent page across a separate SQLite writer commit.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <errno.h>
#include <sqlite3.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

#define SCRATCH_DIRECTORY "outbox-snapshot-scratch"
#define DATABASE_FILE SCRATCH_DIRECTORY "/outbox-snapshot.sqlite3"

typedef struct Entry {
    int revision;
    int amount;
} Entry;

static bool OpenDatabase(int flags, sqlite3 **database)
{
    const int code = sqlite3_open_v2(DATABASE_FILE, database, flags, NULL);
    if (code == SQLITE_OK) return true;
    fprintf(stderr, "Open synthetic database: %s\n", sqlite3_errstr(code));
    return false;
}

static bool RunSql(sqlite3 *database, const char *sql, const char *operation)
{
    if (sqlite3_exec(database, sql, NULL, NULL, NULL) == SQLITE_OK) return true;
    fprintf(stderr, "%s: %s\n", operation, sqlite3_errmsg(database));
    return false;
}

static bool EnableWal(sqlite3 *database)
{
    /* SQLite returns the actual mode. Successful execution alone does not
     * prove the filesystem and SQLite build support concurrent WAL readers. */
    sqlite3_stmt *statement = NULL;
    bool wal = false;
    if (sqlite3_prepare_v2(database, "PRAGMA journal_mode=WAL", -1, &statement, NULL) == SQLITE_OK &&
        sqlite3_step(statement) == SQLITE_ROW) {
        const unsigned char *result = sqlite3_column_text(statement, 0);
        wal = result != NULL && strcmp((const char *)result, "wal") == 0;
    }
    const int finished = sqlite3_finalize(statement);
    if (wal && finished == SQLITE_OK) return true;
    fputs("Enable WAL: choose a local filesystem and SQLite with WAL support.\n", stderr);
    return false;
}

static bool ReadEntry(sqlite3 *reader, int entry_id, Entry *out)
{
    /* Bind the ID as an integer and finalize each SELECT. The open read
     * transaction, rather than a leftover statement, must pin the page. */
    sqlite3_stmt *statement = NULL;
    Entry entry = {0};
    bool found = false;
    if (sqlite3_prepare_v2(reader, "SELECT revision, amount FROM outbox WHERE id = ?1",
                           -1, &statement, NULL) == SQLITE_OK &&
        sqlite3_bind_int(statement, 1, entry_id) == SQLITE_OK &&
        sqlite3_step(statement) == SQLITE_ROW) {
        entry.revision = sqlite3_column_int(statement, 0);
        entry.amount = sqlite3_column_int(statement, 1);
        found = sqlite3_step(statement) == SQLITE_DONE;
    }
    const int finished = sqlite3_finalize(statement);
    if (!found || finished != SQLITE_OK) {
        fprintf(stderr, "Read synthetic entry %d: %s\n", entry_id, sqlite3_errmsg(reader));
        return false;
    }
    *out = entry;
    return true;
}

static bool CheckEntry(Entry entry, int revision, int amount, const char *phase)
{
    if (entry.revision == revision && entry.amount == amount) return true;
    fprintf(stderr, "%s: expected revision %d amount %d, observed revision %d amount %d\n",
            phase, revision, amount, entry.revision, entry.amount);
    return false;
}

static bool CloseDatabase(sqlite3 *database)
{
    if (database == NULL) return true;
    /* Finalizing all statements allows SQLite to close and roll back any
     * transaction left open by an error. */
    const int code = sqlite3_close(database);
    if (code == SQLITE_OK) return true;
    fprintf(stderr, "Close synthetic database: %s\n", sqlite3_errstr(code));
    return false;
}

/* Preserve the original entry point for review. The dispatcher below keeps
 * the no-argument snapshot exercise while adding another C23 observation. */
#if 0
int main(void)
#endif
static int ShowSnapshot(void)
{
    /* Own a fresh directory before SQLite can create a database or sidecars.
     * An existing directory is refused without inspecting or removing it. */
#ifdef _WIN32
    const int created = _mkdir(SCRATCH_DIRECTORY);
#else
    const int created = mkdir(SCRATCH_DIRECTORY, 0700);
#endif
    if (created != 0) {
        fprintf(stderr, "Create %s: %s. Use a fresh local working folder.\n",
                SCRATCH_DIRECTORY, strerror(errno));
        return 1;
    }

    sqlite3 *writer = NULL;
    sqlite3 *reader = NULL;
    Entry before = {0}, pinned = {0}, refreshed_first = {0}, refreshed_second = {0};
    bool verified = false;
    if (!OpenDatabase(SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, &writer) ||
        !EnableWal(writer) ||
        !RunSql(writer, "CREATE TABLE outbox (id INTEGER PRIMARY KEY, "
                       "revision INTEGER NOT NULL, amount INTEGER NOT NULL);"
                       "INSERT INTO outbox VALUES (1, 1, 100), (2, 1, 250);",
                "Seed synthetic entries") ||
        !OpenDatabase(SQLITE_OPEN_READONLY, &reader) ||
        !RunSql(reader, "BEGIN", "Begin reader snapshot") ||
        !ReadEntry(reader, 1, &before) ||
        !CheckEntry(before, 1, 100, "First entry before writer commit"))
        goto done;

    /* This connection commits both changes while the reader still holds its
     * first view. The exercise does not depend on sleeps or thread scheduling. */
    if (!RunSql(writer, "BEGIN IMMEDIATE;"
                       "UPDATE outbox SET revision = 2, amount = amount + 10;"
                       "COMMIT;",
                "Commit synthetic revision") ||
        !ReadEntry(reader, 2, &pinned) ||
        !CheckEntry(pinned, 1, 250, "Second entry in the same snapshot") ||
        !RunSql(reader, "COMMIT", "End first reader snapshot") ||
        !RunSql(reader, "BEGIN", "Begin refreshed reader snapshot") ||
        !ReadEntry(reader, 1, &refreshed_first) ||
        !ReadEntry(reader, 2, &refreshed_second) ||
        !CheckEntry(refreshed_first, 2, 110, "Refreshed first entry") ||
        !CheckEntry(refreshed_second, 2, 260, "Refreshed second entry") ||
        !RunSql(reader, "COMMIT", "End refreshed reader snapshot"))
        goto done;

    /* A connection opened read-only must reject the same kind of write that
     * the writer performed. A separate BEGIN is unnecessary for this check. */
    if (sqlite3_exec(reader, "UPDATE outbox SET amount = 0", NULL, NULL, NULL) != SQLITE_READONLY) {
        fputs("Expected the reader connection to refuse an update.\n", stderr);
        goto done;
    }
    verified = true;

done:
    const bool reader_closed = CloseDatabase(reader);
    const bool writer_closed = CloseDatabase(writer);
    if (!reader_closed || !writer_closed) return 1;
    /* SQLite drops its WAL sidecars after the final close. Remove only the
     * owned fixed database and then the now-empty directory, never a tree. */
    if (remove(DATABASE_FILE) != 0 && errno != ENOENT) {
        perror("Remove synthetic database");
        return 1;
    }
#ifdef _WIN32
    const int removed = _rmdir(SCRATCH_DIRECTORY);
#else
    const int removed = rmdir(SCRATCH_DIRECTORY);
#endif
    if (removed != 0) {
        perror("Remove empty scratch directory");
        return 1;
    }
    if (!verified) return 1;
    printf("Before writer commit: entry 1 revision %d amount %d\n", before.revision, before.amount);
    printf("Same snapshot after writer commit: entry 2 revision %d amount %d\n",
           pinned.revision, pinned.amount);
    printf("New snapshot: entry 1 revision %d amount %d, entry 2 revision %d amount %d\n",
           refreshed_first.revision, refreshed_first.amount,
           refreshed_second.revision, refreshed_second.amount);
    puts("Reader write refused. Scratch database removed.");
    return fflush(stdout) == 0 ? 0 : 1;
}


enum { TITLE_BYTE_LIMIT = 7 };

typedef struct TitleObservation {
    int revision;
    int code_points;
    int bytes;
    char title[32];
} TitleObservation;

static bool ObserveTitle(sqlite3 *database, TitleObservation *out)
{
    /* The temporary database uses UTF-8. The same stored text can be measured
     * as Unicode code points or as a byte sequence without changing its value. */
    sqlite3_stmt *statement = NULL;
    TitleObservation next = {0};
    bool copied = false;
    const char query[] = "SELECT revision, length(title), length(CAST(title AS BLOB)), title "
                         "FROM note WHERE id = 1";
    if (sqlite3_prepare_v2(database, query, -1, &statement, NULL) == SQLITE_OK &&
        sqlite3_step(statement) == SQLITE_ROW) {
        next.revision = sqlite3_column_int(statement, 0);
        next.code_points = sqlite3_column_int(statement, 1);
        next.bytes = sqlite3_column_int(statement, 2);
        const unsigned char *title = sqlite3_column_text(statement, 3);
        if (title != NULL && next.bytes == sqlite3_column_bytes(statement, 3) &&
            next.bytes >= 0 && (size_t)next.bytes < sizeof next.title) {
            memcpy(next.title, title, (size_t)next.bytes + 1U);
            copied = true;
        }
    }
    const int finished = sqlite3_finalize(statement);
    if (!copied || finished != SQLITE_OK) return false;
    *out = next;
    return true;
}

static bool EditObservedTitle(sqlite3 *database, int observed_revision,
                              const char *proposed, int *out_changes)
{
    /* One UPDATE owns both predicates and the publish. Checking the revision
     * with an earlier SELECT would leave a gap before changing the row. */
    sqlite3_stmt *statement = NULL;
    const char update[] = "UPDATE note SET title = ?1, revision = revision + 1 "
                          "WHERE id = 1 AND revision = ?2 "
                          "AND length(CAST(?1 AS BLOB)) <= ?3";
    const bool updated = sqlite3_prepare_v2(database, update, -1, &statement, NULL) == SQLITE_OK &&
        sqlite3_bind_text(statement, 1, proposed, -1, SQLITE_STATIC) == SQLITE_OK &&
        sqlite3_bind_int(statement, 2, observed_revision) == SQLITE_OK &&
        sqlite3_bind_int(statement, 3, TITLE_BYTE_LIMIT) == SQLITE_OK &&
        sqlite3_step(statement) == SQLITE_DONE;
    const int finished = sqlite3_finalize(statement);
    if (!updated || finished != SQLITE_OK) return false;
    *out_changes = sqlite3_changes(database);
    return true;
}

static bool CheckObservedTitle(TitleObservation title, const char *text, int revision)
{
    /* Check every accepted field after refusals, not only rows changed. */
    return title.revision == revision && title.code_points == 3 &&
        title.bytes == TITLE_BYTE_LIMIT && strcmp(title.title, text) == 0;
}

static int ShowObservedEdit(void)
{
    /* Acute accent is encoded separately from e, followed by a supplementary
     * rocket. The examples are known valid and do not involve user input. */
    static const char fits[] = "e\xcc\x81\xf0\x9f\x9a\x80";
    static const char too_long[] = "Xe\xcc\x81\xf0\x9f\x9a\x80";
    sqlite3 *database = NULL;
    TitleObservation first = {0}, second = {0}, accepted = {0}, after = {0};
    int first_changes = -1, stale_changes = -1, long_changes = -1;
    int result = 1;

    /* One memory-only table keeps the observation/commit schedule deterministic.
     * Each editor holds its own copied version before either submits an edit. */
    if (sqlite3_open_v2(":memory:", &database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
                       NULL) != SQLITE_OK ||
        !RunSql(database, "PRAGMA encoding='UTF-8';"
                          "CREATE TABLE note(id INTEGER PRIMARY KEY, title TEXT NOT NULL, "
                          "revision INTEGER NOT NULL);"
                          "INSERT INTO note VALUES (1, 'Ready', 1);", "Seed synthetic title") ||
        !ObserveTitle(database, &first) ||
        !ObserveTitle(database, &second) ||
        first.revision != 1 || second.revision != 1 ||
        strcmp(first.title, "Ready") != 0 || strcmp(second.title, "Ready") != 0 ||
        !EditObservedTitle(database, first.revision, fits, &first_changes) ||
        first_changes != 1 ||
        !ObserveTitle(database, &accepted) ||
        !CheckObservedTitle(accepted, fits, 2)) {
        fputs("The first observed edit did not publish exactly one new revision.\n", stderr);
        goto done;
    }

    /* The second editor sends a valid short title using the old revision.
     * The oversize attempt uses the current revision, isolating its byte limit. */
    if (!EditObservedTitle(database, second.revision, "Draft", &stale_changes) ||
        stale_changes != 0 || !ObserveTitle(database, &after) ||
        !CheckObservedTitle(after, fits, 2)) {
        fputs("The stale edit changed the accepted title or revision.\n", stderr);
        goto done;
    }
    if (sizeof too_long - 1U != TITLE_BYTE_LIMIT + 1U ||
        !EditObservedTitle(database, accepted.revision, too_long, &long_changes) ||
        long_changes != 0 || !ObserveTitle(database, &after) ||
        !CheckObservedTitle(after, fits, 2)) {
        fputs("The oversize edit changed the accepted title or revision.\n", stderr);
        goto done;
    }
    result = 0;

done:
    if (!CloseDatabase(database) || result != 0) return 1;
    printf("Both editors observed revision %d.\n", first.revision);
    printf("First edit: %d row, revision %d, %d code points, %d UTF-8 bytes.\n",
           first_changes, accepted.revision, accepted.code_points, accepted.bytes);
    printf("Stale short edit: %d rows changed; revision %d kept.\n", stale_changes, after.revision);
    printf("Current %zu-byte edit: %d rows changed; revision %d kept.\n",
           sizeof too_long - 1U, long_changes, after.revision);
    return fflush(stdout) == 0 && ferror(stdout) == 0 ? 0 : 1;
}

int main(int argc, char **argv)
{
    /* Keep the original exercise as the default. The named exercise uses
     * SQLite memory only and never enters the scratch-file workflow. */
    if (argc == 1) return ShowSnapshot();
    if (argc == 2 && strcmp(argv[1], "observed-edit") == 0) return ShowObservedEdit();
    fputs("Usage: btb-sqlite-outbox-snapshot [observed-edit]\n", stderr);
    return 2;
}
