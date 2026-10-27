# Derive active, idle and physical K/V payload

**Bits to Banking · Umicom Foundation**  
**Narration and storyboard:** Sammy Hegab

## Learning purpose

Derive active, idle and physical K/V payload. The viewer should be able to distinguish an experimentally testable property from an unmeasured performance assertion.

## Opening

The raw capacity of a store depends on layers, context positions, channels and scalar width.

## Calculation

2 × 2 layers × 4 positions × 8 channels × 4 bytes = 512 bytes. For two active and one idle, 1,024 + 512 = 1,536 physical bytes.

## Storyboard

Use three columns: active reservation, idle retained allocation and combined physical raw bytes. Move one allocation between columns without changing the total.

## Closing question

What memory categories are omitted from the raw K/V figure?

## Viewer exercise

Sketch the lifecycle and state the expected cache budget or lease state at each transition. Reproduce the numerical example before seeing the answer.

*Service to Many Leads to Greatness.*
