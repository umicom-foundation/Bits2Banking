<!--
Umicom Bits2Banking
File: content/lessons/04-web/spring-framework-with-c23/02-bridge-the-exact-values-with-jni.md

PURPOSE:
Java Native Interface gives the Java host a typed way to call the rule without porting its calculation.

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

# Pass the same units through JNI

[Course contents](index.md) · [Previous · Put a receipt rule behind one native function](01-find-the-native-rule.md) · [Next · Supply the native rule through a Spring bean](03-wire-the-native-rule-as-a-bean.md) · [Browser edition](../../../courses/spring-framework-with-c23/lessons/02-bridge-the-exact-values-with-jni.html)

Java Native Interface gives the Java host a typed way to call the rule without porting its calculation.

## Follow the call once

Java calls NativeReceiptRule.check with two int values. The native declaration names decide. The JDK creates a C header for that method, and the C bridge delegates to receipt_decision. The Java and JNI values are signed 32-bit integers. The shared native file owns the limit logic.

```text
Java check(20001, 20000)
  -> JNI decide(20001, 20000)
  -> C receipt_decision(20001, 20000)
  -> 2 (review)
```

Generate the JNI header before compiling its bridge. These commands assume PowerShell at the spring-receipt lab and JAVA_HOME pointing to the chosen JDK. Keep the DLL compiler architecture the same as the JVM.

```powershell
New-Item -ItemType Directory -Force classes, generated | Out-Null
javac -d classes -h generated src/org/umicom/training/NativeReceiptRule.java
gcc -std=c23 -shared -Igenerated "-I$env:JAVA_HOME/include" "-I$env:JAVA_HOME/include/win32" receipt_rule.c native_receipt_jni.c -o receipt_rule.dll
```

- Find the header name referenced by native_receipt_jni.c inside generated.
- Leave an absolute DLL path for the host. If it reports an UnsatisfiedLinkError, inspect architecture, the generated function name and dependent runtime libraries.
- When a JDK reports restricted native access, use its documented opt-in for the trusted classpath application you built. Keep the library in the local lab.

- [Java Native Interface design](https://docs.oracle.com/en/java/javase/25/docs/specs/jni/design.html)
- [Read the JNI bridge](../../../labs/native/service-practice/spring-receipt/native_receipt_jni.c)
- [Read the Java interface](../../../labs/native/service-practice/spring-receipt/src/org/umicom/training/NativeReceiptRule.java)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Learning Spring Framework](../../../courses/learning-spring-framework/index.html)
- [Continue to the Spring Boot native service](../../../courses/spring-boot-native-service/index.html)

[Course contents](index.md) · [Previous · Put a receipt rule behind one native function](01-find-the-native-rule.md) · [Next · Supply the native rule through a Spring bean](03-wire-the-native-rule-as-a-bean.md) · [Browser edition](../../../courses/spring-framework-with-c23/lessons/02-bridge-the-exact-values-with-jni.html)
