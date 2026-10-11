# Episode 18 — Who owns the memory? Pointers and arenas

**Length:** approximately 12–16 minutes. **Demonstration:** the C23 Arena Allocator laboratory. **Related chapters:** [67](../../lessons/03-native-code/67-pointers-and-borrowed-memory.md) and [68](../../lessons/03-native-code/68-arenas-and-checkpoints.md).

## Opening — the problem (0:00–2:00)

**Narration:**

“When we open a document in Umicom Notes, the application must remember the document's text. Several parts of the programme may use that text. A search operation reads it. A preview renders it. A Save command writes the new version. But who is responsible for keeping those bytes in memory, and who is allowed to release them? Today we are going to answer those questions with a small C programme.”

**Screen:** Show a Notes document on the left and a simple storage diagram on the right: one owned document buffer with two arrows to borrowed readers. Point out that the arrows are references, not copies.

**Narration:**

“A pointer is an address, not an ownership certificate. When I pass a pointer to a function, the function must know how long the data is valid and how many bytes it may read. If we lose either piece of information, even simple programmes can become unsafe.”

## The first pointer (2:00–5:00)

**Screen:** Open the pointer example in Lesson 67. Show `unsigned savedNotes = 3U`, the address-of expression `&savedNotes`, and the dereference `*countAddress`.

**Narration:**

“Here is one number in memory. This pointer refers to that number. Reading through the pointer gives us three. Changing the number itself changes what we read through the pointer, because there is only one object. If the object stops existing, the pointer no longer gives us a valid way to use it.”

**Demonstration:** Change the count from 3 to 8 and compile. Explain the displayed result without suggesting that pointers contain objects.

## Building an arena (5:00–10:30)

**Screen:** Open `labs/native/arena-allocator/arena.h` and then `arena.c`.

**Narration:**

“Our arena uses a buffer that its caller already owns. It has three fields: where the storage begins, how large it is, and how many bytes have been reserved. When the programme asks for aligned storage, it checks whether alignment is valid and whether enough space remains. Only then does it return a pointer and advance its position.”

**Screen:** Zoom in on the `available - padding` check. Show a short animation with seven used bytes, one padding byte and an aligned eight-byte object.

**Narration:**

“The subtraction is safe because we first prove that padding is no greater than the available capacity. This order of operations matters. It prevents an unsigned calculation from wrapping and falsely claiming that there is lots of space.”

**Demonstration:** Build the arena laboratory using the commands in Lesson 68. Run CTest. Open `main.c`, reduce the workspace and show the controlled failure. Then restore the original value.

## Checkpoints and lifetimes (10:30–13:30)

**Narration:**

“When the report is finished, the programme returns to a checkpoint. It has not individually freed each string and it has not erased the old bytes. The arena simply allows that space to be reused. Pointers into the released part must not be used again. A saved note that needs to survive tomorrow must have a different owner from this temporary report.”

**Screen:** Animate the report allocations disappearing when the arena position returns to the checkpoint. Emphasise that any old pointer beyond it is invalid for continued use.

## Closing exercise (13:30–16:00)

**Narration:**

“Open the arena test and find the case that tries to allocate more memory than is available. Before running it, predict what should happen to the previous pointer and the arena's used count. Then run the test and compare the result. We have learned not just how to allocate memory, but how to define what failure is allowed to change.”

**Screen:** Show the test command, expected passing results, and a link to the [Umicom Framework allocator header](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/base/memory.h). Finish with the Bits2Banking website and repository links.
