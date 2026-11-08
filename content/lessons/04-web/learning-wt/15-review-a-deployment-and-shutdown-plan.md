<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/15-review-a-deployment-and-shutdown-plan.md

PURPOSE:
Review deployment and shutdown as separate work

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Review deployment and shutdown as separate work

## Before starting

Complete the local build, event checks and browser observation. Keep the server bound to loopback for this course. A public deployment needs an explicitly selected host, network policy and operating procedure; this lesson produces a review plan rather than deploying the lab.

## Inventory what a running server needs

List the executable, matching runtime libraries, Wt resources, intended public assets and launch arguments. Keep application data and logs outside the public directory. Record how the chosen host locates each file when the working directory differs from your development terminal. A build folder is not automatically an installable package.

## State service boundaries

Name the address and port, who may connect, where encrypted transport terminates if used, and which layer enforces access and request limits. This lab has no account creation or authentication. A correctly validated display name does not authorize a user or make an unauthenticated service suitable for sensitive data.

## Plan startup and stopping

Describe a startup check that distinguishes a launched process from a responsive application. Define how the host requests shutdown, how long it waits and where failures are recorded. During a local rehearsal, stop only the lab process you started, observe its terminal and browser, and confirm whether a fresh launch can use the intended port. Do not infer a clean shutdown solely from a disappearing window.

## Review recovery before release

Preserve the previous known package and configuration outside public resources. Specify how to select that package again and how to retain diagnostic logs. If a deployment changes persistent data, its compatibility and recovery need a separate review; the current name-only lab has no such migration.

## Exercise and worked answer

A release note says deployed because cmake --build succeeded. What evidence is missing? Installation layout, runtime dependency loading, the actual startup command, endpoint observation and shutdown behaviour. Add those as pending checks with an identified target environment. Do not invent their outcomes to complete a checklist.

## Read the source

[labs/framework/wt-profile/README.md](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Plan bounded work across a session lifetime](14-plan-bounded-work-and-session-lifetime.md) · [Next: Assemble a web workflow evidence record](16-assemble-a-web-workflow-evidence-record.md)
