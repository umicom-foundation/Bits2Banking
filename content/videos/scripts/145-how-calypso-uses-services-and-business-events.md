# Episode 145 — Data, events and engines: how Calypso shares the work

*Bits to Banking · Treasury From Zero · Approximate duration: 9 minutes*

## Start with the problem (0:00–2:00)

**Narration:** “Imagine every department keeping a separate copy of every trade. One person changes the amount, but the settlement team still has the older number. The risk report and accounting records can now disagree. A financial platform needs clear ownership of authoritative information and a way to notify the right services when it changes.”

## The classic Calypso mental model (2:00–6:30)

**On screen:** A logical diagram: Client → Data Server → Authoritative information; approved change → Event Server → processing engines. Mark it clearly as a conceptual classic-platform view.

**Narration:** “The Data Server is the service gateway responsible for approved access to important trade and reference information. A user or custom application should not bypass the platform's business rules by editing core database tables directly.”

“The Event Server helps distribute notifications. When a trade reaches a relevant state, an event can tell other components that work is available. An Engine Server hosts processing engines that do jobs such as preparing transfers, messages or accounting results. The components are separate because the work has different lifetimes and reliability requirements.”

## What could go wrong? (6:30–9:00)

**Narration:** “Suppose a trade is saved but no settlement transfer is created. Is the Data Server running? Was an event expected and published? Did the correct engine receive it? Was the settlement instruction complete? A restart may hide the evidence, so we begin with identifiers, state and logs.”

“Your practice task is to draw the path of one trade from entry to settlement and write the evidence you would expect at each stage. You do not need a licensed Calypso system; the architecture picture is enough for today's exercise.”

*Calypso internals and exact API names vary by licensed release; this episode teaches core responsibilities.*
