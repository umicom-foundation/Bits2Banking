<img src="../../../content/assets/branding/umicom-wordmark.svg" alt="Umicom">
[Umicom icon](../../../content/assets/branding/umicom.ico)

# Review an HTTP HEAD response

This offline C23 lab helps you trace an optional representation length from a worker to the headers an HTTP client sees. It formats a small teaching fixture and performs no network operations.

1. Configure and build from the Bits2Banking repository root.

   ```powershell
   cmake -S ./labs/framework/fastcgi-head-review -B ./build/fastcgi-head-review -G Ninja
   cmake --build ./build/fastcgi-head-review
   ```

2. Run all six cases and check that they pass.

   ```powershell
   ctest --test-dir ./build/fastcgi-head-review --no-tests=error --output-on-failure
   ```

3. Compare `known-zero` and `unknown` in [the fixture](test_head_review.c). They both send no document bytes. Only the first sends a length value.
4. If a fixture fails, inspect the error name and compare the full expected response with the formatted bytes. Check that the header lines end with CR and LF and that the final blank line is followed only by the C string terminator.

[Back to the WebServer course](../../../content/courses/building-a-web-server-in-c/index.html)

