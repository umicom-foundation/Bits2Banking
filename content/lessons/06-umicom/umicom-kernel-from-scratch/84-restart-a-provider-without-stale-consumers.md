# Restart a provider without stale consumers

## Dependencies refer to live instances

A consumer depends on a healthy provider instance, not merely a familiar service name. When the provider is revoked, consumers must lose eligibility before another user quantum is selected. Otherwise they may continue with a stale assumption.

The controller propagates dependency loss, cancels affected work and collects old owners before admitting replacements. Cleanup follows reverse dependency order so consumers are released before their prerequisites.

## Worked restart

Provider identity 7 and consumer identity 8 are healthy. Restarting the provider first marks affected records unavailable. Cleanup releases the old instances. Only after that succeeds may new identities appear. The name can remain the same; identity and report sequence establish that the new instance is different.

If a frame release fails, the controller retains the relevant handle and returns a cleanup failure. It does not reset the owner to conceal the failure. A retry resumes cleanup rather than admitting overlapping generations.

## Read the implementation

1. Trace ServiceManagerRestart into the stop and propagation helpers.
2. Find the reverse-order loop in cleanup.
3. Identify where a retained failed load is reaped.
4. Find the condition that permits BACKOFF and another attempt.
5. Explain how exhausted attempts affect a required service.

The source and [managed-service tests](https://github.com/umicom-foundation/umicom-kernel/tree/main/tests/managed_services) provide concrete examples. The samples called clock-sample and consumer-sample demonstrate health reporting; their names do not establish complete production clock or consumer services.

## Exercise and answer

Cleanup fails after the old consumer has stopped but before the provider's frames are released. May the replacement start because no user code is running? Answer: no. Retained memory and ownership must still be accounted for. Starting early could overlap resource lifetimes or lose the only recovery handle.

## Verification

An owner-run regression should inject a release refusal, verify that no replacement enters, retry cleanup and confirm identities change only after collection. Separately run the guest controller sequence to exercise native entry. Neither execution was performed while authoring this lesson.

[Course contents](index.md)
