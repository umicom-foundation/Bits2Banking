![Umicom](../../../assets/branding/umicom-logo.svg)

# Qualify the installed client without confusing plans with execution

An installed-client lab checks the public SDK boundary. It consumes exported headers, libraries and CMake targets instead of compiling Framework implementation files into the example. This reveals installation and dependency mistakes that an in-tree test can miss, while keeping the lesson tied to the same public service used by applications.

## Prepare a matching installation

Follow the lab README with a complete Framework SDK containing compiler and toolchain components. Its headers and libraries must come from the same reviewed revision. The lab requires the new selection and synchronization APIs; an older SDK cannot satisfy that contract. Use a new build directory when comparing different SDK installations so cached package paths do not conceal the choice.

## Run the four scenarios

- storage checks well-formed metadata and unavailable conversion without output mutation.
- selection checks the profile/environment publication boundary and receiving pointer ownership.
- compiler checks repeated provider/profile replacement through the public bridge.
- pic checks an explicit argument mapping and unchanged output on an unsupported action.

CTest uses check.cmake to require exit status zero, empty standard error and the complete expected standard output. Each success line follows assertions in the native program. The check does not accept a partial banner as completion. The tool names are deliberately synthetic and are never launched by these scenarios.

## Separate the evidence layers

Successful configuration proves package discovery for that setup. Successful compilation proves declarations and linkage under that compiler. Passing scenarios prove their checked behavior for that binary. None of those results establishes that Studio’s menus work, a discovered real compiler can build your application, a GUI can launch or a shared library can load on every target.

## Recover from a failure

Stop at the first failing stage and retain its output. For a missing CMake target, inspect SDK selection and installed components. For an unresolved function, compare header/library identity. For a failed native assertion, retain the scenario name and expression, then compare the service contract and inputs. Do not print a success line to bypass the check or disable the failing scenario.

## Complete the exercise

Create an evidence sheet with SDK revision, installation path, host/compiler identity, configure/build/test exit results and the four scenario outcomes. Mark any unrun stage explicitly. Finish by describing one separate real-tool integration check and one GUI check you would need before claiming the IDE workflow works. The authored lab has no implied execution result; your recorded run supplies that evidence.

## Source and practice

Use the [installed C23 lab guide](../../../../labs/native/framework-toolchain-selection/README.md) and [complete source](../../../../labs/native/framework-toolchain-selection/main.c). The examples are authored; no build or execution result is implied.

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Express position-independent compilation as an explicit request](23-position-independent-compile-intent.md)

[HTML lesson](../../../courses/learning-build-systems/lessons/24-installed-toolchain-lab-qualification.html)

Sammy Hegab · Umicom Foundation · MIT
