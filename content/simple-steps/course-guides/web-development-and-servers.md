<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/web-development-and-servers.md

PURPOSE:
Guide readers from a first webpage to local server and Framework exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Web development and web servers

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }

1. **Make a page.** Create a practice folder and save `index.html`, `site.css` and the two approved Umicom graphics. Open the HTML file in your browser. [Copy the starter page and stylesheet](../../lessons/04-web/learning-web-servers/01-make-a-page-and-stylesheet.md)
2. **Serve it from your computer.** Start your practice Apache HTTP Server with its listener at `127.0.0.1:8180`. Open `http://127.0.0.1:8180/index.html`. Expect the same heading and an HTTP `200` response. [Set up the local server](../../lessons/04-web/learning-web-servers/03-serve-files-with-apache-http-server.md)
3. **Read a response.** In another PowerShell window, type `curl.exe -I http://127.0.0.1:8180/site.css`. Expect `200` and `text/css`. [Read the request and response](../../lessons/04-web/learning-web-servers/02-read-an-http-exchange.md)
4. **Run the Java example.** Package the page and servlet as `btb-statement.war`. Copy it into your practice Tomcat's `webapps` folder, start Tomcat and request `/btb-statement/summary`. Expect `2 entries reviewed.` [Build the WAR and run Tomcat](../../lessons/04-web/learning-web-servers/04-deploy-a-war-on-tomcat.md)
5. **Run the same archive on WildFly.** Compare its hash with the first archive and repeat the request. Use the WildFly management CLI to remove the archive and stop the server when you finish. [Deploy the same WAR on WildFly](../../lessons/04-web/learning-web-servers/05-deploy-the-same-war-on-wildfly.md)
6. **Find a native route.** Open the Framework example, find the `/api/health` route and trace it to the C function that returns JSON. [Follow the Umicom C23 service](../../lessons/04-web/learning-web-servers/06-compare-a-native-c-web-service.md)

**Check your result.** You can name which component answered each request and show the evidence from that response.

[Continue in the full course](../../lessons/04-web/learning-web-servers/index.md) · [All course guides](index.md)
