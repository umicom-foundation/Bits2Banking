# Choose the Servlet API for your server

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Compile the same `SummaryServlet.java` that you used in [Deploy a web archive on Apache Tomcat](04-deploy-a-war-on-tomcat.md). Make two class directories so you can inspect the result for each server without replacing an earlier build.

## Choose a target and download its API

| Practice server | Servlet API | File to place beside `SummaryServlet.java` |
|---|---|---|
| Red Hat JBoss EAP 8.1 | 6.0 | `jakarta.servlet-api-6.0.0.jar` |
| Apache Tomcat 11 | 6.1 | `jakarta.servlet-api-6.1.0.jar` |

The API JAR gives the compiler the class and method names it can use. Choose the version supplied by your target server. For this comparison, download both listed files and put them in a new practice folder with the Java file you saved from the Tomcat lesson. [Servlet API 6.0.0](https://central.sonatype.com/artifact/jakarta.servlet/jakarta.servlet-api/6.0.0) · [Servlet API 6.1.0](https://central.sonatype.com/artifact/jakarta.servlet/jakarta.servlet-api/6.1.0)

## Compile and inspect the EAP version

1. Open PowerShell in that practice folder.
2. Enter these commands. After the compile, expect the number `0`. Then inspect the class and look for `major version: 61` and the mapping `/summary`.

```powershell
$apiVersion = '6.0.0'
$classes = "classes-$apiVersion"
New-Item -ItemType Directory -Path $classes -ErrorAction Stop
javac --release 17 -proc:none -cp ".\jakarta.servlet-api-$apiVersion.jar" -d $classes .\SummaryServlet.java
$LASTEXITCODE
javap -classpath $classes -verbose btb.web.SummaryServlet |
    Select-String 'major version: 61|/summary|jakarta.servlet.http.HttpServlet'
```

`--release 17` targets the Java 17 class format. `-cp` points at the Servlet API for this compile. `-proc:none` turns off compiler annotation processors while retaining the servlet annotation in the class file. The route `/summary` still appears when you inspect the class.

## Repeat for Tomcat and compare

1. In the same command block, change `6.0.0` to `6.1.0` and run it again. The new directory is `classes-6.1.0`. The original EAP directory stays available.
2. Compare the class version and route. This example uses parts of the API shared by both versions. A larger servlet can depend on methods introduced in one version, so compile the application against its actual target before packaging it.
3. When building the practice WAR, include the chosen compiled classes and the branded page files from the Tomcat lesson. Keep the compile-time Servlet API JAR outside the WAR so the target server supplies the Servlet classes.
4. Check the server’s supported Java version and deploy and test the archive on that target before treating it as ready.

When building a native Umicom service, use the equivalent check for the target Framework interfaces. Record the headers and library versions you compiled against, then verify the running service’s response separately.

[Return to the Web Servers course](index.md) · [Inspect a JBoss EAP deployment](08-inspect-a-jboss-eap-deployment.md) · [Tomcat supported specifications](https://tomcat.apache.org/whichversion.html) · [JBoss EAP component versions](https://docs.redhat.com/en/documentation/red_hat_jboss_enterprise_application_platform/8.1/html/migration_guide/preparing-for-migration-to-jboss-eap-8_default)
