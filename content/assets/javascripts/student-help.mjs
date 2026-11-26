/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/assets/javascripts/student-help.mjs
 *
 * PURPOSE:
 *   Connect the student page's form to the local C question router.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

let routerLoad;

function loadRouter() {
    // The only request fetches the same-site module. Questions stay in memory.
    if (!routerLoad) {
        const url = new URL("student-help.wasm", import.meta.url);
        routerLoad = fetch(url, { mode: "same-origin" })
            .then(response => {
                if (!response.ok) throw new Error("Student help asset is unavailable");
                return response.arrayBuffer();
            })
            .then(bytes => WebAssembly.instantiate(bytes))
            .then(({ instance }) => instance.exports)
            .catch(error => {
                routerLoad = undefined;
                throw error;
            });
    }
    return routerLoad;
}

async function mountStudentHelp() {
    // Material can replace the inner document without re-running this module.
    const form = document.querySelector("[data-btb-help-form]");
    if (!form || form.dataset.mounted) return;
    form.dataset.mounted = "true";

    const question = form.elements.question;
    const ask = form.querySelector("button");
    const status = document.getElementById("btb-help-status");
    const result = document.getElementById("btb-help-result");
    const answers = new Map(Array.from(
        document.querySelectorAll("details[data-btb-answer]"),
        entry => [Number(entry.dataset.btbAnswer), entry]
    ));

    // Keep the guide links available unless the native module is ready.
    let route;
    form.addEventListener("submit", event => {
        event.preventDefault();
        if (!route) return;
        const bytes = route.encoder.encode(question.value);
        if (bytes.length > route.capacity) {
            result.replaceChildren();
            status.textContent = "Try a shorter question.";
            return;
        }

        // Only select from authored elements. User input never enters markup,
        // URLs, or the answer text.
        route.input.set(bytes);
        const entry = answers.get(route.exports.BtbStudentHelpAnswer(bytes.length));
        if (!entry) {
            result.replaceChildren();
            status.textContent = "I could not match that question. Try a topic below or open the course library.";
            return;
        }
        const answer = entry.cloneNode(true);
        answer.removeAttribute("data-btb-answer");
        answer.open = true;
        result.replaceChildren(answer);
        status.textContent = "Answer: " + answer.querySelector("summary").textContent.trim();
    });

    try {
        const exports = await loadRouter();
        const capacity = exports.BtbStudentHelpCapacity();
        const offset = exports.BtbStudentHelpQuery();
        route = {
            exports,
            capacity,
            input: new Uint8Array(exports.memory.buffer, offset, capacity),
            encoder: new TextEncoder()
        };
        if (form.isConnected) {
            question.disabled = false;
            ask.disabled = false;
            status.textContent = "Ready. Ask one question in English.";
        }
    } catch {
        if (form.isConnected) status.textContent = "Question matching is unavailable. You can still read the answers below.";
    }
}

// Material publishes this observable for initial and instant-navigation pages.
// The direct call also supports a page rendered without instant navigation.
if (typeof document$ !== "undefined") document$.subscribe(mountStudentHelp);
void mountStudentHelp();
