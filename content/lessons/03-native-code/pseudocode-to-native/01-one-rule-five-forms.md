![Umicom](../../../assets/branding/umicom-wordmark.svg)

# 1. Write one rule in five forms

Suppose an image row is six pixels wide. Our practice rule stretches exactly six-pixel rows by a factor of seven. Other row widths use a factor of one. Work the result out on paper before running the program.

## Run the executable pseudocode

Save the following as `width.ump` in your practice folder. Use a local Umicom C build that provides the `pseudocode` command. `LET` introduces a name and its starting value. `IF` asks a yes-or-no question, and the lines inside its block run only when the answer is yes. `RETURN` supplies the final value. A semicolon ends each simple statement.

```text
BEGIN
    LET width = 6;
    LET scale = 1;
    IF (width == 6) THEN BEGIN
        scale = 7;
    END
    RETURN width * scale;
END
```

Open a terminal in your practice folder. Supply the full executable path if `umicom-c` is outside your `PATH`.

```powershell
umicom-c pseudocode width.ump --step
```

Press Enter to advance one source statement, or type `run` to finish. The result is 42. Change the initial `width` to 5 and repeat. Predict the result and which line will be skipped. [Umicom C source repository](https://github.com/umicom-foundation/umicom-c)

## Find the same rule in C, D and BASIC

C and D both keep the `==` comparison, the braces around the body and `return` as an explicit result. This C program also runs under the checked C profile with `umicom-c interpret`.

```c
int main(void)
{
    int width = 6;
    int scale = 1;
    if (width == 6) {
        scale = 7;
    }
    return width * scale;
}
```

```d
int main()
{
    int width = 6;
    int scale = 1;
    if (width == 6) {
        scale = 7;
    }
    return width * scale;
}
```

This FreeBASIC example uses `Dim` for a declaration and calls the width `rowWidth`. The `=` in the `If` line asks whether two values are equal. The `=` inside the branch makes an assignment. `End If` closes the branch.

```basic
Dim rowWidth As Integer = 6
Dim rowScale As Integer = 1
If rowWidth = 6 Then
    rowScale = 7
End If
End rowWidth * rowScale
```

The standalone C, D and BASIC forms return the number as the process result. The Umicom interpreter reports a successful execution with its own status and prints the integer result separately.

## Read the x86-64 idea

A register is a small storage location in the CPU. In this Intel-syntax fragment, `cmp` compares two values and sets flags. `jne` jumps when the comparison finds a difference. At `done`, multiplication leaves the result in `eax`. These exact inputs fit the available result register. A native implementation that accepts arbitrary inputs needs the same overflow rule as the source language.

```asm
mov eax, 6       ; width
mov edx, 1       ; scale
cmp eax, 6
jne done
mov edx, 7
done:
imul eax, edx    ; result for this small example
```

<details>
<summary>Worked answer for width five</summary>

The result is five. The comparison is false, so the assignment inside the block is skipped and `scale` stays one. The program returns five times one.

</details>

[Course outline](index.md) · [Next lesson: Follow the execution](02-from-words-to-machine-operations.md) · [Umicom icon](../../../assets/branding/umicom-icon.svg)
