<!--
Umicom Bits2Banking
File: content/simple-steps/maze.md

PURPOSE:
Write and check movement instructions for a small robot maze.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# 12. Plan a robot’s route

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Draw this grid on paper. Put the robot on `S`. It can move one square at a time, up, down, left or right. `#` is a wall and `E` is the exit.

```text
S . #
. . #
# . E
```

1. Move right. The robot should be in the middle square of the top row.
2. Try another move right. The wall blocks it, so it stays where it is.
3. Move down, down, then right. The robot should now be on `E`.
4. Write down the rule you followed. Check the next square before moving. Keep the current position if the move is blocked.

```text
FOR EACH requested move
    IF the next square is inside the grid and clear
        move to it
    IF the robot is on the exit
        stop
```

Check your instructions from the start. The first right sends the robot to row 1, column 2. The blocked right keeps it there. The last right takes it to row 3, column 3.

[Previous step — Build and test the C program](build-project.md) · [Next — Choose a course guide](course-guides/index.md) · [Full algorithms course](../courses/learning-algorithms/index.html)
