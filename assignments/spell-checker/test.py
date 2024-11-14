import subprocess

def run_spellchecker_test(word, expected_output):
    process = subprocess.Popen(["./spellchecker.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    out, _ = process.communicate(input=f"{word}\nexit\n")
    actual_output = out.splitlines()[0]  # Grabbing the result 
    result = "PASS" if actual_output.strip() == expected_output.strip() else "FAIL"
    print(f"Test: {word}\nExpected: {expected_output}\nActual: {actual_output}\nResult: {result}\n")

# Define test cases
tests = [
    ("apple", "Enter a word to spell-check (or 'exit' to quit): The word 'apple' is spelled correctly."),
    ("applle", "Enter a word to spell-check (or 'exit' to quit): Did you mean: apple?"),
    ("bananna", "Enter a word to spell-check (or 'exit' to quit): Did you mean: banana?"),
    ("orrange", "Enter a word to spell-check (or 'exit' to quit): Did you mean: orange?"),
    ("grap", "Enter a word to spell-check (or 'exit' to quit): Did you mean: grape?"),
    ("pech", "Enter a word to spell-check (or 'exit' to quit): Did you mean: peach?"),
    ("a", "Enter a word to spell-check (or 'exit' to quit): No suitable suggestion found."),
    ("ra", "Enter a word to spell-check (or 'exit' to quit): No suitable suggestion found."),
    ("ora", "Enter a word to spell-check (or 'exit' to quit): Did you mean: orange?"),
]

# Run all tests
for word, expected in tests:
    run_spellchecker_test(word, expected)
