# Umicom Bits2Banking
# File: content/labs/data/daily-cash-practice/daily_cash.R
#
# PURPOSE:
#   Group the fictional desk entries by observed day in base R.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT

arguments <- commandArgs(trailingOnly = TRUE)
if (length(arguments) != 1L) {
    stop("Supply the path to daily_cash.csv.", call. = FALSE)
}

# Load the agreed field types so the signed cents remain integers.
entries <- read.csv(arguments[[1L]],
                    colClasses = c("integer", "character", "integer"))
if (!identical(names(entries), c("day", "desk", "change_cents")) ||
    nrow(entries) == 0L || anyNA(entries)) {
    stop("Expected a complete day, desk and change_cents table.", call. = FALSE)
}

# Group the days that appear in the table. An unobserved day stays absent.
daily <- aggregate(change_cents ~ day, data = entries, FUN = sum)
daily <- daily[order(daily$day), ]
cat(sprintf("day %d: %d cents", daily$day, daily$change_cents), sep = "\n")
