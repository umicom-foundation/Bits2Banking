<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/open-banking-account-access/01-follow-account-access-consent.md

PURPOSE:
Identify the customer, the account provider and an account information provider in the UK v4.0.1 profile.

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

# Follow Account Access Consent

[Course contents](index.md) · [Next lesson · Request a Minimal Account View](02-request-a-minimal-account-view.md)

Identify the customer, the account provider and an account information provider in the UK v4.0.1 profile.

## Name the three roles

Open banking lets authorized providers request access to financial data and services under agreed rules. This course uses the UK Open Banking Limited Read/Write Data API specification v4.0.1 account-information flow. A person using the payment service is a payment service user, called the PSU. Their bank or other account provider is the ASPSP. An account information service provider, called the AISP, requests selected data with their permission.

Consent records the type of information allowed, the time conditions and the account selection made during authorization. An access token is a credential used by an authorized client when making a protected request. Keep account identifiers, consent identifiers and credentials separate in the classroom diagram.

## Follow the process on paper

1. Pretend you are the AISP. In the specification, a POST to /account-access-consents registers an intent and returns a ConsentId. Write TRAIN-C101 on a card. The card represents a request waiting for authorization.
2. Play the account provider and ask the fictional PSU whether they agree. Mark one account, TRAIN-A2, as selected. Keep the approval decision on the bank's side of the drawing.
3. After the profile's authorization flow yields suitable access, GET /accounts identifies the accounts permitted under the consent. On your paper copy, draw a response with only TRAIN-A2.

The profile uses OAuth-based access and a compatible security profile. This exercise follows the responsibilities and state changes on paper. Its permission checks receive a result from the trusted adapter rather than a raw login or token.

## Test one change

Cross out the customer's authorization and leave the original request card in place. Explain why the card alone gives the service no permission to read either account.

- [Open Banking Limited v4.0.1 Account and Transaction API Profile](https://openbankinguk.github.io/read-write-api-site3/v4.0.1/profiles/account-and-transaction-api-profile.html)
- [Open Banking Limited v4.0.1 Account Information resource catalogue](https://openbankinguk.github.io/read-write-api-site3/v4.0.1/resources-and-data-models/aisp/)

[Browser edition](../../../courses/open-banking-account-access/lessons/01-follow-account-access-consent.html)

