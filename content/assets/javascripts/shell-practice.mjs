/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/assets/javascripts/shell-practice.mjs
 *
 * PURPOSE:
 *   Connect the existing lesson form to the native C practice workspace.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
const asset = new URL("./shell-practice.wasm", import.meta.url);
const encoder = new TextEncoder();
const decoder = new TextDecoder();
let compiled;

function loadModule() {
    // The only network request loads the same-site lesson asset. Command text
    // stays in the browser and goes directly into the C module's memory.
    compiled ??= (async () => {
        const response = await fetch(asset, { mode: "same-origin" });
        if (!response.ok) throw new Error("Practice module could not be loaded");
        return WebAssembly.compile(await response.arrayBuffer());
    })().catch(error => {
        compiled = undefined;
        throw error;
    });
    return compiled;
}

async function attach() {
    const form = document.querySelector("[data-btb-shell-form]");
    if (!form || form.dataset.ready) return;
    form.dataset.ready = "loading";
    const status = document.getElementById("btb-shell-status");
    const output = document.getElementById("btb-shell-output");
    const { dialect, command, run, reset } = form.elements;
    try {
        // Each visit gets a fresh workspace even when the theme keeps the
        // surrounding page. Switching dialects retains their separate state.
        const { exports: api } = await WebAssembly.instantiate(await loadModule());
        if (!form.isConnected) return;
        form.addEventListener("submit", event => {
            event.preventDefault();
            const bytes = encoder.encode(command.value);
            if (bytes.length <= api.BtbShellCapacity()) {
                new Uint8Array(api.memory.buffer, api.BtbShellInput(), bytes.length).set(bytes);
            }
            const result = api.BtbShellSubmit(Number(dialect.value), bytes.length);
            const text = new Uint8Array(api.memory.buffer, api.BtbShellOutput(), api.BtbShellOutputLength());
            output.textContent = decoder.decode(text);
            status.textContent = result ? "Practice command refused. Read the output." :
                (text.length ? "Practice command finished." : "Practice command finished without output.");
        });
        reset.addEventListener("click", () => {
            api.BtbShellReset(Number(dialect.value));
            command.value = "";
            output.textContent = "";
            status.textContent = "The selected practice workspace is back at its starting folder.";
            command.focus();
        });
        // Clear the previous display so the next prompt and result both
        // belong to the selected practice shell.
        dialect.addEventListener("change", () => {
            output.textContent = "";
            status.textContent = "Enter a command for the selected shell.";
        });
        for (const control of [dialect, command, run, reset]) control.disabled = false;
        status.textContent = "Ready. Enter a command for the selected shell.";
        form.dataset.ready = "ready";
    } catch {
        status.textContent = "The interactive module could not load. Use the worked steps below.";
        form.dataset.ready = "";
    }
}

// Material's instant navigation creates fresh forms on the same document.
if (globalThis.document$) {
    globalThis.document$.subscribe(attach);
} else if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", attach, { once: true });
} else {
    void attach();
}
