# volume0_one_click.py
# Purpose: One-click scaffold + build Volume 0 and Master Book, then commit (and optionally push)
# Created by: Sammy Hegab
# Date: 2025-09-01

from pathlib import Path
from datetime import datetime
import argparse, json, re, subprocess, sys

ROOT         = Path(r"C:\Bits2Banking")
V0_DIR       = ROOT / r"chapters\v00_source_control"
TOC_PATH     = ROOT / "toc.json"
VOLUMES_DIR  = ROOT / "volumes"
BOOK_DIR     = ROOT / "book"
IMAGES_DIR   = ROOT / "images"
COVER_DIR    = ROOT / "bookcover"
COVER_A4     = COVER_DIR / "Bits_to_Banking_Cover_A4_300dpi.png"
COVER_SRC    = IMAGES_DIR / "Book cover for bit to Banking.png"
VOL0_ID      = "v00_source_control"
VOL0_TITLE   = "Volume 0 — Source Control & Collaboration"
VOL0_DOCX    = VOLUMES_DIR / "Volume_00_Source_Control.docx"
MASTER_DOCX  = BOOK_DIR / "Bits_to_Banking_Master_Book.docx"

# --- deps ---
def pip_install(pkg):
    subprocess.check_call([sys.executable, "-m", "pip", "install", pkg])

try:
    from PIL import Image, ImageOps, ImageFilter
except ImportError:
    pip_install("pillow")
    from PIL import Image, ImageOps, ImageFilter

try:
    from docx import Document
    from docx.shared import Pt, Inches
    from docx.enum.style import WD_STYLE_TYPE
    from docx.enum.section import WD_SECTION_START
    from docx.enum.text import WD_ALIGN_PARAGRAPH
    from docx.oxml import OxmlElement
    from docx.oxml.ns import qn
except ImportError:
    pip_install("python-docx")
    from docx import Document
    from docx.shared import Pt, Inches
    from docx.enum.style import WD_STYLE_TYPE
    from docx.enum.section import WD_SECTION_START
    from docx.enum.text import WD_ALIGN_PARAGRAPH
    from docx.oxml import OxmlElement
    from docx.oxml.ns import qn

# --- content (RAW strings to avoid backslash escape issues) ---
FILES = {
"ch00_prelude.md": r"""# Volume 0 Prelude — Recap & Setup

## Why this volume
We set up Git, GitHub, Pull Requests, reviews, and a small CI that builds the book.

## Prerequisites
Windows 10/11 • Internet • ~5–10 GB free.

## Tools
Git + GitHub CLI (gh) • Python 3.11+ • VS Code • PowerShell (5.1 or 7+)

## Layout
C:\Bits2Banking\ (chapters, scripts, volumes, book, bookcover, images, toc.json)


