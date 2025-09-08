---
title: "YAML in 10 Minutes (for this project)"
author: "Umicom Foundation"
date: "06 September 2025"
description: "A fast, practical introduction to YAML with examples tailored to our GitHub Actions and config files."
version: "1.0"
---

# YAML in 10 Minutes (for this project)

YAML is a human‑readable format used for configuration—**indentation matters** and uses **spaces only**.

## 1) The absolute basics

### Mappings (key → value)

```yaml
name: Content sanity check
enabled: true
retries: 3
```

### Lists

```yaml
books:
  - Effective Communication
  - Contributor Basics
  - Leadership & Teamwork
```

### Nesting (indent with 2 spaces)

```yaml
book:
  title: Effective Communication
  author: Tamkin Riaz
  modules:
    - Understanding the Communication Process
    - Active Listening
```

> **Important:** Do **not** use tabs. YAML requires spaces. Mixed tabs/spaces cause hard‑to‑read errors.

## 2) Strings and quoting

Unquoted is fine if there are no special characters. Quote when in doubt.

```yaml
title: Effective Communication
safe: "Yes — includes punctuation, : and # are safe here"
path: "content/effective-communication-course/index.md"
```

Multi‑line strings:

```yaml
description: |
  This course includes:
  - Verbal and non‑verbal communication
  - Listening skills
  - Written communication
```

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
```

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
```

**Fix:** Align the dashes under the same indent level:

```yaml
steps:
  - name: One
    run: echo one
  - name: Two
    run: echo two
```

### C) Unintended colon in unquoted strings

```yaml
title: Effective Communication: A Practical Guide   # may parse oddly
```

**Fix:** Quote it:

```yaml
title: "Effective Communication: A Practical Guide"
```

### D) Trailing spaces after keys

```yaml
name : Value   # ← space before colon not recommended
```

**Fix:**

```yaml
name: Value
```

## 5) Advanced (rarely needed, but good to know)

### Anchors & aliases

```yaml
defaults: &defaults
  retries: 2
  timeout: 30

job:
  <<: *defaults
  retries: 3  # override
```

### Environment variables in Actions

```yaml
env:
  PYTHONWARNINGS: "ignore"
  APP_ENV: "prod"
```

## 6) Quick checklist before committing

- Spaces only, consistent indent (2 spaces works well).
- Quote strings with `:` or `#` or special characters.
- Lists aligned at the same column.
- Run your workflow locally if possible or rely on CI feedback.

That’s it—you’re good to read and adjust YAML in this project.
