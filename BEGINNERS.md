# BEGINNERS — How to add your words to the book (super easy)

> No coding needed. If you can type a paragraph, you can contribute.  
> This guide is for **absolute beginners** (kids and adults).

---

## 🧠 What you’ll do
You will **write a small text** (a paragraph, a list, or an example) and add it to the project.  
We will **review it**, then it becomes part of a **chapter → volume → the book**.

---

## ✍️ Option A — The easiest way (using the website only)

You only need a free GitHub account. No installs.

1) **Open the chapters folder** in your browser  
   - Go to the folder for the first volume: `chapters/v00/`

2) **Pick where your text fits**  
   - `ch00_prelude.md` — short intros, motivation, why learning matters  
   - `ch01_git_github_basics.md` — basic ideas: what is Git, what is GitHub, branches, commits

3) **Click the file → “Edit” (pencil) button**  
   - You’ll see a text editor on the web page.

4) **Write your text**  
   - Start with a heading on a new line:  
     ```markdown
     ## My idea (one short title)
     ```
   - Then write your content. Keep it simple:  
     ```markdown
     - One short point
     - Another short point
     ```
   - If you show commands, use a “code block”:  
     ```text
     git status
     git commit -m "My message"
     ```

5) **Scroll down, describe your change, and press “Propose changes”**  
   - This creates a **Pull Request** (PR). Don’t worry, that’s just “please add my text”.

6) **Wait for checks** (green ticks)  
   - A robot will build a **Word file** from the chapters and attach it to your PR so you can **preview** the book output.

7) **We review and merge**  
   - If anything needs fixing, we’ll help you. When it’s ready, we “merge” and your words go into the book.

> ✅ That’s it. You contributed to a real book using only your web browser!

---

## 💻 Option B — Add a **new file** (still web-only)

If your text is bigger, you can add a new section file and we’ll place it in the right chapter.

1) Open the **`chapters/v00/`** folder on GitHub  
2) Click **“Add file” → “Create new file”**  
3) Name it like this: `v00_my_topic.md` (lowercase, hyphens are okay)  
4) Paste this starter:  
   ```markdown
   # My Topic (short title)

   ## Summary
   One or two sentences in simple words.

   ## Key ideas
   - Point 1
   - Point 2

   ## Example
   ```text
   (Put any commands or tiny example here)
   ```
   ```
5) Press **“Propose new file”** → create the Pull Request  
6) We’ll help move it under the right chapter and include it in the volume build.

---

## 🧩 What happens behind the scenes?

- Chapters live in `chapters/v00/` for **Volume 0**.  
- Our scripts build a **Word document**: `volumes/Volume_00_Source_Control.docx`.  
- When your PR is opened, the robot (CI) **auto-builds the book** and adds the file to your PR so you can download it.  
- After we approve and merge, your words are part of the book for everyone.

---

## 🧪 Want to try locally? (optional)

If you’re curious and want to see the book build on your computer:

### Windows (PowerShell)
```powershell
git clone https://github.com/umicom-foundation/Bits2Banking.git C:\Bits2Banking
cd C:\Bits2Banking
.uild.ps1 install
.uild.ps1 build
start .olumes\Volume_00_Source_Control.docx
```

### macOS / Linux (Makefile)
```bash
git clone https://github.com/umicom-foundation/Bits2Banking.git
cd Bits2Banking && make install && make build
xdg-open ./volumes/Volume_00_Source_Control.docx 2>/dev/null || open ./volumes/Volume_00_Source_Control.docx
```

---

## 🧷 Tips that help

- Keep sentences short. Simple English is great.  
- Use headings like `## Small Title` to group your ideas.  
- Use lists for steps:  
  ```markdown
  1. Do this
  2. Then that
  ```
- If you don’t know where your text fits, **just add it** — we’ll place it for you.  
- Be kind and encouraging — we’re building knowledge to help people.

---

## ❤️ Why your words matter

This book is free and open. We teach **computing → banking** skills and connect learning to **humanitarian relief**.  
Your contribution helps beginners learn and supports people facing crisis in Gaza.

**Thank you.** You are part of something good.
