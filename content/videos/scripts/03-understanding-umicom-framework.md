# Understanding Umicom Framework

**Estimated video length:** 8–10 minutes  
**Related lesson:** [Introducing Umicom Framework](../../lessons/06-umicom/23-introducing-umicom.md)

## Opening — 0:00 to 1:05

**On screen:** Show three applications: an editor, a charting screen and a financial dashboard. Highlight the parts they have in common.

**Narration:**

Think about three applications. One is a development environment used to edit and build code. Another displays trading charts and market data. A third shows an organisation's bank accounts, payments and cash forecasts. Their screens look different, but they still need many of the same capabilities: opening files, managing windows, handling configuration, recording messages and responding to failures.

If each application implements those capabilities separately, every product has another set of problems to maintain. Umicom Framework takes a different approach. It provides reusable components that applications can select and combine, while allowing each application to keep its own specialised behaviour.

In this lesson, we'll explore what a framework is, how a reusable component differs from an application feature, and how the Umicom projects are related.

## A framework is a shared foundation — 1:05 to 2:20

**On screen:** Display the [Umicom architecture diagram](../../assets/diagrams/umicom-architecture.svg) with Framework in the shared layer.

**Narration:**

A framework is a set of organised capabilities and contracts that help developers create applications without starting every project from nothing. In Umicom, these capabilities are primarily written in C23 and exposed through controlled interfaces. A contract describes how a component is called, what information it receives, what it returns and who owns its resources.

For example, saving a document should not require a separate storage system inside every programme. Umicom Studio needs to save source files, while a notes application needs to save notes. They can share reliable document and filesystem services, even though their user interfaces and workflows differ.

The goal is not to put all application logic into one library. Shared behaviour belongs in Framework; the specialised rules for a banking dashboard or a particular trading instrument belong with the product or a reusable domain module.

## Master and Slave Controllers — 2:20 to 3:40

**On screen:** A Master Controller delegates to several Slave Controllers: Documents, Windows, Tasks and Financial Operations.

**Narration:**

The original Umicom architecture introduced the terms Master Controller and Slave Controller. These terms describe responsibilities, not people. The Master Controller coordinates the application's life cycle: which modules are available, what must start first and what should happen when the application shuts down.

Each Slave Controller is responsible for a limited feature area. A document controller manages document operations. A task controller manages work items. A financial service controller may enforce a specific business process. The Master Controller does not have to know every detail of every document, task or bank account.

This division makes the code easier to understand and test. If a feature changes, developers can inspect the responsible module instead of searching through one enormous application file. Modules communicate through defined interfaces and typed messages rather than reaching directly into one another's private data.

## Commands, events and queries — 3:40 to 4:45

**On screen:** Three request cards: SaveDocument (command), DocumentSaved (event), GetDocumentStatus (query).

**Narration:**

A command asks a component to do something. A query asks for information without changing the state. An event records that something has already happened. These sound similar, but separating them helps us reason about a system's behaviour.

Imagine pressing Save in a notes application. The application issues a SaveDocument command. The document service checks the request and attempts to save the file. If the save succeeds, it can publish a DocumentSaved event. Another component might listen for that event and update a recent-files list. A query can then ask whether the document has unsaved changes.

Because each message has a purpose, a developer can trace what initiated a change and which components reacted to it. The same pattern becomes especially valuable when applications grow to include background tasks, financial transactions or distributed services.

## See the source — 4:45 to 6:25

**On screen:** Open the actual Umicom Framework GitHub repository and browse `include/umicom`, `src`, and `examples/framework_demo/main.c`.

**Narration:**

Let's connect the architecture to real source files. Open the Umicom Framework repository on GitHub. The `include/umicom` directory contains the public headers through which clients interact with Framework services. The `src` directory contains implementations. The `examples` directory contains applications and smaller exercises that show how components can be used.

Open `examples/framework_demo/main.c`. It is a compact example of the Master Controller and a registered Slave Controller. Look for the configuration structure, the module descriptor, the registration call and the start operation. You can see the component's identity, the capabilities it provides and the capabilities it requires.

The example also publishes an event when the sample module starts. Instead of explaining events only in a diagram, we can inspect where the event is created and how the programme starts and stops the runtime.

You do not need to memorise the whole file. Identify the entry point, find the public calls, and ask which code belongs to the reusable runtime and which belongs to the example application. That question will guide your understanding of the larger codebase.

## Framework, Kernel and OS — 6:25 to 7:35

**On screen:** Layers: Applications → Framework → System Services → Kernel.

**Narration:**

Umicom Framework is not the same as Umicom Kernel or Umicom OS. The Framework helps applications use reusable services. The operating system supplies process, file, memory and device services. The kernel is the privileged part of that system, responsible for fundamental mechanisms such as interrupts and memory protection.

The Umicom ecosystem includes a separate native Kernel research project as well as an OS project that explores complete system integration. Keeping these boundaries clear means a framework application does not need to implement its own scheduler or storage driver.

You can explore each project through its repository. Some capabilities are implemented and tested, while others are still being researched or developed. Read the current source and documentation rather than assuming that every architectural plan is already a finished feature.

## Closing exercise — 7:35 to 8:50

**On screen:** Open the Umicom notes learning example and show the files for model, session and window.

**Narration:**

Choose a real feature—such as saving a note—and sketch the components it needs. Which part owns the note data? Which part receives a Save command? Which reusable Framework service writes the file? How would the interface report an error?

Next, open `framework/examples/learning/projects` in Umicom Applications. Find `notes_model.c`, `notes_session.c` and `notes_window.c`. Compare their responsibilities with the diagram you drew. You can follow the build instructions in the [Framework application lesson](../../lessons/06-umicom/25-use-the-framework.md).

The more you understand the boundaries between components, the easier it becomes to improve a project without duplicating logic. As you learn, document what you discover and help someone else follow the same steps. That is how shared knowledge grows.
