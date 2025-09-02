import json, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
toc_file = ROOT / "toc.json"

if not toc_file.exists():
    print("toc.json not found (skipping validation).")
    sys.exit(0)

try:
    raw = toc_file.read_text(encoding="utf-8-sig")  # tolerate BOM
    toc = json.loads(raw)
except Exception as e:
    print("Invalid toc.json:", e)
    sys.exit(1)

missing = []

# Prefer the simple "volume0" list if present
if "volume0" in toc and isinstance(toc["volume0"], list):
    for item in toc["volume0"]:
        p = ROOT / item["path"]
        if not p.exists():
            missing.append(str(p))
else:
    # Otherwise, accept your "volumes" schema and just pass (no chapter list provided)
    print("No 'volume0' list in toc.json; skipping strict chapter checks.")

if missing:
    print("Missing files referenced by toc.json:")
    for m in missing:
        print(" -", m)
    sys.exit(1)

print("toc.json OK")
