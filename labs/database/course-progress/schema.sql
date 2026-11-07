-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/database/course-progress/schema.sql
--
-- PURPOSE:
--   Define a small fictional course catalogue with explicit keys and constraints.
--
-- AUTHOR AND ORGANISATION:
-- Sammy Hegab
-- Umicom Foundation
--
-- LICENCE:
-- MIT
-- -----------------------------------------------------------------------------

PRAGMA foreign_keys = ON;
BEGIN;
CREATE TABLE course (
    course_id INTEGER PRIMARY KEY,
    title TEXT NOT NULL UNIQUE,
    lesson_count INTEGER NOT NULL CHECK (lesson_count BETWEEN 1 AND 200)
);
CREATE TABLE learner (
    learner_id INTEGER PRIMARY KEY,
    display_name TEXT NOT NULL CHECK (length(display_name) BETWEEN 1 AND 40)
);
CREATE TABLE progress (
    learner_id INTEGER NOT NULL REFERENCES learner(learner_id),
    course_id INTEGER NOT NULL REFERENCES course(course_id),
    completed INTEGER NOT NULL CHECK (completed BETWEEN 0 AND 200),
    PRIMARY KEY (learner_id, course_id)
);
COMMIT;

