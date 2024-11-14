# Spell-Checker Class in C++

## Objective
Your task is to design and implement a spell-checker class in C++ that checks the spelling of a given word based on a predefined set of words. This class should be efficient in storing and retrieving words using a hash table.

## Description
Write a spell-checker class that stores a set of words, `W`, in a hash table and implements a function, `spellCheck(s)`, which performs a spell check on the string `s` with respect to the set of words, `W`.

- If `s` is in `W`, then the call to `spellCheck(s)` returns an iterable collection that contains only `s`, as it is assumed to be spelled correctly.
- If `s` is not in `W`, `spellCheck(s)` should return a list of every word in `W` that could be a correct spelling of `s`.

Your program should handle common types of misspellings, including:
1. Swapping adjacent characters.
2. Inserting a single character between two adjacent characters.
3. Deleting a single character.
4. Replacing a character with another character.

For an extra challenge, consider implementing phonetic substitutions as well. *(Reference: Book, Page 420, P-9.1)*

## Requirements

### Class Design (2 points)
Define a class `SpellChecker` with the following components:
- A **private hash table** data structure to store a set of correctly spelled words, `W`.
- A **constructor** that takes a list of words and initializes the hash table with these words.
- A **public function** `spellCheck(std::string s)` that takes a string `s` and returns a list of potential correct spellings for `s`.
- Choose an efficient **hash function**.

### Spell Check Function (3 points)
Implement the `spellCheck(std::string s)` function:
- **Check if the word `s` exists** in the hash table `W`. 
    - If `s` is found in `W`, return a collection containing only `s`.
    - If `s` is not in `W`, `spellCheck(s)` should return a list of potential matches from `W` based on the following misspelling conditions:
      - **Swapping**: Swapping any two adjacent characters in `s`.
      - **Insertion**: Inserting a single character between any two adjacent characters in `s`.
      - **Deletion**: Deleting a single character from `s`.
      - **Replacement**: Replacing any character in `s` with another character.

### Testing and User Interface (2 points)
- Implement a **user-friendly interface**.
- Test your spell-checker on various inputs, ensuring it accurately identifies correctly spelled words and provides a list of possible corrections for misspelled words.

### Exception Handling (1 point)
- Implement **exception handling**.

### Phonetic Substitutions and Documentation (2 points)
- Implement **phonetic similarity checks** for additional accuracy in misspelling detection. Allow common phonetic substitutions, such as:
    - `"ph"` for `"f"`
    - `"c"` for `"k"`
- Document your program's functionality, including an explanation of the chosen **hash function** and why it is optimal.

### Time Complexity (4 points)
Determine the worst-case **time complexity** of your program for an input size of `n`. Include:
- A mathematical analysis of the total time taken by your program.
- A screenshot of your code focusing only on the worst-case scenario, excluding constant-time parts.

Provide the time complexity explanation in a **PDF document**.

### Example
- **List of words**: `"apple"`, `"banana"`, `"orange"`, `"grape"`, `"peach"`
- **User input**: `applle`
- **Output**: `apple`

## Submission
Your submission should include:
1. **Source code** with comments explaining the code logic.
2. A **brief report** explaining:
   - Examples of how to use the program.
   - Testing process and results.
   - Time complexity analysis in PDF format.
3. Submit your C++ code files and report as a **single compressed file (ZIP)** on Canvas.
