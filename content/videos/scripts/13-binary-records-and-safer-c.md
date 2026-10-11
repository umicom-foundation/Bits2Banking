# Episode 13 — Turn values into safe bytes with C23

**Approximate duration:** 14–18 minutes  
**Related lesson:** [Write a binary record safely in C23](../../lessons/03-native-code/55-write-a-safe-binary-record-in-c.md)  
**Source code:** [Binary payment records laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/binary-payment-records)

## 00:00–03:00 — Why representation matters

**Narration:**

"A computer stores information as bytes. But an integer's bytes, the padding added to a C structure, and the arrangement of fields are not automatically a safe network format. When we save or exchange data, we need to agree on what each byte means."

**On screen:** Show the sixteen-byte record diagram. Identify the reference number, amount, currency and state. Emphasise that this is a simulated payment record, not a live payment instruction.

## 03:00–06:00 — Design the fields

**Narration:**

"Our teaching record uses four bytes for a payment reference, eight for a non-negative amount in minor units, three for a currency code and one for a training state. The bytes add up to sixteen. The amount 125000 represents £1,250.00 when the currency uses pence as minor units.

"We write integers with the most significant byte first. That convention is called big-endian or network byte order. It means the file has a defined representation even when the programme runs on a processor with a different native byte order."

**On screen:** Highlight the byte offsets in `record.h`. Identify the absence of any pointer field in the wire format.

## 06:00–10:00 — Encode without overflowing memory

**Narration:**

"The encoder validates the input before it writes any output. If the destination has room for fifteen bytes, the operation must refuse to write a sixteen-byte record. On failure it must not leave the caller with an unexplained half-written result."

**On screen:** Open `record.c`. Step through `BtbEncodeRecord`, then read the short `WriteBE` function. Show the explicit capacity comparison.

**Demonstration:** Build the CMake project and run CTest. Run the demo to print the expected hexadecimal bytes.

## 10:00–13:30 — Decode and reject malformed data

**Narration:**

"When decoding bytes, we first check the total input length. We then decode into a temporary record. We accept that record only after checking its fields. A damaged currency code or unknown state cannot silently overwrite a valid object."

**On screen:** Inspect `BtbDecodeRecord` and its tests. Change the currency byte to lowercase and demonstrate that the decoder rejects it. Explain why the test checks that the previously decoded value is unchanged.

## 13:30–17:00 — Make one change yourself

**Narration:**

"Change the example amount from 125000 to 7500 minor units, rebuild and examine the bytes. Only the portion of the record that represents the amount should change. Try to explain exactly why each byte changed."

**On screen:** Show the edit, incremental build and new hexadecimal output. Finish with links to the written lesson, tests and Umicom Framework's finance and messaging contracts.

**Closing:** "A safe message format starts with small decisions: clear field widths, explicit byte order, checked buffer sizes and tests that challenge invalid inputs. Those decisions matter in notes applications, systems software and financial services alike."
