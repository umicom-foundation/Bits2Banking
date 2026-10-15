# Episode 124 — Safe File Transfer and a Useful Incident Timeline

**Bits2Banking · Umicom Foundation · Target: 9–11 minutes**  
**Related chapters:** 81–83.

## Teaching objectives

Verify a harmless local copy, describe when SFTP is appropriate, and assemble a short support timeline that distinguishes known facts from unverified assumptions.

## Segment 1 — Copying is a controlled change

The instructor creates a fictional `notes-status.txt` under their own `UmicomLearning/transfer-practice` folder. First inspect the destination with `Test-Path`. Only when the new destination is empty, copy the file with `Copy-Item`. Compare its SHA-256 to the original using `Get-FileHash`.

**Narration:** “A matching digest checks the bytes. It does not tell us whether the owner authorised the transfer, whether a previous version needs retention or whether the file may be published.”

## Segment 2 — SFTP without risking a real server

Explain that SFTP runs through SSH and therefore inherits the need to verify host identity, account permissions and destination scope. Show only the command shape `sftp student@APPROVED_TRAINING_HOST`, visibly labelled as an unexecuted placeholder. No real upload is performed.

## Segment 3 — The Umicom Notes incident

Use [the evidence flow](../../assets/diagrams/sysadmin-remote-support-evidence-update43.svg). The support timeline observes a running process at 10:02, a successful local TCP connection at 10:03, a failing Notes operation at 10:04, and an unavailable storage dependency at 10:06. Have learners label each as a technical or business observation.

## Closing

Ask students to write the next authorised diagnostic action, the person who can approve it and whether personal data should be included. The correct report records uncertainty instead of inventing a cause.

**Viewer exercise:** Submit a five-row fictional timeline containing time, observation, evidence, uncertainty and next owner. Use invented names only.
