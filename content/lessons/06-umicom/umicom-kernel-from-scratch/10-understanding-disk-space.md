# Understand how the Kernel counts disk space

A file's length and the storage reserved for it are different quantities. Follow the Kernel's real allocation query to see why.

Before choosing a disk slot, use the guest's `disks` command. It lists transport identities. The guide explicitly attaches the synthetic fixture to slot zero; an empty slot is not evidence that the filesystem bytes are damaged.

## 1. Start with bytes, sectors and clusters

A **byte** is a small unit of stored information. A plain English letter in a UTF-8 text file often occupies one byte; other characters can occupy several. A **sector** is a fixed-size block that this disk interface reads. The current teaching image uses 512 bytes per sector. A **cluster** is a group of sectors that the filesystem allocates together.

A **filesystem** records names, file lengths and which storage belongs to files. FAT16 is one particular format. Its File Allocation Table stores a two-byte entry for each cluster. The entry can say free, link to another cluster, end of a chain, or bad. A bad cluster is marked unavailable; it does not contain a usable allocation promise.

 <svg viewbox="0 0 700 110" role="img" aria-label="The device reads sectors; the filesystem groups sectors into allocation units." style="width:100%;max-width:700px"><title>The device reads sectors; the filesystem groups sectors into allocation units.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">512-byte sectors</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Clusters of sectors</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Files use clusters</text></svg>

The device reads sectors; the filesystem groups sectors into allocation units.

## 2. Work through an example on paper

Suppose each cluster has one 512-byte sector. A 700-byte file needs two clusters. Two clusters reserve 1,024 bytes, so 324 reserved bytes are beyond the file's current length. This unused tail is often called **slack**. Another file cannot simply claim that tail as its own cluster.

| Quantity | Calculation | Result |
| --- | --- | --- |
| File length | Actual content | 700 bytes |
| Clusters required | Round 700 / 512 upward | 2 |
| Allocated space | 2 × 512 | 1,024 bytes |
| Slack | 1,024 − 700 | 324 bytes |

Try the same calculation for a 1,300-byte file. It needs three 512-byte clusters: 1,536 allocated bytes and 236 bytes of slack. Notice that none of these calculations counts directory entries or the allocation tables themselves.

## 3. Follow the actual Umicom result

Open [the allocation result declaration](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/fat16_space.h). A **structure** groups related values under one type. `UmicomKernelFat16Space` keeps four cluster counts and their byte totals. Its fields are independent values, not pointers into a device buffer.

```text
totalClusters = freeClusters + allocatedClusters + badClusters
dataBytes     = totalClusters * clusterBytes
freeBytes     = freeClusters * clusterBytes
```

`allocatedClusters` includes entries containing a valid next-cluster number or an end marker. It does not prove that a directory actually owns each of those clusters. Keep the arithmetic question separate from the ownership question.

## 4. Read the real algorithm in order

1. Open [`kernel/fat16_space.inc`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/fat16_space.inc). It is included by `fat16_inspector.c` so it can reuse the existing parser's boundary and read-budget checks.
2. Find `UmicomFatBegin`. It marks the inspector busy so a callback cannot start a second scan inside the first one.
3. Find `UmicomFatPlanGeometry`. Geometry means the sizes and locations that describe the volume. A damaged size must be rejected before it is used to locate data.
4. Follow the outer sector loop. It reads corresponding sectors from both table copies and compares all their bytes.
5. Follow the inner entry loop. It ignores reserved entries zero and one as data clusters, then classifies each usable cluster.
6. Find `UmicomFatCopy(output, &staged, sizeof(staged))`. This publishes the result only after every required read and check succeeded.

A **callback** is a function supplied by the caller. Here it reads one sector into a buffer. The parser decides what the bytes mean; the callback does not supply the expected answer.

## 5. Interpret a real fixture result

The repository's synthetic image contains 12,159 data clusters of 512 bytes each. Six are allocated, 12,153 are free and none are marked bad. These are properties of this teaching image, not a prediction about your computer.

```text
12,159 × 512 = 6,225,408 data bytes
12,153 × 512 = 6,222,336 free bytes
     6 × 512 =     3,072 allocated bytes
```

The image file is larger because it also contains partition metadata, both tables, the root directory and unused space outside this volume. A volume's data capacity is not the same as the host image file's length.

## 6. Connect the result to the console

After preparing the Kernel using its [allocation guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FAT16_SPACE_GUIDE.md), the guest command is `fatspace 0 0`. The first zero selects a device slot; the second selects a primary partition. These coordinates are not Windows drive letters. The guide attaches the provided synthetic image read-only.

No installation is needed to complete the paper and source-reading exercises. Do not attach a physical disk for these lessons.

## Check your understanding

<details>

<summary>Is a 700-byte file guaranteed to occupy exactly 700 disk bytes?</summary>

No. With 512-byte clusters its data allocation needs two clusters, or 1,024 bytes. Metadata takes additional space.

</details>

<details>

<summary>Can the reported free bytes guarantee that the next file creation will succeed?</summary>

No. Permissions, directory capacity, supported operation limits, another writer or a device failure can prevent creation. The query does not reserve clusters.

</details>

Next, learn why a failed read must leave a result unchanged and why matching tables cannot prove every file is correct.

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/10-understanding-disk-space.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: Check what a native program needs](09-program-requirements.md)

[Next: Test storage boundaries without changing a disk](11-testing-storage-boundaries.md)
