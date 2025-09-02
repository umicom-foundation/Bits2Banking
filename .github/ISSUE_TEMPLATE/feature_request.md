@"
name: Feature request
description: Suggest a new chapter, example, or improvement
labels: [enhancement]
body:
  - type: textarea
    id: summary
    attributes:
      label: What would you like to add or improve?
      placeholder: Short description…
    validations:
      required: true
  - type: textarea
    id: details
    attributes:
      label: Any details, links, or examples?
  - type: dropdown
    id: area
    attributes:
      label: Area
      options:
        - Chapters
        - Scripts / Build
        - Diagrams
        - CI / Automation
        - Other
"@ | Set-Content -Encoding utf8 "C:\Bits2Banking\.github\ISSUE_TEMPLATE\feature_request.md"

