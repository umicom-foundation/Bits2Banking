import java.math.BigDecimal;
import java.util.List;

public class LedgerDemo {
    record Posting(String account, BigDecimal debit, BigDecimal credit) {}

    static boolean IsBalanced(List<Posting> postings) {
        BigDecimal totalDebit = BigDecimal.ZERO;
        BigDecimal totalCredit = BigDecimal.ZERO;

        for (Posting posting : postings) {
            totalDebit = totalDebit.add(posting.debit());
            totalCredit = totalCredit.add(posting.credit());
        }
        return totalDebit.compareTo(totalCredit) == 0;
    }

    public static void main(String[] args) {
        List<Posting> journal = List.of(
            new Posting("Cash", new BigDecimal("25.10"), BigDecimal.ZERO),
            new Posting("Donation income", BigDecimal.ZERO, new BigDecimal("25.10"))
        );
        System.out.println("Journal balanced: " + IsBalanced(journal));
    }
}
