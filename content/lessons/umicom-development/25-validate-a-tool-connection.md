# Validate a tool connection


An editor can ask another program for information about source code. For example, Umicom Studio IDE can use Framework language services to request a definition location or a list of completion suggestions. Before sending document content, the two programs need to establish what messages they understand. This lesson follows that conversation and explains why receiving an answer is different from accepting a valid answer.


Read [Follow protocol message boundaries](22-follow-protocol-message-boundaries.md) for an introduction to bytes and message framing. Read [Close background work safely](10-close-background-work.md) if ownership and cleanup are new. You can trace every example on paper. The complete C23 program is `examples/language_lifecycle/main.c` in Umicom Framework, and it uses an in-memory transport rather than starting an external program.



## 1. Name the parts of the conversation


A **client** asks for a service. A **server** supplies that service. These words describe roles; both programs can run on the same computer. A language server examines source text. An editor acts as its client and presents the results to the person editing a project.


A **transport** carries bytes. A pipe between two local programs is one possible transport. A memory buffer is another, useful for repeatable exercises. A **protocol** gives those bytes meaning: it defines the message format, allowed operations and the order in which they occur. Choosing a transport does not prove that the other program understands the protocol.


Framework keeps these responsibilities separate. `UmiLanguageRuntimeTransport` describes read, write and lifetime callbacks. The server connection owns framing and request tracking. Lifecycle functions coordinate initialization and shutdown. Applications use these shared services instead of maintaining their own slightly different handshakes.



## 2. Pair a reply with its request


A request has an identifier, written as `id`. It works like a reference number: the reply repeats it so the client can find the question being answered. It is not a password, a signature or proof that the peer is trustworthy. The example's first request has identifier 1.




```json
{"jsonrpc":"2.0","id":1,"result":{"capabilities":{"hoverProvider":true}}}
```


Braces enclose an object, which groups named values. A colon separates a name from its value, and a comma separates entries. The value `true` is a boolean: one of the two values true and false. The object under `capabilities` describes services the peer advertises. Here it advertises hover information, which an editor can show when the user points at source text.


The `jsonrpc` value identifies the message format. The `result` member holds a successful answer. A failure uses an `error` member with a numeric code and a text message. A response cannot be both a successful result and an error. Repeating a required field is also ambiguous; two readers might otherwise choose different values.



## 3. Follow the state transitions



<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 820 240" role="img" aria-labelledby="lifecycle-title lifecycle-description" style="width:100%;height:auto"><title id="lifecycle-title">A validated language connection</title><desc id="lifecycle-description">A starting connection sends initialize. A valid capabilities response allows ready state. Shutdown checks a null result and always stops the transport. An invalid initialize response leads to failed state and explicit cleanup.</desc><rect x="10" y="35" width="150" height="65" rx="10" fill="#edf4f7" stroke="#315f72"/><text x="85" y="72" text-anchor="middle" fill="#18363f" font-size="20">Starting</text><path d="M160 68 H300" stroke="#315f72" stroke-width="3"/><text x="230" y="30" text-anchor="middle" fill="#18363f" font-size="15">valid initialize</text><rect x="300" y="35" width="160" height="65" rx="10" fill="#e7f5ec" stroke="#267446"/><text x="380" y="72" text-anchor="middle" fill="#18363f" font-size="20">Ready</text><path d="M460 68 H650" stroke="#315f72" stroke-width="3"/><text x="555" y="30" text-anchor="middle" fill="#18363f" font-size="15">shutdown + cleanup</text><rect x="650" y="35" width="160" height="65" rx="10" fill="#edf4f7" stroke="#315f72"/><text x="730" y="72" text-anchor="middle" fill="#18363f" font-size="20">Stopped</text><path d="M85 100 V180 H300" fill="none" stroke="#a44636" stroke-width="3"/><text x="185" y="164" text-anchor="middle" fill="#18363f" font-size="15">invalid initialize</text><rect x="300" y="145" width="160" height="65" rx="10" fill="#fff0eb" stroke="#a44636"/><text x="380" y="184" text-anchor="middle" fill="#18363f" font-size="20">Failed</text><path d="M460 180 H730 V100" fill="none" stroke="#315f72" stroke-width="3"/><text x="575" y="165" text-anchor="middle" fill="#18363f" font-size="15">explicit stop</text></svg>

A state records where a connection is in its lifetime. Framework begins the handshake only for a starting connection whose workspace matches the requested root. It publishes capabilities only after the reply is valid and the initialized notification has been sent. A refused handshake leaves the caller's previous capability output unchanged and marks the connection failed. The caller still owns that connection and must close it.


Shutdown is different from destroying an object. A normal shutdown asks the peer to finish its protocol work; the separate exit notification asks it to leave. Framework then closes the transport. If the reply is invalid or absent, cleanup still runs. The function returns the protocol failure instead of disguising it as success just because the transport was closed.



## 4. Distinguish values that look similar


The successful shutdown result is JSON `null`. It means that this operation has no result data. It is not `false`, an empty object or the string `"null"`. Those values have different types. Types matter because the receiver needs one precise rule for interpreting a message.




```json
{"jsonrpc":"2.0","id":2,"result":null}
```


The example's second request is shutdown, so its reply uses identifier 2. In the invalid-shutdown scenario, the example supplies `false` instead. The lifecycle function refuses that response, stops the transport and does not send the normal exit notification. The example checks each of those observations separately.


Initialization requires an object under `capabilities`. A peer that sends `"capabilities":null` has not supplied that object. Checking only the identifier would miss this mistake. Framework therefore reuses `UmiLanguageResponseTreeRead` to validate the response and then checks the result shape required by the operation. This boundary does not interpret every possible optional capability extension.



## 5. Track who owns the transport




```c
UmiLanguageRuntimeMemoryTransport *memory = NULL;
UmiLanguageRuntimeTransport transport = {0};
UmiStatus status = umi_language_runtime_memory_transport_create(
    &memory, &transport);
```


The asterisk in a pointer declaration means the variable refers to an object stored elsewhere. `NULL` means it does not yet refer to an object. The ampersand passes the address of a variable so a function can place its result there. The zero initializer gives every field in the transport structure an initial zero value.


After creating the server connection with `umi_language_runtime_server_create_with_transport`, ownership moves only if the function succeeds. The original transport's instance becomes null. The server must then destroy the transport; the caller must not destroy it a second time. The separate `memory` pointer is borrowed for supplying and inspecting bytes while the server remains alive.


Read the example's `finished:` label. Every failure reaches this cleanup point. The code destroys the server if one exists, then destroys an original transport only if ownership never moved. A label is a named position in a function. Here, `goto finished` centralizes cleanup instead of repeating it after every error.



## 6. Keep byte-count arithmetic safe


The memory transport is a finite buffer. It reserves one byte for a terminating zero used when inspecting its output. The number of bytes requested by a caller must fit before a copy begins. Unsigned integers have a maximum value; adding beyond that value wraps around. A test such as `used + count >= capacity` can therefore give the wrong answer if the addition already wrapped.




```c
if (used >= capacity) return UMI_STATUS_INVALID_STATE;
if (count >= capacity - used) return UMI_STATUS_CAPACITY_EXCEEDED;
if (count != 0U) memcpy(destination + used, source, count);
```


This excerpt illustrates the checks in `src/language_runtime/memory_transport.c`; its variable names describe the roles. First prove that the stored length is valid. Subtract it from capacity, then compare the requested count with the remaining space. Only after those checks may the code touch the source bytes. A zero-length operation avoids a copy, allowing a null source for an empty append.


The memory transport does not reclaim consumed input space. It is a bounded replay facility, not a continuously growing message queue. That limit belongs in its public contract so callers can choose a different transport for longer sessions. The native pipe transport has a different storage lifetime.



## 7. Build the small installed-SDK example


First follow [Use an installed Framework SDK](06-use-an-installed-sdk.md). The commands below assume a matching SDK at `C:\umicom\installed\framework` and the Framework checkout under `C:\umicom\Umicom-Applications\framework`. Change those paths if your setup differs. Stop at the first error; later commands cannot repair an unsuccessful configuration or build.




```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
New-Item -ItemType Directory -Force "C:\umicom\_local\logs\learning"
cmake -S ".\examples\language_lifecycle" -B "C:\umicom\_local\learning-build\language-lifecycle" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework 2>&1 | Tee-Object "C:\umicom\_local\logs\learning\language-configure.log"
cmake --build "C:\umicom\_local\learning-build\language-lifecycle" --parallel 2 2>&1 | Tee-Object "C:\umicom\_local\logs\learning\language-build.log"
ctest --test-dir "C:\umicom\_local\learning-build\language-lifecycle" --output-on-failure --no-tests=error --output-log "C:\umicom\_local\logs\learning\language-tests.log"
& "C:\umicom\_local\learning-build\language-lifecycle\umicom-language-lifecycle.exe" invalid-shutdown
```


CMake prepares this example's build directory, and the build command compiles the small consumer against the installed libraries. It does not add the Framework source tree as a subproject. CTest runs three scenarios: valid, invalid-initialize and invalid-shutdown. The final command should report an accepted initialization followed by a refused shutdown reply whose transport cleanup still completed. A zero exit status means the example observed its expected outcome, including expected refusals.


A package-location error means the SDK prefix or cached package selection is wrong. An unresolved symbol can mean the installed archive and headers come from different builds. Reinstall the intended SDK rather than adding source-tree include directories to hide the mismatch. This replay example starts no external language server, opens no editor and proves no real server's compatibility.



## 8. Check your understanding



### A reply has the correct identifier but both result and error. Should it be accepted?

No. Correlation finds the request, while response validation checks whether the answer is meaningful. A contradictory response is refused.




### A shutdown reply is refused, but the child has been closed. Did shutdown succeed?

Cleanup completed, but the protocol exchange failed. Preserve both facts and report the failure instead of turning cleanup into a success claim.




### Why is the memory pointer not freed separately after the server takes ownership?

It refers to the same transport storage now owned by the server. Freeing it separately would leave the server with a stale pointer and could cause a second release.




### Why compare count with capacity minus used?

After proving used is within capacity, subtraction gives a valid remaining-space value. It avoids trusting an addition that may already have wrapped.



[Previous: Find text with shared Framework services](24-find-text-with-shared-services.md) · [Course contents](index.md)


