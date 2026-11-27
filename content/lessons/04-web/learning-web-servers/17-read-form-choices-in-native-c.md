<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/17-read-form-choices-in-native-c.md

PURPOSE:
Trace a browser form query through the existing Framework request and response owners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Read form choices in native C

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Send the same two choices from the form exercise to a C route. This time the response names the site and period you chose.

Start with [Send a read-only choice with a form](16-send-a-read-only-choice-with-a-form.md). Build the local C example as shown in [Follow a request into native C23](06-compare-a-native-c-web-service.md).

## 1. Check the example in memory

In PowerShell, set the path to your built Framework example. Replace the sample path with yours.

```powershell
$webExample = 'C:/tools/umicom-web-local-service-example.exe'
& $webExample --port 8093 --check-routes
```

The expected message is `Local route and browser admission checks passed in memory.` These checks call the request and response code directly. Open the actual local service for the next step.

## 2. Start the demo and read the first response

```powershell
& $webExample --port 8093
```

Keep this window running. In a second PowerShell window, make the following request.

```powershell
curl.exe --fail --silent --show-error 'http://127.0.0.1:8093/api/review?site=North+Office&period=week'
```

The output is `North Office, week report`.

## 3. Check a literal plus and a missing choice

```powershell
curl.exe --fail --silent --show-error 'http://127.0.0.1:8093/api/review?site=North+%2B+Annex&period=month'
curl.exe -i 'http://127.0.0.1:8093/api/review?site=North+Office'
```

The first line returns `North + Annex, month report`. The second request leaves out the period. Its HTTP status is 400 and its message asks you to choose both values.

## 4. Follow the values into C

Open `framework/examples/web/local_service.c` in your checkout and find `ReviewSelection`.

1. The Framework parser supplies `request->path` and `request->query` separately. The path selects the callback.
2. `umi_web_query_parse` reads the name and value pairs. A plain plus is decoded to a space, and `%2B` becomes the literal plus.
3. `umi_web_query_get` looks up `site` and `period`. The callback compares both with the choices shown in the exercise.
4. `umi_web_response_set_text` carries the chosen label or the message asking for both values.

The route uses two fixed practice sites. Try changing just `week` to `month` in the first command. Predict the response before sending it.

If the in-memory check still passes but the request returns 404, see which command started the listening process. The default demo serves this route. The `--root` option selects a separate static export. If you already have a practice server on port 8093, stop it before starting the demo, or choose another unused port and update the URLs.

Press Ctrl+C in the server window when you are finished. [Previous lesson](16-send-a-read-only-choice-with-a-form.md) · [Next lesson](18-serve-two-apache-sites-on-one-port.md) · [Web server course](index.md)
