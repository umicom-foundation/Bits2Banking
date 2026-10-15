# Native C23 remote-access review — Update 43

This **offline educational** laboratory composes Update 42's `BtbDeploymentEvaluate` and therefore inherits the tested Update 39–42 evidence, service readiness, maintenance and deployment contracts. It contains **no SSH implementation, live authentication, network socket, DNS lookup, key storage, certificate parser, firewall configuration, service-manager action or Git operation**. It only evaluates caller-supplied fictional claims. No decision is a substitute for production identity verification or human authorisation.

The `BtbRemoteReview` copies an immutable deployment snapshot plus a labelled access scope. `BtbRemoteAttach` copies a single evidence record and refuses repeated assignment. `BtbRemoteEvaluate` reports missing claimed checks as independent bits. Only a qualifying **fictional** deployment with complete, newer-in-sequence access evidence produces `REVIEWABLE`; restored or rolled-back deployments never qualify. All records remain caller-owned and failure paths preserve the caller's output.

From the `Umicom-Bits2Banking` repository root on Windows PowerShell:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\remote-access-review" -B ".\output\learning-build\remote-access-review" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\remote-access-review" --parallel 2
ctest --test-dir ".\output\learning-build\remote-access-review" --no-tests=error --output-on-failure
& ".\output\learning-build\remote-access-review\btb-remote-access-review-demo.exe"
```

On Linux:

```bash
cmake -S labs/native/remote-access-review -B output/learning-build/remote-access-review -G Ninja -DBUILD_TESTING=ON
cmake --build output/learning-build/remote-access-review --parallel 2
ctest --test-dir output/learning-build/remote-access-review --no-tests=error --output-on-failure
./output/learning-build/remote-access-review/btb-remote-access-review-demo
```

Learner exercise: run the named `host-key`, `outside-window`, `rollback`, `atomic-output` and `mutations` tests separately. Explain why a correct return from this lab **does not prove** an SSH host key matches, a real deployment passed, or that any person is authorised to access a server. The toolchain, Windows test results and exact test count must be observed locally before declaring that host accepted.
