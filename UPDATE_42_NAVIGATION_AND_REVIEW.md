# Update 42 — navigation and manual merge review

**Do not overwrite your existing `mkdocs.yml`**. It may contain later additions, course lists, original manuscripts and *Islam: Blueprint for Life* entries that are absent from earlier review copies. This ZIP contains **only a navigation snippet**, not a replacement configuration.

1. Open your checked-out `mkdocs.yml` and `UPDATE_42_MKDOCS_NAV_SNIPPET.yml` in Beyond Compare or an editor.
2. Under the existing *System Administration* course group, add Stage 5 Chapters **61–72** and the five Stage 5 references. If the course group does not exist, create one under the existing `nav:` key, without creating a second `nav:` key.
3. Add engineering Chapters **300–303** under the established software engineering section, or its appropriate extended subgroup.
4. Add Episodes **116–120** under the Videos group. Preserve all previous video and original book references.
5. Check that each referenced `.md` path exists under the existing `content/` documentation root. Do not point MkDocs navigation at the root offline HTML file unless deliberately copied into the configured docs directory and reviewed.
6. Run the existing MkDocs strict build when its environment is available. Resolve warnings without deleting original navigation entries.

The batch also provides `UPDATE_42_SYSTEM_ADMINISTRATION_COMPLETE_COURSE.html` as a **self-contained offline course**. It includes the previous 60 chapter article bodies unchanged and embeds the seven new SVG diagrams (among earlier embedded illustrations). It is not a new website generator and contains no new scripting-language application implementation.

### Engineering note

Source preservation is mandatory. None of this package's code files replaces an existing file. Use only an additive Beyond Compare merge and review `git diff --cached` after `git add -A`. The native C23 laboratory requires existing Updates 39–41 and must not be moved into Framework without the agreed integration review.
