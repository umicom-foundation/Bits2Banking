# Build a form from a shared document model

Understand editing, saving and visual components through the same Framework state model.

Lesson 2 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **component** is a reusable interface part, such as a text field or button. A visual designer lets you arrange components. Its picture is a **view** of a document model: the stored description of components, properties and relationships.

For a notes form, start with a window containing a title field, a notes field and a Save button. Give each component a stable identifier. The identifier connects selection, property editing, event binding and saved data. A displayed caption can change without changing that identity.

```text
document model
 ├─ component tree
 ├─ design canvas
 ├─ property inspector
 └─ generated or rendered application
```

If dragging the button changes only its drawn rectangle, saving and reopening may lose the change. The drag must become an edit of the model. An undo record describes how to reverse that edit. The component tree and property inspector then refresh from the same updated document.

A **declarative** description states what exists, rather than listing every low-level construction call. It still needs validation: a child must have a valid parent, an identifier must not collide, and a requested event handler must be supported. A picture of a button is not an implementation of saving.

## Design on paper

1. Write the four component identifiers: window, title, notes and save.
2. Draw their parent-child tree.
3. Change the button label to “Save note”; keep its identifier.
4. Describe the event: a user activates Save. Describe the command: save the current document. Describe the result: successful save or a specific failure.
5. Move the button and record both old and new positions so the edit can be undone.

Framework's designer document snapshot exposes component count, revision and dirty state. A **revision** is a state version. It lets a reader notice that its previous view may be stale. It is not a timestamp and does not automatically mean the state was persisted.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\designer\document.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiDesignerDocument UmiDesignerDocument;
/**
 * Represent the designer document snapshot data shared with callers of this public
 * contract.
 */
typedef struct UmiDesignerDocumentSnapshot { char application_id[UMI_DECL_ID_CAPACITY]; size_t component_count; uint64_t revision; int dirty; } UmiDesignerDocumentSnapshot;
/**
 * Initialise designer document from caller-provided values so later operations receive a
 * known state.
 */
UmiStatus umi_designer_document_create(const char *application_id,UmiDesignerDocument **out_document);
/**
 * Provide the designer document from declarative operation used by this module and its
 * client applications.
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Locate UmiDesignerDocumentSnapshot. Identify the fields that describe the current model and the field that indicates unsaved changes. Follow a declared operation to src/designer using the repository search.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Should changing the selected component create a new saved file?

### Worked answer

Selection changes which component is being inspected. It need not alter the document or save anything. Editing a component property changes the model; saving is a separate operation.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/studio-workflows/lessons/designer-model.html) · [Learning sequence](../../../../start/learning-sequence.md)
