# Chapter 293 — Compose the existing C23 observation model into a readiness graph

**Bits to Banking · Engineering track · ISO C23**  
**Lab:** `labs/native/service-readiness`; requires Update 39 `labs/native/sysadmin-evidence`.

## Why composition beats a second implementation

We already have a small well-tested C23 library for bounded, typed support observations. A developer facing a new feature could copy its structures and validation code into another folder. That seems fast but immediately creates two authorities. Over time, one might count missing required checks correctly while another treats them as warning-only. Umicom's architectural rule is to **compose existing contracts, then extend the Framework only when a reusable capability is missing**.

Here we reuse the earlier `BtbAdminReviewEvaluate` for every individual service's checks and introduce just one new concept: service A can depend on B, and A's result is constrained by B's result. This model is educational and portable; it does not invoke the OS. A future production implementation must use Umicom Framework's existing observability, task, build and service-lifecycle infrastructure rather than depend on these learning sources.

## Step 1 — Read the public interfaces

The C23 declarations in `service_readiness.h` are intentionally small. Every graph is caller-owned. `BtbServiceGraphRegister` copies service specifications after validating ID, capacity, name termination and absence of self-dependency. Dependencies on service IDs registered later are allowed at registration time, but evaluation refuses any dependency that was never registered. This is important: the graph is not considered valid simply because a path or ID looks plausible.

A `BtbServiceNode` contains copied evidence from Update 39. The current graph has a `captureId`: that is an identifier for one fictional observation session. It is **not** a clock, password or cryptographic proof. Check records carry their own capture identifiers. During evaluation these are compared with the expected session ID, making an older PASS stale rather than ready.

## Step 2 — Create the graph and register scopes

```c
BtbServiceGraph graph;
BtbServiceSpec store = {
    1U, 0U, UINT32_C(1), "Notes document storage"
};
BtbServiceSpec app = {
    2U, UINT32_C(1), UINT32_C(1), "Notes application"
};

if (BtbServiceGraphInit(&graph, UINT64_C(20261014)) != BTB_SERVICE_OK)
    return 1;
if (BtbServiceGraphRegister(&graph, &store) != BTB_SERVICE_OK ||
    BtbServiceGraphRegister(&graph, &app) != BTB_SERVICE_OK)
    return 2;
```

`UINT32_C(1)` makes bit zero of the dependency mask visible. The Notes application (`serviceId` 2) declares a dependency on service 1. The code does not take a pointer to any OS service or borrow a temporary string. The specification is copied into graph-owned value storage.

## Step 3 — Supply one fictional observation

```c
BtbAdminReview review;
BtbAdminObservation observation = {
    1U, UINT64_C(20261014), BTB_ADMIN_PASS,
    "Practice storage check passed"
};

if (BtbAdminReviewInit(&review, UINT64_C(20261014)) != BTB_ADMIN_OK)
    return 3;
if (BtbAdminReviewAdd(&review, &observation) != BTB_ADMIN_OK)
    return 4;
if (BtbServiceGraphAttach(&graph, 1U, &review) != BTB_SERVICE_OK)
    return 5;
```

The observation has a label, state, check ID and capture ID. It is not an actual filesystem test. A label containing the words 'storage passed' is merely supplied classroom data; no function opens a file to prove it. In a real service, data collection and permission checks would have to be implemented by the authorised Framework owner.

Attach a second passing review to service 2, then call `BtbServiceGraphEvaluate`. The result is a copied `BtbServiceSummary` rather than a pointer to internal mutable storage. The caller can inspect service ID, decision, stale/missing counts and inherited dependency flags.

## Step 4 — Understand the verification states

| Status from the new graph | Meaning |
|---|---|
| `BTB_SERVICE_OK` | The graph was evaluated and a complete summary was produced. Individual services may still be BLOCKED. |
| `BTB_SERVICE_INVALID` | Invalid graph, malformed specification or malformed evidence. Output is unchanged on evaluation failure. |
| `BTB_SERVICE_DEPENDENCY_ERROR` | A declared prerequisite service is not registered. |
| `BTB_SERVICE_CYCLE` | The prerequisite chain loops back to a service already being visited. |
| `BTB_SERVICE_DUPLICATE` | Registering the same stable service ID twice is refused. |
| `BTB_SERVICE_FULL` | The fixed eight-record capacity was reached. |

**Critical distinction:** The return value `BTB_SERVICE_OK` is about successful *evaluation*, not aggregate *readiness*. A successful evaluation can yield a blocked service. This is exactly the distinction a professional support team needs when it reports that its monitoring checks ran correctly but detected a failure.

## Step 5 — Build from PowerShell without introducing a script

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\service-readiness" -B ".\output\learning-build\service-readiness" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\service-readiness" --parallel 2
ctest --test-dir ".\output\learning-build\service-readiness" --no-tests=error --output-on-failure
```

The CMake project uses `add_subdirectory` to build the previous laboratory from its existing source location. It does not replace its headers, fork its implementation or overwrite existing CMake definitions. This focused build does not qualify the whole Framework, OS or website.

## Exercises

1. Draw a graph with storage, Notes service and a UI. Which prerequisite is required at each level?
2. Explain why `BtbServiceGraphAttach` takes a pointer to caller-owned `BtbAdminReview` but copies its value.
3. Explain why a graph that references a missing service must refuse evaluation rather than silently produce READY.
4. Find the success and error paths in `BtbServiceGraphEvaluate`. Is `outSummary` modified before all validation completes? No: the function produces a private candidate first.

**Next:** [Chapter 294 — Negative tests and stale evidence](294-verify-stale-and-blocked-service-evidence.md).
