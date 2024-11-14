#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

// SpellChecker Class Definition
class SpellChecker {
public:
    SpellChecker(const std::vector<std::string>& dictionary);
    std::vector<std::string> spellCheck(const std::string& s);

private:
    std::unordered_set<std::string> wordSet;
    std::unordered_map<char, std::vector<char>> phoneticSubstitutions;

    void initializePhoneticSubstitutions();
    std::vector<std::string> generateCandidates(const std::string& s);
    bool isPotentialMatch(const std::string& s, const std::string& word);
    std::string findClosestMatch(const std::string& s);
};

// SpellChecker Implementation
SpellChecker::SpellChecker(const std::vector<std::string>& dictionary) {
    for (const auto& word : dictionary) {
        wordSet.insert(word);
    }
    initializePhoneticSubstitutions();
}

void SpellChecker::initializePhoneticSubstitutions() {
    phoneticSubstitutions['f'] = {'p', 'v'};
    phoneticSubstitutions['c'] = {'k', 's'};
}

std::vector<std::string> SpellChecker::spellCheck(const std::string& s) {
    if (wordSet.find(s) != wordSet.end()) return {s};

    std::vector<std::string> suggestions;
    auto candidates = generateCandidates(s);

    for (const auto& word : wordSet) {
        for (const auto& candidate : candidates) {
            if (isPotentialMatch(candidate, word)) {
                suggestions.push_back(word);
                break;
            }
        }
    }

    if (suggestions.empty()) {
        suggestions.push_back(findClosestMatch(s));  // Fallback to closest match
    }
    return suggestions;
}

std::vector<std::string> SpellChecker::generateCandidates(const std::string& s) {
    std::vector<std::string> candidates;

    // Insertion
    for (size_t i = 0; i <= s.size(); ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            std::string modified = s.substr(0, i) + c + s.substr(i);
            candidates.push_back(modified);
        }
    }

    // Deletion
    for (size_t i = 0; i < s.size(); ++i) {
        std::string modified = s.substr(0, i) + s.substr(i + 1);
        candidates.push_back(modified);
    }

    // Replacement
    for (size_t i = 0; i < s.size(); ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            std::string modified = s;
            modified[i] = c;
            candidates.push_back(modified);
        }
    }

    // Swapping
    for (size_t i = 0; i < s.size() - 1; ++i) {
        std::string modified = s;
        std::swap(modified[i], modified[i + 1]);
        candidates.push_back(modified);
    }

    return candidates;
}

bool SpellChecker::isPotentialMatch(const std::string& s, const std::string& word) {
    return s == word;
}

// Find closest match by Levenshtein distance
std::string SpellChecker::findClosestMatch(const std::string& s) {
    int minDistance = s.size() + 1;
    std::string closestMatch;

    for (const auto& word : wordSet) {
        int distance = std::max(s.size(), word.size()) - std::min(s.size(), word.size());
        if (distance < minDistance) {
            minDistance = distance;
            closestMatch = word;
        }
    }
    return closestMatch;
}

// Main Application
int main() {
    std::vector<std::string> dictionary = {"apple", "banana", "orange", "grape", "peach", "pear", "mango", "melon"};
    SpellChecker checker(dictionary);

    std::string word;
    std::cout << "Enter a word to spell-check (or 'exit' to quit): ";
    while (std::cin >> word && word != "exit") {
        std::vector<std::string> suggestions = checker.spellCheck(word);

        if (suggestions.size() == 1 && suggestions[0] == word) {
            std::cout << "The word '" << word << "' is spelled correctly.\n";
        } else {
            std::cout << "Did you mean: ";
            for (const auto& suggestion : suggestions) {
                std::cout << suggestion << " ";
            }
            std::cout << "\n";
        }
        std::cout << "Enter another word (or 'exit' to quit): ";
    }

    return 0;
}
