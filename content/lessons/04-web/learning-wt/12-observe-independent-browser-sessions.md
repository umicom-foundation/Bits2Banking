<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/12-observe-independent-browser-sessions.md

PURPOSE:
Observe independent browser sessions

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Observe independent browser sessions

## Before starting

Start the lab on loopback with the public-assets command. Open the source and identify the application-owned widget tree. Use two browser contexts with separate storage, such as a normal window and an isolated private context; describe the actual browser setup in your notes.

## Write the expected state before acting

Context A starts with an empty input. Context B should also start empty. Enter Alice_7 in A and Bob in B. The expected results are alice_7 and bob respectively. Change A to invalid input and expect only A to show refusal. Keep the two pages visible while you perform each action.

## Record the sequence

Use a small observation table rather than a single final screenshot. The order matters because a global result variable could appear correct after one submission but overwrite another session later.

~~~text
Step | Context A action/result | Context B action/result
1    | open / initial          | not opened
2    | unchanged               | open / initial
3    | submit Alice_7          | unchanged
4    | unchanged               | submit Bob
5    | submit ../../other      | unchanged
~~~

## Trace an interference defect

If one context changes another, inspect shared static variables, reused widget pointers and any new service cache. The current factory captures pointers belonging to one application instance. A reusable C naming rule has no session-specific result store. Keep a failing sequence before changing ownership; an isolated successful retry does not explain the earlier interaction.

## Understand the limit

This small experiment observes two contexts at a particular moment. It does not establish a maximum session count, resistance to resource exhaustion or safety of future asynchronous code. The sequential fresh-session CTest scenario is useful but observes a different lifetime boundary.

## Exercise and worked answer

Two ordinary tabs show related state. Can you immediately conclude that Framework shares results globally? No. First establish whether the browser contexts and Wt sessions are actually independent, then trace ownership in the server. Record the setup and repeat with isolated storage before changing the pure C policy.

## Read the source

[labs/framework/wt-profile/profile_application.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/profile_application.cpp). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Separate public assets from application source](11-separate-public-assets-from-source.md) · [Next: Diagnose transport, resource and event failures](13-diagnose-http-and-event-failures.md)
