<?php
/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: content/labs/php-tasks/test_task_input.php
 *
 * PURPOSE:
 *   Check task input types, encoding and boundaries without starting a web server.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

require_once __DIR__ . '/task_input.php';

function check_task($input, string $expected): void
{
    $actual = umicom_task_message($input);
    if ($actual !== $expected) {
        fwrite(STDERR, "Unexpected task-validation response.\n");
        exit(1);
    }
}

foreach ([[], ['task'], 7, true, null] as $input) {
    check_task($input, 'A task must be text.');
}
check_task(str_repeat('x', 481), 'A task must be at most 120 characters.');
if (!function_exists('mb_check_encoding') || !function_exists('mb_strlen')) {
    check_task('Read', 'Text validation is unavailable. Enable the mbstring extension.');
    fwrite(STDERR, "Input-shape checks passed; UTF-8 cases skipped because mbstring is unavailable.\n");
    exit(77);
}
check_task('', 'Please enter a task.');
check_task('   ', 'Please enter a task.');
check_task(' Read the Kernel guide ', 'Received task: Read the Kernel guide');
check_task("\xff", 'A task must use valid UTF-8 text.');
check_task(str_repeat('x', 120), 'Received task: ' . str_repeat('x', 120));
check_task(str_repeat('x', 121), 'A task must be at most 120 characters.');
check_task(str_repeat('é', 120), 'Received task: ' . str_repeat('é', 120));
check_task(str_repeat('é', 121), 'A task must be at most 120 characters.');
check_task('<b>Read</b>', 'Received task: <b>Read</b>');
// Validation returns data. The page must still encode it for its HTML context.
if (htmlspecialchars(umicom_task_message('<b>Read</b>'),
        ENT_QUOTES | ENT_SUBSTITUTE, 'UTF-8') !== 'Received task: &lt;b&gt;Read&lt;/b&gt;') {
    fwrite(STDERR, "HTML output encoding did not preserve task text.\n");
    exit(1);
}
fwrite(STDOUT, "Task input checks passed.\n");
