<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/19-use-a-real-void-pointer-output.md

PURPOSE:
Explain the lesson: Receive an allocation through the correct pointer type.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Receive an allocation through the correct pointer type

## Prepare
Open main.c in the arena laboratory. It retains an older pointer-to-pointer cast inside a disabled block, followed by the replacement using titleStorage and bodyStorage.

void * can represent a pointer to an object. void ** points to an actual void * variable. These types describe different levels of access.

## Trace the replacement
The allocation function writes a void * value into titleStorage. After success, main assigns titleStorage to the char * named title.

The conversion happens to the pointer value. The allocator does not write through a void ** cast that refers to a char * variable.

## Lab
Draw two columns: variable type and function parameter type. Add titleStorage as void *, its address as void **, title as char * and its address as char **.

Expected: only the address of titleStorage directly matches the allocator's output parameter.

## Exercise and explanation
Why is casting &title insufficient? A cast changes the expression's type; it does not change the declared type of the underlying pointer object. Access through the resulting incompatible pointer-to-pointer lvalue can violate C's rules.

## Troubleshoot
Treat pointer-to-pointer warnings as design clues. Use an intermediate variable of the API's required type, check success, and then convert the returned pointer value.

The preserved block explains the historical mistake. It is not an alternative exercise to enable. Apply the corrected pattern when studying other allocation interfaces with void ** outputs.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/arena-allocator/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](18-preserve-output-on-allocation-failure.md) · [Next lesson](20-rewind-a-temporary-allocation-scope.md)

