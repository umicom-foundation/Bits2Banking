![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Learn how a build turns source into a usable program

A build is a sequence of steps that reads source files and produces artifacts:
object files, libraries, executables and reports. This course starts with those
words and works toward a shared native build service. You do not need to know
how to write a compiler before starting. Read the first lessons in order, then
use the later exercises to investigate a concrete build problem.

## Prepare your learning folder

1. Use a separate practice checkout or folder where you can inspect source and
   generated output without overwriting a working application.
2. Open a terminal and identify its current directory. A relative path is
   interpreted from that directory; the same command can reach a different file
   when run elsewhere.
3. Record the compiler, CMake and build-tool versions you actually selected.
   An installed executable and an executable found first on PATH need not be
   the same one.
4. Run each command separately and stop on a failure. Preserve its output before
   making the next change, so a later result can be tied to a particular source.

The early lessons use small files and dependency graphs. Later lessons explain
SDK boundaries, literal argument handling, profile selection and pointer
ownership in a native process launch. A stored profile or generated plan is not
evidence that a compiler or application ran. The installed-client exercises need
a matching Framework SDK and their own qualification.

## Work through the lessons

1. [Meet the tools and the files they produce](01-tools-and-artifacts.md)
1. [Read a build as a graph of dependencies](02-dependency-graph.md)
1. [Observe incremental work before changing the build](03-observe-incremental-work.md)
1. [Understand content changes and timestamp limits](04-content-and-timestamps.md)
1. [Give generated configuration one owner](05-generated-configuration.md)
1. [Run independent build jobs in parallel](06-parallel-jobs.md)
1. [Separate failed-test retries from affected-test selection](07-test-selection.md)
1. [Record enough evidence to understand a build result](08-record-build-identity.md)
1. [Use an SDK without rebuilding its source in every application](09-sdk-boundaries.md)
1. [Distinguish the computer building a program from its target](10-host-and-target.md)
1. [Compare builds as controlled experiments](11-reproducible-experiments.md)
1. [Connect an IDE to one shared build service](12-design-a-build-service.md)
1. [Pass a program its arguments without losing their boundaries](13-programs-and-argument-boundaries.md)
1. [Give a parser the exact bytes it may read](14-readable-spans-and-terminators.md)
1. [Keep the previous plan when a command edit is invalid](15-transactional-command-edits.md)
1. [Understand the task grammar and the shell boundary](16-task-grammar-and-shell-boundaries.md)
1. [Investigate command failures through focused regression checks](17-command-planning-regression-lab.md)
1. [Distinguish a stored profile from a usable compiler](18-profile-storage-and-tool-usability.md)
1. [Prepare a child environment without changing the parent shell](19-child-environments-and-path.md)
1. [Publish the selected profile only after its environment is ready](20-publish-toolchain-selection.md)
1. [Keep borrowed process pointers inside their receiving owner](21-environment-pointer-ownership.md)
1. [Replace a compiler provider and profile together](22-synchronize-compiler-selection.md)
1. [Express position-independent compilation as an explicit request](23-position-independent-compile-intent.md)
1. [Qualify the installed client without confusing plans with execution](24-installed-toolchain-lab-qualification.md)

Keep a short record of the command, source revision, output directory and observed status for each exercise. Explain a failure in terms of its stage—configuration, compilation, linking, loading or testing—before changing unrelated settings.

1. [Detect incomplete source before a long compilation](25-detect-incomplete-source-before-compilation.md)

1. [Recognize stale tests after a failed build](26-recognize-stale-tests-after-a-failed-build.md)

1. [Check available storage before building](27-check-available-storage-before-building.md)
1. [Read a Ninja progress record](28-read-a-ninja-progress-record.md)
1. [See which library Ninja will link](29-see-which-library-ninja-will-link.md)
1. [Match a dry plan to its recipe digest](30-match-a-dry-plan-to-its-recipe-digest.md)
1. [Measure the process temporary volume](31-measure-the-process-temporary-volume.md)
1. [Read child and fixture deadlines](32-read-child-and-fixture-deadlines.md)
