# Local order lifecycle laboratory

An order is a request to trade. Acceptance means that this local adapter retained the request; it does not mean that an exchange executed it. This C23 program uses synthetic identifiers and Umicom Framework's simulated broker. It never connects to an account, sends an order over a network or produces a real fill.

## Prepare your tools

Install a C23 compiler, CMake 3.26 or later and Ninja. Install a matching Umicom Framework SDK containing the trading component and the current simulated-broker validation. An SDK is a set of headers, libraries and package files used to build another program. Use the compiler and architecture that match that SDK.

On Windows, open PowerShell and enter each command separately. Adjust the SDK location to your installation. Stop when a command reports an error.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\order-lifecycle"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
& ".\build\btb-order-lifecycle.exe"
~~~

On Linux or macOS, open a terminal in this laboratory directory and use a matching native SDK.

~~~bash
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom-sdk" -DBUILD_TESTING=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
./build/btb-order-lifecycle
~~~

The first command writes build instructions; the second compiles the program; the third runs its checks; the fourth starts the same program directly. A missing package indicates an incorrect SDK prefix or absent trading component. An undefined symbol often means headers and libraries came from different SDK revisions. Repair the installation instead of copying isolated headers.

## Expected output

~~~text
Accepted local request; revision 1. No fill has occurred.
Duplicate identifier refused; one order remains.
Cancelled local request; revision 2. Repeated cancellation changes nothing.
Local session reset. No broker account or network was used.
~~~

## Follow the program

1. The three zero initializers create known storage, a callback table and a request. The caller owns their lifetime.
2. Literal copies fill identifiers and include their terminating zero byte. These are fixed lesson strings, not a method for accepting arbitrary user input.
3. The request selects a side, limit order type, day duration, quantity, price and simulation mode. These names are enums: a finite set of declared choices.
4. The create function fills the broker table. Calling its connect member chooses the local simulation mode. The instance pointer identifies this storage.
5. Submission validates the request, checks the mode and adds one order. Finding it returns a borrowed pointer into the book. The pointer does not own or free that memory.
6. Submitting the same identifier is refused. Cancellation advances revision one to two; repeating it succeeds without advancing again.
7. Destruction resets the book. The program clears its borrowed pointer before the reset and does not use it again.

## Try a controlled change

Set quantity to zero and run again. The acceptance check should fail, because a valid request requires a positive finite quantity. Restore it to 2.0. Next, change only the request environment to paper while keeping the connection in simulation: submission should be refused. Changing the enum cannot connect this adapter to a broker's paper account; this provider is entirely local.

For each experiment record the changed line, expected result, observed result and executable revision. Do not change a check to accept an unexplained failure. Continue with [the trading course](../../../content/courses/framework-and-finance/trading-and-posttrade/index.html).
