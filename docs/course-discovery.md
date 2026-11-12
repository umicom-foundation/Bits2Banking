<!--
Umicom Bits2Banking
File: docs/course-discovery.md

PURPOSE:
Explain complete lesson discovery, edition preservation and owner-run content qualification.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../content/assets/branding/umicom-logo.svg)

# Keep a course lesson discoverable

A lesson can exist on disk and still be missing from a reader's course list or website navigation. Adding a chapter involves both its teaching content and the records connecting its editions.

## 1. Preserve the teaching sources

Keep the complete HTML lesson and Markdown manuscript. They are editable sources, not disposable conversions. When their wording differs, review both before publishing a common edition.

Use canonical Umicom SVG artwork and ICO assets. Course HTML uses the shared learning stylesheet for Segoe UI and Cascadia Code/Consolas with local fallbacks. The website theme disables remote font loading. Native applications use Framework's application branding helper.

## 2. Declare the ordered lesson pair

A course.json lesson has a path, title and manuscript. Both paths resolve from that course.json directory.

For content/courses/building-a-text-editor, ../../lessons reaches content/lessons. The nested content/courses/framework-and-finance/banking-and-payments course needs ../../../lessons instead. Resolve the complete path before copying a reference from another course.

Only manuscript identifies the active edition. Corrected metadata may retain supersededManuscriptPath for engineering review; that field is not a navigation destination. Keep titles, source-reading requirements, modules and completion claims consistent with the actual material.

## 3. Register editions without ambiguity

Add the repository-relative HTML and Markdown paths to knowledge/registries/lesson-media.json. One HTML identity must have one mapping. Different historical HTML addresses may legitimately share a manuscript; preserve that relationship instead of counting another written chapter.

Check for an existing identity before appending. A disagreement needs editorial review. Do not overwrite a mapping automatically to make a checker accept it.

## 4. Connect the reading routes

Add the chapter to browser and manuscript contents. Connect previous and next chapters in each edition. Add the manuscript to nav in mkdocs.yml, relative to content:

~~~yaml
nav:
  - "Example course":
      - "A complete chapter": lessons/example/a-complete-chapter.md
~~~

A path in a comment, title or another configuration section is not an active navigation entry. The checker observes the repository's block-style destination scalars. It does not render YAML or replace MkDocs validation. Change its fixtures if the navigation format changes.

Standalone course HTML keeps local source links for offline use. The configured course_source_links hook maps admitted labs and learning-packs links to the configured public repository during publication. Markdown manuscripts use explicit repository URLs for source files outside content. Local file existence alone does not prove a generated website destination exists.

## 5. Refresh the offline pack

Add new lessons and manuscripts to the learning-packs manifest, retaining existing resource IDs. Include useful complete lab files and guides. Hash final bytes after editing links and navigation.

Keep each native pack within its documented resource capacity. Use an explicit companion pack when needed; do not silently drop resources. Increment a changed pack's revision and check source paths, hashes, resource IDs and catalogue counts together. A valid manifest is not an executed Studio import.

## 6. Qualify the source relationships

The general gate examines every course.json under content/courses. It checks in-tree HTML/manuscript files, unique lesson routes, edition mapping and active manuscript navigation. Existing subject-specific course checks remain in place.

Run one command at a time and stop on an unexpected error:

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\tests\content_integrity -B .\build\content-integrity -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build .\build\content-integrity --parallel 2
ctest --test-dir .\build\content-integrity -R '^btb\.education\.course_discovery(\.|$)' --output-on-failure --no-tests=error
~~~

Expect one catalogue check and twenty-two contract fixtures from this source. Fixtures retain generated directories under the build-owned fixture root for diagnosis. They do not remove an existing tree or write course source.

Cases cover valid nested paths, sibling-course references and quoted labels, shared-manuscript aliases, missing/duplicate/wrong mappings, missing files, incorrect nesting depth, paths outside content, duplicate resolved lessons, malformed metadata, wrong JSON list types and inactive navigation text.

## 7. Interpret the result

Discovery checks establish source relationships. They do not establish a website build, offline import, compiled example, browser font rendering or native icon result. Qualify those workflows separately.

Preserve the first diagnostic and exact revision. source_missing often indicates a misspelled path or wrong nesting depth. edition_missing indicates disagreement with the registry. navigation_missing means no admitted nav destination names the manuscript. Fix the relevant record, refresh affected pack hashes and rerun the matching qualification.

Read [the checker](../tests/content_integrity/course_discovery.cmake), [the fixtures](../tests/content_integrity/test_course_discovery.cmake) and [the shared editor lab](../labs/native/shared-editor/README.md).
