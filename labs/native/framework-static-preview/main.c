/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-static-preview/main.c
 *
 * PURPOSE:
 *   Inspect a real rooted static-file response through Framework without opening a network port.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/web/preview.h"
#include "umicom/platform/native_arguments.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int InspectMain(int argc, char **argv)
{
    if (argc != 4) {
        fputs("Usage: btb-static-preview ABSOLUTE_ROOT GET|HEAD|POST /url-path\n", stderr);
        return 2;
    }
    UmiWebPreview *preview = NULL;
    UmiStatus status = UmiWebPreviewCreate(argv[1], 8080U, &preview);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Preview admission: %s\n", umi_status_text(status)); return 2;
    }
    UmiWebRequest *request = calloc(1U, sizeof(*request));
    UmiWebResponse *response = calloc(1U, sizeof(*response));
    unsigned char *wire = malloc(UMI_WEB_CONNECTION_RESPONSE_LIMIT);
    if (request == NULL || response == NULL || wire == NULL) {
        free(request); free(response); free(wire); UmiWebPreviewDestroy(preview); return 1;
    }
    /* A complete synthetic request exercises the canonical parser and gate.
     * It does not create a socket or bypass URL/Host policy with direct I/O. */
    char input[2048];
    int count = snprintf(input, sizeof(input), "%s %s HTTP/1.1\r\nHost: 127.0.0.1:8080\r\n\r\n",
        argv[2], argv[3]);
    if (count < 0 || (size_t)count >= sizeof(input)) status = UMI_STATUS_CAPACITY_EXCEEDED;
    else status = UmiWebRequestParseStrict(input, (size_t)count, sizeof(input), request);
    if (status == UMI_STATUS_OK) status = UmiWebPreviewHandle(preview, request, response);
    size_t wire_bytes = 0U;
    bool head = request->method == UMI_HTTP_METHOD_HEAD;
    if (status == UMI_STATUS_OK)
        status = UmiWebResponseFormatClosed(response, head, wire, UMI_WEB_CONNECTION_RESPONSE_LIMIT, &wire_bytes);
    if (status == UMI_STATUS_OK) {
        printf("HTTP %d\nrepresentation-bytes: %zu\nwire-bytes: %zu\nbody-sent: %s\n",
            response->status, response->body_length, wire_bytes, head ? "no" : "yes");
        for (size_t i = 0U; i < response->header_count; ++i)
            printf("%s: %s\n", response->headers[i].name, response->headers[i].value);
        /* Hex avoids treating binary data or terminal control bytes as text. */
        fputs("first-bytes:", stdout);
        size_t shown = response->body_length < 32U ? response->body_length : 32U;
        for (size_t i = 0U; i < shown; ++i) printf(" %02x", (unsigned)(unsigned char)response->body[i]);
        putchar('\n');
        if (ferror(stdout)) status = UMI_STATUS_IO_ERROR;
    } else fprintf(stderr, "Exchange inspection: %s\n", umi_status_text(status));
    free(wire); free(response); free(request); UmiWebPreviewDestroy(preview);
    return status == UMI_STATUS_OK ? 0 : 1;
}
int main(int argc, char **argv)
{
    int result = 1;
    UmiStatus status = UmiNativeArgumentsDispatch(argc, argv, InspectMain, &result);
    return status == UMI_STATUS_OK ? result : 1;
}
