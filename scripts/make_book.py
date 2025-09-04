#!/usr/bin/env python3
import argparse, os, sys, yaml, subprocess, pathlib, datetime

ROOT = pathlib.Path(__file__).resolve().parent.parent
CONTENT = ROOT / "content"
BOOKDIR = ROOT / "book"
COVER = ROOT / "images" / "islam_bookcover.png"

def run(cmd):
    print("+", " ".join(cmd))
    subprocess.check_call(cmd)

def main():
    p = argparse.ArgumentParser()
    p.add_argument("--volume", default="v001_islam_blueprint_for_life")
    p.add_argument("--cover", default=str(COVER))
    args = p.parse_args()

    vol_dir = CONTENT / args.volume
    vol_meta = vol_dir / "volume.yml"
    if not vol_meta.exists():
        print(f"Missing: {vol_meta}", file=sys.stderr)
        sys.exit(2)

    with open(vol_meta, "r", encoding="utf-8") as fh:
        meta = yaml.safe_load(fh)

    title = meta.get("title", args.volume)
    author = meta.get("author", "Umicom Foundation")
    chapters = [vol_dir / ch for ch in meta["chapters"]]

    # Combined markdown (add a title page with cover)
    BOOKDIR.mkdir(exist_ok=True)
    combined = BOOKDIR / f"{args.volume}_combined.md"
    with open(combined, "w", encoding="utf-8") as out:
        out.write(f"---\n")
        out.write(f'title: "{title}"\n')
        out.write(f'author: "{author}"\n')
        out.write(f'date: "{datetime.date.today().isoformat()}"\n')
        out.write(f"---\n\n")
        if os.path.exists(args.cover):
            rel = os.path.relpath(args.cover, BOOKDIR)
            out.write(f'![cover]({rel}){{width=100%}}\n\n')
            out.write('<div style="page-break-after: always;"></div>\n\n')
        # stitch chapters in declared order
        for ch in chapters:
            out.write(f"\n\n<div style=\"page-break-after: always;\"></div>\n\n")
            with open(ch, "r", encoding="utf-8") as cf:
                out.write(cf.read())
                out.write("\n")

    pdf_out = BOOKDIR / f"{args.volume}.pdf"
    epub_out = BOOKDIR / f"{args.volume}.epub"

    # Build EPUB (uses cover automatically via --epub-cover-image)
    run([
        "pandoc", str(combined),
        "-o", str(epub_out),
        "--toc",
        "--epub-cover-image", args.cover,
        "--standalone"
    ])

    # Build PDF (wkhtmltopdf engine keeps it lightweight)
    run([
        "pandoc", str(combined),
        "-o", str(pdf_out),
        "--toc",
        "--standalone",
        "--pdf-engine=wkhtmltopdf"
    ])

    print(f"\nEPUB: {epub_out}\nPDF : {pdf_out}")

if __name__ == "__main__":
    main()

