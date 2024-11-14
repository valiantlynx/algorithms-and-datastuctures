import subprocess
import time
from typing import List, Tuple
import random
import string

def generate_test_cases(dictionary_words: List[str], num_test_cases: int) -> List[Tuple[str, str]]:
   test_cases = []

   # Generate correct word tests
   for word in dictionary_words:
       test_cases.append((word, f"The word '{word}' is spelled correctly."))

   # Generate misspelled word tests
   for _ in range(num_test_cases // 2):
       word = random.choice(dictionary_words)
       misspelled = word

       # Apply random misspelling
       for _ in range(random.randint(1, 3)):
           misspelling_func = random.choice([
               lambda w: ''.join(w[i:i+1] + w[i+1:i+2] + w[i+2:] if i+2 < len(w) else w for i in range(len(w)-1)),
               lambda w: w[:random.randint(0, len(w))] + random.choice(string.ascii_lowercase) + w[random.randint(0, len(w)):],
               lambda w: w[:random.randint(1, len(w)-1)] + w[random.randint(1, len(w)-1):] if len(w) > 1 else w,
               lambda w: w[:random.randint(0, len(w)-1)] + random.choice(string.ascii_lowercase) + w[random.randint(1, len(w)):],
               lambda w: w.replace('ph', 'f') if 'ph' in w else w.replace('f', 'ph') if 'f' in w else w
           ])
           misspelled = misspelling_func(misspelled)

       if misspelled != word:
           test_cases.append((misspelled, "Suggestions:"))

   # Generate short word tests
   short_words = [w for w in dictionary_words if len(w) <= 3]
   if short_words:
       for _ in range(num_test_cases // 4):
           word = random.choice(short_words)
           test_cases.append((word, "No suitable suggestions found."))

   # Generate long word tests
   long_words = [w for w in dictionary_words if len(w) >= 8]
   if long_words:
       for _ in range(num_test_cases // 4):
           word = random.choice(long_words)
           test_cases.append((word, "No suitable suggestions found."))

   return test_cases

def run_spellchecker_test(executable_path: str, word: str, dictionary_words: List[str]) -> Tuple[bool, str, str, float]:
   start_time = time.time()

   try:
       process = subprocess.Popen([executable_path],
                                stdin=subprocess.PIPE,
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                text=True)

       out, err = process.communicate(input=f"{word}\nexit\n", timeout=5)
       execution_time = time.time() - start_time

       # Parse the output
       result_lines = [line for line in out.splitlines() if line.strip()]
       actual_output = result_lines[1] if len(result_lines) > 1 else "No output"

       # Determine expected output
       if word in dictionary_words:
           expected_output = f"The word '{word}' is spelled correctly."
       else:
           # Check if any dictionary word is within edit distance 1 or 2
           similar_words = [w for w in dictionary_words if abs(len(w) - len(word)) <= 2]
           if similar_words:
               expected_output = "Suggestions:"
           else:
               expected_output = "No suitable suggestions found."

       success = expected_output in actual_output

       return success, expected_output, actual_output, execution_time

   except subprocess.TimeoutExpired:
       process.kill()
       return False, "Expected response", "Timeout occurred", time.time() - start_time
   except Exception as e:
       return False, "Expected response", f"Error: {str(e)}", time.time() - start_time

def main():
   EXECUTABLE_PATH = "./spellchecker.exe"
   NUM_TEST_CASES = 20

   dictionary_words = [
       "apple", "banana", "orange", "grape", "peach",
       "pear", "mango", "melon", "phone", "fone",
       "cat", "king", "cake"
   ]

   test_cases = generate_test_cases(dictionary_words, NUM_TEST_CASES)

   total_tests = 0
   passed_tests = 0
   total_time = 0
   failures = []

   print(f"Running {len(test_cases)} tests...")
   print("-" * 80)

   for word, expected in test_cases:
       success, expected_output, actual_output, exec_time = run_spellchecker_test(
           EXECUTABLE_PATH, word, dictionary_words)

       total_tests += 1
       total_time += exec_time

       if success:
           passed_tests += 1
           print(f"✓ Test: '{word}' ({exec_time:.3f}s)")
       else:
           failures.append({
               'word': word,
               'expected': expected_output,
               'actual': actual_output,
               'time': exec_time
           })
           print(f"✗ Test: '{word}' ({exec_time:.3f}s)")
           print(f"  Expected: {expected_output}")
           print(f"  Actual: {actual_output}")

   print("\n" + "=" * 80)
   print("Test Summary")
   print("=" * 80)
   print(f"Total Tests: {total_tests}")
   print(f"Passed: {passed_tests}")
   print(f"Failed: {total_tests - passed_tests}")
   print(f"Success Rate: {(passed_tests/total_tests)*100:.2f}%")
   print(f"Average Execution Time: {(total_time/total_tests)*1000:.2f}ms")

   if failures:
       print("\nFailure Details:")
       print("-" * 80)
       for i, failure in enumerate(failures, 1):
           print(f"\nFailure {i}:")
           print(f"Word: {failure['word']}")
           print(f"Expected: {failure['expected']}")
           print(f"Actual: {failure['actual']}")
           print(f"Time: {failure['time']:.3f}s")

if __name__ == "__main__":
   main()