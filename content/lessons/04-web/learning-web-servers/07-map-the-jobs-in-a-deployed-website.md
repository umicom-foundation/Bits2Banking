<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/07-map-the-jobs-in-a-deployed-website.md

PURPOSE:
Describe the responsibilities of a deployed web server, application and browser.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Map the jobs in a deployed website

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }

You have used a browser to look at a file, ask a static server for a page and call an application route. Before deploying a more complex site, decide which component owns each part of the work.

## Match each tool to its job

| Component | Example responsibility |
| --- | --- |
| Browser | Display the HTML and CSS, and run the page's JavaScript when present |
| Apache HTTP Server | Serve public files, or forward selected HTTP requests to another service |
| Apache Tomcat | Run the Java web archive using the Jakarta Servlet API |
| WildFly or Red Hat JBoss EAP | Run Jakarta EE applications that need the wider services provided by their chosen profile |
| Native Umicom Framework application | Compile domain rules to a C23 executable and make a defined route available through the Framework HTTP service |
| Database | Store application records and answer queries from the application service |

A **reverse proxy** receives a browser's HTTP request and passes it to an upstream server. The browser can use one address while the application runs on its own local port. Path routing is one example. Requests for `/lessons/` can stay at the static server, while `/api/` can go to an application. Decide who owns the original prefix and test the path as received by the upstream.

LAMP commonly names a Linux, Apache, MySQL and PHP stack. WAMP uses Windows for the same example stack. A stack is the group of components you choose to run the site. One option for PHP is to let the web server send requests to a PHP-FPM worker through FastCGI. A Java web archive uses a compatible Java container or application server. A native C or D application can run behind the web server when it exposes a defined protocol, such as HTTP. Pick the connection contract before choosing how to start each process.

[Apache reverse proxy guide](https://httpd.apache.org/docs/2.4/howto/reverse_proxy.html) · [PHP-FPM manual](https://www.php.net/manual/en/install.fpm.php)

## Plan a small deployment on paper

1. Sketch one route for a lesson page and one for a native status service.
2. Write the expected content type and one expected result for each route. For example, use `text/html` with a known heading and `application/json` with a `status` field.
3. Decide what to inspect if the HTML works but the status service is unreachable. Start at the upstream address and its startup log, then check the proxy path mapping.
4. Test the upstream directly and the public-facing route separately in a local rehearsal. If the direct result works and the forwarded result fails, investigate the forwarding layer with both outputs to hand.
5. Write where the compiled process runs. In this course the native process runs on the server machine and the browser receives its response. A program executed inside the browser would need a separate browser-supported runtime or execution model.

**Check your answer.** A web page returning `200` establishes that the static route worked for that request. An application route needs its own response check. Separate the two so a learner or operator can see exactly which component needs attention.

[Previous, follow native C23](06-compare-a-native-c-web-service.md) · [Course](index.md) · [Further practice with native routes and workers](../../05-engineering/building-a-web-server-in-c/24-qualify-a-local-c-web-workflow.md)
