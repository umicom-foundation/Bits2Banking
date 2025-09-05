# Volumes — Index

Quick links to each volume, where to upload drafts, and where finalized Markdown lands.

> Upload chapters to `raw_docs/<slug>/`. The ingest bot mirrors/normalizes them into `content/volumes/<slug>/`.

| Volume | Slug | Upload here (raw) | Output (normalized Markdown) |
|---|---|---|---|
| Volume 0 — Project Intro | `volume-0` | <https://github.com/umicom-foundation/Bits2Banking/tree/main/raw_docs/volume-0> | <https://github.com/umicom-foundation/Bits2Banking/tree/main/content/volumes/volume-0> |
| Volume 1 — Introduction to Islam | `introduction-to-islam` | <https://github.com/umicom-foundation/Bits2Banking/tree/main/raw_docs/introduction-to-islam> | <https://github.com/umicom-foundation/Bits2Banking/tree/main/content/volumes/introduction-to-islam> |
| Volume 2 — Bits to Banking | `bits-to-banking` | <https://github.com/umicom-foundation/Bits2Banking/tree/main/raw_docs/bits-to-banking> | <https://github.com/umicom-foundation/Bits2Banking/tree/main/content/volumes/bits-to-banking> |

## How to add a new volume (quick)
1. Create a folder: `raw_docs/<your-volume-slug>/`
2. Add `.md`, `.docx`, or `.pdf` (optional: `bookcover_<Title>.png`)
3. Commit to `main` — the bot writes normalized `.md` into `content/volumes/<slug>/`

See: **[Quick Upload via raw_docs](CONTRIBUTING_RAW_DOCS.md)** for details.

