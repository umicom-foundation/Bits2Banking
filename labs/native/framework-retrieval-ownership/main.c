/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-retrieval-ownership/main.c
 *
 * PURPOSE:
 *   Demonstrate real Framework retrieval ownership, scoring and refused publication.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "umicom/ai/hybrid_retrieval.h"

/* The teaching executable runs one scenario serially. Large fixed owners stay
 * off the thread stack; concurrent applications need their own lifetime policy. */
static UmiAiVectorStore store;
static UmiAiVectorStore saved_store;
static UmiAiChunk chunks[3];
static UmiAiEmbedding embedding;
static UmiAiRetrievalResult results[4];
static UmiAiRetrievalResult saved_results[4];

static bool Require(bool condition, const char *description)
{
    if (!condition) fprintf(stderr, "Contract mismatch: %s\n", description);
    return condition;
}

static bool Prepare(void)
{
    const float values[] = {1.0F, 0.0F};
    umi_ai_vector_store_init(&store);
    return Require(umi_ai_chunk_set(&chunks[0], "guide", 0U, 0U, "target") == UMI_STATUS_OK,
                   "first chunk") &&
        Require(umi_ai_chunk_set(&chunks[1], "guide", 1U, 6U, "target target") == UMI_STATUS_OK,
                "second chunk") &&
        Require(umi_ai_chunk_set(&chunks[2], "guide", 2U, 19U, "other") == UMI_STATUS_OK,
                "third chunk") &&
        Require(umi_ai_embedding_set(&embedding, values, 2U) == UMI_STATUS_OK,
                "query embedding");
}

static bool ChunkOwnership(void)
{
    UmiAiChunk saved;
    if (!Require(umi_ai_chunk_set(&chunks[0], "guide", 0U, 0U, "sample") == UMI_STATUS_OK,
                 "initial chunk")) return false;
    if (!Require(umi_ai_chunk_set(&chunks[0], chunks[0].document_id, 7U, 10U,
                                  chunks[0].text + 1U) == UMI_STATUS_OK, "borrowed strings") ||
        !Require(strcmp(chunks[0].chunk_id, "guide:7") == 0 &&
                 strcmp(chunks[0].text, "ample") == 0 &&
                 chunks[0].start_offset == 10U && chunks[0].end_offset == 15U,
                 "published chunk identity and offsets")) return false;
    (void)memcpy(&saved, &chunks[0], sizeof(saved));
    if (!Require(umi_ai_chunk_set(&chunks[0], "guide", 8U, SIZE_MAX, "x") ==
                    UMI_STATUS_INVALID_ARGUMENT, "overflow refusal") ||
        !Require(memcmp(&saved, &chunks[0], sizeof(saved)) == 0,
                 "refused chunk unchanged")) return false;
    puts("Chunk: guide:7 at bytes 10..15");
    puts("Overflow refusal: previous chunk retained");
    return true;
}

static bool Geometry(void)
{
    const float directions[3][2] = {{2.0F,0.0F},{0.0F,3.0F},{-1.0F,0.0F}};
    const double expected[] = {1.0,0.0,-1.0};
    const float invalid[] = {1.0F,NAN};
    UmiAiEmbedding other;
    UmiAiEmbedding saved;
    if (!Prepare()) return false;
    for (size_t i = 0U; i < 3U; ++i) {
        if (!Require(umi_ai_embedding_set(&other, directions[i], 2U) == UMI_STATUS_OK,
                     "comparison embedding") ||
            !Require(fabs(umi_ai_embedding_cosine(&embedding, &other) - expected[i]) < 1e-12,
                     "cosine geometry")) return false;
    }
    (void)memcpy(&saved, &embedding, sizeof(saved));
    if (!Require(umi_ai_embedding_set(&embedding, invalid, 2U) == UMI_STATUS_INVALID_ARGUMENT,
                 "non-finite component refusal") ||
        !Require(memcmp(&saved, &embedding, sizeof(saved)) == 0,
                 "refused embedding unchanged")) return false;
    puts("Cosine: aligned 1, orthogonal 0, opposite -1");
    puts("Invalid component: previous embedding retained");
    return true;
}

static bool Lexical(void)
{
    if (!Prepare()) return false;
    if (!Require(umi_ai_retrieval_rank("target", chunks, 3U, results, 4U) == 2U,
                 "lexical match count") ||
        !Require(strcmp(results[0].chunk.chunk_id, "guide:1") == 0 &&
                 strcmp(results[1].chunk.chunk_id, "guide:0") == 0, "lexical match order"))
        return false;
    (void)memcpy(saved_results, results, sizeof(results));
    (void)memset(chunks[2].text, 'x', sizeof(chunks[2].text));
    if (!Require(umi_ai_retrieval_rank("target", chunks, 3U, results, 4U) == 0U,
                 "late malformed chunk refusal") ||
        !Require(memcmp(saved_results, results, sizeof(results)) == 0,
                 "lexical output unchanged")) return false;
    puts("Lexical order: guide:1, guide:0");
    puts("Malformed late chunk: output retained");
    return true;
}

static bool StoreAdmission(void)
{
    size_t index = SIZE_MAX;
    double score = 1234.0;
    if (!Prepare() || !Require(umi_ai_vector_store_add(&store, &chunks[0], &embedding) ==
                               UMI_STATUS_OK, "first stored entry")) return false;
    /* Deliberate isolated corruption demonstrates admission, not recovery. */
    store.count = UMI_AI_VECTOR_STORE_CAPACITY + 1U;
    (void)memcpy(&saved_store, &store, sizeof(store));
    if (!Require(!umi_ai_vector_store_valid(&store), "oversized count admission") ||
        !Require(umi_ai_vector_store_add(&store, &chunks[1], &embedding) ==
                    UMI_STATUS_INVALID_STATE, "refused addition") ||
        !Require(umi_ai_vector_store_search(&store, &embedding, &index, &score, 1U) == 0U,
                 "refused search") ||
        !Require(index == SIZE_MAX && score == 1234.0 &&
                 memcmp(&saved_store, &store, sizeof(store)) == 0,
                 "store and outputs unchanged")) return false;
    puts("Oversized store: refused");
    puts("Entry and output bytes: retained");
    return true;
}

static bool TopMatches(void)
{
    const float directions[4][2] = {{1.0F,0.0F},{0.0F,1.0F},{-1.0F,0.0F},{2.0F,0.0F}};
    UmiAiEmbedding value;
    size_t indices[3];
    double scores[3];
    if (!Prepare()) return false;
    for (size_t i = 0U; i < 4U; ++i) {
        if (!Require(umi_ai_embedding_set(&value, directions[i], 2U) == UMI_STATUS_OK,
                     "stored embedding") ||
            !Require(umi_ai_vector_store_add(&store, &chunks[0], &value) == UMI_STATUS_OK,
                     "stored entry")) return false;
    }
    if (!Require(umi_ai_vector_store_search(&store, &embedding, indices, scores, 3U) == 3U,
                 "top match count") ||
        !Require(indices[0] == 0U && indices[1] == 3U && indices[2] == 1U &&
                 scores[0] == 1.0 && scores[1] == 1.0 && scores[2] == 0.0,
                 "stable top match order")) return false;
    puts("Top matches: 0, 3, 1");
    puts("Tied scores: insertion order retained");
    return true;
}

static bool Hybrid(void)
{
    UmiAiHybridRetrievalSettings settings = umi_ai_hybrid_retrieval_settings_default();
    if (!Prepare() || !Require(umi_ai_vector_store_add(&store, &chunks[0], &embedding) ==
                               UMI_STATUS_OK, "hybrid entry")) return false;
    if (!Require(umi_ai_hybrid_retrieval_rank("target", chunks, 1U, &store, &embedding,
                    &settings, NULL, results, 4U) == 1U, "merged candidate count") ||
        !Require(fabs(results[0].score - 1.0) < 1e-12, "merged normalized score")) return false;
    (void)memcpy(saved_results, results, sizeof(results));
    settings.lexical_weight = DBL_MAX;
    settings.vector_weight = DBL_MAX;
    if (!Require(umi_ai_hybrid_retrieval_rank("target", chunks, 1U, &store, &embedding,
                    &settings, NULL, results, 4U) == 0U, "overflowed blend refused") ||
        !Require(memcmp(saved_results, results, sizeof(results)) == 0,
                 "hybrid output unchanged")) return false;
    puts("Combined candidate: score 1");
    puts("Overflowing blend: output retained");
    return true;
}

typedef struct RerankState {
    size_t calls;
    bool refuse_second;
} RerankState;

static double AdjustScore(const char *query, const UmiAiChunk *chunk,
                          double base_score, void *data)
{
    RerankState *state = data;
    (void)query;
    (void)chunk; /* Borrowed for this call; never retained by this client. */
    ++state->calls;
    if (state->refuse_second && state->calls == 2U) return NAN;
    return -base_score;
}

static bool Reranking(void)
{
    RerankState state = {0U,true};
    UmiAiReranker reranker = {AdjustScore,&state};
    if (!Prepare()) return false;
    for (size_t i = 0U; i < 2U; ++i) {
        results[i].chunk = chunks[i];
        results[i].score = (double)(i + 1U);
    }
    (void)memcpy(saved_results, results, sizeof(results));
    if (!Require(umi_ai_reranker_apply(&reranker, "target", results, 2U) ==
                    UMI_STATUS_INVALID_STATE, "late callback refusal") ||
        !Require(state.calls == 2U && memcmp(saved_results, results, sizeof(results)) == 0,
                 "callback calls observed, output retained")) return false;
    state.calls = 0U;
    state.refuse_second = false;
    if (!Require(umi_ai_reranker_apply(&reranker, "target", results, 2U) == UMI_STATUS_OK,
                 "finite reranking") ||
        !Require(state.calls == 2U && results[0].score == -1.0 && results[1].score == -2.0,
                 "descending negative scores")) return false;
    puts("Late callback refusal: 2 calls, output retained");
    puts("Finite reranking: scores -1, -2");
    return true;
}

int main(int argc, char **argv)
{
    bool success;
    if (argc != 2) {
        fputs("Choose chunk, geometry, lexical, store, top, hybrid or rerank.\n", stderr);
        return 2;
    }
    if (strcmp(argv[1], "chunk") == 0) success = ChunkOwnership();
    else if (strcmp(argv[1], "geometry") == 0) success = Geometry();
    else if (strcmp(argv[1], "lexical") == 0) success = Lexical();
    else if (strcmp(argv[1], "store") == 0) success = StoreAdmission();
    else if (strcmp(argv[1], "top") == 0) success = TopMatches();
    else if (strcmp(argv[1], "hybrid") == 0) success = Hybrid();
    else if (strcmp(argv[1], "rerank") == 0) success = Reranking();
    else {
        fputs("Unknown retrieval scenario.\n", stderr);
        return 2;
    }
    if (!success) return 1;
    puts("Local retrieval only; no model training or network request.");
    return 0;
}
