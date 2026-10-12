# Follow a FAT cluster chain

A cluster is a contiguous group of sectors allocated together. A directory entry stores the starting cluster for a file. The File Allocation Table records the next cluster, or an end-of-chain marker.

## 1. Trace a file

Our fixture uses cluster 2 → cluster 3 → `0xFFFF`. The program reads the next 16-bit value from the FAT at `fatStart * bytesPerSector + cluster * 2`. For cluster 2 in a FAT starting at byte 512, this is byte 516.

## 2. Recognise unsafe chains

A chain can loop, point outside the data area, terminate early, or contain the bad-cluster marker `0xFFF7`. A robust reader never follows a cluster address until it has validated the number and checked its byte span. The laboratory stores the visited cluster numbers in a bounded output array and rejects a repeated cluster.

## 3. Try it

Change the test fixture so cluster 3 points back to cluster 2. The test demonstrates that the parser returns `BTB_FAT_CHAIN` instead of looping forever. Restore the end-of-chain marker and run the test again.

## 4. Where this leads

Real filesystems must also validate file length, directory entry ownership, shared allocation, timestamps, backup metadata and crash consistency. A valid chain alone is not a safe filesystem.
