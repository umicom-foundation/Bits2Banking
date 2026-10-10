# Learning website integration

The new website reads `content/` through `mkdocs.yml` and can be built using `python -m mkdocs build --strict` after installing `requirements-docs.txt`. It contains the initial 34 lessons, 17 diagrams, practical source examples, community pages and three complete video scripts.

## Original content

All existing repository files and Git history remain in place. The only path in this bundle that already existed in the observed repository is `mkdocs.yml`. Its original content is retained in `archive/site-config/mkdocs-original.yml`; no prior manuscript files or build scripts are removed or replaced.

The original navigation referenced an absent `content/VOLUMES.md` and historical `content/v001_islam_blueprint_for_life/` tree. The complete historical Islam volume was subsequently located in `dropzone/documents/islam_blueprint_for_life/`; the next section explains how it is restored to website navigation without inventing replacement lessons. The existing BookForge catalogue remains separate pending publishing consolidation.

## Current GitHub Pages workflows

Two existing workflows, `books-build.yml` and `dropzone-build.yml`, publish `output/site` when triggered by changes to books, scripts or dropzone content. The new `learning-site-check.yml` deliberately builds and validates the learning website but **does not deploy to Pages**. Deploying it immediately could overwrite an existing BookForge site. Unify both sources into a single release pipeline, then enable Pages publishing once the existing book catalogue has been verified.

## Validation

Run these from the repository root:

```powershell
python -m pip install -r ".\requirements-docs.txt"
python ".\tools\validate_learning.py"
python -m mkdocs build --strict
python -m pytest -q -p no:cacheprovider ".\tests\test_learning_site.py"
python -m mkdocs serve
```

## Source ownership

Edit the Markdown lessons in `content/lessons/`, original examples in `content/labs/` and video scripts in `content/videos/scripts/`. MkDocs produces `site/`; do not commit generated site files. Canonical API and build documents remain with their respective Umicom source repositories.

## Volume 1 restored to website navigation

The original Islam: Blueprint for Life manuscript has been found under `dropzone/documents/islam_blueprint_for_life/`. It includes all ten chapters that the historic MkDocs navigation listed. The artwork is in `dropzone/images/`, and the original `volume.yml` remains with the manuscript. The preparation command publishes byte-preserving copies of the authored chapters (removing only a UTF-8 BOM where present), plus artwork, into the MkDocs `content/` directory. Neither the original text nor book publication inputs are altered.

The Islam volume is published alongside the computing courses, with new introductory and cross-subject links. It is not replaced or renamed as a computing course.

## Official Umicom identity

The website now uses the official Umicom branding from `Umicom-Applications/framework/resources/brand`: light/dark SVGs, logo PNG and the original `umicom.ico`. The CSS uses the colours and system-font stack from the shared branding. No fonts or substitute icon artwork are redistributed. Run `scripts/Prepare-UmicomLearningSite.ps1` or `tools/prepare_learning_site.py` after merging. The command is non-destructive: it does not overwrite differing existing published files without an explicit `--refresh`.

## Review and build (Windows PowerShell)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
python ".\tools\prepare_learning_site.py"
python ".\tools\validate_learning.py"
python -m pytest -q -p no:cacheprovider ".\tests\test_learning_site.py" ".\tests\test_islam_volume_and_brand.py"
python -m mkdocs build --strict
python -m mkdocs serve
```

The validation workflow also checks out just the official Framework brand directory during GitHub Actions and prepares the original book pages before testing and building. It continues to generate a website preview without publishing to Pages. Keep the existing BookForge Pages workflow intact until the two publishing paths have been reconciled and the existing books are demonstrably preserved.
