#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <string>
#include <vector>
#include <unordered_set>

class SpellChecker {
private:
    std::unordered_set<std::string> wordSet;

    std::vector<std::string> getSwaps(const std::string& s);
    std::vector<std::string> getInsertions(const std::string& s);
    std::vector<std::string> getDeletions(const std::string& s);
    std::vector<std::string> getReplacements(const std::string& s);

public:
    SpellChecker(const std::vector<std::string>& words);
    std::vector<std::string> spellCheck(const std::string& s);
};

#endif
