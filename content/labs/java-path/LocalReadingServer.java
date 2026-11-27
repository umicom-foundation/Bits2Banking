/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/LocalReadingServer.java
 *
 * PURPOSE:
 *   Teach exact HTTP routing and response checks through a loopback exchange.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.nio.charset.StandardCharsets;
import java.time.Duration;

public class LocalReadingServer {
    static void readings(HttpExchange exchange) throws IOException {
        try (exchange) {
            // The registered context matches a prefix. This exercise accepts one exact path.
            if (!exchange.getRequestURI().getRawPath().equals("/readings")) {
                exchange.sendResponseHeaders(404, -1);
                return;
            }
            if (!exchange.getRequestMethod().equals("GET")) {
                exchange.getResponseHeaders().set("Allow", "GET");
                exchange.sendResponseHeaders(405, -1);
                return;
            }

            // Encode the text before giving the response its exact byte length.
            byte[] body = "{\"north\":20}".getBytes(StandardCharsets.UTF_8);
            exchange.getResponseHeaders().set("Content-Type", "application/json");
            exchange.sendResponseHeaders(200, body.length);
            exchange.getResponseBody().write(body);
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        // Bind to this computer and let the operating system choose an available port.
        InetAddress local = InetAddress.getByAddress(new byte[]{127, 0, 0, 1});
        HttpServer server = HttpServer.create(new InetSocketAddress(local, 0), 0);
        try {
            server.createContext("/readings", LocalReadingServer::readings);
            server.start();
            URI endpoint = URI.create("http://127.0.0.1:" + server.getAddress().getPort() + "/readings");
            Duration limit = Duration.ofSeconds(5);
            try (var client = HttpClient.newBuilder().connectTimeout(limit).build()) {
                var get = HttpRequest.newBuilder(endpoint).timeout(limit).GET().build();
                var answer = client.send(get, HttpResponse.BodyHandlers.ofString());
                System.out.println("GET " + answer.statusCode() + " " + answer.body());

                // Check an unsupported method and a different path as separate outcomes.
                var post = HttpRequest.newBuilder(endpoint).timeout(limit)
                        .POST(HttpRequest.BodyPublishers.noBody()).build();
                var method = client.send(post, HttpResponse.BodyHandlers.discarding());
                System.out.println("POST " + method.statusCode() + " (Allow: "
                        + method.headers().firstValue("Allow").orElse("missing") + ")");
                var nested = HttpRequest.newBuilder(endpoint.resolve("/readings/extra")).timeout(limit).GET().build();
                var route = client.send(nested, HttpResponse.BodyHandlers.discarding());
                System.out.println("GET /readings/extra " + route.statusCode());
            }
        } finally {
            server.stop(0);
        }
    }
}
