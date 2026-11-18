![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# A small C boundary for FreeBASIC and D

This original teaching service calculates an integer percentage rounded down without allocating memory. Status 0 means success; status 1 means invalid input and leaves the result untouched. It is not a complete Framework binding.

## Verify the C contract

From the Bits2Banking repository root, with CMake, Ninja and a C23 compiler available:

~~~powershell
cmake -S labs/languages/native-language-boundary -B build/native-language-boundary -G Ninja
cmake --build build/native-language-boundary
ctest --test-dir build/native-language-boundary --output-on-failure
~~~

Run one command at a time and stop if it fails. <!-- Earlier single-test expectation retained: Expect one passing test covering maximum 32-bit input, rounding, null output and invalid counts. -->
Expect two passing tests: percentage arithmetic and callback admission/ownership. It does not run either optional language client.

## FreeBASIC with compatible GNU objects

Use matching architecture GNU/FreeBASIC toolchains; check fbc -version and gcc --version. From this lab folder:

~~~powershell
gcc -std=c23 -Wall -Wextra -c boundary.c -o boundary.o
fbc -lang fb -w all -exx client.bas boundary.o -x basic-client.exe
.\basic-client.exe
~~~

Expect 25 and the FreeBASIC checks message. If the linker rejects the object format or runtime symbols, verify architecture, object format and compiler-runtime compatibility. Do not guess a different parameter type. Unix shells run ./basic-client after choosing that output name.

## D with matching Microsoft objects on Windows

In a developer terminal providing a compatible Microsoft C toolchain and DMD, from this folder:

~~~powershell
cl /nologo /W4 /c boundary.c /Foboundary.obj
dmd -m64 client.d boundary.obj -of=d-client.exe
.\d-client.exe
~~~

The C source uses fixed-width operations supported by a modern Microsoft C compiler. Expect 25 and the D checks message. This is an alternative to the GNU example, not an instruction to mix its boundary.o with this command. On a supported Unix DMD target, pass a matching gcc-produced boundary.o to dmd client.d boundary.o -of=d-client.

FreeBASIC and D clients require compiler-specific execution. Passing C tests do not qualify them. Record compiler version, target and commands. Do not disable checks to hide an ABI problem.

## Connect the idea to Umicom Framework

Start from installed SDK public C headers and exported targets. Wrap required functions, preserve UmiStatus results, document UTF-8 lengths, and provide the Framework release function for each owned handle. Never pass a FreeBASIC String or D array descriptor as an undocumented C pointer. A declaration is an agreement, not a conversion. Exceptions must not cross a C boundary.

The learning-freebasic and learning-d courses explain these clients. Production reusable services remain in Framework; this calculation is confined to the teaching lab.

## Inspect D types without crossing the C boundary

`runtime_types.d` is an independent ordinary-D exercise. It uses classes and
runtime type information, so it does not use `-betterC` and does not link
`boundary.o` or `boundary.obj`. From this lab folder:

~~~powershell
dmd --version
dmd runtime_types.d -of=runtime-types.exe
.\runtime-types.exe
~~~

Expect `Image width: 640`, `Resources created: 2` and
`Type inspection checks passed`. Keep assertions enabled. The example compares
`typeof`, `typeid`, checked class casts and a range-checked integer conversion.
Lesson 23 of Learning D explains each line and controlled failure exercises.
D compiler execution remains a separate requirement from the C boundary test.

## Parse a complete BASIC count

`parse_count.bas` accepts one to seven ASCII digits with a numeric value from
zero through one million. It rejects signs, spaces, trailing text and values
outside that range without changing the output. It is an independent teaching
exercise and does not link the C boundary object. From this folder:

~~~powershell
fbc -version
fbc -lang fb -w all -exx parse_count.bas -x parse-count.exe
.\parse-count.exe
~~~

Expect `Strict count checks passed`. Lesson 15 of Learning FreeBASIC explains
the grammar, the pre-multiplication bound check and every controlled failure.
These BASIC checks require a FreeBASIC compiler; the C tests do not execute them.

## Follow a synchronous C callback

`callback_client.bas` and `callback_client.d` call the new teaching function
`bounded_progress_visit`. C validates all three rows, then calls the selected
language function on the same thread. The callback stops on row1. Two callbacks
were attempted, but only the first was accepted. Neither callback nor context
is retained after the function returns.

Use the same matching object-toolchain setup as the earlier C client:

~~~powershell
gcc -std=c23 -Wall -Wextra -c boundary.c -o boundary.o
fbc -lang fb -w all -exx callback_client.bas boundary.o -x basic-callback.exe
.\basic-callback.exe
~~~

Or, separately, in a matching Microsoft C/DMD developer terminal:

~~~powershell
cl /nologo /W4 /c boundary.c /Foboundary.obj
dmd -m64 callback_client.d boundary.obj -of=d-callback.exe
.\d-callback.exe
~~~

Do not mix the GNU object from the first block with the Microsoft-object block.
The C callback test passing does not establish that either language compiler
accepted its declarations. FreeBASIC/D execution is separate qualification.
Read the corresponding callback lesson before changing the calling convention,
parameter width or context lifetime.

## Inspect declared D field metadata

`field_metadata.d` attaches user-defined labels to two fields and inspects them
with `FieldNameTuple`, `FieldTypeTuple` and `getUDAs`. It generates descriptions
at compile time; it does not create runtime field enumeration or a Framework ABI.
Use an ordinary D runtime build, with assertions and unit tests enabled:

~~~powershell
dmd --version
dmd -unittest field_metadata.d -of=field-metadata.exe
.\field-metadata.exe
~~~

Expect descriptions for `account` and `balanceMinor`, followed by the metadata
checks message. Lesson 25 of Learning D explains annotation versus enforcement,
compile-time iteration and why native object layout is not a file format. D
compiler execution remains required; the C tests do not compile this example.

## Encode an explicit four-byte BASIC field

`encode_record.bas` encodes a 32-bit unsigned value in little-endian byte order.
It checks exact array bounds before writing and preserves the caller's result on
a rejected decode. It does not open a file or expose a BASIC record's memory.

~~~powershell
fbc -version
fbc -lang fb -w all -exx encode_record.bas -x encode-record.exe
.\encode-record.exe
~~~

Expect `78 56 34 12` and `Explicit byte-format checks passed`. Lesson 17 of
Learning FreeBASIC explains each mask, shift and bound check, including why a
round trip needs an independent expected byte sequence. These checks are authored
for FreeBASIC qualification and are not executed by the C lab suite.

## Read BASIC comments without executing their contents

`comments.bas` uses REM, apostrophe comments, a colon statement separator and
quoted text. It checks that only the executable addition changes its integer.

~~~powershell
fbc -lang fb -w all -exx comments.bas -x comments.exe
.\comments.exe
~~~

Expect `REM ?> is text inside a string` and `Comment checks passed`. The
FreeBASIC compiler must still qualify this example. Lesson18 also explains the
separate Umicom C `regions` command, whose REM handling is classification only.
Do not confuse a successful region scan with BASIC or mixed-language execution.

## Checked option masks in FreeBASIC

`checked_flags.bas` distinguishes enabling, disabling and toggling. It rejects
unknown bits before changing the ByRef output and tests an empty requirement
explicitly. These options are teaching values, not an authorization service.
From this directory, with the FreeBASIC compiler available:

~~~powershell
fbc -lang fb -exx -g checked_flags.bas -x checked_flags.exe
.\checked_flags.exe
~~~

Expect binary 101 for read plus audit, 100 after disabling read, then the final
check message. This subject-language exercise requires its own compilation.

## Compile-time type admission in D

`conditional_wire.d` uses static if, a template constraint, static foreach,
static assert and __traits(compiles) to admit explicit uint/ulong encodings.
It compares fixed expected bytes in unittest blocks and includes optional named
debug output. It uses the normal D runtime, not BetterC or a C ABI export.

~~~powershell
dmd -unittest -g conditional_wire.d -of=conditional_wire.exe
.\conditional_wire.exe
dmd -unittest -g -debug=TraceEncoding conditional_wire.d -of=conditional_wire_trace.exe
.\conditional_wire_trace.exe
~~~

Both builds should print decimal bytes 120, 86, 52, 18. The second also includes the
TraceEncoding message. Compiler options above are DMD-specific; verify the
corresponding options when choosing LDC or GDC. No compiler result is implied
by reading this guide or by passing the separate C boundary checks.


## Named constants and read-only views

`named_constants.bas` uses typed FreeBASIC constant expressions for a checked
box-count calculation. Runtime inputs stay ordinary variables; invalid inputs
leave the caller’s output unchanged. `readonly_views.d` shows how a D const
slice can still observe changes through an existing mutable alias, while
`.dup` and `.idup` produce independent copies of these integer elements.

```powershell
fbc -lang fb -exx -w all named_constants.bas -x named_constants.exe
.\named_constants.exe
dmd -g readonly_views.d -of=readonly_views.exe
.\readonly_views.exe
```

The BASIC example should report 42 accepted units, a 600-unit declared bound
and preserved output after refusal. D should print `[8, 7]`, `[6, 9]`,
`[6, 7]` and `[7]` in that order. These subject-language samples require their
own compiler runs; C or Framework tests do not validate them. Both use their
normal language runtime and do not change Framework production language policy.

## Dynamic BASIC entries and D record lookup

`dynamic_entries.bas` bounds an array to eight numeric entries, retains an existing prefix when growing, demonstrates the loss of a truncated tail, and releases dynamic storage with Erase. It keeps no element pointer across a resize. Its application-limit refusal preserves the existing array; it does not promise recoverable behavior for every allocator failure.

`record_lookup.d` distinguishes an absent key from a present zero count, shows shared associative-array assignment and an independent scalar-value duplicate, and sorts copied keys before printing. This is an ordinary D runtime example using associative arrays and library sorting, not a BetterC or allocation-free example. Neither map is a vector database or trained model.

```powershell
fbc -version
fbc -exx dynamic_entries.bas -x dynamic_entries.exe
& .\dynamic_entries.exe
dmd --version
dmd -checkaction=context -of=record_lookup.exe record_lookup.d
& .\record_lookup.exe
```

Run each command separately and stop on errors. These commands are provided for compiler qualification; the examples have not been compiled in the current authoring environment. BASIC should retain 10, 20 and 0 after shrink/regrow. D should print alpha=4, beta=0, then independent alpha=9. Keep checks enabled and record the exact compiler version.

## Temporary values in FreeBASIC

Compile `scoped_values.bas` with `fbc -lang fb scoped_values.bas -x scoped_values.exe`. The expected inner, outer, reviewed and final values are 7, 4, 11 and 15. This source exercise demonstrates shadowing and result copying; it does not claim automatic release of external resources. FreeBASIC compilation remains to be checked with the installed FreeBASIC toolchain.

## Use D metadata to generate explicit checks

`reflected_ranges.d` attaches one InclusiveRange annotation to each PreviewOptions field, inspects those rules at compile time, and checks the actual numeric values at runtime. It accepts only uint and long fields so every accepted value fits the signed comparison type. The unittest block covers low/high failures, inclusive endpoints, first-error order and unchanged source values.

~~~powershell
dmd -unittest -checkaction=context -of=reflected-ranges.exe reflected_ranges.d
& ".\reflected-ranges.exe"
~~~

Expected output includes a valid result of true, an invalid field named width, and unchanged values 640 x 360 with 20 steps. This example remains uncompiled in the current authoring environment. No pass is implied by separate C/Framework tests. The D course lesson 29 explains every stage and contrasts the example with Framework's existing explicit C reflection metadata. Individual ranges do not establish a combined memory budget or permission to run a job.

## Distinguish counted text from encoded bytes

`text_bytes.bas` constructs a small UTF-8 fixture from explicit byte values, demonstrates an embedded zero in a counted String, and shows how a four-byte prefix can split a two-byte code point. It also contains an explicitly narrow printable-ASCII label policy; that function is not a general Unicode validator.

~~~powershell
fbc -lang fb -exx -w all text_bytes.bas -x text_bytes.exe
& ".\text_bytes.exe"
~~~

Expected values are six ASCII bytes, five bytes for the accented fixture, final byte values 195 and 169, and three bytes in the string containing zero. The B after that zero remains in the counted String. This FreeBASIC source is not yet compiler-qualified in the current environment. Lesson 23 explains byte positions, encoding, runtime string ownership and why LLM tokens are a different measure.


## Inspect an Umicom C envelope in FreeBASIC and D

The matching `inspect_umc_header.bas` and `inspect_umc_header.d` examples inspect the
current eight-byte wire header and exact payload length. They reject truncated
prefixes, unsupported profiles, reserved flags, invalid counts and trailing
bytes while preserving the previous output. Neither is a complete decoder.
They deliberately accept a valid envelope whose first opcode was changed to
255; only the Umicom C runtime determines whether its instruction body is valid.

~~~powershell
fbc -lang fb -exx -w all inspect_umc_header.bas -x inspect_umc_header.exe
& ".\inspect_umc_header.exe"
dmd -unittest -g -checkaction=context inspect_umc_header.d -of=inspect_umc_header.exe
& ".\inspect_umc_header.exe"
~~~

Run the two subject-language examples separately; their output filenames are
shown for separate compiler runs. Keep each compiler's evidence separately, or
choose different output names if retaining both executables. The expected facts
are profile 1, two instructions and 26 bytes. FreeBASIC and D compilation remains
unverified in the current authoring environment. D uses its normal runtime;
only the inspector function carries @safe, pure, nothrow and @nogc attributes.
It uses ref because out would reset the caller's result before validation.

The independent `check_umc_fixture.c` sends the same literal to the actual
Umicom C runtime. It checks a return value of 42 and rejects both opcode 255
and a noncanonical higher profile. From the Bits2Banking repository root:

~~~powershell
cmake -S labs/languages/native-language-boundary -B build/native-wire-lesson -G Ninja -DUMICOM_C_SOURCE=C:/umicom/umicom-c -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/native-wire-lesson
ctest --test-dir build/native-wire-lesson --output-on-failure --no-tests=error
~~~

This opt-in configuration retains the two existing C boundary checks and adds
the native bytecode reference check. It uses the runtime's own source-composition
helper and Framework branding resources; no full Framework or application build
is needed. The default configuration without UMICOM_C_SOURCE still owns only
the existing boundary and callback tests. A C pass does not validate either
subject-language implementation. Read FreeBASIC lesson 24 and D lesson 30 for
the step-by-step explanation, array rules, refusal tests and learning exercises.

## Read records and follow their lifetime

`line_records.bas` and `line_records.d` inspect the original ASCII `line-fixture.txt`: four records, three nonempty records and thirteen text bytes. Both keep the first nonempty record, `apple`, and close the input. The BASIC example checks runtime error state inline; compile without `-e`, `-ex` or `-exx` for this error-handling model. The D example copies one retained row because the line range may reuse its buffer.

Use distinct executable names so that one language cannot accidentally run the other example’s old output. From this lab directory, stop on compilation errors:

~~~powershell
fbc -lang fb -g line_records.bas -x line-records-basic.exe
& ".\line-records-basic.exe" ".\line-fixture.txt"
dmd -g -of=line-records-d.exe line_records.d
& ".\line-records-d.exe" ".\line-fixture.txt"
~~~

These original sources are authored exercises. FreeBASIC and D compilation/runtime results remain unverified here. The checks after a line is read limit accepted records; they do not bound a dynamic line allocation. Use the small fixture and a separate copy for boundary experiments. This code is not a general encoding detector, JSONL validator, tokenizer or production importer. Read the paired BASIC and D course lessons for definitions, expected results and error paths.

## Observe local object lifetimes in FreeBASIC

Read `lifetime_probe.bas` with the [construction and destruction lesson](../../../content/lessons/03-native-code/learning-freebasic/26-follow-construction-and-destruction.md). It observes nested local values and a normal early return without owning pointers or other native resources.

~~~powershell
fbc -lang fb -w all lifetime_probe.bas -x lifetime_probe.exe
& .\lifetime_probe.exe
~~~

Expected identity order: create 1, create 2, destroy 2, create 3, destroy 3, destroy 1. All three counters are checked. This is single-threaded observation code, not a safe-copy implementation for a resource-owning wrapper.

## Distinguish D output publication policies

Read `output_publication.d` with the [ref and out lesson](../../../content/lessons/03-native-code/learning-d/32-publish-results-with-ref-and-out.md). The example compares an unchanged-on-refusal result with an `out` parameter that is initialized on entry.

~~~powershell
dmd -unittest -g -of=output_publication.exe output_publication.d
& .\output_publication.exe
~~~

Keep assertions enabled. Expect `ref refusal preserves: 71` and `out refusal starts from: 0`. The unsigned arithmetic checks overflow before computing the sum.

These two commands require their real language compilers. The CMake tests above do not validate either language example, and no successful FreeBASIC or D run is implied by a C test pass.

## Select overloads and admit named states

`overloaded_byte_count.bas` has two typed FreeBASIC overloads sharing one checked
32-bit byte-count rule. A String input uses its counted byte length; a wider
numeric input is checked before narrowing. Refusal leaves the old result intact.
Read [FreeBASIC lesson 27](../../../content/lessons/03-native-code/learning-freebasic/27-select-an-overload-by-its-arguments.md).

`explicit_job_states.d` admits four sparse byte codes before mapping them through
an exhaustive enum switch. Compile-time enumeration prints every declared state;
unit tests check all 256 possible input bytes. Read
[D lesson 33](../../../content/lessons/03-native-code/learning-d/33-admit-enumerated-states-before-dispatch.md).

From this laboratory directory, run each command separately and stop on errors:

~~~powershell
fbc -lang fb -w all overloaded_byte_count.bas -x overloaded-byte-count-basic.exe
& .\overloaded-byte-count-basic.exe

dmd -unittest -g -of=explicit-job-states-d.exe explicit_job_states.d
& .\explicit-job-states-d.exe
~~~

Expect BASIC counts 6, 42, preserved 71 and empty 0. Expect four D states and
refusal of byte 3 while preserving failed. Both subject-language examples remain
uncompiled in the authoring environment. C regression passes do not qualify
these compiler-specific rules, and neither example is a production Framework ABI.

## Observe when an argument is evaluated

The FreeBASIC example `short_circuit_guards.bas` contrasts safe counter calls under And/Or with AndAlso/OrElse, then checks bounds before reading an array with lower bound 2. The D example `lazy_evaluation.d` observes zero, two and one evaluation of a deferred expression. A lazy parameter does not automatically cache its result or run on another thread.

With the appropriate subject compiler available, run each section separately and stop on errors:

```powershell
New-Item -ItemType Directory -Force build/learning-languages | Out-Null
fbc -lang fb -exx labs/languages/native-language-boundary/short_circuit_guards.bas -x build/learning-languages/short-circuit-guards.exe
& ".\build\learning-languages\short-circuit-guards.exe"

dmd -unittest -checkaction=context -of=build/learning-languages/lazy-evaluation.exe labs/languages/native-language-boundary/lazy_evaluation.d
& ".\build\learning-languages\lazy-evaluation.exe"
```

The BASIC program finds index 3 exactly once. The D observations are result/evaluation-count pairs 40/0, 3/2 and 2/1. These are source exercises requiring subject-language qualification; a C build does not compile them.

## Read-only properties and invariant checks

`read_only_properties.bas` exposes a budget through a FreeBASIC getter while checked methods refuse invalid changes. `budget_invariant.d` adds a D object invariant but still performs explicit input checks. The examples own no Framework object and do not imply a shared binary layout. They are language teaching sources; compiler execution must be checked in your installed environment.

```powershell
fbc -lang fb -exx read_only_properties.bas -x read_only_properties.exe
.\read_only_properties.exe
dmd -unittest -checkaction=context budget_invariant.d -of=budget_invariant.exe
.\budget_invariant.exe
```

Run from this directory and stop on an error. Expected BASIC output reports preserved state and exact consumption; expected D output reports preserved value 3. Keep checks enabled while learning. Input refusal must not depend solely on an assertion that a release build could disable.

## Embedded BASIC data and explicit D modules

The BASIC fixture data_records.bas contains exactly four records of four values.
The loop count and field order are part of that trusted source fixture. Read does
not provide a safe end-of-data query: never increase the read count without
adding complete records. Restore moves the next-read cursor back to a label;
it does not clear variables or parse an external document.

From this lab directory, with FreeBASIC available:

~~~powershell
fbc -lang fb -exx data_records.bas -x data-records-basic.exe
.\data-records-basic.exe
~~~

Expect areas 230400 and 2073600, then two refusals preserving 71, followed by a
restored first record of 640 by 360. These are unsigned 32-bit area examples,
not allocations or production image decoding.

The D module_client.d program imports two original modules under umicom_lessons.
The arithmetic module owns checked multiplication; pixel_budget composes the
nonempty four-byte-per-pixel rule; the client prints observations. Supply all
three implementation files to this explicit compiler invocation:

~~~powershell
dmd -unittest -checkaction=context -I. -of=module-client-d.exe module_client.d umicom_lessons/checked_product.d umicom_lessons/pixel_budget.d
.\module-client-d.exe
~~~

Expect 921600 bytes for 640 by 360 RGBA pixels, preserved 71 after refused inputs,
and zero from the generic multiplication service. An import makes names visible;
it is not proof that an implementation object has been linked. Keep normal D
runtime support enabled because the client uses std.stdio. No Framework ABI or
Umicom C mixed-language compilation is implied. Both subject-language examples
are authored and require their own compiler/runtime qualification; C checks do
not validate these sources. Stop after a failed compiler command rather than
launching a retained executable from an older build.

## Record drafts and typed declaration reuse

`record_drafts.bas` uses nested `With` blocks to edit a value record. Its checked
function creates a local candidate and assigns it only after admission. `With`
alone offers no validation, copy or rollback. Run from this lab directory:

```powershell
fbc -lang fb -exx record_drafts.bas -x record-drafts-basic.exe
.\record-drafts-basic.exe
```

Expected output reports input 640 by 360, accepted output 800 by 600, and retained
accepted dimensions after an oversized and an empty request. No image is read,
allocated or resized. The one-million-pixel limit is an exercise policy.

`typed_counter_mixins.d` inserts one typed bounded-counter declaration pattern
into two different structures. Each instance owns its own numeric state; copying
this pointer-free value creates independent state. Run with checks enabled:

```powershell
dmd -unittest -checkaction=context typed_counter_mixins.d -of=typed-counter-mixins.exe
.\typed-counter-mixins.exe
```

Expected lines are `preview=2 remaining=1`, `export=6 remaining=0` and
`copy=3; preview stays 2`. The program checks these conditions through normal
branches as well as unit tests. It neither implements a thread-safe counter nor
defines a binary interface to C. Template mixins are compile-time declaration
reuse, not a runtime plug-in loader. These FreeBASIC/D examples require their own
subject compiler qualification; successful C checks do not establish that result.

## Follow multidimensional pixels in BASIC and D

`pixel_grid.bas` uses explicit row, column and channel bounds and checks four pixel sums. `static_pixel_arrays.d` uses nested static arrays to contrast copied rows with referenced rows. Neither program decodes an image or runs a model. The companion Framework image-tensor laboratory performs the actual reusable RGB-to-float conversion in C.

~~~powershell
fbc -lang fb -w all -exx pixel_grid.bas -x pixel_grid.exe
& .\pixel_grid.exe
dmd -unittest -checkaction=context -of=static_pixel_arrays.exe static_pixel_arrays.d
& .\static_pixel_arrays.exe
~~~

Run separately and stop on any error. The BASIC exercise reports four channel sums: 255, 255, 255 and 765; the total is 1530. Integer spacing may vary. The D exercise expects original total 1530 after editing copied rows, edited total 1020 after removing red through references, and saved-copy total 1530. The D example uses the ordinary runtime for console output; it is not a BetterC executable.

These language examples are authored with official reference review. FreeBASIC and D compilation/execution have not been performed in the current mirror environment. C tests of Framework’s separate converter do not qualify these language programs.

## Admit fixed fields and decode text units

`fixed_ascii_fields.bas` formats printable ASCII fields after checking width and content. It preserves the previous field on a normal refusal and demonstrates raw LSet truncation separately. `utf_text_units.d` compares UTF-8/16/32 unit counts, code-point offsets and invalid UTF-8 refusal. Neither example defines a production bank record or model tokenizer.

~~~powershell
fbc -lang fb -w all -exx fixed_ascii_fields.bas -x fixed_ascii_fields.exe
& .\fixed_ascii_fields.exe
dmd -unittest -checkaction=context -of=utf_text_units.exe utf_text_units.d
& .\utf_text_units.exe
~~~

Run separately and stop on errors. Expected BASIC fields are `[AB7   ]`, `[    42]`, retained `[AB7   ]`, four spaces and deliberate raw truncation `[LONG]`. D reports lengths 7, 4 and 3, UTF-8 offsets 0, 1 and 3, two code points in the combining example, and malformed UTF-8 refusal. These language examples remain uncompiled and unexecuted in the current mirror environment; course-link or C tests do not qualify their language behavior.

## Exchange values and preserve view qualifiers

swap_values.bas follows scalar values, pointer aliases and variable-length
string exchanges. It checks that swapping pointers changes which object a
pointer names without exchanging the integers themselves. Expected observations
are values 42 and 6, then 42 and 9 after the pointer write, labels [export] and
[preview], and 42 after the same-variable exchange. Integer spacing may vary.

qualifier_preserving_views.d returns bounded prefixes through one inout function.
Its unit tests inspect mutable, const and immutable result types at compile time.
The runtime observations are mutable=8 const=8 frozen=3, lengths=2,3,2 and empty
length=0. Borrowing neither allocates an independent copy nor extends arbitrary
native storage lifetime. The console program still uses ordinary D runtime support.

~~~powershell
fbc -lang fb -w all -exx swap_values.bas -x swap_values.exe
& .\swap_values.exe
dmd -unittest -checkaction=context -of=qualifier_preserving_views.exe qualifier_preserving_views.d
& .\qualifier_preserving_views.exe
~~~

Run separately and stop on errors. These original language exercises remain
uncompiled and unexecuted in the current mirror environment. Check the compiler
identity: a command named gdc may be an unrelated shell alias. Existing C tests
and lesson-link checks do not validate FreeBASIC or D source acceptance.

## Inspect storage before defining a file format

record_layout.bas and record_layout.d inspect a one-byte kind and a four-byte
count in default and deliberately packed records. Native layout observations
are target-dependent. Both examples expect the explicit packed record to occupy
five bytes with count at offset one. Neither saves raw record bytes.

~~~powershell
fbc -lang fb -w all -exx record_layout.bas -x record_layout.exe
& .\record_layout.exe
dmd -unittest -checkaction=context -of=record_layout_d.exe record_layout.d
& .\record_layout_d.exe
~~~

Run separately and stop on errors. FreeBASIC SizeOf(samples) returns the element
datatype size, four bytes; its three-element payload is calculated from bounds
and occupies twelve bytes. D's static array occupies twelve bytes, while a slice
descriptor has a target-dependent size distinct from its referenced payload.
Use typed field copies and explicit encoders rather than dumping padding or
runtime descriptors. These examples remain uncompiled and unexecuted in this
mirror; a course-link check is not subject-language qualification.

## Own background workers explicitly

thread_counter.bas uses one mutex around a shared counter and joins every successfully created worker before destroying the lock or its borrowed context. thread_counter.d uses a shared atomic counter and scope-exit joins; the final result is read only after the owner helper returns. Both finite-worker examples expect 20,000 increments and keep partial-start cleanup explicit.

~~~powershell
fbc -lang fb -mt -w all -exx thread_counter.bas -x thread_counter_basic.exe
& .\thread_counter_basic.exe
dmd -unittest -checkaction=context -of=thread_counter_d.exe thread_counter.d
& .\thread_counter_d.exe
~~~

Run separately and stop on errors. These examples remain uncompiled and unexecuted here. The D helper is deliberately serial and non-reentrant, and uses the normal D runtime. Neither example is a reusable application scheduler, cancellation service or performance benchmark. Garbage collection, atomic fields and guessed delays do not replace explicit worker completion.

## Select one union alternative explicitly

`tagged_number.bas`, `tagged_number.d` and `tagged_number.c` store either a whole or fractional value with an explicit tag. Checked accessors preserve caller outputs on a mismatch or unknown tag. The D example uses compile-time field checks to distinguish structural reflection from runtime selection. These records are teaching types, not an exported cross-language ABI.

```powershell
fbc -lang fb -w all -exx tagged_number.bas -x tagged_number_basic.exe
& .\tagged_number_basic.exe
dmd -unittest -checkaction=context -of=tagged_number_d.exe tagged_number.d
& .\tagged_number_d.exe
```

Run separately and stop on errors. To qualify the C counterpart independently of optional BASIC/D compilers, configure this laboratory with approved Framework branding resources:

```powershell
cmake -S . -B build/tagged-number -G Ninja -DUMICOM_BUILD_TAGGED_NUMBER_LAB=ON -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/tagged-number --parallel 2
ctest --test-dir build/tagged-number --output-on-failure
```

A C test pass is not evidence that a BASIC or D compiler ran. Unknown tags are refused before payload reads. No example serializes native union bytes, treats a tag change as numerical conversion, or implements owning-pointer alternatives.

## Selective expressions and ordinary arguments

`conditional_selection.bas`, `.d` and `.c` use separate harmless counters to show which expressions run. FreeBASIC IIf and D/C conditional expressions select one branch. An ordinary function receiving two by-value arguments receives values that were already computed. The examples do not rely on an argument evaluation order. They exercise both true and false choices.

~~~powershell
fbc -lang fb -exx conditional_selection.bas -o conditional_selection.exe
.\conditional_selection.exe
dmd -unittest -g -of=conditional_selection-d.exe conditional_selection.d
.\conditional_selection-d.exe
~~~

FreeBASIC and D executions require those compilers and remain unverified here. The current FreeBASIC keyword reference documents selected-expression evaluation; do not substitute rules from another BASIC dialect or an older conflicting tutorial. The complete programs are small executable specifications to check against your selected toolchain.

For the C comparison, configure this laboratory with `-DUMICOM_BUILD_CONDITIONAL_SELECTION_LAB=ON -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework`, build `umicom-conditional-selection`, and run `ctest --test-dir build -R conditional-selection --output-on-failure`. Use your actual matching Framework source location. This C result does not validate either other language.


## Local names and retained storage

The `local_storage.bas`, `local_storage.d` and `local_storage.c` examples compare a fresh automatic counter, a retained static counter and two explicitly owned counters. Automatic calls produce 1, 1; static calls in one process/thread produce 1, 2. Separate owners remain independent. At the small teaching cap of 3, refusal preserves both the counter and the output sentinel 99.

~~~powershell
fbc -lang fb -exx local_storage.bas -o local_storage.exe
.\local_storage.exe
dmd -unittest -g -of=local_storage-d.exe local_storage.d
.\local_storage-d.exe
~~~

<!-- Earlier exercise instruction retained for review: Keep D assertions enabled: these are executable teaching checks, and compiling with release-mode assertion removal would remove checks and some calls. -->
The active D example uses an ordinary checked function so its calls and checks still execute when assertions are disabled. Its earlier assertion-based form remains disabled for review. The FreeBASIC and D programs remain authored examples until exercised with those compilers. Their behavior must not be inferred from a C run.

The C comparison uses the optional `UMICOM_BUILD_LOCAL_STORAGE_LAB` CMake option and the existing Framework branding source path. Build `umicom-local-storage` and run CTest with `-R local-storage`. This is host C23 code using a compiler such as GCC; it is not an example within Umicom C's current bounded integer-language profile.

A static local name does not imply one object per caller. D mutable static variables are thread-local by default; C and FreeBASIC static locals are shared storage and need a separately designed synchronization policy for concurrent mutation. None of these examples starts threads. Static storage does not automatically persist to disk or survive restarting the process.

## Nested BASIC comments

Read `block_comments.bas` with the BASIC comment lesson. It demonstrates nested blocks and an expression that continues across a newline inside a comment. Build with `fbc -lang fb -exx block_comments.bas -o block_comments.exe`, then run `./block_comments.exe`. Expect `Answer: 42` and `Nested comments preserved the statement`. This example requires the subject-language compiler; native C checks do not validate it. Umicom C region discovery is a separate lexical-only tool.

## Runtime dispatch through a common interface

Read `virtual_rules.bas` and `virtual_rules.d` with the runtime-dispatch lessons. The first uses concrete FreeBASIC values and borrowed base pointers; the second uses D class objects and interface references. They test zero, boundary and excess requests with two explicit admission policies. These are original language exercises, not production Framework provider contracts.

~~~powershell
fbc -lang fb -exx virtual_rules.bas -o virtual_rules-basic.exe
.\virtual_rules-basic.exe
dmd -unittest -g -of=virtual_rules-d.exe virtual_rules.d
.\virtual_rules-d.exe
~~~

Expect `Umicom virtual rules: all checks passed` only after all checks execute. Ordinary Require/require calls keep operations active when assertions are disabled. No FreeBASIC or D compiler run is implied by source publication; record compiler version, target and result when exercising them. Do not pass language-specific objects/vtables across a C ABI. Reuse explicit C function/context contracts for native Framework integration.


## Boolean values and binary flag bytes

The original boolean_wire.bas, boolean_wire.d and boolean_wire.c examples use an explicit one-byte teaching format: only 0 and 1 are valid. Each tests every possible byte, rejects 2..255 and preserves the destination on refusal. A successful decode of zero returns success while producing false. Do not confuse that status with the decoded value.

~~~powershell
fbc -lang fb -exx boolean_wire.bas -o boolean-wire-basic.exe
.\boolean-wire-basic.exe

dmd -unittest -g -of=boolean-wire-d.exe boolean_wire.d
.\boolean-wire-d.exe
~~~

Expected final lines after successful execution are:

~~~text
Umicom Boolean wire: all 256 bytes checked.
Explicit encoding: false=0, true=1.
~~~

FreeBASIC converts its logical true value to integer -1; D converts true to integer 1. Neither fact is permission to copy a language's Boolean storage bytes into an external record. The explicit encoder defines this record's bytes. Native C and D numeric-to-Boolean conversion also accepts nonzero values such as 2, which is deliberately invalid in this strict record format. Validate before converting.

The C comparison uses UMICOM_BUILD_BOOLEAN_WIRE_LAB=ON and the existing Framework branding source path. Build umicom-boolean-wire and select CTest with -R boolean-wire. This host C23 program is separate from Umicom C's bounded integer language, which supports true/false literal spelling but not a bool variable type. C qualification does not qualify the authored FreeBASIC and D examples.


## Choose numeric conversion policies explicitly

`rounding_policy.bas` compares FreeBASIC `CInt`, `Fix` and `Int` on exact halves and quarters. `rounding_policy.d` compares D casts, `trunc`, `floor`, `ceil` and `round`. Each has a separate checked signed-32-bit boundary that admits the original value and preserves the caller’s integer on refusal. The languages deliberately have different nearest-halfway defaults; use the explicit shared Framework contract for product calls.

Follow BASIC lesson 43 and D lesson 48 for the complete steps, tables, expected output and recovery guidance. These subject-language examples require their own compilers; a C exercise pass does not qualify them.

## Operators with an explicit meaning

`flag_operators.bas` and `flag_operators.d` teach bit-set union/intersection without mutating operands. A separate admission function refuses unknown external bits and preserves the caller’s previous result. The D version constrains its operator template and checks supported syntax with reflection; reflection is not a test of mathematical correctness or authorization.

Read BASIC lesson 44 and D lesson 49 for exact commands, expected output and recovery. Both subject-language examples remain uncompiled in this mirror environment. Production Framework behavior remains in the shared C service.

## D comment and string boundaries

The standalone comment_boundaries.d example compares raw and escaped paths with
a compile-time assertion. It prints delimiter characters as data and uses balanced
nested comments. It requires an actual D compiler and runtime. The separate
Umicom C regions command classifies examples/d_regions.umc; it does not compile
or execute D. See the [boundary lesson](../../../content/courses/learning-d/lessons/50-follow-comment-and-string-boundaries.html)
for exact commands, expected output and the envelope scanner’s smaller lexical
contract. Subject-language execution remains to be qualified where D is installed.
