# Framework HTTP contract laboratory

Study HTTP messages without opening a network port. Four small C programs use the installed **Umicom::web** library. Framing, routing and response serialization remain Framework responsibilities. The memory transport is a teaching adapter, not a second HTTP implementation.

## Prepare the workspace

Install a matching Framework SDK with its web component first. Read [Learning Umicom Framework](../../../content/lessons/umicom-development/index.md) for the SDK workflow. Use the same compiler family and architecture for the SDK and this lab.

In PowerShell, from the Bits2Banking checkout:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/framework-http-contracts -B build/http-contracts -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/applications -DBUILD_TESTING=ON
cmake --build build/http-contracts --parallel 2
ctest --test-dir build/http-contracts --output-on-failure --no-tests=error
& ".\build\http-contracts\btb-http-framing.exe"
```

Stop if a command fails. The prefix is an example: substitute the actual SDK installation containing UmicomFrameworkConfig.cmake.

In Bash, from the same repository:

```bash
cmake -S labs/native/framework-http-contracts -B build/http-contracts -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom-sdk" -DBUILD_TESTING=ON
cmake --build build/http-contracts --parallel 2
ctest --test-dir build/http-contracts --output-on-failure --no-tests=error
./build/http-contracts/btb-http-framing
```

Four registered tests are expected. These commands and expectations are authored exercises; they are not evidence of an executed run.

## Read the programs in order

| Program | Main question | Expected observation |
| --- | --- | --- |
| framing.c | How many bytes make one request? | A missing body byte is BUSY; A, NUL, B has length three; duplicate lengths fail |
| response.c | How is a HEAD reply different? | Same declared body length, five fewer transmitted bytes |
| routes.c | Which function owns /health? | One exact match calls the handler; /missing produces 404 without another call |
| exchange.c | What if reads/writes are short? | Framework accumulates them; a failed write can follow a completed handler |

The CHECK-style macro reports an expression and source line. It remains active in release builds, unlike standard assert when NDEBUG is defined.

## Recover from problems

A package-not-found error means the prefix, installation or selected component needs attention. Do not copy Framework source files into this lab. An undefined symbol may mean the SDK was built before the matching public header implementation.

A failed assertion is useful evidence: preserve the exact source revision, compiler, SDK prefix and output. Do not change a required result just to make the command green.

## Extend the experiment

Add one case at a time: a missing Host, an incomplete header, a HEAD route or a cancellation token. Predict whether a handler should run before compiling.

No listener, TLS, login, persistent store or real browser is involved. Follow the existing Framework local-service example for the next network step.
