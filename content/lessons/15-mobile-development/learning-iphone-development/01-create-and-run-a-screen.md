<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-iphone-development/01-create-and-run-a-screen.md

PURPOSE:
Explain the lesson: Create and run your first iPhone screen.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Create and run your first iPhone screen

## Start here
An application is a program that a person can launch. A project groups its source, settings and resources. Xcode is Apple's development environment; the simulator runs an iPhone software environment on a Mac. This course uses a small exercise counter, not financial or personal data.

You need a supported Mac, Xcode and an installed iOS Simulator runtime. You can read the course on Windows or Linux, but the native iPhone build exercises use Xcode on macOS.

## Set up step by step
1. Install Xcode and open it once to complete its setup.
2. Create a new iOS App project named ActivityLab.
3. Select Swift as the language and SwiftUI as the interface.
4. Save the project in a practice folder you can find again.
5. Select an installed iPhone simulator as the run destination.
6. Run the unchanged template. Wait for the simulator to display its starting screen.
7. Stop the run from Xcode before making your first change.

A successful template run establishes that the basic environment works. It does not yet test the Umicom example.

## Understand the parts
The generated app type provides the entry point. A view describes visible content. State holds values that may change. The simulator's window is the visible result of that code.

~~~text
project settings -> compiler -> application -> simulator screen
source files --------^
~~~

## First exercise
Change only the template's greeting text to "My learning activity". Run again. Confirm the new text appears. If it does not, check the selected project, target and run destination before editing other settings.

## Connect to Umicom
The next lessons use the same C activity model as the desktop teaching application. SwiftUI handles the native screen. The C model decides whether a count update is valid. Keeping those responsibilities separate makes it possible to teach several interfaces without copying the rule.

## Troubleshooting
A missing simulator runtime is an environment problem, not a defect in your greeting. Install a compatible runtime through Xcode's settings. A signing error for a physical phone should not prevent you from first trying an installed simulator.

## Check your understanding
Explain the difference between source code, a project and a running application. Record the Xcode version and simulator destination used for your first successful run.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/iphone-framework-activity/README.md). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](02-call-the-shared-c-model.md)

