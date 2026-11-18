<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/09-pointers-and-allocation-lifetimes.md

PURPOSE:
Follow pointers and allocation lifetimes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Follow pointers and allocation lifetimes

[Course contents](index.md)
A pointer stores an address, not the object itself. Dereferencing follows that address to access storage. A pointer can be null, stale or outside a valid object. Knowing its numeric value does not prove that it is safe to use. The owner of an allocation is responsible for releasing it exactly once under the matching API.

~~~basic
Dim As Long value = 12
Dim As Long Ptr address = @value
Print *address
*address = 19
Print value
Dim As Long Ptr numbers = CPtr(Long Ptr, Callocate(4, SizeOf(Long)))
If numbers = 0 Then
    Print "Allocation failed"
    End 1
End If
numbers[0] = 7
numbers[3] = 9
Print numbers[0] + numbers[3]
Deallocate(numbers)
numbers = 0
~~~

1. Compile pointers.bas with -lang fb -w all -exx and run. Expect 12, 19 and 16.
2. Draw value as a box and address as an arrow to it. Assignment through *address changes the box.
3. Draw the separate four-element allocation. Valid element indexes are 0 through 3.
4. After Deallocate, cross out the allocation and set the pointer to zero. Explain why another copied pointer would still be stale.
5. Do not add a read after Deallocate as a normal test: that is undefined access, not a value you can reliably predict.

@ obtains an address and * dereferences it. Ptr declares a pointer type. CPtr expresses a pointer conversion; it does not validate the address. Callocate requests zero-filled storage, SizeOf reports a representation size, and Deallocate releases storage from the compatible allocation family. These are runtime operations with failure and lifetime contracts.

New and Delete belong to another allocation/construction pattern. Match New with Delete, and array New with its matching array deletion syntax. Do not mix Deallocate with an allocation whose contract requires a different release function. A Framework-owned handle must use the documented Framework release function, not a guessed BASIC deallocator.


## Check

For input-controlled counts, validate a maximum and multiplication overflow before allocating. A fixed four-element example avoids that calculation hazard deliberately. A garbage-collected wrapper or a pointer cast cannot repair an invalid underlying lifetime.


## Continue learning

[Previous: Call a small C service from FreeBASIC](08-a-reviewed-c-boundary.md) · [Course contents](index.md) · [Next: Separate declarations, implementations and namespaces](10-declarations-includes-and-namespaces.md)
