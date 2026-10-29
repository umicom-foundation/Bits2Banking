# Carry image pixels from a worker to a window

Read the accompanying [Umicom source example](https://github.com/umicom-foundation/umicom-framework/blob/main/adapters/gtk4/learning_catalogue_images.c). Match its revision to your checkout before comparing behavior.

A diagram is stored as bytes in a file, but a window needs pixels it can display. A *pixel* is one sample in a rectangular image. This chapter follows the native learning catalogue in Umicom Framework: it reads a verified PNG, decodes it away from the window's event processing, and gives the window its own stable pixel storage.

Read [Introduction to GTK4](05-introduction-to-gtk4.md) and [Keep reading state consistent](17-keep-reading-state-consistent.md) first if callbacks and candidate readers are new. You can follow the explanation without compiling anything. The implementation is in `adapters/gtk4/learning_catalogue_images.c` in your Framework checkout.

## 1. Separate a file from its picture

PNG stores compressed image information. A *decoder* interprets that format and produces pixels. The compressed file's length does not tell you how much memory the decoded picture will need. A small file might describe a much larger rectangle.

Framework's catalogue first verifies the file against the digest in its learning-pack manifest. A *digest* is a fixed-length value computed from the bytes. A mismatch means the file differs from the admitted version. A matching digest still does not prove that those bytes form a valid PNG, or identify a trustworthy author. Verification and decoding answer different questions.

## 2. Understand RGBA and a row

The native image path uses four channels for each pixel: red, green, blue and alpha. Alpha represents opacity. Each channel occupies one byte, with a value from 0 to 255. Red at 255, green and blue at 0, and alpha at 255 describes fully opaque red. Alpha at 128 describes approximately half opacity; it does not mean half the red value.

The pixels use *straight alpha*: colour samples remain separate from opacity. The GTK texture is told this exact format using `GDK_MEMORY_R8G8B8A8`. Choosing a premultiplied format without converting the samples would misinterpret translucent colours.

A *stride* is the byte distance from one row's start to the next row's start. This adapter uses tightly packed rows, so a width of 100 pixels gives a stride of 400 bytes. Ten such rows need 4,000 bytes. Other image systems can add padding; never assume every external image uses this formula.

```c
size_t stride = (size_t)width * 4U;
size_t byte_count = stride * (size_t)height;
size_t at = y * stride + x * 4U;
pixels[at]      = row[x].red;
pixels[at + 1U] = row[x].green;
pixels[at + 2U] = row[x].blue;
pixels[at + 3U] = row[x].alpha;
```

This is an excerpt from the adapter's copying step. It is not a complete program. The surrounding code checks dimensions before these multiplications and ensures each coordinate is inside the admitted rectangle. Explicit channels avoid depending on how a compiler lays out a structure or how an integer's bytes are ordered.

## 3. Bound the work before allocating memory

The catalogue admits source resources up to 1 MiB. For a decoded image, it separately limits each side to 2,048 pixels and the total to 1,048,576 pixels. A 1,024 by 1,024 RGBA buffer therefore needs 4,194,304 bytes, or 4 MiB. The decoded surface and a copied buffer can exist at the same time, so that buffer size is not the process's entire memory cost.

The adapter reads the PNG's initial dimension fields only after checking that the header bytes exist. Those fields help reject excessive work early. The shared Media decoder still validates the complete format and chunk checksums. An early dimension check is not a substitute for format validation.

## 4. Keep the window responsive

[Illustration: verified PNG bytes → decoded private surface → immutable owned RGBA bytes → GTK texture. File work and decoding run on the worker; texture publication runs on GTK.]A *worker* is execution assigned away from GTK's event-processing thread. The reader's worker performs file verification and decoding. It does not change GTK widgets. The completed job carries the result back to GTK, which updates the picture.

The decoder returns an owned image surface. The adapter copies its channels into an RGBA byte allocation and releases that temporary surface. `g_bytes_new_take` then transfers ownership of the allocation to an immutable `GBytes` object. After that transfer, the old pointer is not another independently owned allocation that the worker should free.

On the GTK thread, `gdk_memory_texture_new` retains the bytes needed by the texture. The picture retains its paintable. Consequently the job can release its reference after publication without leaving the window pointing at freed worker storage. These are distinct owners with explicit reference lifetimes, not a global image buffer shared by unrelated windows.

## 5. Treat failure as a normal result

The optional PNG service may be absent. The file might be another format, too large, damaged or animated. Those conditions produce a visible limitation message for the verified resource; the viewer does not silently open another program or download a codec.

A recoverable allocation failure follows a different path: the candidate is not published and the previous reader remains. Its selection, text, image and Back/Forward history must agree. Replacing the history before pixels are ready would make the visible page describe a different state from the navigation controls.

Closing the catalogue marks its owner as retired. A pending worker may still finish, but its late result cannot populate a disposed panel. During publication, GTK can emit synchronous notifications. Metadata is established before those callbacks, and a new mutating operation reports busy until publication finishes.

## 6. Trace the real implementation

- Open `adapters/gtk4/learning_catalogue_jobs.c`. Find the active `PrepareDisplay` function and its image-resource branch. Preserved disabled implementations are historical alternatives, not the code that executes.
- Open `adapters/gtk4/learning_catalogue_images.c`. Follow dimension admission, Media decoding, row copying and the transfer into `GBytes`.
- Find `LearningCatalogueImagePublish`. Notice that it creates the texture on the GTK thread and checks retirement after observable widget changes.
- Read `tests/learning_pack/test_catalogue_images_gtk4.c` for real-codec and fallback cases. Read `test_catalogue_image_failure_gtk4.c` for a deterministic provider seam that makes allocation failures observable even when host libpng is absent. A provider seam is a narrow replaceable boundary used to control one dependency during a test.Source inspection explains the intended contract. It does not establish that the application compiled, rendered correctly, or passed these tests on your machine.

## Try it in the learning catalogue

- Use a matching application build that includes the native learning catalogue. Load a pack that declares a small static PNG as an image resource.
- Open the guide, then explicitly open its declared image link. Expected behavior with the PNG capability is a picture and a verified-image message. Without it, expect an explicit capability notice.
- Use Back. Expected behavior is the earlier guide, without leftover image pixels.
- Close the catalogue during another read. Expected behavior is orderly retirement, with no late reopening of the window.The complete authoring instructions are in Framework's `docs/learning/view-learning-illustrations.html`. Inline HTML images currently retain descriptions; separately opened PNG resources provide the pixel view. Keep a written explanation alongside any important diagram.

## Check your understanding

**Why is a 2,048 by 2,048 image refused?**

Each side meets its individual limit, but 4,194,304 total pixels exceed the separate total-pixel limit. Both rules must hold.

**Does a matching SHA-256 digest prove that PNG decoding will succeed?**

No. It establishes agreement with the admitted bytes. Those bytes may still contain a malformed or unsupported image.

**Why not free the RGBA allocation immediately after creating the texture?**

Ownership has transferred to reference-counted bytes retained by the texture. Freeing the raw allocation independently would invalidate that ownership contract.

**What does a successful CopyIllustration call establish?**

It copied the selected resource's illustration metadata. Inspect the copied status and has_pixels fields to determine whether pixels were prepared.

[Previous: Follow protocol message boundaries](22-follow-protocol-message-boundaries.md) · [Course contents](index.md)

Sammy Hegab · Umicom Foundation · MIT. Original learning material.

[Next: Find text with shared Framework services](24-find-text-with-shared-services.md)

## Follow an image reference without loading it automatically

An HTML `img` element can name a source file using `src` and describe its meaning using `alt`. The reading model retains the description and separately copies bounded source metadata. `UmiBrowserReadingDocumentImageAt` returns that metadata; it never opens the file. An unusable source has an explicit status and an empty target, so a clipped filename cannot accidentally name another resource.

The native catalogue lists these references under Reading controls. The learner chooses an illustration and explicitly opens it. `UmiLearningCatalogueGtk4OpenReadingImage` checks the displayed reader's admitted pack, requires the resource kind to be image and refuses fragments, remote addresses and undeclared files. Only then does the existing worker verify and decode bytes. Back returns to the guide. This separates describing an image, admitting a local resource and decoding its pixels into three reviewable steps.

Follow `src/browser/reading_document_builder.c` for metadata ownership and `adapters/gtk4/learning_catalogue_reading.c` for the explicit action. The old text-only description is retained. Pixels are still shown in a separate bounded viewport rather than inserted among paragraphs.

## Apply the idea

<details>
<summary>Choose who releases the pixels</summary>
<p>A worker prepares valid pixels, but the learner closes the panel before publication. Should the worker reopen the panel to show the image?</p>
<p><strong>Explanation:</strong> No. Closing the panel retires its request. Release the prepared result through its current owner and do not create a late visible update. If ownership has already transferred to reference-counted bytes, release that reference instead of freeing the same allocation separately.</p>
</details>
