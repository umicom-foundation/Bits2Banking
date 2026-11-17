<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-language-interoperability/02-follow-the-c-contract.md

PURPOSE:
Teach follow the c contract and its failure path.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Follow the C contract and its failure path

[Course contents](index.md) · [Previous](01-prepare-a-shared-boundary.md) · [Next](03-call-c-from-cpp.md)

## Read the public declaration
~~~c
int BtbActivityNext(int current);
~~~
The first int is the return type. current is the name of the input parameter. The semicolon ends a declaration: this header describes the function but does not contain its implementation. The C bridge calls BtbActivityAdvance, which already owns the counting rule.

## Follow a valid call
1. Open bridge.c and activity.c side by side.
2. Find the negative-input check. It runs before conversion to unsigned. Converting -1 first would produce a large unsigned value, hiding the original meaning.
3. Follow current = 41 into BtbActivityAdvance. The model checks the output pointer and upper bound before addition.
4. Observe the local next variable. The bridge owns its storage; the C model writes it only on success and retains no pointer.
5. Follow current = 1000. The model returns a capacity status; the bridge returns -1. A caller must not treat -1 as a new count.

## Run the existing tests
After lesson 1, run ctest --test-dir build/activity-adapters --output-on-failure --no-tests=error. Read test_bridge.c before changing anything. It checks values near both accepted and rejected boundaries.

## A deliberately small ABI
This interface uses a C int on both sides, not a language-default integer guessed to be equivalent. A future interface with text must specify encoding, length, allocation ownership and lifetime. A future interface with structures must specify layout and versioning. C linkage alone does not answer these questions.

The bridge is a teaching adapter owned by Bits2Banking. It uses Framework status values but is not advertised as a new Framework SDK API. Real reusable application services should expose their own documented Framework contracts.

## Exercise and worked answer
Would returning current + 1 in every language make the system easier to maintain? It would duplicate the rule and allow different limits or errors to drift apart. Keep the rule in C and translate only the interface. What should happen for -1? Rejection before the signed-to-unsigned conversion. Explain both answers before editing the next client.

## Read the complete source

[labs/native/activity-adapters/bridge.c](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/activity-adapters/bridge.c)
