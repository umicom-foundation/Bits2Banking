/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/web/framework-activity/page.js
 *
 * PURPOSE:
 *   Connect browser controls to the exported C activity function.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

/* The static import is retained for comparison. A dynamic import belongs inside
 * the error boundary so a missing generated module produces visible guidance.
 * import createActivityModule from "./activity.js";
 */

const button = document.querySelector("#complete");
const output = document.querySelector("#completed");
const message = document.querySelector("#message");
let current = 0;
button.disabled = true;
try {
    const { default: createActivityModule } = await import("./activity.js");
    const module = await createActivityModule();
    button.disabled = false;
    message.textContent = "Ready";
    button.addEventListener("click", () => {
        const next = module._BtbActivityNext(current);
        if (next >= 0) {
            current = next;
            output.textContent = String(current);
            message.textContent = "Exercise recorded";
        } else {
            message.textContent = "No change: check the count or begin another activity";
        }
    });
} catch {
    message.textContent = "The C module could not load. Check the build files and HTTP server.";
}

