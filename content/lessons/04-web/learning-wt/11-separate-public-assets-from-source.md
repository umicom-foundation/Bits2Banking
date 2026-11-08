<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/11-separate-public-assets-from-source.md

PURPOSE:
Separate public assets from application source

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate public assets from application source

## Before starting

Complete a successful lab build. Locate build-source/public and the actual Wt resources directory in your installation. This lesson uses a loopback-only server. Keep source files and qualification logs outside the directories selected for public resources.

## Draw the file boundary

The document root is a directory offered to the web-serving layer. It is not the application source root. CMake creates an empty public directory so the launch command can name an intentional boundary. Wt resources are supplied separately from the installed package. Adding a file to a public directory is an exposure decision even when no navigation link points to it.

## Select real paths

Replace the example resources path before running. Test-Path must report True for that directory. Run from the lab directory so build-source/public resolves as intended.

~~~powershell
Test-Path 'C:/libraries/wt/share/Wt/resources'
.\build-source\btb-wt-profile.exe --docroot 'build-source/public' --resources-dir 'C:/libraries/wt/share/Wt/resources' --http-address 127.0.0.1 --http-port 9090
~~~

## Observe resource requests

Open http://127.0.0.1:9090/ and inspect the browser Network panel during a reload. Compare failed resource paths with the configured Wt resources directory. A missing stylesheet or script concerns resource delivery; changing the accepted name alphabet cannot repair it. Stop the server with Ctrl+C after the exercise.

## Investigate an unexpected file response

Request only harmless files you created for this local exercise. If a private source file can be fetched, preserve the launch arguments and inspect which directory was exposed before making another run. Remove the exposure by selecting the intended public directory, then repeat the observation. Do not publish logs or credential material to test this boundary.

## Exercise and worked answer

A colleague proposes --docroot . from the repository root because resource errors disappear. Why is that an unsuitable fix? It broadens the files offered by the server and hides the incorrect resources selection. Keep the narrow document root and correct the Wt resources path. The lab configuration is still not a reviewed Internet deployment.

## Reference

[Wt application and connector overview](https://www.webtoolkit.eu/wt/doc/reference/html/overview.html). Consult the version matching your installation.

## Read the source

[labs/framework/wt-profile/README.md](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Exercise production widget events without HTTP](10-exercise-server-events-without-http.md) · [Next: Observe independent browser sessions](12-observe-independent-browser-sessions.md)
