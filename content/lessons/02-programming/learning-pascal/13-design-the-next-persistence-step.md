<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/13-design-the-next-persistence-step.md

PURPOSE:
Explain the lesson: Design saving before adding file writes.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Design saving before adding file writes

## Prepare
Run or read the course notebook demo using COURSE-BOOK.md. Its values exist only in memory. This lesson designs the next persistence step without pretending a file format has already been implemented.

Persistence means retaining data after the process ends.

## Specify a record
A saved course needs a name, total count and completed count. Decide how the file identifies its format version and how a reader detects an incomplete record.

A tab-separated text format is easy to inspect, but tabs and newlines inside names would need an escaping rule. The current name policy excludes them, which simplifies a first experiment.

## Plan a safe reader
1. Read into temporary candidate storage.
2. Validate the format and version.
3. Validate every name and progress count.
4. Reject duplicate names and more than eight courses.
5. Publish the candidate only when the entire file is accepted.

Expected: a malformed last row leaves the existing notebook untouched.

## Lab
Write three example files on paper: a valid two-course file, one with completed greater than total, and one truncated halfway through a row. Identify the check that rejects each invalid case.

## Plan a writer
A production save needs a clear policy for an existing destination and interrupted writes. Before implementing one, inspect Framework's existing document and atomic-storage services. Do not assume opening a destination for writing preserves its previous contents.

## Troubleshoot
A readable file is not automatically a valid notebook. Parsing, domain validation and publication are separate steps. Keep their error messages distinct so a learner can locate the failure without guessing.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/pascal-progress/COURSE-BOOK.md). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](12-check-each-course-independently.md)

