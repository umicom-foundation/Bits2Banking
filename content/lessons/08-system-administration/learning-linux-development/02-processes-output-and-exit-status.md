# Processes, output and exit status

[Course contents](index.md) · [Previous: Your first user-space build](01-your-first-user-space-build.md)

## What happens when a program runs

Continue with `hello` from the previous lesson. An executable is a file; a process is a running instance of a program. The shell starts it, waits when appropriate and receives an exit status when it finishes. By convention, zero means success and a nonzero value indicates a problem or another documented outcome.

Programs normally have standard output for results and standard error for diagnostics. They are separate streams even when both appear in the same terminal.

## Capture a result in your chosen folder

```sh
./hello > output.txt 2> errors.txt
result=$?
printf 'Program status: %s\n' "$result"
cat output.txt
cat errors.txt
```

`>` writes standard output to a file, replacing that file's previous contents. `2>` redirects standard error. Choose disposable practice filenames. `result=$?` saves the status immediately, before another command replaces it. Expect the learning message in output.txt, an empty errors.txt and status zero.

An empty error log does not prove every behaviour is correct: a faulty program might report nothing. You still need an expected result and a check. Similarly, text in a log is not necessarily an error; classify its actual meaning.

## Exercise and answer

In a practice copy of hello.c, change `return 0;` to `return 3;`, rebuild successfully and repeat the commands. The message is unchanged, but the status becomes 3. This demonstrates why looking only for visible output misses failures. Restore the original return value afterward.

## Follow the same idea in Umicom

Read the activity console's handling of `UmiStatus`. The service reports a domain result; the application decides how to display it and which process status to return. Build, test and launch logs should preserve both diagnostics and the command's actual outcome. A later module will cover pipelines, whose final command's status may hide an earlier failure unless handled deliberately.

Never solve a permission error by automatically running the whole development workflow as administrator. First identify the requested path and use a practice folder you own. Learning the boundary between your program and the operating system makes troubleshooting much more precise.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/console.c). Path: `labs/native/framework-activity/console.c`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://docs.kernel.org/process/howto.html). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-linux-development/lessons/02-processes-output-and-exit-status.html).

[Course contents](index.md) · [Previous: Your first user-space build](01-your-first-user-space-build.md)

Sammy Hegab · Umicom Foundation · Original learning material.
