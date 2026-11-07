# Use Bits2Banking courses in Umicom Studio IDE

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

## Course manifest paths

| Course | Manifest path | Lessons |
| --- | --- | --- |
| Building a Compiler in C | `learning-packs/building-a-compiler-in-c.json` | 30 |
| Building a Text Editor in C | `learning-packs/building-a-text-editor.json` | 8 |
| Building a Web Server in C | `learning-packs/building-a-web-server-in-c.json` | 16 |
| Building Bitcoin from Scratch Using Assembly and C | `learning-packs/building-bitcoin-in-c.json` | 3 |
| Building Blockchain from Scratch | `learning-packs/building-blockchain-from-scratch.json` | 13 |
| Building Linux from Scratch Using C Code | `learning-packs/building-linux-from-scratch.json` | 3 |
| Learning C: For beginners | `learning-packs/c-from-the-beginning.json` | 11 |
| Introduction to Computers | `learning-packs/computing-from-the-beginning.json` | 8 |
| Introduction to Distributed Learning, Blockchain and Verifiable AI | `learning-packs/distributed-learning.json` | 95 |
| Financial Instruments Pricing Using C, C++ and Java | `learning-packs/financial-instruments-pricing.json` | 4 |
| Learning Accounting and Financial Controls | `learning-packs/framework-and-finance-accounting-and-control.json` | 2 |
| Introduction to Banking and Payments | `learning-packs/framework-and-finance-banking-and-payments.json` | 10 |
| Learning Build and Runtime Diagnostics | `learning-packs/framework-and-finance-builds-and-diagnostics.json` | 2 |
| Introduction to Commodity and Digital-Asset Systems | `learning-packs/framework-and-finance-commodities-and-digital-assets.json` | 2 |
| Learning Data and Messaging Services | `learning-packs/framework-and-finance-data-and-messaging.json` | 2 |
| Learning Financial-System Integration | `learning-packs/framework-and-finance-financial-integration.json` | 2 |
| Introduction to Umicom Framework Architecture | `learning-packs/framework-and-finance-framework-boundaries.json` | 2 |
| Introduction to Native AI and Retrieval | `learning-packs/framework-and-finance-native-ai-and-learning.json` | 2 |
| Introduction to Secure Connected Services | `learning-packs/framework-and-finance-secure-connected-services.json` | 2 |
| Learning Studio Documents and Visual Design | `learning-packs/framework-and-finance-studio-workflows.json` | 2 |
| Introduction to Trading and Post-Trade Systems | `learning-packs/framework-and-finance-trading-and-posttrade.json` | 10 |
| Introduction to Treasury Management Systems | `learning-packs/framework-and-finance-treasury-operations.json` | 2 |
| Introduction to Bitcoin | `learning-packs/introduction-to-bitcoin.json` | 3 |
| Introduction to Bitcoin Source Code | `learning-packs/introduction-to-bitcoin-source-code.json` | 3 |
| Introduction to Blockchain | `learning-packs/introduction-to-blockchain.json` | 3 |
| Introduction to Calypso API Development | `learning-packs/introduction-to-calypso-api-development.json` | 3 |
| Introduction to Operating Systems | `learning-packs/introduction-to-operating-systems.json` | 12 |
| Introduction to Programming | `learning-packs/introduction-to-programming.json` | 16 |
| Introduction to Treasury Management Systems | `learning-packs/introduction-to-treasury-management-systems.json` | 21 |
| Introduction to Version Control | `learning-packs/introduction-to-version-control.json` | 5 |
| Learning Motorola 6800 Assembly | `learning-packs/learning-6800-assembly.json` | 2 |
| Learning Motorola 68000 Assembly | `learning-packs/learning-68000-assembly.json` | 4 |
| Learning Algorithms | `learning-packs/learning-algorithms.json` | 9 |
| Android Development | `learning-packs/learning-android.json` | 10 |
| Learning Bootstrap | `learning-packs/learning-bootstrap.json` | 2 |
| Learning C | `learning-packs/learning-c.json` | 33 |
| Learning CMake | `learning-packs/learning-cmake.json` | 12 |
| Learning CodeIgniter | `learning-packs/learning-codeigniter.json` | 2 |
| Introduction to Computers | `learning-packs/learning-computer-architecture.json` | 8 |
| Learning C++ | `learning-packs/learning-cpp.json` | 6 |
| Learning CSS | `learning-packs/learning-css.json` | 8 |
| Learning Cyber Security | `learning-packs/learning-cyber-security.json` | 18 |
| Learning D Language | `learning-packs/learning-d.json` | 12 |
| Learning Data Structures | `learning-packs/learning-data-structures.json` | 25 |
| Learning Flutter | `learning-packs/learning-flutter.json` | 4 |
| Learning GTK4 | `learning-packs/learning-gtk4.json` | 11 |
| Learning HDL and VHDL | `learning-packs/learning-hdl-vhdl.json` | 42 |
| Learning HTML | `learning-packs/learning-html.json` | 10 |
| Learning iPhone Development | `learning-packs/learning-iphone-development.json` | 10 |
| Learning Java | `learning-packs/learning-java.json` | 8 |
| Learning JavaScript | `learning-packs/learning-javascript.json` | 10 |
| Learning Kotlin | `learning-packs/learning-kotlin.json` | 12 |
| Learning Laravel | `learning-packs/learning-laravel.json` | 2 |
| Learning Linux Development | `learning-packs/learning-linux-development.json` | 3 |
| Learning NoSQL and MongoDB | `learning-packs/learning-nosql.json` | 8 |
| Learning Pascal | `learning-packs/learning-pascal.json` | 13 |
| Learning PHP | `learning-packs/learning-php.json` | 3 |
| Learning Pine Script | `learning-packs/learning-pinescript.json` | 2 |
| Learning Python | `learning-packs/learning-python.json` | 11 |
| Learning Qt | `learning-packs/learning-qt.json` | 8 |
| Learning RabbitMQ and Message Queues | `learning-packs/learning-rabbitmq.json` | 8 |
| Learning React | `learning-packs/learning-react.json` | 2 |
| Introduction to RISC-V | `learning-packs/learning-riscv.json` | 20 |
| Learning RISC-V Assembly | `learning-packs/learning-riscv-assembly.json` | 16 |
| Learning Rust | `learning-packs/learning-rust.json` | 6 |
| Learning Spring Framework | `learning-packs/learning-spring-framework.json` | 2 |
| Learning SQL | `learning-packs/learning-sql.json` | 11 |
| Learning Wt | `learning-packs/learning-wt.json` | 8 |
| Learning x86 Assembly | `learning-packs/learning-x86-assembly.json` | 4 |
| Learning Zend Framework | `learning-packs/learning-zend-framework.json` | 2 |
| Learning Zig | `learning-packs/learning-zig.json` | 6 |
| LLM from Scratch | `learning-packs/llm-from-scratch.json` | 125 |
| Safer C Programming | `learning-packs/safer-c-programming.json` | 35 |
| Learning Umicom Framework | `learning-packs/umicom-development.json` | 94 |
| Umicom Kernel from Scratch | `learning-packs/umicom-kernel-from-scratch.json` | 74 |
| Umicom OS from Scratch | `learning-packs/umicom-os-from-scratch.json` | 18 |
| Learning Build Systems | `learning-packs/learning-build-systems.json` | 12 |
