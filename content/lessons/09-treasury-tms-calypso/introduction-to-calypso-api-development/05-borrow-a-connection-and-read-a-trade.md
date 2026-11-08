# Borrow a connection and read one trade

## Connection ownership

DSConnection gives a client access to remote services. The supplied guide demonstrates ConnectionUtil for applications that establish their own session. An extension inside an existing application often receives a session instead. That difference determines who may disconnect it.

ClassicTradeReader borrows a non-null DSConnection. It neither connects nor disconnects. Authentication, authorization and timeout configuration belong to the host. This avoids terminating a shared session when one lesson operation ends.

## Follow the real boundary

~~~java
Trade trade = connection.getRemoteTrade().getTrade(id);
result.add(new Identity(id,
    trade == null ? null : Long.valueOf(trade.getId())));
~~~

These calls are based on the guide's remote-client examples. The complete [Java source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/java/calypso-classic-readonly/ClassicTradeReader.java) compiles only when the licensed SDK supplies the matching contract.

The adapter copies identity into an owned result. It does not return a mutable vendor Trade for unrelated code to modify. It deliberately omits product-specific fields: a trade's amount, settlement currency and pricing currency are not interchangeable concepts.

## Walk through the outcomes

For an approved ID, compare the returned identity with the authorized application view. If no object is returned, preserve that absence. Do not label it unauthorized or nonexistent without documented server behaviour. If the service throws, let the operation fail; an empty successful list would hide a connectivity or permission problem.

No save, action or event acknowledgement occurs. Reading a trade still requires an approved account and data scope.

## Exercise and answer

Two panels share the host's DSConnection. Panel A finishes its query and disconnects. Panel B then fails. Where is the ownership error? Answer: A treated a borrowed connection as an owned connection. The host should manage the shared lifetime; A should release only its own local results.

## Verification

Compile first, then have the owner run one approved read in a non-production environment. Capture release, patch, JAR identities and the observed outcome. This lesson supplies source, not evidence of a completed remote call.

[Course contents](index.md)
