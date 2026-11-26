<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/physical-readiness.md

PURPOSE:
Determine which evidence is required before a real USB, optical disc or installation is appropriate.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# 11. Decide whether a physical target is ready

Begin with the result from your virtual tests and the official release information for the exact machine and medium. The current Kernel diagnostic and Foundation live exercises place particular limits on what can be claimed. Keep a written decision you can revisit when new evidence arrives.

1. Check the named physical target. Record its architecture, firmware version and intended boot mode. In Windows, open **System Information** to read **System Type**, **BIOS Mode**, and **Secure Boot State**. These fields describe the computer you are looking at. Keep its recovery method and a current backup of anything it stores.
2. Identify the release image and actual medium. For optical media, check the supported BIOS or UEFI catalogue entry. For USB, choose a release image that explicitly supports a removable USB disk and that firmware mode. Compare the downloaded file’s digest with an independently supplied release digest.
3. List every missing observation in a small table. A realistic entry might read “same ISO hash with x64 UEFI in QEMU: reviewed”, “physical optical drive on this system: pending”, and “installation, reboot and recovery: pending”. A different image, firmware build or medium needs its own record.
4. Review the target before a future authorized write. Read the manufacturer, serial, capacity and sector size from the supplied writer's device inventory and compare them to the physical label. A drive letter does not identify a whole disk. Rediscover after reconnecting the device or changing USB ports. When a supported release provides a procedure, follow its target, confirmation and independent readback instructions. Leave every unrelated drive attached to normal operations undisturbed.

Use a spare target approved for the release. The Framework device writer is disabled by default and its available experimental profile is narrow. GPT transfers in that profile require exact target length. The desktop and course examples exercise inspection and ordinary file production. This workshop ends before a physical write, optical burn or firmware policy change. A Foundation guest running from its initial RAM filesystem still needs a separate install workflow and target-specific recovery evidence before anyone can install it as an OS.

**Check yourself.** Name one exact artifact and one target. List what has passed and what is still pending for that combination. If the only observation is a virtual boot, list hardware installation as pending.

[Previous · Rehearse a transfer](inspect-and-copy.md) · [Next · C evidence lab](evidence-lab.md) · [Project media qualification](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/virtual-machines-and-boot-media.md#5-prepare-physical-media-when-a-release-qualifies-it)
