# Course logo and offline brand assets

This course release includes `content/courses/assets/branding/umicom-icon-on-dark.svg`.
Its four **visible `<path>` elements, colours and transforms** were copied
exactly from the official Umicom Framework file
`resources/brand/umicom-icon-on-dark.svg` (Git blob
`7f3b9c53c6013ea7f17fa0ccc023f11152f0b1c1`). We verified each path's
length and FNV-1a32 value before packaging. The release SVG is a compact
rendering derivative: it omits the original *invisible* `fill="none"` paths,
so it is NOT byte-identical to the source master. No brand geometry was
redesigned and no original repository asset was overwritten.

All HTML headers and favicons use a path relative to the HTML file leading
into the bundled course asset directory. This deliberately fixes the earlier
release that referred to `content/assets/branding` without including those
assets in the standalone ZIP. Open with `file:///` offline and the icon loads.

The authoritative complete master remains the Umicom Framework resource.
When a release process can copy this master automatically, replace this
compact derivative with a byte-identical copy and verify its Git blob SHA.
Do not independently edit either asset as a branding redesign.

## Inline header resilience

All rendered HTML pages additionally **inline the same four approved visible
SVG path elements** in their headers. The mark therefore does not depend on a
network request or a file:// SVG image load. Favicon and design assets use the
local bundled SVG, and Framework remains the master source. The inline paths
are generated release material; do not edit them manually across pages.
