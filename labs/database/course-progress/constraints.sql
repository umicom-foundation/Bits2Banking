-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/database/course-progress/constraints.sql
--
-- PURPOSE:
--   Expose one deliberate foreign-key failure for an interactive diagnostic exercise.
--
-- AUTHOR AND ORGANISATION:
-- Sammy Hegab
-- Umicom Foundation
--
-- LICENCE:
-- MIT
-- -----------------------------------------------------------------------------

-- Run interactively after schema.sql and seed.sql.
-- The first statement is intentionally invalid and must report a foreign-key error.
PRAGMA foreign_keys = ON;
INSERT INTO progress VALUES (99, 1, 1);
-- The invalid statement must not add a progress row.
SELECT COUNT(*) AS unchanged_rows FROM progress;

