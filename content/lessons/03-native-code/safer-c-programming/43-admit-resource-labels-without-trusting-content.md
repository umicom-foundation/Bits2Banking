<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/43-admit-resource-labels-without-trusting-content.md

PURPOSE:
Admit resource labels without trusting their contents

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Admit resource labels without trusting their contents

[Course contents](index.md)

## Start with a label and a box

Imagine a box labelled photographs. The label describes what someone expects inside; it does not prove what is actually inside. A software resource also has a label describing its format. An image might be labelled image/png, a text document text/plain, and structured data application/json. This lesson uses a small C program to admit these labels into an Umicom Framework catalogue. It opens no image, document or network connection. You will learn why validating a label and validating content are separate jobs.


## Define the unfamiliar words

Metadata is information describing something else. A resource is something a program can discover or use, such as a document, panel definition or theme. A descriptor is a C structure containing that metadata. A registry stores descriptors so other parts of the application can look them up by stable names. Reflection lets a program inspect descriptions of types or resources. C does not discover every application type automatically; Framework uses explicit declarations. The earlier D lessons show a different mechanism in which the compiler inspects declarations at compile time.


| Word | In this exercise |
| --- | --- |
| Resource identifier | learning.preview, the stable lookup name |
| Module identifier | learning.media, the contributing module name |
| Resource URI | memory://learning/preview, a descriptive address that this exercise does not open |
| Media type | image/svg+xml, a description of expected representation |
| Display name | Example preview metadata, text intended for a person |


## Read type and subtype separately

A concrete media type normally contains a top-level type, a slash and a subtype. In image/png, image is the top-level type and png is the subtype. In application/json, application identifies the broad category and json names the representation. A plus suffix can describe a structured syntax: image/svg+xml uses XML syntax. The spelling alone does not install a decoder or validate a document. Framework also preserves older catalogue labels such as umicom.layout. Those are internal identifiers, not automatically registered Internet media types.


## Know which input contract you are using

This descriptor accepts a concrete type/subtype label without parameters or wildcard ranges. A complete HTTP Content-Type value can have parameters, for example text/plain; charset=UTF-8. That is useful in its own protocol, but it is not the input shape accepted by this resource descriptor. Similarly image/* is a range used for matching, not one concrete format. Do not remove pieces of an unfamiliar header blindly and assume the remaining text explains the encoding. A real HTTP parser needs its own contract and must retain parameters that affect interpretation.


| Input | Descriptor result | Reason |
| --- | --- | --- |
| application/json | Accepted | Concrete type and subtype |
| image/svg+xml | Accepted | Concrete name with a structured syntax suffix |
| umicom.layout | Accepted | Retained legacy identifier |
| image/* | Refused | Wildcard range |
| text/plain; charset=UTF-8 | Refused | Parameterized header value |
| image/png/extra | Refused | More than one separator |
| image/ | Refused | Missing subtype |


## Count bytes before copying

The public descriptor stores media_type in a fixed array of 128 char elements. A C string ends with a zero byte, so at most 127 nonzero bytes fit. This is the current Framework capacity, not a statement that every valid Internet media name must fit. The example calls strlen only on valid string literals, checks length against sizeof the destination, then copies length plus one bytes. The extra byte is the terminator. Calling strlen on an arbitrary pointer without a guaranteed terminator would be unsafe; use a counted-input boundary before this step when data comes from a file or network.

~~~c
size_t length = strlen(labels[i]);
if (length >= sizeof resource.media_type) return 1;
memcpy(resource.media_type, labels[i], length + 1U);
~~~


## Separate display text from portable names

People can have names and descriptions in many languages. This specific type/subtype naming policy uses ASCII letters, digits and a restricted punctuation set. The first character of each component must be a letter or digit. Spaces, control bytes and non-ASCII bytes are refused in this slash form. This makes the syntax independent of the current text locale. It does not provide a Unicode display-name validator, filename policy or permission rule. Keep each field’s purpose explicit instead of reusing one convenient string validator everywhere.


## Prepare the exercise

1. Finish the earlier C setup and reflection ownership lesson. You need a C23 compiler, CMake and Ninja. CMake prepares build rules; Ninja executes them; the compiler translates C source.
2. Open the Bits2Banking repository and locate labs/framework/reflection-snapshot/media_labels.c. Keep the complete Framework header and implementation versions together.
3. Choose an installed SDK or the explicit source exercise below. The source exercise compiles selected Framework files and is useful for learning, but it does not qualify a separately installed package.
4. Run each command separately. Stop if configuration or compilation fails; an old executable may still exist in the build directory.


## Build the source exercise

For installed SDK use, omit UMICOM_FRAMEWORK_SOURCE and use a separate build directory with -DCMAKE_PREFIX_PATH pointing to your actual SDK. The lab requests the reflection component and links Umicom::reflection. Use matching architecture and toolchain versions. Missing component errors are not repaired by copying implementation code into the application; identify which SDK was selected.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/framework/reflection-snapshot -B build/reflection-source -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/reflection-source --parallel 2
ctest --test-dir build/reflection-source -R "lesson.reflection.resource-labels" --output-on-failure --no-tests=error
~~~


## Follow the program in order

1. Initialize a resource descriptor with zeros, then set its structure size, stable identifiers, display text, URI and resource kind. Zero initialization prevents accidental uninitialized fields; it does not make every descriptor valid.
2. Visit four literal labels. For each, check capacity, copy the complete string, call umi_reflection_resource_descriptor_validate, and compare the status with the expected admission result.
3. Create one small registry. Type, module and resource capacities are set to one, keeping this learning example deliberately bounded. Check creation before using its pointer.
4. Register image/svg+xml. The registry owns a copy of the metadata after successful registration. The local descriptor remains yours.
5. Change the local label to image/* and attempt an upsert. Upsert means insert when absent or replace when present. Here the invalid metadata must be refused before replacing the existing resource.
6. Read the stored descriptor and check that image/svg+xml remains. Destroy the registry through the cleanup path whether a later check succeeds or fails.


## Read the expected observations

These messages describe the operations this exercise checks. The process returns a failure code if an expected status, registry value or output operation fails. CTest reports that code. A passing run establishes these narrow metadata behaviors for the binary that ran. It does not prove image decoding, network transport, rendering or application UI behavior.

~~~text
umicom.layout: accepted
application/json: accepted
image/svg+xml: accepted
text/plain; charset=UTF-8: refused
Refused replacement preserved image/svg+xml.
Only metadata was inspected; no resource bytes were opened.
~~~


## Learn from a validator mismatch

An internal identifier validator may allow letters, digits, dots, underscores and hyphens. Reusing it for a media type would reject the slash in application/json and the plus sign in image/svg+xml. The underlying lesson is that two fields containing char arrays can still have different grammars. Test valid examples as well as invalid ones. An overly strict validator can prevent a supported workflow; an overly permissive validator can admit data that a later stage misinterprets.


## Keep the ownership boundary clear

The registry copies metadata, not the resource’s content. Destroying the registry releases its own records; it does not delete the described file or unload a decoder. A returned resource descriptor contains fixed arrays rather than pointers into registry storage. Other reflection snapshots can contain internal pointers, as the previous lesson demonstrated. Read the exact API contract instead of assuming that every structure with the word descriptor has identical copying rules. Serialize concurrent access according to the owning service’s contract.


## Apply the idea to Umicom products

Media can describe image and video assets, Studio can describe documentation or preview resources, and other applications can discover schemas or themes through a common catalogue. These clients should use the shared Framework validator and registry rather than maintaining separate copies. A renderer must still verify decoder support, content bounds, ownership and the user’s permitted operation. A descriptor that says image/svg+xml must never be treated as authority to execute arbitrary active content.


## Practice without opening untrusted content

1. Replace application/json with video/mp4 and predict the admission result before compiling. It should be accepted as a syntactically concrete name.
2. Replace it with video/* and explain why the result differs. A range is not a concrete subtype.
3. Explain why a 127-byte terminated name can fit while 128 nonzero bytes cannot. Account for the terminator.
4. After a refused upsert, identify which stored value must remain unchanged. Explain why returning an error after already replacing it would violate the intended behavior.
5. Write three separate questions for a future image importer: Is the label syntactically accepted? Does a compatible decoder support it? Do these actual bytes form an admitted image? Do not collapse the answers into one Boolean.


## Read the naming specification


- [RFC 6838 — media-type naming and registration](https://www.rfc-editor.org/rfc/rfc6838#section-4.2)


[Previous: Copy metadata with explicit pointer ownership](42-copy-metadata-with-explicit-pointer-ownership.md)

[Next: Add with a checked result](44-add-with-a-checked-result.md)
