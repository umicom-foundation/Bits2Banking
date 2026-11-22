<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/graphics-from-scratch/06-present-with-gtk4.md

PURPOSE:
Show a GTK4 texture bridge that preserves raster and presentation ownership.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Present a pixel buffer with GTK4

[Previous: Call the C library from D](05-call-from-d.md) · [Course contents](index.md)

The raster produces pixels and can export them to a file. A desktop application can also display them inside a GTK4 view. The lab bridge turns an admitted image into a texture, an image object that GTK can paint. The platform host still owns the widget, the window and the event loop. [GDK memory texture constructor](https://docs.gtk.org/gdk4/ctor.MemoryTexture.new.html) · [GTK picture constructor](https://docs.gtk.org/gtk4/ctor.Picture.new_for_paintable.html)

## Follow ownership across the boundary

1. The source image has packed RGB triples and a row stride. `GDK_MEMORY_R8G8B8` describes that exact channel order. [GDK pixel formats](https://docs.gtk.org/gdk4/enum.MemoryFormat.html)
2. The `umicom_raster_create_texture` adapter checks the layout and copies the visible bytes from each row. The new rows contain no padding. An immutable `GBytes` snapshot owns the copied bytes.
3. The new texture keeps the snapshot alive. Your C code can reuse its original drawing storage after the adapter returns.
4. The host assigns the texture to a `GtkPicture` that it already owns. When the widget keeps its own reference, the caller releases its local texture reference.

```c
GdkTexture *preview = umicom_raster_create_texture(&image);
if (preview != NULL) {
    gtk_picture_set_paintable(picture, GDK_PAINTABLE(preview));
    g_object_unref(preview);
}
```

Use the widget call on the UI thread of your existing GTK4 application. The sample's files `gtk4_texture.h` and `gtk4_texture.c` only implement the adapter. To compile it, configure an additional build directory with the steps from the export lesson and `-DUMICOM_RASTER_GTK4_BRIDGE=ON`. The build needs GTK4 development files discoverable by `pkg-config`. If CMake cannot find them, keep using the console lab while you prepare the GTK4 toolchain.

With the bridge enabled, CTest also verifies the snapshot in memory. The test overwrites the original buffer and reads back the texture's unchanged colours. It needs no window or display. [GDK texture download](https://docs.gtk.org/gdk4/method.Texture.download.html)

## Finish the course

Change one shape, predict the visible pixels, then run both raster tests. Build the C and Assembly versions and compare their output hashes. Optionally call the same C library from D. Write down which component owns the pixels and which owns the texture. If you use a texture in a host app, confirm the older snapshot stays visible after you draw a new scene into the C buffer.

The next step toward Umicom Media or a workbench is to compare this teaching buffer with the existing Framework image-view and canvas contracts. Reuse those Framework services for product work. For a Kernel exercise, compare this tightly defined pixel format and validated stride to the [boot framebuffer admission lesson](../../06-umicom/umicom-kernel-from-scratch/79-admit-optional-boot-descriptors.md).

[Previous: Call the C library from D](05-call-from-d.md) · [Course contents](index.md) · [All lessons](../../index.md)
