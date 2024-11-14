#include "SpellChecker.h"
#include <algorithm>

SpellChecker::SpellChecker(const std::vector<std::string>& words) {
    for (const auto& word : words) {
        wordSet.insert(word);
    }
}

std::vector<std::string> SpellChecker::getSwaps(const std::string& s) {
    std::vector<std::string> swaps;
    for (size_t i = 0; i < s.length() - 1; ++i) {
        std::string temp = s;
        std::swap(temp[i], temp[i + 1]);
        swaps.push_back(temp);
    }
    return swaps;
}

std::vector<std::string> SpellChecker::getInsertions(const std::string& s) {
    std::vector<std::string> insertions;
    for (size_t i = 0; i <= s.length(); ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            std::string temp = s;
            temp.insert(i, 1, c);
            insertions.push_back(temp);
        }
    }
    return insertions;
}

std::vector<std::string> SpellChecker::getDeletions(const std::string& s) {
    std::vector<std::string> deletions;
    for (size_t i = 0; i < s.length(); ++i) {
        std::string temp = s;
        temp.erase(i, 1);
        deletions.push_back(temp);
    }
    return deletions;
}

std::vector<std::string> SpellChecker::getReplacements(const std::string& s) {
    std::vector<std::string> replacements;
    for (size_t i = 0; i < s.length(); ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            if (c != s[i]) {
                std::string temp = s;
                temp[i] = c;
                replacements.push_back(temp);
            }
        }
    }
    return replacements;
}

std::vector<std::string> SpellChecker::spellCheck(const std::string& s) {
    std::vector<std::string> suggestions;
    if (wordSet.find(s) != wordSet.end()) {
        return {s}; // Correctly spelled
    }

    std::vector<std::string> candidates;
    auto addCandidates = [&](const std::vector<std::string>& words) {
        for (const auto& word : words) {
            if (wordSet.find(word) != wordSet.end()) {
                candidates.push_back(word);
            }
        }
    };

    addCandidates(getSwaps(s));
    addCandidates(getInsertions(s));
    addCandidates(getDeletions(s));
    addCandidates(getReplacements(s));

    std::unordered_set<std::string> uniqueSuggestions(candidates.begin(), candidates.end());
    suggestions.assign(uniqueSuggestions.begin(), uniqueSuggestions.end());

    return suggestions;
}
