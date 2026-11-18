<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/08-a-reviewed-c-boundary.md

PURPOSE:
Call a small C service from FreeBASIC

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Call a small C service from FreeBASIC

[Course contents](index.md)
An application binary interface, or ABI, is the machine-level agreement between compiled modules. It includes how parameters and results are passed, symbol names, sizes and alignment. It is different from syntax. FreeBASIC does not gain the entire Framework API merely by including a C header as text.

The repository’s labs/languages/native-language-boundary example exposes one C function: bounded_progress. It accepts two signed 32-bit counts and a pointer to a 32-bit result. Success is 0; invalid input is 1. On failure the output is unchanged. The caller owns the output; the service allocates no memory. The complete C source and BASIC/D clients are provided together.

~~~basic
Extern "C"
    Declare Function bounded_progress Cdecl Alias "bounded_progress" _
        (ByVal completed As Long, ByVal total As Long, _
         ByVal percent As Long Ptr) As Long
End Extern
Dim As Long percent = -1
Dim As Long status = bounded_progress(2, 8, @percent)
If status <> 0 Then
    Print "Invalid progress"
    End 1
End If
Print percent
~~~

1. Read boundary.h and boundary.c in the companion lab. Verify that int32_t is used for every exported number.
2. Choose compiler toolchains targeting the same architecture and compatible object format. The lab’s FreeBASIC example describes the GNU object workflow; a Microsoft COFF/CRT mismatch needs a separate build configuration.
3. Compile the C source to an object, then pass that object and the BASIC client to fbc. Follow the lab README commands.
4. Run the client and expect 25. Run its negative check and confirm that an invalid total leaves the previous result unchanged.

Extern "C" chooses C linkage; Cdecl states the calling convention. The details on 32-bit x86 differ from the platform ABI on 64-bit systems, so never copy a stack diagram as a universal rule. Alias fixes the exported symbol spelling. Long supplies the intended 32-bit BASIC value. Ptr declares a pointer, and @ obtains the address of the caller’s variable.

For real Framework use, build a small binding around documented public headers and installed libraries. Keep strings as explicit encoded bytes and lengths, provide matching release functions for owned handles, and never free an allocation with an unrelated language allocator. Start with a narrow console consumer before integrating Studio or Media UI.


## Boundary limits

The lab demonstrates ABI design; it does not certify every FreeBASIC compiler/Framework SDK combination. The C side has a standalone regression target. The BASIC client must be compiled and tested with a recorded FreeBASIC version before release. No model is downloaded, app launched or network request made by this example.


## Further reading

- [FreeBASIC CDECL](https://www.freebasic.net/wiki/KeyPgCdecl)
- [FreeBASIC manual](https://www.freebasic.net/wiki/DocToc)

## Continue learning

[Previous: Records, reusable modules and files](07-records-modules-and-files.md) · [Course contents](index.md)

[Continue to Follow pointers and allocation lifetimes](09-pointers-and-allocation-lifetimes.md)
