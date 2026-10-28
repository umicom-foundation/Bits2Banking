# Remembering connection settings safely

A program often needs to remember choices after it closes. Examples include a window size, a preferred language, or the port used to connect to another program. This is called **persistence**: keeping information beyond the lifetime of one running process.

This lesson follows the local broker settings service in Umicom Framework. You can study its code without a broker account, market data or money.

## Separate settings from permission

Umicom Trader lets you choose Paper or Live. A **mode** is a named choice. A **port** is a number that identifies a communication endpoint. A **client ID** identifies one connection to the broker program.

Saving these numbers does not save permission to trade or even permission to connect.

| Remembered value | Why it can be useful |
| --- | --- |
| Program choice | The broker program may have a different default port |
| Paper port and client ID | A testing session can use its own endpoint |
| Live port and client ID | The real-account session can use a separate endpoint |

Passwords, authentication codes and Live acknowledgement are absent from this format. The application always asks you to make the connection decision again.

## Start with a structure

The real header is [access_profiles.h](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/broker_connectivity/access_profiles.h).

```c
UmiBrokerAccessProfiles profiles;
UmiStatus status = UmiBrokerAccessProfilesDefault(&profiles);
if (status != UMI_STATUS_OK) {
    return status;
}
profiles.paper.clientId = 42;
```

Read the example in order:

1. A **structure** groups related values. Here it holds one Paper plan and one Live plan.
2. The first line declares storage named `profiles`. Declaration alone does not fill it with valid settings.
3. The function ending in `Default` supplies valid starting values.
4. `&profiles` means “the address of profiles”. It tells the function where to put the result.
5. `status` reports success or failure. The `if` statement prevents later code from using a failed result.
6. The dots in `profiles.paper.clientId` select the Paper plan and then its client ID.
7. Assigning `42` changes memory only. It does not write a file or contact another program.

This fragment belongs inside a function that returns `UmiStatus`. It is not a complete program by itself.

## Turn values into bytes

An **encoding** is a rule for representing information as bytes. The Framework uses a small text format:

```text
UMICOM-BROKER-PROFILES 1
paper 0 7497 42
live 0 7496 35
```

The first line identifies the format. The number after the name is its format version. Each remaining line names a mode followed by the program, port and client ID.

The parser does not trust text simply because it came from a local file. A user might edit it accidentally, a write might fail, or a newer program might produce a format this program does not understand.

Read [access_profiles.c](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ibkr_connection/access_profiles.c). Its cursor records the input size and current position. Before reading a literal word, the parser checks how many bytes remain. Before multiplying a number by ten, it checks whether the new digit would exceed the allowed maximum.

The parser builds a temporary structure. Only after the entire input is valid does it copy that structure into the caller's output. This is why a damaged file does not partly change the current settings.

## Prevent two writers from losing each other's work

Imagine one window saves Paper settings while another saves Live settings:

```text
Window A: acquire guard -> read both modes -> replace Paper -> publish -> release
Window B: guard busy    -> wait and retry  -> read updated file -> replace Live
```

A **guard file** gives cooperating writers a shared place to acquire an operating-system lease. A lease is temporary ownership held by an open handle. The file can remain after the handle closes; an existing filename does not mean an operation is still running.

The guard is not a security boundary. Another program that ignores the lease can still change the settings file. The directory must be one you control.

Read [access_profile_store.c](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ibkr_connection/access_profile_store.c). It reuses the Framework's file lease and complete-file replacement services instead of inventing another storage system.

## Keep a window responsive

Reading or writing a disk can take time. If a graphical application waits for disk I/O on the same thread that draws buttons, the window can appear frozen.

The broker window therefore copies the requested path and settings into a worker request. A **worker** performs the file operation away from the GTK event loop. When it finishes, the result returns to the GTK thread.

The result must check whether the window still exists. If the user closed it, the worker must not try to update its old controls. A save already in progress may still finish; closing the window does not undo publication.

## Try the application workflow

1. Open the broker inspector in Umicom Trader while disconnected.
2. Select Paper and enter your local API port and client ID.
3. Expand **Saved Paper and Live settings**.
4. Review the absolute settings path and choose **Save selected mode**.
5. Change the displayed port without connecting.
6. Choose **Load selected mode**. The saved port should return.
7. Repeat with Live. Loading must leave the Live acknowledgement unchecked.

These are expected results to check in a built application. They do not require sending an order. The current inspector is read-only.

## Questions to check your understanding

- Why is declaring a structure different from giving it valid values?
- Why should loading a file not imply permission to connect?
- Why does the parser check arithmetic before multiplying by ten?
- Why must both writers use the same guard path?
- What should happen when a worker finishes after its window closes?

Answers: a declaration provides storage; connection permission is a new user decision; unchecked multiplication can overflow before a later check notices; otherwise the writers do not coordinate; and completion must release its resources without updating retired controls.

Continue with [local broker sessions](local-broker-sessions.md), [memory ownership](../03-native-code/58-memory-ownership-in-c23.md), or the [financial systems index](index.md).
