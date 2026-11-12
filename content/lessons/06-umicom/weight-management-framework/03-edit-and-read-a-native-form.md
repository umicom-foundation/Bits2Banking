<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/weight-management-framework/03-edit-and-read-a-native-form.md

PURPOSE:
Build and inspect the C client

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Build and inspect the C client

## Before you begin
Use a Framework SDK containing the new weight-log header and matching application library. Read examples/weight_log/README.md. The following commands assume you are in the Framework source root; replace the SDK prefix with your installed qualified SDK.

~~~powershell
cmake -S examples/weight_log -B build/weight-log-consumer -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=C:/sdk/umicom
cmake --build build/weight-log-consumer
ctest --test-dir build/weight-log-consumer --output-on-failure
~~~

Run each command separately and stop on an error. This course gives the procedure; a source example is not an executed result on your machine.

## Read the ownership in main.c
The example allocates a UmiStructuredForm, obtains the immutable schema, parses kilograms and creates typed answers. The date has text type. Mass has integer type and the exact unit token mass.g.

~~~c
status = umi_structured_form_set(schema, form, form->revision,
                                "weight.mass_grams", &mass);
if (status == UMI_STATUS_OK)
    status = umi_weight_log_read(form, &entry);
~~~

The complete program handles earlier failures before reaching these calls. Copying this fragment alone does not initialize a form or authorize storage.

1. Find the allocation and its matching free.
2. Find where the current edit revision is supplied.
3. Find the unit assignment and distinguish it from the user-facing label.
4. Follow each failure to the final return code.

## Expected result
A qualified successful run prints Synthetic observation: 2024-02-29, 80250 g and returns zero. It has not saved a database record. Only this known fixture is printed; real notes and measurements should not enter ordinary diagnostic logs.

## Exercise and recovery
Change the fixture date to 2023-02-29 in a practice copy. Predict which shared call rejects it and why no final entry should be printed. Restore the valid fixture before comparing with the published example.

If the header is found but a symbol fails to link, inspect the SDK prefix and library identity. A mixed old library/new header is different from a C syntax error. If configuration cannot find Umicom::application, qualify the installed component rather than adding source files directly to the consumer.


[Course contents](index.md) · [Previous lesson](02-convert-kilograms-without-rounding.md) · [Next lesson](04-save-revisions-with-the-existing-record-service.md)
