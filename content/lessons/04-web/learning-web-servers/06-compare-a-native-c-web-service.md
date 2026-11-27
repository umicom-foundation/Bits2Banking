<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/06-compare-a-native-c-web-service.md

PURPOSE:
Trace an HTTP request into the existing native Umicom Framework C23 service.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Follow a request into native C23

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }

The Java servlet and a native C handler both answer an HTTP request. Tomcat supplies the listener, reads the request and calls the servlet. In Umicom Framework a C23 program composes the listener, route table and handler directly.

## Read the route

1. Open [Follow a browser request into C](../../05-engineering/building-a-web-server-in-c/01-follow-a-request.md) and find the source link.
2. Locate `/api/health` in the registered routes. Trace it to the C `Health` handler.
3. Find the body and content type chosen by the handler. Then find the route declaration, where the method and path are registered separately from the response code.

Write down the two paths from the course in your own words.

```text
Tomcat:  GET /btb-statement/summary -> servlet mapping -> doGet -> text
Umicom:  GET /api/health            -> Framework route -> Health -> JSON
```

## Check the native result

If you have the Framework build tools ready, follow the configure and build steps in [Run and explain a Framework service](../../05-engineering/building-a-web-server-in-c/07-run-and-explain-a-framework-service.md). Use your local checkout and stop on build errors. Start the resulting example with `--port 8280` so it can be distinguished from the earlier servers.

In another PowerShell window, run this read-only request.

```powershell
curl.exe -i http://127.0.0.1:8280/api/health
```

Look for `200`, a JSON content type and the values `umicom-local-example` and `ready`. After recording the result, press **Ctrl+C** in the Framework terminal to stop your practice listener.

## Compare the evidence

| Observation | What it establishes |
| --- | --- |
| A C compiler built the target | The example code compiled and linked in that build environment |
| The local GET returned expected JSON | Your client reached the selected route and received the response |
| The Java servlet returned the expected text | The WAR deployed and answered that route on the chosen server |

When you read source without running it, label the result **expected**. One local response checks one request path. Further checks cover lifecycle, repeated requests and the intended deployment environment.

[Previous, deploy on WildFly](05-deploy-the-same-war-on-wildfly.md) · [Course](index.md) · [Next, map the jobs in a deployed website](07-map-the-jobs-in-a-deployed-website.md) · [Umicom native web workflow](../../05-engineering/building-a-web-server-in-c/24-qualify-a-local-c-web-workflow.md)
