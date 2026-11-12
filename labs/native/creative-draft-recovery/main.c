/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/creative-draft-recovery/main.c
 *
 * PURPOSE:
 *   Teach scene preparation, editable recovery and refused changes through installed Framework services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/creative_workspace/media_brief_document.h"
#include "umicom/creative_workspace/media_storyboard.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* This teaching client composes public services. Framework owns document shape,
 * Unicode admission, serialization and filesystem publication. Keep learner
 * experiments here so application code does not fork those shared policies. */
static UmiStatus CopyText(char *destination, size_t capacity, const void *bytes, size_t size)
{
    if (destination == NULL || bytes == NULL || size >= capacity ||
        memchr(bytes, 0, size) != NULL) return UMI_STATUS_CAPACITY_EXCEEDED;
    memcpy(destination, bytes, size);
    destination[size] = 0;
    return UMI_STATUS_OK;
}
static UmiStatus BuildStory(UmiMediaStoryboardDraft *draft, bool unresolved)
{
    UmiMediaStoryboardScene scene = {0};
    strcpy(scene.title, "The workshop opens");
    strcpy(scene.story, unresolved ? "Show @{workshop-image} as the door opens."
                                   : "Daylight reaches a workbench; a maker opens the door.");
    scene.duration_seconds = 8U;
    UmiStatus status = UmiMediaStoryboardAppend(draft, &scene);
    if (status != UMI_STATUS_OK) return status;
    strcpy(scene.title, "A careful measurement");
    strcpy(scene.story, "The maker measures a timber joint and records the result.");
    scene.duration_seconds = 10U;
    return UmiMediaStoryboardAppend(draft, &scene);
}
static UmiStatus BuildDocument(UmiMediaBriefDocument *out)
{
    UmiMediaStoryboardDraft story = {0};
    UmiMediaStoryboard *plan = NULL;
    UmiCreativeExport instructions = {0};
    UmiMediaBrief *brief = NULL;
    UmiMediaBriefDocument candidate = {0};
    candidate.draft.kind = UMI_MEDIA_BRIEF_VIDEO;
    strcpy(candidate.draft.title, "An introduction to the workshop");
    strcpy(candidate.draft.direction, "Use measured pacing; review references before rendering.");
    UmiStatus status = BuildStory(&story, false);
    if (status == UMI_STATUS_OK) status = UmiMediaStoryboardCreate(&story, NULL, 0U, &plan);
    if (status == UMI_STATUS_OK) status = UmiMediaStoryboardSceneInstructions(plan, 0U, &instructions);
    if (status == UMI_STATUS_OK)
        status = CopyText(candidate.draft.source, sizeof(candidate.draft.source),
                          instructions.bytes, instructions.size);
    if (status == UMI_STATUS_OK) status = UmiMediaBriefCreate(&candidate.draft, &brief);
    if (status == UMI_STATUS_OK) {
        const char *prompt = UmiMediaBriefPrompt(brief);
        status = CopyText(candidate.prompt, sizeof(candidate.prompt), prompt, strlen(prompt));
    }
    /* Commit the complete candidate only after every stage has succeeded.
     * Both exported instructions and the brief's borrowed prompt can now close:
     * the value document owns its copies, independently of either producer. */
    if (status == UMI_STATUS_OK) *out = candidate;
    UmiMediaBriefDestroy(brief);
    UmiCreativeExportFree(&instructions);
    UmiMediaStoryboardDestroy(plan);
    return status;
}
static bool SameDocument(const UmiMediaBriefDocument *a, const UmiMediaBriefDocument *b)
{
    return a->draft.kind == b->draft.kind &&
        strcmp(a->draft.title, b->draft.title) == 0 &&
        strcmp(a->draft.source, b->draft.source) == 0 &&
        strcmp(a->draft.direction, b->draft.direction) == 0 &&
        strcmp(a->prompt, b->prompt) == 0;
}
static UmiStatus RoundTrip(const UmiMediaBriefDocument *document, UmiMediaBriefDocument *out)
{
    UmiCreativeAsset *asset = NULL;
    const void *bytes = NULL;
    size_t size = 0U;
    UmiStatus status = UmiMediaBriefDocumentExport(document, NULL, &asset);
    if (status == UMI_STATUS_OK) status = UmiCreativeAssetBytes(asset, &bytes, &size);
    if (status == UMI_STATUS_OK) status = UmiMediaBriefDocumentImport(bytes, size, NULL, out);
    UmiCreativeAssetDestroy(asset);
    return status;
}
static UmiStatus Pipeline(void)
{
    UmiMediaBriefDocument document = {0}, restored = {0};
    UmiStatus status = BuildDocument(&document);
    if (status == UMI_STATUS_OK) status = RoundTrip(&document, &restored);
    if (status == UMI_STATUS_OK && !SameDocument(&document, &restored))
        status = UMI_STATUS_INVALID_STATE;
    if (status == UMI_STATUS_OK) {
        puts(restored.prompt);
        puts("Expected: scene instructions and prepared text survive a document round trip.");
        puts("No image, video, audio or provider request was produced.");
    }
    return status;
}
static UmiStatus Unfinished(void)
{
    UmiMediaBriefDocument document = {0}, restored = {0};
    strcpy(document.prompt, "Keep this opening idea while I choose a source.");
    UmiStatus status = RoundTrip(&document, &restored);
    UmiMediaBrief *prepared = NULL;
    UmiStatus preparation = UmiMediaBriefCreate(&restored.draft, &prepared);
    UmiMediaBriefDestroy(prepared);
    if (status == UMI_STATUS_OK &&
        (!SameDocument(&document, &restored) || preparation != UMI_STATUS_INVALID_ARGUMENT))
        status = UMI_STATUS_INVALID_STATE;
    if (status == UMI_STATUS_OK)
        puts("Expected: unfinished text recovers; preparing an empty title/source is refused.");
    return status;
}
static UmiStatus OwnedBytes(void)
{
    UmiMediaBriefDocument document = {0}, captured = {0}, restored = {0};
    UmiCreativeAsset *asset = NULL;
    const void *bytes = NULL;
    size_t size = 0U;
    UmiStatus status = BuildDocument(&document);
    if (status == UMI_STATUS_OK) {
        captured = document;
        status = UmiMediaBriefDocumentExport(&document, NULL, &asset);
    }
    strcpy(document.draft.source, "A later edit must not rewrite the exported asset.");
    strcpy(document.prompt, "A separately edited prompt.");
    if (status == UMI_STATUS_OK) status = UmiCreativeAssetBytes(asset, &bytes, &size);
    if (status == UMI_STATUS_OK) status = UmiMediaBriefDocumentImport(bytes, size, NULL, &restored);
    if (status == UMI_STATUS_OK && !SameDocument(&captured, &restored))
        status = UMI_STATUS_INVALID_STATE;
    UmiCreativeAssetDestroy(asset);
    if (status == UMI_STATUS_OK)
        puts("Expected: the asset retains its captured bytes after the source value changes.");
    return status;
}
static UmiStatus SourceChange(void)
{
    UmiMediaBriefDocument document = {0}, before = {0}, restored = {0};
    UmiMediaBrief *fresh = NULL;
    UmiStatus status = BuildDocument(&document);
    if (status == UMI_STATUS_OK) {
        before = document;
        strcpy(document.draft.source, "The workshop closes at sunset.");
        status = RoundTrip(&document, &restored);
    }
    if (status == UMI_STATUS_OK) status = UmiMediaBriefCreate(&restored.draft, &fresh);
    if (status == UMI_STATUS_OK &&
        (strcmp(restored.prompt, before.prompt) != 0 ||
         strcmp(restored.prompt, UmiMediaBriefPrompt(fresh)) == 0))
        status = UMI_STATUS_INVALID_STATE;
    UmiMediaBriefDestroy(fresh);
    if (status == UMI_STATUS_OK)
        puts("Expected: recovered edited text remains independent; review it against the changed source.");
    return status;
}
static UmiStatus Refused(void)
{
    static const char unsupported[] =
        "{\"format\":\"umicom-media-creation-draft\",\"version\":99,"
        "\"draft\":{\"kind\":\"video\",\"title\":\"new\",\"source\":\"new\",\"direction\":\"\"},"
        "\"prompt\":\"replacement\"}";
    UmiMediaBriefDocument document = {0}, before;
    UmiStatus status = BuildDocument(&document);
    if (status != UMI_STATUS_OK) return status;
    memcpy(&before, &document, sizeof(before));
    UmiStatus rejected = UmiMediaBriefDocumentImport(unsupported, sizeof(unsupported) - 1U,
                                                    NULL, &document);
    if (rejected == UMI_STATUS_OK || memcmp(&before, &document, sizeof(before)) != 0)
        return UMI_STATUS_INVALID_STATE;
    puts("Expected: a future document version is refused without changing any destination byte.");
    return UMI_STATUS_OK;
}
static UmiStatus Cancelled(void)
{
    UmiMediaBriefDocument document = {0}, before;
    UmiCreativeAsset *asset = NULL, *refused = NULL;
    UmiCancellationToken *token = NULL;
    const void *bytes = NULL;
    size_t size = 0U;
    UmiStatus status = BuildDocument(&document);
    memcpy(&before, &document, sizeof(before));
    if (status == UMI_STATUS_OK) status = UmiMediaBriefDocumentExport(&document, NULL, &asset);
    if (status == UMI_STATUS_OK) status = UmiCreativeAssetBytes(asset, &bytes, &size);
    if (status == UMI_STATUS_OK) status = umi_cancellation_token_create(&token);
    if (status == UMI_STATUS_OK) {
        umi_cancellation_token_request(token);
        UmiStatus exported = UmiMediaBriefDocumentExport(&document, token, &refused);
        UmiStatus imported = UmiMediaBriefDocumentImport(bytes, size, token, &document);
        if (exported != UMI_STATUS_CANCELLED || imported != UMI_STATUS_CANCELLED ||
            refused != NULL || memcmp(&before, &document, sizeof(before)) != 0)
            status = UMI_STATUS_INVALID_STATE;
    }
    UmiCreativeAssetDestroy(refused);
    UmiCreativeAssetDestroy(asset);
    umi_cancellation_token_destroy(token);
    if (status == UMI_STATUS_OK)
        puts("Expected: pre-requested cancellation produces no asset and preserves the destination.");
    return status;
}
static UmiStatus Unresolved(void)
{
    UmiMediaStoryboardDraft draft = {0}, restored = {0};
    UmiCreativeAsset *asset = NULL;
    UmiMediaStoryboard *plan = NULL;
    const void *bytes = NULL;
    size_t size = 0U;
    UmiStatus status = BuildStory(&draft, true);
    if (status == UMI_STATUS_OK) status = UmiMediaStoryboardDraftExport(&draft, NULL, &asset);
    if (status == UMI_STATUS_OK) status = UmiCreativeAssetBytes(asset, &bytes, &size);
    if (status == UMI_STATUS_OK) status = UmiMediaStoryboardDraftImport(bytes, size, NULL, &restored);
    if (status == UMI_STATUS_OK &&
        UmiMediaStoryboardCreate(&restored, NULL, 0U, &plan) != UMI_STATUS_NOT_FOUND)
        status = UMI_STATUS_INVALID_STATE;
    UmiMediaStoryboardDestroy(plan);
    plan = NULL;
    if (status == UMI_STATUS_OK) {
        UmiCreativeAssetLibraryEntry inventory = {0};
        strcpy(inventory.id, "workshop-image");
        strcpy(inventory.asset.label, "Workshop reference description");
        inventory.asset.declared_kind = UMI_CREATIVE_ASSET_IMAGE;
        status = UmiMediaStoryboardCreate(&restored, &inventory, 1U, &plan);
    }
    UmiMediaStoryboardDestroy(plan);
    UmiCreativeAssetDestroy(asset);
    if (status == UMI_STATUS_OK)
        puts("Expected: unresolved tags recover as text; preparation needs an explicit matching inventory.");
    return status;
}
static UmiStatus Bounds(void)
{
    UmiMediaBriefDocument document = {0};
    UmiCreativeAsset *asset = NULL;
    memset(document.draft.source, 'x', sizeof(document.draft.source));
    UmiStatus status = UmiMediaBriefDocumentExport(&document, NULL, &asset);
    bool refused_without_owner = status == UMI_STATUS_CAPACITY_EXCEEDED && asset == NULL;
    UmiCreativeAssetDestroy(asset);
    if (!refused_without_owner) return UMI_STATUS_INVALID_STATE;
    /* The storyboard output can exceed the smaller creation-source field. Refuse
     * the composition at that boundary; choose one scene rather than truncate. */
    UmiMediaStoryboardDraft draft = {0};
    UmiMediaStoryboardScene scene = {0};
    strcpy(scene.title, "A long scene");
    memset(scene.story, 'x', sizeof(scene.story) - 1U);
    scene.duration_seconds = 8U;
    status = UmiMediaStoryboardAppend(&draft, &scene);
    if (status == UMI_STATUS_OK) status = UmiMediaStoryboardAppend(&draft, &scene);
    UmiMediaStoryboard *plan = NULL;
    UmiCreativeExport instructions = {0};
    if (status == UMI_STATUS_OK) status = UmiMediaStoryboardCreate(&draft, NULL, 0U, &plan);
    if (status == UMI_STATUS_OK) status = UmiMediaStoryboardInstructions(plan, &instructions);
    if (status == UMI_STATUS_OK) {
        char destination[2049] = "Keep the existing source";
        char before[sizeof(destination)];
        memcpy(before, destination, sizeof(before));
        UmiStatus copy = CopyText(destination, sizeof(destination), instructions.bytes, instructions.size);
        if (copy != UMI_STATUS_CAPACITY_EXCEEDED || memcmp(before, destination, sizeof(before)) != 0)
            status = UMI_STATUS_INVALID_STATE;
    }
    UmiCreativeExportFree(&instructions);
    UmiMediaStoryboardDestroy(plan);
    if (status == UMI_STATUS_OK)
        puts("Expected: invalid storage and oversized composition are refused without truncation.");
    return status;
}
int main(int argc, char **argv)
{
    UmiStatus status = UMI_STATUS_INVALID_ARGUMENT;
    if (argc == 2 && strcmp(argv[1], "pipeline") == 0) status = Pipeline();
    else if (argc == 2 && strcmp(argv[1], "unfinished") == 0) status = Unfinished();
    else if (argc == 2 && strcmp(argv[1], "owned-bytes") == 0) status = OwnedBytes();
    else if (argc == 2 && strcmp(argv[1], "source-change") == 0) status = SourceChange();
    else if (argc == 2 && strcmp(argv[1], "refused") == 0) status = Refused();
    else if (argc == 2 && strcmp(argv[1], "cancel") == 0) status = Cancelled();
    else if (argc == 2 && strcmp(argv[1], "unresolved") == 0) status = Unresolved();
    else if (argc == 2 && strcmp(argv[1], "bounds") == 0) status = Bounds();
    else if (argc == 4 && strcmp(argv[1], "save") == 0 && strcmp(argv[3], "--replace") == 0) {
        UmiMediaBriefDocument document = {0};
        status = BuildDocument(&document);
        if (status == UMI_STATUS_OK) status = UmiMediaBriefDocumentSave(&document, argv[2], NULL);
        if (status == UMI_STATUS_OK) puts("Creation document saved at the selected absolute path.");
    } else if (argc == 4 && strcmp(argv[1], "open") == 0 &&
               strcmp(argv[3], "--replace-current") == 0) {
        UmiMediaBriefDocument document = {0};
        status = BuildDocument(&document);
        if (status == UMI_STATUS_OK) status = UmiMediaBriefDocumentLoad(argv[2], NULL, &document);
        if (status == UMI_STATUS_OK) {
            puts(document.draft.title);
            puts(document.prompt);
            puts("Recovered text requires review; no send or generation permission was restored.");
        }
    } else {
        fputs("usage: creative-draft-recovery pipeline|unfinished|owned-bytes|source-change|\n"
              "       refused|cancel|unresolved|bounds\n"
              "       creative-draft-recovery save ABSOLUTE_PATH --replace\n"
              "       creative-draft-recovery open ABSOLUTE_PATH --replace-current\n", stderr);
        return 2;
    }
    if (status != UMI_STATUS_OK) fprintf(stderr, "Recovery exercise failed: status %d\n", (int)status);
    return status == UMI_STATUS_OK ? 0 : 1;
}
