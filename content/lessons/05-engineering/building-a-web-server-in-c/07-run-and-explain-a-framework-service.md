# Run and explain a Framework service

[Course contents](index.md) · [Previous: Buffer capacity and partial input](06-buffer-capacity-and-partial-input.md)

## Read the real example before building

Open Framework's examples/web/local_service.c using the source link below. Its Home and Health handlers construct responses; its main function configures routes and server lifetime. The inspected example accepts --port and optionally --root. It does not accept a guessed --host option.

Find ParsePort. It accepts decimal ports between 1024 and 65535 and rejects invalid characters and overflow. Find the loopback request gate. Then find route registration for /api/health and /api/echo. Loopback limits the exercise to the local machine; it does not make every local request trusted.

```text
local client -> connection and framing -> route -> handler
                                                  |
local client <- response bytes <-------------------+
```

## Prepare the optional run

1. Prepare the Windows UCRT64 tools described in the Framework setup guide: CMake, Ninja, GCC and the repository's required libraries.
2. Open PowerShell in the Framework checkout. The example below assumes it is under C:\umicom\Umicom-Applications\framework; use your own checkout location if different.
3. Configure with learning examples enabled, then build only umicom-web-local-service-example and its dependencies. A target is CMake's name for a buildable library or program. The target is declared in cmake/UmicomLocalWebService.cmake.
4. Launch the program with --port 8080. If the port is occupied, choose another permitted port and change the client URL to match. Run each line separately and stop on any error.

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-debug -DUMICOM_BUILD_LEARNING_EXAMPLES=ON
cmake --build --preset windows-ucrt64-debug --target umicom-web-local-service-example --parallel 2
& ".\build\windows-ucrt64-debug\bin\umicom-web-local-service-example.exe" --port 8080
```

The preset supplies the compiler and build directory. If it reports a missing dependency, resolve that configure error before building. If the target is unknown, check the learning-examples option and whether this checkout contains the source linked below. Do not treat a previous executable as the result of a failed build. While the service runs, open a second terminal for a read-only request:

```powershell
curl.exe -i http://127.0.0.1:8080/api/health
```

The inspected handler specifies status 200, application/json content and a service/status response containing umicom-local-example and ready. These are expected results for this source, not evidence that your build or server has run. An absent response needs investigation of the launch log, port and process state.

## Trace a failure

Stop the practice server and repeat the request. Connection failure is different from an HTTP error response: no handler may have run at all. Keep these categories distinct in logs. Do not expose this learning server to a network as a production deployment; authentication, TLS, resource limits and operational hardening need explicit qualification.

## Exercise

Where should a new /api/version response be implemented: in the socket receive loop or in a route handler? Which layer should reject oversized headers?

## Explained answer

A route handler owns the version response. Shared connection/parser code enforces header limits before routing. This separation lets Studio, Media and other applications reuse Framework web services while supplying their own domain behaviour.

## Continue learning

[Course contents](index.md) · [Previous: Buffer capacity and partial input](06-buffer-capacity-and-partial-input.md)

[Browser edition](../../../courses/building-a-web-server-in-c/lessons/07-run-and-explain-a-framework-service.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/examples/web/local_service.c). This public revision matches the source inspected for this lesson.

[Primary reference](https://www.rfc-editor.org/rfc/rfc9112.html).

[Next: Reject an invalid port before starting a server](08-reject-an-invalid-port-before-launch.md)
