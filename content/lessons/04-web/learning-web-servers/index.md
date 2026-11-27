<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/index.md

PURPOSE:
Introduce the beginner course on building and serving web applications.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Web development and web servers

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }

Create a small website about a fictional statement. Read what the browser asks for, serve the page with Apache HTTP Server, then run one Java application on Tomcat and WildFly. Lesson 6 follows the same HTTP idea into a native C23 service.

You can read and trace every example before installing anything. For the local exercises, use PowerShell, a text editor and a browser. The Apache and Java exercises list their own tools. Use one practice folder and keep the servers on the same computer as the browser.

## Lessons

1. [Make a web page and its stylesheet](01-make-a-page-and-stylesheet.md). Open a saved page and see which file controls its appearance.
2. [Read an HTTP request and response](02-read-an-http-exchange.md). Find the method, path, status, content type and body.
3. [Serve your page with Apache HTTP Server](03-serve-files-with-apache-http-server.md). Set a document root, test the configuration and request two files.
4. [Deploy a web archive on Apache Tomcat](04-deploy-a-war-on-tomcat.md). Compile a small Java request handler and package it with the page.
5. [Deploy the same web archive on WildFly](05-deploy-the-same-war-on-wildfly.md). Compare the result with Tomcat and learn where Red Hat JBoss EAP fits.
6. [Follow a request into native C23](06-compare-a-native-c-web-service.md). Locate a route in Umicom Framework and compare the evidence from both implementations.
7. [Map the jobs in a deployed website](07-map-the-jobs-in-a-deployed-website.md). Decide where a static file, a Java application, a native worker and the browser belong.
8. [Inspect a Red Hat JBoss EAP deployment](08-inspect-a-jboss-eap-deployment.md). Compare a management record with an application response.
9. [Check an Apache configuration copy](09-check-an-apache-configuration-copy.md). Compare the checker’s results for working, incomplete and repaired settings.
10. [Choose the Servlet API for your server](10-choose-the-servlet-api-for-your-server.md). Compile the same servlet for two target API versions and inspect the class.
11. [Follow a request in an access log](11-follow-a-request-in-an-access-log.md). Find the requested path and returned status in a short practice log.
12. [Reuse a response with an ETag](12-reuse-a-response-with-an-etag.md). Use a saved ETag to decide whether the client needs a new response body.
13. [Set a message for a missing page](13-set-a-message-for-a-missing-page.md). Explain a missing page and keep HTTP 404 through the local C host or Apache.
14. [Run a separate local Tomcat instance](14-run-a-separate-local-tomcat-instance.md). Keep a local practice instance’s applications, configuration and logs separate from the server programs.
15. [Serve an XHTML document](15-serve-an-xhtml-document.md). Check the document media type and the difference between GET and HEAD.
16. [Send a read-only choice with a form](16-send-a-read-only-choice-with-a-form.md). Read named browser form values in a GET request and compare two responses.
17. [Read form choices in native C](17-read-form-choices-in-native-c.md). Use the local C route to decode ordinary form values and return the selected practice report label.
18. [Serve two Apache sites on one port](18-serve-two-apache-sites-on-one-port.md). Read two site names in the Apache configuration listing and point them at different folders.
19. [Tell which Apache site answered](19-tell-which-apache-site-answered.md)
20. [Keep links inside an application context](20-keep-links-inside-an-application-context.md)
21. [Verify a web archive upgrade and rollback](21-verify-a-web-archive-upgrade-and-rollback.md)
22. [Read which methods a web route allows](22-read-which-methods-a-web-route-allows.md)

[Start with the short guide](../../../simple-steps/course-guides/web-development-and-servers.md) · [All web development lessons](../index.md) · [Learning Java](../../03-native-code/learning-java/index.md)
