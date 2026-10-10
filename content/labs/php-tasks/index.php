<?php
$task = '';
$message = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $task = trim((string)($_POST['task'] ?? ''));

    if ($task === '') {
        $message = 'Please enter a task.';
    } elseif (mb_strlen($task) > 120) {
        $message = 'A task must be at most 120 characters.';
    } else {
        $message = 'Received task: ' . $task;
    }
}
?>
<!doctype html>
<html lang="en-GB">
<head><meta charset="utf-8"><title>Umicom Task Entry</title></head>
<body>
  <h1>Umicom Task Entry</h1>
  <form method="post">
    <label for="task">Task</label>
    <input id="task" name="task" maxlength="120" required>
    <button type="submit">Send</button>
  </form>
  <p><?= htmlspecialchars($message, ENT_QUOTES | ENT_SUBSTITUTE, 'UTF-8') ?></p>
</body>
</html>
