<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/51-record-a-device-observation.md

PURPOSE:
Explain the lesson: Record a device observation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Record a device observation

A useful hardware observation explains what was connected, what firmware ran and what the observer saw. Without those details, another learner cannot distinguish a software change from a different board or wiring arrangement.

## Setup recap

Use the original non-wireless RP2040 Pico described in WIRING.md. Read the pin instructions before connecting anything. Disconnect power while changing the button wiring. The laboratory uses GP15 and a ground pin and requires no external voltage source.

## 1. Identify the firmware

Record the source revision, compiler version, SDK revision and board setting. Keep the build output associated with those values. When copying a UF2 file, verify that the destination is the board's bootloader volume.

Loading firmware replaces the previous application on that board. Keep any firmware you need to restore before beginning the exercise.

## 2. Observe a small sequence

After startup, the model begins at zero and the LED should be off. Press and release the button once. Observe the LED. Repeat and record the result of each press.

Do not infer the full count from one LED observation. Off could describe zero, two or another even count. The interface deliberately exposes only parity.

## 3. Record unexpected behavior

Useful notes include whether the button was held, whether the LED flickered, whether the board restarted and which physical pins were used. A photo of the unpowered wiring can help review the connection.

A host test result, a successful compiler exit and a physical observation belong in separate fields. Each answers a different question.

## Exercise and recovery

Prepare a three-column table: action, expected observation and actual observation. Leave the last column blank until the action is performed. Include startup, a held press, release, another press and power cycling.

If startup does not match, check that the intended firmware was copied and that the board is the supported model. If only press counting differs, investigate wiring and contact bounce. If the device becomes unresponsive, follow the board's documented BOOTSEL recovery rather than formatting an arbitrary drive.

This example does not persist progress. After power cycling, beginning again at zero is expected behavior.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/microdevices/pico-activity/WIRING.md). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](50-read-a-button-as-a-sampled-signal.md)


[Next: Use an SDK service without copying it](52-use-an-sdk-service-without-copying-it.md)
