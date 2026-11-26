# Use Bits2Banking courses in Umicom Studio IDE

![Umicom](../content/assets/branding/umicom-wordmark.svg)

[![Umicom icon](../content/assets/branding/umicom-icon.svg)](../content/assets/branding/umicom.ico)

A course is an ordered set of lessons. Each lesson has a web page and a Markdown manuscript. Markdown is plain text with simple marks for headings, lists and code. Both versions contain the same lesson so they can support a browser, an editor and later publishing tools.

An offline manifest is a small JSON document that names the course files and records a SHA-256 checksum for each one. A checksum is a fingerprint of the bytes. The Framework checks it before presenting a resource. A manifest does not grant permission to run examples, install software or send documents to a model.

## Before you start

Keep the complete Bits2Banking checkout in a folder you can choose and find again, for example C:\umicom\Umicom-Bits2Banking. Keep its content and learning-packs folders together. The paths in these manifests are relative to that checkout, not to an individual course folder.

You need a Studio build that exposes the learning catalogue's manifest-path field. An older build may only offer the default learning-pack.json name. Updating the source alone does not update an already built executable.

## Open a course

1. Open Studio's learning catalogue from its learning command or start page.
2. Enter the absolute Bits2Banking folder as the library folder. On Windows the example is C:\umicom\Umicom-Bits2Banking.
3. Enter the manifest path for your course, for example learning-packs/learning-cmake.json. Use the course list below to find other paths.
4. Load the library. Read any version, missing-file or checksum error before continuing.
5. Select the course in the catalogue and open a lesson. Start with the course guide, then follow the lesson numbers.
6. Remember the library if you want a local shortcut. The remembered choice keeps both the root folder and the selected manifest path. It does not copy the lesson files.
7. To resume, reopen the remembered library and select its course before opening a resource.

The native reader presents verified text and declared resources. It is not a full web browser and does not run page scripts. Open the course index in a browser when you want the web presentation. A link to material outside the selected pack can be refused by the reader; use the corresponding course pack or browser for that reference. The shelf holds at most 32 packs at once. Remove an unused shelf entry before adding another; this does not delete course files.

## Work through a synthetic bank statement

Open these packs in the Bits2Banking desktop reader or in Studio's Learning Catalogue. Each guide links to its web lessons and Markdown manuscripts. Choose a pack first, then use the lesson order in the guide. Where an exercise calls for a compiler, database or browser, run it with the tool named in the lesson.

| Study path | Manifest |
| --- | --- |
| Native statement calculations with Umicom C and C23 | [`native-statement-calculations.json`](native-statement-calculations.json) |
| SQL statement reconciliation | [`sql-statement-reconciliation.json`](sql-statement-reconciliation.json) |
| Accessible statement review with HTML, CSS and JavaScript | [`accessible-statement-review.json`](accessible-statement-review.json) |
| Go statement tools | [`go-statement-tools.json`](go-statement-tools.json) |

The exercises share fictional accounts and transactions. You can start with any path, then compare its result with the result from another tool.

## Larger courses and manuscript companions

The larger Framework, LLM and Kernel courses use two manifests each. The original manifest keeps the HTML course and its stable pack identity. A companion manifest holds the Markdown manuscripts with a distinct pack identity. All lesson files and existing resource identifiers are retained.

One native pack admits at most 256 resources. HTML and Markdown editions of the same lesson count as two resources. The course list counts lessons, so a course with 152 lessons can exceed the resource limit when both editions are placed in one manifest.

Load learning-packs/umicom-development-manuscripts.json for the Framework manuscripts, learning-packs/llm-from-scratch-manuscripts.json for the LLM manuscripts, or learning-packs/umicom-kernel-from-scratch-manuscripts.json for the Kernel manuscripts. Each companion begins with an index linking its declared Markdown resources. Keep the complete checkout as the library root.

A link to the other edition may lie outside the selected pack and be refused by the native reader. Select the other manifest explicitly or use the browser presentation. Loading a companion uses another shelf slot; the shelf supports at most 32 packs.

Existing checkpoints remain recorded against their original pack, revision and resource identities. A moved manuscript keeps its resource ID, but this does not migrate its previous checkpoint to the companion pack. Review earlier records separately; no completion is inferred from the move.

After integration, verify the selected course and its companion manifest with the existing learning-pack verify command, substituting its path. Then qualify catalogue load, lesson navigation, Back/Forward and checkpoint history. Manifest restructuring and source checks alone do not establish these runtime results.

## Verify files from a terminal

After the native umicom command has been built, this command checks every file in one pack without running the lesson examples:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
& ".\build\windows-ucrt64-all-debug\bin\umicom.exe" learning-pack verify "C:\umicom\Umicom-Bits2Banking" "learning-packs/learning-cmake.json" 0.9.0
```

The final argument is the learning-host compatibility version, not a compiler version. These manifests describe host 0.9.0. Use the version supported by the installed reader and do not change this number to suppress a compatibility failure.

## Update a course pack deliberately

A course edit changes its checksum. Review the edited lessons first, then use the Framework-backed authoring command to prepare a new revision at a new filename:

```powershell
& "C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin\umicom.exe" learning-pack prepare "C:\umicom\Umicom-Bits2Banking" "learning-packs/learning-cmake.json" "learning-packs/learning-cmake-reviewed.json" 0.9.0
```

The destination must not already exist. Keep the old manifest for comparison. Verify the new file, then use the catalogue's replacement review before accepting it. A revision is a reviewed content change, not an excuse to trust an unexpected file. Preparing a manifest reads current files; it is not a snapshot of a folder that another program is changing.

## Troubleshooting

- **File not found:** confirm the library folder contains content and learning-packs. Do not use content/courses as the root for these manifests.
- **Checksum mismatch:** compare the file with the reviewed source. Git is configured to keep HTML and Markdown with LF line endings so an ordinary Windows checkout preserves the manifest bytes. Do not disable verification to hide a content difference.
- **Manifest too large or too many resources:** the Framework bounds one pack to 256 resources and 256 KiB of manifest text. Separate a larger curriculum into several packs.
- **A lesson opens but an example does not run:** reading a resource never executes it. Follow that lesson's build and run steps in a development workspace.
- **A remembered course opens the wrong revision:** reopen its exact root and manifest path, inspect the replacement review and then choose the new course entry.

<!-- Earlier catalogue count retained for review: | LLM from Scratch | `learning-packs/llm-from-scratch.json` | 125 | -->
<!-- Earlier catalogue count retained for review: | Learning Umicom Framework | `learning-packs/umicom-development.json` | 94 | -->

## Course manifest paths

| Course | Manifest path | Lessons |
| --- | --- | --- |
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 128 |
| Building a Text Editor in C | `learning-packs/building-a-text-editor.json` | 14 |
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 59 |
| Building Bitcoin from Scratch Using Assembly and C | `learning-packs/building-bitcoin-in-c.json` | 3 |
| Building Blockchain from Scratch | `learning-packs/building-blockchain-from-scratch.json` | 13 |
| Building Linux from Scratch Using C Code | `learning-packs/building-linux-from-scratch.json` | 3 |
| Learning C: For beginners | `learning-packs/c-from-the-beginning.json` | 11 |
| Introduction to Computers | `learning-packs/computing-from-the-beginning.json` | 8 |
| Introduction to Distributed Learning, Blockchain and Verifiable AI | `learning-packs/distributed-learning.json` | 95 |
| Financial Instruments Pricing Using C, C++ and Java | `learning-packs/financial-instruments-pricing.json` | 4 |
| Learning Accounting and Financial Controls | `learning-packs/framework-and-finance-accounting-and-control.json` | 2 |
| Introduction to Banking and Payments | `learning-packs/framework-and-finance-banking-and-payments.json` | 25 |
| Learning Build and Runtime Diagnostics | `learning-packs/framework-and-finance-builds-and-diagnostics.json` | 2 |
| Introduction to Commodity and Digital-Asset Systems | `learning-packs/framework-and-finance-commodities-and-digital-assets.json` | 2 |
| Learning Data and Messaging Services | `learning-packs/framework-and-finance-data-and-messaging.json` | 2 |
| Learning Financial-System Integration | `learning-packs/framework-and-finance-financial-integration.json` | 2 |
| Introduction to Umicom Framework Architecture | `learning-packs/framework-and-finance-framework-boundaries.json` | 2 |
| Introduction to Native AI and Retrieval | `learning-packs/framework-and-finance-native-ai-and-learning.json` | 2 |
| Introduction to Secure Connected Services | `learning-packs/framework-and-finance-secure-connected-services.json` | 2 |
| Learning Studio Documents and Visual Design | `learning-packs/framework-and-finance-studio-workflows.json` | 3 |
| Introduction to Trading and Post-Trade Systems | `learning-packs/framework-and-finance-trading-and-posttrade.json` | 33 |
| Introduction to Treasury Management Systems | `learning-packs/framework-and-finance-treasury-operations.json` | 2 |
| Introduction to Bitcoin | `learning-packs/introduction-to-bitcoin.json` | 3 |
| Introduction to Bitcoin Source Code | `learning-packs/introduction-to-bitcoin-source-code.json` | 3 |
| Introduction to Blockchain | `learning-packs/introduction-to-blockchain.json` | 3 |
| Introduction to Calypso API Development | `learning-packs/introduction-to-calypso-api-development.json` | 11 |
| Introduction to Operating Systems | `learning-packs/introduction-to-operating-systems.json` | 12 |
| Introduction to Programming | `learning-packs/introduction-to-programming.json` | 16 |
| Introduction to Treasury Management Systems | `learning-packs/introduction-to-treasury-management-systems.json` | 25 |
| Introduction to Version Control | `learning-packs/introduction-to-version-control.json` | 5 |
| Learning Motorola 6800 Assembly | `learning-packs/learning-6800-assembly.json` | 2 |
| Learning Motorola 68000 Assembly | `learning-packs/learning-68000-assembly.json` | 4 |
| Learning Algorithms | `learning-packs/learning-algorithms.json` | 9 |
| Android Development | `learning-packs/learning-android.json` | 18 |
| Learning Bootstrap | `learning-packs/learning-bootstrap.json` | 2 |
| Learning C | `learning-packs/learning-c.json` | 33 |
| Learning CMake | `learning-packs/learning-cmake.json` | 12 |
| Learning CodeIgniter | `learning-packs/learning-codeigniter.json` | 2 |
| Introduction to Computers | `learning-packs/learning-computer-architecture.json` | 8 |
| Learning C++ | `learning-packs/learning-cpp.json` | 6 |
| Learning CSS | `learning-packs/learning-css.json` | 8 |
| Learning Cyber Security | `learning-packs/learning-cyber-security.json` | 24 |
| Learning D Language | `learning-packs/learning-d.json` | 59 |
| Learning Data Structures | `learning-packs/learning-data-structures.json` | 25 |
| Learning Flutter | `learning-packs/learning-flutter.json` | 20 |
| Learning GTK4 | `learning-packs/learning-gtk4.json` | 26 |
| Learning HDL and VHDL | `learning-packs/learning-hdl-vhdl.json` | 50 |
| Learning HTML | `learning-packs/learning-html.json` | 16 |
| Learning iPhone Development | `learning-packs/learning-iphone-development.json` | 18 |
| Learning Java | `learning-packs/learning-java.json` | 10 |
| Learning JavaScript | `learning-packs/learning-javascript.json` | 10 |
| Learning Kotlin | `learning-packs/learning-kotlin.json` | 12 |
| Learning Laravel | `learning-packs/learning-laravel.json` | 2 |
| Learning Linux Development | `learning-packs/learning-linux-development.json` | 3 |
| Learning NoSQL and MongoDB | `learning-packs/learning-nosql.json` | 8 |
| Learning Pascal | `learning-packs/learning-pascal.json` | 13 |
| Learning PHP | `learning-packs/learning-php.json` | 12 |
| Learning Pine Script | `learning-packs/learning-pinescript.json` | 2 |
| Learning Python | `learning-packs/learning-python.json` | 11 |
| Learning Qt | `learning-packs/learning-qt.json` | 24 |
| Learning RabbitMQ and Message Queues | `learning-packs/learning-rabbitmq.json` | 13 |
| Learning React | `learning-packs/learning-react.json` | 2 |
| Introduction to RISC-V | `learning-packs/learning-riscv.json` | 20 |
| Learning RISC-V Assembly | `learning-packs/learning-riscv-assembly.json` | 21 |
| Learning Rust | `learning-packs/learning-rust.json` | 6 |
| Learning Spring Framework | `learning-packs/learning-spring-framework.json` | 2 |
| Learning SQL | `learning-packs/learning-sql.json` | 14 |
| Learning Wt | `learning-packs/learning-wt.json` | 16 |
| Learning x86 Assembly | `learning-packs/learning-x86-assembly.json` | 9 |
| Learning Zend Framework | `learning-packs/learning-zend-framework.json` | 2 |
| Learning Zig | `learning-packs/learning-zig.json` | 6 |
| LLM from Scratch | `learning-packs/llm-from-scratch.json` | 144 |
| LLM from Scratch — Markdown manuscripts | `learning-packs/llm-from-scratch-manuscripts.json` | 144 |
| Safer C Programming | `learning-packs/safer-c-programming.json` | 43 |
| Learning Umicom Framework | `learning-packs/umicom-development.json` | 208 |
| Learning Umicom Framework — Markdown manuscripts | `learning-packs/umicom-development-manuscripts.json` | 208 |
| Umicom Kernel from Scratch | `learning-packs/umicom-kernel-from-scratch.json` | 146 |
| Umicom OS from Scratch | `learning-packs/umicom-os-from-scratch.json` | 73 |
| Learning Build Systems | `learning-packs/learning-build-systems.json` | 32 |
<!-- Earlier count retained. Inactive mapping and ELF evidence add two lessons.
| Multikernel systems and workload isolation | `learning-packs/multikernel-systems.json` | 9 |
-->
| Multikernel systems and workload isolation | `learning-packs/multikernel-systems.json` | 11 |
| MINIX OS Foundations | `learning-packs/minix-os-foundations.json` | 12 |
| Learning Maven | `learning-packs/learning-maven.json` | 4 |
| Learning Gradle | `learning-packs/learning-gradle.json` | 4 |
| Learning XML | `learning-packs/learning-xml.json` | 4 |
| Build a weight-management companion with Umicom Framework | `learning-packs/weight-management-framework.json` | 9 |
| Generative AI: Image and Video Training Foundations | `learning-packs/generative-ai-foundations.json` | 32 |
| Learning FreeBASIC | `learning-packs/learning-freebasic.json` | 45 |
| Native languages through C and assembly | `learning-packs/native-language-interoperability.json` | 12 |
| Preparing Data for LLM Training | `learning-packs/preparing-llm-training-data.json` | 34 |
| Umicom Kernel from Scratch — Markdown manuscripts | `learning-packs/umicom-kernel-from-scratch-manuscripts.json` | 146 |
| Accessible Statement Review | `learning-packs/accessible-statement-review.json` | 2 |
| AngularJS and Legacy Statement Screens | `learning-packs/angularjs-legacy-statements.json` | 3 |
| Banking Technology Foundations | `learning-packs/banking-technology-foundations.json` | 4 |
| Bookkeeping from Your First Entry | `learning-packs/bookkeeping-from-first-entry.json` | 4 |
| Bootstrap and Native Statement Reports | `learning-packs/bootstrap-native-statements.json` | 3 |
| Build a Banking Application in C | `learning-packs/build-a-bank-application-in-c.json` | 5 |
| Build a Trading Application in C | `learning-packs/build-a-trading-application-in-c.json` | 5 |
<!-- Prior count retained for review. The C23 lab adds three lessons.
| C23 Keywords for Beginners | `learning-packs/c23-keyword-reference.json` | 7 |
-->
| C23 Keywords for Beginners | `learning-packs/c23-keyword-reference.json` | 10 |
| C++20 Keyword and Token Reference | `learning-packs/cpp20-keyword-reference.json` | 8 |
| D Keywords for Beginners | `learning-packs/d-keyword-reference.json` | 8 |
| D Special Tokens for Beginners | `learning-packs/d-special-token-reference.json` | 4 |
| First C# Statements | `learning-packs/first-csharp-statements.json` | 4 |
| FpML for Treasury and Trade Confirmation | `learning-packs/fpml-for-treasury.json` | 3 |
| Go Keywords for Beginners | `learning-packs/go-keyword-reference.json` | 4 |
| Go Statement Tools | `learning-packs/go-statement-tools.json` | 2 |
| Java SE 25 keyword reference | `learning-packs/java-keyword-reference.json` | 7 |
| Mathematics for Application Builders | `learning-packs/mathematics-for-application-builders.json` | 7 |
| MongoDB Receipt Documents in C23 | `learning-packs/mongodb-c23-documents.json` | 3 |
| MySQL Ledger Practice in C23 | `learning-packs/mysql-c23-ledger.json` | 3 |
| Native Statement Calculations | `learning-packs/native-statement-calculations.json` | 2 |
| Node.js and Native Statement Reports | `learning-packs/nodejs-native-reporting.json` | 3 |
| UK Open Banking Account Access | `learning-packs/open-banking-account-access.json` | 3 |
| Oracle Database Ledger Practice in C23 | `learning-packs/oracle-database-c23-ledger.json` | 3 |
| Practical Web and Data Foundations | `learning-packs/practical-web-and-data-foundations.json` | 6 |
| Pricing Financial Instruments from Cash Flows | `learning-packs/pricing-from-cashflows.json` | 5 |
| Automated Testing with Umicom Framework | `learning-packs/automated-testing-with-umicom.json` | 18 |
| Programming across languages | `learning-packs/programming-across-languages.json` | 9 |
| Python 3.14 keyword reference | `learning-packs/python-keyword-reference.json` | 8 |
| RabbitMQ Outbox Practice in C23 | `learning-packs/rabbitmq-c23-outbox.json` | 3 |
| React and Native Statement Data | `learning-packs/react-native-statements.json` | 3 |
| Rust 2024 Keywords for Beginners | `learning-packs/rust-keyword-reference.json` | 7 |
| Spring Boot with a Native C23 Service | `learning-packs/spring-boot-native-service.json` | 3 |
| Spring Framework with a Native C23 Receipt Rule | `learning-packs/spring-framework-with-c23.json` | 3 |
| SQL Statement Reconciliation | `learning-packs/sql-statement-reconciliation.json` | 2 |
| Swift Payment Messages and ISO 20022 | `learning-packs/swift-payment-messages.json` | 3 |
| Umicom C checked integer keywords and syntax | `learning-packs/umicom-c-keyword-reference.json` | 5 |

<!-- Previous rows retained for review. The active table follows current course metadata.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 94 |
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 42 |
| Learning Cyber Security | `learning-packs/learning-cyber-security.json` | 21 |
| Learning PHP | `learning-packs/learning-php.json` | 3 |
| Learning RISC-V Assembly | `learning-packs/learning-riscv-assembly.json` | 16 |
| Learning x86 Assembly | `learning-packs/learning-x86-assembly.json` | 4 |
| Umicom Kernel from Scratch | `learning-packs/umicom-kernel-from-scratch.json` | 129 |
| Umicom OS from Scratch | `learning-packs/umicom-os-from-scratch.json` | 64 |
| Learning Build Systems | `learning-packs/learning-build-systems.json` | 26 |
| Multikernel systems and workload isolation | `learning-packs/multikernel-systems.json` | 6 |
| Umicom Kernel from Scratch — Markdown manuscripts | `learning-packs/umicom-kernel-from-scratch-manuscripts.json` | 129 |
-->
<!-- Previous catalogue row retained after course continuation: | Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 46 | -->
<!-- Earlier displayed compiler course count was64; the current course sequence has82 entries. -->
<!-- Prior catalogue row retained: | Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 82 | -->
<!-- Prior catalogue row retained: | Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 83 | -->
<!-- Prior catalogue row retained: | Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 84 | -->
<!-- Prior catalogue row retained: compiler course had 85 lessons before checked shifts. -->
<!-- Previous count retained: 12 D lessons before the reflection sequence. -->
<!-- Previous D table count was24 before field metadata. -->
<!-- Previous D table count was25 before compile-time type admission. -->
<!-- Previous catalogue row retained after course continuation: | Learning HTML | `learning-packs/learning-html.json` | 10 | -->
<!-- Previous course count retained for review; eight model lessons extend this course.
| Learning Qt | `learning-packs/learning-qt.json` | 16 |
-->
<!-- Prior catalogue row retained: | Safer C Programming | `learning-packs/safer-c-programming.json` | 41 | -->
<!-- Previous catalogue row retained after course continuation: | Umicom Kernel from Scratch | `learning-packs/umicom-kernel-from-scratch.json` | 94 | -->
<!-- Previous catalogue row retained: 109 lessons before UDP admission. -->
<!-- Previous displayed Kernel count was112; current manifest includes the continued VM and networking sequence. -->
<!-- Prior count retained: | Learning Build Systems | `learning-packs/learning-build-systems.json` | 24 | -->

<!-- The previous OS course count is kept for review. The active table includes the new dependency diagnostic lesson.
| Umicom OS from Scratch | `learning-packs/umicom-os-from-scratch.json` | 68 |
-->

<!-- Earlier count retained. The observed-edit lesson extends Learning SQL by one lesson.
| Learning SQL | `learning-packs/learning-sql.json` | 13 |
-->

<!-- Earlier count retained. The native snapshot lessons extend Learning SQL by two lessons.
| Learning SQL | `learning-packs/learning-sql.json` | 11 |
-->

## Keep native packs stable during website publication

A native pack names exact file bytes. Website tools must not insert a logo or rewrite a link in those files after their checksums have been reviewed. The source-link and branding hooks share `hooks/publication_artifacts.py` to identify native payloads before either hook changes generated pages. Invalid, missing or linked payload paths stop publication before page rewriting begins. This is publication admission, not a replacement for Framework pack verification.

1. Author native page branding in the source HTML. Reuse the approved wordmark SVG, SVG icon, ICO favicon and shared `content/assets/branding/umicom-brand.css` stylesheet. The stylesheet selects installed font families; it does not distribute or download font files.
2. Keep the existing page structure, text and navigation. For an adaptive page, use the approved light and dark wordmark variants without redrawing either asset.
3. Use a published repository URL for a source file outside the website's `content` folder. A local link can work in a checkout while failing on the website. Repository links require network access; the corresponding local files remain available in the complete checkout.
4. Refresh every manifest that owns a changed source file. The introductory Framework and finance pack and the longer subject packs can reference the same page. Review and verify each affected pack using the native commands above.
5. Run the source-link and branding checks before building the site:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
python -m unittest discover -s tests -p "test_course_source_links.py" -v
python -m unittest discover -s tests -p "test_umicom_branding.py" -v
python -m mkdocs build --strict
```

Run each command separately and stop on an error. These are qualification instructions, not a claim that the checks have passed. The combined regression covers link rewriting followed by branding: native payloads and their manifest stay byte-for-byte unchanged, while ordinary generated pages receive the shared artwork. The hooks do not recalculate a checksum to conceal an unexpected generated change.

If a pack is refused, inspect the reported manifest and path. Restore the reviewed source or deliberately author a new revision; do not disable the check or redirect a resource through a symbolic link. Keep the full checkout together when reading locally. The native reader supplies its own application branding and does not promise browser CSS or image rendering.

<!-- Earlier course count retained for review; the active table includes the toolchain-selection lessons.
| Learning Build Systems | `learning-packs/learning-build-systems.json` | 17 |
-->

<!-- Previous trading course row retained for review after course expansion:
| Introduction to Trading and Post-Trade Systems | `learning-packs/framework-and-finance-trading-and-posttrade.json` | 10 |
The active table reflects all thirty-three declared lessons. -->

## Native languages through C and assembly

Select learning-packs/native-language-interoperability.json with the complete Bits2Banking checkout as the library root. It contains the twelve-lesson shared ABI course, three two-lesson language introductions and the complete lab sources. Existing C, C++, Rust, Zig and D courses remain available separately. Optional compilers and installed-SDK examples require their own qualification.

## Native language and model-training foundations

<!-- Previous FreeBASIC sequence contained 16 lessons; retained as revision history. -->
<!-- Previous FreeBASIC count was17 before comment-boundary practice. -->
<!-- Earlier course index retained: - Learning FreeBASIC: [learning-freebasic.json](learning-freebasic.json), 24 lessons. -->
<!-- Earlier count retained for review: - Learning FreeBASIC: [learning-freebasic.json](learning-freebasic.json), 25 lessons. -->
<!-- Prior FreeBASIC count retained: 26 before overload practice. -->
- Learning FreeBASIC: [learning-freebasic.json](learning-freebasic.json), 45 lessons.
<!-- Previous data-preparation count was14 before selected JSONL export. -->
<!-- Earlier published index count retained for review: - Preparing Data for LLM Training: [preparing-llm-training-data.json](preparing-llm-training-data.json), 20 lessons. -->
<!-- Earlier count retained for review: - Preparing Data for LLM Training: [preparing-llm-training-data.json](preparing-llm-training-data.json), 22 lessons. -->
<!-- Earlier sequence length retained for review: 23 lessons before selected microbatch reduction. -->
- Preparing Data for LLM Training: [preparing-llm-training-data.json](preparing-llm-training-data.json), 34 lessons.
<!-- Previous generative sequence contained 12 lessons before cumulative coefficients. -->
<!-- Prior generative count: 17 before continuous objective weighting. -->
- Generative AI: Image and Video Training Foundations: [generative-ai-foundations.json](generative-ai-foundations.json), 32 lessons and native C objective/noise/schedule/guidance/trajectory/prediction-conversion/padded-frame/weighted-objective labs.

<!-- Earlier course index retained: - Learning D: [learning-d.json](learning-d.json), 30 lessons including runtime type inspection, callbacks, field metadata, compile-time admission and explicit range validation. -->
<!-- Earlier count retained for review: - Learning D: [learning-d.json](learning-d.json), 31 lessons including runtime type inspection, callbacks, field metadata, compile-time admission, explicit range validation and input-range ownership. -->
<!-- Prior D count retained: 32 before explicit enum admission. -->
- Learning D: [learning-d.json](learning-d.json), 51 lessons including runtime type inspection, callbacks, field metadata, compile-time admission, explicit range validation and input-range ownership.

## Connected programming, mathematics and project courses

Start with the [learning pathways](../content/start/connected-learning.md). Open one pack at a time in the desktop reader. If a link points into another course, load that course’s pack separately or follow the link in the browser edition.

| Course | Manifest |
| --- | --- |
| Programming across languages | [programming-across-languages.json](programming-across-languages.json) |
| Umicom C checked integer keywords and syntax | [umicom-c-keyword-reference.json](umicom-c-keyword-reference.json) |
| C23 Keywords for Beginners | [c23-keyword-reference.json](c23-keyword-reference.json) |
| C++20 Keyword and Token Reference | [cpp20-keyword-reference.json](cpp20-keyword-reference.json) |
| Go Keywords for Beginners | [go-keyword-reference.json](go-keyword-reference.json) |
| Python 3.14 keyword reference | [python-keyword-reference.json](python-keyword-reference.json) |
| Java SE 25 keyword reference | [java-keyword-reference.json](java-keyword-reference.json) |
| D Keywords for Beginners | [d-keyword-reference.json](d-keyword-reference.json) |
| D Special Tokens for Beginners | [d-special-token-reference.json](d-special-token-reference.json) |
| First C# Statements | [first-csharp-statements.json](first-csharp-statements.json) |
| Mathematics for Application Builders | [mathematics-for-application-builders.json](mathematics-for-application-builders.json) |
| Bookkeeping from Your First Entry | [bookkeeping-from-first-entry.json](bookkeeping-from-first-entry.json) |
| Pricing Financial Instruments from Cash Flows | [pricing-from-cashflows.json](pricing-from-cashflows.json) |
| Practical Web and Data Foundations | [practical-web-and-data-foundations.json](practical-web-and-data-foundations.json) |

## Applied native courses

Start with the [applied course guide](../content/start/applied-native-courses.md). Choose one offline pack and follow its lesson order. Use the linked browser editions when moving between courses.

| Course | Manifest |
| --- | --- |
| React and Native Statement Data | [react-native-statements.json](react-native-statements.json) |
| Node.js and Native Statement Reports | [nodejs-native-reporting.json](nodejs-native-reporting.json) |
| AngularJS and Legacy Statement Screens | [angularjs-legacy-statements.json](angularjs-legacy-statements.json) |
| Bootstrap and Native Statement Reports | [bootstrap-native-statements.json](bootstrap-native-statements.json) |
| Spring Framework with a Native C23 Receipt Rule | [spring-framework-with-c23.json](spring-framework-with-c23.json) |
| Spring Boot with a Native C23 Service | [spring-boot-native-service.json](spring-boot-native-service.json) |
| MySQL Ledger Practice in C23 | [mysql-c23-ledger.json](mysql-c23-ledger.json) |
| Oracle Database Ledger Practice in C23 | [oracle-database-c23-ledger.json](oracle-database-c23-ledger.json) |
| MongoDB Receipt Documents in C23 | [mongodb-c23-documents.json](mongodb-c23-documents.json) |
| RabbitMQ Outbox Practice in C23 | [rabbitmq-c23-outbox.json](rabbitmq-c23-outbox.json) |
| Banking Technology Foundations | [banking-technology-foundations.json](banking-technology-foundations.json) |
| Build a Banking Application in C | [build-a-bank-application-in-c.json](build-a-bank-application-in-c.json) |
| UK Open Banking Account Access | [open-banking-account-access.json](open-banking-account-access.json) |
| Swift Payment Messages and ISO 20022 | [swift-payment-messages.json](swift-payment-messages.json) |
| FpML for Treasury and Trade Confirmation | [fpml-for-treasury.json](fpml-for-treasury.json) |
| Build a Trading Application in C | [build-a-trading-application-in-c.json](build-a-trading-application-in-c.json) |

<!-- The previous course count is retained for review after adding two ABI exercises.
| Programming across languages | `learning-packs/programming-across-languages.json` | 7 |
-->

<!-- The previous count is retained for review. The counted progress lesson increases the catalogue to 28.
| Learning Build Systems | `learning-packs/learning-build-systems.json` | 27 |
-->

<!-- The previous count is retained for review after adding the common-radix lesson.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 104 |
-->

<!-- The previous count is retained for review after adding the local-update lesson.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 105 |
-->

<!-- The previous count is retained for review after adding the reached-statement lesson.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 106 |
-->

<!-- Retain the earlier lesson count after adding exact saved result selection.
| Automated Testing with Umicom Framework | `learning-packs/automated-testing-with-umicom.json` | 6 |
-->

<!-- The previous count is retained for review after adding the C and D lesson.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 107 |
-->

<!-- The previous count remains for review. The link-rule lesson brings the total to 29.
| Learning Build Systems | `learning-packs/learning-build-systems.json` | 28 |
-->

<!-- Keep the preceding course count for review after adding the counters lesson.
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 45 |
-->

<!-- Retain the prior course count after adding the workflow summary lesson.
| Automated Testing with Umicom Framework | `learning-packs/automated-testing-with-umicom.json` | 7 |
-->

<!-- Retain the prior compiler course count after adding checked locals and paused slots.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 108 |
-->

<!-- Retain the earlier count after adding the running-log lesson.
| Automated Testing with Umicom Framework | `learning-packs/automated-testing-with-umicom.json` | 8 |
-->

<!-- Keep the preceding course count for review after adding the media type lesson.
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 46 |
-->

<!-- Keep the previous course count for review after adding the recipe-digest lesson.
| Learning Build Systems | `learning-packs/learning-build-systems.json` | 29 |
-->

<!-- Retain the prior compiler course count after adding checked shift translation.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 110 |
-->

<!-- Retain the earlier WebServer course count after adding the export-header lesson.
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 47 |
-->

<!-- Retain the earlier compiler course count after adding the digit-grouping exercise.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 111 |
-->

<!-- Retain the earlier count after adding the HTTP status exercise.
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 48 |
-->

<!-- Retain the earlier compiler course count after adding the signed-comparison exercise.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 112 |
-->

<!-- Retain the earlier count after adding the outer-run lesson.
| Automated Testing with Umicom Framework | `learning-packs/automated-testing-with-umicom.json` | 9 |
-->

<!-- Retain the earlier compiler course count after adding the slot-watch lesson.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 113 |
-->

<!-- Keep the previous course count after adding the temporary-volume lesson.
| Learning Build Systems | `learning-packs/learning-build-systems.json` | 30 |
-->

<!-- Retain the earlier compiler course count after adding the short-circuit lesson.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 114 |
-->

<!-- Retain the earlier Kernel course catalogue counts.
| Umicom Kernel from Scratch | `learning-packs/umicom-kernel-from-scratch.json` | 133 |
| Umicom Kernel from Scratch — Markdown manuscripts | `learning-packs/umicom-kernel-from-scratch-manuscripts.json` | 133 |
-->

<!-- Retain the earlier course count after adding the counted-body exercise.
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 49 |
-->

<!-- Retain the preceding course counts after adding these practice lessons.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 115 |
| Automated Testing with Umicom Framework | `learning-packs/automated-testing-with-umicom.json` | 10 |
| Learning Build Systems | `learning-packs/learning-build-systems.json` | 31 |
-->

<!-- Retain the earlier D course count after adding the report review module.
| Learning D Language | `learning-packs/learning-d.json` | 51 |
-->

<!-- Retain the previous OS course count after linking the new boot report lesson.
| Umicom OS from Scratch | `learning-packs/umicom-os-from-scratch.json` | 69 |
-->

<!-- Retain the earlier web server course count after adding three response lessons.
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 50 |
-->

<!-- Retain the earlier compiler course count after linking three fixed-name lessons.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 116 |
-->

<!-- Retain the earlier OS course count after adding two report publication lessons.
| Umicom OS from Scratch | `learning-packs/umicom-os-from-scratch.json` | 70 |
-->

<!-- Retain both earlier Kernel course counts after linking two transcript lessons.
| Umicom Kernel from Scratch | `learning-packs/umicom-kernel-from-scratch.json` | 134 |
| Umicom Kernel from Scratch — Markdown manuscripts | `learning-packs/umicom-kernel-from-scratch-manuscripts.json` | 134 |
-->

<!-- Retain the prior compiler course count after adding the signed-local lesson.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 119 |
-->

<!-- Retain the earlier compiler course count after adding script session practice.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 120 |
-->

<!-- Retain the earlier course count after adding the metadata exercise.
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 53 |
-->

<!-- Retain the earlier course count after linking the build and test evidence lessons.
| Automated Testing with Umicom Framework | `learning-packs/automated-testing-with-umicom.json` | 11 |
-->

<!-- Retain the earlier compiler course count after linking the Boolean-local lesson.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 121 |
-->

<!-- Retain the earlier Kernel counts before adding the saved-build lesson.
| Umicom Kernel from Scratch | `learning-packs/umicom-kernel-from-scratch.json` | 136 |
| Umicom Kernel from Scratch — Markdown manuscripts | `learning-packs/umicom-kernel-from-scratch-manuscripts.json` | 136 |
-->

<!-- Retain the earlier compiler lesson count after adding the Boolean literal size lesson.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 122 |
-->

<!-- Retain both earlier Kernel counts before adding the host evidence lesson.
| Umicom Kernel from Scratch | `learning-packs/umicom-kernel-from-scratch.json` | 137 |
| Umicom Kernel from Scratch — Markdown manuscripts | `learning-packs/umicom-kernel-from-scratch-manuscripts.json` | 137 |
-->

<!-- Retain the earlier Automated Testing course count after adding the console fixture lesson.
| Automated Testing with Umicom Framework | `learning-packs/automated-testing-with-umicom.json` | 14 |
-->

<!-- Retain both earlier Kernel pack counts for review after adding the finished artifact lesson.
| Umicom Kernel from Scratch | `learning-packs/umicom-kernel-from-scratch.json` | 138 |
| Umicom Kernel from Scratch — Markdown manuscripts | `learning-packs/umicom-kernel-from-scratch-manuscripts.json` | 138 |
-->

<!-- Retain the earlier Automated Testing pack count for review after adding the build path lesson.
| Automated Testing with Umicom Framework | `learning-packs/automated-testing-with-umicom.json` | 15 |
-->

<!-- Retain the earlier Web Server pack count for review after adding the named-event lesson.
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 54 |
-->

<!-- Retain the earlier Compiler pack count for review after the unsigned byte lesson.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 123 |
-->

<!-- Retain the earlier course count for review after adding the build storage lesson.
| Automated Testing with Umicom Framework | `learning-packs/automated-testing-with-umicom.json` | 16 |
-->

<!-- The earlier catalogue row counted 124 Compiler lessons. The active row includes the three typed console lessons. The preceding row stays here for review.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 124 |
-->

<!-- The earlier catalogue row counted 72 lessons. The active row includes the executable review lesson, and this earlier row remains for review.
| Umicom OS from Scratch | `learning-packs/umicom-os-from-scratch.json` | 72 |
-->

<!-- The previous row counted 55 lessons. The new total includes the managed FastCGI binding lesson. The earlier row remains for review.
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 55 |
-->

<!-- The earlier catalogue counted 127 lessons. The current row includes the signed cast exercise.
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 127 |
-->

<!-- The earlier catalogue counted 17 lessons before the execution outcome chapter.
| Automated Testing with Umicom Framework | `learning-packs/automated-testing-with-umicom.json` | 17 |
-->

<!-- Preserve the previous catalogue count. The active row now includes both device discovery lessons.
| Umicom Kernel from Scratch | `learning-packs/umicom-kernel-from-scratch.json` | 139 |
-->

<!-- Preserve the previous catalogue count. The active row now includes both device discovery lessons.
| Umicom Kernel from Scratch — Markdown manuscripts | `learning-packs/umicom-kernel-from-scratch-manuscripts.json` | 139 |
-->

<!-- Retain the earlier WebServer catalogue count after adding a compiled resource lesson.
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 56 |
-->

<!-- Retain the earlier WebServer count after linking worker HEAD lessons.
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 57 |
-->

<!-- Retain the earlier Kernel course count after adding permissions lessons.
| Umicom Kernel from Scratch | `learning-packs/umicom-kernel-from-scratch.json` | 141 |
-->

<!-- Retain the earlier Kernel course count after adding permissions lessons.
| Umicom Kernel from Scratch — Markdown manuscripts | `learning-packs/umicom-kernel-from-scratch-manuscripts.json` | 141 |
-->

<!-- Retain the earlier Kernel course count after adding optical evidence lessons.
| Umicom Kernel from Scratch | `learning-packs/umicom-kernel-from-scratch.json` | 143 |
-->

<!-- Retain the earlier Kernel course count after adding optical evidence lessons.
| Umicom Kernel from Scratch — Markdown manuscripts | `learning-packs/umicom-kernel-from-scratch-manuscripts.json` | 143 |
-->
