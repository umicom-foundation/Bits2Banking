-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/database/course-progress/read.sql
--
-- PURPOSE:
--   Project, filter and order progress rows without changing stored data.
--
-- AUTHOR AND ORGANISATION:
-- Sammy Hegab
-- Umicom Foundation
--
-- LICENCE:
-- MIT
-- -----------------------------------------------------------------------------

SELECT title, lesson_count FROM course ORDER BY course_id;
SELECT learner_id, course_id, completed FROM progress
WHERE completed > 0 ORDER BY completed DESC, learner_id, course_id;
SELECT title FROM course WHERE course_id = 99;

