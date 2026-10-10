# Integrating the Umicom educational website

Merge this `Umicom-Bits2Banking` folder over the local repository folder of the same name, reviewing full-file replacements in Beyond Compare. No file is deleted and no existing manuscript, BookForge programme or Git history is changed.

1. Review `mkdocs.yml`: the 34 technical lessons are retained and the complete original **Islam: Blueprint for Life** navigation is restored.
2. Run `python tools/prepare_learning_site.py` from `C:\umicom\Umicom-Bits2Banking`. This takes the original ten manuscript chapters from `dropzone/documents/islam_blueprint_for_life/`, the original book images from `dropzone/images/` and the canonical logo, icon and favicon from your Framework checkout.
3. Run `python tools/validate_learning.py` and both test files; then `python -m mkdocs build --strict`.
4. Open the site locally with `python -m mkdocs serve`, checking Volume 1 and the new branded header.
5. Review `git status`, `git diff --check`, and the complete staged diff. No existing source or book content should appear as deleted. Commit and push only after verification.

The brand-sync helper copies source artwork without altering it. The included updated CI workflow continues to **validate only**; GitHub Pages deployment is unchanged, pending a separate consolidation of the existing BookForge website publisher.
