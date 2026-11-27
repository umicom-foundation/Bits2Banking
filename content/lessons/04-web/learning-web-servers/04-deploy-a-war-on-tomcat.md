<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/04-deploy-a-war-on-tomcat.md

PURPOSE:
Compile a portable Jakarta Servlet and package and deploy it locally on Apache Tomcat.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Deploy a web archive on Apache Tomcat

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }

A servlet is a Java class the server can call for an HTTP request. In this exercise Tomcat serves the practice page from a file and calls a servlet to make the response for `/summary`.

You need a JDK version 17 or later and a fresh [Apache Tomcat 11 Core ZIP](https://tomcat.apache.org/download-11.cgi). Verify the archive using the instructions on that page and extract it into a practice folder. The JDK supplies `javac` and `jar`. Tomcat supplies the Jakarta Servlet interfaces and the HTTP listener. If Java is new to you, start with [Learning Java](../../03-native-code/learning-java/index.md).

## Prepare the application

1. In PowerShell, set `$tomcat` to the folder containing your extracted `bin`, `conf` and `lib` directories. Check your Java tools first. Make sure `JAVA_HOME` points at this JDK folder if Tomcat needs help locating it.

    ```powershell
    $lab = Join-Path $env:USERPROFILE "web-servers-lab"
    $tomcat = "C:\learning\apache-tomcat-11"
    java -version
    javac -version
    jar --version
    Test-Path "$tomcat\lib\servlet-api.jar"
    New-Item -ItemType Directory -Path "$lab\war-root\WEB-INF\classes" -Force
    ```

2. Save this Java source as `SummaryServlet.java` in `$lab`. The source belongs next to the packaging folder so only its compiled class goes in the archive.

    ```java
    package btb.web;

    import java.io.IOException;
    import jakarta.servlet.annotation.WebServlet;
    import jakarta.servlet.http.HttpServlet;
    import jakarta.servlet.http.HttpServletRequest;
    import jakarta.servlet.http.HttpServletResponse;

    // The container adds this route beneath the deployed application's path.
    @WebServlet("/summary")
    public class SummaryServlet extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response)
                throws IOException {
            // Describe the body before obtaining its writer.
            response.setContentType("text/plain");
            response.setCharacterEncoding("UTF-8");
            int reviewedCount = 2;
            response.getWriter().println(reviewedCount + " entries reviewed.");
        }
    }
    ```

    `@WebServlet` gives the path inside the application. `doGet` handles GET requests. The first two response calls tell the browser how to interpret the body. The last call writes the fictional result.

3. Copy your static page and its assets in, then compile the servlet and create a WAR. A WAR is an archive of a Java web application's files. Run one line at a time and stop on an error.

    ```powershell
    Copy-Item "$lab\public\*" "$lab\war-root"
    javac --release 17 -cp "$tomcat\lib\servlet-api.jar" -d "$lab\war-root\WEB-INF\classes" "$lab\SummaryServlet.java"
    jar --create --file "$lab\btb-statement.war" -C "$lab\war-root" .
    jar --list --file "$lab\btb-statement.war"
    Get-FileHash "$lab\btb-statement.war"
    ```

    Expect to see `index.html`, `site.css`, the two brand files and `WEB-INF/classes/btb/web/SummaryServlet.class` in the archive. The server supplies the Servlet API at runtime, so keep `servlet-api.jar` out of your WAR. Save the hash so you can verify you use the same archive in the next lesson.

## Start Tomcat and check two routes

1. In your practice copy of `conf\server.xml`, find the active HTTP connector, usually the one with `port="8080"`. Change to `port="8181"` and add `address="127.0.0.1"` to that connector. Keep its other attributes. Use the standard archive and leave other example connectors commented.

    ```xml
    <Connector port="8181" address="127.0.0.1" protocol="HTTP/1.1"
               connectionTimeout="20000" redirectPort="8443" />
    ```

    A connector takes incoming connections and hands their requests to Tomcat. The address setting makes this connector listen only on this computer. The excerpt shows where the two edited attributes go.

2. Leave the practice archive intact in `$lab`. Copy it to `webapps` and start Tomcat in your existing PowerShell window.

    ```powershell
    Copy-Item "$lab\btb-statement.war" "$tomcat\webapps"
    & "$tomcat\bin\catalina.bat" run
    ```

3. Once the terminal says the server has started, run these in a second PowerShell window.

    ```powershell
    curl.exe -i http://127.0.0.1:8181/btb-statement/index.html
    curl.exe -i http://127.0.0.1:8181/btb-statement/summary
    ```

    Expect `200` for each URL. The first response contains HTML. The second response has a `text/plain` content type and the body `2 entries reviewed.` The prefix `/btb-statement` is the application context path, normally derived from the WAR filename in this exercise.

4. In the Tomcat terminal, press **Ctrl+C** and confirm termination if the command prompts you. Verify the practice URL stops responding.

If Tomcat answers with `404`, check its deployment log and make sure the URL includes `/btb-statement`. If Java reports a missing `jakarta.servlet` package, check the compile command's classpath. Older examples may use `javax.servlet` under a different Servlet generation. Follow Tomcat 11's Jakarta documentation for this exercise.

[Tomcat 11 setup](https://tomcat.apache.org/tomcat-11.0-doc/setup.html) · [HTTP connectors](https://tomcat.apache.org/tomcat-11.0-doc/config/http.html) · [Web application deployment](https://tomcat.apache.org/tomcat-11.0-doc/deployer-howto.html)

[Previous, serve files with Apache](03-serve-files-with-apache-http-server.md) · [Course](index.md) · [Next, deploy the same WAR on WildFly](05-deploy-the-same-war-on-wildfly.md)
