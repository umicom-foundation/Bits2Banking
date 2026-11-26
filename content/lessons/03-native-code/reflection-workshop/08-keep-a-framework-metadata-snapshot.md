<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/08-keep-a-framework-metadata-snapshot.md

PURPOSE:
  Teach Framework registry ownership through an independent type metadata snapshot.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Keep a Framework reflection snapshot

[Workshop](index.md) · [Native C field catalogue](01-name-fields-in-native-c.md)

A Studio panel can display information about a type provided by another
component. When the component is removed, a report may still need the
description it already read. This lesson uses the Framework registry
to give the report independent storage for those facts.

## 1. Find the public description

Open [`registry_snapshot.c`](../../../labs/languages/reflection-workshop/framework-snapshot/registry_snapshot.c).
Find the `Reading` declaration and then `reading_fields`. A reflection field
descriptor is an explicit record of a member's name, layout and flags.
`UMI_REFLECTION_FIELD` gets the location and size from the C declaration.
The application supplies the description and works out which fields are
part of its public metadata.

Find the full type descriptor next. It records the stable ID
`workshop.reading`, schema version, live C type size and the two field
descriptions. The sample registers metadata for the type and creates no
`Reading` value.

## 2. Follow the owners in order

1. Call `umi_reflection_registry_register_type`. On success the registry
   owns copies of the non-empty descriptor arrays.
2. Call `umi_reflection_registry_get_type` with the exact type ID. It
   prepares a snapshot in storage supplied by the caller. The snapshot's
   descriptor points into the arrays in that specific snapshot object.
3. Use `umi_reflection_type_snapshot_copy` for the second retained
   snapshot. It sets the destination descriptor's pointers to its own
   arrays. Ordinary structure assignment would copy the old pointer
   addresses unchanged.
4. Unregister the type and destroy the registry. Clear the original
   snapshot. The report reads the retained snapshot and checks where its
   field pointer points before reading the fields.

[Framework registry declarations](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/reflection/registry.h)

## 3. Build against an installed Framework SDK

Use an SDK whose `reflection` component exports the public snapshot copy
API. Prepare a C23 compiler for the same target and toolchain family as
the SDK. Open PowerShell in the Bits2Banking repository and set `$Sdk` to
the full path of that SDK. This example uses CMake 3.25 or later and Ninja.

```powershell
$Sdk = 'C:\path\to\UmicomFrameworkSdk'
$Lab = '.\content\labs\languages\reflection-workshop\framework-snapshot'
$Out = '.\build\reflection-framework'
cmake -S $Lab -B $Out -G Ninja -DCMAKE_BUILD_TYPE=Debug "-DCMAKE_PREFIX_PATH=$Sdk"
cmake --build $Out --target framework-registry-snapshot
& (Join-Path $Out 'framework-registry-snapshot.exe')
```

Run each line separately. Stop on a configure or build error. Read the
SDK and component named by the error before trying a different SDK.

```text
Registered type: workshop.reading (2 fields)
Registry count after removal: 0
Retained fields: 2
station_id: read-only flag set
degrees_c: read-only flag clear
```

The current registry count confirms removal. The next three lines show
that the retained record still owns two readable fields. A descriptor's
flags guide a client when it displays metadata. A real write still needs
the application to validate the selection, value, live object and permission.

## 4. Check a policy change

In a practice copy, add `UMI_REFLECTION_FIELD_READ_ONLY` to the
`degrees_c` description. Rebuild and compare the report. Expect only the
final line to change from `clear` to `set`. Explain why the type remains
registered under the same ID and how a consumer can label that observation.

[Return to the workshop](index.md)
