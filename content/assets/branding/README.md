# Umicom website branding

The website keeps approved Umicom artwork alongside its content. The original logo, symbol and Windows favicon variants are also maintained in [Umicom Framework](https://github.com/umicom-foundation/umicom-framework/tree/main/resources/brand). The home page uses the supplied vector wordmark with a scalable viewBox; its path geometry is unchanged. Keep the retained variants when updating approved artwork.

- `umicom-icon-on-dark.svg` is used in the website header.
- `umicom.ico` is the browser favicon.
- `umicom-wordmark.svg` is the approved home page artwork. Its viewBox preserves the original proportions when the image is resized.
- `umicom-logo.png` remains available as the earlier raster artwork.
- The remaining source SVG and PNG variants support light and dark displays.

The website uses the operating system's text fonts; no font redistribution is required.

The home page applies the `umicom-wordmark` class to the image. This limits its width while allowing it to shrink on narrow screens. A light backing keeps the supplied dark lettering and white details visible in both colour themes. Lesson diagrams do not inherit this branding rule.
