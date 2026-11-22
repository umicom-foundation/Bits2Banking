<!--
Umicom Bits2Banking
File: content/lessons/04-web/spring-boot-native-service/02-keep-config-outside-the-rule.md

PURPOSE:
Move the absolute DLL name out of the app source and diagnose missing or invalid configuration.

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

# Configure the lab library outside the native rule

[Course contents](index.md) · [Previous · Start a Boot application with no web listener](01-start-without-a-web-listener.md) · [Next · Replay the same native case from a Boot test](03-replay-the-native-decision.md) · [Browser edition](../../../courses/spring-boot-native-service/lessons/02-keep-config-outside-the-rule.html)

Move the absolute DLL name out of the app source and diagnose missing or invalid configuration.

## Try three configurations on paper

- With a real absolute lab DLL, bean construction loads the library and the native test can produce a receipt status.
- Omit umicom.receipt.library. The required-property lookup reports missing configuration before processing a receipt.
- Supply a relative filename. NativeReceiptRule rejects it so the chosen library does not depend on the current working directory.

Add one development value to src/main/resources/application.properties, or override it for one local launch. If you use the Boot wrapper on Windows, the commands below package the app and show how you would supply a per-run value. Replace the jar name with the built artifact under target.

```properties
umicom.receipt.library=C:/absolute/lab/receipt_rule.dll
```

```powershell
.\mvnw.cmd package
java -jar target/receipt-training.jar "--umicom.receipt.library=C:/absolute/lab/receipt_rule.dll"
```

Use the JVM native-access option documented for your chosen JDK if its diagnostic requires an opt-in. A fresh build still needs the generated JNI header and native library. If the app fails early, find the first missing property or link error and keep its message separate from the rule outcome.

- [Spring Boot externalised configuration](https://docs.spring.io/spring-boot/reference/features/external-config.html)
- [Java JNI design](https://docs.oracle.com/en/java/javase/25/docs/specs/jni/design.html)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Spring Framework with a Native C23 Receipt Rule](../../../courses/spring-framework-with-c23/index.html)
- [Continue to MySQL bindings](../../../courses/mysql-c23-ledger/index.html)

[Course contents](index.md) · [Previous · Start a Boot application with no web listener](01-start-without-a-web-listener.md) · [Next · Replay the same native case from a Boot test](03-replay-the-native-decision.md) · [Browser edition](../../../courses/spring-boot-native-service/lessons/02-keep-config-outside-the-rule.html)
