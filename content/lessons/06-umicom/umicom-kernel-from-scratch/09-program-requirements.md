# Check what a native program needs

A service can exist without being suitable for a particular task. The native client checks a small list of requirements before the program continues.

## 1. Separate discovery from a request

Discovery asks what interface and limits the running image reports. A requirement says what this program needs. An actual service call then performs work subject to the Kernel's checks. A successful requirement check cannot grant a permission or reserve a future call.

 <svg viewbox="0 0 700 110" role="img" aria-label="Compatibility is checked before using a service; the service still makes its own decision." style="width:100%;max-width:700px"><title>Compatibility is checked before using a service; the service still makes its own decision.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">discover the contract</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">check requirements</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">handle service result</text></svg>

Compatibility is checked before using a service; the service still makes its own decision.

## 2. Find the real code

In your Kernel checkout, open `include/umicom/user/native_contract.h`, `programs/support/native_contract.c` and `programs/diagnostic/main.c`. Search for `UmicomUserContractCheck`. It takes two borrowed pointers and returns a named result. It does not allocate memory or perform another environment call.

```text
static const UmicomUserRequirements requirements = {
    sizeof(UmicomUserRequirements), 0U, 0U, 16U, 9U, 1U
};
```

This is the real diagnostic policy, not a complete program. The first field says how many bytes the known structure occupies. The next two request minimum minor version zero and no optional feature bits. The fourth requests a copy limit of at least 16 bytes. The fifth and sixth describe nine calls already used and one still needed. The final call exits the program.

## 3. Count the calls on paper

| Work | Calls | Total used |
| --- | --- | --- |
| Identity | 1 | 1 |
| Copy | 1 | 2 |
| Discover seven values | 7 | 9 |
| Exit | 1 | 10 |

The current monitor allows 32 calls. At the check there are 23 left, so one needed call fits. The source first proves used is no greater than the limit, then subtracts. Adding huge unsigned values can wrap to a small value and give the wrong answer.

## 4. Understand the feature mask

A bit is one binary digit, zero or one. Each feature occupies a different bit in the mask. A mask of 5 has bits for values 1 and 4. Requiring 4 succeeds against 5 because that bit is present; requiring 2 does not. The C expression `(available & required) == required` checks that every required bit is present.

The existing bits describe compiled messaging, file, stream and reporting routes. They do not say that this program owns a service handle. A handle is a service-managed reference, and the service checks its authority separately.

## 5. Predict a refusal

1. 32 calls allowed, 31 used, 2 needed: insufficient call budget.
2. 64 bytes allowed for one copy, 65 required: insufficient copy limit.
3. The required service bit is absent: missing feature.

A caller must handle these results without pretending the operation completed. The function leaves both inputs unchanged. Its structure-size check supports optional future trailing fields inside the caller's C program; it does not make an arbitrary pointer safe and is not a serialized network format.

## 6. Follow the evidence

The focused checks live in `tests/native_contract/requirements_tests.c`. They cover exact limits, overflow, missing features, malformed contracts and unchanged input. The diagnostic argument 4 also runs the shared implementation inside the separate guest program. Follow the Kernel guide for the two commands; a host test alone is not proof that an environment call worked.

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/09-program-requirements.html) · [Learning sequence](../../../start/learning-sequence.md)
