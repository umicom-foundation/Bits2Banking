# Copy one owned service observation

## Why diagnostics need an owner

A status panel should not walk live kernel records while callbacks or scheduling can change them. Even correct individual fields become misleading if a phase comes from one step and service states come from another.

UmicomKernelServiceManagerSnapshot copies phase, count, the last observed clock and service information into caller-owned storage. The structure contains values, not handles, ELF pointers or callbacks. Existing Query remains available for a single service.

~~~c
UmicomKernelManagedServiceSnapshot snapshot;
UmicomKernelServiceManagerStatus result =
    UmicomKernelServiceManagerSnapshot(&manager, &snapshot);
~~~

Check result before reading snapshot. On refusal, the output remains unchanged. On success, unused service slots are zeroed. The output must not overlap manager storage.

## Serialization is part of the contract

Call between user quanta on the serialized owner thread. This is not an SMP lock or an atomic publication mechanism for arbitrary concurrent readers. A callback during an active operation receives BUSY. Closed or unsafe managers can still be inspected, but a diagnostic copy grants no permission to restart them.

The timestamp is the controller's last observation, not a new clock sample. A previously copied HEALTHY record remains a historical observation after restart; it must not authorize a new dependent operation.

## Worked example

Capture a healthy two-service snapshot. Request provider restart. The old copy remains unchanged, while a fresh snapshot shows revoked readiness. That distinction makes reports reproducible without pretending the old state remains current.

## Exercise and answer

A UI stores the snapshot and later decides to admit work because phase was HEALTHY. What is missing? Answer: a current decision through the owning controller. The snapshot is evidence, not authority.

## Regression route

The authored owned-snapshot and snapshot-refusal cases check independent copies, restart visibility, closed state, zero unused slots and unchanged output on refusal. Callback-reentry also checks BUSY. Run the managed-service suite through the Kernel's documented owner procedure; these additions have only been statically reviewed. Extend the model without treating a host test as proof of RISC-V boot or hardware correctness.

[Course contents](index.md)

[Next lesson](86-encode-a-boot-handoff-through-the-kernel.md)
