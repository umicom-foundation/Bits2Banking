-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/database/course-progress/savepoint.sql
--
-- PURPOSE:
--   Retain a valid outer change while discarding a nested experiment.
--
-- AUTHOR AND ORGANISATION:
-- Sammy Hegab
-- Umicom Foundation
--
-- LICENCE:
-- MIT
-- -----------------------------------------------------------------------------

BEGIN;
UPDATE progress SET completed = 4 WHERE learner_id = 1 AND course_id = 1;
SAVEPOINT experiment;
UPDATE progress SET completed = 5 WHERE learner_id = 1 AND course_id = 1;
ROLLBACK TO experiment;
RELEASE experiment;
SELECT completed AS retained_outer_value FROM progress
WHERE learner_id = 1 AND course_id = 1;
ROLLBACK;

