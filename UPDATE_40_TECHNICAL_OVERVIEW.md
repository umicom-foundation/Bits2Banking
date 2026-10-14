# Major Update 40 — Technical Overview

**Title:** System Administration: Practical Infrastructure and Native C23 Service Readiness  
**Author/project lead:** Sammy Hegab · Umicom Foundation  
**Date:** 14 October 2026  
**Scope:** `Umicom-Bits2Banking` only  
**Language policy:** ISO C23 native laboratory, Markdown teaching materials, CMake declarative build, SVG illustrations and a self-contained HTML reader. No new Python, PowerShell or JavaScript implementation files.

## Pedagogical progression

The System Administration: From Zero course comprises **48 sequential chapters** after this update. The original 1–24 introduction and the 25–36 intermediate chapters remain unchanged. The 12 new chapters (37–48) develop investigation skills, including a safe practice laboratory, system baselines, scheduled work, disks and mount points, verified practice backups, ACL reading, network layers, firewall observation, process-vs-readiness distinction, update change-control, incident timelines and a reviewed capstone.

The new lessons contain command rationale and expected results for Windows PowerShell 7 and Linux terminals; sensitive operations are excluded. The offline HTML edition retains the 36 previously rendered chapters and adds Stage 3 in one file, with all new SVG diagrams embedded. It is a reading artefact, not a web-server executable or a claim of site publication.

The engineering track advances Chapters **292–295** and the video-script series advances Episodes **106–110**.

## C23 component boundaries

```
Earlier Update 39 lab: BtbAdminReview, BtbAdminReviewEvaluate
                        │ (reuse existing C23 implementation)
                        ▼
New Update 40 lab: BtbServiceGraph, BtbServiceGraphEvaluate
                        │
                        ▼
                 BtbServiceSummary
             READY / REVIEW / BLOCKED
```

`BtbServiceGraph` contains up to **eight** copied service specifications (identifiers 1–32), their copied observations and a logical capture identifier. A bitmask declares prerequisites and mandatory check IDs. A bounded depth-first traversal rejects cycles and unknown dependencies. Individual service observation checks are delegated to the previous `BtbAdminReviewEvaluate` implementation. A blocked prerequisite propagates a blocked result; an optional warning propagates review if nothing required is blocked.

**Trust boundary:** Every result is about fictional supplied values, not observed host state. No service manager, Windows registry, firewall, Git repository, database, network socket or production Umicom service is accessed. This laboratory must not be promoted to a reusable production service without first reviewing existing Framework service supervision, observability, VCS, build/test and security contracts.

## Input/output contract

- Graph and summary objects are **caller-owned** and stack-allocatable.
- Register/Attach copy their input values; no pointers are retained.
- An invalid Register/Attach preserves graph contents.
- Evaluate builds a private candidate; unknown dependencies, cycles and malformed state preserve `outSummary` on rejection.
- Capture IDs represent logical classroom sessions only. A previous observation must not count as a passing *current* required check.
- CTest names identify individual scenarios so failures are reproducible without timing-dependent OS events.

## Acceptance boundaries

Focused validation on the available Linux host: GCC 14.2.0 C23 and Clang 17 C23 + ASan/UBSan each passed 32/32 CTest cases, including Update 39's unchanged regression suite. No claim is made about Windows UCRT64, the complete MkDocs website, live GitHub Pages or a real Umicom Framework/OS integration. The package includes explicit commands for those checks.

## Preservation and future design

No existing files are replaced or deleted in this partial merge package. The original *Creating a New Umicom Application* beginner guide from Update 38, the historical books, the original early chapters and all earlier C23 labs remain the owner's authoritative materials; this batch links to them rather than copying or silently rewriting them.

**Next:** Stage 4 could cover user-account lifecycle and policy, local server configuration, task identity and isolation, incident response exercises, backup rotation, configuration baselines, service packaging and monitoring concepts. Shared working implementations remain Framework-owned and native C23/Assembly-first.
