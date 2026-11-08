<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/13-diagnose-http-and-event-failures.md

PURPOSE:
Diagnose transport, resource and event failures

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Diagnose transport, resource and event failures

## Before starting

Keep the server terminal and browser developer tools visible. Use only the local lab and your own server process. Know the selected port and source revision. This exercise classifies evidence before changing code; it does not deliberately damage a package or kill unrelated processes.

## Separate the stages

An executable that cannot load a required library has not started its listener. A connection refusal means the browser did not reach a listening endpoint at that address and port. A loaded page with failed resource requests reached some HTTP handling. A displayed form with the wrong validation message reached the user interface. These observations narrow the investigation but do not by themselves identify every cause.

## Perform a controlled stop

Submit Alice_7 successfully if the lab runs, then stop your server with Ctrl+C. Repeat a browser action and record what changes in the page, Network panel and Console. Restart with the same explicit command, reload in a fresh context and repeat the form workflow. Label expected interruptions separately from unexpected failures.

## Inspect the first relevant evidence

For a loader error, record the missing library and selected runtime paths. For address-in-use, check your earlier process and selected port. For resource failures, compare the requested URL with the configured asset directories. For a wrong result, run the focused event fixture and compare the exact bytes entering the C service. Do not paste credentials or session tokens into public reports.

## Make the record reproducible

Save commands, exit status where observed, server output, browser version and an action timeline. Keep source identity beside the evidence. A successful retry can be useful, but preserve the first failure and state what changed before retrying.

~~~text
Identity: Framework revision, Bits2Banking revision, local edits
Environment: compiler, Wt, OS, browser
Action: launch command and ordered interactions
Observed: exact message, failed request or process status
Next check: the smallest test of the current explanation
~~~

## Exercise and worked answer

The CTest event suite passes but a browser page is blank with a missing script response. Which layer should be checked first? Resource delivery and browser initialization. The event fixture does not fetch scripts. Repair the resource path, repeat browser observation, and keep the event-test result and browser result as separate evidence.

## Read the source

[labs/framework/wt-profile/README.md](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Observe independent browser sessions](12-observe-independent-browser-sessions.md) · [Next: Plan bounded work across a session lifetime](14-plan-bounded-work-and-session-lifetime.md)
