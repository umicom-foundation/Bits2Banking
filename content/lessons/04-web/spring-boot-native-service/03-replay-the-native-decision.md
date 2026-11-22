<!--
Umicom Bits2Banking
File: content/lessons/04-web/spring-boot-native-service/03-replay-the-native-decision.md

PURPOSE:
Use the receipt boundary cases to distinguish a host startup problem from a calculation change.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Replay the same native case from a Boot test

[Course contents](index.md) · [Previous · Configure the lab library outside the native rule](02-keep-config-outside-the-rule.md) · [Browser edition](../../../courses/spring-boot-native-service/lessons/03-replay-the-native-decision.html)

Use the receipt boundary cases to distinguish a host startup problem from a calculation change.

## Keep a small shared evidence table

- Native fixture: run the dependency-free C test for 20000, 20001 and invalid inputs.
- Adapter fixture: compare exact returned status codes for the same inputs through NativeReceiptRule.
- Host fixture: retain a configuration failure case with the missing property and one successful startup case with receipt-status=2.

D exposes C linkage with extern(C), and long differs between D and C on some platforms. Use int for a signed 32-bit lesson argument. The matching C header is the reference for constants and any compiler-specific boundary. This D expression can independently check the expected truth value before learning JNI.

```d
bool aboveCeiling(int cents, int ceiling) {
    return cents > 0 && ceiling > 0 && cents > ceiling;
}
```

aboveCeiling(20001, 20000) is true. For exactly 20000 it is false. The boolean is only the review predicate. The full native function still keeps invalid and accepted results distinct.

## Apply this to Umicom

An Umicom Automated Testing lesson can store host setup cases separately from rule cases. When a runner cannot find the library, use a setup failure and preserve the unexecuted rule probe.

- [Read the complete native lab source](../../../labs/native/service-practice/spring-receipt/main.c)
- [Compare the relational boundary](../../../courses/mysql-c23-ledger/index.html)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Spring Framework with a Native C23 Receipt Rule](../../../courses/spring-framework-with-c23/index.html)
- [Continue to MySQL bindings](../../../courses/mysql-c23-ledger/index.html)

[Course contents](index.md) · [Previous · Configure the lab library outside the native rule](02-keep-config-outside-the-rule.md) · [Browser edition](../../../courses/spring-boot-native-service/lessons/03-replay-the-native-decision.html)
