<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/06-keep-the-fixture-permissions-small.md

PURPOSE:
Keep the fixture permissions small

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep the fixture permissions small

A test fixture should have the access it needs for its own experiment. Narrow access makes it easier to verify what the test changed and where it can safely run.

## Read one example permission

A read-only exercise asks for an account summary from a synthetic data set. Its plan permits a database read. A proposed write belongs to a different exercise with its own fixture.

~~~c
const uint32_t fixtureScope = UMI_UAT_DATABASE_READ;
const UmiUatOperation request = UMI_UAT_DATABASE_WRITE;
const bool inScope = (fixtureScope & (uint32_t)request) != 0U;
~~~

Expect `inScope` to be false. The preview stores a permission gate if a row is outside the owner's scope. It can also report that an allowed operation has no adapter support.

## Keep security evidence defensive

A security assertion can check a normal expected refusal. For example, a practice report screen shows a summary only when the synthetic user has its read permission. Compare a fixture with the read permission and one without it. The test records the observable denial and confirms that a previous display value remains usable. Use fictional identities and sample amounts.

1. Write down the intended permissions for the fixture.
2. Observe the ordinary allowed and refused cases.
3. Check that the refused case preserves both the fixture’s data and its visible state.
4. Keep session labels simple. Treat produced log files as evidence for the approved test environment.

For larger automated testing, the Framework target binding identifies a platform, target and session. The trusted adapter still owns its real permissions. Evidence can record that the declared plan was ready and separately record what the target actually did.

[Course contents](index.md) · [Previous lesson · Qualify each platform separately](05-qualify-each-platform-separately.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/06-keep-the-fixture-permissions-small.html) · [Native C23 lab source](../../../labs/native/automated-testing-preview/main.c) · [SDK build description](../../../labs/native/automated-testing-preview/CMakeLists.txt)

[Next lesson · Select one saved test result](07-select-one-saved-test-result.md)
