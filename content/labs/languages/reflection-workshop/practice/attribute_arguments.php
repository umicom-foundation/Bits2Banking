<?php
/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/practice/attribute_arguments.php
 *
 * PURPOSE:
 *   Read the declared arguments of a present PHP property attribute and report its absence.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

declare(strict_types=1);

#[Attribute(Attribute::TARGET_PROPERTY)]
final class PublicLabel
{
    public function __construct(public string $text)
    {
    }
}

final class Reading
{
    #[PublicLabel('Degrees Celsius')]
    public int $degrees;

    public string $station;
}

$record = new ReflectionClass(Reading::class);
foreach (['degrees', 'station'] as $name) {
    $property = $record->getProperty($name);
    $labels = $property->getAttributes(PublicLabel::class);
    if ($labels === []) {
        printf("%s: no PublicLabel\n", $name);
        continue;
    }

    // The fixture uses one positional argument. Reading the attributes'
    // declared arguments keeps the PublicLabel constructor out of the report.
    $declared = $labels[0]->getArguments();
    printf("%s: %s\n", $name, $declared[0]);
}
