# 171. Connect the nonblocking reactor to Umicom's service boundaries

**Learning objective:** Recognise which ideas transfer from the educational C23 HTTP server to reusable Umicom Framework components and which implementations should not be copied.  
**Prerequisites:** [Chapter 166](166-http-service-ownership-in-umicom.md) and [Chapters 167–170](167-why-nonblocking-io-matters.md).

## 1. An event loop is an execution mechanism, not a business service

A banking dashboard can present a trade summary, a treasury balance and a list of completed payments. A nonblocking socket layer only receives and transmits bytes. It must not be given authority to post a journal, submit an order or read an arbitrary database table. Those actions require separate authenticated services, checked business commands, audit and authorised data ownership.

In the Bits2Banking laboratory, the connection slot owns one socket and its outgoing bytes. An HTTP parser checks syntax; a route service owns registered handlers; a static-root service owns checked read-only files. The reactor borrows the route service and static root. None of these components owns a trading book, a customer account or a payment instruction.

This aligns with the reusable boundaries in Umicom Framework. The production web server should own network listeners and native I/O; application services should own business-state transitions. Applications should consume Framework contracts rather than reproduce socket infrastructure inside each product.

## 2. Relate the lifecycle to Master and Slave Controllers

The **Master Controller** coordinates startup, readiness and shutdown. A **Slave Controller** owns the bounded business module it supervises. A web-service component may implement a listener lifecycle, but it does not become the owner of unrelated application resources. The same principle appears in a market-data subscriber, a Data Server repository and a supervised child process.

For example, when a market-data request is cancelled, a component must not free memory still referenced by a pending native completion. The Update 28 reactor's single owner makes this easy to visualise: close a socket only in the slot's release path. A future multithreaded version would require explicit synchronization, lifetime tokens and cancellation acknowledgements before releasing shared resources.

## 3. Reuse the public contracts, not the teaching implementation

Read these existing sources to compare interface design:

- [Umicom Framework Web Server API](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/server.h)
- [Umicom Framework static file contracts](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/static_files.h)
- [Umicom Framework local HTTP example](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/web/local_service.c)
- [Umicom Kernel process-owned file services](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/PROCESS_FILE_SERVICES.md)

The precise Framework ABI, function signatures and OS services must be checked against the current source before integration. The small server here intentionally does **not** attempt to speak directly to Umicom Kernel sockets or imply that the native Kernel implements a complete TCP/IP user-space hosting environment.

## 4. From a request slot to a reusable service capability

To design a professional shared web capability, document these contracts before choosing a network backend:

| Contract | Questions to answer |
|---|---|
| Listener ownership | Who opens, binds, listens, stops and closes? Which interfaces can be bound? |
| Request admission | How many clients, headers and pending operations are allowed? How is capacity pressure reported? |
| Identity and permissions | Who may call a handler and view its data? What is the security context? |
| Parsing and framing | Which HTTP versions, headers and body formats are supported? How are ambiguous lengths refused? |
| Response delivery | Which bytes are locally accepted, queued, acknowledged or failed? |
| Shutdown | Who stops admission? What is the grace period and final cleanup signal? |
| Observability | How are timed-out, refused and incomplete operations represented without exposing secrets? |
| Testing | Which deterministic policy, socket integration, fuzzing and Windows/Linux checks prove the chosen contract? |

Our reactor implements only a deliberately narrow local subset. Its eight-slot limit, single-threaded route dispatch and loopback-only binding are educational design choices, not general Framework policy.

## 5. A concrete financial example

Consider a fictional account-monitoring dashboard. A browser sends `GET /api/account-summary` and the web layer validates its HTTP envelope. The request then enters an authenticated application service, where identity and account permissions are checked before any query is executed. A Data Server service retrieves authorised state and returns a bounded response. The web layer serialises that response and sends it through the socket reactor. A completed local send is never recorded as a confirmed transfer, payment or trade.

To use the Umicom patterns correctly, the ledger and payment services remain sole owners of their business transactions. Neither the HTTP route nor the GUI can bypass the checked command interface. An integration engine can publish a business event only after authoritative state has been committed; a socket completion callback alone must not generate a financial event.

## 6. Future development: parallel workers belong behind contracts

A later lesson may add asynchronous file completion, a thread pool or a scalable readiness backend. Before that stage, the project needs explicit contracts for handoff ownership, stable generation identifiers, bounded queues, priority and fairness, shutdown barriers and cross-thread route access. Merely creating eight threads because the reactor supports eight connections would conceal rather than solve those problems.

The Update 27 four-record admission model is useful for this next step because it distinguishes waiting from active work and refuses stale completions. It still needs to be integrated with real descriptors and concurrency rules before it can act as a genuine worker scheduler.

**Capstone exercise:** Design a small authenticated, **simulated** treasury reporting API on paper. Identify the HTTP admission limit, the responsible Slave Controller, the read-only query contract, the identity check, the response limit, the timeout policy and the audit fields. Mark precisely which services may mutate a ledger. Finally draw the shutdown sequence from the Master Controller through the web listener, pending responses, Data Server and audit service. Do not implement money movement as a side effect of a GET request.

**Next chapter group:** From portable `select()` readiness to a tested asynchronous execution service: fairness, bounded work handoff and explicit multithreaded lifetime contracts. Production web functionality remains Framework-owned.
