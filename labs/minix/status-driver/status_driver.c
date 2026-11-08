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
