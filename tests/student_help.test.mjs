/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: tests/student_help.test.mjs
 *
 * PURPOSE:
 *   Check the native answer module, guide coverage and browser form behavior.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import assert from "node:assert/strict";
import { readFile } from "node:fs/promises";
import test from "node:test";

const asset = new URL("../content/assets/javascripts/student-help.wasm", import.meta.url);
const page = new URL("../content/community/student-help/index.md", import.meta.url);
const wasmBytes = await readFile(asset);
const { instance, module } = await WebAssembly.instantiate(wasmBytes);
const api = instance.exports;
const input = new Uint8Array(
    api.memory.buffer, api.BtbStudentHelpQuery(), api.BtbStudentHelpCapacity()
);

function ask(question) {
    const bytes = new TextEncoder().encode(question);
    input.set(bytes);
    return api.BtbStudentHelpAnswer(bytes.length);
}

test("the C23 module matches a question to a named answer and takes no imports", () => {
    assert.deepEqual(WebAssembly.Module.imports(module), []);
    const cases = [
        ["What is PowerShell?", 1],
        ["How do I install or update PowerShell?", 1],
        // Real beginner wording exercises each branch after slash and phrase
        // normalisation, including the explicit 5.1 side-by-side route.
        ["how to install/update my PowerShell to PowerShell version 7", 1],
        ["Do I need to download or upgrade PowerShell to version 7?", 1],
        ["How do I install/update PowerShell 7 from Windows PowerShell 5.1?", 2],
        ["How do I install PowerShell 7 on Windows 11?", 2],
        ["I have Windows PowerShell 5.1. How do I upgrade to 7?", 2],
        ["How do I UPDATE POWERSHELL 7?", 3],
        ["How do I update my PowerShell installation?", 3],
        ["How do I check my PowerShell version?", 4],
        ["$PSVersionTable.PSVersion", 4],
        ["WinGet isn't recognised.", 5],
        ["I cannot find winget to install PowerShell", 5],
        ["Can I install pwsh on Ubuntu?", 6],
        ["How do I get PowerShell on my Mac?", 6],
        ["How do I check free disk space?", 7],
        ["What is my current folder in PowerShell?", 8],
        ["How can I make a practice folder?", 8],
        ["How do I set up the C toolchain?", 9],
        ["How can I compile my first C program?", 10],
        ["What does git status show?", 11],
        ["Can I clone my repository?", 12],
        ["How can I test my CMake project?", 13],
        ["Where is the installed Framework SDK workshop?", 14],
        ["How do I prepare a bootable USB?", 15],
        ["I need an Umicom Kernel boot image", 15],
        ["How do I run Umicom C?", 16],
        ["What should I look for in a build log?", 17],
        ["Show me an Umicom C reflection example", 18],
        ["How can I keep a Framework metadata snapshot?", 19],
        ["How do I open the boot wizard in Umicom Setup Centre?", 20],
        ["Where is the contributor wiki?", 21],
        // Specific symptoms should open their exact guide before the more
        // general boot, SDK or build-log choices are considered.
        ["How do I verify a prebuilt Kernel launch kit?", 22],
        ["The installed Framework SDK headers differ from the exported SDK identity.", 23],
        ["Why does Studio build refuse --phase without an argument?", 24],
        ["Which temperature is warm enough?", 0],
        ["I am using gcctool powershellish ninjalikefront", 0],
        ["<script src='untrusted.js'></script>", 0],
        [" . ? ", 0]
    ];
    for (const [question, expected] of cases) assert.equal(ask(question), expected, question);
});

test("the router limits byte reads and handles an exactly full query", () => {
    assert.equal(input.length, 256);
    assert.equal(ask("PowerShell".padEnd(input.length, "!")), 1);
    assert.equal(api.BtbStudentHelpAnswer(input.length + 1), 0);
    assert.equal(api.BtbStudentHelpAnswer(0), 0);
});

test("every answer remains readable as a linked section in the page source", async () => {
    const markdown = await readFile(page, "utf8");
    const entries = Array.from(markdown.matchAll(
        /<details data-btb-answer="(\d+)" markdown="1">([\s\S]*?)<\/details>/g
    ));
    // The first router covered IDs 1 through 17. The expanded check
    // also requires the four new source-linked answers to stay in order.
    // assert.deepEqual(entries.map(entry => Number(entry[1])), Array.from({ length: 17 }, (_, i) => i + 1));
    // The previous twenty-one routes remain intact. Three diagnostic guides
    // extend the consecutive IDs so each compiled result resolves to a card.
    // assert.deepEqual(entries.map(entry => Number(entry[1])), Array.from({ length: 21 }, (_, i) => i + 1));
    assert.deepEqual(entries.map(entry => Number(entry[1])), Array.from({ length: 24 }, (_, i) => i + 1));
    for (const [section] of entries) {
        assert.match(section, /<summary>[^<]+<\/summary>/);
        assert.match(section, /\]\(\.\.\/[^)]+\.md(?:#[^)]+)?\)/);
    }
    // The mixed question must offer actions and real site links for either
    // version the learner might see in their Windows terminal.
    assert.match(entries[0][0], /winget install --id Microsoft\.PowerShell/);
    assert.match(entries[0][0], /winget upgrade --id Microsoft\.PowerShell/);
    assert.match(entries[0][0], /powershell-setup\.md#update-an-existing-powershell-7-installation/);
    assert.match(markdown, /assets\/branding\/umicom-wordmark\.svg/);
    assert.match(markdown, /assets\/branding\/umicom-wordmark-on-dark\.svg/);
    assert.match(markdown, /id="btb-help-status" role="status"/);
});

test("the browser adapter loads locally and displays only an authored answer", async () => {
    let submit;
    let activate;
    let displayed;
    let attach;
    let form;
    const status = {};
    const inputField = { value: "", disabled: true };
    const answerNode = { removeAttribute() {}, querySelector: () => ({ textContent: "Update steps" }) };
    const request = [];
    const originalFetch = globalThis.fetch;
    globalThis.document = {
        querySelector: () => form,
        getElementById: id => id === "btb-help-status" ? status : {
            replaceChildren: node => { displayed = node; }
        },
        querySelectorAll: () => [{ dataset: { btbAnswer: "3" }, cloneNode: () => answerNode }]
    };
    globalThis.document$ = { subscribe: callback => { attach = callback; } };
    globalThis.fetch = async (url, options) => {
        request.push([url.href, options.mode]);
        return { ok: true, arrayBuffer: async () => wasmBytes };
    };

    try {
        await import("../content/assets/javascripts/student-help.mjs");
        assert.equal(typeof attach, "function");
        assert.deepEqual(request, []);

        // Simulate an instant navigation from another page into student help.
        form = {
            dataset: {}, elements: { question: inputField }, isConnected: true,
            querySelector: () => ({ set disabled(value) { activate = !value; } }),
            addEventListener: (name, callback) => { if (name === "submit") submit = callback; }
        };
        await attach();
        assert.equal(activate, true);
        assert.equal(inputField.disabled, false);
        assert.deepEqual(request, [[asset.href, "same-origin"]]);

        let prevented = false;
        const event = { preventDefault: () => { prevented = true; } };
        inputField.value = "How do I update PowerShell 7?";
        submit(event);
        assert.equal(prevented, true);
        assert.equal(displayed, answerNode);
        assert.equal(displayed.open, true);
        assert.equal(status.textContent, "Answer: Update steps");

        inputField.value = "<script src='untrusted.js'></script>";
        submit(event);
        assert.equal(displayed, undefined);
        assert.match(status.textContent, /could not match/);
        assert.deepEqual(request, [[asset.href, "same-origin"]]);
    } finally {
        globalThis.fetch = originalFetch;
        delete globalThis.document;
        delete globalThis.document$;
    }
});
