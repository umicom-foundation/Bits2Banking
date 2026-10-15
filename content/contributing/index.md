# Contribute to Bits to Banking and Umicom

A useful contribution does not have to be complicated. Improving a link, adding an explanation or demonstrating a reproducible error can help many future learners.

## Find something to improve

Open the [Bits2Banking repository](https://github.com/umicom-foundation/Bits2Banking). Read a chapter and try its exercise. If a step is unclear or a command no longer works, note the problem and the result you expected.

## Contribute through GitHub

The [complete first pull request lesson](../lessons/05-engineering/17-first-pull-request.md) explains how to fork a repository, create a branch, make one edit, inspect the changes, push to GitHub and ask a maintainer to review the result.

## Work with a local copy

When you have Git installed, you can keep a checkout on your computer. The [Windows development setup](local-website.md) explains how to preview the lessons and check their internal links before sharing a change.

## Explore code contributions

Start with the [Umicom development lessons](../lessons/06-umicom/index.md). Read the source and tests alongside the explanations. The Framework, Kernel, OS and application repositories each maintain their own implementation contracts and build guides.

You can help someone else understand a topic you have learned. Sharing a clear explanation is as valuable as making a small code improvement.

## Teaching and assessment

The [teaching guides](../teaching/index.md) contain session plans, worked answers and assessment rubrics. Keep course instructions beside the published lessons or the laboratory they explain, so a reader can use them without access to a maintainer's working notes.

## Choose material for publication

Publish lessons, source examples, contributor instructions and diagrams that help readers understand or use the project. Keep original authorship and licence notices with that material.

Keep personal messages, raw support logs, private assessments, internal audits and delivery plans in a local directory outside the repository. Before sharing an error report, remove credentials and personal data and include only the information needed to reproduce the problem.

Edit the authored files under `content/` and source laboratories under `labs/native/`. Generated website and book files are not replacements for their editable sources. Framework APIs and build contracts belong in the Framework documentation; link to that source rather than duplicating private implementation files.

Before staging a contribution, run `git status`, inspect the proposed changes and follow the [website checks](local-website.md). Ignore rules help prevent accidental additions; they do not remove files already tracked by Git or erase older commits.
