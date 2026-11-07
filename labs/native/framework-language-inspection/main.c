/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: main.c
 *
 * PURPOSE:
 *   Inspect document identities and file filters through Umicom Framework without opening files.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/document/languages.h"
#include "umicom/document/file_filter.h"
#include "umicom/editor/comment_style.h"
#include <stdio.h>

static int Inspect(const char *filename, const UmiDocumentFileFilterSet *filters)
{
    UmiDocumentLanguageIdentity identity;
    UmiStatus status = umi_document_language_detect(filename, &identity);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Cannot inspect name: status %d\n", (int)status);
        return 1;
    }
    printf("%s: %s\n", filename, identity.language_id);
    const UmiDocumentLanguageChoice *choice = NULL;
    status = UmiDocumentLanguageChoiceFind(identity.language_id, &choice);
    if (status == UMI_STATUS_OK) printf("  Choice: %s\n", choice->display_name);
    else if (status != UMI_STATUS_NOT_FOUND) return 1;
    const UmiEditorLineCommentStyle *style = NULL;
    status = UmiEditorLineCommentStyleFind(identity.language_id, &style);
    if (status == UMI_STATUS_OK) printf("  Line comment: %s\n", style->prefix);
    else if (status == UMI_STATUS_NOT_FOUND) puts("  Line comment: no shared profile");
    else return 1;
    for (size_t i = 0U; i < filters->count; ++i)
        if (umi_document_file_filter_matches(&filters->filters[i], filename))
            printf("  Filter: %s\n", filters->filters[i].name);
    return 0;
}

int main(int argc, char **argv)
{
    /* The description set is moderately large; static storage keeps this
     * single-threaded teaching tool independent of a small thread stack. */
    static UmiDocumentFileFilterSet filters;
    if (umi_document_file_filters_default(&filters) != UMI_STATUS_OK) return 1;
    if (argc < 2) {
        fputs("Usage: language-inspection <filename> [filename ...]\n", stderr);
        return 2;
    }
    for (int i = 1; i < argc; ++i)
        if (Inspect(argv[i], &filters) != 0) return 1;
    return 0;
}
