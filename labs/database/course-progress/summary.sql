-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/database/course-progress/summary.sql
--
-- PURPOSE:
--   Aggregate recorded progress while keeping missing enrolments distinct from zero.
--
-- AUTHOR AND ORGANISATION:
-- Sammy Hegab
-- Umicom Foundation
--
-- LICENCE:
-- MIT
-- -----------------------------------------------------------------------------

SELECT c.title, COUNT(p.learner_id) AS enrolments,
       COALESCE(SUM(p.completed), 0) AS completed_lessons
FROM course AS c
LEFT JOIN progress AS p ON p.course_id = c.course_id
GROUP BY c.course_id, c.title
ORDER BY c.course_id;

