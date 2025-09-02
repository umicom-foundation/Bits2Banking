@"
# Contributing Guide (Short & Friendly)

## Flow (How to help)
1. Create a new branch from `main`
2. Make a tiny change (even one sentence)
3. Build Volume 0 locally (see README)
4. Commit with a clear message (use “docs:” / “build:” / “fix:”)
5. Push and open a Pull Request (PR)

## Style
- Keep PRs small and focused
- Prefer Markdown in `chapters/`
- For scripts, include a header:
    - Created by: Sammy Hegab
    - Date: YYYY-MM-DD
- Section
    - Keep PRs small and focused
    - Use clear commit messages

## Local quick build
```powershell
pip install python-docx
python scripts\make_volume0_min.py
# or (if you edited chapters):
python scripts\make_volume0_from_md.py
