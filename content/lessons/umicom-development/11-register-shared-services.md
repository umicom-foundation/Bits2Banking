# Register shared application services

## What you will learn

A large application is easier to understand when its parts have clear jobs. In this lesson you will follow how Umicom Framework records the services that those parts provide. You will learn what a registry contains, why registration can fail, and why an object must remain alive after another part receives its address. You can read and draw the examples without installing a compiler. The final activity uses the real Framework regression files when you are ready to build them.

Continue from [Close background work safely](10-close-background-work.md). If the words function, structure or pointer are new, return to the functions and memory chapters in [Learning C](../../courses/learning-c/index.html). A pointer is a value that identifies where an object lives in memory. It does not automatically keep that object alive.

## A service, a capability and a module

A service is an object that performs a useful job or holds shared state. A document store, for example, can hold the documents used by editor commands. A capability is a name describing something available to the application. A module is a named part of the application that can provide capabilities and use services.

A registry is a catalogue that connects names to descriptions. Looking up a service is like consulting an index: the catalogue helps you find the object, but finding it is not the same as creating it, starting it or owning it. Framework separates these responsibilities so that application modules do not need to implement their own catalogues.

Open `include/umicom/runtime/capability_registry.h` in the Framework source. Find `UmiCapabilityDescriptor`. Its fields include an identifier, a version, the provider's module identifier and a provider pointer. Then open `include/umicom/runtime/service_registry.h` and find `UmiServiceDescriptor`. The service descriptor also has a destroy callback and ownership flags. A callback is a function supplied for another part of the program to call at a defined point.

## Why a group must be accepted together

Suppose a module offers two capabilities: reading a document and writing a document. The application already has another provider for the writing capability, and that capability permits only one provider. If registration adds the reader first and then rejects the writer, the catalogue contains half of a module that was never accepted.

Framework uses a batch operation to prevent this partial result. A batch is a group of proposed changes. The registry checks every descriptor, identifier, conflict and capacity requirement before it writes any of them. Either the complete group is accepted, or the catalogue remains as it was. This is an all-or-nothing operation within this registry call. It is not a distributed database transaction and does not start any services.

Read `UmiCapabilityRegistryRegisterBatch` in `src/runtime/capability_registry.c`. Notice the validation loop followed by the storage loop. Follow where `registry->count` changes. Count describes how many entries are currently visible, not how many have merely been proposed.

## Trace a real corrected retry

Open `tests/test_registration_transactions.c` and find `CheckMaster`. This fixture uses the actual Master Controller, not a drawing of one. A fixture is the small, controlled setup needed for a test.

The test declares these arrays:

```c
const char *invalid[] = {"example.first", "", NULL};
const char *duplicate[] = {"example.first", "example.first", NULL};
const char *corrected[] = {"example.first", "example.second", NULL};
```

`const char *` describes a pointer to characters that this code must not modify. The square brackets declare an array of those pointers. Each quoted value is a string. The empty string has no name in it. `NULL` is the sentinel that marks the end of this pointer array; it is different from an empty string.

The fixture first registers invalid or duplicate capabilities. It checks the returned `UmiStatus`, then checks that the module count and capability count have not grown. It also checks that `example.first` did not leak into the catalogue. It then supplies the corrected array and registers the same module identifier again. A successful retry proves something that merely checking an error code would miss: rejection did not leave hidden membership behind.

The controller's implementation temporarily records module membership while it admits capabilities. If capability admission fails, it removes that provisional membership. No module callback runs in this interval. This guarantee depends on the controller's serial ownership rule: one owner performs these composition operations, rather than several threads changing the same controller at once.

## Understand singleton ownership

A singleton capability permits one provider. A flag is a named bit used to describe a property; `UMI_CAPABILITY_SINGLETON` is the flag for this rule. Two ordinary providers may share a capability name when their provider identifiers differ. Once either provider requires singleton ownership, that combination is a conflict.

The order must not change the result. An ordinary provider cannot bypass a singleton by arriving later without the flag. The regression cases `singleton-existing` and `singleton-incoming` check both directions. The `multiple-providers` case checks that the legitimate alternative still works.

This illustrates a useful testing habit: when a rule compares two things, reverse their order. An implementation can accidentally inspect only the new item and forget the item already stored.

## An identifier is not a permanent pointer

The registries store identifier characters inside their own entries. A public descriptor has pointers to those character arrays. Removing an entry may move later entries down to close the gap.

Copying an entry moves its character arrays, but a copied pointer still contains the old address. The implementation must reconnect each moved descriptor to the arrays in its new location. Otherwise, a later insertion can overwrite the old location and make one service appear to have another service's name.

Draw three entries labelled A, B and C. Remove A, move B and C left, then place D in the free slot. Draw the identifier pointer inside each entry. Which pointers still point to the old positions? Now move those arrows to the arrays inside the new positions. This is the purpose of rebinding.

Follow the `compaction` cases in `tests/test_registration_transactions.c` and `tests/test_service_registry_ownership.c`. They remove an entry and reuse the vacated slot before checking the surviving identifiers. This is stronger than checking only that the count became smaller.

A caller must also respect the API contract: a descriptor returned by `find` or `at` is borrowed. Reacquire it after catalogue mutation. Do not keep a pointer into movable registry storage and treat it as an everlasting identity.

## Who destroys the service object?

The registry copies names, but the service pointer still identifies the original object. With ordinary borrowed registration, the caller owns that object's lifetime. With `UMI_SERVICE_OWNED` and a destroy callback, the registry invokes the callback when the registration is removed or released.

In the service ownership fixture, `Describe` constructs a descriptor and `Destroy` counts destruction obligations. Those are helpers in the real test file, not public Framework API names. The objects are deliberately small so that the test can check exactly which object is destroyed and how many times.

Replacing a service with a different object should retire the old owned object after accepting the replacement. Replacing metadata for the very same object should not destroy that object and then keep its address. The `same-object` and `owned-replacement` cases distinguish these paths. An invalid replacement must not destroy the current object at all.

Changing an owned registration to borrowed registration for the same object also changes responsibility. The registry stops owning its eventual destruction. That is an explicit ownership transfer; it is not permission to abandon the object or leak its resources.

## Why callbacks cannot destroy the enclosing application

A destructor can call other code. If the registry holds its write mutex while calling the destructor, a callback that tries to change the registry again may wait for a lock already held by its own operation. A mutex is a lock used to protect a shared write. Waiting for yourself to release a lock is one form of deadlock.

The checked registry path runs destructors outside that mutex. It records that a destructor is active and refuses register, unregister and release operations during the callback. Read-only inspection follows the owner's serial access discipline. The callback must return normally; escaping through native thread termination is outside the contract.

The enclosing owner matters too. Studio's bootstrap owns the composition used by its frontends. A service destructor must not recursively destroy that bootstrap while cleanup is still using its state. Read `UmiStudioBootstrapRelease` in Studio's `src/app/bootstrap.c`. It refuses this reentry before it releases UI or background services.

A partly released owner is also different from a stopped application. Once destruction has begun, restarting it could use models that were already released. Framework and Studio retain a release-only state: the owner can retry closure, but cannot restart a partly destroyed graph. This is why a single “running” Boolean is not enough to describe every lifecycle stage.

## Build and inspect the focused checks

First use the [Windows development guide](../../umicom/windows-development.md) to prepare a configured Framework checkout. Run the following commands from that Framework directory. Use a separate terminal so that you can read each result. Stop when a command fails.

```powershell
cmake --build build/windows-ucrt64-debug --target umicom-registration-transactions-test umicom-service-ownership-test --parallel 2
ctest --test-dir build/windows-ucrt64-debug -R "^framework[.](registration[.]transaction|service[.]ownership)[.]" --output-on-failure --no-tests=error
```

The build tool still builds changed dependencies needed by these targets. A target does not mean “ignore dependency changes.” The test selection keeps this exercise focused on registry behaviour. A passing run reports each selected case as passed and returns success. These results do not prove that the whole Studio interface, every broker connection or every application workflow works.

If a target is unknown, check that the corresponding test source and its CMake registration are present in your checkout, then reconfigure using the repository's documented preset. If CTest finds no tests, check the build directory and whether testing was enabled. Do not treat an empty selection as a pass.

Keep the output log and the source revision used for the run. A source-reading conclusion, a successful compilation and a passing runtime test are different kinds of evidence.

## Check your understanding

1. A module's second capability conflicts. Should its first capability remain registered?
2. Why is an empty string different from the `NULL` at the end of a capability array?
3. Why can copying a structure leave an identifier pointer wrong?
4. Should replacing metadata for the same object call that object's destructor first?
5. Can a retained bootstrap restart after part of its release has succeeded?
6. Does a registry's write lock make every returned pointer safe for concurrent use?

Answers: (1) No; rejected admission leaves the original catalogue unchanged. (2) The empty string is an invalid name; `NULL` ends the array. (3) The pointer still names the old storage even when the character array moved. (4) No; the retained object must remain alive. (5) No; retry closure instead of using partly destroyed state. (6) No; borrowed-pointer lifetime and reader/writer ownership rules still apply.

For a final paper exercise, list three objects in a Studio workflow: a registry, a shared service and a view using that service. Write who owns each one, who borrows it, and what must finish before it can be destroyed. Compare your diagram with the real bootstrap and service registry source rather than assuming that closing a window ends every object lifetime.

[Read the Framework service ownership contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/runtime/service_registry.h)

<details><summary>Why is checking an error code alone not enough?</summary><p>An operation can report failure after changing part of its state. Check that the original catalogue is unchanged, then try corrected input. Both checks are needed to demonstrate a usable failure path.</p></details>

[Previous lesson](10-close-background-work.md) · [Course overview](index.md) · [Next: Inspect application services](12-inspect-application-services.md)
