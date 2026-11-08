# Validation and HTML output

Validation decides whether input is acceptable. Output encoding decides how accepted or rejected text is safely represented in a particular output format. They solve different problems.

## 1. Read the two server checks

 In [index.php](../../../labs/php-tasks/index.php), empty text produces Please enter a task. Otherwise, `mb_strlen($task) > 120` checks its length. The mbstring extension supplies multibyte string functions. The current call uses the configured internal encoding; it does not explicitly set UTF-8. Server configuration therefore matters. A robust service should choose and validate an encoding deliberately.

[index.php](../../../labs/php-tasks/index.php) calls the validator in [task_input.php](../../../labs/php-tasks/task_input.php). It first refuses non-string input and more than 480 bytes, then checks that mbstring is available and the text is valid UTF-8. After trimming, empty text produces Please enter a task. `mb_strlen($task, 'UTF-8') > 120` enforces the code-point limit explicitly. One visible symbol can contain several code points, so this is not a count of screen glyphs. Missing mbstring produces an unavailable message rather than a fatal function-call error.

The HTML `maxlength` and `required` attributes help someone entering data in a browser. They do not secure the server: a program can send a request without using that form.

## 2. Understand output encoding

```text
htmlspecialchars($message, ENT_QUOTES | ENT_SUBSTITUTE, 'UTF-8')
```

This call prepares text for an HTML context. Characters such as less-than and ampersand receive encoded representations so the browser treats them as text. ENT_QUOTES includes both kinds of quotation mark. ENT_SUBSTITUTE handles invalid sequences using replacement characters in this conversion. The vertical bar combines these option flags.

<svg viewbox="0 0 700 110" role="img" aria-label="A task containing angle brackets should remain text in the response." style="width:100%;max-width:700px"><title>A task containing angle brackets should remain text in the response.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">task text</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">HTML encoding</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">visible text</text></svg>

A task containing angle brackets should remain text in the response.

The short echo syntax `<?= ... ?>` writes the expression result into the response. Encoding for HTML text is not a general solution for SQL queries, operating-system commands or every JavaScript context. Each boundary needs its own rules.

## 3. Predict visible results

Suppose an invented task is `<b>Read</b>`. The response should display those brackets and letters as part of the message, rather than turning the task into a bold HTML element. An empty task should produce the prompt, not a Received task message. A task over the server limit should produce the length message.

## 4. Name the missing product features

This lab has no sign-in, authorization, request-forgery protection for a future authenticated mutation, shared task store, rate limit or deployment configuration. It only receives input and displays a response. Do not describe it as a hosted collaborative Kanban service. The Umicom roadmap separates reusable workflow services from each desktop, web and mobile presentation.

## 5. Practice a design review

1. Find the browser-side limit.
2. Find the server-side limit.
3. Find the final HTML encoding.
4. Explain why removing any one changes behavior even when the others remain.

Answer: browser rules guide entry, server rules enforce acceptance for arbitrary requests, and output encoding protects the chosen display context. For the next step, compare [the browser-local task board](../learning-javascript/02-local-storage-and-untrusted-data.md): saving in one browser is also different from a shared authenticated server.

## Read the regression cases

[test_task_input.php](../../../labs/php-tasks/test_task_input.php) checks arrays, invalid UTF-8, exact and excessive limits, multibyte text and HTML encoding. In a prepared PHP 8-or-later environment, you can run `php test_task_input.php` from this lab directory. Exit77 means UTF-8 coverage was skipped because mbstring was unavailable; it is not a complete pass. Run these checks in your own environment; reading an expected result is not execution evidence.

---

[Read this lesson in HTML](../../../courses/learning-php/lessons/02-validation-and-html-output.html) · [Learning sequence](../../../start/learning-sequence.md)

[Next: Count text at the right boundary](03-count-text-at-the-right-boundary.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](01-requests-and-task-input.md)
