# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/test_sql_transaction_exercise.py
#
# PURPOSE:
#   Validate the actual lesson statements on a disposable SQLite connection.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------

from contextlib import closing
from pathlib import Path
import sqlite3


def test_duplicate_statement_leaves_staged_update_until_rollback():
    lab = Path(__file__).resolve().parents[1] / "labs" / "database" / "course-progress"
    with closing(sqlite3.connect(":memory:")) as database:
        for baseline in ("schema.sql", "seed.sql"):
            database.executescript((lab / baseline).read_text(encoding="utf-8"))

        # Submit the same complete statements as .read with .bail off. Record
        # the one deliberate refusal while allowing the exercise to roll back.
        statement = ""
        errors = []
        observations = []
        for line in (lab / "constraint-rollback.sql").read_text(encoding="utf-8").splitlines(keepends=True):
            statement += line
            if not sqlite3.complete_statement(statement):
                continue
            try:
                result = database.execute(statement)
                if result.description is not None:
                    observations.extend((*row, database.in_transaction) for row in result.fetchall())
            except sqlite3.IntegrityError as error:
                errors.append(error.sqlite_errorcode)
            statement = ""

        assert not statement.strip()
        assert errors == [sqlite3.SQLITE_CONSTRAINT_PRIMARYKEY]
        assert observations == [
            ("before", 3, 4, False),
            ("after-refusal", 4, 4, True),
            ("after-rollback", 3, 4, False),
        ]
