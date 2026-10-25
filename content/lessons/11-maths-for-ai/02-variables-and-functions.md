# Mathematics for AI — Unit 2: Variables, Expressions and Functions

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## What you will learn

Read a mathematical expression as a sequence of ordinary operations, substitute a number for a variable, evaluate a function, and recognise powers and square roots in formulas used by language models.

## 1. A letter names a changing value

A programming variable such as `tokenCount` holds a value. Mathematicians often use a shorter symbol, such as `x`. The symbol does not make a calculation more complicated; it lets one relationship describe several inputs.

Consider:

**Calculation:** `f(x)=2x+1.`

The name `f` labels the function, and `f(x)` means **the result of applying rule f to input x**. Writing `2x` is shorthand for `2× x`; it does not mean the two-character string `2x`.

If `x=3`, then `f(3)=2×3+1=6+1=7`. If `x=5`, then `f(5)=11`. Nothing about the rule changed.

## 2. Expression versus equation

An *expression* such as `2x+1` gives a value after the variable is supplied. An *equation* states that two expressions are equal, as in `f(x)=2x+1`. Evaluation means carrying out the arithmetic; it does not mean learning the correct answer from data.

Function notation can also be chained. Let `g(x)=x^2`. Then `g(f(3))=g(7)=49`. The inner function `f` runs first; the outer function `g` receives its result. This simple pattern anticipates a neural network's sequence of transformations.

## 3. From symbols to C23

The **educational expression** `2.0F * input + 1.0F` has the same arithmetic meaning as `2x+1`. In C, the `*` operator explicitly means multiplication. `input` is a variable name, and `2.0F` denotes a `float` literal. Production numerical operations, memory management and model execution must use their existing Umicom Framework implementations; a notation example is not a replacement library.

## 4. Squares, roots and scaling

A superscript `2` means “multiply by itself”: `3^2=3×3=9`. The principal square root asks for a **nonnegative** number whose square equals the argument: `√9 = 3`. For nonnegative `d`, `√d` is a well-defined scale factor.

In scaled dot-product attention, a score is commonly divided by `√dₖ`, where `d_k` denotes the number of channels per query/key head. If `d_k=16`, the divisor is `4`. The purpose of scaling is to keep dot-product magnitudes more manageable as vector dimension increases; it does not guarantee correct attention by itself.

## 5. Function chains in an LLM

A token representation may be projected into a **query**, compared with **keys** by a score function, passed through **softmax** to form nonnegative weights, and used to combine **values**. Each step maps inputs to outputs. Understanding a function as a repeatable mathematical rule is the foundation for reading the more complicated equations later.

## 6. Practice

1. For `g(n)=3n-2`, calculate `g(4)`.
2. For `h(x)=x^2+2`, calculate `h(-3)`. Why does the square become positive?
3. Calculate `f(f(2))` when `f(x)=2x+1`.
4. If an attention head has `d_k=64`, calculate `√dₖ`.

<details>
<summary>Show worked answers</summary>

1. `3×4-2=12-2=10`.
2. `(-3)×(-3)+2=9+2=11`. The product of two negative numbers is positive.
3. First `f(2)=5`, then `f(5)=11`.
4. `√64 = 8`.

</details>

## 7. Further study

Write the rule `p(t)=t/4` in words, and then explain whether the variable `t` must mean *time*. A symbol has meaning only when the surrounding problem defines it.

**Companion reading:** [Illustrated Unit 2](../../courses/maths-for-ai/lessons/02-variables-and-functions.html) · [Previous: Numbers and Percentages](01-counting-ratios-and-percentages.md) · [Next: Vectors and Dot Products](03-vectors-and-dot-products.md).
