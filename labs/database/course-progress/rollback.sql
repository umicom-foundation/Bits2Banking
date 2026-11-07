-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/database/course-progress/rollback.sql
--
-- PURPOSE:
--   Demonstrate a temporary edit and rollback without leaving changed progress.
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
SELECT completed AS during_transaction FROM progress
WHERE learner_id = 1 AND course_id = 1;
ROLLBACK;
SELECT completed AS after_rollback FROM progress
WHERE learner_id = 1 AND course_id = 1;

