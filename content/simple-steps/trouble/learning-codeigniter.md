<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-codeigniter.md

PURPOSE:
Give learners an additional practical case for Learning CodeIgniter.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace a page missing from the local route table

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice controller has a show method for a page called brews, yet a GET request to /brews returns 404.

1. Check the local route table for a GET /brews entry before editing the controller.
2. Add the explicit route to the course controller's show method and reload the local page.

**Check your result.** GET /brews returns the practice page with its Brewing notes heading.

[Step-by-step course guide](../course-guides/learning-codeigniter.md) · [Full course](../../courses/learning-codeigniter/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-codeigniter.md)
