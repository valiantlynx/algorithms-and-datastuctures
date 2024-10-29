# Print Job Scheduling with Priority Queue Using Max-Heap

## Overview

This project implements a print job scheduling system using a priority queue based on a max-heap. The program allows users to add print jobs with different priorities and processes them efficiently according to priority. Higher-priority print jobs are processed before lower-priority ones.

## Features

### Task 1: Priority Queue Design and Implementation (5 Points)
- **Priority Queue**: A max-heap is used to implement the priority queue, ensuring that print jobs with higher priority values are processed first.
- **Print Job Structure**: Each print job has a `name` and a `priority` (integer), with higher numbers indicating higher priority.
- **Error Handling**: Manages invalid input cases such as non-unique job names.

### Task 2: Adding Print Jobs (3 Points)
- **User Interface**: Users can add jobs with specified priority levels.
- **Automatic Prioritization**: Jobs are inserted into the queue without requiring user management of priority order.
- **Unique Job Names**: If a job with a duplicate name is attempted, an error is displayed.
- **Display Next Job**: After each insertion, the highest-priority job is displayed (without processing it).

### Task 3: Updating Job Priority (2 Points)
- **Priority Update**: Users can update the priority of existing jobs, which are then repositioned in the max-heap.
- **Updated Job Order**: After updating a job's priority, the system displays the updated order of jobs.

## Example Usage

### Scenario
Manage a print queue with multiple jobs, each with different priorities. Higher-priority jobs should be printed first.

### Input Sequence and Expected Output

1. **Insert Job**: 
   - Name: `"Thesis"`, Priority: `4`
   - **Output**: Queue contains: `["Thesis"]`
   - **Next Priority**: Thesis (Priority: 4)

2. **Insert Job**: 
   - Name: `"Project"`, Priority: `5`
   - **Output**: Queue contains: `["Project", "Thesis"]`
   - **Next Priority**: Project (Priority: 5)

3. **Insert Job**: 
   - Name: `"Report"`, Priority: `3`
   - **Output**: Queue contains: `["Project", "Thesis", "Report"]`
   - **Next Priority**: Project (Priority: 5)

4. **Insert Job**: 
   - Name: `"Assignment"`, Priority: `2`
   - **Output**: Queue contains: `["Project", "Thesis", "Report", "Assignment"]`
   - **Next Priority**: Project (Priority: 5)

5. **Display Next Job**: 
   - **Output**: Project (Priority: 5) is the next print job.

6. **Process Job**: Project is printed and removed.
   - **Output**: Queue contains: `["Thesis", "Report", "Assignment"]`
   - **Next Priority**: Thesis (Priority: 4)

7. **Insert Job**: 
   - Name: `"Invoice"`, Priority: `6`
   - **Output**: Queue contains: `["Invoice", "Thesis", "Report", "Assignment"]`
   - **Next Priority**: Invoice (Priority: 6)

8. **Update Job Priority**: Update `"Thesis"` to Priority `7`
   - **Output**: Queue contains: `["Thesis", "Invoice", "Report", "Assignment"]`
   - **Next Priority**: Thesis (Priority: 7)

## Submission

Submit the following:
1. **Source Code**: Include comments to explain code logic.
2. **Report**: Describe functionality, examples, testing process, and results.

## Grading Criteria

- **Print Job Scheduling Implementation**: 4 Points
- **Error Handling**: 1 Point
- **Task 2 Implementation**: 3 Points
- **Task 3 Implementation**: 2 Points