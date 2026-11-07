<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-javascript/05-publish-a-checked-action-result.md

PURPOSE:
Explain the lesson: Publish a checked action result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Publish a checked action result

## An event requests a change

A click listener is a function called when the browser delivers a click event. That function should ask the model for a result and then update the presentation. Changing the display first can show a result that the model has refused.

The activity lab stores one temporary number named current. It calls the C export with that number and receives either an accepted next number or a negative refusal value.

## Setup recap

Build and serve the [browser activity lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/README.md). Read page.js together with labs/native/activity-adapters/bridge.c and the existing framework-activity/activity.c. A browser console can help inspect values, but changes made there are not saved source edits.

## Read the decision

~~~javascript
const next = module._BtbActivityNext(current);
if (next >= 0) {
    current = next;
    output.textContent = String(current);
}
~~~

The assignment comes after the success condition. Refusal updates the explanation, while the previous count remains. textContent inserts text rather than interpreting the result as HTML. String converts a number to its display representation; it does not validate an arbitrary business value.

## Lab

1. Load the page and record its starting count.
2. Activate the button once, then again.
3. Expect one increment for each accepted action.
4. Review the native bridge test cases for negative and maximum values.
5. In a separate exercise copy, start current at 999 and make the output match that initial state.
6. Accept one action, then request another.
7. Expect 1000 to remain visible with a refusal explanation on the second request.

Keep source initialization and the initial display consistent. Otherwise a test can accidentally begin with two different states.

## Exercise and explanation

Should a failed request set the count back to zero? No. That would be a second state change unrelated to the refused action. A separate reset command would need its own model contract and visible purpose.

## Connection to larger applications

Order entry, saving a file and editing a media timeline all need truthful outcomes. Real operations may be asynchronous or partially completed, so their contracts are more detailed than this counter. Do not reuse the counter's simple failure guarantee without checking the service you are calling.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/page.js). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-await-a-native-module.md)


[Next: Wait for a compiled C module](07-wait-for-a-native-module.md)
