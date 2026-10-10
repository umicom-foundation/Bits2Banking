# What is a computer?

**Estimated video length:** 6–8 minutes  
**Related lesson:** [Inside a computer](../../lessons/01-computers/01-inside-a-computer.md)

## Opening — 0:00 to 0:45

**On screen:** A laptop, a phone, a desktop computer and a small server. The words *input*, *process*, *output* and *storage* appear one at a time.

**Narration:**

A computer can help you write a document, display a photograph, play music, manage a list of tasks or calculate how much money is available in an account. The tasks may appear very different, but the same basic idea is involved in all of them. A computer receives information, follows instructions, produces results and can store information for later use.

In this lesson, we are going to open up that process and look at the parts that make it possible. You do not need to know programming or electronics. By the end, you will be able to describe the most important hardware components and explain how a simple action, such as saving a note, travels through a computer.

## Hardware and software — 0:45 to 1:40

**On screen:** Label a keyboard, screen, CPU, memory and storage. Then show a note-taking application window.

**Narration:**

Start by separating two ideas: hardware and software. Hardware means the physical parts of a computer. You can touch a keyboard, connect a mouse, or replace a storage drive. Software means the instructions and related information that allow those physical components to carry out useful tasks.

Imagine writing a note. The note-taking application is software. The keyboard is an input device that lets you enter letters. The processor executes instructions that update the note in memory. The screen displays what you typed. When you press Save, the computer writes the information to storage so it can be opened again later.

The hardware does not need a different set of parts for each application. One computer can run a note-taking programme, a calculator, a development environment and a banking simulator because the same hardware can execute different sequences of instructions.

## The processor and memory — 1:40 to 3:00

**On screen:** Show the [computer hardware diagram](../../assets/diagrams/computer-hardware.svg). Highlight CPU, RAM and SSD in turn.

**Narration:**

The central processing unit, or CPU, executes instructions. It can add numbers, compare values, move data and make decisions based on the programme being run. Modern processors often contain several cores, which allow them to work on multiple streams of instructions.

The CPU needs fast access to the information it is using. Random-access memory, usually shortened to RAM, holds the current programme and working data. Think about a note that you are editing. The version visible in the editor may contain changes that you have not saved. Those changes are part of the computer's working state.

Storage is different. A solid-state drive, or SSD, keeps files when the computer is switched off. If you save the note, it can be stored on that drive and loaded again tomorrow. If you never save it, the changes may be lost when the application closes or the computer loses power.

Memory and storage are both essential, but they serve different purposes. Faster access often comes at the cost of less capacity. The computer uses several levels of storage, including small CPU caches, main memory and much larger persistent drives.

## The operating system — 3:00 to 4:05

**On screen:** Put a simple flow on screen: Person → Notes application → Operating system → Storage device.

**Narration:**

Applications do not normally control the storage drive or screen hardware directly. The operating system provides services that programmes can use. Windows, Linux and other operating systems manage processes, memory, files, devices and access permissions.

Return to the Save button. The note-taking application asks the operating system to save information to a file. The operating system checks the request, uses its filesystem and storage drivers, and reports whether the operation succeeded. If the file is protected, there may be an error. If the drive is full, there may also be an error. A well-designed application must show the problem rather than claiming that the document was saved.

This division of responsibilities is an important foundation for understanding operating systems and software architecture later in the course.

## Live demonstration — 4:05 to 5:25

**On screen:** Open Windows PowerShell, run the commands and highlight their output.

**Narration:**

We can ask the computer to describe itself. On Windows, open the Start menu, search for PowerShell and open it. PowerShell is a command-line programme. Instead of clicking a button, we type an instruction and the programme prints a result.

First, type `Get-CimInstance Win32_Processor` followed by Enter. The command asks Windows for information about its processor. You should see properties such as the CPU name and the number of cores. The exact values depend on your computer.

Next, type `Get-CimInstance Win32_ComputerSystem`. This command includes information about your computer model and installed physical memory. Finally, type `Get-CimInstance Win32_OperatingSystem` to inspect the operating system.

You do not have to memorise these commands. Notice how each one asks the system for information and returns a structured result. That is the same general request-and-response idea we will encounter later when applications communicate with services and databases.

## Closing exercise — 5:25 to 6:40

**On screen:** Return to the hardware diagram and show three questions.

**Narration:**

Before you continue, try explaining what happens when you open a note, type a sentence and press Save. Which part executes instructions? Where do your unsaved changes live? Which part keeps the saved file after the computer is switched off?

If you can answer those questions in your own words, you have the beginning of a useful mental model for the entire computer. Next, we will look at the bits and bytes that computers use to represent letters, numbers and instructions.

Continue with [Bits and digital logic](../../lessons/01-computers/02-bits-and-logic.md). You can find the written lesson, diagrams and exercises on the Bits to Banking website.
