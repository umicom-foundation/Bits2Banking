-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/database/course-progress/constraint-rollback.sql
--
-- PURPOSE:
--   Observe a rejected duplicate and undo the earlier change in its transaction.
--
-- AUTHOR AND ORGANISATION:
-- Sammy Hegab
-- Umicom Foundation
--
-- LICENCE:
-- MIT
-- -----------------------------------------------------------------------------

-- Read schema.sql and seed.sql in a disposable database first. The SQLite
-- shell's .bail off setting lets the exercise inspect the expected refusal.
SELECT 'before' AS stage, completed, (SELECT COUNT(*) FROM progress) AS all_rows
FROM progress WHERE learner_id = 1 AND course_id = 1;

-- This change is visible on the same connection while the transaction is open.
BEGIN;
UPDATE progress SET completed = 4 WHERE learner_id = 1 AND course_id = 1;

-- The same learner and course already form a primary key. SQLite refuses this
-- statement while the earlier update stays staged on the same connection.
INSERT INTO progress (learner_id, course_id, completed) VALUES (1, 1, 8);
SELECT 'after-refusal' AS stage, completed, (SELECT COUNT(*) FROM progress) AS all_rows
FROM progress WHERE learner_id = 1 AND course_id = 1;

-- The application makes the rollback explicit after the expected failure.
ROLLBACK;
SELECT 'after-rollback' AS stage, completed, (SELECT COUNT(*) FROM progress) AS all_rows
FROM progress WHERE learner_id = 1 AND course_id = 1;
