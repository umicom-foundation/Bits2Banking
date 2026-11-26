<!--
Umicom Bits2Banking
File: content/simple-steps/python.md

PURPOSE:
Run the same coffee time calculation in Python.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Convert brew time in Python

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Save these two lines in `coffee.py` in a practice folder.

   ```python
   minutes = 4
   print(minutes * 60, "seconds")
   ```

   The first line names the brew time. The second line multiplies it by 60 and shows the number with its unit.

2. With Python 3 installed, open PowerShell in that folder. Run the next command. If your installation uses `python` in PowerShell, use `python coffee.py`.

   ```powershell
   py -3 coffee.py
   ```

3. Check for `240 seconds`. Change `4` to `3`, save and run the command again. The new result is `180 seconds`.

[Compare with C](c.md) · [Full Python course](../courses/learning-python/index.html) · [Guide to the Python course](course-guides/learning-python.md)

<!-- Earlier demonstration code is retained for comparison. The active steps use an everyday task and check its result.

```python
print(2 + 1)
```

```powershell
py -3 apples.py
```

```sh
python3 apples.py
```
-->
