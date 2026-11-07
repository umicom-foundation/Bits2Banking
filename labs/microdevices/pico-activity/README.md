# A Framework contract on a microdevice

This optional project reads a button on a non-wireless Raspberry Pi Pico. Each accepted sampled press advances the same C model used by the desktop, browser and mobile activity examples. Odd counts light the board LED; even counts turn it off. The limit remains 1,000.

Only Framework status declarations are needed by this small model. This does not establish that the full Framework desktop runtime runs on the board. The firmware and physical wiring have not yet been qualified.

## Prepare the tools

1. Install Git, CMake 3.24 or newer, Ninja and an Arm embedded GCC toolchain that supports C23. The executable is named `arm-none-eabi-gcc`; a Windows desktop GCC cannot produce this firmware.
2. Follow the [Pico SDK setup guide](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html) to obtain the SDK and its required submodules. Record its revision and your tool versions. The SDK has its own dependencies; this project does not download them during configuration.
3. Keep the Bits2Banking and Framework source checkouts available. Read [wiring and recovery](WIRING.md) before attaching a button.
4. In a new terminal, check `arm-none-eabi-gcc --version`, `cmake --version` and `ninja --version`. A command-not-found message means the tool's bin folder is not on that terminal's PATH.

## Configure and build

From the Bits2Banking repository root, use a new build directory. Replace the two dependency paths with your actual folders.

PowerShell:

~~~powershell
cmake -S labs/microdevices/pico-activity -B build/pico-activity -G Ninja -DPICO_BOARD=pico -DPICO_SDK_PATH=C:/Dev/pico-sdk -DUMICOM_FRAMEWORK_ROOT=C:/umicom/Umicom-Applications/framework
cmake --build build/pico-activity --parallel 2
~~~

Bash:

~~~bash
cmake -S labs/microdevices/pico-activity -B build/pico-activity -G Ninja -DPICO_BOARD=pico -DPICO_SDK_PATH="$HOME/dev/pico-sdk" -DUMICOM_FRAMEWORK_ROOT="$HOME/dev/umicom-framework"
cmake --build build/pico-activity --parallel 2
~~~

Stop if either command fails. Expected output includes `build/pico-activity/btb-pico-activity.uf2`. A UF2 is a firmware transfer format, not a program to double-click on Windows. CMake also retains an ELF for debugging.

For a compiler that rejects C23, install a compatible cross compiler and configure a fresh build directory. Do not link a Windows Framework archive into the firmware to bypass a missing header.

## Review before loading

Read the three C files listed by CMake. The board code owns GPIO access. The button adapter remembers whether the last sample was pressed. The activity model validates the count before updating it. Its host cases live in [activity-adapters](../../native/activity-adapters/README.md); passing those cases would still leave board wiring and timing to check.

Use the loading and observation steps in WIRING.md. One physical press can bounce into several electrical transitions. The example demonstrates sampling and ownership, so it deliberately does not promise one count for each physical press. A production input needs a separately specified and tested filtering policy.

## Record the experiment

Keep board model, SDK revision, compiler version, source revision, firmware digest, wiring and observations together. Reset clears the RAM count. No filesystem, network connection or credential storage is used.

