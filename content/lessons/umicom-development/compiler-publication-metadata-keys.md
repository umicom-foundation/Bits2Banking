![Umicom](../../assets/branding/umicom-logo.svg)

# Distinguish request identity from artifact freshness

## Start with the question a key can answer

A build cache associates a key with an artifact, such as an object file. The key should change when relevant input changes. However, a key is only as complete as the data supplied to its construction. Framework’s compiler request key describes request metadata. It does not read a source file, inspect an included header or identify the installed compiler binary. Understanding this boundary prevents a quick metadata lookup from becoming an unsupported claim that an old executable is safe to reuse.



Read Keys in the companion C laboratory. It constructs a request through the installed Framework service, changes one field at a time and compares the resulting identities. No driver is launched. Begin with the same request values in both owners so each observation isolates the field under discussion.



## Keep collection roles in the identity

~~~c
changed = request;
umi_compiler_request_add_include(&changed, "shared");
uint64_t include_key = umi_compiler_request_hash(&changed);
changed = request;
umi_compiler_request_add_definition(&changed, "shared");
uint64_t definition_key = umi_compiler_request_hash(&changed);
~~~



The complete laboratory checks each returned status before using the value. The string shared has different meaning as an include directory and as a definition. A serialization that merely concatenates all option strings can lose that distinction. Framework includes collection names and counts, preserves their order and encodes scalar values explicitly. Working directory, debug information and other request flags also contribute.



Unused array slots and bytes after a string terminator are not active metadata. Hashing structure padding would introduce unrelated object representation into identity. Conversely, an excessive public count or an unterminated active field is refused before traversal. The zero result identifies malformed storage; it is not a valid cache key.



## Choose additional evidence for reuse

A nonzero key remains non-cryptographic and can collide. A source file can change while its path and command stay identical. A compiler upgrade can also change output without changing this request. A production reuse decision therefore needs content and dependency identities, the selected toolchain and environment, and an artifact verification policy. A valid flag supplied by a caller is not a filesystem observation.



## Practice

Draw two columns headed metadata identity and reuse evidence. Place working directory, source digest, driver version, include-directory order and object-file existence in the appropriate column. Then explain what happens when a header changes without a command-line change. Run the keys scenario only after SDK qualification and report the limited observations it prints; do not label the artifact current from that result.



## Source and practice

[Compiler publication laboratory](../../../labs/native/framework-compiler-publication/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-publication-metadata-keys.html)

[Previous lesson](compiler-preview-qualification.md) · [Next lesson](compiler-publication-centre.md) · [Course index](index.md)

Sammy Hegab · Umicom Foundation · MIT
