# Spell Checker in C++

## Requirements

- C++11 or higher
- Standard library support for `<iostream>`, `<string>`, `<unordered_set>`, `<vector>`

## Compilation

To compile the program, use a C++ compiler:

```bash
g++ main.cpp -o spellchecker -std=c++11
```

Run the executable:

```bash
./spellchecker
```

## Project Overview

This project implements a spell-checker class in C++ that verifies the spelling of a given word against a predefined set of correctly spelled words stored in a hash table. The program provides suggestions for misspelled words based on common types of misspelling errors, such as swapping, insertion, deletion, and replacement of characters.

## Features

- **Efficient Word Storage**: Stores correctly spelled words in a hash table for quick lookups.
- **Misspelling Detection**: Identifies possible correct words by:
  - Swapping adjacent characters
  - Inserting a character between any two adjacent characters
  - Deleting a character
  - Replacing a character with another
- **Phonetic Substitution (Optional)**: Can detect phonetically similar words, e.g., `"ph"` for `"f"`.
- **User-Friendly Interface**: Provides a simple way to check the spelling of words and view suggestions.

## Usage

- **spellCheck(s)**: Takes a string `s` as input. If `s` is found in the dictionary, it is considered correctly spelled. If `s` is not found, the function returns a list of possible corrections.

## Example

```cpp
// Initialize spell checker with a list of words
SpellChecker checker({"apple", "banana", "orange", "grape", "peach"});

// Check spelling
std::vector<std::string> suggestions = checker.spellCheck("applle");

// Output: apple
```

## Testing

This program includes a test suite that verifies functionality:
- Correctly spelled words should return only the input word.
- Misspelled words should return a list of possible corrections.

## Time Complexity Analysis

The worst-case time complexity is analyzed for an input size of `n`. For details, refer to the PDF included in this project, which includes both the complexity analysis and code snippet for the worst-case scenario.

## Authors

- Valiantlynx

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.