# Requests and task input

A browser can send a request to a server. PHP code runs on the server and prepares a response. The browser receives the resulting page, not the PHP source.

## 1. Open the source without a server

Read [the task-entry source](../../../labs/php-tasks/index.php) as a text file in your editor. If a learning host downloads it or executes it instead, use your local repository copy. You can follow every step on paper. Optional execution requires a local PHP environment with the mbstring extension; opening a .php file as an ordinary local browser file does not execute its server logic.

 <svg viewbox="0 0 700 110" role="img" aria-label="The server prepares a new response for each request." style="width:100%;max-width:700px"><title>The server prepares a new response for each request.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">browser form</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">PHP request handler</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">HTML response</text></svg>

The server prepares a new response for each request.

## 2. Read the variables

```text
$task = '';
$message = '';
```

The dollar sign begins a PHP variable name. The equals sign assigns a value. Two quotes with nothing between create an empty string. A semicolon ends a statement. The values start afresh when this request is handled; they do not form a shared permanent task database.

## 3. Separate viewing from submitting

The condition `$_SERVER['REQUEST_METHOD'] === 'POST'` checks whether this request submits the form. The triple equals performs a strict comparison, including type. `$_SERVER` is a server-provided collection of request information. `$_POST` holds parsed form inputs for this kind of request. Neither collection should be treated as permission to perform arbitrary actions.

 ```text
$task = trim((string)($_POST['task'] ?? ''));
```


Start with the innermost expression. Look for the form key task; `??` supplies an empty string when it is absent or null. The string cast requests text. `trim` removes certain surrounding whitespace characters. A crafted request can supply a non-scalar value: casting alone is not a complete shape check and can produce a warning. The current lab is a small form demonstration, not a hardened public endpoint. 

```text
$message = umicom_task_message($_POST['task'] ?? '');
```


Start with the innermost expression. Look for the form key task; `??` supplies an empty string when it is absent or null. The function in [task_input.php](../../../labs/php-tasks/task_input.php) checks that the supplied value is a string before using it. It bounds bytes, requires valid UTF-8, trims surrounding whitespace and checks the character limit. Array-valued input produces a text-validation message instead of a conversion warning.


The page locates that helper through `__DIR__`, the directory containing the PHP source, rather than assuming a working directory. The old cast-based handler remains inactive for comparison. Input validation alone does not make this a complete authenticated public service.

 

## 4. Match the form fields


The input element has `name="task"`, which determines the submitted key. Its id connects it with `<label for="task">`. A label makes the field understandable and easier to select. The button submits the form. The method attribute selects POST. No database write occurs in this example.

 

## 5. Trace a request


1. A normal page view starts with an empty message.
2. Submit an invented task such as Read the Kernel guide.
3. The handler trims it, checks it and builds a message.
4. The response includes that message as text.


Predict what three spaces become after trimming. Answer: the empty string, which takes the prompt-to-enter-a-task branch. In a future Umicom web client, a reusable C23 service can own task validation and persistence while a frontend presents the result. This course does not claim that such a shared server is already deployed.

---

[Read this lesson in HTML](../../../courses/learning-php/lessons/01-requests-and-task-input.html) · [Learning sequence](../../../start/learning-sequence.md)
