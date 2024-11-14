#include <iostream>
#include <vector>
#include <string>
#include "SpellChecker.h"

void runSpellCheckerInterface() {
    std::vector<std::string> wordList = {"apple", "banana", "orange", "grape", "peach", "pear", "mango", "melon"};
    SpellChecker spellChecker(wordList);

    std::cout << "=== Spell Checker ===\n";
    std::cout << "Enter a word to check its spelling, or 'exit' to quit.\n";

    std::string input;
    while (true) {
        std::cout << "\nWord to check: ";
        std::cin >> input;

        if (input == "exit") break;

        std::vector<std::string> suggestions = spellChecker.spellCheck(input);

        if (!suggestions.empty() && suggestions[0] == input) {
            std::cout << "Correct spelling: " << input << "\n";
        } else {
            std::cout << "Incorrect spelling. Did you mean:\n";
            for (const auto& suggestion : suggestions) {
                std::cout << " - " << suggestion << "\n";
            }
        }
    }
}

int main() {
    runSpellCheckerInterface();
    return 0;
}
