<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/55-keep-regression-observations-type-correct.md

PURPOSE:
Keep regression observations type correct

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Keep regression observations type correct

## Preparation and outcome

Open fixture_test.c in the C library composition lab and read its signed-zero case. Also locate the Framework financial rate admission and environment admission tests. You will learn how a warning can originate in test scaffolding or a platform macro, while preserving the behavior the regression intends to check.

## Equality does not distinguish zero signs

For the host floating-point implementation used by this lab, negative zero compares equal to positive zero. A test that only checks amount == 0.0 cannot establish that an identity conversion preserved the sign. The double-precision copysign function copies a sign onto a nonzero magnitude:

~~~c
const double negative = -0.0;
const double positive = +0.0;
/* Both compare equal, but their signs produce different observations. */
int same_value = negative == positive;
double negative_marker = copysign(1.0, negative);
double positive_marker = copysign(1.0, positive);
~~~

Expected observations are a true same_value, negative_marker equal to -1.0 and positive_marker equal to +1.0. The maintained test checks all three. It does not divide by zero to infer a sign and does not inspect a guessed floating-point bit layout.

## Preserve the claim while changing its expression

A Windows math header can implement signbit with type-selection macros whose unselected expressions still expose conversions to compiler diagnostics. The Framework fixture observed a double-to-float warning at this macro call. Replacing the test with a cast to float would weaken the observation's precision contract.

The revised fixture keeps the conversion call, checks that the result is zero, and uses double copysign to inspect its sign. It additionally checks positive zero. The former expression remains disabled for engineering review. This repairs the test expression; it does not establish that the production financial service has passed its runtime regressions.

Run the independent representation check:

~~~powershell
ctest --test-dir build/c-library-composition -R signed-zero --output-on-failure --no-tests=error
~~~

Expect one pass on a conforming host with the required signed-zero behavior. If the result differs, record the compiler, target and floating-point options before deciding whether the test contract or environment needs adjustment. Options that discard signed-zero distinctions are incompatible with this exercise's purpose.

## Inclusion changes a test's scope

Some environment tests include a production .c file after substituting allocation or filesystem boundaries. That makes the test globals and included production definitions part of one translation unit. A test global called written can be shadowed by otherwise reasonable local formatting counters with the same name inside the included file.

Give capture state a descriptive fixture-specific name, such as captured_environment_text. Keep production counters local to their functions. This avoids changing reusable production logic solely to satisfy a collision created by the fixture. It also makes the test's observable state easier to identify.

## Exercise and verification record

Write down four separate claims: compilation succeeded, warnings were absent under the recorded flags, the expected number of tests ran, and each relevant assertion passed. These are different observations. A configure pass establishes none of the last three.

For the environment fixture, find the substitutions immediately before the production include and the matching undef directives afterward. Explain which effects are observed and which are never performed. For the signed-zero fixture, deliberately reverse the expected sign in a scratch copy, verify that the regression fails, then restore it. A useful test should detect the specific wrong behavior it was written to prevent.

When diagnosing a real build, save the original warning and the source identity before editing. After a fix, record a fresh build result rather than relabeling the earlier warning as a pass.

[Course contents](index.md) · [Previous lesson](54-check-the-bytes-of-a-c-test-fixture.md) · [Next lesson](56-read-hexadecimal-and-binary-source.md)
