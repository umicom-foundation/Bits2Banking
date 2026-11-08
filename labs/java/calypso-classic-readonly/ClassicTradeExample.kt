/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: ClassicTradeExample.kt
 *
 * PURPOSE:
 *   Consume the documented Java SDK adapter from an existing Kotlin session.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import com.calypso.tk.service.DSConnection

// The host owns the authenticated session and permission policy.
fun readApprovedTradeIdentities(connection: DSConnection, approvedIds: IntArray): List<String> {
    return ClassicTradeReader(connection).read(approvedIds).map { identity ->
        val returned = identity.returnedId
        if (returned == null) identity.requestedId.toString() + ": no record returned"
        else identity.requestedId.toString() + ": returned " + returned.toString()
    }
}
