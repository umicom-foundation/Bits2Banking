<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-xml/03-separate-parsing-from-application-validation.md

PURPOSE:
Separate parsing from application validation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate parsing from application validation

## Before you begin
Use only the small synthetic documents from this course. Keep a list of the fields your reader would accept: one measurement value, an explicit unit and an optional note. Define byte and item limits before planning a native import service.

## Design an admission sequence
First limit the input size and parse under an explicit policy. Then check the expected root and namespace. Next reject unknown or repeated required fields, parse integer text with overflow checks and admit the unit. Only after the complete record is accepted should a service publish a new value to its caller.

~~~xml
<measurement unit="g">
  <value>80000</value>
  <value>81000</value>
</measurement>
~~~

This tree is structurally ordinary XML. An application expecting exactly one value must decide how to reject the duplicate instead of silently using whichever value a helper returns first. A document that parses is not automatically a valid measurement.

## Keep external access explicit
A general XML parser may support document types and external entities. An untrusted import should not gain network or filesystem authority merely from text inside the document. The future native Framework adapter needs a reviewed parser policy, bounded memory and regression fixtures before it can be used for user records. This introductory course does not supply that adapter.

## Exercise
Write an expected-result table for missing value, duplicate value, unsupported unit, integer overflow, unexpected namespace and oversized input. For every refusal, require the prior accepted record to remain unchanged. Add a successful synthetic case to show that the refusal policy still allows the intended document.

## Connect to the build-tool courses
Maven validate checks a Maven project model and can involve build configuration. Do not execute an unknown downloaded POM merely to ask whether arbitrary XML is well formed. Use a parser designed for the input's trust boundary. For the supplied trusted lab, compare a POM syntax error with a later Java test failure and explain why they occur at different stages.

[W3C XML specification](https://www.w3.org/TR/xml/) · [Maven POM model](https://maven.apache.org/guides/introduction/introduction-to-the-pom.html)

[Course contents](index.md) · [Previous lesson](02-understand-namespace-identity.md) · [Next lesson](04-interpret-a-test-report-as-evidence.md)
