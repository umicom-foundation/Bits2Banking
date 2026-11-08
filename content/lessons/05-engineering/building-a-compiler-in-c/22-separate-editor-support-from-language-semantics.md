<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/22-separate-editor-support-from-language-semantics.md

PURPOSE:
Separate editor support from language semantics

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate editor support from language semantics

A compiler reads a program and translates it into another representation. An IDE adds editing, project navigation and commands around that compiler. In this module, Umicom C accepts a deliberately small arithmetic language. Umicom Framework supplies the project recipe and Studio presents it. We follow the connection between those three responsibilities.

## Prepare the tools

1. Open PowerShell on Windows or a terminal running bash on Linux. A terminal accepts written commands; each command below starts an existing program.
2. Find your Umicom C executable. Run `umicom-c --version`. If it is not found, add its actual installation directory to PATH for this terminal or use its full path. PATH is the list of folders searched for program names.
3. Run `cmake --version` and `ninja --version`. CMake prepares a build description; Ninja follows that description. Install any missing tool through your platform's normal package manager.
4. Choose a practice destination, such as `C:\umicom\examples\arithmetic-preview`. The Studio starter requires a new folder: choose its parent first and do not create the final folder in advance.
5. In a Studio build containing the new Framework recipe, use **File → New Project**, choose **Umicom C Arithmetic Preview**, enter project details and the new destination, then create it. Generation creates text files only. It does not install dependencies or run the program.

The terminal exercises use that generated project independently of Studio's interface. See [Learning CMake](../../../courses/learning-cmake/index.html) for a longer introduction.

## Several integration points

Recognising a filename, colouring text, accepting a program and executing it are different operations. Studio uses Framework's language catalogue to recognise `.uc` without claiming a debugger, formatter or every C declaration.

1. Open the Umicom C language descriptor in Framework. Identify its identifier, extension, tools and advertised capabilities.
2. Follow document detection for `.uc`. It attaches a language identity to a document.
3. Follow the comment-style mapping. A line-comment command inserts `//`. Inserting comment syntax is editor behaviour; parsing belongs to the compiler.
4. Read the actual grammar in Umicom C before proposing a keyword. Write one accepted example and one rejected example first.
5. For a proposed feature, identify effects on tokens, parser, instruction representation, execution and tests. Explain which stages change and why.

## Plan a language extension

Suppose a learner asks for variables. A complete plan must answer how a name is declared, where its value lives, how references find it, what happens before assignment and how scopes end. Colouring a word as an identifier does not implement these rules. Start with a small written grammar and tests before advertising a capability in an IDE.

Keep compiler behaviour in Umicom C and shared editor/project integration in Framework. Studio calls those interfaces. The same project can then be used from a terminal and future applications can share the integration.

## Review exercise

Draw boxes for document detection, project recipe, compiler and interpreter. Trace a saved `main.uc` through **check** and **run**. Mark where syntax acceptance ends and runtime execution begins. Finally list unsupported features in the compiler you actually built. Honest limits make the course easier to follow and the integration easier to extend.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/developer_project/languages/umicom_c.c).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Previous: Test language failures through the tool](21-test-language-failures-through-the-tool.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Next lesson](23-inspect-a-program-before-running-it.md)

[Written course contents](index.md)
