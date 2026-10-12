# Episode 44 — What happens when you press Save?

**Duration:** approximately 12–16 minutes  
**Companion lessons:** [132](../../lessons/05-engineering/132-from-device-sectors-to-filesystems.md), [133](../../lessons/05-engineering/133-build-a-writeback-sector-store.md)  
**Demonstration:** `labs/native/writeback-sector-store`  
**Reference:** [Umicom Kernel writable VirtIO guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/WRITABLE_VIRTIO_BLOCK.md)

## Opening: a saved note is more than bytes (0:00–1:20)

**On screen:** Umicom Notes mock-up showing the sentence “Keep a record of the budget approved by the class.” The cursor clicks Save. Fade to a diagram labelled Application → Filesystem → Block driver → Storage device.

**Narration:**

“When you press Save, something interesting happens. The words are already visible on your screen. They are already held somewhere in the computer's memory. But are they safely stored for tomorrow? To answer that, we have to look beneath the application's window. The file has a name. The operating system must find that name and the filesystem must work out which storage regions belong to it. The block device does not know that it is saving a note. It only understands operations on numbered sectors. Today we will build a small C program that makes the distinction visible. We will see a Save appear to work and then deliberately make its bytes disappear in a simulated restart.”

**Demonstration:** Point to one step at a time in the diagram. Do not animate all arrows at once.

## Part 1: find a byte (1:20–3:20)

**On screen:** Four columns labelled sector 0, 1, 2, 3. Each column contains 512 byte slots.

**Narration:**

“Imagine a very small storage device with four sectors. Each sector is 512 bytes. In total, that gives us 2048 bytes, just enough for a teaching exercise. Sector zero begins at byte zero. Sector one begins at byte 512. Sector two begins at byte 1024. Sector three begins at byte 1536. We compute those offsets by multiplying the sector number by the sector size. In a real storage driver, we must check the device's capacity and make sure the multiplication cannot overflow. A large number must never become permission to access memory outside the device.”

“Now notice what this picture does not contain: there is no filename, directory or student account. Those belong to the filesystem layer above the block device. A filesystem maps names and file offsets to stored bytes. That separation means the Notes application can use different storage devices without writing a new block driver for each one.”

**Pause and ask:** “Where does sector nine start on a device using 512-byte sectors?” Display `9 × 512 = 4608` after a short pause.

## Part 2: two copies of one sector (3:20–5:45)

**On screen:** Show [the write-back diagram](../../assets/diagrams/writeback-cache-and-flush.svg). Highlight the orange staged copy and the teal stable copy. Open `block_store.h` beside it.

**Narration:**

“Our laboratory keeps two copies of every sector. One is called staged and one is called stable. We also keep a small dirty flag. Whenever our program changes a sector, we copy the complete 512 bytes into staged storage and mark that sector dirty. Reading the current value returns the staged copy. Reading the stable value returns the last flushed copy. In a real computer both of these arrays would reside in ordinary RAM, so this is a model rather than a persistence mechanism. We define the stable copy as the state that our simulated crash will preserve.”

“Look closely at the function signature. It takes a pointer to the storage owner, a sector number and a pointer to the bytes to write. A valid sector number is zero through three. The code checks the number before indexing the array. This is one of the most important habits in C: validate first, then access memory.”

**On screen:** Walk through `BtbStorageStage()`. Point out the full-sector copy and the dirty flag. Then read the two copies.

## Part 3: flush is a separate operation (5:45–8:20)

**Narration:**

“Staging is not flushing. Flushing means asking the lower layer to move accepted changes towards its stable storage boundary. In this laboratory, `BtbStorageFlush()` copies dirty sectors into the stable array. We can allow it to process all sectors, or deliberately stop it after a limited number. If two sectors are dirty and we permit only one to reach the stable copy, the result must say incomplete. Pretending that both were saved would be incorrect.”

“In a real system, what a successful flush guarantees depends on the device protocol, the controller, its write cache and the storage medium. A C library `fflush()` is not a magic power-loss guarantee. For now, we use a deterministic simulation so that we can inspect which state survives.”

**Demonstration:** Build the laboratory, run the tests, then run the example using these commands:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\writeback-sector-store" -B ".\output\learning-build\writeback-sector-store" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\writeback-sector-store" --parallel 2
ctest --test-dir ".\output\learning-build\writeback-sector-store" --output-on-failure
& ".\output\learning-build\writeback-sector-store\btb-sector-store-demo.exe"
```

**On screen:** Highlight the line that says stable storage is empty before the flush, followed by the restored note after flush and simulated restart.

## Part 4: deliberately interrupt the save (8:20–10:50)

**Narration:**

“Now try something more revealing. The tests stage two different sectors. We then allow one sector to flush but not the other. A restart discards the unflushed bytes. This is not a programming trick. It illustrates a question that every real storage system must answer: if a multi-part update is interrupted, how do we know which parts actually reached storage?”

“Consider a filesystem writing a new file body and a new file length. If one reaches storage without the other, the metadata and file contents may disagree. This is why filesystems need explicit ordering and recovery rules. In our next episode, we will build a small journal that records an accepted Notes update before applying it to the main copy.”

**Demonstration:** Open the unit test. Identify where `BtbStorageFlush(&store, 1U, ...)` produces an incomplete result. Walk through the assertions after `BtbStorageCrash()`. Do not modify the student's files during filming unless the changes are clearly shown and restored.

## Closing and next exercise (10:50–12:45)

**Narration:**

“We started with a simple Save button and discovered several independent contracts. The document service decides which note to save. The filesystem owns the filename and data layout. The block driver submits numbered requests. The device reports completion and may need an additional flush to establish stable storage. The words 'accepted', 'completed' and 'durable' are not interchangeable.”

“For practice, change the test's flush budget to zero. Before running anything, predict the number of sectors that will survive the simulated crash. Then restore the test and run it again. A useful engineer can explain the expected outcome before reading the output.”

“The lesson and complete source code are available on the Bits2Banking website and in the Umicom Foundation's Bits2Banking repository. Next time, we will build a journal that can recover an accepted note after a carefully timed interruption. Our goal is to understand the real mechanisms, one tested step at a time, and then use that knowledge to help others learn.”
