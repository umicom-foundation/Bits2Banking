/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/LocalReadingDatabase.java
 *
 * PURPOSE:
 *   Teach typed JDBC parameters and transaction boundaries with a local in-memory database.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class LocalReadingDatabase {
    static void addReading(Connection database, String site, int units) throws SQLException {
        try (var insert = database.prepareStatement("INSERT INTO reading(site, units) VALUES (?, ?)")) {
            // The values keep their JDBC types and never become part of the SQL text.
            insert.setString(1, site);
            insert.setInt(2, units);
            insert.executeUpdate();
        }
    }

    static long totalAtSite(Connection database, String site) throws SQLException {
        String sql = "SELECT COALESCE(SUM(units), 0) FROM reading WHERE site = ?";
        try (var query = database.prepareStatement(sql)) {
            query.setString(1, site);
            try (var totals = query.executeQuery()) {
                // An aggregate without GROUP BY returns one row, even for an empty site.
                if (!totals.next()) {
                    throw new SQLException("Expected one total row");
                }
                return totals.getLong(1);
            }
        }
    }

    public static void main(String[] args) throws SQLException {
        // A named H2 memory database exists only for this local exercise.
        try (var database = DriverManager.getConnection("jdbc:h2:mem:readings")) {
            try (var schema = database.createStatement()) {
                schema.executeUpdate("CREATE TABLE reading (site VARCHAR(20) NOT NULL, units INTEGER NOT NULL)");
            }

            // Set the transaction mode after creating the table so each boundary is clear.
            database.setAutoCommit(false);
            addReading(database, "north", 12);
            addReading(database, "north", 8);
            addReading(database, "south", 5);
            database.commit();
            System.out.println("Confirmed north units: " + totalAtSite(database, "north"));

            addReading(database, "north", 3);
            System.out.println("During the trial: " + totalAtSite(database, "north"));
            database.rollback();
            System.out.println("After rollback: " + totalAtSite(database, "north"));
            System.out.println("Unlisted site: " + totalAtSite(database, "west"));
        }
    }
}
