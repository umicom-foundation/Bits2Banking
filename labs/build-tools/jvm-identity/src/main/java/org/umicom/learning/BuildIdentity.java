/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: BuildIdentity.java
 *
 * PURPOSE:
 *   Keep a small JVM build identity independent of the selected build tool.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
package org.umicom.learning;

/** Teaching fixture for Maven and Gradle; no Framework domain logic is copied. */
public record BuildIdentity(String component, String version) {
    public BuildIdentity {
        if (component == null || component.isBlank())
            throw new IllegalArgumentException("component is required");
        if (version == null || version.isBlank())
            throw new IllegalArgumentException("version is required");
    }
    public String display() {
        return component + ":" + version;
    }
}
