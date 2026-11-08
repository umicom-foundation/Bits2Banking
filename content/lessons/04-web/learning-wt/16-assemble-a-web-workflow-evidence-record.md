<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/16-assemble-a-web-workflow-evidence-record.md

PURPOSE:
Assemble a web workflow evidence record

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Assemble a web workflow evidence record

## Before starting

Collect the lab source identity and whatever results you actually produced in earlier lessons. If you only read the course, keep every execution field marked not run. The capstone combines evidence from different layers without converting plans into passes.

## Build a useful matrix

Separate the shared C contract, Wt signal wiring, HTTP/resource delivery, independent browser contexts, accessibility and deployment. For each layer, name the check, target environment, outcome and evidence location. An event fixture cannot stand in for a browser or deployment result.

~~~text
Layer | Check | Environment | Actual outcome | Evidence
C policy | boundary contract | native compiler | not run | pending
Wt events | nine CTest cases | selected Wt kit | not run | pending
Browser | click and Enter | selected browser | not run | pending
Sessions | independent contexts | same local host | not run | pending
Deployment | startup and shutdown | selected host | not run | pending
~~~

## Explain one diagnosis

Choose a real observed failure or explicitly label a hypothetical example. Write the symptom, the layer implicated by evidence, a proposed cause, the corrective change and the next check. If a missing resource path was corrected, do not describe the C naming algorithm as repaired. If no cause is established, say so and preserve the unknown.

## Compare with another frontend

Open the Qt profile lab and find the same UmiLocalProfileNameBytes call. Compare a shared acceptance/refusal vector, then list the different event and lifetime checks. For Qt WebAssembly the policy runs in the browser; for this Wt lab it runs in the server application. Shared source does not collapse those target environments into one qualification result.

## Submit a reviewable capstone

Provide the source changes, dependency identities, exact commands, expected results, actual results and remaining checks. Keep private logs and browser session material in your own evidence folder; public learning notes should use sanitized examples. Retain the previous implementation when proposing a replacement so a reviewer can understand the change.

## Exercise and worked answer

Your nine event cases pass, but independent contexts were not checked and no installed package was launched. What can the report claim? It can report those event cases passing for the recorded source and environment. Session isolation and installation remain unverified. The honest matrix gives the next learner a precise starting point.

## Read the source

[labs/framework/wt-profile/test_application.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/test_application.cpp). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Review deployment and shutdown as separate work](15-review-a-deployment-and-shutdown-plan.md)
