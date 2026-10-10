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
