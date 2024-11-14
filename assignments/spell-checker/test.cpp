#define TESTING
#include <iostream>
#include <functional>
#include <sstream>
#include <string>
#include "main.cpp" // Include the main.cpp file containing PriorityQueue

// Helper function to capture output of specific actions
std::string captureOutput(std::function<void()> func) {
    std::ostringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

// Helper function to print test results
void printTestResult(const std::string& testDescription, const std::string& actualOutput, const std::string& expectedOutput, bool condition) {
    std::cout << "Test: " << testDescription << "\n";
    std::cout << "Expected: " << expectedOutput << "\n";
    std::cout << "Actual: " << actualOutput << "\n";
    std::cout << (condition ? "Result: PASS" : "Result: FAIL") << "\n\n";
}

// Function to perform the example test sequence
void runExampleTest() {
    PriorityQueue queue;
    bool condition;
    std::string output;

    // Step 1: Insert "Thesis" with Priority 4
    output = captureOutput([&]() { queue.insertJob("Thesis", 4); });
    condition = (output.find("Next job: Thesis (Priority: 4)") != std::string::npos);
    printTestResult("Insert 'Thesis' with priority 4", output, "Next job: Thesis (Priority: 4)", condition);

    // Step 2: Insert "Project" with Priority 5
    output = captureOutput([&]() { queue.insertJob("Project", 5); });
    condition = (output.find("Next job: Project (Priority: 5)") != std::string::npos);
    printTestResult("Insert 'Project' with priority 5", output, "Next job: Project (Priority: 5)", condition);

    // Step 3: Insert "Report" with Priority 3
    output = captureOutput([&]() { queue.insertJob("Report", 3); });
    condition = (output.find("Next job: Project (Priority: 5)") != std::string::npos);
    printTestResult("Insert 'Report' with priority 3", output, "Next job: Project (Priority: 5)", condition);

    // Step 4: Insert "Assignment" with Priority 2
    output = captureOutput([&]() { queue.insertJob("Assignment", 2); });
    condition = (output.find("Next job: Project (Priority: 5)") != std::string::npos);
    printTestResult("Insert 'Assignment' with priority 2", output, "Next job: Project (Priority: 5)", condition);

    // Step 5: Display Print Job with Highest Priority (Project)
    output = captureOutput([&]() { queue.displayHighestPriorityJob(); });
    condition = (output.find("Next job: Project (Priority: 5)") != std::string::npos);
    printTestResult("Display job with highest priority", output, "Next job: Project (Priority: 5)", condition);

    // Step 6: Process (Print) the Job with the Highest Priority (Project)
    output = captureOutput([&]() { queue.processJob(); });
    condition = (output.find("Processing: Project (Priority: 5)") != std::string::npos);
    printTestResult("Process job with highest priority", output, "Processing: Project (Priority: 5)", condition);

    // Step 7: Insert "Invoice" with Priority 6
    output = captureOutput([&]() { queue.insertJob("Invoice", 6); });
    condition = (output.find("Next job: Invoice (Priority: 6)") != std::string::npos);
    printTestResult("Insert 'Invoice' with priority 6", output, "Next job: Invoice (Priority: 6)", condition);

    // Step 8: Update "Thesis" priority to 7
    output = captureOutput([&]() { queue.updatePriority("Thesis", 7); });
    condition = (output.find("Updated Thesis to priority 7") != std::string::npos);
    printTestResult("Update 'Thesis' priority to 7", output, "Updated Thesis to priority 7", condition);

    std::cout << "Example test sequence finished.\n";
}

int main() {
    runExampleTest();
    return 0;
}
