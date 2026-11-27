/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/web-method-response/read_route_methods.c
 *
 * PURPOSE:
 *   Compare the allowed methods and response statuses for a local practice file.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/web/static_files.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    UmiHttpMethod method;
    const char *name;
    const char *path;
} MethodCase;

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("Give the full path of the practice site folder.\n", stderr);
        return 2;
    }

    /* Framework owns the path policy and checks each file under this root. */
    UmiWebStaticFiles files;
    if (umi_web_static_files_init(&files, argv[1]) != UMI_STATUS_OK) {
        fputs("Use the full path of the practice site folder.\n", stderr);
        return 2;
    }

    /* Reuse the ordinary request and response records with no network listener. */
    UmiWebRequest *request = calloc(1U, sizeof *request);
    UmiWebResponse *response = calloc(1U, sizeof *response);
    if (request == NULL || response == NULL) {
        free(request);
        free(response);
        return 1;
    }

    const MethodCase cases[] = {
        { UMI_HTTP_METHOD_GET, "GET", "/handout.txt" },
        { UMI_HTTP_METHOD_HEAD, "HEAD", "/handout.txt" },
        { UMI_HTTP_METHOD_POST, "POST", "/handout.txt" },
        { UMI_HTTP_METHOD_GET, "GET", "/missing.txt" }
    };

    int result = 0;
    for (size_t index = 0U; index < sizeof cases / sizeof cases[0]; ++index) {
        const MethodCase *current = &cases[index];
        request->method = current->method;

        /* Set the method and path through the shared request contract. */
        if (umi_web_request_set_target(request, current->path) != UMI_STATUS_OK ||
            UmiWebStaticFilesHandle(request, response, &files) != UMI_STATUS_OK) {
            result = 1;
            break;
        }

        /* Display the returned status and the optional Allow field separately. */
        const char *allowed = "-";
        for (size_t field = 0U; field < response->header_count; ++field) {
            if (strcmp(response->headers[field].name, "Allow") == 0) {
                allowed = response->headers[field].value;
                break;
            }
        }
        if (printf("%s %s %d %s\n", current->name, current->path,
                   response->status, allowed) < 0) {
            result = 1;
            break;
        }
    }

    free(response);
    free(request);
    return (fflush(stdout) == 0) ? result : 1;
}
