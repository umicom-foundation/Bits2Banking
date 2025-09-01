r"""
#Created by: Sammy Hegab
#Date: 01-09-2025
make_cover_variants.py
Create print-ready covers from a source image, saved into C:\Bits2Banking\bookcover\
- A4 portrait @ 300 DPI (2480×3508 px)
- 6×9 in + 0.125" bleed (6.125×9.25) @ 300 DPI (1838×2775 px)
- Optional A4 SVG page that embeds the PNG and draws trim/safe guides.

Run:
  python C:\Bits2Banking\scripts\make_cover_variants.py
"""

from pathlib import Path
import argparse, base64
from PIL import Image, ImageOps, ImageFilter

ROOT = Path(r"C:\Bits2Banking")
DEFAULT_SRC = ROOT / r"images\bits2banking-book_cover.png"
OUT_DIR = ROOT / "bookcover"   # <— changed from volumes/ to bookcover/

A4_W, A4_H = 2480, 3508        # A4 portrait @300DPI
W6x9, H6x9 = 1838, 2775        # 6.125" x 9.25" @300DPI (with bleed)

def prepare(img: Image.Image, w: int, h: int) -> Image.Image:
    img = img.convert("RGB")
    img = img.filter(ImageFilter.UnsharpMask(radius=2.0, percent=120, threshold=3))
    return ImageOps.fit(img, (w, h), method=Image.LANCZOS, centering=(0.5, 0.5))

def write_png(im: Image.Image, path: Path):
    path.parent.mkdir(parents=True, exist_ok=True)
    im.save(path, dpi=(300, 300), optimize=True)

def write_svg_with_png_embed(png_path: Path, svg_path: Path):
    b64 = base64.b64encode(png_path.read_bytes()).decode("ascii")
    svg = f'''<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="210mm" height="297mm" viewBox="0 0 210 297">
  <defs>
    <style>
      .safe {{ fill: none; stroke: #00BFFF; stroke-width: 0.2; stroke-dasharray: 1 1; }}
      .trim {{ fill: none; stroke: #FF3B30; stroke-width: 0.2; stroke-dasharray: 1 1; }}
      .label {{ font: 3px monospace; fill: #444; }}
    </style>
  </defs>
  <image x="0" y="0" width="210" height="297" href="data:image/png;base64,{b64}"/>
  <rect x="0" y="0" width="210" height="297" class="trim"/>
  <rect x="3" y="3" width="204" height="291" class="safe"/>
  <text x="4" y="10" class="label">A4 210×297 mm @ 300 DPI</text>
</svg>
'''
    svg_path.write_text(svg, encoding="utf-8")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--src", default=str(DEFAULT_SRC), help="Path to source cover image")
    ap.add_argument("--a4", action="store_true", help="Only A4 PNG")
    ap.add_argument("--six9", action="store_true", help="Only 6x9+bleed PNG")
    ap.add_argument("--svg", action="store_true", help="Only SVG wrapper")
    args = ap.parse_args()

    src = Path(args.src)
    if not src.exists():
        raise SystemExit(f"Source cover not found:\n  {src}")

    im = Image.open(src)
    only = args.a4 or args.six9 or args.svg

    if args.a4 or not only:
        a4_img = prepare(im, A4_W, A4_H)
        out_a4 = OUT_DIR / "Bits_to_Banking_Cover_A4_300dpi.png"
        write_png(a4_img, out_a4)
        print("Wrote:", out_a4)

    if args.six9 or not only:
        six_img = prepare(im, W6x9, H6x9)
        out_6x9 = OUT_DIR / "Bits_to_Banking_Cover_6x9_bleed_300dpi.png"
        write_png(six_img, out_6x9)
        print("Wrote:", out_6x9)

    if args.svg or not only:
        out_a4 = OUT_DIR / "Bits_to_Banking_Cover_A4_300dpi.png"
        if not out_a4.exists():
            a4_img = prepare(im, A4_W, A4_H)
            write_png(a4_img, out_a4)
        out_svg = OUT_DIR / "Bits_to_Banking_Cover_A4_300dpi.svg"
        write_svg_with_png_embed(out_a4, out_svg)
        print("Wrote:", out_svg)

if __name__ == "__main__":
    main()
