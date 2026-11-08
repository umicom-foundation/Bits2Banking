/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: ClassicTradeReader.java
 *
 * PURPOSE:
 *   Read explicitly requested trade identities through the documented classic Calypso Java boundary.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import com.calypso.tk.core.Trade;
import com.calypso.tk.service.DSConnection;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/** Original adapter based on the classic APIs described in the Treasury guide.
 * Compile against the licensed target SDK before use. The application owns the
 * authenticated connection, permissions, timeout policy and disconnect. This
 * class neither establishes a session nor saves or modifies a vendor object.
 */
public final class ClassicTradeReader {
    public static final int MAX_REQUESTS = 256;
    private final DSConnection connection;
    public ClassicTradeReader(DSConnection connection) {
        if (connection == null) throw new IllegalArgumentException("Connection is required");
        this.connection = connection;
    }
    public static final class Identity {
        public final int requestedId;
        public final Long returnedId;
        private Identity(int requestedId, Long returnedId) {
            this.requestedId = requestedId;
            this.returnedId = returnedId;
        }
        // A null vendor result is not proof that the caller has permission to
        // know whether a trade exists. Preserve absence without guessing why.
        public boolean hasRecord() { return returnedId != null; }
    }
    public List<Identity> read(int[] requestedIds) throws Exception {
        if (requestedIds == null || requestedIds.length == 0 || requestedIds.length > MAX_REQUESTS)
            throw new IllegalArgumentException("Request 1 to 256 distinct positive classic trade IDs");
        // Snapshot before validation: a caller cannot alter IDs halfway through
        // the batch. This object is still an owner-thread, serial-use adapter.
        int[] ids = requestedIds.clone();
        Set<Integer> seen = new HashSet<Integer>();
        for (int id : ids)
            if (id <= 0 || !seen.add(id)) throw new IllegalArgumentException("Invalid or repeated trade ID");
        List<Identity> result = new ArrayList<Identity>(ids.length);
        for (int id : ids) {
            Trade trade = connection.getRemoteTrade().getTrade(id);
            result.add(new Identity(id, trade == null ? null : Long.valueOf(trade.getId())));
        }
        // If any remote call throws, no successful partial list is returned.
        // This is not a database snapshot: trades can change between calls.
        return Collections.unmodifiableList(result);
    }
}
