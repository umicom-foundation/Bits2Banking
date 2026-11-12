/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: status_driver.c
 *
 * PURPOSE:
 *   Adapt an original bounded read-only example to the MINIX 3.3.0 character-driver API.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <minix/drivers.h>
#include <minix/chardriver.h>
#include <minix/sef.h>
#include <errno.h>
#include "read_window.h"
#include "read_reply.h"

/* Original read-only learning driver for the v3.3.0 character-driver API.
 * No device I/O, interrupt, persistent counter or live-update state is owned. */
static const char status_text[] = "Umicom learning status: ready\n";
static int status_open(devminor_t minor, int access, endpoint_t endpoint)
{
    (void)access;
    (void)endpoint;
    return minor == 0 ? OK : ENXIO;
}
static int status_close(devminor_t minor)
{
    return minor == 0 ? OK : ENXIO;
}
/* The earlier inline read implementation is retained for comparison with the
 * original release-specific example. The active adapter delegates portable
 * bounds and outcome publication to read_reply, preserving the same grant API. */
#if 0
static ssize_t status_read(devminor_t minor, u64_t position, endpoint_t endpoint,
    cp_grant_id_t grant, size_t requested, int flags, cdev_id_t id)
{
    size_t offset = 0, count = 0;
    (void)flags;
    (void)id;
    if (minor != 0) return ENXIO;
    if (!umi_learning_read_window((uint64_t)position, requested,
            sizeof(status_text) - 1, &offset, &count))
        return EINVAL;
    if (count == 0) return 0;
    const int result = sys_safecopyto(endpoint, grant, 0,
        (vir_bytes)(status_text + offset), count);
    return result == OK ? (ssize_t)count : result;
}
#endif

typedef struct StatusCopyContext {
    endpoint_t endpoint;
    cp_grant_id_t grant;
} StatusCopyContext;

static int status_copy(void *opaque, const char *source, size_t count)
{
    const StatusCopyContext *context = opaque;
    /* The endpoint and grant belong to this request. No grant is retained after
     * the synchronous callback; the destination starts at grant offset zero. */
    return sys_safecopyto(context->endpoint, context->grant, 0,
        (vir_bytes)source, count);
}
static ssize_t status_read(devminor_t minor, u64_t position, endpoint_t endpoint,
    cp_grant_id_t grant, size_t requested, int flags, cdev_id_t id)
{
    StatusCopyContext context = {endpoint, grant};
    UmiLearningReadReply reply;
    UmiLearningReadResult result;
    (void)flags;
    (void)id;
    if (minor != 0) return ENXIO;
    result = umi_learning_read_reply(status_text, sizeof(status_text) - 1,
        (uint64_t)position, requested, status_copy, &context, &reply);
    if (result == UMI_LEARNING_READ_INVALID) return EINVAL;
    if (result == UMI_LEARNING_READ_COPY_FAILED) return reply.copy_status;
    /* The fixed response is shorter than ssize_t's positive range. General
     * variable-size services must establish their own representability bound. */
    return (ssize_t)reply.bytes;
}
static int status_init(int type, sef_init_info_t *info)
{
    (void)type;
    (void)info;
    chardriver_announce();
    return OK;
}
static struct chardriver operations = {
    .cdr_open = status_open,
    .cdr_close = status_close,
    .cdr_read = status_read
};
int main(void)
{
    sef_setcb_init_fresh(status_init);
    sef_setcb_init_restart(status_init);
    /* No live-update callback is registered: that protocol is not implemented. */
    sef_startup();
    chardriver_task(&operations);
    return OK;
}
