# FAT16 boot sector and volume layout

A filesystem gives names to bytes stored in disk sectors. FAT16 divides a volume into a boot sector, reserved sectors, File Allocation Tables (FATs), a fixed-size root directory, and a data area. Our exercise uses an **image file**: a normal file containing fictional sector bytes, not a physical disk.

## 1. Read the first sector

The initial sector contains a BIOS Parameter Block (BPB). Offsets are counted from zero. Two bytes at offsets 11–12 encode bytes per sector in **little-endian** order: the least-significant byte comes first. Offset 13 stores sectors per cluster. Offsets 14–15 store the number of reserved sectors, 16 stores FAT count, 17–18 store the root-entry count, and 22–23 store sectors per FAT.

The final two bytes of the 512-byte first sector are `55 AA`. This signature is a structural check, not proof that a disk image is safe or that the rest of it uses FAT16.

## 2. Calculate a layout

For 512-byte sectors, 32 root entries require `(32 × 32 + 511) / 512 = 2` sectors. Suppose the volume has one reserved sector, one FAT containing 20 sectors, and 5000 total sectors. The FAT begins at sector 1; the root directory at sector 21; the data area at sector 23. There are 4977 data clusters when each cluster occupies one sector. This is within FAT16's standard cluster-count classification of 4085 to 65524.

## 3. Try the code

Compile and test the [FAT16 inspector laboratory](../../labs/index.md). Examine `BtbFat16Open()` in `fat16.c`. It validates the geometry *before* returning a completed result. Modify the boot-sector signature in a **copy of the test fixture**, rerun inspection, and check that the file is refused.

## 4. Check understanding

Why is the FAT16 label alone insufficient? Why must the parser know both the file length and the sector count? Why is an absolute sector position different from a byte offset?
