# 10. C++: objects, libraries and resource ownership

C++ builds on ideas from C and offers additional tools for organising programs: classes, constructors, destructors, generic containers, algorithms and abstractions that express ownership. In Umicom, the public boundary remains a C ABI; C++ is appropriate behind adapters when its facilities or external libraries provide a clear benefit.

We will implement a small note journal. The program collects notes in memory, then saves them to a file. It also shows why C++ resource management differs from manually calling `fclose` in C.

## Write `notes.cpp`

```cpp
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class NoteJournal {
public:
    void Add(const std::string& note) {
        if (!note.empty()) {
            notes_.push_back(note);
        }
    }

    bool Save(const std::string& filename) const {
        std::ofstream output(filename, std::ios::app);
        if (!output) {
            return false;
        }
        for (const std::string& note : notes_) {
            output << note << '\n';
        }
        output.flush();
        return output.good();
    }

private:
    std::vector<std::string> notes_;
};

int main() {
    NoteJournal journal;
    journal.Add("Plan the Umicom task board");
    journal.Add("Review the framework module catalogue");

    if (!journal.Save("notes.txt")) {
        std::cerr << "Unable to save notes.\n";
        return 1;
    }
    std::cout << "Notes saved.\n";
    return 0;
}
```

Compile and run it using a C++ compiler:

```powershell
g++ -std=c++20 -Wall -Wextra -Wpedantic -o notes-cpp.exe notes.cpp
.\notes-cpp.exe
```

The code uses C++20-compatible features; you do not need experimental language functionality to understand the example.

## Read the object model

`class NoteJournal` defines a type combining **state** and **operations**. The state is `notes_`, a `std::vector` containing `std::string` values. A vector manages a growable collection: it allocates more memory when needed and releases that memory when its lifetime ends. `Add` and `Save` are member functions.

`public` identifies operations that callers can use. `private` hides implementation details. This is **encapsulation**: other code does not need to know how the journal stores its notes to request that a note be added.

`const std::string&` passes a string by reference without copying it and promises not to modify that argument through the reference. The `Save` method is itself `const`, meaning it does not modify the visible state of its journal object.

## RAII and destructors

The `std::ofstream` object opens a file when it is constructed. When the `Save` function returns, the object is destroyed and its resources are released automatically. This is **Resource Acquisition Is Initialisation (RAII)**. It reduces the risk of forgetting a cleanup operation when several return paths exist.

That automatic cleanup does not mean every error disappears. The program checks whether the stream opened successfully and whether output operations succeeded. The result is still the caller's responsibility to interpret. A production file-save path also needs to consider flush and close failures, atomic replacement, permissions and recovery.

## Composition before inheritance

For a larger application, we can give `NoteJournal` a storage dependency rather than embedding every database and file operation inside the same class. A storage adapter might save to a local file, SQLite or a remote service. That is **composition**: building one useful unit by combining others through defined interfaces.

Umicom Framework prefers explicit module contracts and controlled adapters. C++ classes and exceptions should stay inside a private implementation rather than crossing the stable C interface used by C modules and other programming languages.

## Compare with C

In C, we used a `char` array with a fixed capacity and explicitly opened and closed the file. In C++, `std::string` manages string storage and `std::vector` manages a collection. You still need to understand ownership: resource safety is achieved through a clear lifetime model, not by ignoring memory.

## Check your understanding

What information is hidden in `private`? Why is RAII useful when a function has several possible exits? What would be the benefit of a storage adapter shared between a notes application and a Kanban board?

**Next:** [Use Java for a financial record](11-java.md).
