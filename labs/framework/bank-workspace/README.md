# Banking workspace lab

This small desktop program hosts Framework's banking operations. The banking data is a local simulation: it does not move real money, contact a bank or authenticate a customer. A database is a file containing structured records; the launcher lets you choose its location.

## Prepare the tools

You need Git to obtain sources, a C23 compiler, CMake to describe build steps, Ninja to execute those steps, GTK4 development libraries, and an installed Umicom Framework SDK containing the banking GTK adapter. Install matching compiler/runtime packages. An application built with the Windows UCRT64 environment must use its corresponding GTK libraries.

In PowerShell, use an existing SDK installation and replace its path if yours differs:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\bank-workspace"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/applications
cmake --build build --parallel 2
& ".\build\bank-workspace.exe"
```

In a Bash terminal, replace the SDK prefix with your installation:

```bash
cd ~/umicom/Umicom-Bits2Banking/labs/framework/bank-workspace
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom-sdk"
cmake --build build --parallel 2
./build/bank-workspace
```

Run one command at a time. Stop when a command fails and read its first error. A missing imported target means the SDK lacks the adapter; a missing DLL or shared object means the runtime search path is incomplete. Neither should be fixed by copying financial logic into this host.

## Choose a workspace

1. Create an empty practice folder somewhere you can access easily.
2. Start the lab. Leave the filename blank and press Banking operations. Read the location message; no database should open.
3. Choose a new filename inside your practice folder. The chooser only fills the path field.
4. Press Banking operations. The service opens or creates the selected simulation database.
5. Close the operational window. Use Browse existing to select the same database and open it again.
6. Try a filename whose parent folder does not exist. The launcher reports the failure and remains available for a corrected path.

An existing file is opened, not overwritten with an empty ledger. Do not select an unrelated or valuable database. Earlier per-user databases remain in their original location; they are never moved automatically. Back up a closed database before investigating an older format.

## Read the program

Activate is called when GTK activates the application. It reuses an existing window when available. gtk_application_window_new associates a window with that application. UmiGtk4BankOperationsLauncherCreate supplies the complete shared workflow. gtk_window_set_child gives GTK the widget to display. g_application_run processes events until the application exits; g_object_unref releases the application's final reference.

The host contains no balance arithmetic, command parsing or SQL. Those operations belong to Framework. The operational adapter manages its child window and closes that child when the host closes.

## Acceptance exercise

Check blank, cancelled, valid, Unicode, unavailable and reopened paths. Confirm choosing alone creates no file. Record actual results rather than treating a successful compilation as proof that all controls work. Automated native interaction cases reside in Framework's tests/bank_operations/test_native_commands.c; its storage boundary is deliberately replaced with memory storage, so it does not prove disk persistence.
