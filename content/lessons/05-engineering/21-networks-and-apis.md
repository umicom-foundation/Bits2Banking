# 21. Networks, HTTP and application APIs

Two programs do not need to run on the same computer to communicate. A network carries information between machines, and protocols define how that information is represented and exchanged.

A browser opening a page, Git fetching a repository and a trading application receiving market data all involve communication protocols. Understanding the basic vocabulary helps you distinguish a connection problem from an application defect.

## Addresses, names and connections

An **IP address** identifies a network endpoint. A **port** helps identify a particular service on a machine. **DNS** translates domain names, such as `example.com`, into addresses. **TCP** provides an ordered, reliable byte stream between endpoints. **UDP** transports datagrams without providing TCP's reliability guarantees.

An **HTTP** client sends a request; an HTTP server sends a response. Common request methods include `GET` for retrieving a resource and `POST` for submitting information. Responses carry **status codes**: for example, `200` normally means success and `404` means the requested resource was not found.

**HTTPS** is HTTP protected by TLS. Encryption protects information in transit and authentication helps the client verify the server's identity. Using HTTPS does not automatically make application logic or stored data secure.

## Run a local web server

Create a new folder with a single file named `index.html`, then open a terminal in that folder:

```powershell
python -m http.server 8000 --bind 127.0.0.1
```

This starts a simple development server on your own computer. Leave that terminal open and, in another PowerShell window, enter:

```powershell
Invoke-WebRequest -Uri "http://127.0.0.1:8000/" |
    Select-Object StatusCode
```

The expected HTTP status is `200` if the server started correctly. Now request a page that does not exist:

```powershell
try {
    Invoke-WebRequest -Uri "http://127.0.0.1:8000/missing.html"
} catch {
    Write-Output $_.Exception.Message
}
```

The request should report a missing resource. Stop the server with **Ctrl+C** when finished.

## What is an API?

An **Application Programming Interface** (API) is a contract through which software exposes operations or data. Not all APIs use networks: a C header also defines an API. A network API might offer a resource such as `GET /tasks` and return JSON:

```json
[
  {"id": "T-101", "title": "Review docs", "status": "todo"},
  {"id": "T-102", "title": "Run tests", "status": "done"}
]
```

A **schema** defines which fields may appear and what they mean. An API should explain error results as carefully as success results. A caller must not assume that a network timeout proves a requested write failed; the server may have completed the work before the response was lost. Unique operation identifiers and idempotency rules can prevent duplicate effects when requests are retried.

## Connections in Umicom

Umicom Framework uses provider-neutral contracts to connect modules and external services. For example, a trading application can request market data through a framework boundary while an adapter handles the details of a broker's API. This keeps the application's business rules independent of any one vendor's protocol or library.

In a financial application, connection monitoring is not enough. The system must also reconcile order updates, payments, messages and persisted events so it knows whether processing completed as intended.

**Next:** [Use modules and design patterns](22-modules-and-patterns.md).
