#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

// SpellChecker Class Definition
class SpellChecker {
public:
    SpellChecker(const std::vector<std::string>& dictionary);
    std::vector<std::string> spellCheck(const std::string& word);

private:
    std::unordered_set<std::string> wordSet;
    int calculateLevenshteinDistance(const std::string& source, const std::string& target);
    std::vector<std::string> findClosestMatches(const std::string& word);
};

// SpellChecker Implementation
SpellChecker::SpellChecker(const std::vector<std::string>& dictionary) {
    for (const auto& word : dictionary) {
        wordSet.insert(word);
    }
}

std::vector<std::string> SpellChecker::spellCheck(const std::string& word) {
    if (wordSet.find(word) != wordSet.end()) {
        return {word};  // Word is correctly spelled
    }
    
    return findClosestMatches(word);
}

int SpellChecker::calculateLevenshteinDistance(const std::string& source, const std::string& target) {
    std::vector<std::vector<int>> dp(source.size() + 1, std::vector<int>(target.size() + 1));

    for (size_t i = 0; i <= source.size(); ++i) dp[i][0] = i;
    for (size_t j = 0; j <= target.size(); ++j) dp[0][j] = j;

    for (size_t i = 1; i <= source.size(); ++i) {
        for (size_t j = 1; j <= target.size(); ++j) {
            int cost = (source[i - 1] == target[j - 1]) ? 0 : 1;
            dp[i][j] = std::min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
        }
    }
    return dp[source.size()][target.size()];
}

std::vector<std::string> SpellChecker::findClosestMatches(const std::string& word) {
    int minDistance = std::numeric_limits<int>::max();
    std::vector<std::string> closestMatches;

    for (const auto& dictWord : wordSet) {
        int distance = calculateLevenshteinDistance(word, dictWord);
        if (distance < minDistance) {
            minDistance = distance;
            closestMatches.clear();
            closestMatches.push_back(dictWord);
        } else if (distance == minDistance) {
            closestMatches.push_back(dictWord);
        }
    }
    return closestMatches;
}

// Main Application
int main() {
    std::vector<std::string> dictionary = {"apple", "banana", "orange", "grape", "peach", "pear", "mango", "melon"};
    SpellChecker checker(dictionary);

    std::string input;
    while (true) {
        std::cout << "Enter a word to spell-check (or 'exit' to quit): ";
        std::cin >> input;
        if (input == "exit") break;

        auto suggestions = checker.spellCheck(input);
        if (suggestions.empty()) {
            std::cout << "No suitable suggestion found.\n";
        } else if (suggestions[0] == input) {
            std::cout << "The word '" << input << "' is spelled correctly.\n";
        } else {
            std::cout << "Did you mean: ";
            for (const auto& suggestion : suggestions) {
                std::cout << suggestion << " ";
            }
            std::cout << "?\n";
        }
    }

    return 0;
}
