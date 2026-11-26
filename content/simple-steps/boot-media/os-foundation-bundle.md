<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/os-foundation-bundle.md

PURPOSE:
Prepare and verify the x64 Linux-based Umicom OS Foundation bundle.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# 5. Build and verify an OS Foundation bundle

Use a Linux or WSL terminal with the prerequisites in the [OS development guide](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/installation-and-development.md). Keep the build outputs on a Linux filesystem you own. The OS host application installed on Windows has a different launch path.

1. Select the reviewed OS and primary Framework checkouts. Build the native image tool in a fresh directory. The PowerShell tool paths from the earlier Kernel exercises belong to the Windows host.

   ~~~bash
   set -eu
   OS=/mnt/c/umicom/umicomOS
   FW=/mnt/c/umicom/Umicom-Applications/framework
   STAMP=$(date -u +%Y%m%dT%H%M%SZ)
   mkdir -p "$HOME/umicom-builds"
   BUILD="$HOME/umicom-builds/image-tool-$STAMP"
   cmake -S "$OS/tools/os-image" -B "$BUILD" -G Ninja \
     -DCMAKE_BUILD_TYPE=Release -DUMICOM_OS_FRAMEWORK_SOURCE="$FW"
   cmake --build "$BUILD" --parallel 2
   ctest --test-dir "$BUILD" --output-on-failure --no-tests=error
   TOOL="$BUILD/bin/umicom-os-image"
   "$TOOL" profile --file "$OS/image/native/profile.umi"
   ~~~

   Save the Buildroot commit, kernel version and archive digest printed by the selected profile. A profile describes the inputs you must use.

2. Read the [pinned Buildroot preparation instructions](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/native-image-workflow.md). Enter your dedicated clean Buildroot checkout. Compare its commit to the profile and confirm that `git status --short` prints nothing. Prepare the x64 recipe in a new workspace only after those checks agree.

   ~~~bash
   read -r -p 'Absolute path to your reviewed Buildroot checkout: ' BR
   git -C "$BR" rev-parse HEAD
   git -C "$BR" status --short
   ~~~

   ~~~bash
   RUN="$HOME/umicom-builds/os-x64-$STAMP"
   "$TOOL" prepare --os "$OS" --framework "$FW" --buildroot "$BR" \
     --output "$RUN" --arch x86_64 --git /usr/bin/git
   "$TOOL" configure --output "$RUN" --make /usr/bin/make
   "$TOOL" build --output "$RUN" --make /usr/bin/make --jobs 2
   "$TOOL" pack --output "$RUN" --bundle "$RUN/bundle"
   "$TOOL" verify --bundle "$RUN/bundle"
   ~~~

3. Review the four produced files. Save digests of `bzImage`, the initial filesystem, and both manifests. Keep these inputs together for the direct, optical and disk-image lessons.

   ~~~bash
   sha256sum "$RUN/bundle/bzImage" "$RUN/bundle/umicom-rootfs.cpio.gz" \
     "$RUN/bundle/input-manifest.umi" "$RUN/bundle/image.umi"
   ~~~

If preparation reports a changed input or an occupied destination, leave the attempted workspace available for review. Confirm the checkout identity and use a new workspace. A tool build or bundle verification can succeed before you attempt any guest boot.

**Check yourself.** The x64 kernel is named `bzImage` and its matching initial filesystem is `umicom-rootfs.cpio.gz`. A separate RISC-V run uses `--arch riscv64`, a fresh output directory and produces `Image` in place of `bzImage`.

[Previous · Kernel diagnostic ISO](kernel-diagnostic-iso.md) · [Next · Direct VM boot](os-direct-boot.md) · [Buildroot host requirements](https://buildroot.org/downloads/manual/manual.html#requirement)
