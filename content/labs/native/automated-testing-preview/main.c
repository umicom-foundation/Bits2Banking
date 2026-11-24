/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/automated-testing-preview/main.c
 *
 * PURPOSE:
 *   Preview a small test plan with the Framework SDK and observe refusal without dispatch.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/testing/uat_target.h"

#include <stdio.h>

/* The lesson's amount rule changes the caller's value only on admission. */
static bool admit_pennies(int input, int *out)
{
    if (out == NULL || input < 0) return false;
    *out = input;
    return true;
}

/* Any callback would contradict the preview contract. Counting it exposes an
 * unexpected dispatch without connecting to a device or ready application. */
static UmiStatus unexpected_dispatch(void *context, const UmiUatTarget *target,
    UmiUatOperation operation, const UmiTestCase *test, UmiCancellationToken *cancellation,
    UmiTestResult *result)
{
    (void)target;
    (void)operation;
    (void)test;
    (void)cancellation;
    (void)result;
    unsigned *calls = context;
    ++*calls;
    return UMI_STATUS_INVALID_STATE;
}

int main(void)
{
    /* Preserve a rejected caller value before checking the accepted value. */
    int amount = 77;
    if (admit_pennies(-1, &amount) || amount != 77) return 1;
    if (!admit_pennies(42, &amount) || amount != 42) return 2;

    const UmiUatTarget target = {
        UMI_UAT_TARGET_PROTOCOL, UMI_UAT_DESKTOP, "lesson.preview", "practice-1"
    };
    const UmiUatOperation operation = UMI_UAT_UNIT;
    UmiUatStep step = {.phase = UMI_UAT_ASSERT};
    umi_test_case_init(&step.test, "amount-unit", "Check the amount rule");
    if (umi_test_case_set_command(&step.test, "admission-preview-only", "", "") != UMI_STATUS_OK) return 3;
    step.test.timeout_ms = 1000U;

    unsigned calls = 0U;
    UmiUatDriver driver = {
        .binding = target,
        .supportedOperations = UMI_UAT_UNIT,
        .execute = unexpected_dispatch,
        .context = &calls
    };

    /* Check the same exact target and unit operation before varying one gate. */
    UmiUatTargetAdmission admission;
    if (UmiUatCheckTargetAdmission(&target, UMI_UAT_UNIT, &driver, &step, &operation, 1U, &admission) != UMI_STATUS_OK ||
        admission.gate != UMI_UAT_TARGET_ADMISSION_READY || admission.operationIndex != SIZE_MAX) return 4;

    driver.supportedOperations = UMI_UAT_UI_OBSERVE;
    if (UmiUatCheckTargetAdmission(&target, UMI_UAT_UNIT, &driver, &step, &operation, 1U, &admission) != UMI_STATUS_UNAVAILABLE ||
        admission.gate != UMI_UAT_TARGET_ADMISSION_OPERATION_UNAVAILABLE || admission.operationIndex != 0U ||
        admission.operation != UMI_UAT_UNIT) return 5;

    /* The adopter owns permission even if the configured adapter can execute. */
    driver.supportedOperations = UMI_UAT_UNIT;
    if (UmiUatCheckTargetAdmission(&target, UMI_UAT_UI_OBSERVE, &driver, &step, &operation, 1U, &admission) != UMI_STATUS_PERMISSION_DENIED ||
        admission.gate != UMI_UAT_TARGET_ADMISSION_OPERATION_DENIED || admission.operationIndex != 0U) return 6;
    if (calls != 0U) return 7;

    puts("Amount rule passed. Preview: ready, unavailable, denied. Adapter calls: 0.");
    return 0;
}
