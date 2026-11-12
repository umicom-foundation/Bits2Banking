/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: build.gradle.kts
 *
 * PURPOSE:
 *   Build the shared JVM fixture with the Java plugin and explicit test dependency.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
plugins { java }
group = "org.umicom.learning"
version = "1.0.0"
repositories { mavenCentral() }
java { toolchain { languageVersion = JavaLanguageVersion.of(17) } }
dependencies { testImplementation("junit:junit:4.13.2") }
tasks.withType<JavaCompile>().configureEach { options.encoding = "UTF-8" }
tasks.test { useJUnit() }
