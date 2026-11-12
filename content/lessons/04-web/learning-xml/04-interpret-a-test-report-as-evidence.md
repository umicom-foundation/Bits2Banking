<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-xml/04-interpret-a-test-report-as-evidence.md

PURPOSE:
Interpret an XML test report as evidence

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Interpret an XML test report as evidence

XML describes structured text. A document can be well formed while its contents are incomplete, stale or inconsistent. Test reports make that distinction concrete: parsing a report is the beginning of interpretation, not proof that a test run passed.

## Read a small report

This illustrative fragment is teaching data, not an executed result:

~~~xml
<testsuite name="identity" tests="3" failures="1" errors="0" skipped="1">
  <testcase name="preservesIdentity"/>
  <testcase name="rejectsMissingComponent">
    <failure message="Expected an exception"/>
  </testcase>
  <testcase name="rejectsBlankVersion"><skipped/></testcase>
</testsuite>
~~~

The suite has one passing case, one failing case and one skipped case under this example's convention. A skipped case is not a pass. The XML language specifies element and attribute structure, but it does not define a universal JUnit report schema. Use the report producer's contract when interpreting fields. See the [XML specification](https://www.w3.org/TR/xml/) for the syntax rules.

## Connect it to real source

The JVM lab's BuildIdentityTest.java declares three tests. After a successful Maven test run, inspect target/surefire-reports/TEST-org.umicom.learning.BuildIdentityTest.xml. The Gradle route writes its report under build/test-results/test. These paths identify expected outputs, not proof that the files belong to the latest invocation.

1. Check the runner's exit result.

2. Confirm that the file was produced by the current run and intended project.

3. Inspect individual testcase outcomes and compare them with the suite totals.

4. Keep failures, errors and skips separate. Preserve the report when diagnosis continues.

## Exercise conflicting evidence

Change tests="3" to tests="30" in a disposable copy of the fragment. It remains well-formed XML, but the number no longer agrees with the three visible cases. A consumer must define how it handles such inconsistency; it should not manufacture twenty-seven successes.

Now imagine that the report says all cases passed but the runner exits unsuccessfully. Preserve both facts. The failure might occur after test execution, or the report might be stale. Do not discard the process failure merely because the document contains a convenient total.

## Keep data boundaries explicit

Diagnostic text can contain less-than signs, ampersands and quotes. XML escaping represents those characters without turning them into elements or attributes. Use a maintained serializer and a bounded parser contract instead of concatenating untrusted text into markup.

For an importer that only needs local reports, define limits for document size, cases and diagnostic text, and avoid resolving external resources. This lesson does not implement a new XML parser or assert that every producer uses the same conventions. The next useful step is a regression fixture for each report dialect your application actually accepts.

[Course contents](index.md) · [Previous lesson](03-separate-parsing-from-application-validation.md)
