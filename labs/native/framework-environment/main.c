/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-environment/main.c
 *
 * PURPOSE:
 *   Use installed Framework environment ownership without launching a child process.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/toolchain/environment.h"
#include "umicom/toolchain/kit_environment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A discovery can be structurally usable while its toolset is incomplete.
 * Framework keeps that distinction separate from rejected storage updates. */
static int PracticeKitUpdate(const char *scenario)
{
    UmiToolchainKitSnapshot *kit = calloc(1U, sizeof *kit);
    UmiCrossToolchainSnapshot *cross = calloc(1U, sizeof *cross);
    int result = 1;
    if (!kit || !cross) goto done;
    umi_toolchain_kit_init(kit, "kit.practice", "Practice kit");
    strcpy(kit->profile_id, "practice");
    strcpy(kit->host_triple, "native-host");
    strcpy(kit->target_triple, "native-host");
    strcpy(kit->sysroot, "sdk/target");
    if (!strcmp(scenario, "cross-partial")) {
        cross->struct_size = (uint32_t)sizeof *cross;
        cross->api_version = UMI_CROSS_TOOLCHAIN_API_VERSION;
        cross->state = UMI_CROSS_TOOLCHAIN_PARTIAL;
        strcpy(cross->target_triple, "synthetic-cross-target");
        strcpy(cross->compiler_path, "synthetic/cross-cc");
        UmiStatus status = umi_toolchain_kit_apply_cross_toolchain(kit, cross);
        if (status != UMI_STATUS_UNAVAILABLE || kit->state != UMI_TOOLCHAIN_KIT_DEGRADED ||
            kit->revision != 2U || strcmp(kit->target_triple, cross->target_triple)) goto done;
        puts("partial discovery retained; target=synthetic-cross-target; not ready");
    } else if (!strcmp(scenario, "kit-revision")) {
        kit->revision = UINT64_MAX;
        UmiStatus status = umi_toolchain_kit_set_sysroot(kit, "another/target");
        if (status != UMI_STATUS_CAPACITY_EXCEEDED || kit->revision != UINT64_MAX ||
            strcmp(kit->sysroot, "sdk/target")) goto done;
        puts("revision exhausted; sysroot=sdk/target");
    } else {
        UmiStatus status = umi_toolchain_kit_set_sysroot(kit, kit->sysroot + 4U);
        if (status != UMI_STATUS_OK || kit->revision != 2U || strcmp(kit->sysroot, "target")) goto done;
        puts("overlapping replacement; sysroot=target");
    }
    result = 0;
done:
    free(cross); free(kit);
    return result;
}

/* The application owns plans; Framework owns validation and composition.
 * Heap storage avoids placing several 200 KiB records on a thread's stack. */
int main(int argc, char **argv)
{
    const char *scenario = argc == 2 ? argv[1] : "compose";
    /* Admit the added kit scenarios while retaining the original exercise modes.
     * The previous argument gate is kept for engineering review. */
#if 0
    if (argc > 2 || (strcmp(scenario, "compose") && strcmp(scenario, "alias") &&
        strcmp(scenario, "refusal") && strcmp(scenario, "borrow") &&
        strcmp(scenario, "kit") && strcmp(scenario, "kit-refusal"))) {
        fputs("Use compose, alias, refusal, borrow, kit or kit-refusal.\n", stderr);
        return 2;
    }
#endif
    if (argc > 2 || (strcmp(scenario, "compose") && strcmp(scenario, "alias") &&
        strcmp(scenario, "refusal") && strcmp(scenario, "borrow") &&
        strcmp(scenario, "kit") && strcmp(scenario, "kit-refusal") &&
        strcmp(scenario, "cross-partial") && strcmp(scenario, "kit-revision") &&
        strcmp(scenario, "kit-overlap"))) {
        fputs("Use compose, alias, refusal, borrow, kit, kit-refusal, cross-partial, kit-revision or kit-overlap.\n", stderr);
        return 2;
    }
    if (!strcmp(scenario, "cross-partial") || !strcmp(scenario, "kit-revision") ||
        !strcmp(scenario, "kit-overlap")) return PracticeKitUpdate(scenario);
    UmiEnvironmentPlan *base = calloc(1U, sizeof *base);
    UmiEnvironmentPlan *overlay = calloc(1U, sizeof *overlay);
    UmiEnvironmentPlan *result = calloc(1U, sizeof *result);
    int exit_code = 1;
    if (!base || !overlay || !result) goto done;
    UmiStatus status = umi_environment_plan_add(base, "COURSE", "practice");
    if (status == UMI_STATUS_OK) status = umi_environment_plan_add(base, "MODE", "debug");
    if (status == UMI_STATUS_OK) status = umi_environment_plan_add(overlay, "MODE", "release");
    if (status != UMI_STATUS_OK) goto done;
    if (!strcmp(scenario, "kit") || !strcmp(scenario, "kit-refusal")) {
        UmiToolchainKitSnapshot *kit = calloc(1U, sizeof *kit);
        if (!kit) goto done;
        umi_toolchain_kit_init(kit, "kit.practice", "Practice kit");
        strcpy(kit->profile_id, "practice");
        strcpy(kit->target_triple, "synthetic-target");
        strcpy(kit->c_compiler, "kit-compiler");
        if (!strcmp(scenario, "kit-refusal")) {
            status = umi_environment_plan_add(result, "PREVIOUS", "retained");
            strcpy(kit->javac, "invalid\ncompiler");
        }
        if (status == UMI_STATUS_OK)
            status = umi_toolchain_kit_environment_plan(kit, NULL, result);
        free(kit);
        if (!strcmp(scenario, "kit-refusal")) {
            const char *old = umi_environment_plan_find(result, "PREVIOUS");
            if (status != UMI_STATUS_INVALID_ARGUMENT || !old || strcmp(old, "retained")) goto done;
            puts("refused malformed kit override; previous=retained");
        } else {
            if (status != UMI_STATUS_OK) goto done;
            const UmiEnvironmentVariable *variables = umi_environment_plan_variables(result);
            if (!variables) goto done;
            for (size_t i = 0; i < result->count; ++i)
                printf("%s=%s\n", variables[i].name, variables[i].value);
        }
    } else if (!strcmp(scenario, "refusal")) {
        status = umi_environment_plan_add(result, "PREVIOUS", "retained");
        if (status != UMI_STATUS_OK) goto done;
        /* Simulate a damaged public record; real clients should use setters. */
        memset(overlay->entries[0].value, 'x', sizeof overlay->entries[0].value);
        status = umi_environment_plan_compose(base, overlay, result);
        const char *old = umi_environment_plan_find(result, "PREVIOUS");
        if (status != UMI_STATUS_INVALID_ARGUMENT || !old || strcmp(old, "retained")) goto done;
        puts("refused malformed overlay; previous=retained");
    } else {
        UmiEnvironmentPlan *destination = !strcmp(scenario, "alias") ? base : result;
        status = umi_environment_plan_compose(base, overlay, destination);
        if (status != UMI_STATUS_OK) goto done;
        if (!strcmp(scenario, "borrow")) {
            /* The setter owns its input before replacing the same storage. */
            const char *old = umi_environment_plan_find(destination, "MODE");
            if (!old) goto done;
            status = umi_environment_plan_set(destination, "MODE", old + 2);
            if (status != UMI_STATUS_OK) goto done;
        }
        const UmiEnvironmentVariable *variables = umi_environment_plan_variables(destination);
        if (!variables) goto done;
        for (size_t i = 0; i < destination->count; ++i) {
            if (variables[i].name != destination->entries[i].name ||
                variables[i].value != destination->entries[i].value) goto done;
            /* Only synthetic non-secret values are printed in this exercise. */
            printf("%s=%s\n", variables[i].name, variables[i].value);
        }
    }
    exit_code = 0;
done:
    free(result); free(overlay); free(base);
    return exit_code;
}
