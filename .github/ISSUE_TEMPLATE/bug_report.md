@"
name: Bug report
description: Report a problem in a chapter, script, or build
labels: [bug]
body:
  - type: textarea
    id: what-happened
    attributes:
      label: What happened?
      description: What did you run, what did you expect, and what went wrong?
      placeholder: Clear steps to reproduce…
    validations:
      required: true
  - type: input
    id: os
    attributes:
      label: OS
      placeholder: Windows 11 / macOS 14 / Ubuntu 24.04
  - type: input
    id: python
    attributes:
      label: Python version
      placeholder: 3.11.x
  - type: textarea
    id: logs
    attributes:
      label: Logs / screenshots
      render: shell
"@ | Set-Content -Encoding utf8 "C:\Bits2Banking\.github\ISSUE_TEMPLATE\bug_report.md"

