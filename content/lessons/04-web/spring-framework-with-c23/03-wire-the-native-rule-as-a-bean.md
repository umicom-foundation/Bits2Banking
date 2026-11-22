<!--
Umicom Bits2Banking
File: content/lessons/04-web/spring-framework-with-c23/03-wire-the-native-rule-as-a-bean.md

PURPOSE:
A Spring configuration method creates the rule object so the application receives one checked dependency.

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

# Supply the native rule through a Spring bean

[Course contents](index.md) · [Previous · Pass the same units through JNI](02-bridge-the-exact-values-with-jni.md) · [Browser edition](../../../courses/spring-framework-with-c23/lessons/03-wire-the-native-rule-as-a-bean.html)

A Spring configuration method creates the rule object so the application receives one checked dependency.

## Follow the owner of each part

A bean is an object managed by the Spring container. Put the source excerpt below in TrainingConfig.java in a project with spring-context and the Java class from the preceding lesson. The property points to the lab DLL. The exercise uses a locally built library selected by the operator.

```java
package org.umicom.training;
import java.nio.file.Path;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration(proxyBeanMethods = false)
public class TrainingConfig {
    @Bean
    NativeReceiptRule rule() {
        String path = System.getProperty("training.receipt.library");
        if (path == null || path.isBlank()) {
            throw new IllegalStateException("Supply the absolute training library path");
        }
        return new NativeReceiptRule(Path.of(path));
    }

    public static void main(String[] args) {
        try (var context = new AnnotationConfigApplicationContext(TrainingConfig.class)) {
            NativeReceiptRule rule = context.getBean(NativeReceiptRule.class);
            System.out.println(rule.check(20001, 20000));
        }
    }
}
```

If you use Maven, put that source and NativeReceiptRule.java in src/main/java/org/umicom/training and use the spring-context dependency release compatible with your chosen JDK. After compiling, copy runtime dependencies with mvn dependency:copy-dependencies. On Windows, this classpath includes your configured Maven output and the copied jars. A modern JDK may require its documented native-access option for this classpath app.

```powershell
java "-Dtraining.receipt.library=C:/absolute/lab/receipt_rule.dll" -cp "target/classes;target/dependency/*" org.umicom.training.TrainingConfig
```

Expect 2. The container fails at its dependency boundary when the property is absent or the library cannot be loaded. If the rule prints an unexpected status, run the native receipts exercise first.

## Apply this to Umicom

In an Umicom Workshop, keep a shared validation service responsible for the cents and exception policy and have each environment call it. Give Umicom Bank the same boundary cases in each host before qualifying a user interface. This teaching JNI wrapper is a local example and does not expose a product API.

- [Spring Framework bean declarations](https://docs.spring.io/spring-framework/reference/core/beans/java/bean-annotation.html)
- [Continue with Boot configuration](../../../courses/spring-boot-native-service/index.html)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Learning Spring Framework](../../../courses/learning-spring-framework/index.html)
- [Continue to the Spring Boot native service](../../../courses/spring-boot-native-service/index.html)

[Course contents](index.md) · [Previous · Pass the same units through JNI](02-bridge-the-exact-values-with-jni.md) · [Browser edition](../../../courses/spring-framework-with-c23/lessons/03-wire-the-native-rule-as-a-bean.html)
