<!--
Umicom Bits2Banking
File: content/start/applied-native-courses.md

PURPOSE:
Guide learners from native calculations to web frameworks, data services and fictional financial applications.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Build native practice projects for web and finance

Start with fictional records and check the C calculation on paper. Then learn how to display the result, save it, or move it between systems. A language used by a framework can read the native result and pass it on. An adapter is the small part that connects the two environments.

Go to [the beginner learning pathways](connected-learning.md) if files, commands or whole-cents amounts are new to you. You can read the courses without registering for a service or connecting a real account.

## Build a screen and a server adapter

| Course | What you will practise |
| --- | --- |
| [React](../courses/react-native-statements/index.html) | Display a native statement result as components and verify which rows are visible. |
| [Node.js](../courses/nodejs-native-reporting/index.html) | Read a native report at the runtime boundary and handle an unavailable or invalid result. |
| [AngularJS 1.x](../courses/angularjs-legacy-statements/index.html) | Read a legacy controller and record what a migration must preserve. AngularJS is the predecessor of current Angular and its official support has ended. |
| [Bootstrap](../courses/bootstrap-native-statements/index.html) | Apply a responsive layout to native-generated statement data and check accessible headings. |

## Connect services and data stores

| Course | What you will practise |
| --- | --- |
| [Spring Framework](../courses/spring-framework-with-c23/index.html) | Use dependency injection to supply a small adapter for a native rule. |
| [Spring Boot](../courses/spring-boot-native-service/index.html) | Keep service configuration and response mapping around the C calculation. |
| [MySQL](../courses/mysql-c23-ledger/index.html) | Validate whole-cents fields in native code and trace the two sides of a transaction. |
| [Oracle Database](../courses/oracle-database-c23-ledger/index.html) | Plan a native service boundary and preserve exact fixed-scale values. |
| [MongoDB](../courses/mongodb-c23-documents/index.html) | Match checked native data to an explicit document shape. |
| [RabbitMQ](../courses/rabbitmq-c23-outbox/index.html) | Track an accepted message identity, a broker acknowledgement and a safely repeated delivery. |

## Follow a financial workflow

| Course | What you will practise |
| --- | --- |
| [Banking Technology Foundations](../courses/banking-technology-foundations/index.html) | Read ledgers and holds, follow a payment and reconcile results. |
| [Build a Banking Application in C](../courses/build-a-bank-application-in-c/index.html) | Post one transfer, preserve a journal and handle repeats before designing a database adapter. |
| [Open Banking](../courses/open-banking-account-access/index.html) | Trace consent and a permitted account read with synthetic identifiers. |
| [Swift payment messages](../courses/swift-payment-messages/index.html) | Follow a payment message reference and identify the result that still needs reconciliation. |
| [FpML for treasury](../courses/fpml-for-treasury/index.html) | Map selected trade terms into a checked native record and retain their units. |
| [Build a Trading Application in C](../courses/build-a-trading-application-in-c/index.html) | Admit a fictional limit order, choose one eligible offer and verify the cash and position result. |

## Express the same native calculation four ways

Suppose a synthetic account has 3,600 posted cents and holds 900 cents. Subtract the held amount from the posted amount. Paper gives 2,700 cents. Keep the same inputs and units when comparing the language examples.

~~~text
SET posted cents TO 3600
SET held cents TO 900
SHOW posted cents minus held cents
~~~

~~~c
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    const int64_t posted = 3600, held = 900;
    printf("%" PRId64 "\n", posted - held);
    return 0;
}
~~~

~~~d
import std.stdio : writeln;

void main()
{
    const long posted = 3600, held = 900;
    writeln(posted - held);
}
~~~

~~~freebasic
Dim As LongInt posted = 3600
Dim As LongInt held = 900
Print LTrim(Str(posted - held))
~~~

~~~asm
; x86-64 Intel syntax. At the end, RAX holds 2700.
; A host program can read that value according to its calling convention.
mov rax, 3600
sub rax, 900
~~~

Start by tracing the lines. If the hold changes to 500, the expected output is 3,100. These examples use literal non-negative values in range. A real application needs a checked input contract and tests for missing, out-of-range and mismatched-currency data.

Follow [Programming across languages](../courses/programming-across-languages/index.html) for a full comparison of loops and decisions, or [Umicom C checked integer keywords and syntax](../courses/umicom-c-keyword-reference/index.html) to perform the same subtraction with the Umicom C practice compiler.
