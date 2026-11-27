<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/05-deploy-the-same-war-on-wildfly.md

PURPOSE:
Deploy the same web archive on WildFly and explain the role of Red Hat JBoss EAP.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Deploy the same web archive on WildFly

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }

WildFly is a community Jakarta EE application server. It can run web applications and also provides facilities used by larger applications, such as managed transactions and data sources. Red Hat JBoss Enterprise Application Platform, called JBoss EAP, is a supported Red Hat product derived from WildFly. Its release, supported JDKs and product lifecycle have their own documentation.

In this exercise you will use standard WildFly 42 and the same Tomcat WAR. The example uses a small set of Jakarta Servlet interfaces common to both servers. An application using vendor extensions or another Jakarta EE version needs its own compatibility check.

## Start one local server

1. Finish [the Tomcat lesson](04-deploy-a-war-on-tomcat.md) and retain `btb-statement.war` in the practice folder. Choose the standard ZIP from [WildFly downloads](https://www.wildfly.org/downloads/). Follow the download verification instructions and extract it into a new folder. WildFly 42 requires Java 17 or later and recommends a current Java 25 update. Check the requirements for the version you use.
2. In PowerShell, correct the example folder and start the practice copy. The two address settings keep application and management access on the loopback address in the standard configuration.

    ```powershell
    $wildfly = "C:\learning\wildfly-42.0.0.Final"
    Test-Path "$wildfly\bin\standalone.bat"
    & "$wildfly\bin\standalone.bat" "-b=127.0.0.1" "-bmanagement=127.0.0.1"
    ```

    Expect a `True` result and then the server's startup messages. This standard standalone setup uses port `8080` for the application and `9990` for management. If a port is occupied, stop and read the startup error. Close the application using the port only if it is your own practice process.

## Deploy and compare

1. In another PowerShell window, enter the practice folder and check the saved archive's hash. Then open the management CLI in the same window. Use the same corrected WildFly folder.

    ```powershell
    $lab = Join-Path $env:USERPROFILE "web-servers-lab"
    $wildfly = "C:\learning\wildfly-42.0.0.Final"
    Set-Location $lab
    Get-FileHash .\btb-statement.war
    & "$wildfly\bin\jboss-cli.bat" --connect "--controller=127.0.0.1:9990"
    ```

    The hash should match the Tomcat lesson. Run the CLI under the same local account as the practice server. WildFly's local CLI can authenticate using the server's local file token. Keep that management connection on your machine.

2. At the management prompt, type these commands on separate lines.

    ```text
    deployment deploy-file btb-statement.war
    deployment list
    quit
    ```

    The list should include `btb-statement.war`. If deployment fails, read the first cause in the server terminal. Confirm that the WAR contains the class from the previous lesson and that your server release and Java version meet its requirements.

3. Back in PowerShell, request the page and servlet.

    ```powershell
    curl.exe -i http://127.0.0.1:8080/btb-statement/index.html
    curl.exe -i http://127.0.0.1:8080/btb-statement/summary
    ```

    Expect `200` and the same result from the servlet. Write down the URL, status, content type and body for Tomcat and WildFly. The port and server-specific headers may differ. The body remains `2 entries reviewed.`

4. Reopen the management CLI and enter `deployment undeploy btb-statement.war`, followed by `deployment list`. The WAR name should disappear from the list. Enter `shutdown` to stop the practice server, then check that its practice URL no longer responds. If the Windows terminal shows `Press any key to continue`, press a key after the server reports that it stopped.

## Choose the reference for the server you use

If your organisation runs JBoss EAP, ask which EAP release and Java version it supports. Follow that release's installation, management and deployment guide. Write down which Jakarta EE profile and APIs the application needs. A WildFly lab result is one way to learn the workflow. A support decision requires checking the exact EAP environment.

[WildFly getting started](https://docs.wildfly.org/42/Getting_Started_Guide.html) · [WildFly deployment and management](https://docs.wildfly.org/42/Admin_Guide.html) · [Red Hat JBoss EAP 8.1 documentation](https://docs.redhat.com/en/documentation/red_hat_jboss_enterprise_application_platform/8.1)

[Previous, deploy on Tomcat](04-deploy-a-war-on-tomcat.md) · [Course](index.md) · [Next, follow a request into native C23](06-compare-a-native-c-web-service.md)
