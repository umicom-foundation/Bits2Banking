# Connect, load and observe the Pico activity example

## Identify the board and connections

This lab targets the original non-wireless RP2040 Raspberry Pi Pico. It uses its GPIO-controlled LED and an external momentary button. A GPIO is a general-purpose digital input or output. GPIO names and physical pin numbers are different labels.

Use the board's official pinout to locate **GP15** and a **GND** pin. Disconnect USB power while changing wires. Connect only a button between GP15 and GND. Do not attach external voltage. With a four-leg push button, use its datasheet or an unpowered continuity check to identify legs that connect only when pressed.

~~~text
GP15 ---- momentary button ---- GND
  |
internal pull-up enabled by the firmware
~~~

The pull-up holds the released input high. Pressing the button connects it to ground, so the software converts a low reading into `pressed = true`. The built-in LED requires no extra wire.

The [Pico hardware API reference](https://www.raspberrypi.com/documentation/pico-sdk/hardware.html#hardware_gpio) documents the GPIO operations. This application adds the connection to the existing activity model.

## Load a reviewed firmware file

1. Disconnect the Pico.
2. Hold its BOOTSEL button while connecting USB.
3. Confirm the newly appearing device is the Pico's RPI-RP2 volume.
4. Copy your built `btb-pico-activity.uf2` onto that volume. Verify the destination before copying. No disk formatting is needed.
5. The board restarts into the firmware. Disconnect and reconnect it normally to restart again.

Loading replaces the application currently stored on the board. Keep its original firmware if you need to return to it. The vendor [SDK introduction](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) explains this bootloader workflow.

## Observe the state changes

1. Start with the external button released. The LED begins off.
2. Press and hold it. An accepted rising sample changes the count and LED parity.
3. Keep holding it. A steady high `pressed` value should not keep incrementing.
4. Release, then press again. The next accepted edge changes parity again.
5. Restart the board. The count returns to zero because it was only in RAM.

Do not infer the exact count from the LED: it displays parity, meaning odd or even, not a decimal number. Bounce may produce extra edges, and a press shorter than the sampling interval can be missed. Write down unexpected behaviour rather than treating it as success.

## If the observation differs

No USB volume: check the data cable and BOOTSEL sequence. Build errors: inspect the first compiler diagnostic and confirm the cross compiler and board name. LED changes without pressing: check GP15 wiring and the button's connected pairs with power removed. LED never changes: confirm the non-wireless board and the firmware filename, then inspect the host model cases before changing hardware code.

Physical testing and any switch-filter design remain separate work from the authored source.

