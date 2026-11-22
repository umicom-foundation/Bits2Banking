# Run the reserve statement exercise on Umicom WebServer

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

The [statement calculation course](../courses/native-statement-calculations/index.html) uses a synthetic ledger. The reserve account has two posted entries, `+2600` and `−850` cents. Their posted movement is `1750` cents. A third entry, `+500`, is pending. This lab runs the calculation on a loopback Umicom WebServer and lets you decide whether to include that third amount in a practice result.

```c
int umicom_run(int adjustment)
{
    int posted = 2600 - 850;
    return posted + adjustment;
}
```

The integer `adjustment` is the request input. For a posted-only result, supply zero. For the practice result that includes the pending amount, supply `500`.

## Build the checked program and host

1. Use a current Umicom C compiler and the existing Bits2Banking site export. Follow the [native education setup](native-education-tools.md) to build the site. Keep the generated `site` directory separate from the manuscript and the source code.
2. Compile the original `labs/native/statement-cvm-web/statement_review.uc` exercise to a required-input artifact. This is the checked Umicom C integer profile. The program has a single entry point named `umicom_run`, which receives one signed integer. It takes that integer as an adjustment in cents and adds it to the known posted movement.

   ```powershell
   $Books = 'C:\umicom\Umicom-Bits2Banking'
   $Framework = 'C:\umicom\Umicom-Applications\framework'
   $Compiler = 'C:\umicom\umicom-c'
   $Native = 'C:\umicom\build\bits2banking-native-web'
   $Artifact = Join-Path $Native 'statement-review.umcb'
   $CvmTool = Join-Path $Compiler 'build\bin\umicom-c.exe'
   New-Item -ItemType Directory -Path $Native -Force | Out-Null
   & $CvmTool compile-input (Join-Path $Books 'labs\native\statement-cvm-web\statement_review.uc') $Artifact
   if ($LASTEXITCODE -ne 0) { throw 'The checked statement program did not compile.' }
   ```

3. Build the existing Framework local WebServer with that specific artifact. Use an Umicom C checkout that includes the browser worker resources expected by the existing application configuration.

   ```powershell
   $Build = Join-Path $Native 'framework'
   cmake -S $Framework -B $Build -G Ninja `
     -DUMICOM_BUILD_LEARNING_EXAMPLES=ON `
     -DUMICOM_LOCAL_WEB_CVM_PREVIEW=ON `
     "-DUMICOM_C_PREVIEW_SOURCE=$Compiler" `
     "-DUMICOM_LOCAL_WEB_CVM_APPLICATION=$Artifact"
   if ($LASTEXITCODE -ne 0) { throw 'Framework configuration failed.' }
   cmake --build $Build --target umicom-web-local-service-example --parallel 2
   if ($LASTEXITCODE -ne 0) { throw 'WebServer compilation failed.' }
   ```

4. Select the published **output** directory and enable the exercise explicitly. Use the absolute path to your exported site. The server validates its embedded required-input artifact before opening the listener.

   ```powershell
   $Site = (Resolve-Path (Join-Path $Books 'site')).Path
   $WebServer = Join-Path $Build 'bin\umicom-web-local-service-example.exe'
   & $WebServer --port 8765 --root $Site --with-cvm-application
   ```

## Try the calculation

1. While the local service is running, open the [reserve statement practice form](http://127.0.0.1:8765/labs/statement-cvm-web/) and select **Calculate movement**. You can also open the [worked example with the pending 500 cents](http://127.0.0.1:8765/cvm/application/run?input=500) directly. Expect an HTTP `200` JSON response containing `"value":2250`. The response also reports the number of interpreted instructions.
2. Change `input=500` to `input=0` and reload. The posted-only result is `1750`. Try `input=-25` for a synthetic decrease. Expect `1725`. These are movements in cents. An account balance would also depend on the opening amount.
3. Remove the value or provide two `input` fields. Expect HTTP `400` and `{"error":"query"}`. The route accepts one literal signed 32-bit decimal value. A value that makes the result exceed the signed range is also refused. The exercise changes no saved ledger and opens no files during calculation.
4. Stop the local service with Ctrl+C. Relaunch without `--with-cvm-application` for the existing static-only preview. After an edit, compile to a fresh artifact filename and configure the host with that new path before rebuilding. The host embeds the compiled bytes, and the compiler preserves existing output files.

## Choose the appropriate preview

The optional exercise runs on local IPv4 loopback. It is available only with the explicit launch flag and sees only the selected artifact. The existing website layout, local brand resources and ordinary static routes continue to belong to the site export. This C23 host mounts the Umicom C calculation through Framework's file and route services. The established MkDocs renderer still produces the existing HTML layout and search assets.

The Framework local WebServer bounds each static response to **1 MiB** and returns HTTP `413` for a larger file. A full Bits2Banking export can exceed that limit in its generated homepage, search index and historical book artwork. Check your export with `Get-ChildItem $Site -File -Recurse | Where-Object Length -gt 1MB`. Use the [streaming education preview](native-education-tools.md#generate-and-preview-html) for the complete catalogue and larger files. For example, use `umicom-education serve --repo $Books --port 8766` in a separate terminal after generating the HTML. The small [standalone practice entry](http://127.0.0.1:8765/labs/statement-cvm-web/) and result route belong to the bounded Framework listener on port `8765`.

If the executable rejects `--with-cvm-application`, inspect `--help` and confirm that the selected compiler produced a required-input artifact and that the Framework configuration names it. If the page is missing, verify that `--root` points at the generated `site`, which contains `index.html`. These local checks cover the exercise and preview. The separate public deployment workflow owns host configuration and publication.
