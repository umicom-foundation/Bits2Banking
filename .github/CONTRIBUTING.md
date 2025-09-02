# Contributing to Bits to Banking

Welcome 👋 and thank you for your interest in helping us build this open book project!  
We want **beginners to feel comfortable** making their first contribution, so here are very simple steps.

---

## Quick Start for Contributions

### 1. Fork & Clone
1. Click the **Fork** button (top right of GitHub).  
2. Clone your fork to your computer:
   ```powershell
   git clone https://github.com/<your-username>/Bits2Banking.git C:\Bits2Banking
   cd C:\Bits2Banking
   ```

### 2. Create a Branch
Make a new branch for your change:
```powershell
git checkout -b feat/my-chapter
```

### 3. Write or Edit a Chapter
- All chapters are in `chapters/v00/` (Volume 0).  
- Start your file with a heading:
  ```markdown
  # My New Chapter
  A short intro goes here.
  ```
- Keep it simple: headings, paragraphs, lists, and code fences.

### 4. Build Locally
Check your changes before sending them:
```powershell
python scripts\make_volume0_from_md.py
```
Open the output file:
```powershell
start .\volumes\Volume_00_Source_Control.docx
```

### 5. Commit & Push
```powershell
git add chapters/v00/my_new_chapter.md
git commit -m "feat: add my new chapter"
git push origin feat/my-chapter
```

### 6. Open a Pull Request
- Go to your fork on GitHub.  
- Click **Compare & Pull Request**.  
- Describe your change briefly.

CI will build your changes and attach the `.docx` file for reviewers.

---

## Style Guide (Simple Rules)

- Use `#` for chapter titles, `##` for subsections.  
- Write in clear, beginner-friendly English.  
- Keep paragraphs short (2-3 sentences).  
- Lists should have a blank line above them.  
- Use code fences with language, e.g.:
  ```python
  print("Hello world")
  ```

---

## Community & Conduct

We value:
- Respect and patience (everyone is learning).  
- Contributions of all sizes (fix a typo, add a paragraph, or write a chapter).  
- Transparency — all donations and outputs go directly to help civilians in need.  

If you’re unsure about anything, open a **Discussion** or ask in your Pull Request.  

---

## Thank You 💙

Every contribution brings us closer to:
- A complete, open computing & finance guide.  
- Funding education and relief for civilians suffering in Gaza.  
- Building a community that values knowledge and humanity.
