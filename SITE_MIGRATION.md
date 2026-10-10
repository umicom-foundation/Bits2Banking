# Learning website integration

The new website reads `content/` through `mkdocs.yml` and can be built using `python -m mkdocs build --strict` after installing `requirements-docs.txt`. It contains the initial 34 lessons, 17 diagrams, practical source examples, community pages and three complete video scripts.

## Original content

All existing repository files and Git history remain in place. The only path in this bundle that already existed in the observed repository is `mkdocs.yml`. Its original content is retained in `archive/site-config/mkdocs-original.yml`; no prior manuscript files or build scripts are removed or replaced.

The original navigation referenced absent files such as `content/VOLUMES.md` and a historical `content/v001_islam_blueprint_for_life/` tree. Those navigation entries are archived until their underlying source material is located. They must not be replaced with invented or empty lessons.

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
