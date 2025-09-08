![Cover](output/assets/covers/Volume_00_Bits_to_Banking_Master_Book_Cover.png)

# Bits_to_Banking_Master_Book


## Contents

- Foreword: My Chapter Title
- Foreword: volume2-introduction
- Foreword: volume1-introduction
- Foreword: Introduction to Islam A Complete Way of Life
- Contributing via raw docs Quick Guide
- Volumes Index
- Python Primer for Contributors
- Effective Communication Skills Course
- Bits to Banking Open Book
- history of money
- Chapter 3 The Decline of Sound Money
- Bits to Banking Master Book
- Chapter 4 Modern Banking and Finance
- Master Guide
- Chapter 5 Technology and Banking
- Chapter 6 Islamic Finance The Future
- Chapter 7 Recap Volume 1 Summary
- Chapter 7 Umicom ABS Coin AssetBacked SharīʿahCompliant
- Contributor Basics
- YAML in 10 Minutes for this project
- Effective Communication Skills Course
- hello
- 0009 Governance Firewalls Designing for Justice
- 0008 Hall of Shame Collaboration Corruption and Betrayal
- Bits2Banking Course Library
- ch00 prelude
- ch01 git GitHub basics

***



## Foreword: My Chapter Title


## Big picture

- You (or any contributor) put files in **`raw_docs/<volume-slug>/`**.
- The **Ingest bot** (GitHub Actions) mirrors or converts them into **`content/volumes/<volume-slug>/`**.
- The output is normalized Markdown (front-matter, title, code fence languages, etc.) and ready to review/publish.

---

## Folder layout

```text
raw_docs/                 # Drop-zone for uploads (md, docx, pdf), one folder per volume
content/volumes/          # Bot-populated Markdown output (auto-numbered chapters)
chapters/                 # (Legacy/authoring) Existing Volume 0 authoring
docs/                     # Website pages (MkDocs)
.github/                  # CI workflows, issue templates, policies
tools/                    # Helper scripts for scaffolding volumes
```text

---

## Contribute in 3 minutes

1. **Pick a volume slug** (lowercase, hyphens): e.g., `volume-0`, `introduction-to-islam`, `bits-to-banking`  
2. **Upload your file(s)** into `raw_docs/<slug>/` as **`.md`**, **`.docx`**, or **`.pdf`**.  
   - Optional cover image: **`bookcover_<book_title>.png`** (or `.jpg`)  
3. **Commit to `main`** (or open a PR).  
4. Bot converts/copies into `content/volumes/<slug>/` and auto-numbers new chapters: `ch01-…`, `ch02-…`

### Examples
```text
raw_docs/volume-0/intro.md
raw_docs/introduction-to-islam/history.docx
raw_docs/bits-to-banking/bookcover_Bits_to_Banking.png
```text

---

## What the bot does (exactly)

1. **Markdown passthrough**  
   Copies `.md` to `content/volumes/<slug>/` (and lists them for auto-numbering).
2. **DOCX → Markdown**  
   Uses Pandoc to produce GitHub-Flavored Markdown; extracts embedded images to `content/volumes/<slug>/images/<basename>/`.
3. **PDF → DOCX → Markdown (best-effort)**  
   Converts text-based PDFs via LibreOffice → DOCX → Markdown. Scanned/image-only PDFs become images and may need manual edits.
4. **Book cover standardization**  
   Files named `bookcover_<book_title>.(png|jpg|jpeg)` are saved as `content/volumes/<slug>/images/cover.png`.
5. **Auto-numbering (new files only)**  
   Fresh files from this run are renamed to `chNN-<slug>.md` to keep chapters ordered. Existing files are not renamed.
6. **Normalization**  
   Adds YAML front-matter if missing (title, volume, status, dates), ensures a top-level `# Title`, and fixes bare code fences to `text`.

### Guards & hygiene
- Skips junk/temp files (e.g., `~$docx`, `.tmp`, `.DS_Store`, `Thumbs.db`).
- Warns (does not fail) on uppercase or spaces in filenames—use **lowercase-hyphenated** names.
- Skips very large files with a **warning** (Markdown >2MB, DOCX >20MB, PDF >40MB, images >10MB).

---

## File conventions (quick rules)

- **Filenames:** `lowercase-hyphenated.md` (e.g., `risk-management.md`)  
- **One H1 per chapter:**  
  ```markdown
  # My Chapter Title
  ```
- **Code fences** specify a language:  
  ```python
  print("hello")
  ```
  Use `text` if unsure.

---

## Start a new volume (optional helpers)

### Windows (PowerShell)
```powershell
# From the repo root
.    ools
ew-volume.ps1 introduction-to-islam
```text

### macOS/Linux (Bash)
```bash
# From the repo root
bash tools/new-volume.sh introduction-to-islam
```text

This creates:
```text
raw_docs/<slug>/
content/volumes/<slug>/images/
content/volumes/<slug>/ch00-<slug>.md (placeholder)
```text

---

## Maintainer review flow (what happens after the bot)

1. You push to `main` (or open a PR).  
2. The bot writes normalized Markdown into `content/volumes/<slug>/`.  
3. Maintainer reviews and curates the chapters.  
4. Docs site/build pipelines pick up the content for publishing.

---

## Troubleshooting

- **Nothing happened**: Make sure you committed into `raw_docs/<slug>/` and the file isn’t too large. Check Actions → *Ingest* logs.  
- **Weird formatting**: For DOCX/PDF conversions, open the produced `.md` in `content/volumes/<slug>/` and adjust manually.  
- **Filename warnings**: Rename to lowercase-hyphenated; commit again.  
- **Cover image not found**: Ensure filename starts with `bookcover_` and is `.png`/`.jpg` in the same `raw_docs/<slug>/` folder.

---

## Suggested volumes

- **Volume 0:** `volume-0` — project introduction (this file).
- **Volume 1:** `introduction-to-islam` — foundations, history, core concepts.
- **Volume 2:** `bits-to-banking` — computing → OS → programming → security → finance.

Happy writing! ✨



## Foreword: volume2-introduction


## Who this is for

- Beginners who want a clear, practical route from zero to building useful things.  
- Engineers from other fields who want a **finance-tech** overview.  
- Contributors who can add examples, diagrams, labs, or case studies.

---

## Learning outcomes

By the end you will be able to:

- Explain how data becomes meaning: **bits → bytes → files → processes**.  
- Use the command line and write small programs to automate tasks.  
- Model and query data in **relational databases**.  
- Understand core **networking** and **security** ideas.  
- Read and discuss **banking/treasury** workflows with the right vocabulary.  

---

## Suggested outline

- **ch01 — Bits & Binary:** Representation, integers, text, endianness.  
- **ch02 — Operating Systems primer:** Processes, memory, filesystems, permissions.  
- **ch03 — Programming basics:** Variables, control flow, functions, modules, tests.  
- **ch04 — Data modeling & SQL:** Tables, keys, normalization, joins, transactions.  
- **ch05 — Networking:** TCP/IP, HTTP, tools, client–server mini-labs.  
- **ch06 — Security essentials:** Hashing, crypto at a high level, auth, threat basics.  
- **ch07 — Finance foundations:** Money flows, accounts, ledgers, payments rails.  
- **ch08 — Market data & pricing:** Instruments, quotes, risk-at-a-glance.  
- **ch09 — Treasury systems overview:** Positions, cash, risk, settlement; where **Calypso/TMS** fits.  
- **ch10 — Mini projects:** ETL a CSV into a DB; simple pricing/reporting script; mock “ops” day.

This outline will evolve with contributions and reviewer feedback.

---

## Contributing to this volume

1. Create or use the folder:
   ```text
   raw_docs/bits-to-banking/
   ```
2. Add chapters as **.md**, **.docx**, or **.pdf**.  
   - Optional cover image: `bookcover_Bits_to_Banking.png`  
3. Commit to **main** (or open a PR). The **Ingest** bot will:
   - Convert/copy to `content/volumes/bits-to-banking/`
   - Auto-number new chapters (`ch01-...`)
   - Normalize Markdown (front-matter, title, code fences)

If your file is very large (PDF > 40MB, DOCX > 20MB, MD > 2MB), it will be **skipped** with a warning in the Action logs.

---

## Getting hands-on (starter tasks)

- Reproduce a binary-to-decimal conversion with a short script.  
- Write a CLI that reads a CSV and prints summary stats.  
- Spin up a local database and run three non-trivial joins.  
- Use a packet capture tool to observe a simple HTTP request.  
- Sketch a money movement from account A → B and identify risks.

We’ll refine these into end-to-end labs as the volume grows.

---

## Next steps

Pick a chapter (e.g., **Bits & Binary**) and start drafting under `raw_docs/bits-to-banking/`.  
Include small, runnable examples and short exercises.



## Foreword: volume1-introduction


## Who this is for

- Curious readers with **no prior background**.
- Educators, parents, and learners looking for **clear definitions** and **primary-source pointers**.
- Contributors who want to help with **editing, translation notes, or adding references**.

> We aim for **accuracy**, **neutrality**, and **respect** for diverse Muslim communities and scholarly traditions.

---

## What this volume covers

- A beginner-friendly **overview of Islam**: key beliefs and practices.
- Concise context for **history**, **sources**, and **schools of thought**.
- Clear definitions for common terms and a short **glossary**.
- Signposts to primary sources and widely used translations.

This is **not** a replacement for scholarly study; it is an introduction that points to deeper resources.

---

## How to use this volume

- Read sequentially or dip into sections you need.  
- Use the **glossary** when you encounter new terms.  
- Follow the **Further Reading** notes at the end of chapters.

If you notice unclear phrasing or missing context, please contribute a correction (see **Contributing** below).

---

## Sources and methodology (at a glance)

- **Primary sources**: the Qur'an and the Sunnah (the teachings and practices attributed to the Prophet Muhammad, recorded in hadith literature).  
- **Secondary sources**: classical and modern scholarship, commentaries (tafsir), legal theory (usul al‑fiqh), and history.  
- When citing English translations, we note that **word choices vary**; contributors may suggest improvements and add references.  
- We avoid sectarian polemics; where scholarly views diverge, we **describe multiple perspectives** clearly.

---

## Key terms at a glance

- **Allah** — Arabic for God; used by Arabic‑speaking Muslims and non‑Muslims alike.  
- **Qur'an** — central scripture of Islam.  
- **Sunnah** — the prophetic example; teachings/practices reported in hadith.  
- **Hadith** — reports about what the Prophet said, did, or approved; collected with chains of transmission.  
- **Sharia** — the broad path or way; ethical‑legal framework derived from sources.  
- **Fiqh** — jurisprudence; the human understanding and application of the law.  
- **Ummah** — the global community of Muslims.  
- **Mosque (Masjid)** — place of worship.  
- **Five Pillars** — declaration of faith, prayer, almsgiving, fasting in Ramadan, and pilgrimage (Hajj).

> These brief definitions are for orientation; later chapters expand them with sources and examples.

---

## Suggested outline for this volume

- **ch01 — Orientation:** What this book covers and how to read it.  
- **ch02 — The Qur'an:** Structure, themes, translations, recitation.  
- **ch03 — The Sunnah and Hadith:** Collections, authentication, usage.  
- **ch04 — Core Beliefs:** God, prophethood, revelation, afterlife.  
- **ch05 — Practices:** Prayer, charity, fasting, pilgrimage.  
- **ch06 — Ethics and Law:** Sharia, fiqh, objectives (maqasid), diversity of opinion.  
- **ch07 — History (very brief):** Early community, spread, languages, scholarship.  
- **ch08 — Contemporary topics:** Community life, education, and common questions.  
- **ch09 — Glossary & study tips:** How to keep learning.  
- **ch10 — Further reading:** Translations, introductions, beginner courses.

This outline is a **starting point**; contributors can suggest reordering or new sections.

---

## Contributing (for this volume)

1. Create or use the folder:  
   ```text
   raw_docs/introduction-to-islam/
   ```
2. Add your chapter as **.md**, **.docx**, or **.pdf**.  
   - Optional cover image named like: `bookcover_Introduction_to_Islam.png`  
3. Commit to **main** (or open a PR). The **Ingest** bot will:
   - Convert or copy to `content/volumes/introduction-to-islam/`
   - Auto‑number new chapters (`ch01‑...`, `ch02‑...`)
   - Normalize Markdown (front‑matter, title, code fences)

If your file is very large (PDF > 40MB, DOCX > 20MB, MD > 2MB), the bot will **skip it** and print a warning in the Action logs.

---

## A short glossary (starter)

- **Aqidah** — creed or beliefs.  
- **Tafsir** — exegesis/commentary on the Qur'an.  
- **Madhhab** — legal school (e.g., Hanafi, Maliki, Shafi'i, Hanbali).  
- **Imam** — leader of prayer; also used for senior scholars in history.  
- **Maqasid al‑Sharia** — higher objectives of the law (e.g., protection of faith, life, intellect, family, property).

---

### Next

Propose a **chapter you want to write** (e.g., “The Qur'an: an overview”) and add it under `raw_docs/introduction-to-islam/`.  
We’ll grow this volume together with clear, sourced, respectful chapters.



## Foreword: Introduction to Islam A Complete Way of Life

# Introduction to Islam — A Complete Way of Life

Islam begins with a clear truth: **Allah is One**, the Creator of the heavens and the earth, and He created humanity with purpose, wisdom, and dignity. In the Qur’an, Allah tells us He placed humankind on earth as **khalīfah**—stewards who cultivate goodness, restrain harm, and build just communities. Islam is therefore **A Complete Way of Life (DEEN)**: not only private worship, but belief, prayer, character, family, markets and contracts, governance, mercy to people and to every living thing.

> **Q 2:30 (Arabic):** وَإِذْ قَالَ رَبُّكَ لِلْمَلَائِكَةِ إِنِّي جَاعِلٌ فِي الْأَرْضِ خَلِيفَةً
> **Meaning:** “When your Lord said to the angels, ‘I am placing upon the earth a khalīfah (successive authority).’”
>
> **Q 51:56 (Arabic):** وَمَا خَلَقْتُ الْجِنَّ وَالْإِنسَ إِلَّا لِيَعْبُدُونِ
> **Meaning:** “I did not create jinn and humans except that they worship (serve) Me.”

To “worship” Allah is more than prayer and fasting. It means **serving Allah’s cause** with truthfulness in everyday life: keeping promises, honoring contracts, protecting life and dignity, feeding the poor, preserving the environment, and refusing corruption. Islam shapes a person whose **heart is with Allah** and whose **hands serve people**. Lived individually and collectively, Islam brings balance, justice, and barakah.

## Submission: Entirely, Not Selectively

“Islam” literally means **submission**. Submitting to Allah’s guidance is not a loss of freedom; it is aligning with the way the Designer designed life to work best. The Qur’an warns against **picking a few rules we like and discarding the rest**; that breeds hypocrisy and injustice. Entering Islam **holistically** brings harmony.

> **Q 2:208 (Arabic):** يَا أَيُّهَا الَّذِينَ آمَنُوا ادْخُلُوا فِي السِّلْمِ كَافَّةً
> **Meaning:** “O you who believe! Enter into Islam **completely**.”

**Example — selective ethics fails:** a leader who prays but lies in contracts poisons trust; a trader who gives charity but manipulates weights harms the poor. Islam closes these loopholes by joining **ʿaqīdah** (belief), **ʿibādah** (worship), and **muʿāmalāt** (dealings) into one moral whole.

## The Five Pillars — A Daily System of Growth

The **Five Pillars** are the **engine of transformation**. Together they train **time management, commitment, sacrifice, community responsibility, and constant remembrance**. They interlock like ribs of an arch: remove one and the structure weakens; practice them together and life straightens.

### 1) Shahādah — The Foundation of Meaning

The testimony “Lā ilāha illā Allāh, Muḥammad rasūl Allāh” orients everything: **no rivals to Allah** in fear, hope, love, obedience, law, and loyalty. It resets identity away from ego, tribe, race, or ideology.

> **Q 47:19 (Arabic):** فَاعْلَمْ أَنَّهُ لَا إِلَٰهَ إِلَّا ٱللَّهُ وَٱسْتَغْفِرْ لِذَنبِكَ
> **Meaning:** “Know that there is no deity except Allah, and seek forgiveness for your sin.”

**Interconnection:** The shahādah feeds **ṣalāh** with sincerity, **zakāh** with purpose, **ṣawm** with patience, and **ḥajj** with devotion. It’s the compass.

### 2) Ṣalāh (Prayer) — Time Management and Presence

Five daily prayers carve the day into **sacred appointments** with Allah, training punctuality, focus, and humility. Each call to prayer reminds the soul that **Allāhu Akbar (Allah is greater)**—greater than deadlines, profits, anxieties, and screens.

> **Q 20:14 (Arabic):** إِنَّنِيٓ أَنَا ٱللَّهُ لَآ إِلَٰهَ إِلَّآ أَنَا فَٱعْبُدْنِي وَأَقِمِ ٱلصَّلَاةَ لِذِكْرِي
> **Meaning:** “Indeed, I am Allah; there is no deity except Me, so worship Me and establish prayer for My remembrance.”
>
> **Q 29:45 (Arabic):** إِنَّ ٱلصَّلَاةَ تَنْهَىٰ عَنِ ٱلْفَحْشَاءِ وَٱلْمُنكَرِ
> **Meaning:** “Indeed, prayer restrains from immorality and wrongdoing.”

**Allāhu Akbar — the daily reset:** The phrase in the adhān and prayer **shrinks the ego** and **re-centers priorities**. For a few minutes each time, we detach from the rushing world to realign with the **real purpose**.

### 3) Zakāh (Purifying Alms) — Discipline and Social Justice

Zakāh is a **due** on wealth for those eligible; it **purifies** the giver and **relieves** the vulnerable. Its annual cycle demands accounting, planning, and responsibility.

> **Q 9:103 (Arabic):** خُذْ مِنْ أَمْوَالِهِمْ صَدَقَةً تُطَهِّرُهُمْ وَتُزَكِّيهِمْ بِهَا
> **Meaning:** “Take from their wealth charity by which you purify and grow them.”
>
> **Q 9:60 (Arabic):** إِنَّمَا ٱلصَّدَقَاتُ لِلْفُقَرَاءِ وَٱلْمَسَاكِينِ...
> **Meaning:** “Charities are for the poor, the needy…” (lists categories)

**Interconnection:** Zakāh turns private piety into **public mercy**; it complements prayer and prepares the heart for **sacrifice** in fasting and **solidarity** in ḥajj.

### 4) Ṣawm (Fasting) — Patience, Focus, and Freedom from Addictions

Ramadān trains **self-mastery**: hunger without complaint, restraint without resentment, generosity without show. It resets body rhythms and compels **time stewardship** (suḥūr, ifṭār, nightly Qur’ān).

> **Q 2:183 (Arabic):** يَا أَيُّهَا ٱلَّذِينَ آمَنُوا كُتِبَ عَلَيْكُمُ ٱلصِّيَامُ... لَعَلَّكُمْ تَتَّقُونَ
> **Meaning:** “Fasting has been prescribed for you… so that you may become God-conscious.”

**Interconnection:** Fasting strengthens prayer’s presence, softens the heart for giving, and readies the pilgrim for ḥajj’s hardships.

### 5) Ḥajj (Pilgrimage) — Unity, Planning, and Lifelong Renewal

Ḥajj is a **once-in-a-lifetime summit** for those able. It requires **logistics, savings, patience**, and **collective discipline** as millions move in a common rhythm, all in simple garments, all equal before Allah.

> **Q 3:97 (Arabic):** وَلِلَّهِ عَلَى ٱلنَّاسِ حِجُّ ٱلْبَيْتِ مَنِ ٱسْتَطَاعَ إِلَيْهِ سَبِيلًا
> **Meaning:** “Pilgrimage to the House is a duty owed to Allah by people who are able to find a way.”
>
> **Q 22:27 (Arabic):** وَأَذِّنْ فِي ٱلنَّاسِ بِٱلْحَجِّ يَأْتُوكَ رِجَالًا...
> **Meaning:** “Proclaim the pilgrimage to the people; they will come to you on foot and on every lean camel…”

**Interconnection:** Ḥajj **completes** what shahādah began, what ṣalāh and ṣawm trained, and what zakāh funded—**a life woven into community and submission**.

**How the Pillars teach rhythm and responsibility:** Daily (ṣalāh), yearly (zakāh, ṣawm), once-in-a-lifetime (ḥajj), and constant (shahādah). They **structure time**, **prioritize values**, and **anchor the heart**.

## One Human Family — No Superior Race

Islam teaches we all descend from **Ādam and Ḥawwāʾ**. Humanity is one family. We differ in languages and cultures, but none of this makes one group superior. Honor with Allah is by **taqwā** (God-consciousness) and good deeds, not by blood, color, passport, or tribe.

> **Q 49:13 (Arabic):** يَا أَيُّهَا النَّاسُ إِنَّا خَلَقْنَاكُم مِّن ذَكَرٍ وَأُنثَىٰ وَجَعَلْنَاكُمْ شُعُوبًا وَقَبَائِلَ لِتَعَارَفُوا ۚ إِنَّ أَكْرَمَكُمْ عِندَ ٱللَّهِ أَتْقَىٰكُمْ
> **Meaning:** “O humankind! We created you from a male and a female and made you peoples and tribes so that you may know one another. Indeed, the most honored of you with Allah is the most God-conscious.”

The Prophet ﷺ declared in the Farewell Sermon that there is **no superiority** of Arab over non-Arab, nor white over black, except by taqwā. Supremacist ideologies—old or new—contradict Allah’s justice and **tear the human family apart**.

> **Q 5:8 (Arabic):** وَلَا يَجْرِمَنَّكُمْ شَنَآنُ قَوْمٍ عَلَىٰ أَلَّا تَعْدِلُوا ۚ اعْدِلُوا هُوَ أَقْرَبُ لِلتَّقْوَىٰ
> **Meaning:** “Do not let hatred of a people lead you away from justice. Be just—that is nearer to taqwā.”

**Historical snapshot — Copt and the governor’s son:** In Egypt, a Coptic man complained that a governor’s son struck him. The case reached **ʿUmar ibn al-Khaṭṭāb** (raḍiyallāhu ʿanhu). The Caliph called them to Madinah; the Copt struck the offender back in public, and ʿUmar rebuked the governor: “Since when do you enslave people when their mothers bore them free?” Justice in Islam does not bend to rank.

## Freedom of Choice — No Compulsion

Islam invites with proof and mercy. **There is no compulsion** in accepting the way of life. Allah gave us reason and will, and He holds each person accountable for their own choices.

> **Q 2:256 (Arabic):** لَا إِكْرَاهَ فِي الدِّينِ
> **Meaning:** “There is no compulsion in religion.”

**The Madinah Charter** recognized the security of Muslim and non-Muslim communities alike and bound them to common justice and defense. Coercion corrupts faith; persuasion, example, and due process nurture it.

## All Scriptures — One Message: Islam (Tawḥīd and Justice)

Islam teaches that Allah sent **revelation** and **messengers** across ages to call people to **tawḥīd** (oneness of God) and righteous living. The **Tawrāh (Torah)** given to Mūsā (Moses), the **Zabūr (Psalms)** to Dāwūd (David), the **Injīl (Gospel)** to ʿĪsā (Jesus), the **Suhuf** of Ibrāhīm (Abraham) and Mūsā, and finally the **Qur’ān** to Muḥammad ﷺ—**all** summoned humanity to **submit to Allah (Islam)**, avoid idolatry, uphold justice, and prepare for accountability.

> **Q 21:25 (Arabic):** وَمَا أَرْسَلْنَا مِن قَبْلِكَ مِن رَّسُولٍ إِلَّا نُوحِي إِلَيْهِ أَنَّهُ لَآ إِلَٰهَ إِلَّآ أَنَا فَاعْبُدُونِ
> **Meaning:** “We sent no messenger before you except that We revealed to him: ‘There is no deity but Me, so worship Me.’”
>
> **Q 16:36 (Arabic):** وَلَقَدْ بَعَثْنَا فِي كُلِّ أُمَّةٍ رَّسُولًا أَنِ ٱعْبُدُوا ٱللَّهَ وَٱجْتَنِبُوا ٱلطَّاغُوتَ
> **Meaning:** “We certainly sent into every nation a messenger: ‘Worship Allah and avoid false gods.’”
>
> **Q 42:13 (Arabic):** شَرَعَ لَكُم مِّنَ ٱلدِّينِ مَا وَصَّىٰ بِهِ نُوحًا… وَٱلَّذِيٓ أَوْحَيْنَآ إِلَيْكَ…
> **Meaning:** “He has ordained for you of religion what He enjoined upon Noah and what We have revealed to you…”
>
> **Q 3:19 (Arabic):** إِنَّ الدِّينَ عِندَ ٱللَّهِ ٱلْإِسْلَامُ
> **Meaning:** “Indeed, the religion with Allah is Islam.”

Muslims affirm the **original** revelations; the Qur’ān also warns that some altered or concealed parts of prior scripture.

> **Q 2:75 (Arabic):** قَدْ كَانَ فَرِيقٌ مِّنْهُمْ يَسْمَعُونَ كَلَـٰمَ ٱللَّهِ ثُمَّ يُحَرِّفُونَهُ مِنۢ بَعْدِ مَا عَقَلُوهُ
> **Meaning:** “A group among them would hear the words of Allah, then alter it after understanding it.”
>
> **Q 3:78 (Arabic):** وَإِنَّ مِنْهُمْ لَفَرِيقًا يَلْوُونَ أَلْسِنَتَهُم بِٱلْكِتَـٰبِ لِتَحْسَبُوهُ مِنَ ٱلْكِتَـٰبِ
> **Meaning:** “Among them is a group who distort their tongues with the Book so you think it is from the Book.”

By contrast, Allah promises the Qur’ān’s preservation.

> **Q 15:9 (Arabic):** إِنَّا نَحْنُ نَزَّلْنَا ٱلذِّكْرَ وَإِنَّا لَهُ لَحَـٰفِظُونَ
> **Meaning:** “Indeed, We sent down the Reminder, and indeed We will guard it.”

The Qur’ān **confirms and safeguards** truths that remain in earlier scriptures, summons the People of the Book back to **tawḥīd** and justice, and completes divine guidance.

> **Q 5:48 (Arabic):** وَأَنزَلْنَآ إِلَيْكَ ٱلْكِتَـٰبَ بِٱلْحَقِّ مُصَدِّقًا لِّمَا بَيْنَ يَدَيْهِ مِنَ ٱلْكِتَـٰبِ وَمُهَيْمِنًا عَلَيْهِ
> **Meaning:** “We revealed to you the Book in truth, confirming what came before it of the Scripture and as a guardian over it.”

## Prophets, Scripture, and the Unseen

Across history, Allah sent messengers when generations drifted from purpose. Muslims believe in **all the prophets**—Ādam, Nūḥ, Ibrāhīm, Mūsā, ʿĪsā, and Muḥammad (عليهم السلام)—and in the revelation they brought in its original purity. We also believe in the **angels**, the **jinn**, the **Last Day**, and the **divine decree**.

> **Q 2:285 (Arabic):** آمَنَ الرَّسُولُ بِمَا أُنزِلَ إِلَيْهِ مِن رَّبِّهِ وَالْمُؤْمِنُونَ…
> **Meaning:** “The Messenger has believed in what was revealed to him from his Lord, and [so have] the believers: all of them have believed in Allah, His angels, His books, and His messengers…”

The Qur’an also warns about those who **throw revelation behind their backs** and follow devils into manipulation and sorcery.

> **Q 2:102 (Arabic):** وَاتَّبَعُوا مَا تَتْلُوا ٱلشَّيَاطِينُ عَلَىٰ مُلْكِ سُلَيْمَانَ…
> **Meaning:** “They followed what devils recited during the reign of Solomon… Solomon did not disbelieve, but the devils disbelieved, teaching people magic…”

Any group that demands **allegiance above Allah’s command**—or trades truth for secrecy and worldly power—must be refused. A believer’s pledge is to **Allah alone**.

## Signs in Revelation and in Nature

The Qur’an calls us to **think, observe, and reflect**. It is a book of guidance, not a lab manual, yet many verses point us to the natural world in ways that harmonize with what science discovers—encouraging **humility** and **research**.

- **Creation from a joined origin (Q 21:30):** the heavens and the earth were a unified entity before being parted.
  > **Arabic:** أَوَلَمْ يَرَ الَّذِينَ كَفَرُوا أَنَّ السَّمَاوَاتِ وَالْأَرْضَ كَانَتَا رَتْقًا فَفَتَقْنَاهُمَا
- **Expansion and sustaining of the heavens (Q 51:47):** Allah’s power to extend and uphold.
  > **Arabic:** وَالسَّمَاءَ بَنَيْنَاهَا بِأَيْيدٍ وَإِنَّا لَمُوسِعُونَ
- **Mountains as stabilizing “pegs” (Q 78:6–7):** imagery of anchoring and stability.
  > **Arabic:** أَلَمْ نَجْعَلِ الْأَرْضَ مِهَادًا ۝ وَالْجِبَالَ أَوْتَادًا
- **Barriers between bodies of water (Q 25:53; 55:19–20):** natural boundaries where mixing is constrained.
  > **Arabic:** مَرَجَ الْبَحْرَيْنِ يَلْتَقِيَانِ ۝ بَيْنَهُمَا بَرْزَخٌ لَّا يَبْغِيَانِ
- **Embryonic development in stages (Q 23:12–14):** vivid, stage-wise progression that resonates with embryology.
  > **Arabic (excerpt):** ثُمَّ خَلَقْنَا النُّطْفَةَ عَلَقَةً فَخَلَقْنَا الْعَلَقَةَ مُضْغَةً فَخَلَقْنَا الْمُضْغَةَ عِظَامًا فَكَسَوْنَا الْعِظَامَ لَحْمًا
- **Life from water (Q 21:30):** water’s centrality to life—calling for stewardship and conservation.
  > **Arabic:** وَجَعَلْنَا مِنَ الْمَاءِ كُلَّ شَيْءٍ حَيٍّ
- **Iron “sent down” (Q 57:25):** bestowed with strength and benefit—apt for its stellar origin and human use.
  > **Arabic:** وَأَنزَلْنَا الْحَدِيدَ فِيهِ بَأْسٌ شَدِيدٌ

These are **āyāt**—signs that invite rational confidence in the Creator and energize a life of learning and service.

## Simple, Clear Pointers to the Creator

- **The phone in the street:** If you found a smartphone on a beach, with a glass screen, chipset, camera, and a tuned OS, would you say “the waves made it”? The more **ordered** and **purposeful** a thing is, the more it points to **mind** and **will** behind it. The cosmos is not less ordered than a phone.
- **The house and the blueprint:** No one walks into a house and says, “bricks arranged themselves.” Walls align, beams bear load, plumbing follows design. The world shows **laws**, **constants**, **coded life**—signs of an **Author**.
- **You, the observer:** You experience **consciousness**, **moral intuition**, and **meaning**. Matter alone does not explain duty and beauty; **fitrah** (innate disposition) recognizes a higher moral lawgiver.
- **Beginning needs a beginner:** What begins to exist has a cause. The universe is not past-eternal; it began. A **first cause**, uncaused, powerful and knowing, best fits **Allah**, the Necessary Being.

> **Q 52:35–36 (Arabic):** أَمْ خُلِقُوا مِنْ غَيْرِ شَيْءٍ أَمْ هُمُ الْخَالِقُونَ ۝ أَمْ خَلَقُوا السَّمَاوَاتِ وَالْأَرْضَ
> **Meaning:** “Were they created from nothing, or are they creators? Or did they create the heavens and the earth?”

## Jihād — The Struggle to Uplift and Defend

“Jihād” means **striving/struggle**. Its broadest sense is to exert oneself for Allah—**to learn and teach**, **to reform the self**, **to serve people**, **to repair the earth**, and, when necessary, **to defend those under attack** within strict moral limits.

### Striving against the self (jihād al-nafs)

Conquering arrogance, greed, and anger; establishing prayer, honesty, and patience. The Prophet ﷺ said the **strong** person is not the one who overpowers others, but **who controls himself** when angry (Bukhārī, Muslim).

### Striving with knowledge and teaching

Seeking knowledge is an obligation. Disseminating truth and countering falsehood is part of jihād—**pens before swords**. Reform is durable when **minds** and **hearts** change.

### Striving with service and care for creation

Feeding the poor, healing the sick, building schools, and **protecting the environment** are all jihād. Planting a sapling even as the Hour approaches is rewarded (authentic meaning reported in Musnad Aḥmad).

> **Q 30:41 (Arabic):** ظَهَرَ الْفَسَادُ فِي الْبَرِّ وَالْبَحْرِ بِمَا كَسَبَتْ أَيْدِي النَّاسِ
> **Meaning:** “Corruption has appeared on land and sea because of what people’s hands have earned.”
> **Q 2:205 (Arabic):** وَإِذَا تَوَلَّىٰ سَعَىٰ فِي الْأَرْضِ لِيُفْسِدَ فِيهَا وَيُهْلِكَ الْحَرْثَ وَالنَّسْلَ
> **Meaning:** “When he turns away, he strives throughout the land to cause corruption and destroy crops and descendants.”

### Defensive struggle when attacked

Islam permits **defense** against aggression, expulsion, and persecution—**never** transgression or targeting innocents. The Qur’an sets clear boundaries.

> **Q 22:39–40 (Arabic):** أُذِنَ لِلَّذِينَ يُقَاتَلُونَ بِأَنَّهُمْ ظُلِمُوا... وَلَوْلَا دَفْعُ ٱللَّهِ ٱلنَّاسَ بَعْضَهُم بِبَعْضٍ لَّهُدِّمَتْ صَوَامِعُ وَبِيَعٌ...
> **Meaning:** “Permission [to fight] is given to those who are fought because they were wronged… Had Allah not checked one people by means of another, monasteries, churches, synagogues, and mosques would have been demolished.”
>
> **Q 2:190 (Arabic):** وَقَاتِلُوا فِي سَبِيلِ ٱللَّهِ ٱلَّذِينَ يُقَاتِلُونَكُمْ وَلَا تَعْتَدُوا
> **Meaning:** “Fight in the way of Allah those who fight you, **but do not transgress**.”

**Prophetic rules:** No killing of non-combatants (women, children, elderly), no mutilation, no treachery, no destroying crops or animals, no demolishing homes or houses of worship (Bukhārī, Muslim; instructions narrated from Abū Bakr to armies). This applies whether resisting **occupation**, confronting **banditry**, or defending one’s **family**—always within law, restraint, and accountability.

**Balance:** Most of a believer’s life-jihād is **constructive**—purifying the self, educating, building just institutions, and protecting the vulnerable. Defensive force is last-resort, bound by ethics.

## Justice in Markets and Public Life

Islam demands justice at both the **market** and **governance** levels. Cheating the scale is condemned; **riba** (usury/interest) is forbidden because it grows money without real production or shared risk; and rulers are warned not to govern by anything other than what Allah revealed.

> **Q 83:1–3 (Arabic):** وَيْلٌ لِّلْمُطَفِّفِينَ • الَّذِينَ إِذَا اكْتَالُوا عَلَى النَّاسِ يَسْتَوْفُونَ • وَإِذَا كَالُوهُمْ أَو وَّزَنُوهُمْ يُخْسِرُونَ
> **Meaning:** “Woe to those who give less in measure… when they take, they take in full; when they measure for others, they give less.”
>
> **Q 2:275 (Arabic):** أَحَلَّ اللَّهُ الْبَيْعَ وَحَرَّمَ الرِّبَا
> **Meaning:** “Allah has permitted **trade** and forbidden **riba**.”
>
> **Q 5:44–47 (Arabic):** وَمَن لَّمْ يَحْكُم بِمَا أَنزَلَ ٱللَّهُ…
> **Meaning:** “Whoever does not judge by what Allah has revealed—then they are the disbelievers… the wrongdoers… the defiantly disobedient.”

**Hadith — market ethics:** “The buyer and the seller have the option (to cancel) so long as they have not separated; if they were truthful and clear, they will be blessed in their sale; if they concealed and lied, the blessing of their sale will be erased.” (Bukhārī, Muslim)

**Hadith — hoarding:** “Whoever hoards (to raise prices) is sinful.” (Reported in Muslim)

The Prophet ﷺ set rules that block hidden exploitation in exchange. About **ribāwī** items, he said that **gold for gold and silver for silver** must be **like-for-like**, **equal**, and **hand-to-hand** when exchanged; if they **differ in type**, the exchange must still be **spot (immediate)**. He corrected **Bilāl** when he swapped **inferior for superior dates** on unequal terms, teaching that such a swap of the **same kind** is the **essence of riba**; the fair way is to **sell for cash and then buy** the better dates (Ṣaḥīḥ Muslim; Bukhārī in meaning).

These rules protect markets from stealth advantage and keep money as a **measure of value**, not a tool for **guaranteed gain without risk**. This underpins the preference for **intrinsic or asset-backed money** over unconstrained paper promises.

## Money Should Track Real Value

For centuries Muslims used **gold (dīnār)** and **silver (dirham)**—monies with **intrinsic value**. Islam’s concern is **justice**: money should not become a device to **create claims out of thin air** for a guaranteed return. That is why we will later argue for **asset-backed** monetary design (e.g., **Umicom**)—transparent issuance against **real, auditable reserves** and contracts that **share risk**.

**Historical note — Islamic coinage:** Early Muslim coinage standardized weights and Qur’anic inscriptions, discouraging portraits and idolatrous symbols. Coins traveled across trade routes from al-Andalus to China, supporting fair exchange.

## Mercy for All Creation

Islam extends mercy beyond humans. The Prophet ﷺ told of a woman punished for **mistreating a cat**, and a man **forgiven** for giving water to a thirsty dog (Bukhārī, Muslim). Allah condemns environmental corruption and waste.

> **Q 30:41 (Arabic):** ظَهَرَ الْفَسَادُ فِي الْبَرِّ وَالْبَحْرِ بِمَا كَسَبَتْ أَيْدِي النَّاسِ
> **Meaning:** “Corruption has appeared on land and sea because of what people’s hands have earned.”

**Abū Bakr’s rules of engagement:** When dispatching an army, he advised, “Do not kill women, children, or the elderly; do not mutilate; do not cut down fruitful trees; do not destroy inhabited places; do not kill monks in monasteries.” Mercy and restraint are Islamic law, not afterthoughts.

We are **trustees**: consume ethically, farm responsibly, protect ecosystems, and avoid waste.

## Courage against Fear-Mongering and Hypocrisy

During the **Confederates’ siege** of Madinah, fear-mongers tried to paralyze the believers; true believers grew firmer in reliance and action.

> **Q 33:22 (Arabic):** وَلَمَّا رَأَى ٱلْمُؤْمِنُونَ ٱلْأَحْزَابَ قَالُوا هَٰذَا مَا وَعَدَنَا ٱللَّهُ وَرَسُولُهُ وَصَدَقَ ٱللَّهُ وَرَسُولُهُ ۚ وَمَا زَادَهُمْ إِلَّا إِيمَانًا وَتَسْلِيمًا
> **Meaning:** “When the believers saw the confederates, they said, ‘This is what Allah and His Messenger promised us,’ and it only increased them in faith and submission.”

We are also commanded to **verify news** and refuse to amplify panic or propaganda.

> **Q 49:6 (Arabic):** يَا أَيُّهَا الَّذِينَ آمَنُوا إِن جَاءَكُمْ فَاسِقٌ بِنَبَإٍ فَتَبَيَّنُوا
> **Meaning:** “O you who believe! If a sinner comes to you with news, verify it.”

**Hadith — stand for justice:** “Support your brother whether he is the oppressor or the oppressed.” They asked, “We know how to help the oppressed; how do we help the oppressor?” He said, “By preventing him from oppression.” (Bukhārī)

## Satanic Divide-and-Rule vs. Islam’s Unity

From the first sin of **arrogance** (Q 7:12), Shayṭān’s method is to plant **“I am better”**—the seed of racism and classism. Ideologies that elevate one group as **“chosen”** to dominate and dispossess others invert justice. History gives hard lessons: **Nazi Germany’s** racial myth fueled catastrophic war and genocide. In our time, **Zionism as a political project** has produced the **dispossession and occupation of Palestine**, repeated assaults on civilians, and systems of **apartheid-like control**—all standing against the Qur’anic commands of justice, sanctity of life, and equality of the children of Ādam. Islam rejects **all** supremacist doctrines—whether draped in race, nation, or religion. The remedy is **tawḥīd** (one Creator), **qisṭ** (justice), and **ʿadl** (fair dealing) applied to **everyone**.

> **Q 4:135 (Arabic):** يَا أَيُّهَا الَّذِينَ آمَنُوا كُونُوا قَوَّامِينَ بِالْقِسْطِ شُهَدَاءَ لِلَّهِ…
> **Meaning:** “O you who believe, stand firm in justice, witnesses for Allah, even if against yourselves or parents and relatives…”

**Historical witness — Andalusian convivencia (imperfect but real):** Across centuries, Jews, Christians, and Muslims wrote poetry, traded, and studied in a shared urban life. When power abused, scholars protested; when justice ruled, cities flourished. Justice is practical: contracts honored, minorities protected, courts open.

## Short Quotes from Notable Non-Muslim Voices

> “The lies which well-meaning zeal has heaped round this man are disgraceful to ourselves only.” — Thomas Carlyle, *On Heroes* (1841)
>
> “His readiness to undergo persecution for his beliefs… argue his sincerity.” — W. Montgomery Watt, *Muhammad at Mecca* (1953)
>
> “The only man in history who was supremely successful on both the religious and secular levels.” — Michael H. Hart, *The 100* (1978)
>
> “Islam is a democratic spirit… in the mosques, monarch and peasant kneel side by side.” — Sarojini Naidu, speech excerpts (early 20th c.)
>
> “If this be Islam, do we not all live in Islam?” — Johann Wolfgang von Goethe, *West-östlicher Divan* (1819)
>
> “It was not the sword that won a place for Islam… it was the rigid simplicity, the scrupulous regard for pledges.” — M. K. Gandhi, *Young India* (1928)

## Author’s Note — Why I Refused Freemasonry

I was invited to join **Freemasonry** and declined, because Islam requires transparent pledges to Allah alone, justice above group loyalty, and avoidance of esoteric rites and secretive allegiances.

- **Secret oaths and layered allegiances**: Islam commands transparent pledges to Allah alone.
  > **Q 16:91 (Arabic):** وَأَوْفُوا بِعَهْدِ ٱللَّهِ إِذَا عَاهَدتُّمْ
  > **Meaning:** “Fulfill Allah’s covenant when you pledge.”

- **Brotherhood above justice**: The Prophet ﷺ bound us to justice **even against ourselves**. A closed brotherhood that shields members conflicts with **Q 4:135**.
- **Ritual symbolism and esoterica**: Islam bars avenues that resemble **sorcery** or occult symbolism.
  > **Q 2:102** warns against following the teachings of devils and magic.

- **Secrecy that conceals harm**: Islam’s rule is to cooperate in **birr** and **taqwā**, not in sin and aggression.
  > **Q 5:2 (Arabic):** وَتَعَاوَنُوا عَلَى الْبِرِّ وَالتَّقْوَىٰ وَلَا تَعَاوَنُوا عَلَى الْإِثْمِ وَالْعُدْوَانِ

For me, Islam’s clarity, public ethics, and accountability make such secretive structures unnecessary and spiritually dangerous.

## Building Character: From Intention to Institutions

- **Intention (niyyah):** “Actions are by intentions.” (Bukhārī, Muslim)
  Start with **ikhlāṣ** (sincerity), then seek excellence (**iḥsān**) in craft, trade, and service.
  > **Q 67:2 (Arabic):** لِيَبْلُوَكُمْ أَيُّكُمْ أَحْسَنُ عَمَلًا — “…that He may test you [to see] which of you is **best** in deed.”
- **Truthfulness (ṣidq):** Truth sets contracts and communities at ease.
  > **Q 9:119 (Arabic):** يَا أَيُّهَا الَّذِينَ آمَنُوا اتَّقُوا ٱللَّهَ وَكُونُوا مَعَ ٱلصَّادِقِينَ
- **Trust (amānah):** Positions are a trust.
  > **Q 4:58 (Arabic):** إِنَّ ٱللَّهَ يَأْمُرُكُمْ أَن تُؤدُّوا ٱلْأَمَانَاتِ إِلَىٰ أَهْلِهَا
- **Brotherhood:** “None of you truly believes until he loves for his brother what he loves for himself.” (Bukhārī, Muslim)
- **Institutions:** Courts must be accessible; markets transparent; rulers accountable; media honest; schools form integrity and skill. Islam is not merely personal piety—it is the **architecture of justice**.

## Giving and Serving — The Upper Hand

Islam trains us to be **givers** who lift others. **Zakāt** purifies wealth; voluntary charity heals hearts; **service** binds communities.

> **Hadith (Bukhārī, Muslim):** «الْيَدُ الْعُلْيَا خَيْرٌ مِنَ الْيَدِ السُّفْلَى»
> **Meaning:** “The upper hand is better than the lower hand.”
>
> **Q 3:92 (Arabic):** لَن تَنَالُوا الْبِرَّ حَتَّىٰ تُنفِقُوا مِمَّا تُحِبُّونَ
> **Meaning:** “You will never attain righteousness until you spend from what you love.”

Our project—**education** plus **ethical finance**—aims to **serve people** so families, students, and small businesses can breathe and build.

## Where to next

With belief, revelation, justice, unity, the Five Pillars, and the ethics of jihād clarified—we next examine how money and markets can enable or destroy justice. Continue to **History of Money** to see how just exchange and sound money kept communities stable, and how manipulation corrupted markets and states.

**Next chapter:** *History of Money* → `history_of_money.md`

## Summary (Refresher)

- Allah created us with **purpose**: to know Him and do right.
- **All prophets and scriptures** called to **Islam**: worship Allah alone and uphold justice.
- **Islam = submission**—a mercy when embraced **completely**.
- The **Five Pillars** interlock to build time-management, commitment, sacrifice, and constant remembrance.
- **Jihād** is comprehensive striving: self-reform, knowledge, service, environmental care, and ethical defense against aggression—**without transgression**.
- **One human family**; racism and supremacism are satanic diseases.
- **No compulsion**: guidance is clear; choice is free; judgment is Allah’s.
- **Prophets** called to tawḥīd and justice (ISLAM - The Complete Way of Life/The Perfect Blueprint to a successful life); **Qur’an’s signs** invite reflection, **knowledge** strengthens faith.
- **Trade permitted, riba forbidden**; fairness in exchange is worship.
- **Money** should track **real value** and **share risk**; we’ll propose **Umicom Financial Markets and Interensic Based Money** later.
- **Stand firm in justice**; verify news; stop oppression—including by those “on our side”.
- **Serve** more than you take; build institutions that embody Qur’anic justice.

## Supplications (Duʿā’)

### For seeing truth and acting on it
**Arabic:** اللَّهُمَّ أَرِنَا الْحَقَّ حَقًّا وَارْزُقْنَا اتِّبَاعَهُ، وَأَرِنَا الْبَاطِلَ بَاطِلًا وَارْزُقْنَا اجْتِنَابَهُ.
**Meaning:** O Allah, show us truth as truth and grant us to follow it; show us falsehood as falsehood and grant us to avoid it.

### For justice and mercy in dealings
**Arabic:** اللَّهُمَّ بَارِكْ لَنَا فِي أَرْزَاقِنَا، وَارْزُقْنَا الصِّدْقَ فِي الْبَيْعِ وَالشِّرَاءِ، وَنَجِّنَا مِنَ الرِّبَا وَالظُّلْمِ.
**Meaning:** O Allah, bless our provision, grant us honesty in trade, and save us from riba and oppression.

### English
O Allah, show us truth as truth and enable us to follow it; show us falsehood as falsehood and enable us to avoid it. Make us keys to goodness and locks against harm, and use us to serve people and help the oppressed. Āmīn.

### For courage and unity
**Arabic:** اللَّهُمَّ ثَبِّتْ قُلُوبَنَا عِنْدَ الْفِتَنِ، وَاجْمَعْ كَلِمَتَنَا عَلَى الْحَقِّ، وَانْصُرِ الْمُسْتَضْعَفِينَ.
**Meaning:** O Allah, keep our hearts firm in trials, unite us upon truth, and aid the oppressed.

---

### ← [Volume index](../index.md)
**Next:** [History of Money →](history_of_money.md)



## Contributing via raw docs Quick Guide

# Contributing via `raw_docs/` (Quick Guide)

This project welcomes contributions from beginners and busy experts alike.
If you can upload a file, you can contribute. 🚀

---

## What to upload

- Chapters/sections as **.md**, **.docx**, or **.pdf**
- Optional cover image as: **`bookcover_<book_title>.png`** (PNG preferred, 1600–2400px wide)

> Tip: If you’re not sure about formatting, just upload the file. The bot will convert and normalize it.

---

## Where to put files

One folder **per volume** under `raw_docs/`:

```text
raw_docs/<volume-slug>/
├─ my-chapter.docx        # or .md / .pdf
├─ another-section.md
└─ bookcover_My_Title.png # optional
```text

### Examples
```text
raw_docs/generalist-ai/intro.docx
raw_docs/starting-a-business/bookcover_Starting_Your_Own_Business.png
```text

**Volume slug rules:** lowercase, use hyphens: `generalist-ai`, `starting-a-business`.

---

## What the bot (CI) does for you

When you push to `main`:

1. **Markdown passthrough**
   - Copies `.md` from `raw_docs/<slug>/` → `content/volumes/<slug>/`.
2. **DOCX → Markdown**
   - Converts `.docx` to `.md` (GitHub-Flavored Markdown).
   - Extracts embedded images to `content/volumes/<slug>/images/<basename>/`.
3. **PDF → DOCX → Markdown (best-effort)**
   - Converts text-based `.pdf` to `.docx`, then to `.md`.
   - Scanned PDFs produce images; text quality depends on the source.
4. **Auto-number new chapters**
   - Renames fresh files to `chNN-<slug>.md` (e.g., `ch01-introduction.md`), only for files processed this run. Existing files are untouched.
5. **Normalize Markdown**
   - Adds YAML front-matter (title, volume, status, dates).
   - Ensures a top-level `# Title`.
   - Fixes blank code fences to use `text` (satisfies markdownlint MD040).

### Output lives in
```text
content/volumes/<volume-slug>/
```text

---

## Naming tips (optional but helpful)

- File names: short, lowercase, hyphenated:
  `distributed-systems-overview.md`, `risk-management.docx`
- One top-level heading in `.md`:
```markdown
# My Chapter Title
```text
- Code blocks:
```python
print("hello")
```text
(Use `text` if you’re unsure.)

---

## Quick scaffolding (optional helpers)

### Windows (PowerShell)
```powershell
# From the repo root
.    ools
ew-volume.ps1 generalist-ai
```text

### macOS/Linux (Bash)
```bash
# From the repo root
bash tools/new-volume.sh generalist-ai
```text

These create:
```text
raw_docs/<slug>/
content/volumes/<slug>/images/
content/volumes/<slug>/ch00-<slug>.md (placeholder)
```text

---

## Submitting work

- If you can edit the repo, **commit directly to `main`** under `raw_docs/<slug>/`.
- Otherwise, fork → branch → PR (the classic way).

That’s it. The bot will mirror/convert your files and you (the maintainer) review final content under `content/volumes/<slug>/`.



## Volumes Index

# Volumes — Index

Quick links to each volume, where to upload drafts, and where finalized Markdown lands.

> Upload chapters to `raw_docs/<slug>/`. The ingest bot mirrors/normalizes them into `content/volumes/<slug>/`.

| Volume | Slug | Upload here (raw) | Output (normalized Markdown) |
|---|---|---|---|
| Volume 0 — Project Intro | `volume-0` | <https://github.com/umicom-foundation/Bits2Banking/tree/main/raw_docs/volume-0> | <https://github.com/umicom-foundation/Bits2Banking/tree/main/content/volumes/volume-0> |
| Volume 1 — Introduction to Islam | `introduction-to-islam` | <https://github.com/umicom-foundation/Bits2Banking/tree/main/raw_docs/introduction-to-islam> | <https://github.com/umicom-foundation/Bits2Banking/tree/main/content/volumes/introduction-to-islam> |
| Volume 2 — Bits to Banking | `bits-to-banking` | <https://github.com/umicom-foundation/Bits2Banking/tree/main/raw_docs/bits-to-banking> | <https://github.com/umicom-foundation/Bits2Banking/tree/main/content/volumes/bits-to-banking> |

## How to add a new volume (quick)
1. Create a folder: `raw_docs/<your-volume-slug>/`
2. Add `.md`, `.docx`, or `.pdf` (optional: `bookcover_<Title>.png`)
3. Commit to `main` — the bot writes normalized `.md` into `content/volumes/<slug>/`

See: **[Quick Upload via raw_docs](CONTRIBUTING_RAW_DOCS.md)** for details.




## Python Primer for Contributors


# Python Primer for Contributors

This is a **practical crash course**: just enough Python to read, tweak, and trust our scripts.

## 1) Running Python

```bash
python --version
python scripts/ingest.py
```text

(If a virtual environment is used, we’ll document it in the script header.)

## 2) Paths with `pathlib`

```python
from pathlib import Path

repo = Path(__file__).resolve().parents[1]
raw = repo / "raw_docs"
content = repo / "content"
for p in raw.glob("**/*"):
    print(p)
```text

## 3) Reading and writing text files

```python
from pathlib import Path

text = Path("example.md").read_text(encoding="utf-8")
Path("out.md").write_text(text, encoding="utf-8")
```text

## 4) Recognising chapters by filename

We keep human‑friendly names with spaces. To detect chapters reliably, match patterns like `chapter<number>_Title.ext` (case‑insensitive).

```python
import re
from pathlib import Path

chapter_re = re.compile(r"chapter\s*(\d+)", re.IGNORECASE)

def chapter_num(path: Path) -> int | None:
    m = chapter_re.search(path.stem)
    return int(m.group(1)) if m else None
```text

## 5) Ordering chapters safely (idempotent)

```python
def order_chapters(paths):
    with_numbers = [(chapter_num(p), p) for p in paths]
    # Sort: numbered first (by number), then the rest by name
    with_numbers.sort(key=lambda t: (t[0] is None, t[0] if t[0] is not None else 10**9, str(t[1]).lower()))
    return [p for _, p in with_numbers]
```text

Gaps (e.g., chapter 1, 2, 4) won’t break ordering; chapter 4 just comes after 2.

## 6) Inferring metadata from filenames

When metadata is missing, we infer from the filename: title and (if present) author/date tokens.

```python
def infer_title(path: Path) -> str:
    # Strip 'chapterN_' prefix if present and use remaining words
    name = chapter_re.sub("", path.stem).strip(" _-")
    return name.replace("_", " ").strip() or path.stem
```text

## 7) Combining chapters into one Markdown

```python
def combine_markdown(chapter_files, title):
    parts = [f"# {title}\n\n"]
    for f in chapter_files:
        parts.append(Path(f).read_text(encoding="utf-8").strip() + "\n\n")
    return "\n".join(parts)
```text

## 8) Clear, human error messages

Whenever something goes wrong, print messages that explain **what** and **how to fix**:

```python
def error(msg: str):
    raise SystemExit(f"[ERROR] {msg}\nPlease check the filename or content and try again.")
```text

Examples:
- Missing cover image → “Cover not found. Place an image named ‘cover.*’ alongside the manuscript.”
- Bad image path in a chapter → “Image ‘assets/fig1.png’ not found. Ensure it exists and the path is correct.”

## 9) Converting Markdown → DOCX/PDF (overview)

Tools we may use (documented elsewhere in the repo):
- `pandoc` for `.md` → `.docx`/`.pdf`
- Python wrappers or shell commands to drive Pandoc

Example shell (conceptual):

```bash
pandoc book.md -o book.docx --resource-path=.:assets
pandoc book.md -o book.pdf  --resource-path=.:assets
```text

## 10) Tiny exercise (optional)

- Create two files: `chapter1_Intro.md` and `chapter5_Advanced.md` with one heading each.
- Use the `order_chapters` function to verify ordering is 1 then 5.
- Infer titles with `infer_title` and print them.
- Combine the two into one Markdown string.

That’s the practical Python you’ll see in our scripts.



## Effective Communication Skills Course


# Effective Communication Skills Course

**Author:** Tamkin Riaz  
**Location:** London, June 2025  
---

## Foreword

Effective communication is the foundation of human interaction. Whether in personal relationships, professional settings, or global collaborations, the ability to communicate clearly and empathetically defines success.  
This book is designed to provide a structured, practical approach to mastering communication skills that are essential in today’s interconnected world.  

---

## About the Author

**Tamkin Riaz** is an experienced educator and trainer based in London, specializing in leadership development, communication, and professional skills. His career spans mentoring, teaching, and empowering individuals from diverse cultural and professional backgrounds.  

---

## Introduction

Communication is more than words—it is the art of connecting ideas, emotions, and intentions. This course-book introduces essential communication principles and provides practical tools to help learners improve listening, speaking, writing, and interpreting nonverbal cues.  

The structure follows a modular design, allowing students to focus on specific areas while building toward a complete mastery of effective communication skills.  

---

## Executive Summary

- **Module 1:** Understanding the Communication Process  
- **Module 2:** Active Listening Skills  
- **Module 3:** Verbal Communication Techniques  
- **Module 4:** Nonverbal Communication  
- **Module 5:** Written Communication  

Each module includes **overview, objectives, lessons, activities, and assessments**, making it practical and learner-focused.  

---

# Course Syllabus

### Module 1: Understanding the Communication Process
**Overview:** Introduces the fundamental elements of communication.  
**Learning Objectives:**
- Define communication and its importance.  
- Identify components: sender, receiver, message, channel, encoding, decoding, feedback, context, noise.  
- Differentiate communication types: verbal, nonverbal, written, visual.  
- Recognize and overcome barriers.  

**Content:**  
- Lesson 1: Introduction to Communication  
- Lesson 2: The Communication Process Model  
- Lesson 3: Communication Channels  
- Lesson 4: Barriers to Communication  

**Activities:** Self-Assessment Quiz, Case Study, Discussion Forum  
**Assessment:** Multiple-choice quiz on key concepts  

---

### Module 2: Active Listening Skills
**Overview:** Develops active listening, a vital skill for understanding and responding effectively.  

**Learning Objectives:**  
- Define active listening and its benefits.  
- Identify principles: attention, feedback, defer judgment, appropriate response.  
- Apply techniques in communication scenarios.  
- Avoid barriers.  

**Content:**  
- Lesson 1: What is Active Listening?  
- Lesson 2: Principles of Active Listening  
- Lesson 3: Techniques for Active Listening  
- Lesson 4: Barriers to Active Listening  

**Activities:** Role-play, Video Analysis, Self-reflection  
**Assessment:** Practical listening exercise  

---

### Module 3: Verbal Communication Techniques
**Overview:** Explores how to use language effectively across contexts.  

**Learning Objectives:**  
- Use clear, concise language.  
- Adapt to audience and situation.  
- Apply appropriate tone and volume.  
- Avoid jargon.  
- Use persuasion.  

**Content:**  
- Lesson 1: Choosing the Right Words  
- Lesson 2: Adapting to Your Audience  
- Lesson 3: Tone and Volume  
- Lesson 4: Persuasive Language  

**Activities:** Language Analysis, Presentation, Debate  
**Assessment:** Presentation evaluation  

---

### Module 4: Nonverbal Communication
**Overview:** Examines body language, facial expressions, tone of voice.  

**Learning Objectives:**  
- Identify types: expressions, posture, gestures, touch, proxemics.  
- Understand emotional impact.  
- Interpret cues accurately.  
- Use nonverbal to support verbal.  
- Recognize cultural differences.  

**Content:**  
- Lesson 1: Types of Nonverbal Communication  
- Lesson 2: Interpreting Nonverbal Cues  
- Lesson 3: Using Nonverbal Communication Effectively  
- Lesson 4: Cultural Differences  

**Activities:** Observation, Video/Image Analysis, Role-play  
**Assessment:** Interpretation exercise  

---

### Module 5: Written Communication
**Overview:** Develops effective writing skills for professional and social use.  

**Learning Objectives:**  
- Write professional emails.  
- Structure reports.  
- Create engaging posts.  
- Apply grammar and punctuation.  
- Adapt style to audience.  

**Content:**  
- Lesson 1: Email Etiquette  
- Lesson 2: Report Writing  
- Lesson 3: Social Media Writing  
- Lesson 4: Grammar and Punctuation  

**Activities:** Email, Report, Social Media writing tasks  
**Assessment:** Written assignment  

---

## Executive Conclusion

This course has been structured to provide practical skills that learners can apply immediately. Communication is a lifelong skill, and mastery requires consistent practice. By completing the modules and engaging in reflective activities, students will gain the confidence to communicate effectively across personal and professional contexts.  

---

# Index (Placeholder)

Page numbers will be automatically generated in PDF/Word builds.

- Foreword – p. 1  
- About the Author – p. 2  
- Introduction – p. 3  
- Executive Summary – p. 4  
- Module 1 – p. 6  
- Module 2 – p. 14  
- Module 3 – p. 21  
- Module 4 – p. 29  
- Module 5 – p. 37  
- Executive Conclusion – p. 45  

---



## Bits to Banking Open Book

# Bits to Banking — Open Book

Welcome to the Umicom Foundation’s open book. Start with **Volume 1 — Islam: Blueprint for Life**.

## Volume 1 — Islam: Blueprint for Life

- [Introduction to Islam](v001_islam_blueprint_for_life/introduction_to_islam.md)
- [History of Money](v001_islam_blueprint_for_life/history_of_money.md)
- [Decline of Sound Money](v001_islam_blueprint_for_life/decline_of_sound_money.md)
- [Modern Banking & Finance](v001_islam_blueprint_for_life/modern_banking_and_finance.md)
- [Technology & Banking](v001_islam_blueprint_for_life/technology_and_banking.md)
- [Islamic Finance & the Future](v001_islam_blueprint_for_life/islamic_finance_and_future.md)
- [Governance Firewalls](v001_islam_blueprint_for_life/governance_firewalls.md)
- [Hall of Shame — Collaboration & Betrayal](v001_islam_blueprint_for_life/hall_of_shame_collaboration_and_betrayal.md)
- [Umicom ABS Coin (Asset-Backed)](v001_islam_blueprint_for_life/umicom_abs_coin.md)
- [Recap](v001_islam_blueprint_for_life/recap.md)



## history of money

﻿# Chapter 2 — History of Money (5,000 Years) and Islam’s Ethic of Trade

Money is a tool. In righteous hands and just systems, it enables exchange, investment, and prosperity. In corrupt systems, it becomes an engine of exploitation. Islam enters this story with a **moral compass**: honest weights, fair contracts, real assets, shared risk, and a strict prohibition of **riba** (interest/usury). This chapter surveys money’s long arc—from barter to bullion to banknotes to today’s fiat—then shows how Islam corrected abuse and built trust.

## 2.1 Why Study Money

Because money shapes **daily life**: wages, food prices, savings, charity, and public services. If money can be created at will by a few or chained to interest, it will quietly transfer wealth from the many to the few. Islam commands **justice** and **measure**:

> وَأَقِيمُوا الْوَزْنَ بِالْقِسْطِ وَلَا تُخْسِرُوا الْمِيزَانَ (الرحمن 9)
> *“Establish weight in justice and do not fall short in the balance.”* (Q 55:9)
>
> وَيْلٌ لِّلْمُطَفِّفِينَ الَّذِينَ إِذَا اكْتَالُوا عَلَى النَّاسِ يَسْتَوْفُونَ وَإِذَا كَالُوهُمْ أَوْ وَّزَنُوهُمْ يُخْسِرُونَ (المطففين 1–3)
> *“Woe to those who give less in measure—who, when they receive by measure from people, take in full; but when they measure or weigh for them, give less.”* (Q 83:1–3)

## 2.2 A Quick Timeline (5,000 Years)

- **Barter → Commodity Money:** Early markets swapped goods; then widely valued commodities (salt, grain, beads, livestock) became money.
- **Metals (Copper, Silver, Gold):** Durable, divisible, and portable. Ancient Lydia minted coins (~7th c. BCE); weights/assays built trust.
- **Islamic Era (7th–10th c. CE):** With Islam’s spread, **ethics** and **law** standardized trade across continents. Contracts (murābaḥah, muḍārabah), trust networks, and **sound coinage** supported huge caravans and maritime routes.
- **Bills of Exchange & Paper:** Merchants used promissory notes and **sakk** (cheques). Later, state paper claims to metal emerged.
- **Banking & Central Banking:** Receipts for deposited gold/silver circulated as money; over-issuance led to panics. Central banks arose to backstop banks—often socializing losses.
- **Fiat Era (1971→):** The US ended dollar–gold convertibility; fiat currencies float. Now money is ledger entries created largely via **interest-bearing debt**.

## 2.3 Arabia Before Islam → Caravans and Markets

Pre-Islamic Arabia had seasonal markets (e.g., ʿUkāẓ), trade caravans between Yemen–Shām, and exposure to Byzantine and Sasanian coins. Economic life was vibrant but **uneven**: cheating in measure, usurious debt, and predatory contracts existed. Islam confronted this with **honesty**, **mercy**, and **law**—preserving enterprise while removing exploitation.

## 2.4 The Prophet ﷺ as a Trader

The Prophet ﷺ worked as a merchant, **sincere and trustworthy** (al-Ṣādiq al-Amīn). He partnered with **Khadīja** (رضي الله عنها), honoring contracts and sharing profits fairly. He taught that trade must be free of fraud, deception, and riba. **Trust**—truthful disclosure, timely payment, fulfillment—was the currency that multiplied business and brought **barakah** (blessing).

## 2.5 Contracts Islam Encouraged

- **Muḍārabah** — investor provides capital, entrepreneur provides effort; profits shared by ratio; **losses** borne by capital unless negligence.
- **Mushārakah** — equity partnership; profits by agreement, losses by capital share.
- **Murābaḥah** — cost-plus sale of a real, owned asset (not a disguised loan).
- **Salam & Istisnāʿ** — pre-paid/agreed manufacture for real needs, with clarity and delivery terms.
- **Ijārah** — leasing use-rights, not selling forbidden uncertainty.

These reflect Islam’s rule: **no guaranteed return without bearing risk** and **no money-from-money** without real trade or assets.

## 2.6 Islamic Coinage and Global Finance

Under **ʿAbd al-Malik** (Umayyad), the first **purely Islamic dinars/dirhams** were minted: Qur’anic inscriptions, no portraits, stable weights. Bimetallic standards (gold dinar, silver dirham) created reliable pricing across regions and centuries. Muslim merchants stitched together trade from **al-Andalus to China**, using fair contracts and credible coinage.

> وَأَحَلَّ اللَّهُ الْبَيْعَ وَحَرَّمَ الرِّبَا (البقرة 275)
> *“Allah has permitted trade and forbidden riba.”* (Q 2:275)

## 2.7 Riba in Exchange — Why “Intrinsic Value” Matters

The Prophet ﷺ defined exchange of **ribawi** items:

> «الذَّهَبُ بِالذَّهَبِ، وَالْفِضَّةُ بِالْفِضَّةِ، وَالْبُرُّ بِالْبُرِّ، وَالشَّعِيرُ بِالشَّعِيرِ، وَالتَّمْرُ بِالتَّمْرِ، وَالْمِلْحُ بِالْمِلْحِ، مِثْلًا بِمِثْلٍ، يَدًا بِيَدٍ؛ فَإِذَا اخْتَلَفَتْ هَذِهِ الأَصْنَافُ فَبِيعُوا كَيْفَ شِئْتُمْ إِذَا كَانَ يَدًا بِيَدٍ» (مسلم)
> *“Gold for gold, silver for silver, wheat for wheat, barley for barley, dates for dates, and salt for salt—like for like, equal for equal, hand to hand; if the kinds differ, sell as you wish, so long as it is hand to hand.”* (Muslim)

**Bilāl’s dates** example shows **riba al-faḍl**: unequal swap of the same kind on the spot is forbidden. The principle protects markets from **hidden exploitation**. From this, scholars derived that **money**—being a standard of value—should not become a tool to **extract value without risk**. Our project’s thesis (to be debated respectfully) is that **fiat**—created at will and lent at interest—facilitates systemic riba and **hidden taxation via inflation**, whereas **asset-backed** or intrinsically valuable money better aligns with Islamic aims.

> وَمَا آتَيْتُم مِّن رِّبًا لِّيَرْبُوَا فِي أَمْوَالِ النَّاسِ فَلَا يَرْبُوا عِندَ اللَّهِ (الروم 39)
> *“What you give in riba to increase within the wealth of people does not increase with Allah.”* (Q 30:39)

## 2.8 Supremacist Empires, Colonial Currency, and Modern Apartheid-Like Controls

History shows that **supremacist ideologies** weaponize money. Empires imposed currency boards and debt to control colonies. In the 20th century, **Nazism** dehumanized minorities and plundered economies. In recent times, **Zionism as a political project** has produced policies—**dispossession, settlement expansion, and collective punishment**—that crush Palestinian economic life. Checkpoints, blockades, and permit regimes function like **financial throttles**: they fragment markets, destroy family wealth, and trap youth in unemployment. Islam condemns such oppression and calls us to defend the weak, speak truth, and build **halal alternatives**.

>… مَن قَتَلَ نَفْسًا بِغَيْرِ نَفْسٍ أَوْ فَسَادٍ فِي ٱلْأَرْضِ فَكَأَنَّمَا قَتَلَ ٱلنَّاسَ جَمِيعًا (المائدة 32)
> *“…whoever kills a soul—unless [in retribution] or for (grave) corruption in the land—it is as if he had slain all mankind.”* (Q 5:32)
>
> يَا أَيُّهَا الَّذِينَ آمَنُوا كُونُوا قَوَّامِينَ لِلَّهِ شُهَدَاءَ بِالْقِسْطِ (المائدة 8)
> *“O you who believe! Be steadfast for Allah, witnesses in justice.”* (Q 5:8)

## 2.9 Lessons for Today

- **Sound money** (gold/silver or strong asset-backing) restrains arbitrary creation, aligns with **real economy**, and discourages riba.
- **Contracts** must link financing to **real assets/work**, not to compounding debt.
- **Justice** in policy: end structures that strip wealth from the vulnerable by design.
- **Build** halal rails—transparent, asset-backed instruments; ethical fintech; community funds.

This is the road toward our **Umicom Asset-Backed Security Coin**: a Shariah-aligned unit of account and exchange anchored to verified, audited assets—constructed to **serve people**, not exploit them.

## Supplication (Duʿāʾ)

### Arabic
اللَّهُمَّ بَارِكْ لَنَا فِي رِزْقِنَا، وَاجْعَلْ مَالَنَا قُوَّةً لِلطَّاعَةِ، وَحِصْنًا مِنَ الظُّلْمِ، وَنَجِّنَا مِنَ الرِّبَا وَمِنْ نُظُمِ الظُّلْمِ، وَارْزُقْنَا صِدْقًا فِي الْبَيْعِ وَالشِّرَاءِ وَالْعُقُودِ.

### English
### O Allah, bless our provision; make our wealth a strength for obedience and a shield against injustice; save us from riba and oppressive systems; and grant us truthfulness in buying, selling, and contracts

## Chapter Summary (Refresher)

- Money’s form changed across millennia, but Islam’s **ethic** stayed constant: honest measure, fair exchange, no riba.
- The Prophet ﷺ modeled trustworthy trade; Islamic contracts align **profit with risk** and **finance with real assets**.
- **Ribawi rules** (gold/silver, like-for-like, hand-to-hand) protect markets from exploitation.
- **Fiat + interest** tends to centralize power and silently tax the poor; **asset-backed** money better serves justice.
- Supremacist projects—from Nazism to modern apartheid-like policies—weaponize money; Islam commands we **stand for justice** and **build alternatives**.




## Chapter 3 The Decline of Sound Money

﻿
# Chapter 3 — The Decline of Sound Money

## 3.1 Colonialism and currency control
European empires conquered lands and **replaced intrinsic money** with currencies tied to their banks. Debt and taxation in foreign money created dependence.

## 3.2 From receipts to fiat
Paper began as a **claim on gold/silver**. Over time, issuers printed more notes than reserves → **fiat** (value by decree).

## 3.3 Bretton Woods (1944) → 1971
The dollar was pegged to gold at $35/oz; the world pegged to the dollar. In **1971**, the dollar left gold entirely. From then on: unlimited printing and chronic inflation.

> **“Woe to those who give less than due…”** *(Al‑Muṭaffifīn 83:1–3)* — inflation quietly reduces people’s purchasing power.

## 3.4 Riba and the debt engine
Loans are created with **interest**; money to pay the interest does not exist unless new debt is issued. Nations and families become permanent debtors.

> **“…If you do not desist, then be informed of a war from Allah and His Messenger.”**
> **فَإِن لَّمْ تَفْعَلُوا فَأْذَنُوا بِحَرْبٍ مِّنَ ٱللَّهِ وَرَسُولِهِ** *(Al‑Baqarah 2:279)*

## 3.5 The 2008 lesson
Risky mortgages were bundled and sold as safe. When borrowers defaulted, the system crashed. Banks were rescued by money printing; ordinary people were not.

## 3.6 Why this matters
- Inflation is **hidden theft** from savers and workers.
- Riba concentrates wealth with lenders.
- Sound money and just contracts are **moral necessities**, not nostalgia.

### Supplication
### اللَّهُمَّ نَجِّنَا مِنْ ظُلْمِ الرِّبَا، وَاهْدِنَا لِبِنَاءِ نِظَامٍ عَادِلٍ قَائِمٍ عَلَى شَرِيعَتِكَ
### O Allah, save us from the oppression of riba and guide us to build a just system based on Your Sharīʿah

[← Chapter 2](history_of_money.md) | [Next → Chapter 4](modern_banking_and_finance.md)



## Bits to Banking Master Book



Bits to Banking
Master Guide — From Bits → Banking → Calypso
Dedication and Acknowledgements
First and foremost, all thanks are due to Allah, who blessed us with knowledge, patience, and strength to pursue this project. I thank my parents, my late father who always encouraged me to seek knowledge, and my brothers and sisters who supported me throughout the years.
I extend heartfelt thanks to my family, mentors, friends, and colleagues who shaped my journey of learning and service. To my dear friend Mujahid Sufian and his wife Dr. Alefiah Mubeen, steadfast supporters of the Umicom Foundation and now contributors to this book, bringing deep expertise in Machine Learning and Data Science. To Dr. Ahmed El Banaa, physiotherapy specialist at the Military Hospital in Egypt, who worked tirelessly with Palestinian patients, and has become a close friend and brother. To Islam Mahmoud, who despite injury continued designing, documenting and supporting aid distribution in Gaza. To Mohammed Al Danaf and his family for their bravery and sacrifice in delivering aid and supporting through their business network in Gaza. To Khaled Matter, a mobile developer from Gaza, who even while injured volunteered to share knowledge through his phone. To Mohammed Soliman, always rushing to support financially and contributing his experience. To Saheesh Rafeeque, business partner and founder of Eastern Bridge, for his backing and logistics expertise.
I also extend heartfelt thanks to Tarneem Elyan, an Artificial Intelligence and Data Engineer from North Gaza, who despite the hardships of war has volunteered her time to distribute humanitarian aid in her community and to contribute her knowledge to this book. Her courage and expertise in data science and AI bring hope and practical value to our shared mission.
Finally, to all the brave men and women who risked their lives delivering humanitarian aid, many martyred or injured, and to the doctors serving Palestinians in Egypt, and to every software engineer, reviewer, and student who contributes to this vision—this book is dedicated to you.
How to Use This Series
• ≤ 4 chapters per volume. Small, printable, and easy to study.
• Kid → Teen → Adult. We begin with everyday analogies, then level up with code and labs.
• Smooth transitions. Each volume ends with a 1-page refresh and “what’s next.”
• Code in boxes; simple diagrams. Monospace, high contrast, print-friendly.
Roadmap at a Glance
• Vol. 1 — Foundations of Computing: bits, gates, Boolean, binary & hex, CPU, ISA (x86/ARM/RISC-V), assembly → C → C++ → Java.
• Vol. 2 — Operating Systems & Linux From Scratch: what an OS does, kernel vs userland, processes, memory, filesystems, network; build a tiny Linux.
• Vol. 3 — Databases & Data Engineering: PostgreSQL/Oracle, indexing/transactions, NoSQL, warehousing, ETL, data quality.
• Vol. 4 — Networking & Protocols: TCP/UDP, HTTP/REST, TLS; FIX, SWIFT ISO 20022, FpML; queues and messaging.
• Vol. 5 — Cybersecurity for Builders: threats, OWASP, memory bugs, secrets/KMS, secure deployment, audit/compliance.
• Vol. 6 — Programming Deep Dives: C/C++, Java (JVM, concurrency), Python, Rust, Zig, PHP; patterns, testing, packaging, web & mobile overviews.
• Vol. 7 — Finance & Treasury Primer: markets 101, asset classes, front/middle/back office, PnL, risk, settlement, clearing; history of money → digital.
• Vols. 8–12 — Calypso Series (multiple slim books): Fast-Track; Architecture & Core; Risk Compute; Position/Liquidity/KPI; Market Data/Quotes; Integration/Messaging.
• Vol. 13 — Customization & Extensions: SPIs, adapters, scheduled tasks, UI add-ons, reports; multi-language examples.
• Vol. 14 — Testing, Deployment & Ops: CATT, perf/load, observability, HA/DR, upgrades, blue/green, rollback.
• Vol. 15 — RISC-V & Advanced Computing: assembly → Linux on RISC-V, QEMU/WSL2 labs, cross-compiling, tiny compiler projects.
• Vol. 16 — Projects & Capstones: commodity exchange, privacy-first video platform, social + fundraising site, UmiCOIN (asset-backed).
Mini-Introductions (Sample)
Volume 1 — Foundations of Computing
What you’ll get: the “why” behind every 1 and 0. Play with binary using fingers, build AND/OR with paper switches, watch a CPU “fetch-decode-execute,” then translate simple programs from Python → C → assembly.
You’ll be able to:
1) Explain binary and overflow to a kid.
2) Write a 10-line program and peek at its assembly.
3) Connect CPU cycles to how a trade instruction is processed.
Volume 2 — Operating Systems & Linux From Scratch
We explain processes, memory, files, users, then compile a tiny Linux. You’ll boot your own system and run basic tools.
You’ll be able to:
1) Read process lists and memory usage.
2) Understand system services (systemd) and logs.
3) Prepare a finance-friendly Linux profile.
Video Micro-Lessons (Titles & Descriptions)
• Bits vs Switches (3 min) — A light switch becomes a 1 or 0; two switches make AND/OR.
• Binary Counting with Fingers (5 min) — Count to 31 on one hand; meet overflow.
• From CPU to Instructions (6 min) — Fetch, decode, execute; registers are sticky notes.
• Hello, Assembly (7 min) — Add two numbers with registers & memory moves.
• C to Machine Code (8 min) — Compile a tiny C program and compare assembly.
• Processes & Memory (6 min) — Stacks/heaps/syscalls; why programs crash.
• Build a Tiny Linux (8 min) — Compile + boot a minimal system; first prompt!
• Your First REST Endpoint (5 min) — Create /hello; add a nightly job.
Lightweight Diagrams (Printable ASCII)
[CPU]--fetch-->[Instruction]--decode-->[Execute]
   |                               |
 [Registers] <-------------------- [ALU]
Process
  ├─ Code (read-only)
  ├─ Heap (grows up)     <-- new objects
  └─ Stack (grows down)  <-- function calls
REST Control Plane
Client -> Risk Services -> Risk Server
   \__ health/status      \__ MQ + compute
On-Ramp Labs (Quick Wins)
• Build & run a one-file program in C, C++, Java, Python.
• Boot a tiny Linux VM; list processes & services.
• Create /hello in Java; schedule a nightly job; check logs & metrics.
• Create a DB table, insert a row, read it back.
Glossary (Short & Sweet)
• Bit — Tiniest piece of info: 0 or 1.
• CPU — The ‘thinker’ that follows instructions fast.
• Register — A tiny ultra-fast box inside the CPU.
• Process — A running program with its own memory world.
• Message Queue — A mailbox for servers to pass work.
• Latency — How long something takes (track p95/p99).
Where to Go Next
Start with Volume 1 — Foundations of Computing, then Volume 2 — Operating Systems & Linux From Scratch. When ready, enter the Calypso volumes for banking-grade platforms.



## Chapter 4 Modern Banking and Finance

﻿
# Chapter 4 — Modern Banking and Finance

## 4.1 How banks create money
When a bank issues a loan, it **credits** the borrower’s account with new deposits — money created from nothing — then demands repayment **plus interest**.

## 4.2 Central banks and governments
Governments sell bonds; central banks buy them with newly created reserves. Taxpayers carry the **interest burden**.

> **“Allah destroys riba and gives increase for charities.”**
> **يَمْحَقُ ٱللَّهُ ٱلرِّبَا وَيُرْبِى ٱلصَّدَقَـٰتِ** *(Al‑Baqarah 2:276)*

## 4.3 Why it collapses
Debt must grow to service past interest. Eventually, defaults rise; the state prints more money → inflation. The cycle repeats.

## 4.4 Real‑world impacts (case snapshots)
- **Student debt (US)** — lifelong repayments for millions.
- **IMF programs** — currency devaluation and austerity.
- **Egypt** — repeated devaluations crush wages and savings.
- **Gaza** — transfers blocked; fees consume aid.

> **“A time will come when everyone will consume riba; if he does not consume it, its dust will reach him.”** *(Abū Dāwūd 3331)*

## 4.5 Islam’s alternative at a glance
- **Mudarabah/Musharakah** — risk‑sharing, not risk‑shifting.
- **Ijarah** — fair leasing.
- **Zakat/Waqf** — social safety and productive endowments.

### Supplication
### اللَّهُمَّ عَلِّمْنَا مَا يَنْفَعُنَا، وَانْفَعْنَا بِمَا عَلَّمْتَنَا، وَارْزُقْنَا مَالًا حَلَالًا طَيِّبًا
### O Allah, teach us what benefits us, benefit us through what You have taught us, and grant us pure halal wealth

[← Chapter 3](decline_of_sound_money.md) | [Next → Chapter 5](technology_and_banking.md)



## Master Guide

Bits to Banking
Master Guide — From Bits → Banking → Calypso
Dedication and Acknowledgements
First and foremost, all thanks are due to Allah, who blessed us with knowledge, patience, and strength to pursue this project. I thank my parents, my late father who always encouraged me to seek knowledge, and my brothers and sisters who supported me throughout the years.
I extend heartfelt thanks to my family, mentors, friends, and colleagues who shaped my journey of learning and service. To my dear friend Mujahid Sufian and his wife Dr. Alefiah Mubeen, steadfast supporters of the Umicom Foundation and now contributors to this book, bringing deep expertise in Machine Learning and Data Science. To Dr. Ahmed El Banaa, physiotherapy specialist at the Military Hospital in Egypt, who worked tirelessly with Palestinian patients, and has become a close friend and brother. To Islam Mahmoud, who despite injury continued designing, documenting and supporting aid distribution in Gaza. To Mohammed Al Danaf and his family for their bravery and sacrifice in delivering aid and supporting through their business network in Gaza. To Khaled Matter, a mobile developer from Gaza, who even while injured volunteered to share knowledge through his phone. To Mohammed Soliman, always rushing to support financially and contributing his experience. To Saheesh Rafeeque, business partner and founder of Eastern Bridge, for his backing and logistics expertise.
I also extend heartfelt thanks to Tarneem Elyan, an Artificial Intelligence and Data Engineer from North Gaza, who despite the hardships of war has volunteered her time to distribute humanitarian aid in her community and to contribute her knowledge to this book. Her courage and expertise in data science and AI bring hope and practical value to our shared mission.
Finally, to all the brave men and women who risked their lives delivering humanitarian aid, many martyred or injured, and to the doctors serving Palestinians in Egypt, and to every software engineer, reviewer, and student who contributes to this vision—this book is dedicated to you.
How to Use This Series
• ≤ 4 chapters per volume. Small, printable, and easy to study.
• Kid → Teen → Adult. We begin with everyday analogies, then level up with code and labs.
• Smooth transitions. Each volume ends with a 1-page refresh and “what’s next.”
• Code in boxes; simple diagrams. Monospace, high contrast, print-friendly.
Roadmap at a Glance
• Vol. 1 — Foundations of Computing: bits, gates, Boolean, binary & hex, CPU, ISA (x86/ARM/RISC-V), assembly → C → C++ → Java.
• Vol. 2 — Operating Systems & Linux From Scratch: what an OS does, kernel vs userland, processes, memory, filesystems, network; build a tiny Linux.
• Vol. 3 — Databases & Data Engineering: PostgreSQL/Oracle, indexing/transactions, NoSQL, warehousing, ETL, data quality.
• Vol. 4 — Networking & Protocols: TCP/UDP, HTTP/REST, TLS; FIX, SWIFT ISO 20022, FpML; queues and messaging.
• Vol. 5 — Cybersecurity for Builders: threats, OWASP, memory bugs, secrets/KMS, secure deployment, audit/compliance.
• Vol. 6 — Programming Deep Dives: C/C++, Java (JVM, concurrency), Python, Rust, Zig, PHP; patterns, testing, packaging, web & mobile overviews.
• Vol. 7 — Finance & Treasury Primer: markets 101, asset classes, front/middle/back office, PnL, risk, settlement, clearing; history of money → digital.
• Vols. 8–12 — Calypso Series (multiple slim books): Fast-Track; Architecture & Core; Risk Compute; Position/Liquidity/KPI; Market Data/Quotes; Integration/Messaging.
• Vol. 13 — Customization & Extensions: SPIs, adapters, scheduled tasks, UI add-ons, reports; multi-language examples.
• Vol. 14 — Testing, Deployment & Ops: CATT, perf/load, observability, HA/DR, upgrades, blue/green, rollback.
• Vol. 15 — RISC-V & Advanced Computing: assembly → Linux on RISC-V, QEMU/WSL2 labs, cross-compiling, tiny compiler projects.
• Vol. 16 — Projects & Capstones: commodity exchange, privacy-first video platform, social + fundraising site, UmiCOIN (asset-backed).
Mini-Introductions (Sample)
Volume 1 — Foundations of Computing
What you’ll get: the “why” behind every 1 and 0. Play with binary using fingers, build AND/OR with paper switches, watch a CPU “fetch-decode-execute,” then translate simple programs from Python → C → assembly.
You’ll be able to:
1) Explain binary and overflow to a kid.
2) Write a 10-line program and peek at its assembly.
3) Connect CPU cycles to how a trade instruction is processed.
Volume 2 — Operating Systems & Linux From Scratch
We explain processes, memory, files, users, then compile a tiny Linux. You’ll boot your own system and run basic tools.
You’ll be able to:
1) Read process lists and memory usage.
2) Understand system services (systemd) and logs.
3) Prepare a finance-friendly Linux profile.
Video Micro-Lessons (Titles & Descriptions)
• Bits vs Switches (3 min) — A light switch becomes a 1 or 0; two switches make AND/OR.
• Binary Counting with Fingers (5 min) — Count to 31 on one hand; meet overflow.
• From CPU to Instructions (6 min) — Fetch, decode, execute; registers are sticky notes.
• Hello, Assembly (7 min) — Add two numbers with registers & memory moves.
• C to Machine Code (8 min) — Compile a tiny C program and compare assembly.
• Processes & Memory (6 min) — Stacks/heaps/syscalls; why programs crash.
• Build a Tiny Linux (8 min) — Compile + boot a minimal system; first prompt!
• Your First REST Endpoint (5 min) — Create /hello; add a nightly job.
Lightweight Diagrams (Printable ASCII)
[CPU]--fetch-->[Instruction]--decode-->[Execute]
   |                               |
 [Registers] <-------------------- [ALU]
Process
  ├─ Code (read-only)
  ├─ Heap (grows up)     <-- new objects
  └─ Stack (grows down)  <-- function calls
REST Control Plane
Client -> Risk Services -> Risk Server
   \__ health/status      \__ MQ + compute
On-Ramp Labs (Quick Wins)
• Build & run a one-file program in C, C++, Java, Python.
• Boot a tiny Linux VM; list processes & services.
• Create /hello in Java; schedule a nightly job; check logs & metrics.
• Create a DB table, insert a row, read it back.
Glossary (Short & Sweet)
• Bit — Tiniest piece of info: 0 or 1.
• CPU — The ‘thinker’ that follows instructions fast.
• Register — A tiny ultra-fast box inside the CPU.
• Process — A running program with its own memory world.
• Message Queue — A mailbox for servers to pass work.
• Latency — How long something takes (track p95/p99).
Where to Go Next
Start with Volume 1 — Foundations of Computing, then Volume 2 — Operating Systems & Linux From Scratch. When ready, enter the Calypso volumes for banking-grade platforms.



## Chapter 5 Technology and Banking

﻿
# Chapter 5 — Technology and Banking

## 5.1 Bits to value
Computers store and move **bits (0/1)**. Your bank balance is a number in a **database**.

## 5.2 Banking tech stack (simplified)
- **Core banking systems** — accounts, payments, loans.
- **Treasury/Capital Markets** — platforms like Calypso/Murex for trading & risk.
- **Databases** — Oracle/SQL store transactions.
- **Messaging** — SWIFT/FIX/FpML move instructions between banks.

## 5.3 Milestones
- **Sakk** (cheques) and **hawāla** — Islamic Golden Age.
- **Double‑entry** — merchant accounting revolution.
- **Telegraph** → early electronic transfers.
- **SWIFT (1973)**, **ATMs (1967)**, **online/mobile banking**.
- **Blockchain (2009–)** — distributed ledgers (powerful but often speculative when unbacked).

## 5.4 Why Islam matters here
Tech is a tool. Without Sharīʿah principles (no riba/gharar/maysir; real assets; transparency), technology can **amplify injustice**.

### Supplication
### اللَّهُمَّ وَفِّقْنَا لِتَسْخِيرِ التِّقْنِيَةِ فِي الْخَيْرِ وَالْعَدْلِ
### O Allah, enable us to harness technology for good and justice

[← Chapter 4](modern_banking_and_finance.md) | [Next → Chapter 6](islamic_finance_and_future.md)



## Chapter 6 Islamic Finance The Future

﻿
# Chapter 6 — Islamic Finance & The Future

## 6.1 Core prohibitions
- **Riba (interest)** — guaranteed gain on loans.
- **Gharar** — excessive uncertainty/ambiguity.
- **Maysir** — gambling/speculation.

## 6.2 Halal contracts
**Mudarabah, Musharakah, Ijarah, Murabaha, Salam, Sukuk** — real assets, real risk.

> **“Do not consume one another’s wealth unjustly; only [in lawful] trade by mutual consent.”**
> **وَلَا تَأْكُلُوا أَمْوَالَكُمْ بَيْنَكُمْ بِالْبَاطِلِ إِلَّا أَن تَكُونَ تِجَارَةً عَن تَرَاضٍ** *(An‑Nisāʾ 4:29)*

## 6.3 Global snapshots
- **Malaysia** — sukuk leadership; strong regulation.
- **Gulf** — scale & ambition; risk of mimicking conventional debt.
- **Pakistan** — legal push toward riba‑free; tough implementation.
- **Sudan** — system‑wide adoption hindered by governance.
- **London** — Western hub showing cross‑faith trust.

## 6.4 Pitfalls & crises
- **Asian Crisis (1997)** — hot money & devaluations.
- **Dubai 2009** — over‑leveraged projects; sukuk design lessons.
- **Cosmetic “Islamic” products** — form without substance.

## 6.5 Everyday impact
- **Families** — musharakah housing vs. interest mortgages.
- **SMEs** — risk‑sharing finance instead of debt traps.
- **Poor** — zakat, waqf, **qard ḥasan** dignity.
- **Environment** — stewardship (khilāfah), no waste/corruption.

### Supplication
### اللَّهُمَّ طَهِّرْ أَمْوَالَنَا، وَبَارِكْ فِي مَعَاشِنَا، وَاجْعَلْنَا مِفْتَاحًا لِلْخَيْرِ
### O Allah, purify our wealth, bless our livelihoods, and make us keys to goodness

[← Chapter 5](technology_and_banking.md) | [Next → Chapter 7](umicom_abs_coin.md)



## Chapter 7 Recap Volume 1 Summary


# Chapter 7 Recap — Volume 1 Summary

- Islam is a complete way of life; justice in trade is worship.
- History shows sound money → stability; debasement → collapse.
- Modern banking creates money as debt; riba enslaves.
- Technology runs finance; without Sharīʿah it amplifies injustice.
- Islamic finance = real assets, risk‑sharing, zakat/waqf.
- Umicom ABS Coin = asset‑backed, transparent, redeemable.

## اللَّهُمَّ اجْعَلْنَا مِنْ أَهْلِ الصِّدْقِ وَالْعَدْلِ، وَوَفِّقْنَا لِخِدْمَةِ خَلْقِكَ
### O Allah, make us people of truth and justice, and grant us success in serving Your creation

[← Chapter 7](umicom_abs_coin.md)



## Chapter 7 Umicom ABS Coin AssetBacked SharīʿahCompliant

﻿
# Chapter 7 — Umicom ABS Coin (Asset‑Backed, Sharīʿah‑Compliant)

## 7.1 The need
- Fiat inflates away savings.
- Unbacked crypto is speculative.
- Many “Islamic” products mimic interest finance.

## 7.2 What Umicom is
A **digital coin backed by real assets** (gold, silver, food, energy, commodities), recorded on a transparent ledger with redeemability.

**Sharīʿah fit:** no riba, no gharar (clear assets/terms), no maysir (value from assets, not chance).

## 7.3 How it works (simple flow)
1) **Assets deposited** → coins minted.
2) **Circulation** → trade, remittances, aid, SME finance.
3) **Redemption** → coin returned for underlying assets.

## 7.4 Who benefits
- **Families** — savings that keep purchasing power.
- **Businesses** — stable unit of account for trade.
- **Communities in crisis** — direct, low‑fee aid.
- **Nations** — issue value tied to real output.

## 7.5 Case sketches
- **Gaza** — aid without 50% transfer losses.
- **Egypt** — inflation‑resistant savings.
- **Africa** — tokenise resources; avoid dollar debt.
- **Remittances** — instant, near‑zero‑cost.

> **“And establish weight in justice and do not make deficient the balance.”** *(Ar‑Raḥmān 55:9)*

### Supplication
### اللَّهُمَّ بَارِكْ فِي مَشْرُوعِ Umicom، وَاجْعَلْهُ سَبِيلًا لِلْعَدْلِ وَالْمَنْفَعَةِ لِلنَّاسِ
### O Allah, bless the Umicom project and make it a path to justice and benefit for people

[← Chapter 6](islamic_finance_and_future.md) | [Next → Recap](recap.md)



## Contributor Basics


# Contributor Basics

Welcome! This short guide helps you (and future contributors) understand the **minimum YAML and Python** needed to read and trust our scripts and automation.

## Chapters

- [YAML in 10 Minutes (for this project)](yaml-for-contributors.md)
- [Python Primer for Contributors](python-primer-for-contributors.md)

> Tip: Keep UK English spelling in docs and comments.



## YAML in 10 Minutes for this project


# YAML in 10 Minutes (for this project)

YAML is a human‑readable format used for configuration—**indentation matters** and uses **spaces only**.

## 1) The absolute basics

### Mappings (key → value)

```yaml
name: Content sanity check
enabled: true
retries: 3
```text

### Lists

```yaml
books:
  - Effective Communication
  - Contributor Basics
  - Leadership & Teamwork
```text

### Nesting (indent with 2 spaces)

```yaml
book:
  title: Effective Communication
  author: Tamkin Riaz
  modules:
    - Understanding the Communication Process
    - Active Listening
```text

> **Important:** Do **not** use tabs. YAML requires spaces. Mixed tabs/spaces cause hard‑to‑read errors.

## 2) Strings and quoting

Unquoted is fine if there are no special characters. Quote when in doubt.

```yaml
title: Effective Communication
safe: "Yes — includes punctuation, : and # are safe here"
path: "content/effective-communication-course/index.md"
```text

Multi‑line strings:

```yaml
description: |
  This course includes:
  - Verbal and non‑verbal communication
  - Listening skills
  - Written communication
```text

## 3) GitHub Actions: minimal anatomy

```yaml
name: Content sanity check

on:
  push:
    paths:
      - "content/**"
  pull_request:
    paths:
      - "content/**"

jobs:
  check:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Run a shell command
        run: echo "Hello YAML"
```text

Key parts you’ll see often:

- `on`: events that trigger the workflow (e.g., `push`, `pull_request`).
- `jobs`: one or more tasks to run.
- `runs-on`: the virtual machine image.
- `steps`: a sequence of actions or shell commands.
- `uses`: re‑use an action.
- `run`: execute a shell command.

## 4) Common mistakes (and how to fix them)

### A) Mixed indentation (tabs vs spaces)

**Problem:** “mapping values are not allowed here” or cryptic errors.  
**Fix:** Ensure only spaces are used; keep consistent indentation (commonly 2 spaces).

### B) Misaligned list items

```yaml
steps:
    - name: One
      run: echo one
  - name: Two  # ← Misaligned under 'steps'
    run: echo two
```text

**Fix:** Align the dashes under the same indent level:

```yaml
steps:
  - name: One
    run: echo one
  - name: Two
    run: echo two
```text

### C) Unintended colon in unquoted strings

```yaml
title: Effective Communication: A Practical Guide   # may parse oddly
```text

**Fix:** Quote it:

```yaml
title: "Effective Communication: A Practical Guide"
```text

### D) Trailing spaces after keys

```yaml
name : Value   # ← space before colon not recommended
```text

**Fix:**

```yaml
name: Value
```text

## 5) Advanced (rarely needed, but good to know)

### Anchors & aliases

```yaml
defaults: &defaults
  retries: 2
  timeout: 30

job:
  <<: *defaults
  retries: 3  # override
```text

### Environment variables in Actions

```yaml
env:
  PYTHONWARNINGS: "ignore"
  APP_ENV: "prod"
```text

## 6) Quick checklist before committing

- Spaces only, consistent indent (2 spaces works well).
- Quote strings with `:` or `#` or special characters.
- Lists aligned at the same column.
- Run your workflow locally if possible or rely on CI feedback.

That’s it—you’re good to read and adjust YAML in this project.



## Effective Communication Skills Course

# Effective Communication Skills Course

📘 **Book:** [effective-communication-course.md](effective-communication-course.md)  
✍️ **Author:** Tamkin Riaz  
📍 **Location:** London, June 2025  
📖 **Version:** 1.0  

---

## Overview

This book provides a complete **Effective Communication Skills Course**, designed to help learners improve their ability to listen, speak, write, and interpret nonverbal cues.  

The course is structured into **five modules**:  

1. Understanding the Communication Process  
2. Active Listening Skills  
3. Verbal Communication Techniques  
4. Nonverbal Communication  
5. Written Communication  

Each module includes **learning objectives, lessons, activities, and assessments** to ensure both knowledge and practice.  

---

## Navigation

- 📄 [Full Book (effective-communication-course.md)](effective-communication-course.md)  
- 📂 [Parent Folder (content/)](../)  

---

## Contribution

We welcome contributions! 🚀  
If you’d like to suggest edits, examples, or additional activities:  

1. Fork this repository  
2. Edit `effective-communication-course.md`  
3. Submit a Pull Request  

Your input helps us make the course more engaging and accessible.  

---



## hello

﻿# Hello from raw_docs



## 0009 Governance Firewalls Designing for Justice

# 0009 — Governance Firewalls: Designing for Justice

It’s not enough to denounce corruption; we must **engineer against it**—in constitutions, budgets, and code.

## Principles (Qur’an & Sunnah)

- **Justice (al-ʿadl):** judge fairly (Q 4:58; Q 5:8).
- **Trusts (amānāt):** render trusts to their people (Q 4:58).
- **No riba/bribery:** end structures that reward extraction (Q 2:275; 2:188).
- **Consultation (shūrā):** participatory decision-making (Q 42:38).

## Institutional firewalls (policy)

1) **Public money, public ledgers:** machine-readable budgets, procurement, and transfers.
2) **Conflict-of-interest regimes:** mandatory disclosures, recusal rules, gift registers.
3) **Open tendering:** competitive bids; publish contracts; blacklist offenders.
4) **Independent audit & courts:** tenure-protected, budget-independent.
5) **Civic oversight:** FOI laws, whistleblower shields, protected press.
6) **Zakat & waqf governance:** clear mandates, audited distribution dashboards.

## Financial firewalls (design)

- **No guaranteed return without risk.**
- **Asset-backed issuance:** money linked to real goods/services.
- **Capital buffers & liquidity corridors** that don’t socialize losses.
- **Real-time transparency:** traceable flows (with privacy safeguards).
- **Smart contracts with Shariah checks:** automated compliance (no interest leg, ownership transfer before sale, etc.).

## Pattern kit (checklists)

- **Procurement checklist:** publish RFP → open bids → award rationale → contract text → delivery milestones → payments log.
- **Public-funds checklist:** inflow sources → allocation rules → disbursement proofs → independent audit → citizen feedback loop.
- **Shariah audit checklist:** contract type → ownership/risk → pricing transparency → settlement timing → no riba/gharar/maysir.

## Toward Umicom (teaser)

A **Shariah-aligned, asset-backed digital unit** can encode these firewalls: issuance against **audited reserves**, on-chain proofs of assets and liabilities, contracts that enforce **risk sharing** and **fair exchange**, and governance that regular people can verify.

## Duʿāʾ

اللَّهُمَّ أَقِمْ بَيْنَنَا قِسْطًا، وَانْصُرْ مَنْ نَصَرَ الْحَقَّ، وَاخْذُلْ مَنْ خَانَ الْأَمَانَةَ.
O Allah, establish justice among us, support those who support truth, and thwart those who betray trusts.

---

**← Previous:** [Hall of Shame](hall_of_shame_collaboration_and_betrayal.md)




## 0008 Hall of Shame Collaboration Corruption and Betrayal

# 0008 — Hall of Shame: Collaboration, Corruption, and Betrayal

This chapter documents **patterns** of collaboration with oppressors and **historical cases** backed by public records. The aim is reform, not rage.

> **Q 4:135:** Stand firm for justice, witnesses for Allah—even against yourselves.
> **Q 2:188:** Do not consume one another’s wealth unjustly or use it to bribe rulers.

## Why leaders sell out

- **Private gain:** money, property, immunity, titles.
- **Foreign leverage:** threats/sanctions or promises of support.
- **Weak institutions:** no audits, no free press, no independent courts.
- **Decayed ethics:** riba-soaked economies that reward extraction.

## Documented historical examples (illustrative)

- **Benedict Arnold** (1780): plotted to surrender West Point for money and rank.
- **Vidkun Quisling** (1940–45): Nazi collaborator in Norway.
- **Philippe Pétain** (Vichy France): collaborationist regime, convicted post-war.
- **Wang Jingwei** (WWII China): Japanese-backed government in Nanjing.
- **Andrey Vlasov** (WWII): led Russian Liberation Army with the Nazis.
- **Mīr Jaʿfar** (1757): defected at Plassey; opened Bengal to Company control.
- **Ephialtes** (480 BCE): betrayed the pass at Thermopylae for reward.
- **Sale of Joan of Arc** (1430): captured then ransomed to enemies.

(*A separate appendix can house extended dossiers with sources.*)

## Islamic framing

- **Rule by revelation, not bribery.**
- **Strong contracts and public ledgers.**
- **Shūrā (consultation)** and independent judiciary.
- **Zakat/waqf** as social floors that weaken “sell-out” incentives.

## Summary

Betrayal recurs across civilizations. Only **systems**—ethical finance, transparent governance, real accountability—cure the disease.

## Duʿāʾ

اللَّهُمَّ احْفَظْ أُمَّتَنَا مِنْ خَوَانَةِ الْأَمَانَةِ، وَارْزُقْنَا قَادَةً عَادِلِينَ، وَانْصُرِ الْمُسْتَضْعَفِينَ فِي كُلِّ مَكَانٍ.
O Allah, protect our community from betrayal, grant us just leaders, and aid the oppressed everywhere.

---

**← Previous:** [0007 — Recap](recap.md)
**Next →** [0009 — Governance Firewalls: Designing for Justice](governance_firewalls.md)




## Bits2Banking Course Library

# 📚 Bits2Banking – Course Library

Welcome to the **Bits2Banking Content Library**.  
Here you will find structured educational books, each living in its own folder under `content/`.  

Our goal is to make every course easy to follow, contribute to, and update.  
Each book includes **foreword, author details, introduction, modules, activities, assessments, and conclusion**.  

---

## Available Courses

### 1. [Effective Communication Skills Course](effective-communication-course/README.md)
*Author:* Tamkin Riaz (London, June 2025)  
*Description:* A complete guide to mastering personal and professional communication through verbal, nonverbal, listening, and writing techniques.  

---

## Contributing

We welcome contributions from learners, educators, and professionals worldwide 🌍.  
To contribute:  

1. Fork the repository  
2. Add or improve content in any course folder  
3. Submit a Pull Request  

---

## Roadmap

Upcoming books in the series (planned):  
- ✅ Effective Communication Skills Course (completed draft)  
- 🔄 Leadership & Teamwork Skills  
- 🔄 Critical Thinking & Problem Solving  
- 🔄 Emotional Intelligence in Professional Life  

---

*This content is part of the **Umicom Foundation – Bits2Banking Project**, dedicated to open education and practical skill-building.*  



## ch00 prelude

﻿# Prelude — Recap & Setup (placeholder)

> This chapter has moved to the new content system.
> For current content, see: `content/v001_islam_blueprint_for_life/`.



## ch01 git GitHub basics

﻿# Git & GitHub Basics (placeholder)

> This chapter has moved to the new content system.
> For current content, see: `content/v001_islam_blueprint_for_life/`.
