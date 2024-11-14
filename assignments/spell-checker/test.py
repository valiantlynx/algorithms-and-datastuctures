import subprocess

def run_spellchecker_test(word, expected_output):
    process = subprocess.Popen(
        ["./spellchecker"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
    )
    stdout, _ = process.communicate(input=word + "\nexit\n")

    result = expected_output in stdout
    print(f"Test: {word}")
    print(f"Expected: {expected_output}")
    print(f"Actual: {stdout.strip()}")
    print(f"Result: {'PASS' if result else 'FAIL'}\n")
    return result

# Define test cases
tests = [
    ("apple", "The word 'apple' is spelled correctly."),
    ("applle", "Did you mean: apple"),
    ("bananna", "Did you mean: banana"),
    ("orrange", "Did you mean: orange"),
    ("grap", "Did you mean: grape"),
    ("pech", "Did you mean: peach"),
    ("girrafe", "Did you mean: grape"),  # Example of fallback match
    ("a", "Did you mean: apple"),       # Closest match for single letters
    ("ra", "Did you mean: grape")        # Fallback for very different input
]

# Run each test case
for word, expected in tests:
    run_spellchecker_test(word, expected)
