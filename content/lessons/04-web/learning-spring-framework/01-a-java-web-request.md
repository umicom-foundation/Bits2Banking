# A Java web request

[Course contents](index.md) · [Next: Supply a service through a constructor](02-supply-a-service-through-a-constructor.md)

## Begin with the request path

Complete Learning Java before starting. Spring provides application infrastructure. Spring Boot helps configure and start a Spring application. An HTTP controller receives a request and returns a result; it is not the same thing as a desktop button callback, although both connect an event to behaviour.

Use Spring Initializr at `https://start.spring.io`. Select Maven, Java, a stable Spring Boot release and a Java version supported by that release and your installed JDK. Set the package name to `org.umicom.learning`, the artifact to `learning-portal`, and add Spring Web. Generate and extract the project into your chosen practice folder. Keep its generated application class and build file.

Create `src/main/java/org/umicom/learning/LearningController.java`:

```java
package org.umicom.learning;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class LearningController {
    @GetMapping("/learning")
    public String overview() {
        return "Choose a learning course";
    }
}
```

An annotation begins with `@` and supplies metadata. Here it tells Spring that the class handles web requests and which path calls the method. The package must be under the generated application's package so normal component discovery can find it.

Run `./mvnw.cmd spring-boot:run` on Windows PowerShell or `./mvnw spring-boot:run` on Linux. Open `http://localhost:8080/learning`. Expect the sentence, then stop the server with Ctrl+C. If port 8080 is already used, resolve that conflict before interpreting it as a controller defect.

## Exercise and answer

Add another method mapped to `/learning/help` returning `Follow one course in order`. Both paths should work independently. A 404 suggests a path or discovery issue; a build failure happens earlier and needs its compiler diagnostic investigated first.

Compare the existing Java ledger example's calculation with this controller. A web entry point should coordinate a request, not become a second implementation of authoritative banking logic. Later integration can call shared Umicom services through a documented boundary; this lesson creates no such connection yet.

[Review the prerequisite course](../../../courses/learning-java/index.html).


## Source and further reading

[Read the related Umicom example](../../../labs/java-ledger/LedgerDemo.java). Path: `content/labs/java-ledger/LedgerDemo.java`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://spring.io/guides/gs/serving-web-content/). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-spring-framework/lessons/01-a-java-web-request.html).

[Course contents](index.md) · [Next: Supply a service through a constructor](02-supply-a-service-through-a-constructor.md)

Sammy Hegab · Umicom Foundation · Original learning material.
