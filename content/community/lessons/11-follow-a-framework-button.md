# Follow a button into Umicom Framework

Trace a real desktop action from its button to the shared Framework function and its regression test.

**Before you start:** A text editor and local source copies of Umicom OS and Umicom Applications. This is a reading lab. You do not need to build either application.

[Community learning route](../index.md) · [Printable HTML](../handouts/11-follow-a-framework-button.html)

## Start with the action you can describe

A user chooses Browse applications on the desktop home screen. The intended result is an application list. Opening that list does not launch every application. Keeping these two actions separate makes the button easier to understand and test.

## 1. Find the application source

Open your source folder in an editor. In the Umicom OS repository, find applications/os/src/gtk4/desktop_shell.c. Search for open_applications. Read where the button is created and where its clicked signal is connected. A signal is a notification from a widget. A callback is the function registered to respond.

The callback asks the Framework titlebar to open its existing application catalogue. The OS does not make a second catalogue or maintain a second application list. This keeps the shared behaviour in one place.

## 2. Read the public declaration

In Umicom-Applications/framework, open include/umicom/ui/gtk4/workstation/shell_header.h. Find umi_gtk4_ws_window_titlebar_open_applications. A declaration tells a caller the function name, parameter type and return type. The implementation lives in a source file.

```c
UmiStatus umi_gtk4_ws_window_titlebar_open_applications(
    UmiGtk4WorkstationWindowTitlebar *titlebar);
```

titlebar is a pointer to a Framework object created earlier. A pointer identifies an object in memory; passing it does not create a copy. UmiStatus reports whether the operation could be performed. A null pointer has no object, so it is rejected.

## 3. Find the implementation and its checks

Open adapters/gtk4/workstation/shell_header_gtk4.c in Framework and search for the same function name. Notice the checks before gtk_menu_button_popup. The button must belong to the expected window and be mapped and sensitive. Mapped means it is currently presented as part of a visible widget hierarchy. Sensitive means the widget is enabled for interaction.

A successful return means the existing catalogue was asked to open. It does not claim that an application was installed or started. Callers should show an understandable message when the window is not ready.

## 4. Follow the tests

Read Framework tests/ui_workstation/test_window_titlebar_gtk4.c and OS applications/os/tests/test_desktop_shell.c. The checks include a null argument, an unopened window and the visible desktop action. Regression tests record expected behaviour so later changes can be checked against it.

Reading a test is not the same as running it. These native tests require the matching Framework revision, GTK libraries and a graphical environment. Record a pass only after that test has actually run.

## Your turn

Write four lines in your notes: the button label, the callback name, the Framework function and the expected failure result before the window is ready. Then explain why opening the catalogue should not launch a program by itself.

## Continue when you are ready

[Previous: Build and test a small notes project](10-build-and-test-a-small-project.md) · [Next: Read a build log and choose the next step](12-read-a-build-log.md)

[Explore the related course](../../courses/umicom-development/index.html). You can finish this exercise without leaving this page.

[Video teaching script](../video-scripts/11-follow-a-framework-button.md) · [Short community message](../messages/11-follow-a-framework-button.md)
