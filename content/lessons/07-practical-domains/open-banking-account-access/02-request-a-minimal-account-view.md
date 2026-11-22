<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/open-banking-account-access/02-request-a-minimal-account-view.md

PURPOSE:
Map one read permission to a small account response and preserve the access decision in a review trace.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom Foundation" width="220">
</picture>

# Request a Minimal Account View

[Course contents](index.md) · [Previous lesson · Follow Account Access Consent](01-follow-account-access-consent.md) · [Next lesson · Check the Trusted Consent in C23](03-check-consent-in-c.md)

Map one read permission to a small account response and preserve the access decision in a review trace.

## Choose the minimum data

The v4.0.1 profile lists ReadAccountsBasic and ReadAccountsDetail as separate permissions. The access token's accounts scope and the permissions recorded on the consent play distinct roles. For the exercise, take a verified read context, choose the account permitted by the consent, and return only the two fields in the classroom projection.

~~~json
{
  "trainingConsent": "TRAIN-C101",
  "permission": "ReadAccountsBasic",
  "selectedAccount": "TRAIN-A2",
  "preview": {"account": "TRAIN-A2", "label": "Practice savings"}
}
~~~

The property names above are from a teaching projection. Consult the official Accounts resource for actual response fields. A request for transactions or a payment initiation is a different operation with its own permission and profile.

## Keep a small worksheet

- Approved, within time and TRAIN-A2 selected. Record permit with the simulated operation and projection size.
- TRAIN-A3 requested under the same consent. Record deny and return no account data.
- Granted access removed in the account provider's practice register. Record deny for TRAIN-A2 and require a fresh permitted request before providing data.
- Request at the consent expiry boundary. In our classroom rule a grant is valid up to but excluding that time. Record deny.

A review entry can retain the operation, outcome and a safe trace key. Live tokens, secrets and full customer payloads belong outside the troubleshooting log. The native practice project should keep the decision separate from the caller that assembles a response.

- [Open Banking Limited v4.0.1 Account and Transaction API Profile](https://openbankinguk.github.io/read-write-api-site3/v4.0.1/profiles/account-and-transaction-api-profile.html)
- [Open Banking Limited v4.0.1 Account Information resource catalogue](https://openbankinguk.github.io/read-write-api-site3/v4.0.1/resources-and-data-models/aisp/)
- [Practical Web and Data Foundations](../../../courses/practical-web-and-data-foundations/index.html)

[Browser edition](../../../courses/open-banking-account-access/lessons/02-request-a-minimal-account-view.html)

