import subprocess

def run_spellchecker_test(word, expected_output):
    process = subprocess.Popen(["./spellchecker.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    out, _ = process.communicate(input=f"{word}\nexit\n")
    actual_output = out.splitlines()[1]  # Grabbing the result line after input prompt
    result = "PASS" if actual_output.strip() == expected_output.strip() else "FAIL"
    print(f"Test: {word}\nExpected: {expected_output}\nActual: {actual_output}\nResult: {result}\n")

# Define test cases
tests = [
    ("apple", "The word 'apple' is spelled correctly."),
    ("applle", "Did you mean: apple?"),
    ("bananna", "Did you mean: banana?"),
    ("orrange", "Did you mean: orange?"),
    ("grap", "Did you mean: grape?"),
    ("pech", "Did you mean: peach?"),
    ("a", "No suitable suggestion found."),
    ("ra", "No suitable suggestion found."),
    ("ora", "Did you mean: orange?"),
]

# Run all tests
for word, expected in tests:
    run_spellchecker_test(word, expected)
