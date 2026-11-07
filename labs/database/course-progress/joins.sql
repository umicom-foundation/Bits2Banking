-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/database/course-progress/joins.sql
--
-- PURPOSE:
--   Show matching rows and learners with no course progress.
--
-- AUTHOR AND ORGANISATION:
-- Sammy Hegab
-- Umicom Foundation
--
-- LICENCE:
-- MIT
-- -----------------------------------------------------------------------------

SELECT l.display_name, c.title, p.completed, c.lesson_count
FROM progress AS p
JOIN learner AS l ON l.learner_id = p.learner_id
JOIN course AS c ON c.course_id = p.course_id
ORDER BY l.learner_id, c.course_id;

SELECT l.display_name, p.course_id
FROM learner AS l
LEFT JOIN progress AS p ON p.learner_id = l.learner_id
ORDER BY l.learner_id, p.course_id;

