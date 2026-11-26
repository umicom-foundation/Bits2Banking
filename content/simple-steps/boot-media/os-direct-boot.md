<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/os-direct-boot.md

PURPOSE:
Collect normal and forced recovery evidence for the same verified OS bundle.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# 6. Boot the OS bundle directly

Direct loading supplies the Linux kernel and initial filesystem to QEMU. This first isolates guest startup from bootloader and optical-drive problems. Use the `$RUN` and `$TOOL` values from the [bundle lesson](os-foundation-bundle.md).

1. Verify the bundle, record its manifest hash and get the x64 emulator version. Use an absolute QEMU path to keep the environment easy to reproduce.

   ~~~bash
   set -eu
   "$TOOL" verify --bundle "$RUN/bundle"
   sha256sum "$RUN/bundle/image.umi"
   QEMU=/usr/bin/qemu-system-x86_64
   "$QEMU" --version
   ~~~

2. Start normal and forced recovery in separately named result directories. If either name has been used, choose a fresh pair. The commands use separate guest sessions and stop automatically.

   ~~~bash
   "$TOOL" boot --bundle "$RUN/bundle" --qemu "$QEMU" \
     --mode normal --result "$RUN/direct-normal" --timeout 90
   "$TOOL" boot --bundle "$RUN/bundle" --qemu "$QEMU" \
     --mode recovery --result "$RUN/direct-recovery" --timeout 90
   cat "$RUN/direct-normal/result.umi" "$RUN/direct-recovery/result.umi"
   ~~~

3. Open both `console.log` files. Normal should complete the two Foundation service checks. Forced recovery should skip those services and report its reason for recovery. Check successful termination in each result. Record failures, timeouts and missing markers as incomplete evidence.

If you built a separate RISC-V Foundation bundle, use that bundle’s `Image`, `qemu-system-riscv64` and the [reviewed OpenSBI workflow](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/installation-and-development.md#check-normal-and-recovery-with-reviewed-opensbi-firmware). The native Kernel exercise has a different firmware entry.

**Check yourself.** Two records can share a bundle identity and still show different startup paths. Keep both results before making an ISO. Direct loading exercises the guest and leaves optical boot and Secure Boot to later checks.

[Previous · Build the bundle](os-foundation-bundle.md) · [Next · Create an optical image](os-optical-iso.md) · [QEMU direct Linux boot](https://www.qemu.org/docs/master/system/linuxboot.html)
