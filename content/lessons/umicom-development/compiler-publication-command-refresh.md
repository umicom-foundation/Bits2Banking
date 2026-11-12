![Umicom](../../assets/branding/umicom-logo.svg)

# Refresh a stored command without losing its ownership

## A repeated source can have a new command

A compilation database gives tools a description of how a source is compiled. Editing a profile may change warnings, optimisation or the working directory while the source path stays the same. If a planner treats the existing database row as a harmless duplicate and ignores it, the returned plan can disagree with the record that other tools read. Both values may be individually well-formed while the combined workflow is wrong.



Read Refresh in the installed laboratory. It plans one source, changes the profile’s warnings-as-errors intent and plans the same source again. The observation checks that there is still one row, that both command owners contain the new option and that the stored directory is refreshed. It also verifies that the add-only API still reports a duplicate when called explicitly.



## Choose insertion or replacement deliberately

~~~c
/* Add-only clients retain duplicate refusal. */
UmiStatus added = umi_polyglot_compilation_database_add(database, &entry);
/* A client that intends replacement selects the separate operation. */
UmiStatus updated = umi_polyglot_compilation_database_upsert(database, &entry);
~~~



Upsert means insert when the key is absent and update when it is present. Here the key is the literal source string. It is not canonical filesystem identity, and this API does not merge several build configurations for one source. Keep separate databases when separate configurations must coexist. Check each status; the snippet illustrates the two contracts rather than a recommended sequence of unconditional calls.



## Copy strings and rebuild views

A plan owns inline argument strings and caches pointers into them. Copying the structure copies those pointers too, which can leave the receiving record referring to the caller’s array. Successful database publication rebases its views into the stored plan. The returned plan has its own rebased views. Mutating one owner’s strings must not change the other owner’s values.



Replacing a known source does not need a free slot, so it can succeed in a full database. It still consumes revision and is refused when that counter is exhausted. A new source at capacity is also refused. Every failure preserves the complete database; reading a stale row after a failed update must not be described as a successful refresh.



## Practice

Write a small state table with an absent source, an existing source, a full database and an exhausted revision. Predict add-only and upsert results for each combination. Then explain why a borrowed lookup pointer becomes unsafe after owner destruction or concurrent mutation even when its source key has not changed. Use the refresh scenario as evidence of ownership behavior, not as proof that an external language server accepted the database.



## Source and practice

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Compiler publication laboratory](../../../labs/native/framework-compiler-publication/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-publication-command-refresh.html)
-->
[Compiler publication laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-compiler-publication/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-publication-command-refresh.html)

[Previous lesson](compiler-publication-centre.md) · [Next lesson](compiler-publication-policy.md) · [Course index](index.md)

Sammy Hegab · Umicom Foundation · MIT
