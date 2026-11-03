# Verify the guest environment

A service can run successfully while still having more access than intended. An operating system therefore needs to check both what the service did and the environment in which it ran. A user ID alone does not describe every permission a Linux process holds.

## Read the production boundary

1. Open `boot/foundation/supervisor.c` in Umicom OS. Find the group removal, user change, resource limits and `PR_SET_NO_NEW_PRIVS` call.
2. Open `guest_environment.h`. Its observation mask says which measurements succeeded. Missing measurements must not be interpreted as successful zero values.
3. Read `guest_environment.c`. The policy checks real and effective IDs, empty supplementary groups, privilege restrictions, limits, workspace ownership and mount restrictions.
4. Read `platform_check.c`. This is the Linux adapter: it gathers observations from the running guest and passes them to the policy.

## Understand three separate protections

Supplementary groups can grant file access even when the primary group is correct. The no-new-privileges setting prevents a later executable from granting additional privileges. Resource limits bound particular resources such as open descriptors and file output. These mechanisms complement each other; none makes arbitrary hostile software safe.

The private work directory must belong to the service user and group, have mode `0700`, and be the current working directory. The probe also checks the filesystem types and `nosuid,nodev,noexec` restrictions on proc, sys, run and tmp. This is the minimal guest's current contract, not a universal policy for every Linux desktop.

## Run a synthetic policy lab

Configure the existing OS boot-plan lab using lesson two, then build this focused target:

```text
cmake --build "C:\umicom\Umicom-Bits2Banking\build\os-boot-plan" --target btb-os-environment-tests
ctest --test-dir "C:\umicom\Umicom-Bits2Banking\build\os-boot-plan" -R "^bits2banking[.]os_environment[.]" --output-on-failure --no-tests=error
```

Expected result: the policy accepts the complete synthetic observation and rejects the missing measurement, extra group and executable temporary mount cases. This does not prove that Linux applied those restrictions. Only a separately recorded guest run exercises the production collector.

## Exercise and review

Add a case whose soft file limit is small but whose hard limit is unlimited. Explain why checking only the soft limit is insufficient: the process may raise it up to the hard limit. Then remove the workspace observation bit and verify that the policy reports incomplete evidence instead of an ownership failure.

<details>

<summary>Does a passed environment probe certify the OS?</summary>

No. It checks specific properties of one packaged service at one instant. It does not authenticate the image, inspect every service, establish hardware support or prove that a desktop is ready for daily use.

</details>

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/07-applications-os-and-kernel.md), then use the [connected learning map](../../../courses/learning-paths.html#os) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

[Next: keep service process and stream ownership](09-service-process-ownership.md)

---

[Read this lesson in HTML](../../../courses/umicom-os-from-scratch/lessons/08-guest-environment.html) · [Learning sequence](../../../start/learning-sequence.md)
