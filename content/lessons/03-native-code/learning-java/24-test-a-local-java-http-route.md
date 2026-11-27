# Test a local Java HTTP route

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Write a short HTTP exchange on your own computer. One route returns a confirmed reading as JSON. Two other requests show how the answer changes when the method or path is wrong. Read [Read an HTTP exchange](../../04-web/learning-web-servers/02-read-an-http-exchange.md) first if `GET` or a response status is new to you.

## Run the example

1. Save [LocalReadingServer.java](../../../labs/java-path/LocalReadingServer.java) in a practice folder.
2. Open your terminal in that folder. Compile and start the exercise using the JDK from the course.
3. Read the three output lines. The server stops automatically when the exercise finishes.

```powershell
javac --release 21 LocalReadingServer.java
java LocalReadingServer
```

Expected output

```text
GET 200 {"north":20}
POST 405 (Allow: GET)
GET /readings/extra 404
```

## Follow the request and the response

1. `127.0.0.1` means the current computer. Port `0` lets the operating system choose an available port for this run.
2. The server registers `/readings` and checks the exact path. A request for `/readings/extra` reaches the prefix context, then receives `404` because the extra path has no route in this exercise.
3. The permitted method is `GET`. `POST` receives `405` and an `Allow` header that says `GET`.
4. The successful response includes `application/json` and the byte length of the encoded text. The client reads those bytes and prints the status and body.
5. Each request has a five-second wait limit. The `finally` block stops the practice server even if a request fails.

## Practise and recover

1. Change the reading value in `body` from `20` to `25` and run the two commands again. Only the JSON body in the first line should change.
2. Explain the difference between an unsupported method for a route and a path with no route.
3. If the program reports a connection error, check that loopback connections are available in your practice environment and try again. The program uses a new port each time.

The same three checks make a starting point for a native Umicom Webserver route test. Check the status, response headers and body before wiring in the code that produces the reading.

[Return to Learning Java](index.md) · [Read a local database with JDBC](23-read-a-local-database-with-jdbc.md) · [JDK HTTP server API](https://docs.oracle.com/en/java/javase/21/docs/api/jdk.httpserver/com/sun/net/httpserver/HttpServer.html) · [Java HTTP client API](https://docs.oracle.com/en/java/javase/21/docs/api/java.net.http/java/net/http/HttpClient.html)
