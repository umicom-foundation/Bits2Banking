-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/database/course-progress/integrity.sql
--
-- PURPOSE:
--   Separate SQLite structural checks from an application-level progress rule.
--
-- AUTHOR AND ORGANISATION:
-- Sammy Hegab
-- Umicom Foundation
--
-- LICENCE:
-- MIT
-- -----------------------------------------------------------------------------

PRAGMA quick_check;
PRAGMA foreign_key_check;
-- The table CHECK cannot compare completed with another table's lesson_count.
SELECT p.learner_id, p.course_id, p.completed, c.lesson_count
FROM progress AS p JOIN course AS c ON c.course_id = p.course_id
WHERE p.completed > c.lesson_count;

