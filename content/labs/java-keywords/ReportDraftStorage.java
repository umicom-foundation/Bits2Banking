/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-keywords/ReportDraftStorage.java
 *
 * PURPOSE:
 *   Restore a report draft from bytes while rebuilding its temporary preview.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

public final class ReportDraftStorage {
    private static final class ReportDraft implements Serializable {
        private static final long serialVersionUID = 1L;

        private static String previewStyle = "wide";
        private final int rows;
        private transient String cachedPreview;

        private ReportDraft(int rows) {
            this.rows = rows;
        }

        private String preview() {
            // Build this display text from the current style and the saved count.
            if (cachedPreview == null) {
                cachedPreview = previewStyle + " preview of " + rows + " rows";
            }
            return cachedPreview;
        }
    }

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        ReportDraft original = new ReportDraft(3);
        System.out.println("Original preview " + original.preview());

        ByteArrayOutputStream bytes = new ByteArrayOutputStream();
        try (ObjectOutputStream writer = new ObjectOutputStream(bytes)) {
            writer.writeObject(original);
        }

        // The running class changes its display style after the draft is saved.
        ReportDraft.previewStyle = "compact";
        ReportDraft restored;
        try (ObjectInputStream reader =
                new ObjectInputStream(new ByteArrayInputStream(bytes.toByteArray()))) {
            restored = (ReportDraft) reader.readObject();
        }

        System.out.println("Restored row count " + restored.rows);
        System.out.println("Current class style " + ReportDraft.previewStyle);
        System.out.println("Restored cached preview " + restored.cachedPreview);
        System.out.println("Rebuilt preview " + restored.preview());
    }
}
