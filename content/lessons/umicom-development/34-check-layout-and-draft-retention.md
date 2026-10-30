# Check layouts without losing your work

Read the [corresponding Framework source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/ui_workstation/test_workspace_focus_gtk4.c) at the revision used by your build. Source-reading exercises do not establish that an installed workflow has been qualified.

A layout can look convincing in a drawing and still fail in a real application. Text may disappear when a panel moves, a button may be outside the window, or a keyboard shortcut may reach a hidden control. A useful check describes an action and its expected result. This chapter builds a small review around real Umicom source and disposable data. You do not need a broker account or private media to practise it.

## 1. Record the starting point

1. Write down the application name, executable path, source revision and build configuration. A source revision identifies the version of the code; Debug and Release are different build configurations.
2. Record the window size, display scaling and input method. Scaling changes how large text and controls appear. A layout that works at one size can fail at another.
3. Choose a small synthetic example: two text files for Studio, a guest market view for Trader, or two local practice clips for Media. Keep original files outside your experiment.
4. Write the expected result before performing the action. For example: “Resizing the Inspector keeps the unapplied clip name and does not change the recipe.”

## 2. Separate observations

| Check | Evidence to collect | What it does not prove |
| --- | --- | --- |
| Geometry | All required controls are inside their regions at two window sizes | That a visible control performs its command |
| State retention | The same draft text and selected item survive a layout change | That the draft has been saved to disk |
| Keyboard access | Focus reaches visible panels and skips hidden ones | That every screen-reader announcement is correct |
| Domain action | A reviewed operation produces the expected result | That unrelated operations or live services are qualified |

Do not substitute a mockup for a screenshot of the running application. A mockup explains intent; a runtime capture records a particular observed screen. Likewise, a test source file is a description of checks, not proof that they ran. A skipped test is an outstanding observation, not a pass.

## 3. Review the shared host test

Open tests/ui_workstation/test_workspace_focus_gtk4.c in Framework. Its provider creates three actual GtkEntry widgets. An entry is a one-line editable text field. Each receives the same draft text so the test can compare it after layout operations. The host starts empty, content retention is enabled, then the three panels are populated. This order matters: enabling retention after a populated host is deliberately refused.

```c
CHECK(umi_gtk4_workspace_layout_host_create(
    layout, CreateBody, &fixture, &host) == UMI_STATUS_OK);
CHECK(umi_gtk4_workspace_layout_host_set_content_retention(
    host, 1) == UMI_STATUS_OK);
```

CHECK is a test macro. A macro is a named piece of source expanded by the C preprocessor. Here it reports a failed condition and jumps to cleanup. The ampersand supplies an address so create can return the new host. UMI_STATUS_OK is the named success status. Read the complete file for allocation, population and cleanup: the two lines alone are not a complete test.

The test presents a native window, moves focus through Files, Editor and Output, hides and restores the Editor, then maximises and restores it. It checks the number of created bodies and their text. If the host silently reconstructs them, a final text comparison alone could miss the problem if replacement code copied the same string; the creation count provides a second observation.

## 4. Review the Media integration checks

Open tests/video_sequence/workspace_customisation.inc. The keyboard-regions case moves through the actual source notebook, Preview, Inspector and Timeline. The keyboard-hidden case hides two regions first and confirms that navigation leaves them hidden. Both retain an unsubmitted field value and compare the complete sequence before and after. The shared final check uses Undo to confirm that navigation did not consume an editing-history slot.

The test’s Capture helper records the mapped GTK widget through its renderer and saves a PNG in its fixture directory. The test output prints the resulting path. This is a real capture when that test executes; no screenshot is created simply by reading the source. Playback, encoding and sound still require their own checks.

## 5. Perform a manual review

1. Open the relevant application and establish the disposable starting state. Capture the window before changing its layout.
2. Resize the window and a panel divider. Verify that labels, scrollbars and required action buttons remain reachable.
3. Enter an unapplied draft value. Hide and restore its panel, then maximise and restore another panel where supported. Return to the original field.
4. Use F6 and Shift+F6 between regions. Use Tab inside a region. Confirm that selection and navigation do not activate an edit, order or export command.
5. In Studio, switch between two edited tabs. In Trader, check instrument and account context after moving a panel. In Media, compare the recipe and undo behaviour after navigation.
6. Save a capture of the resulting window and describe any difference from the expected result. Keep personal paths, account information and real financial or media data out of public examples.

## 6. Interpret an incomplete result

If the window cannot start, inspect the launch and build diagnostics before attempting the layout exercise. If GTK has no display session, a native test may return the configured skip code 77. Record that prerequisite and arrange a suitable desktop session. If navigation cannot find another panel, check whether it is hidden, disabled, on another notebook page or in a different native window. Do not change the expected result merely to produce a pass.

The same review pattern applies to other Umicom products: define a small real workflow, preserve its data, exercise presentation changes, and collect identified results. Shared tests qualify shared mechanisms; product acceptance still needs the real installed application and the user task it promises to support.

## Check your understanding

A layout test passes in a small shared-host fixture, but Studio loses text when switching tabs. Can the fixture result be used to close the Studio defect?

<details><summary>Show an explanation</summary>

No. The fixture establishes only its own checks. Studio may have a different ownership or document-switching problem. Preserve the fixture result, record the failing product journey, and add a regression that exercises that exact route.

</details>

[Course contents](index.md) · [Read the illustrated lesson](../../courses/umicom-development/lessons/34-check-layout-and-draft-retention.html)
