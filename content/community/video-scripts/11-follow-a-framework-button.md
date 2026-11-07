# Video script: Follow a button into Umicom Framework

**Aim:** Trace a real desktop action from its button to the shared Framework function and its regression test.

**Preparation:** A text editor and local source copies of Umicom OS and Umicom Applications. This is a reading lab. You do not need to build either application. Use a separate practice folder and hide notifications or personal account details before recording.

[Lesson and exact commands](../lessons/11-follow-a-framework-button.md)

## Opening words

Next, we will take this topic one step at a time: follow a button into umicom framework. Follow one step at a time. Pause the video whenever you need a little more time.

## Scene 1

Show the desktop source in an editor. Highlight the button label and clicked signal connection without pretending the application has been run.

## Scene 2

Open the public declaration beside the implementation. Explain a pointer and status using this exact call, then read each guard.

## Scene 3

Show the test source and separate its expectations from execution evidence. Ask the learner to draw the button-to-callback-to-Framework path.

## Walkthrough and pauses

### Start with the action you can describe

**Say:** A user chooses Browse applications on the desktop home screen. The intended result is an application list. Opening that list does not launch every application. Keeping these two actions separate makes the button easier to understand and test.

### 1. Find the application source

**Say:** Open your source folder in an editor. In the Umicom OS repository, find applications/os/src/gtk4/desktop_shell.c. Search for open_applications. Read where the button is created and where its clicked signal is connected. A signal is a notification from a widget. A callback is the function registered to respond.

**Say:** The callback asks the Framework titlebar to open its existing application catalogue. The OS does not make a second catalogue or maintain a second application list. This keeps the shared behaviour in one place.

### 2. Read the public declaration

**Say:** In Umicom-Applications/framework, open include/umicom/ui/gtk4/workstation/shell_header.h. Find umi_gtk4_ws_window_titlebar_open_applications. A declaration tells a caller the function name, parameter type and return type. The implementation lives in a source file.

**On screen — type one line at a time:**

```c
UmiStatus umi_gtk4_ws_window_titlebar_open_applications(
    UmiGtk4WorkstationWindowTitlebar *titlebar);
```

Pause. Read the result before continuing.

**Say:** titlebar is a pointer to a Framework object created earlier. A pointer identifies an object in memory; passing it does not create a copy. UmiStatus reports whether the operation could be performed. A null pointer has no object, so it is rejected.

### 3. Find the implementation and its checks

**Say:** Open adapters/gtk4/workstation/shell_header_gtk4.c in Framework and search for the same function name. Notice the checks before gtk_menu_button_popup. The button must belong to the expected window and be mapped and sensitive. Mapped means it is currently presented as part of a visible widget hierarchy. Sensitive means the widget is enabled for interaction.

**Say:** A successful return means the existing catalogue was asked to open. It does not claim that an application was installed or started. Callers should show an understandable message when the window is not ready.

### 4. Follow the tests

**Say:** Read Framework tests/ui_workstation/test_window_titlebar_gtk4.c and OS applications/os/tests/test_desktop_shell.c. The checks include a null argument, an unopened window and the visible desktop action. Regression tests record expected behaviour so later changes can be checked against it.

**Say:** Reading a test is not the same as running it. These native tests require the matching Framework revision, GTK libraries and a graphical environment. Record a pass only after that test has actually run.

### Your turn

**Say:** Write four lines in your notes: the button label, the callback name, the Framework function and the expected failure result before the window is ready. Then explain why opening the catalogue should not launch a program by itself.

## Closing words

Before moving on, try the exercise once more in your own practice folder. If the result is different, compare the command and current location with the lesson. You can come back to this step at any time.
