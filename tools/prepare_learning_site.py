#!/usr/bin/env python3
"""Publish existing book and approved Framework branding assets into the MkDocs tree.

Original manuscripts and assets remain untouched in their source directories.
By default, this tool never overwrites a different published file.
"""

from __future__ import annotations

import argparse
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
CHAPTERS = (
    "introduction_to_islam.md",
    "history_of_money.md",
    "decline_of_sound_money.md",
    "modern_banking_and_finance.md",
    "technology_and_banking.md",
    "islamic_finance_and_future.md",
    "umicom_abs_coin.md",
    "governance_firewalls.md",
    "hall_of_shame_collaboration_and_betrayal.md",
    "recap.md",
)
IMAGES = (
    "islam_bookcover.png",
    "Diagram_Timeline_of_Money.png",
    "Diagram_Banks_Create_Money.png",
    "Diagram_2008_Crash.png",
    "Diagram_Riba_vs_Islamic.png",
    "Diagram_Tech_in_Banking.png",
    "Diagram_Umicom_ABS_Coin.png",
    "Diagram_Umicom_Issuance.png",
    "Diagram_Umicom_Circulation.png",
    "Diagram_Umicom_Redemption.png",
    "Poster_Quran_FairTrade.png",
    "Poster_Quran_Riba.png",
    "Poster_Hadith_HonestMerchant.png",
)
BRAND_FILES = (
    "umicom-icon.svg",
    "umicom-icon-on-dark.svg",
    "umicom-logo.svg",
    "umicom-logo-on-dark.svg",
    "umicom-icon.png",
    "umicom-logo.png",
    "umicom.ico",
)


def locate_brand(explicit: str | None) -> Path:
    if explicit:
        path = Path(explicit).expanduser().resolve()
        if not path.is_dir():
            raise FileNotFoundError(f"Brand directory not found: {path}")
        return path
    parent = ROOT.parent
    for path in (
        parent / "Umicom-Applications" / "framework" / "resources" / "brand",
        parent / "umicom-applications" / "framework" / "resources" / "brand",
        parent / "umicomOS" / "framework" / "resources" / "brand",
        ROOT / ".site-brand-framework" / "resources" / "brand",
    ):
        if path.is_dir():
            return path
    raise FileNotFoundError(
        "Umicom Framework brand not found. Use --brand-source PATH pointing "
        "to framework/resources/brand."
    )


def publish(source: Path, destination: Path, refresh: bool, *, remove_bom: bool = False) -> str:
    if not source.is_file():
        raise FileNotFoundError(f"Missing source: {source}")
    data = source.read_bytes()
    if remove_bom and data.startswith(b"\xef\xbb\xbf"):
        data = data[3:]
    if destination.is_file():
        if destination.read_bytes() == data:
            return "unchanged"
        if not refresh:
            return "different (preserved; use --refresh after reviewing)"
    destination.parent.mkdir(parents=True, exist_ok=True)
    destination.write_bytes(data)
    return "updated" if refresh else "added"


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--brand-source", help="Path to canonical Framework resources/brand directory")
    parser.add_argument("--refresh", action="store_true", help="Explicitly update published copies if the originals have changed")
    args = parser.parse_args(argv)

    volume_source = ROOT / "dropzone" / "documents" / "islam_blueprint_for_life"
    image_source = ROOT / "dropzone" / "images"
    try:
        brand_source = locate_brand(args.brand_source)
        assignments = [
            (volume_source / n, ROOT / "content" / "v001_islam_blueprint_for_life" / n, True)
            for n in CHAPTERS
        ]
        assignments += [
            (image_source / n, ROOT / "content" / "assets" / "books" / "islam" / n, False)
            for n in IMAGES
        ]
        assignments += [
            (brand_source / n, ROOT / "content" / "assets" / "branding" / n, False)
            for n in BRAND_FILES
        ]
        missing = [str(src) for src, _, _ in assignments if not src.is_file()]
        if missing:
            print("The following required source assets were not found:", file=sys.stderr)
            for path in missing:
                print(f"  {path}", file=sys.stderr)
            return 2
        for src, dst, remove_bom in assignments:
            result = publish(src, dst, args.refresh, remove_bom=remove_bom)
            print(f"{result}: {dst.relative_to(ROOT)}")
        print("Ready to validate and build the learning website.")
        return 0
    except (OSError, ValueError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
