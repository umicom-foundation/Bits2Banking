<?php
/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/property_catalogue.php
 *
 * PURPOSE:
 *   Catalogue public PHP property declarations and their type metadata.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

declare(strict_types=1);

final class Reading
{
    public string $station;
    public readonly int $degreesC;
    private string $internalLabel;
}

// Build a catalogue of public declarations, without creating a Reading
// instance or reading values from any property.
$properties = (new ReflectionClass(Reading::class))
    ->getProperties(ReflectionProperty::IS_PUBLIC);
$byName = [];
foreach ($properties as $property) {
    $byName[$property->getName()] = $property;
}
ksort($byName, SORT_STRING);

// Handle a named type explicitly. A union or missing type needs its own
// display rule before it belongs in this particular report.
foreach ($byName as $name => $property) {
    $type = $property->getType();
    if (!($type instanceof ReflectionNamedType)) {
        fwrite(STDERR, "Expected one named type for $name\n");
        exit(1);
    }

    $declaration = $property->isReadOnly() ? 'declared readonly' : 'ordinary declaration';
    printf("%s: %s, %s\n", $name, $type->getName(), $declaration);
}
