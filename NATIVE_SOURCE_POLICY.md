# Native development and publication formats

New executable software for Bits2Banking and the shared Umicom platform uses **C23** as its primary language. Use architecture-specific **Assembly** when it teaches an instruction-set contract or provides a justified low-level implementation. Keep the stable Umicom Framework public C ABI authoritative and applications thin.

Educational articles and book manuscripts use **Markdown**. The existing MkDocs website needs **YAML** configuration and HTML/CSS presentation; these are content and presentation formats, not additional application runtimes. **CMake** is the declarative build configuration for native learning laboratories. Windows contributors may use PowerShell to invoke those tools; the delivered application logic should not depend on PowerShell scripts.

Do not add new Python, JavaScript, C++, Java, PHP or other executable implementation files as a convenience when C23 or Assembly can satisfy the actual requirement. If an external tool requires another language, document why it is needed, confine the dependency to an adapter, and retain the native core. Existing lessons in other languages and historical BookForge scripts are preserved: removing them would destroy authored educational material and break compatibility before an equivalent replacement exists.

Practical laboratories must include complete source files, compiler warnings, positive and negative tests, and a reproducible build. C interfaces should document buffer capacity, ownership, object lifetime, error results and whether rejected input can change caller-owned state. Native validators report deficiencies; they must not silently edit or delete manuscripts.

For the existing publishing pipeline, the C23 `umicom-education audit` command validates local Markdown destinations in the configured navigation. It does not claim to parse general YAML. The strict MkDocs build remains the final website validation until a native renderer with equivalent capability has been implemented and qualified.
