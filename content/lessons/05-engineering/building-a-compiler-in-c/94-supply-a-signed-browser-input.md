<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/94-supply-a-signed-browser-input.md

PURPOSE:
Run one compiled Umicom C artifact with signed input on the CLI and in a browser.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Supply a signed input in a browser worker

[Course contents](index.md)

## Compile the rule once

A parameter is a local variable that receives a value from the caller when a function starts. In `examples/checked-input.uc` from the Umicom C checkout, `input` is a signed 32-bit integer. The function doubles it and adds two on the positive path. Use the same artifact each time you change the input.

~~~c
int umicom_run(int input)
{
    int total = input * 2;
    if (input > 0) {
        total += 2;
    }
    return total;
}
~~~

1. Build Umicom C by following `docs/execution-guide.md` in its checkout. Use a build with `compile-input` and `exec-input` in its help. Stop if a command returns an error you did not expect.
2. Choose a new temporary directory for the exercise. Adjust the executable path below if your build uses a different directory.
3. Compile the supplied function once. Then run it with both a positive and a negative input.

~~~powershell
Set-Location 'C:/umicom/umicom-c'
$tool = (Resolve-Path './build/bin/umicom-c.exe').Path
$practice = New-Item -ItemType Directory -Path (Join-Path $env:TEMP ('umicom-input-' + [guid]::NewGuid()))
$artifact = Join-Path $practice.FullName 'checked-input.umcb'
& $tool compile-input './examples/checked-input.uc' $artifact
& $tool exec-input $artifact 20 --max-steps 64
& $tool exec-input $artifact -5 --max-steps 64
~~~

| Input | Result | Instructions executed |
| --- | --- | --- |
| `20` | `42` | `16` |
| `-5` | `-10` | `12` |
| `0` | `0` | `12` |
| `1073741822` | `2147483646` | `16` |
| `-1073741824` | `-2147483648` | `12` |

The positive path includes the addition and so uses extra instructions. Fuel is a limit on the number of VM instructions. Try a limit of one to see an unfinished run refused. Changing the limit does not change the artifact.

## Compare with the same source as native C

The Bits2Banking lab `labs/languages/umicom-c-project/compare-int-input.c` calls `umicom_run` through a normal native function call. Build it with the same `.uc` source. The GCC option `-x c` treats the source with the `.uc` extension as C. This comparison requires a compiler whose `int` is signed and 32 bits wide.

~~~powershell
$native = Join-Path $practice.FullName 'compare-int-input.exe'
$driver = 'C:/umicom/Umicom-Bits2Banking/labs/languages/umicom-c-project/compare-int-input.c'
& 'C:/msys64/ucrt64/bin/gcc.exe' -std=c23 -x c './examples/checked-input.uc' $driver -o $native
& $native 20
& $native -1073741824
~~~

The host admits only inputs for which the native calculation fits. Native C signed overflow has undefined behavior, so deliberately running the overflowing function is an invalid comparison. Try `1073741823` in the VM to see its checked arithmetic refusal. Try `2147483648` to see the separate input range refusal.

## Send the same bytes to the browser worker

Follow `docs/browser-arithmetic.md` in the Umicom C checkout to serve a practice page over local HTTP. Keep the `browser` directory next to the page module and copy `checked-input.umcb` beside it. A worker is a separate browser thread. This one reads Umicom bytecode through its JavaScript interpreter, using the `int-input` profile to supply the parameter.

~~~javascript
const worker = new Worker(new URL("./browser/worker.mjs", import.meta.url), {
    type: "module",
});
worker.addEventListener("message", ({data}) => {
    console.log(data);
    worker.terminate();
}, {once: true});
const response = await fetch("./checked-input.umcb");
if (!response.ok) throw new Error("Could not read the practice artifact");
const artifact = await response.arrayBuffer();
worker.postMessage({id: 1, profile: "int-input", input: 20, artifact, fuel: 64}, [artifact]);
~~~

Expect `ok: true`, `value: 42` and `instructions: 16`. The transfer gives the worker ownership of the buffer. Fetch it again before sending `-5`, or transfer a fresh copy. Keep the page, worker and artifact on the same origin, which means the same scheme, host and port. Serve `.mjs` as JavaScript if the browser refuses to load the module.

An optional Framework loopback preview accepts the same artifact at `/api/cvm/preview-int?input=20` when the local toolchain demonstration is enabled. Use the instructions in the Framework local web service lesson to start it. That endpoint runs the native VM on the server. The worker exercise runs the interpreter inside the browser.

## Follow the parameter into the VM

Read byte 5 with `([IO.File]::ReadAllBytes($artifact))[5]`. The example stores an input flag there. The first instructions are `PUSH 0` and `STORE_LOCAL 0`. After the host validates the artifact and those instructions, it substitutes the signed value in its copy of the first operand. The file remains reusable. The existing VM sees local slot zero initialized before the function body reads it.

Try the ordinary `exec` command with this artifact and check the refusal. A host that does not know how to supply the parameter cannot interpret the placeholder as the user's value. Repeat a successful `exec-input` run and take a second SHA-256 digest of the artifact. The two digests should match. This lesson covers one signed parameter and a bounded computation in Umicom's bytecode format.

[Previous lesson on Boolean words](93-lower-boolean-words-without-changing-the-vm.md)
