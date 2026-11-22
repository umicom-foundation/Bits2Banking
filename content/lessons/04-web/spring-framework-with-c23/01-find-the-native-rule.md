<!--
Umicom Bits2Banking
File: content/lessons/04-web/spring-framework-with-c23/01-find-the-native-rule.md

PURPOSE:
A fictional training receipt uses an exact number of cents. Its decision is a tiny core that both a native test and a Java host can call.

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

# Put a receipt rule behind one native function

[Course contents](index.md) · [Next · Pass the same units through JNI](02-bridge-the-exact-values-with-jni.md) · [Browser edition](../../../courses/spring-framework-with-c23/lessons/01-find-the-native-rule.html)

A fictional training receipt uses an exact number of cents. Its decision is a tiny core that both a native test and a Java host can call.

## Trace three receipts

A receipt is accepted when it is positive and does not exceed a configured ceiling. A larger amount goes for review. A nonpositive amount or ceiling is invalid. Write the decision for 10000, 20000 and 20001 cents with a 20000-cent ceiling. Expect accept, accept and review, respectively.

```c
if (cents <= 0 || ceiling <= 0) {
    return RECEIPT_INVALID;
}
return cents > ceiling ? RECEIPT_REVIEW : RECEIPT_ACCEPT;
```

Run the same comparison with 10000 cents and a zero ceiling. It returns invalid. The input and exit values are signed and fixed width, so a caller can recognise a result without interpreting print output. The acceptance ceiling includes its exact endpoint.

## Recognise the comparison in Assembly

Using Intel syntax, this x86-64 fragment assumes the prior positivity check passed and EAX holds cents while EDX holds the ceiling. SETG writes one if the signed comparison is strictly greater. The equality case leaves CL at zero. CL is the low byte of RCX, so implement the complete language calling convention before turning this fragment into an Assembly function.

```asm
cmp eax, edx
setg cl
```

## Optional native practice

From the Bits2Banking checkout, open a Windows UCRT64 toolchain session. In PowerShell with the C23 compiler already on your path, compile the supplied files. Expect exit code 0 and the line shown below when you run the resulting training program. If the compiler is missing, use the paper trace first.

```powershell
Set-Location labs/native/service-practice/spring-receipt
gcc -std=c23 -Wall -Wextra -Werror main.c receipt_rule.c -o receipt-rule.exe
.\receipt-rule.exe
```

```text
receipt rules ready
```

- [Read the complete native lab source](../../../labs/native/service-practice/spring-receipt/receipt_rule.h)
- [Read the rule implementation](../../../labs/native/service-practice/spring-receipt/receipt_rule.c)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Learning Spring Framework](../../../courses/learning-spring-framework/index.html)
- [Continue to the Spring Boot native service](../../../courses/spring-boot-native-service/index.html)

[Course contents](index.md) · [Next · Pass the same units through JNI](02-bridge-the-exact-values-with-jni.md) · [Browser edition](../../../courses/spring-framework-with-c23/lessons/01-find-the-native-rule.html)
