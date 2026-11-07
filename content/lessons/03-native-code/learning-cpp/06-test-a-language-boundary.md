<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-cpp/06-test-a-language-boundary.md

PURPOSE:
Explain the lesson: Check a language boundary with explicit cases.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a language boundary with explicit cases

## The same declaration must work for every caller

A boundary test checks the contract seen from the consuming language. The activity model already has C checks. This C++ test adds a different observation: C++ can include the bridge header, link the C implementation and interpret its results correctly.

## Setup recap

Open the [C++ activity lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/cpp-activity-client/README.md). Use matching C/C++ compilers and the Framework SDK. Configure with BUILD_TESTING=ON. If you only want to read the exercise, no compiler is required.

## Read the case table

Each Case stores a current count and the expected returned value. The table includes zero, the last successful increment, a full model, a negative value and the largest and smallest int values.

These cases explain the boundary:

- 0 becomes 1.
- 999 becomes 1000.
- 1000 cannot be incremented by this model.
- Negative values are rejected before conversion to the unsigned model representation.
- Extreme representable values must not wrap into a valid-looking count.

A range-based for loop visits every Case. The loop compares the actual result with the expected result and returns failure when they differ.

## Lab

1. Build the lab.
2. Run `ctest --test-dir build --output-on-failure --no-tests=error`.
3. Identify the case that proves zero is accepted.
4. Identify the case that rejects capacity exhaustion.
5. Compare test_client.cpp with the C adapter test.
6. In a practice copy, omit the C library from the link command. Observe that a header can compile while the final executable fails to link. Restore the original build definition.

Keep deliberate experiments outside the source used for a delivery.

## Why explicit limits matter

An integer's range is finite. `INT_MIN` and `INT_MAX` describe the limits of this implementation's int type. Using those names avoids assuming a decimal width in the C++ source.

The adapter accepts only the activity range even when int can represent much more. Representation and business rules are different checks, and both must hold.

## Exercise and explanation

Does this test prove Android JNI integration works? No. It tests the C++ boundary. JNI adds its own function naming, library loading and platform requirements. Reuse the model tests, then qualify each adapter.

## Record evidence

Save the compiler versions, Framework SDK revision, command and result. A passing test against one SDK does not automatically qualify a different SDK or a mobile build. The source here is authored coverage until those commands are executed.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/cpp-activity-client/test_client.cpp). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-call-a-framework-c-boundary.md)

