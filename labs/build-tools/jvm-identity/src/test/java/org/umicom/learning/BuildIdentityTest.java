/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: BuildIdentityTest.java
 *
 * PURPOSE:
 *   Verify identity publication and required input with the same tests in both build tools.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
package org.umicom.learning;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class BuildIdentityTest {
    @Test public void preservesIdentity() {
        BuildIdentity identity = new BuildIdentity("native-client", "1.0.0");
        assertEquals("native-client:1.0.0", identity.display());
        assertEquals("native-client", identity.component());
        assertEquals("1.0.0", identity.version());
    }
    @Test(expected = IllegalArgumentException.class)
    public void rejectsMissingComponent() { new BuildIdentity(null, "1.0.0"); }
    @Test(expected = IllegalArgumentException.class)
    public void rejectsBlankVersion() { new BuildIdentity("native-client", " "); }
}
