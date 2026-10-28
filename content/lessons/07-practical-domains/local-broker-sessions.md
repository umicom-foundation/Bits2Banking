# Understanding local broker sessions

This lesson connects programming concepts to the startup screen in Umicom Trader. You do not need a broker account, money or a network connection to follow the code example.

A **broker** is a business that provides access to financial markets. A **client application** is software that asks another program or service to do something. Umicom Trader is a client of a local broker program. A **session** is the period during which programs exchange messages with a particular identity and set of permissions.

## Four questions that software must keep separate

| Question | What answers it? | What does not answer it? |
| --- | --- | --- |
| What does the user want? | Choosing Guest, Paper or Live | A chart colour |
| Who has signed in? | The broker's authentication process | A local workspace username |
| Is a connection ready? | The messages received on that connection | The fact that a window is open |
| May this application send an order? | An implemented, authorised execution service | A selected Live label |

**Authentication** means checking an identity, often with a password and another factor. **Authorisation** means deciding what that identity or application is allowed to do. Reading account information and placing an order are different permissions.

The current Umicom broker inspector reads observations; it does not send, change or cancel orders. The main chart workspace uses simulation. Opening either window does not turn fictional prices into market observations.

## Follow the message path

```text
You select a mode in Umicom Trader
                 |
                 v
A local connection plan is created
                 |
                 v
You authenticate in the broker program
                 |
                 v
You explicitly connect the Umicom inspector
                 |
                 v
The inspector receives account and market observations
```

Guest stops before broker authentication: it opens a local simulation workspace. A Paper broker session is an external testing environment. A Live broker session refers to a real account, even when the current software only reads information.

The connection plan stores a mode, a program choice, a port and a client ID. It has no field for a broker password or authentication code.

## Read a real Framework call

The complete example is [access_plan.c in Umicom Framework](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/ibkr_connection/access_plan.c). Its public contract is [access_plan.h](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/broker_connectivity/access_plan.h).

```c
UmiBrokerAccessPlan plan;
UmiStatus status = UmiBrokerAccessPlanCreate(UMI_BROKER_ACCESS_PAPER, &plan);
```

Read these two lines slowly:

1. `UmiBrokerAccessPlan` names a structure: a group of related values. `plan` is the name we give one such group.
2. The semicolon ends the declaration. At this point we have not yet established valid values for the plan.
3. `UmiBrokerAccessPlanCreate` is a function: a named piece of code that performs a task.
4. Parentheses enclose its inputs. The comma separates them.
5. `UMI_BROKER_ACCESS_PAPER` is a named choice from an enumeration. Using a name makes the purpose clearer than an unexplained number.
6. `&plan` supplies the address of our structure. It tells the function where to write its result.
7. `UmiStatus` describes the result of an operation. The caller must check for `UMI_STATUS_OK` before using the new plan.

Passing an address does not give a function unlimited ownership. The caller owns this structure. Creation fills it during the call; it does not keep the address for later use.

## Understand the numbers

A **port** is a numbered endpoint used by communicating programs. A **client ID** identifies one API connection to the broker program. Neither is a password.

The example creates these defaults:

| Mode | Program | Port | Client ID |
| --- | --- | --- | --- |
| Guest | TWS default choice, unused | 0, meaning no endpoint | 0, unused |
| Paper | TWS | 7497 | 35 |
| Live | TWS | 7496 | 35 |

Selecting IB Gateway changes the default Paper and Live ports to 4002 and 4001. Real installations can use different configured ports. A port number is therefore a setting, not evidence of an authenticated account type.

The adapter uses `127.0.0.1`, the loopback address. This directs the connection to another program on the same computer.

## Observe a refusal

```c
UmiIbkrConnectionOptions options;
UmiStatus status = UmiBrokerAccessPlanConnectionOptions(&plan, false, &options);
```

Here `false` means that the caller has not acknowledged Live access. Paper can produce read-only connection options. Guest returns `UMI_STATUS_UNAVAILABLE`, because it has no broker endpoint. Live without acknowledgement returns `UMI_STATUS_PERMISSION_DENIED`.

A refused operation leaves `options` unchanged. In this example it has no useful initial value, so the caller must not read it after a refusal. The full program checks the status instead.

None of these functions opens a socket. A **socket** is an operating-system resource used to exchange network messages. Separating planning from opening a socket lets a user review settings before anything connects.

## Run the local example

Use an already configured Framework build with the broker connection component enabled. In a PowerShell terminal at the Umicom Applications checkout:

```powershell
cmake --build --preset windows-ucrt64-all-debug --target umicom-broker-access-example --parallel 2
& ".\build\windows-ucrt64-all-debug\bin\umicom-broker-access-example.exe"
```

Stop if the build reports an error. If the target is unknown, configure the updated source with the project's documented preset first. The expected final line is:

```text
Plans inspected locally. No broker connection was opened.
```

The program prints defaults and checks expected refusals. It does not authenticate, read balances or place orders.

## Try these questions

1. Why can Guest use the workspace without a broker password?
2. If a Live window is visible, does that prove it is connected?
3. Why should a newly opened Live window require acknowledgement again?
4. Why must the caller check the function's result before reading `options`?
5. Could changing a port turn a simulation into a correctly authorised live order service?

Answers: Guest uses local simulation; a window is only presentation; a previous acknowledgement belongs to a previous connection decision; a failed operation has not produced valid output; and an endpoint setting cannot supply execution behaviour or authorisation.

Continue with [market data, orders and execution](33-trading-platforms.md), [accounts](30-accounts.md), or the [business and financial systems index](index.md). For the native UI workflow, read [Choosing a session in Umicom Trader](https://github.com/umicom-foundation/umicom-trader-module/blob/main/docs/choosing-a-trader-session.html).
