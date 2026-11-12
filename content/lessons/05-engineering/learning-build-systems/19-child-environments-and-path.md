![Umicom](../../../assets/branding/umicom-logo.svg)

# Prepare a child environment without changing the parent shell

A build process needs more than an executable name. Environment variables can choose a compiler, describe SDK locations or affect dependency lookup. Changing the parent shell globally makes later tasks depend on earlier tasks. An owned child-environment plan keeps each intended launch explicit and reviewable.

## Understand the two owners

UmiToolchainProfile owns discovery metadata. UmiEnvironmentPlan owns a bounded set of variable names and values, together with a process-facing pointer view. Preparing this plan does not launch a process or change the parent environment. A later launch operation must receive it and keep its storage alive for the required lifetime.

~~~c
UmiStatus status = umi_environment_plan_from_toolchain(profile, environment);
if (status != UMI_STATUS_OK) return status;
const char *compiler = umi_environment_plan_find(environment, "CC");
if (compiler == NULL) return UMI_STATUS_UNAVAILABLE;
~~~

The fragment belongs inside a status-returning function with valid caller-owned profile and environment pointers. CC is borrowed from the plan. Do not free it, and do not retain it across an operation that can replace or destroy that plan.

## Account for inherited PATH

When a profile supplies a bin directory, environment preparation can combine it with inherited PATH. The result must fit the declared capacity. An oversized inherited value can therefore prevent preparation even when the compiler path itself is short. An absent inherited PATH contributes no empty segment. A successful plan remains metadata; it does not prove the directory exists or the selected driver can execute.

## Make a repeatable experiment

The installed lab leaves bin_directory empty so its ownership checks do not depend on the host PATH length. It checks an explicit CC value instead. This is deliberate fixture design, not advice to omit search paths from a real project. A separate owner-run integration exercise should use the intended SDK directory and record the inherited environment assumptions.

## Exercise and recovery

- Explain why a newline-bearing compiler path can be stored as text yet refused as an environment value.
- Identify which operation prepares values and which future operation would execute a child.
- If preparation refuses a value, retain the prior plan, report the status and correct the input. Do not truncate PATH or overwrite the parent environment merely to obtain success.

## Source and practice

Use the [installed C23 lab guide](../../../../labs/native/framework-toolchain-selection/README.md) and [complete source](../../../../labs/native/framework-toolchain-selection/main.c). The examples are authored; no build or execution result is implied.

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Distinguish a stored profile from a usable compiler](18-profile-storage-and-tool-usability.md) · [Next: Publish the selected profile only after its environment is ready](20-publish-toolchain-selection.md)

[HTML lesson](../../../courses/learning-build-systems/lessons/19-child-environments-and-path.html)

Sammy Hegab · Umicom Foundation · MIT
