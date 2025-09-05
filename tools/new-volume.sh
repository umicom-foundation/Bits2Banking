#!/usr/bin/env bash
# Create a new volume scaffold for Bits2Banking
# Usage: bash tools/new-volume.sh <volume-slug>
# Slug must be lowercase letters, numbers, and hyphens.

set -euo pipefail

err() { printf "\nERROR: %s\n" "$*" >&2; exit 1; }

# 1) Validate working directory (must be repo root containing .git)
[ -d ".git" ] || err "Run this from the repository root (folder containing .git)."

# 2) Validate argument
if [ "${1-}" = "" ]; then
  err "Missing slug.\nUsage: bash tools/new-volume.sh <volume-slug>"
fi

SLUG="$1"
if ! [[ "$SLUG" =~ ^[a-z0-9]+(-[a-z0-9]+)*$ ]]; then
  err "Slug '$SLUG' is invalid. Use lowercase letters, numbers and hyphens only (e.g., generalist-ai)."
fi

# 3) Paths
RAW="raw_docs/$SLUG"
DST="content/volumes/$SLUG"
IMG="$DST/images"
PLACEHOLDER="$DST/ch00-$SLUG.md"

# 4) Create directories
mkdir -p "$RAW" "$IMG"

# 5) Add placeholder chapter if none exists
if [ ! -f "$PLACEHOLDER" ]; then
  TODAY="$(date +%Y-%m-%d)"
  cat > "$PLACEHOLDER" <<EOF
---
title: "$SLUG — placeholder"
volume: "$SLUG"
status: draft
source: "scaffold"
created: $TODAY
updated: $TODAY
tags: []
---

# $SLUG (placeholder)

This file was created by \`tools/new-volume.sh\`.
Upload chapters to **raw_docs/$SLUG/** as \`.md\`, \`.docx\`, or \`.pdf\`.
The ingest workflow will mirror/convert them into this folder.
EOF
fi

printf "Scaffolded:\n  %s\n  %s\n  %s\n" "$RAW" "$DST" "$IMG"
printf "Next: add files to raw_docs/%s/ and push to main.\n" "$SLUG"

