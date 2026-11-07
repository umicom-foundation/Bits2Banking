# Install Flutter and run a first application

Flutter is a toolkit for building application interfaces. Flutter application code is commonly written in Dart. A widget describes a part of a screen: text, a button, spacing, or a larger composition. This course begins with a small learning counter and explains the code it uses. No previous Dart or mobile course is required.

## Setup recap: Set up tools and a target

1. Follow [Flutter's installation guide](https://docs.flutter.dev/install) for Windows or Linux. Install the Flutter SDK into a writable tools folder and add its `bin` folder to PATH, the directories searched for commands.
2. Open a new PowerShell or bash terminal. Run `flutter --version`. Flutter includes a compatible Dart SDK; do not separately install an arbitrary Dart version for this example.
3. Run `flutter doctor`. This reports tool availability. Read each finding; a successful Flutter download alone does not provide every platform toolchain.
4. For this first lab, use the web target and install the supported browser required by the current Flutter guide. Run `flutter devices` and confirm that the browser target appears. Android deployment is a later optional step requiring the Android SDK and an emulator or connected device.

Reading needs only a browser. Running needs internet access for initial dependencies and permission to install the selected tools. See [Open a terminal](../../08-system-administration/03-open-powershell-or-linux-terminal.md) for a longer introduction to command windows and current folders.

## 2. Create a project

In PowerShell:

```powershell
New-Item -ItemType Directory -Force 'C:\umicom-learning'
Set-Location 'C:\umicom-learning'
flutter create --project-name lesson_counter lesson_counter
Set-Location '.\lesson_counter'
flutter devices
flutter run -d chrome
```

In bash:

```bash
mkdir -p "$HOME/umicom-learning"
cd "$HOME/umicom-learning"
flutter create --project-name lesson_counter lesson_counter
cd lesson_counter
flutter devices
flutter run -d chrome
```

Use a new project folder. `flutter create` creates the template. `--project-name` sets the Dart package name; later imports in this course use `lesson_counter`. `-d chrome` selects the Chrome device when it is listed. If your supported browser has another device identifier, use the identifier shown by `flutter devices`. Stop if a command fails instead of continuing into a partly created project.

## 3. Observe the template

The generated application should open in the browser. Try its counter button. Return to the terminal and press `q` to stop the development run when finished. This establishes that the generated project and selected target work before introducing the learning example.

| Project path | Meaning |
| --- | --- |
| `lib/main.dart` | Application entry and screen source |
| `pubspec.yaml` | Package description, dependencies and assets |
| `test` | Automated test source |
| `web` | Files supporting the browser target |
| `android` | Android host files when that platform is included |

The pipeline is **Dart widgets → Flutter build → chosen platform runtime → visible screen**. Choosing another target can require extra platform tools even though much application source is shared.

## 4. Make one visible change

Open `lib/main.dart` in a text editor. Find the title displayed by the template and change its text. Save the file and follow the running terminal's reload or restart command. Confirm the changed title appears. Reload and restart are different: reloading can retain state, while restarting starts the application again. Neither replaces a deliberate test of a newly installed release.

If the browser does not launch, inspect the terminal's device error. If dependency download fails, inspect the first package error and connectivity. If a source change has no effect, check that the editor and terminal are using the same project folder.

## Exercise and next step

Explain which file you edited and which command launched the result. The answer should identify `lib/main.dart` and `flutter run -d` with your device identifier. In the next lesson you will replace the template with [Umicom's local counter example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-lesson-counter/main.dart), then exercise its buttons in an automated widget test.

[Course contents](index.md) · [Next: widgets, state and tests](02-widgets-state-and-tests.md)
