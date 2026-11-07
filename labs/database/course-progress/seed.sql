-- -----------------------------------------------------------------------------
-- Umicom Bits2Banking
-- File: labs/database/course-progress/seed.sql
--
-- PURPOSE:
--   Insert a repeatable fictional dataset for relational learning exercises.
--
-- AUTHOR AND ORGANISATION:
-- Sammy Hegab
-- Umicom Foundation
--
-- LICENCE:
-- MIT
-- -----------------------------------------------------------------------------

BEGIN;
INSERT INTO course VALUES
    (1, 'Learning C', 10),
    (2, 'Learning RISC-V', 8),
    (3, 'Learning HDL', 6);
INSERT INTO learner VALUES (1, 'Learner A'), (2, 'Learner B'), (3, 'Learner C');
INSERT INTO progress VALUES (1, 1, 3), (1, 2, 0), (2, 1, 10), (2, 3, 2);
COMMIT;

