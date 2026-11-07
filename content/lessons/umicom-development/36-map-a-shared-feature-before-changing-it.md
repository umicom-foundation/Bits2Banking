# Map a shared feature before changing it

[Course contents](index.md) · [Previous: Read calendar data without inventing values](35-read-calendar-data-without-inventing-values.md)

## A small map makes a large project understandable

Complete the first-application and build-and-diagnose modules in this course. A contract states what an operation accepts, returns and changes. An implementation performs it. A consumer calls it. A test compares actual behaviour with the contract. These roles can live in different files without being different features.

Use the activity example as a complete small map:

```text
activity.h       declaration and promises
activity.c       rule implementation
console.c        text interface
window.c         GTK4 interface
test_activity.c  checks of the rule
CMakeLists.txt   build relationships
```

## Follow one request

Start at `BtbActivityAdvance` in the header. Write down the maximum count and what must happen to the output on failure. Find the definition in `activity.c`. Then find its callers in the console and window sources. Both callers should interpret the same status rather than independently decide the maximum.

The example uses Framework's status vocabulary, but its practice activity rule belongs to the lesson project. It is a teaching model of shared ownership, not a claim that every example function is a Framework public API. In an application feature, reusable production behaviour belongs in Framework and application-specific presentation remains in the client.

## Plan a change before editing

Suppose the practice limit becomes 500. List the affected promise, implementation, boundary checks and user-facing explanation. Do not begin by replacing every number 1000 in the repository: unrelated numbers may mean something else. A focused search for the function and its callers gives evidence of the change's scope.

In a personal practice copy, change the agreed limit consistently. Configure and build using the example README, then run its checks. These are distinct steps: configure discovers dependencies and creates build rules; build compiles and links; tests execute behaviour. A successful configure is not a test pass.

## Exercise and answer

Which checks distinguish a correct 500 limit from a display-only change? Test 499 becoming 500, 500 being rejected without changing the output, and a null output being rejected. Then verify the window reports failure appropriately. If the console and window disagree, trace their calls rather than duplicating fixes in both interfaces.

Keep a short engineering explanation of the change and a regression check. That gives the next contributor a reason and a way to verify it, instead of a mysterious new constant.

[Review the prerequisite course](../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/activity.h). Path: `labs/native/framework-activity/activity.h`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://cmake.org/cmake/help/latest/guide/tutorial/index.html). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../courses/umicom-development/lessons/36-map-a-shared-feature-before-changing-it.html).

[Course contents](index.md) · [Previous: Read calendar data without inventing values](35-read-calendar-data-without-inventing-values.md)

Sammy Hegab · Umicom Foundation · Original learning material.

[Next: Use a Framework function in a practical lab](37-use-a-framework-function-in-a-lab.md)
