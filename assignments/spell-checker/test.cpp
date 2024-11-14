#define TESTING
#include <iostream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include "SpellChecker.h"

// Helper function to capture output
std::string captureOutput(std::function<void()> func) {
    std::ostringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

// Helper function to print test results
void printTestResult(const std::string& testDescription, const std::string& actualOutput, const std::string& expectedOutput, bool condition) {
    std::cout << "Test: " << testDescription << "\n";
    std::cout << "Expected: " << expectedOutput << "\n";
    std::cout << "Actual: " << actualOutput << "\n";
    std::cout << (condition ? "Result: PASS" : "Result: FAIL") << "\n\n";
}

// Function to perform extensive tests
void runSpellCheckerTests() {
    std::vector<std::string> dictionary = {"apple", "banana", "orange", "grape", "peach", "pear", "mango", "melon"};
    SpellChecker checker(dictionary);

    bool condition;
    std::string output;

    // Test case 1: Correct word
    output = captureOutput([&]() {
        std::vector<std::string> result = checker.spellCheck("apple");
        if (!result.empty()) std::cout << result[0];
    });
    condition = (output == "apple");
    printTestResult("Correctly spelled word 'apple'", output, "apple", condition);

    // Test case 2: Misspelled word with suggestion
    output = captureOutput([&]() {
        std::vector<std::string> result = checker.spellCheck("applle");
        for (const auto& suggestion : result) {
            std::cout << suggestion << " ";
        }
    });
    condition = (output.find("apple") != std::string::npos);
    printTestResult("Misspelled word 'applle'", output, "apple", condition);

    // Additional tests with random misspellings
    std::vector<std::string> misspellings = {"bananna", "orrange", "grap", "pech"};
    for (const auto& misspelling : misspellings) {
        output = captureOutput([&]() {
            std::vector<std::string> result = checker.spellCheck(misspelling);
            for (const auto& suggestion : result) {
                std::cout << suggestion << " ";
            }
        });
        condition = (output.find(misspelling) == std::string::npos);
        printTestResult("Misspelling test for '" + misspelling + "'", output, "Expected suggestion for misspelling", condition);
    }

    std::cout << "Spell Checker tests completed.\n";
}

int main() {
    runSpellCheckerTests();
    return 0;
}
