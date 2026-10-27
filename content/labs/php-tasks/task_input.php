<?php
/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: content/labs/php-tasks/task_input.php
 *
 * PURPOSE:
 *   Validate form text before counting characters or composing a response.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

function umicom_task_message($input): string
{
    // Form keys may contain arrays in a crafted request. Casting is not validation.
    if (!is_string($input)) {
        return 'A task must be text.';
    }
    // UTF-8 uses at most four bytes per code point. Bound work before decoding.
    if (strlen($input) > 480) {
        return 'A task must be at most 120 characters.';
    }
    if (!function_exists('mb_check_encoding') || !function_exists('mb_strlen')) {
        return 'Text validation is unavailable. Enable the mbstring extension.';
    }
    if (!mb_check_encoding($input, 'UTF-8')) {
        return 'A task must use valid UTF-8 text.';
    }
    $task = trim($input);
    if ($task === '') {
        return 'Please enter a task.';
    }
    if (mb_strlen($task, 'UTF-8') > 120) {
        return 'A task must be at most 120 characters.';
    }
    // HTML encoding belongs at the output boundary in index.php.
    return 'Received task: ' . $task;
}
