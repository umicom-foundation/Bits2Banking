# Introduction to GTK4

## Build a window from smaller parts

GTK4 is a toolkit for graphical interfaces. A widget is a part of that interface, such as a button, label or container. A label displays text; a button accepts an action; a box arranges child widgets; a window contains the page.

Our example has this hierarchy:

~~~text
Application
  Window: Learning with Umicom Framework
    Vertical box
      Label: Completed exercises: 0
      Button: Record one exercise
~~~

GTK handles the platform's window and input events. The application supplies callbacks: functions GTK calls when something happens. A button's clicked signal is one such event. This is event-driven programming; the program does not repeatedly ask whether the user pressed the button.

## Read the activation path

Open [window.c](../../../labs/native/framework-activity/window.c).

main creates a GtkApplication and connects its activate signal to Activate. g_application_run starts the event loop. An event loop waits for input and dispatches work to the connected callbacks. When the application exits, main releases its reference.

Activate constructs a window, its vertical box, a label and a button. It sets the title and margins, adds the label and button to the box, adds the box to the window, then presents the window. The order establishes ownership before the user can interact.

The activity state contains a count and a borrowed pointer to its label. g_object_set_data_full attaches the state to the window together with g_free as its cleanup function. When the window's object lifetime ends, that state is released. GTK containers own their child widgets; this example does not free the label by hand.

## Follow a click

Completed calls BtbActivityAdvance, the same function used by the console. It then formats either a new count or a readable Framework error and changes the label text. It does not duplicate the validation rule.

The callback temporarily retains the window with g_object_ref and releases it with g_object_unref. This keeps attached state alive while observable label notifications run. Such lifetime decisions matter when a larger application can close or rebuild a panel from another callback.

The example stores no files and makes no network requests. Closing and reopening its window starts a new count. Persistence would be a separate feature with an explicit storage contract.

## Enable the optional GTK target

Install the tools and SDK described in [Windows setup](../../umicom/windows-development.md). Reconfigure the existing lab with its graphical option enabled:

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\framework-activity" -B ".\build\framework-activity" -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework;C:/msys64/ucrt64" -DBUILD_TESTING=ON -DBTB_ACTIVITY_GTK4=ON
cmake --build ".\build\framework-activity" --parallel 2
ctest --test-dir ".\build\framework-activity" --output-on-failure --no-tests=error
& ".\build\framework-activity\btb-activity-window.exe"
~~~

CMake uses pkg-config to discover GTK's headers and libraries. This is dependency discovery, not a download. If GTK is not found, check pkg-config --modversion gtk4 and the UCRT64 installation before continuing.

## Check the actual interaction

1. Confirm that the new window displays a count of zero.
2. Activate Record one exercise once. Expect one.
3. Activate it twice more. Expect three.
4. Use the keyboard to focus and activate the button.
5. Close the window, then launch it again. Expect zero because persistence is not part of this example.

The six automated tests exercise the shared count contract. They do not perform these GUI steps. Record the GUI result separately instead of treating a passing console test as evidence for keyboard focus, rendering or window lifetime.

For the original toolkit explanation, see [GTK's getting-started guide](https://docs.gtk.org/gtk4/getting_started.html). The example here is an original Umicom teaching consumer.

**Question:** Should the button callback contain another copy of the counting rules?

**Answer:** No. Both front ends call the same checked function. A future correction then reaches both presentations, and the independent logic tests remain useful.

Return to [the development course contents](index.md) or explore [Umicom OS from Scratch](../../courses/umicom-os-from-scratch/index.html).

[Course contents](index.md)
