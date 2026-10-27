# Who owns the keys and values?

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Format:** Narration and storyboard, approximately four minutes.

**Opening visual:** A model checkpoint branches to three independent requests. Each request owns one box marked “K/V store”. A large pool box contains those three stores.

**Narration (0:00–0:45):** “When a Transformer generates text, keys and values let it reuse earlier token projections. They do not replace the model itself. Every conversation develops its own token history. If two sessions accidentally write into the same mutable cache, later predictions can depend on the wrong conversation.”

**On-screen labels (0:45–1:25):** Model weights; pool; session lease; store; projected rows. Move the arrows from the model to the stores without adding an arrow that grants the pool ownership of the model weights.

**Narration (1:25–2:30):** “In our native Framework, `StackedKvStore` owns the rows and validates full-context rollover. A pool coordinates stores and their reservations. Think of a library with several lockers. The library tracks who has a locker; it does not rearrange the books inside every locker.”

**Worked example (2:30–3:20):** Two layers, four positions and eight channels use 512 FP32 bytes per store. A budget of 1,024 bytes admits two independent stores, not three. Reset clears rows, while release frees an entire reservation.

**Review question (3:20–3:45):** “What must remain independent between two conversations using the same checkpoint?” Reveal: their mutable retained token histories and K/V store lifetimes.

**Close (3:45–4:00):** Follow LLM Lessons 329–336 and Mathematics Units 197–202.

*Service to Many Leads to Greatness.*
