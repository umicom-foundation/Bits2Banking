<!--
Umicom Bits2Banking
File: content/lessons/04-web/spring-boot-native-service/01-start-without-a-web-listener.md

PURPOSE:
Boot helps assemble a Spring application. The exercise picks command-line mode explicitly and calls the existing native rule.

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

# Start a Boot application with no web listener

[Course contents](index.md) · [Next · Configure the lab library outside the native rule](02-keep-config-outside-the-rule.md) · [Browser edition](../../../courses/spring-boot-native-service/lessons/01-start-without-a-web-listener.html)

Boot helps assemble a Spring application. The exercise picks command-line mode explicitly and calls the existing native rule.

## Sketch the startup sequence

Boot examines your dependencies for auto-configuration. Spring manages the beans. The ApplicationRunner is the small Java adapter that calls the C23 method after the context starts. No web module is needed.

```text
Configure the context for non-web mode.
Create the native rule bean using an absolute lab path.
Call the rule for a fixed synthetic receipt.
Print its status and close the context.
```

Complete the preceding course through the JNI DLL. Use a Boot Maven project from Spring Initializr with package org.umicom.training and the core Spring Boot starter. Add NativeReceiptRule.java to src/main/java/org/umicom/training. Use BootReceiptApplication.java as the application class.

```java
package org.umicom.training;
import java.nio.file.Path;
import org.springframework.boot.ApplicationRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.WebApplicationType;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.core.env.Environment;

@SpringBootApplication
public class BootReceiptApplication {
    public static void main(String[] args) {
        var app = new SpringApplication(BootReceiptApplication.class);
        app.setWebApplicationType(WebApplicationType.NONE);
        try (var context = app.run(args)) {
            // The runner completed while Boot opened the context.
        }
    }
    @Bean
    NativeReceiptRule receiptRule(Environment environment) {
        return new NativeReceiptRule(Path.of(
            environment.getRequiredProperty("umicom.receipt.library")));
    }
    @Bean
    ApplicationRunner receiptSample(NativeReceiptRule rule) {
        return args -> System.out.println("receipt-status=" + rule.check(20001, 20000));
    }
}
```

Boot may show its normal startup messages. Look for receipt-status=2. If the starter accidentally loads a web implementation, check its dependency tree and the explicit NONE setting before changing the business rule.

- [Spring Boot auto-configuration](https://docs.spring.io/spring-boot/reference/using/auto-configuration.html)
- [SpringApplication startup](https://docs.spring.io/spring-boot/reference/features/spring-application.html)
- [Read the complete native lab source](../../../labs/native/service-practice/spring-receipt/receipt_rule.c)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Spring Framework with a Native C23 Receipt Rule](../../../courses/spring-framework-with-c23/index.html)
- [Continue to MySQL bindings](../../../courses/mysql-c23-ledger/index.html)

[Course contents](index.md) · [Next · Configure the lab library outside the native rule](02-keep-config-outside-the-rule.md) · [Browser edition](../../../courses/spring-boot-native-service/lessons/01-start-without-a-web-listener.html)
