#define TESTING
#include <iostream>
#include <cassert>
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


void runExampleTest() {
    PriorityQueue queue;


    // Step 1: Insert "Thesis" with Priority 4
    std::string output = captureOutput([&]() { queue.insertJob("Thesis", 4); });
    assert(output.find("Next job: Thesis (Priority: 4)") != std::string::npos);
    assert(queue.getTopJob().name == "Thesis" && queue.getTopJob().priority == 4);

    // Step 2: Insert "Project" with Priority 5
    output = captureOutput([&]() { queue.insertJob("Project", 5); });
    assert(output.find("Next job: Project (Priority: 5)") != std::string::npos);
    assert(queue.getTopJob().name == "Project" && queue.getTopJob().priority == 5);

    // Step 3: Insert "Report" with Priority 3
    output = captureOutput([&]() { queue.insertJob("Report", 3); });
    assert(output.find("Next job: Project (Priority: 5)") != std::string::npos);
    assert(queue.getTopJob().name == "Project" && queue.getTopJob().priority == 5);

    // Step 4: Insert "Assignment" with Priority 2
    output = captureOutput([&]() { queue.insertJob("Assignment", 2); });
    assert(output.find("Next job: Project (Priority: 5)") != std::string::npos);
    assert(queue.getTopJob().name == "Project" && queue.getTopJob().priority == 5);

    // Step 5: Display Print Job with Highest Priority (Project)
    output = captureOutput([&]() { queue.displayHighestPriorityJob(); });
    assert(output.find("Next job: Project (Priority: 5)") != std::string::npos);

    // Step 6: Process (Print) the Job with the Highest Priority (Project)
    output = captureOutput([&]() { queue.processJob(); });
    assert(output.find("Processing: Project (Priority: 5)") != std::string::npos);
    assert(queue.getTopJob().name == "Thesis" && queue.getTopJob().priority == 4);

    // Step 7: Insert "Invoice" with Priority 6
    output = captureOutput([&]() { queue.insertJob("Invoice", 6); });
    assert(output.find("Next job: Invoice (Priority: 6)") != std::string::npos);
    assert(queue.getTopJob().name == "Invoice" && queue.getTopJob().priority == 6);

    // Step 8: Update "Thesis" priority to 7
    output = captureOutput([&]() { queue.updatePriority("Thesis", 7); });
    assert(output.find("Updated Thesis to priority 7") != std::string::npos);
    assert(queue.getTopJob().name == "Thesis" && queue.getTopJob().priority == 7);
    assert(captureOutput([&]() { queue.displayHighestPriorityJob(); }).find("Next job: Thesis (Priority: 7)") != std::string::npos);

    std::cout << "Example test sequence passed.\n";
}


int main() {
    runExampleTest();
    std::cout << "All tests passed.\n";
    return 0;
}
