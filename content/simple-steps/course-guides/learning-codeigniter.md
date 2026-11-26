<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-codeigniter.md

PURPOSE:
Provide practical first steps and a result to check for Learning CodeIgniter.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning CodeIgniter

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. With PHP and Composer set up as the lesson describes, type `composer create-project codeigniter4/appstarter learning-portal` in a practice folder. [An explicit route](../../lessons/04-web/learning-codeigniter/01-an-explicit-route.md)
2. Open `learning-portal`, add the lesson’s `Learning` controller and `learning` route, then run `php spark serve --host 127.0.0.1 --port 8080`. [An explicit route](../../lessons/04-web/learning-codeigniter/01-an-explicit-route.md)
3. Open `http://127.0.0.1:8080/learning`. Add the second lesson’s `learning/course` route and view, then open that new path. [A controller and an escaped view](../../lessons/04-web/learning-codeigniter/02-a-controller-and-an-escaped-view.md)

**Check your result.** The first page shows `Choose a learning course`. The second shows a heading that reads `Learning HTML & CSS`.

[Continue in the full course](../../courses/learning-codeigniter/index.html) · [All course guides](index.md)
