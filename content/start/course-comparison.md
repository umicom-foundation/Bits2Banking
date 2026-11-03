# Courses, lessons and reading formats

A **course** is a suggested learning route. A **lesson** explains one topic inside that route. Some written lessons are useful reference chapters without a matching browser course. A **book** selects and arranges chapters for a longer edition.

Use the [written course catalogue](written-courses.md) for the course order. Use the [lesson library](../lessons/index.md) to look up a subject. Both begin from the same [learning sequence](learning-sequence.md).

## The source folders

| Folder | What it contains | How to use it |
| --- | --- | --- |
| `content/lessons` | Markdown lesson manuscripts grouped by subject | Read an explanation, edit its text or follow the course links. |
| `content/courses` | Browser lessons, course introductions and diagrams | Read the same subject with its browser presentation. |
| `content/books` | Book introductions and chapter collections | Choose a longer edition after checking its prerequisites. |
| `labs` | Practical source files and project instructions | Build a separate practice copy when the lesson reaches that step. |
| `content/umicom` | Product and development guides | Connect the subject to the real Umicom application. |
| `knowledge/registries` | Structured lists of source relationships | Help publishing tools find corresponding pages without guessing names. |

The numbered lesson folders group subjects. They do not mean that you must finish every finance, systems or AI chapter before returning to programming. Older course paths remain available for bookmarks.

## Compare the course versions

The table counts lesson source pairs, not completed assessments or verified software features. Eight older computer-introduction addresses intentionally share their Markdown manuscripts with the current course. The catalogue therefore has 1,160 browser addresses and 1,152 distinct paired manuscripts. Counts include further reference chapters, not just each introductory route. A pair means both files exist. It does not prove that older versions say exactly the same thing: review both before making a shared edition.

| Course | Lesson pairs | Markdown location | Browser introduction |
| --- | ---: | --- | --- |
| Introduction to Computers | 8 | `content/lessons/00-getting-started` | [Open](../courses/learning-computer-architecture/index.html) |
| Learning C | 17 | `content/lessons/learning-c` | [Open](../courses/learning-c/index.html) |
| Introduction to Version Control | 4 | `content/lessons/05-engineering/introduction-to-version-control` | [Open](../courses/introduction-to-version-control/index.html) |
| Umicom Framework Development | 35 | `content/lessons/umicom-development` | [Open](../courses/umicom-development/index.html) |
| Building a Web Server in C | 4 | `content/lessons/05-engineering/building-a-web-server-in-c` | [Open](../courses/building-a-web-server-in-c/index.html) |
| Learning HTML | 2 | `content/lessons/04-web/learning-html` | [Open](../courses/learning-html/index.html) |
| Learning CSS | 2 | `content/lessons/04-web/learning-css` | [Open](../courses/learning-css/index.html) |
| Learning JavaScript | 2 | `content/lessons/04-web/learning-javascript` | [Open](../courses/learning-javascript/index.html) |
| Learning PHP | 2 | `content/lessons/04-web/learning-php` | [Open](../courses/learning-php/index.html) |
| Learning Python | 2 | `content/lessons/02-programming/learning-python` | [Open](../courses/learning-python/index.html) |
| Learning C++ | 2 | `content/lessons/03-native-code/learning-cpp` | [Open](../courses/learning-cpp/index.html) |
| Learning Java | 2 | `content/lessons/03-native-code/learning-java` | [Open](../courses/learning-java/index.html) |
| Introduction to RISC-V | 2 | `content/lessons/03-native-code/learning-riscv` | [Open](../courses/learning-riscv/index.html) |
| Learning RISC-V Assembly | 3 | `content/lessons/03-native-code/learning-riscv-assembly` | [Open](../courses/learning-riscv-assembly/index.html) |
| Umicom Kernel from Scratch | 14 | `content/lessons/06-umicom/umicom-kernel-from-scratch` | [Open](../courses/umicom-kernel-from-scratch/index.html) |
| Umicom OS from Scratch | 9 | `content/lessons/06-umicom/umicom-os-from-scratch` | [Open](../courses/umicom-os-from-scratch/index.html) |
| Building a Compiler in C | 9 | `content/lessons/05-engineering/building-a-compiler-in-c` | [Open](../courses/building-a-compiler-in-c/index.html) |
| Mathematics for AI | 316 | `content/lessons/11-maths-for-ai` | [Open](../courses/maths-for-ai/index.html) |
| Building an LLM from Scratch | 506 | `content/lessons/10-native-ai` | [Open](../courses/llm-from-scratch/index.html) |
| Introduction to Distributed Learning | 84 | `content/lessons/12-distributed-learning` | [Open](../courses/distributed-learning/index.html) |
| Guide to AI Research | 56 | `content/lessons/13-ai-research` | [Open](../courses/ai-research/index.html) |
| Umicom application and financial-system studies | 24 | `content/lessons/06-umicom/framework-studies/framework-boundaries`<br>`content/lessons/06-umicom/framework-studies/studio-workflows`<br>`content/lessons/06-umicom/framework-studies/builds-and-diagnostics`<br>`content/lessons/06-umicom/framework-studies/data-and-messaging`<br>`content/lessons/06-umicom/framework-studies/secure-connected-services`<br>`content/lessons/07-practical-domains/framework-studies/banking-and-payments`<br>`content/lessons/07-practical-domains/framework-studies/accounting-and-control`<br>`content/lessons/07-practical-domains/framework-studies/trading-and-posttrade`<br>`content/lessons/07-practical-domains/framework-studies/treasury-operations`<br>`content/lessons/07-practical-domains/framework-studies/commodities-and-digital-assets`<br>`content/lessons/07-practical-domains/framework-studies/financial-integration`<br>`content/lessons/10-native-ai/framework-studies/native-ai-and-learning` | [Open](../courses/framework-and-finance/index.html) |
| Introduction to Blockchain and Distributed Ledgers | 36 | `content/lessons/14-blockchain-ledgers` | [Open](../courses/blockchain-ledgers/index.html) |
| Introduction to Computers — earlier course address | 8 | `content/lessons/00-getting-started` | [Open](../courses/computing-from-the-beginning/index.html) |
| Learning C — earlier reading sequence | 11 | `content/lessons/c-from-the-beginning` | [Open](../courses/c-from-the-beginning/index.html) |

## Create another edition

1. Choose a course and its lesson order. Do not assemble unrelated pages simply because their filenames are next to one another.
2. Compare each Markdown and HTML pair. Keep unique explanations, diagrams, exercises and answers.
3. Check the code against the named source file. Keep angle brackets, quotation marks and indentation intact.
4. Decide what the new edition needs. A printed book needs numbered figures; a video script needs narration and screen actions; an accessible PDF needs searchable text and descriptive captions.
5. Record the source revision and selected lesson order with the edition. Check the result after conversion: an exporter can change code wrapping or lose a diagram.

Markdown and HTML remain editable sources. Word documents, PDFs, books and video scripts are derived editions. The source map is available now; automatic export into all these formats is a separate capability. See [Maintaining learning sources](../contributing/learning-sources.md).
