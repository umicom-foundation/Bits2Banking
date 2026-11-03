# Using the learning library

A lesson explains one subject. A course puts related lessons into a useful order. A book brings longer explanations together. A project lets you practise by changing a working example. You can use these different forms without studying every page in the library.

## 1. Choose where to begin

If files, folders and commands are unfamiliar, begin with [the learning sequence](learning-sequence.md). It starts with using a computer, then introduces small C programs. You do not need to know finance, artificial intelligence or operating-system internals first.

If you already understand the basics, choose a subject in the [course catalogue](../courses/index.html) or the [written course catalogue](written-courses.md). Read the prerequisites at its entrance. A prerequisite is something the lesson expects you to understand beforehand.

## 2. Stay within one course

Read its introduction, first lesson and worked example. Try the exercise before reading its answer. Follow the course's contents or Previous and Next links. Optional source studies are a choice after the foundations, not a compulsory jump into another subject.

The number in a file's name is a stable address. It can remain unchanged when the teaching order improves. Use the course contents for the current reading order.

## 3. Choose a reading format

- **Markdown**, a file ending in `.md`, is readable text with simple marks for headings, lists and code. It is useful for editing and reviewing a lesson in an IDE.
- **HTML**, a file ending in `.html`, is a browser page. It can show page layouts, diagrams and interactive illustrations.
- **Books and documents** group selected lessons into an edition. Their chapter numbers need not match the lesson folders.

The [media map](../../knowledge/registries/lesson-media.json) associates browser lessons with their manuscripts. Existing versions may contain different explanations or diagrams. Keep both when comparing them; an automatic conversion is not a substitute for checking the teaching content.

## 4. Use the subject folders

`content/lessons` groups written material by topic: computer basics, programming, native code, the web, engineering and specialist subjects. `content/courses` holds browser courses and their course descriptions. `content/books` is the book catalogue. `labs` holds practical code examples. `content/umicom` explains using and developing Umicom software.

For example, start [Learning C](../lessons/learning-c/index.md), then follow [Umicom Framework Development](../lessons/umicom-development/index.md). The [activity project](../umicom/development-path.md) connects the lesson to real source files, a console program, a window and tests.

## 5. Read lessons in Studio

Open Guided Learning or the local learning catalogue. A packaged content module can offer its course directly. Otherwise choose the folder containing its `learning-pack.json` and load it. A pack is a declared collection of lessons; not every course folder is already a pack.

The native reader displays supported structured text and local links. Use the browser edition for full HTML presentation. Keep your exercises in a folder you choose. Opening a lesson does not run its code, install a compiler or change a project.

If a course is absent from the native catalogue, use its browser or Markdown version. If a checksum fails, obtain a consistent pack; do not bypass its file checks. See the [content authoring guide](../contributing/learning-sources.md) when maintaining a course.
