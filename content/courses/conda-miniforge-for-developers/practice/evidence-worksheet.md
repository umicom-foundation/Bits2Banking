<!--
Umicom Bits2Banking
File: content/courses/conda-miniforge-for-developers/practice/evidence-worksheet.md

PURPOSE:
Provide a blank learner record for actual environment observations.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Environment exercise evidence

Use this worksheet in a private practice folder. Do not put credentials, private package URLs or personal diagnostic logs in a public repository. Fill observed values only after running the commands; leave steps not run explicitly marked.

## Identity
- Date and operator:
- Operating system and architecture:
- PowerShell version and profile:
- Miniforge prefix and Conda version:
- Specification filename and SHA-256 (optional):
- Application revision, if an application is involved:

## Observations
| Step | Expected observation | Actual observation | Result: not run / pass / fail |
| --- | --- | --- | --- |
| Miniforge Prompt | Conda version and installation prefix | | not run |
| Fresh PowerShell | Conda resolves and runs | | not run |
| Capstone interpreter | Python 3.12 in the capstone prefix | | not run |
| Alternate interpreter | Python 3.11 in a different prefix | | not run |
| Version comparison | True | | not run |
| Pip metadata check | No incompatible declared requirements | | not run |
| Recreated environment | Separate prefix; comparison True | | not run |
| Native tool inventory afterwards | Project's supported native executable paths | | not run |

## Explain the result
1. Which observation proves interpreter selection more strongly than the prompt label?
2. Did the recreated packages exactly match? If not, which version constraints allowed the difference?
3. What failed first, if anything? Record that command and diagnostic before later errors.
4. What does this exercise leave untested? Include application, GPU, model and native build behaviour where relevant.

## Return to the course
Read [the capstone](../lessons/10-capstone-and-knowledge-check.html) and compare its completion criteria with this record. Environment removal is optional and is not part of the assessment.

