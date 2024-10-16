# Assignment Title: Implementing and Analyzing the Quick Sort with Random Pivot (Randomized Quick Sort) Algorithm in C++

## Assignment Description
In this assignment, you will implement and analyze the Randomized Quick Sort algorithm in C++. Randomized Quick Sort is a variation of the classic Quick Sort algorithm that uses a randomly selected pivot to enhance the average-case performance and avoid worst-case scenarios on certain inputs.

## Implementation
Write a C++ program that implements the Randomized Quick Sort algorithm. Your program should include the following components:

- A function to perform the Randomized Quick Sort to sort an unsorted array.
- Input and output mechanisms to take user input for an unsorted array and display the sorted array.
- Ensure that your program handles integers and floating-point numbers based on user input.
- Implement error handling to manage edge cases gracefully (e.g., when the array is empty or input is invalid).

## Testing and Analysis

- The program should ask the user to input an unsorted array.
- Call the Randomized Quick Sort function to sort the array and output the sorted result.
- Perform a complexity analysis of the Randomized Quick Sort algorithm (Mathematical Prove), and compare its performance (execution time) with the following algorithms:
  - Merge Sort
  - Normal Quick Sort

### Testing Example

**Input:**

```
Unsorted Array: [29, 10, 14, 37, 13, 7, 1, 20]
```

**Output:**

```
The sorted array is: [1, 7, 10, 13, 14, 20, 29, 37]
```

### Explanation:

The array is sorted in ascending order using the Randomized Quick Sort algorithm, which randomly selects a pivot at each recursive step to avoid worst-case time complexity.

## Documentation and Submission
Include comments and documentation within your code to explain the logic and purpose of each component.

Write a brief report that includes:

- A description of the Randomized Quick Sort algorithm and how it works.
- Results of the performance analysis, is it possible to optimize this algorithm? and how?
- Discuss the efficiency of Randomized Quick Sort in comparison to Merge Sort and Normal Quick Sort based on your results.

Submit your C++ code files and the report as a single compressed file (ZIP file) through your Canvas group.

## Grading Criteria
Your assignment will be evaluated based on the following criteria:

- Correct implementation of the Randomized Quick Sort algorithm that handles integers and floating-points (3 Points).
- Effective error handling (1 Point).
- Clarity and readability of the code, including comments and documentation (1 Point).
- Accuracy and clarity of the performance analysis report (worst time complexity discussion included) in a PDF file (3 Points).