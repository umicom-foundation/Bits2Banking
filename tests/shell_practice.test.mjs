/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: tests/shell_practice.test.mjs
 *
 * PURPOSE:
 *   Check the compiled shell model and the browser's form adapter.
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

const asset = new URL("../content/assets/javascripts/shell-practice.wasm", import.meta.url);
const bytes = await readFile(asset);
const module = await WebAssembly.compile(bytes);

async function openWorkspace() {
    const { exports: api } = await WebAssembly.instantiate(module);
    const encoder = new TextEncoder();
    const decoder = new TextDecoder();
    // Read output through the same exported view the browser adapter uses.
    function output() {
        return decoder.decode(new Uint8Array(api.memory.buffer, api.BtbShellOutput(), api.BtbShellOutputLength()));
    }
    function command(mode, text) {
        const input = encoder.encode(text);
        new Uint8Array(api.memory.buffer, api.BtbShellInput(), input.length).set(input);
        return [api.BtbShellSubmit(mode, input.length), output()];
    }
    return { api, command, output };
}

test("the compiled model keeps Bash and PowerShell folder state separate", async () => {
    const { api, command } = await openWorkspace();
    assert.deepEqual(WebAssembly.Module.imports(module), []);
    assert.deepEqual(command(0, " pwd "), [0, "/practice\n"]);
    assert.deepEqual(command(0, "ls"), [0, "reports\nsamples\n"]);
    assert.deepEqual(command(0, "cd reports"), [0, ""]);
    assert.deepEqual(command(1, "get-location"), [0, "C:\\practice\n"]);
    assert.deepEqual(command(0, "cat 'closing notes.txt'"), [0, "Approved\nPending\nApproved\n"]);
    assert.deepEqual(command(1, "set-location SAMPLES"), [0, ""]);
    assert.deepEqual(command(1, 'Get-Content "LIMITS.TXT"'), [0, "Daily review limit: 4\n"]);
    assert.deepEqual(command(0, "pwd"), [0, "/practice/reports\n"]);
    assert.deepEqual(command(0, "cd .."), [0, ""]);
    api.BtbShellReset(1);
    assert.deepEqual(command(1, "Get-Location"), [0, "C:\\practice\n"]);
});

test("paths, syntax and unsupported commands report predictable status", async () => {
    const { api, command, output } = await openWorkspace();
    assert.equal(api.BtbShellCapacity(), 192);
    assert.equal(command(0, "cd /")[0], 1);
    assert.deepEqual(command(0, "echo $?"), [0, "1\n"]);
    assert.deepEqual(command(0, "echo $?"), [0, "0\n"]);
    assert.equal(command(1, "Get-Content missing.txt")[0], 1);
    assert.deepEqual(command(1, "$?"), [0, "False\n"]);
    assert.deepEqual(command(1, "$?"), [0, "True\n"]);
    assert.equal(command(0, "cd reports")[0], 0);
    assert.equal(command(0, "cd .. extra")[0], 2);
    assert.equal(command(0, 'cat "closing notes.txt')[0], 2);
    assert.equal(command(0, "cat closing notes.txt")[0], 2);
    assert.equal(command(0, "ls | sort")[0], 2);
    assert.equal(command(0, "anything")[0], 127);
    assert.deepEqual(command(0, "echo $?"), [0, "127\n"]);
    assert.deepEqual(command(0, "pwd"), [0, "/practice/reports\n"]);
    assert.equal(api.BtbShellSubmit(0, api.BtbShellCapacity() + 1), 2);
    assert.match(output(), /too long/);
    assert.equal(api.BtbShellSubmit(7, 0), 2);
    assert.deepEqual(command(0, "pwd"), [0, "/practice/reports\n"]);
});

test("the article keeps approved branding, labelled controls and a written exercise", async () => {
    const page = await readFile(new URL("../content/practice/shell/index.md", import.meta.url), "utf8");
    assert.match(page, /umicom-wordmark\.svg.*umicom-wordmark-light/u);
    assert.match(page, /umicom-wordmark-on-dark\.svg/u);
    assert.match(page, /id="btb-shell-status" role="status"/u);
    assert.match(page, /label for="btb-shell-command"/u);
    assert.match(page, /\x60echo \$\?\x60/u);
    assert.match(page, /shell-practice\/index\.md/u);
});

test("the browser adapter loads locally and creates a fresh workspace on a new visit", async () => {
    const status = {};
    const output = {};
    const fetches = [];
    let currentForm;
    let visit;
    function control(value) {
        const listeners = new Map();
        return { value, disabled: true, listeners, focus() {},
            addEventListener: (name, listener) => listeners.set(name, listener) };
    }
    function freshForm() {
        const dialect = control("0");
        const command = control("");
        const run = control();
        const reset = control();
        const events = new Map();
        return { dataset: {}, isConnected: true, elements: { dialect, command, run, reset }, events,
            addEventListener: (name, listener) => events.set(name, listener) };
    }
    const savedFetch = globalThis.fetch;
    globalThis.document = {
        querySelector: () => currentForm,
        getElementById: id => id === "btb-shell-status" ? status : output,
    };
    globalThis.document$ = { subscribe: listener => { visit = listener; } };
    globalThis.fetch = async (url, options) => {
        fetches.push([url.href, options.mode]);
        return { ok: true, arrayBuffer: async () => bytes };
    };
    try {
        await import("../content/assets/javascripts/shell-practice.mjs");
        const event = { preventDefault() {} };
        currentForm = freshForm();
        await visit();
        assert.equal(currentForm.elements.run.disabled, false);
        currentForm.elements.command.value = "cd reports";
        currentForm.events.get("submit")(event);
        currentForm.elements.command.value = "pwd";
        currentForm.events.get("submit")(event);
        assert.equal(output.textContent, "/practice/reports\n");
        currentForm.elements.command.value = "£".repeat(192);
        currentForm.events.get("submit")(event);
        assert.match(output.textContent, /too long/);
        currentForm.elements.dialect.value = "1";
        currentForm.elements.dialect.listeners.get("change")();
        assert.equal(output.textContent, "");
        currentForm.elements.reset.listeners.get("click")();
        assert.match(status.textContent, /starting folder/);
        currentForm.isConnected = false;
        currentForm = freshForm();
        await visit();
        currentForm.elements.command.value = "pwd";
        currentForm.events.get("submit")(event);
        assert.equal(output.textContent, "/practice\n");
        assert.deepEqual(fetches, [[asset.href, "same-origin"]]);
    } finally {
        globalThis.fetch = savedFetch;
        delete globalThis.document;
        delete globalThis.document$;
    }
});
