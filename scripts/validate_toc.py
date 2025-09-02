import json, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
toc_file = ROOT / "toc.json"

if not toc_file.exists():
    print("toc.json not found (skipping validation).")
    sys.exit(0)

try:
    toc = json.loads(toc_file.read_text(encoding="utf-8"))
except Exception as e:
    print("Invalid toc.json:", e)
    sys.exit(1)

missing = []
# Expect structure like: {"volume0": [{"path":"chapters/v00/001-introduction.md"}]}
for item in toc.get("volume0", []):
    p = ROOT / item["path"]
    if not p.exists():
        missing.append(str(p))

if missing:
    print("Missing files referenced by toc.json:")
    for m in missing:
        print(" -", m)
    sys.exit(1)

print("toc.json OK")
