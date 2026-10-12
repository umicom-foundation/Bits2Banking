"""Socket-level verification of the *native C23* optional nonblocking reactor.

This is test automation, not a Python HTTP server or new application runtime.
Only loopback sockets are used. No network requests leave the test machine.
"""
import os
import signal
import socket
import subprocess
import sys
import time
from pathlib import Path

HOST = "127.0.0.1"


def choose_port():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.bind((HOST, 0))
        return sock.getsockname()[1]


def connect(port):
    client = socket.create_connection((HOST, port), timeout=3)
    client.settimeout(4)
    return client


def exchange(port, request):
    with connect(port) as client:
        client.sendall(request)
        data = bytearray()
        while True:
            part = client.recv(32768)
            if not part:
                return bytes(data)
            data.extend(part)
            if len(data) > 2 * 1024 * 1024:
                raise AssertionError("response exceeded test budget")


def require(response, expected):
    assert response.startswith(expected), repr(response[:256])


def run(server, root):
    port = choose_port()
    kwargs = {}
    if os.name == "nt":
        kwargs["creationflags"] = subprocess.CREATE_NEW_PROCESS_GROUP
    process = subprocess.Popen(
        [server, "--port", str(port), "--root", root, "--routes", "--nonblocking"],
        stdout=subprocess.PIPE, stderr=subprocess.PIPE, **kwargs)
    try:
        for _ in range(60):
            if process.poll() is not None:
                raise AssertionError("native server exited during startup")
            try:
                with connect(port):
                    break
            except OSError:
                time.sleep(0.05)
        else:
            raise AssertionError("native server did not bind loopback")

        # A client that has sent only half a header must not block a second
        # client, even though the service has no worker threads.
        with connect(port) as slow:
            slow.sendall(b"GET /health HTTP/1.1\r\nHost: localhost\r\n")
            begin = time.monotonic()
            result = exchange(port, b"GET /health HTTP/1.1\r\nHost: localhost\r\n\r\n")
            require(result, b"HTTP/1.1 200")
            assert time.monotonic() - begin < 2.0, "slow peer blocked reactor"

            # Original static-file and registered-route behaviour is retained.
            index = exchange(port, b"GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n")
            require(index, b"HTTP/1.1 200")
            header, separator, body = index.partition(b"\r\n\r\n")
            assert separator and body, "static response missing a body"
            tag = None
            for line in header.split(b"\r\n"):
                if line.lower().startswith(b"etag: "):
                    tag = line[6:]
            assert tag and tag.startswith(b'W/"'), "weak ETag missing"
            conditional = exchange(port,
                b"GET /index.html HTTP/1.1\r\nHost: localhost\r\nIf-None-Match: " +
                tag + b"\r\n\r\n")
            require(conditional, b"HTTP/1.1 304")
            assert conditional.endswith(b"\r\n\r\n"), "304 sent a body"
            head = exchange(port, b"HEAD /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n")
            require(head, b"HTTP/1.1 200")
            assert head.endswith(b"\r\n\r\n"), "HEAD sent a body"
            route = exchange(port, b"GET /api/courses HTTP/1.1\r\nHost: localhost\r\n\r\n")
            require(route, b"HTTP/1.1 200")
            missing = exchange(port, b"GET /does-not-exist.xyz HTTP/1.1\r\nHost: localhost\r\n\r\n")
            require(missing, b"HTTP/1.1 404")
            # The slow peer completes after a syntactically valid terminator.
            slow.sendall(b"\r\n")
            assert slow.recv(1024).startswith(b"HTTP/1.1 200")

        # No indefinite retention of a slow header reader.
        with connect(port) as idle:
            idle.sendall(b"GET /health HTTP/1.1\r\nHost: localhost\r\n")
            time.sleep(3.6)
            assert idle.recv(1) == b"", "idle deadline did not release peer"

        if os.name != "nt":
            # POSIX signal handler requests quiescence; outstanding slots are
            # reclaimed before the listener exits. Windows Ctrl+C is checked
            # separately from an interactive PowerShell session.
            process.send_signal(signal.SIGINT)
            process.wait(timeout=13)
            assert process.returncode == 0, "graceful shutdown failed"
    finally:
        if process.poll() is None:
            process.terminate()
            try:
                process.wait(timeout=5)
            except subprocess.TimeoutExpired:
                process.kill()
                process.wait(timeout=3)
        # Pipes are read only after termination so the server's short startup
        # messages cannot fill the pipe and alter its scheduling.
        stdout, stderr = process.communicate(timeout=3)
        if process.returncode not in (0, -signal.SIGTERM, 1):
            sys.stderr.write(stderr.decode("utf-8", "replace"))
            raise AssertionError(f"unexpected native exit {process.returncode}")
        if not stdout.startswith(b"Bits2Banking nonblocking"):
            raise AssertionError("nonblocking mode did not start")


if __name__ == "__main__":
    if len(sys.argv) != 3 or not Path(sys.argv[2]).is_dir():
        sys.exit("usage: test_nonblocking_integration.py SERVER_EXECUTABLE SAMPLE_SITE")
    run(sys.argv[1], sys.argv[2])
    print("nonblocking loopback integration: passed")
