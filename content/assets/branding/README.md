# Umicom website branding

The website keeps approved Umicom artwork alongside its content. The original logo, symbol and Windows favicon variants are also maintained in [Umicom Framework](https://github.com/umicom-foundation/umicom-framework/tree/main/resources/brand). The home page uses the supplied vector wordmark with a scalable viewBox; its path geometry is unchanged, and its letter counter is a transparent cutout. Keep the retained variants when updating approved artwork.

- `umicom-icon-on-dark.svg` is used in the website header.
- `umicom.ico` is the browser favicon.
- `umicom-wordmark.svg` is the approved home page artwork. Its viewBox preserves the original proportions when the image is resized.
- `umicom-wordmark-on-dark.svg` supplies the same geometry with a pale wordmark for the dark theme.
- `umicom-logo.png` remains available as the earlier raster artwork.
- The remaining source SVG and PNG variants support light and dark displays.

The website uses the operating system's text fonts; no font redistribution is required.

The home page applies the `umicom-wordmark` class to the image. This limits its width while allowing it to shrink on narrow screens. The background and letter counter are transparent. The site selects a light or dark vector variant with its theme; no white backing is added. Lesson diagrams do not inherit this branding rule.

## Publish existing and new lessons with the same identity

The MkDocs configuration loads `hooks/umicom_branding.py` after the course source-link adapter. It works on the generated site, so the same policy reaches older standalone lessons and future pages without copying a logo into every manuscript. Native application artwork still comes from Framework.

1. Keep the approved wordmarks, icon variants, `umicom.ico` and `umicom-brand.css` in this directory. Change an asset only when an approved replacement is available. The publisher requires generated assets to match these source bytes.
2. In a standalone HTML page, keep the existing page header or main element. The adapter uses that region; it does not create a different document layout. Existing Umicom SVG references are repaired relative to the generated page. A page without one receives the approved wordmark.
3. Keep example markup escaped inside code samples. Comments and scripts are not treated as displayed logos. Do not place a fake logo in a comment to satisfy an audit.
4. Use the dark wordmark on a permanently dark header. The existing `site` header class identifies that design. Pages using `prefers-color-scheme` can select the matching light or dark artwork. Review contrast in the actual browser, including a narrow window and print preview.
5. Keep source content and generated site output in separate directories. A publication failure for missing, changed or linked assets needs investigation before deployment; do not bypass the check by removing the asset from the required set.

`umicom-brand.css` defines body, heading and code font roles using installed fonts. The MkDocs theme has automatic hosted font loading disabled. The first available font in each role is used; appearance therefore depends on the fonts installed on the reader’s computer. The stylesheet does not embed, download or redistribute font files. Preserve the artwork proportions and transparent background.

### Native learning packs

A native learning manifest binds each payload file to a checksum. Both the source-link and branding adapters share `hooks/publication_artifacts.py` and leave pages declared by an `umicom.learning.pack` manifest unchanged, because changing their bytes would invalidate the pack. The native reader supplies its own Framework branding. To change a native pack page, edit its source, review the native pack preparation workflow, regenerate its identities explicitly, and qualify the result in the reader. A browser publication is not a native pack release.

### Verify a publication

From the repository root, the focused adapter checks can be run with `python -m unittest discover -s tests -p test_umicom_branding.py`. Then build the site using the repository’s documented MkDocs environment and inspect the generated pages. A successful source check does not establish that a browser rendered the correct logo or font.

Inspect at least a deeply nested lesson, an older standalone course, an adaptive page and a native pack page. The generated lesson should load its local SVG, ICO and stylesheet without failed requests; its headings, lesson text and navigation should remain available. Repeat publication to confirm that extra logo or favicon elements do not accumulate. Raw source pages opened directly do not pass through the publication adapter.

The introductory Framework and finance pages now carry the approved SVG wordmarks, SVG icon, ICO favicon and installed-font stylesheet in their source HTML. Their manifests are updated deliberately with the reviewed source bytes. The pipeline regression in `test_umicom_branding.py` exercises both adapters in their configured order; run the source-link suite too when qualifying a publication.

### Responsive artwork

A browser can choose a picture source or an image srcset instead of its fallback src. Publication repairs these candidate lists when every candidate is a known local Umicom logo or icon. It maps the retained logo/icon PNG names to their approved SVG equivalents and preserves density or width descriptors, sizes, alternative text and the selected light/dark variant. A picture source converted to vector artwork receives the SVG media type. Source elements outside a picture are left alone.

Mixed illustration/brand lists, external URLs, data URLs and unsupported or contradictory descriptors are preserved for manual review. They must not be treated as verified Umicom artwork. Keep canonical logo candidates together, use either distinct positive density values or distinct positive widths, and review the generated page at more than one window size. Native payload ownership still takes precedence: change those files through their source and manifest workflow.

### Retained templates and embedded markup

The publication adapter observes active document markup before deciding that a page already has its Umicom identity. A logo, favicon or stylesheet inside a retained HTML template cannot satisfy the active page. Nested templates, title and textarea text, raw-text examples and conditional noscript content remain unchanged. The adapter shares this context policy with its stylesheet observer, so a lesson that merely mentions an adaptive CSS feature does not select dark artwork on that basis.

Keep the original template or example bytes when preserving design history. Place the actual logo and local font stylesheet in the active header/head as described above. The publisher may supply missing branding outside the retained content. It does not evaluate arbitrary CSS visibility, script-created content or browser layout; those still need browser review. Active inline CSS and local published stylesheets supply the adaptive-theme hint.

Qualification should include an older page with retained template artwork, a nested template, an editable markup example in a textarea, and a live logo following those examples. Run the branding suite, then publish twice and inspect the active SVG, ICO and fonts in the browser. Native pack payloads continue to be excluded from rewriting because their manifests bind exact bytes.

## Offline logo aliases

The older umicom-logo.svg and umicom-logo-on-dark.svg paths now contain the same approved path geometry as the wordmark variants. They no longer redraw the name through an installed font. Their previous SVG implementations remain inside non-rendering definitions in the canonical masters for review. Keep these aliases usable because standalone lessons and offline readers can open source HTML without the website publication hook.

The source-asset cases in tests/test_umicom_branding.py inspect active paint primitives, aspect ratio and external dependencies independently of generated-page rewriting. Run them during qualification; authored cases alone do not establish rendered appearance.
