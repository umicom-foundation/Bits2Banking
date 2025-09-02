# Bits to Banking — Open Book Project

[![Build](https://github.com/umicom-foundation/Bits2Banking/actions/workflows/build-volume0.yml/badge.svg)](https://github.com/umicom-foundation/Bits2Banking/actions/workflows/build-volume0.yml)
[![Lint](https://github.com/umicom-foundation/Bits2Banking/actions/workflows/lint.yml/badge.svg)](https://github.com/umicom-foundation/Bits2Banking/actions/workflows/lint.yml)
[![Docs](https://img.shields.io/badge/docs-online-blue)](https://umicom-foundation.github.io/Bits2Banking)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Learn computing from **bits → operating systems → programming → databases → networking → security → finance**, then into **Calypso/TMS** and real projects.  
We publish in small, printable **volumes** so beginners and adults can follow step by step.

---

## Our Cause

This project is part of the **Umicom Foundation**’s mission: **open education with real-world impact**.  

At the same time, we are committed to supporting **civilians in Gaza** who are suffering siege, starvation, and genocide.  
Through this project we aim to:  

- Provide **free educational resources** worldwide.  
- Channel project proceeds and donations into **relief and education** for those in crisis.  
- Stand in solidarity with Palestinians and all oppressed people by combining **knowledge sharing** with **direct humanitarian action**.  

---

## Founder

**Sammy Hegab** — software engineer, educator, and humanitarian.  

- 10+ years in the financial sector, working on Treasury Management Systems (Calypso, Summit, Murex).  
- Background in energy, fintech, and open-source advocacy (RISC-V, Linux, free software).  
- Founder of the Umicom Foundation, which promotes **education, relief, and technology** projects.  

I started Bits to Banking to make computing and finance approachable for all learners, and to channel learning into **real help for people under siege and suffering**.

---

## Support & Donations

If you’d like to support **Bits to Banking** and our humanitarian work, you can donate directly to **Umicom Foundation**.  
We publish regular transparency reports to ensure **100% of donations go to the cause**.

### GBP (UK)
```
Name: Umicom Foundation
Account number: 37131884
Sort code: 23-08-01
IBAN: GB42 TRWI 2308 0137 1318 84
SWIFT/BIC: TRWIGB2LXXX
Bank: Wise Payments Limited, 1st Floor, Worship Square, 65 Clifton Street, London, EC2A 4JE, United Kingdom
```

### USD (US)
```
Name: Umicom Foundation
Account Number: 8314463525
Account Type: Checking
Routing Number (Wire & ACH): 026073150
SWIFT/BIC: CMFGUS33
```

### EUR (SEPA/International)
```
Name: Umicom Foundation
IBAN: BE10 9670 9734 3304
SWIFT/BIC: TRWIBEB1XXX
Bank: Wise, Rue du Trône 100, 3rd floor, Brussels, 1050, Belgium
```

### AUD (Australia)
```
Name: Umicom Foundation
Account Number: 219034134
BSB Code: 774001
SWIFT/BIC: TRWIAUS1XXX
Bank: Wise Australia Pty Ltd, Suite 1, Level 11, 66 Goulburn Street, Sydney, NSW, 2000
```

### CAD (Canada)
```
Name: Umicom Foundation
Account Number: 200116215179
Institution Number: 621
Transit Number: 16001
SWIFT/BIC: TRWICAW1XXX
Bank: Wise Payments Canada Inc., 99 Bank Street, Suite 1420, Ottawa, ON, K1P 1H4, Canada
```

---

## What you’ll get (first run)

- A small **Volume 0** Word file you can open locally.  
- Two short chapters you can edit in Markdown.  
- A simple “edit → build → pull request” flow.  

---

## Quick Start (Windows)

> Requirements: **Python 3.11+** and **Git**  
> Download: <https://python.org> • <https://git-scm.com> • (Optional: [VS Code](https://code.visualstudio.com))

```powershell
# 0) Get the source
git clone https://github.com/umicom-foundation/Bits2Banking.git C:\Bits2Banking
cd C:\Bits2Banking

# 1) Set up a virtual environment and install dependencies
python -m venv .venv
.\.venv\Scriptsctivate
python -m pip install --upgrade pip
pip install -r requirements.txt   # if requirements.txt is missing, run:  pip install python-docx

# 2) Build Volume 0 locally
python scripts\make_volume0_from_md.py

# 3) Open the output
start .olumes\Volume_00_Source_Control.docx
```

---

## Repository Layout

- `chapters/v00/` — Markdown chapters for Volume 0  
- `scripts/` — Python build scripts  
- `volumes/` — generated `.docx` (git-ignored)  
- `docs/` — website pages (MkDocs)  
- `images/`, `bookcover/` — artwork and assets  

---

## Contributing (Step-by-Step)

1. **Fork** the repo and create a branch (e.g., `feat/my-chapter`).  
2. Add/edit a file in `chapters/v00/` (start with `# Title` as the first line).  
3. Build locally:  
   ```powershell
   python scripts\make_volume0_from_md.py
   ```
4. Open `volumes/Volume_00_Source_Control.docx` and check your changes.  
5. Commit, push, and open a Pull Request.  
6. ✅ **CI will attach the built `.docx`** to your PR.  

---

## Acknowledgements

**Founding contributors**
- Sammy Hegab (project lead, author, builder)  

**Supporters & community**
- Families, friends, and volunteers of Umicom Foundation  
- All who stand with civilians in Gaza and support relief & education  

(If you’d like to be acknowledged as a supporter or partner, please open a PR or contact us.)  

---

## License

MIT — see [LICENSE](LICENSE).  

---

**Project website:** <https://umicom-foundation.github.io/Bits2Banking>
