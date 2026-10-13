# Episode 86 — A shared Framework change does not end at compilation

**Bits to Banking · Umicom Foundation · Presenter script**  
**Companion lessons:** Chapters 252–254 · **Format:** screen demonstration with narrated architecture diagram · **Estimated running time:** 10–13 minutes.

## Learning outcome and setup (0:00–1:30)

**On screen:** Open `content/assets/diagrams/change-impact-propagation-update36.svg`. Introduce three questions: What changed? Who depends on it? Which tests prove the consumers still work?

**Narration:** “A shared Framework library is useful because many applications can use the same tested implementation. It also creates a responsibility: a change to that library can affect code we did not edit. Today we will distinguish the Git commit, the CMake dependency, the runtime deployment and the parent repository's submodule reference. These are related, but they are not interchangeable.”

**Teaching note:** Explain that the illustrated modules are fictional training nodes, not automatically discovered live Umicom modules.

## Read-only Git evidence (1:30–4:00)

**On screen:** PowerShell in a clean `C:\umicom\Umicom-Applications` checkout. Do not modify files.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git rev-parse HEAD
git -C ".\framework" rev-parse HEAD
git status
git diff --submodule=log -- framework
```

**Narration:** “Two commits appear because the parent repository and its Framework submodule are separate repositories. Updating the Framework checkout does not rewrite the parent's recorded gitlink automatically. A clean status does not prove a build, and the parent SHA is not the Framework SHA.”

**Failure branch:** If the checkout is dirty, show `git status` only and stop. Never run destructive cleanup to make an educational recording appear tidy.

## Build a small dependency graph (4:00–8:00)

**On screen:** Open `labs/native/change-impact/impact_demo.c` and find the four calls to `BtbImpactAddModule`, the dependency edges, and the plan. Highlight the arrows from the consumer to the dependency and the reverse direction of potential impact.

**Narration:** “The base module changed. The VCS module depends on base, Studio depends on VCS and the OS desktop depends on base. The planner includes downstream consumers. This model has fixed storage and no Git parser — its job is to explain a policy decision, not to operate on the repository. For production, Umicom Framework already implements change planning through `UmiBuildAutomation`; use that existing service.”

Run the prebuilt demo only after showing its build from the README. Read out the affected modules and the mask of required gates.

## Review and close (8:00–13:00)

**On screen:** Show that the simulated first review lacks OS boot evidence. Contrast a successful native unit test with an independently observed QEMU boot or a GUI start by double-click.

**Narration:** “A green Framework build is encouraging but does not make an Umicom OS release ready. We must name the downstream evidence and show it was collected from the intended revision. If a gate was not run, record ‘not run’. If the relevant repo is dirty, preserve it before switching.”

**Audience task:** Draw one shared Framework module with two consumers, and specify a source-identification command and one required test per consumer. Submit the diagram and commands; no source changes required.

**Production boundary:** The episode never creates a production source-impact service or modifies Framework, Applications or OS.
