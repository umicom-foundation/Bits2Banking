# Episode 146 — Your first C23 cash-ladder demonstration

*Bits to Banking · Treasury From Zero · Approximate duration: 11 minutes*

## What are we building? (0:00–2:00)

**Narration:** “Up to now we have used a notebook to forecast money coming in and going out. We can ask a small C program to keep these records for us. You do **not** need to understand C yet: first concentrate on the financial meaning.”

**On screen:** A simple cash ladder with GBP receipts, GBP payments and their dates. No live accounts or credentials.

## Explain exact amounts (2:00–4:30)

**Narration:** “A useful rule in financial software is not to store an amount of settled money as an unlabelled floating-point number. For a two-decimal teaching currency, one hundred pounds can be represented as ten thousand minor units. That keeps the simple cash arithmetic exact. Every record must still carry a currency and a date.”

## Run the laboratory (4:30–8:00)

**On screen:** From the Bits2Banking root, demonstrate the existing `labs/native/treasury-cash-ladder` CMake project using the README's interactive Windows or Linux commands. Explain each command before executing it. Show the demo and read the output with the viewer.

**Narration:** “The source belongs to a classroom simulator. It does not connect to a bank or Calypso. Before accepting a cash movement, it checks the required fields. The tests deliberately try invalid input and make sure errors do not corrupt the stored results.”

## Close with evidence (8:00–11:00)

**Narration:** “A program printing the expected figure once is not enough. We also want repeatable tests, including a negative amount where it is forbidden, a duplicate record and a balance that would overflow the supported range. Only then can we say the *teaching contract* behaves as intended for those cases.”

“Your last exercise is to change the fictional date of a receipt and explain how the forecast should change. Try the arithmetic on paper first. In later programming chapters, we will change code together and compare the program with the handwritten answer.”

*Do not treat this educational program as a payment system, bank ledger or licensed Calypso adapter.*
