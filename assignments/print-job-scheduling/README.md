# Print Job Scheduling with Priority Queue Using Max-Heap

## Requirements

- C++11 or higher
- Standard library support for `<iostream>`, `<vector>`, `<unordered_map>`, `<string>`

## Compilation

Compile the program using a C++ compiler:

```bash
g++ main.cpp -o main -std=c++11
```

Run the executable:

```bash
./main
```

## Program Overview

This project implements a priority queue for scheduling print jobs using a max-heap data structure. The system manages print jobs with different priorities and processes them based on priority, with higher-priority jobs handled before lower-priority ones. Users can add print jobs, update their priorities, and view the next job in line for processing.

## Features

- **Max-Heap Priority Queue**: Organizes print jobs by priority.
- **Job Insertion and Processing**: Allows job addition, displays the next job, and processes the highest-priority job.
- **Priority Update**: Users can update an existing job's priority, which automatically repositions the job in the queue.

## Authors

- Valiantlynx

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.