<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/08-inspect-a-jboss-eap-deployment.md

PURPOSE:
Read a local JBoss EAP deployment record and distinguish it from application behavior.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Inspect a Red Hat JBoss EAP deployment

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }

A browser asks an application to do work. A management console or command line tells an operator which applications the server knows about. This exercise reads a deployment record first, then asks how you would verify the application itself.

Start with a local standalone Red Hat JBoss Enterprise Application Platform 8.1 training instance that you are authorised to inspect. The exercise also works on paper with the practice row below. Read how the [WildFly lab used its deployment CLI](05-deploy-the-same-war-on-wildfly.md) before comparing the two environments.

## 1. Identify the application and its server

Write down the product release, the Java version supported for that installation, and the application archive name. EAP 8.1 uses Jakarta EE 10 and Servlet 6.0. The Tomcat 11 practice compile used Servlet 6.1. Use the API version supported by your target and verify that specific build before moving an application. [EAP 8.1 migration and component versions](https://docs.redhat.com/en/documentation/red_hat_jboss_enterprise_application_platform/8.1/html/migration_guide/preparing-for-migration-to-jboss-eap-8_default) · [Tomcat supported specifications](https://tomcat.apache.org/whichversion.html)

A standalone server has one local server configuration. A managed domain lets operators manage servers in groups. The same deployment name can have different rollout results across the groups. This exercise uses one standalone instance. [JBoss EAP management guide](https://docs.redhat.com/en/documentation/red_hat_jboss_enterprise_application_platform/8.1/html/configuration_guide/eap-mgmt-overview_default)

## 2. Read the deployment list

Set the path to the approved local EAP installation. Use the management port configured for your training server. The example uses the default port on the same machine.

~~~powershell
$eapHome = 'C:/btb-lab/jboss-eap-8.1'
$cli = Join-Path $eapHome 'bin/jboss-cli.bat'
if (-not (Test-Path -LiteralPath $cli -PathType Leaf)) {
    throw 'Set the path to the EAP training installation.'
}
& $cli --connect --controller=127.0.0.1:9990
~~~

At the management prompt, enter these two commands in order.

~~~text
deployment info
quit
~~~

Look for the archive name, runtime name, enabled flag and recorded status. This sample row represents one possible training deployment.

| Name | Runtime name | Enabled | Status |
| --- | --- | --- | --- |
| `btb-statement.war` | `btb-statement.war` | `true` | `OK` |

If the connection is refused, check whether the training server is running and whether you used its management port. If authentication is requested, follow the administrator’s local access procedure. If the named archive is absent, record it as missing. Keep the command output free of credentials. [EAP deployment listing](https://docs.redhat.com/en/documentation/red_hat_jboss_enterprise_application_platform/8.1/html/configuration_guide/managing-application-deployments_default)

## 3. Check one application response

Ask the instructor for the intended HTTP address and application context. For the fictional statement app, this might be the already deployed `/btb-statement/summary` route on the training server. Use the approach from the [HTTP lesson](02-read-an-http-exchange.md) to write down the observed status and body. Keep the result beside the deployment record.

| Evidence | What to record |
| --- | --- |
| Management | Target instance, archive identity, enabled flag, runtime name and status |
| HTTP | Host and port, requested path, status and the response you expected |

**Check yourself.** If the management view shows `OK` and the request returns `404`, check the context and route before deciding whether the application is ready. In a managed domain, record the target server group before interpreting a result.

The same distinction applies to Umicom Framework. A reviewed application identity is one record. The result from a bounded HTTP request is another. Keep both when describing whether a service started and serves the intended route.

[Web server course](index.md) · [Native C23 service](06-compare-a-native-c-web-service.md)
