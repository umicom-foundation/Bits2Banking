<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-xml/02-understand-namespace-identity.md

PURPOSE:
Understand XML namespace identity

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Understand XML namespace identity

## Before you begin
Keep the Maven POM and the synthetic measurement example open. Locate xmlns on the project element before reading any namespace-aware lookup code. The namespace URI identifies a vocabulary; it is not an instruction to download or execute content from that address.

## Compare names precisely
A namespace-aware element name combines a namespace name and a local name. Two different prefixes can refer to the same namespace, while the same prefix can mean different things in different scopes.

~~~xml
<a:measurement xmlns:a="urn:umicom:learning:measurement" unit="g">
  <a:value>80000</a:value>
</a:measurement>
~~~

Renaming a to m everywhere in this example preserves the expanded element names when the binding stays the same. Changing the namespace URI changes their identity. The unprefixed unit attribute has no namespace merely because its owning element has one.

## Follow the Maven default
The POM uses a default namespace, so its unprefixed elements belong to the Maven vocabulary. The xsi prefix identifies schema-instance attributes. Do not remove namespace declarations just to make a naive local-name-only query find an element.

## Exercise
Write the namespace URI and local name for project, modelVersion and the schemaLocation attribute in the lab POM. Then create a second synthetic element named value in another namespace and explain why a parser must not confuse it with the measurement value.

Expected conclusion: prefixes are convenient spellings, whereas the resolved namespace and local name determine element identity. An import service should admit the expected vocabulary explicitly before interpreting fields.

## Diagnose a missing lookup
If a query finds no nodes, compare the query's namespace binding with the document's actual binding. A visible tag spelling by itself does not prove that a namespace-aware query names the same element.

[W3C Namespaces in XML](https://www.w3.org/TR/xml-names/)

[Course contents](index.md) · [Previous lesson](01-read-and-repair-a-document.md) · [Next lesson](03-separate-parsing-from-application-validation.md)
