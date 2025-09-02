# Makefile — Bits2Banking
# Lightweight helpers for common tasks.
# Usage examples:
#   make install
#   make build
#   make docs
#   make lint
#   make clean

PY ?= python

.PHONY: help install build docs lint lint-md lint-typos clean

help:
	@echo "Targets:"
	@echo "  install   - Upgrade pip and install dependencies"
	@echo "  build     - Build Volume 0 DOCX"
	@echo "  docs      - Build MkDocs site to ./site"
	@echo "  lint      - Run markdown and typos linters (if installed)"
	@echo "  clean     - Remove generated artifacts (volumes/*.docx, site/)"
	@echo ""
	@echo "Tip: On Windows, run from Git Bash or PowerShell with 'make' available."

install:
	$(PY) -m pip install --upgrade pip
	@if [ -f requirements.txt ]; then \
		$(PY) -m pip install -r requirements.txt; \
	else \
		$(PY) -m pip install python-docx; \
	fi
	@echo "Install done."

build:
	$(PY) scripts/make_volume0_from_md.py

docs:
	$(PY) -m pip install mkdocs mkdocs-material >/dev/null 2>&1 || true
	mkdocs build --strict

lint: lint-md lint-typos

lint-md:
	@command -v markdownlint-cli2 >/dev/null 2>&1 && markdownlint-cli2 || echo "markdownlint-cli2 not installed (skipping)."

lint-typos:
	@command -v typos >/dev/null 2>&1 && typos . || echo "typos not installed (skipping)."

clean:
	@rm -rf site
	@rm -f volumes/*.docx
	@echo "Cleaned generated artifacts."
