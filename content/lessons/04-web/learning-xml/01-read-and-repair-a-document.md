<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-xml/01-read-and-repair-a-document.md

PURPOSE:
Read and repair an XML document

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read and repair an XML document

## Before you begin
Open the supplied labs/build-tools/jvm-identity/pom.xml as text. Keep an unchanged copy for comparison. Use a plain text editor that preserves UTF-8 and shows line numbers. You can complete the first reading exercise without installing Maven or executing a build.

## Follow the tree
An XML document has one document element. Start and end tags nest in order, and attribute values use quotes. The following small teaching record is well formed:

~~~xml
<measurement unit="g">
  <value>80000</value>
  <note>Morning &amp; evening example</note>
</measurement>
~~~

The element names carry application-defined meaning. XML syntax alone does not know that g means grams or that value is supposed to contain an integer. The entity reference amp represents an ampersand in text; a literal ampersand needs appropriate escaping.

## Read a real project
Find project in the POM, then locate properties, dependencies and build beneath it. Match every closing tag to its opening tag. Notice that comments are separate from element content and that whitespace between structural elements makes the file readable.

## Exercise
In a scratch copy, close measurement before closing value. Explain the crossed nesting and repair it. Next remove the quotes from unit and repair that error. Finally replace 80000 with unknown. Explain why the last document can remain well formed even though the application cannot interpret its value as an integer.

Expected conclusion: syntax checks answer whether a document follows XML rules. An application's validation contract answers whether the data makes sense for that application. A file extension does not establish either result.

## Recover from an error
Use the first parser line and column as a starting point, then examine preceding tags and quotes. Later diagnostics can be consequences of the first malformed construct. Keep the original document when practising repairs, and never treat changing an expected result as a syntax fix.

[W3C XML specification](https://www.w3.org/TR/xml/)

[Course contents](index.md) · [Next lesson](02-understand-namespace-identity.md)
