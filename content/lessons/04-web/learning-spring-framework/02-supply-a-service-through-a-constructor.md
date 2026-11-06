# Supply a service through a constructor

[Course contents](index.md) · [Previous: A Java web request](01-a-java-web-request.md)

## Put a dependency where it can be seen

A dependency is something a component needs to do its work. Constructor injection means supplying that dependency when the object is created. It makes the relationship explicit and allows a test to supply a controlled implementation later.

In the same package, create `CourseAdvice.java`:

```java
package org.umicom.learning;

import org.springframework.stereotype.Service;

@Service
public class CourseAdvice {
    public String firstStep() {
        return "Read, predict, practise, compare";
    }
}
```

Create a second controller file, `AdviceController.java`, preserving the previous controller:

```java
package org.umicom.learning;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class AdviceController {
    private final CourseAdvice advice;

    public AdviceController(CourseAdvice advice) {
        this.advice = advice;
    }

    @GetMapping("/learning/advice")
    public String show() {
        return advice.firstStep();
    }
}
```

Spring discovers the service and supplies it to the single constructor. `final` means this field is assigned once; it does not imply that every possible object stored there is immutable. The controller calls a method instead of constructing a new service inside every request.

## Observe and investigate

Restart the application using the previous lesson's command and open `/learning/advice`. Expect the four-part sentence. If startup reports a missing dependency, check the package and service annotation. If it reports ambiguous routes, check that each method has its intended unique mapping.

## Exercise and answer

Change the sentence only in CourseAdvice and restart. The response should change without editing the controller's request mapping. This demonstrates separation of responsibilities; it is not yet a proof of testability or production correctness.

Compare with the Umicom activity example: its window depends on a shared rule. The underlying principle is to supply or call the shared behaviour rather than recreate it in each interface. A future native adapter needs explicit error, lifetime and transport contracts. Dependency injection alone does not provide those contracts or make Java objects directly callable from C.

[Review the prerequisite course](../../../courses/learning-java/index.html).


## Source and further reading

[Read the related Umicom example](../../../labs/java-ledger/LedgerDemo.java). Path: `content/labs/java-ledger/LedgerDemo.java`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://spring.io/guides/gs/serving-web-content/). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-spring-framework/lessons/02-supply-a-service-through-a-constructor.html).

[Course contents](index.md) · [Previous: A Java web request](01-a-java-web-request.md)

Sammy Hegab · Umicom Foundation · Original learning material.
