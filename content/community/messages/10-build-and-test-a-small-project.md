# Build and test a small notes project

Now we will build a small project. From its folder, type -> cmake -S . -B build -G Ninja
If that succeeds -> cmake --build build
Then -> ctest --test-dir build --output-on-failure --no-tests=error
Configure, build and test are separate steps. Stop and read the first failure before continuing.

[Full steps, explanations and recovery help](../lessons/10-build-and-test-a-small-project.md)
