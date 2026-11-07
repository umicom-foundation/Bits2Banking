-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/database/course-progress/checks.sql
--
-- PURPOSE:
--   Assert seeded results and rollback behavior using temporary SQL constraints.
--
-- AUTHOR AND ORGANISATION:
-- Sammy Hegab
-- Umicom Foundation
--
-- LICENCE:
-- MIT
-- -----------------------------------------------------------------------------

CREATE TEMP TABLE expected_true (value INTEGER NOT NULL CHECK (value = 1));
INSERT INTO expected_true SELECT COUNT(*) = 3 FROM course;
INSERT INTO expected_true SELECT COUNT(*) = 4 FROM progress;
INSERT INTO expected_true SELECT SUM(completed) = 15 FROM progress;
INSERT INTO expected_true SELECT COUNT(*) = 1 FROM learner AS l
WHERE NOT EXISTS (SELECT 1 FROM progress AS p WHERE p.learner_id = l.learner_id);
BEGIN;
UPDATE progress SET completed = 4 WHERE learner_id = 1 AND course_id = 1;
INSERT INTO expected_true SELECT completed = 4 FROM progress
WHERE learner_id = 1 AND course_id = 1;
ROLLBACK;
INSERT INTO expected_true SELECT completed = 3 FROM progress
WHERE learner_id = 1 AND course_id = 1;
SELECT 'Course progress checks reached the end' AS observation;

