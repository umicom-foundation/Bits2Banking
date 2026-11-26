<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/os-optical-iso.md

PURPOSE:
Stage a verified x64 OS bundle and produce an optical ISO using native Linux tools.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# 7. Create an OS optical image

Use the reviewed x64 Foundation bundle. Build or locate the native Linux Setup Centre console, `grub-mkrescue` and `xorriso`. The installed GRUB tooling determines which firmware entries the ISO can provide. The Windows CLI can inspect images but the ISO-producing implementation here requires Linux.

1. In the Linux terminal from the [bundle lesson](os-foundation-bundle.md), build the native console with its process adapter. Check the command list before selecting the producer.

   ~~~bash
   set -eu
   SETUP_BUILD="$RUN/setup-centre-tools"
   cmake -S "$OS/tools/setup-centre" -B "$SETUP_BUILD" -G Ninja \
     -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF \
     -DUMICOM_SETUP_CANONICAL_PROCESS=ON -DUMICOM_OS_FRAMEWORK_SOURCE="$FW"
   cmake --build "$SETUP_BUILD" --target umicom-setup --parallel 2
   SETUP="$SETUP_BUILD/bin/umicom-setup"
   "$SETUP" --help
   ~~~

   Expect `media-stage` and `media-iso`. Select absolute paths for both your trusted GRUB producer and the comparison tool. These paths are common locations on Linux.

2. Stage the verified inputs and produce the ISO in a different new directory. Use directory paths for both `--output` arguments.

   ~~~bash
   "$TOOL" verify --bundle "$RUN/bundle"
   "$SETUP" media-stage --kernel "$RUN/bundle/bzImage" \
     --initrd "$RUN/bundle/umicom-rootfs.cpio.gz" --output "$RUN/media-stage"
   "$SETUP" media-iso --prepared "$RUN/media-stage" \
     --grub /usr/bin/grub-mkrescue --output "$RUN/media-iso"
   ISO="$RUN/media-iso/UmicomOS.iso"
   sha256sum "$ISO"
   ~~~

3. Compare the three files stored in the ISO to the independently selected kernel, archive and staged GRUB menu. The comparison reads files and leaves the ISO unchanged.

   ~~~bash
   digest_before=$(sha256sum < "$ISO")
   bash "$OS/.github/scripts/verify-optical-payload.sh" /usr/bin/xorriso "$ISO" \
     "$RUN/bundle/bzImage" "$RUN/bundle/umicom-rootfs.cpio.gz" \
     "$RUN/media-stage/tree/boot/grub/grub.cfg"
   test "$(sha256sum < "$ISO")" = "$digest_before"
   ~~~

   Check for matching `/boot/kernel`, `/boot/initrd` and `/boot/grub/grub.cfg`. Keep the staging receipt, producer log and ISO hash together. If the producer reports an unavailable module, compare the installed GRUB modules to the intended boot mode before retrying in an unused directory.

**Check yourself.** You have an optical candidate identified by its hash and three matched inner files. A matching payload leaves the firmware boot question open.

[Previous · Direct boot](os-direct-boot.md) · [Next · Test a virtual optical boot](os-optical-vm.md) · [OS optical workflow](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/virtual-machines-and-boot-media.md#3-prepare-an-x86-64-optical-test-image)
