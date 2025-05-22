#include "UserInterface.h"
#include <iostream>
#include <limits>
#include <algorithm>

UserInterface::UserInterface() {
}

void UserInterface::run() {
    bool exit = false;
    while (!exit) {
        displayMenu();
        int choice = getMenuChoice(1, 11);
        
        switch (choice) {
            case 1: addStudent(); break;
            case 2: editStudent(); break;
            case 3: removeStudent(); break;
            case 4: addTest(); break;
            case 5: editTest(); break;
            case 6: removeTest(); break;
            case 7: addTestResult(); break;
            case 8: editTestResult(); break;
            case 9: removeTestResult(); break;
            case 10: showAllInfo(); break;
            case 11: exit = true; break;
        }
    }
}

void UserInterface::displayMenu() {
    std::cout << "\nPlease choose:\n\n"
              << "1. Add student\n"
              << "2. Edit student\n"
              << "3. Remove student\n\n"
              << "4. Add test\n"
              << "5. Edit test\n"
              << "6. Remove test\n\n"
              << "7. Add test result\n"
              << "8. Edit test result\n"
              << "9. Remove test result\n\n"
              << "10. Show all info\n"
              << "11. Exit\n" << std::endl;
}

int UserInterface::getMenuChoice(int minValue, int maxValue) {
    int choice;
    while (true) {
        std::cout << "Enter your choice (" << minValue << "-" << maxValue << "): ";
        if (std::cin >> choice && choice >= minValue && choice <= maxValue) {
            // Clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        } else {
            // Clear error state and input buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

std::string UserInterface::getInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

void UserInterface::addStudent() {
    std::string name = getInput("Enter student name: ");
    std::string email = getInput("Enter student email: ");
    
    if (dataManager.addStudent(name, email)) {
        std::cout << "Student added successfully." << std::endl;
    } else {
        std::cout << "Failed to add student." << std::endl;
    }
}

void UserInterface::editStudent() {
    auto& students = dataManager.getStudents();
    if (students.empty()) {
        std::cout << "No students available to edit." << std::endl;
        return;
    }
    
    int index = selectStudent();
    if (index < 0) {
        return;  // Back was selected
    }
    
    std::string name = getInput("Enter new name: ");
    std::string email = getInput("Enter new email: ");
    
    if (dataManager.editStudent(index, name, email)) {
        std::cout << "Student updated successfully." << std::endl;
    } else {
        std::cout << "Failed to update student." << std::endl;
    }
}

void UserInterface::removeStudent() {
    auto& students = dataManager.getStudents();
    if (students.empty()) {
        std::cout << "No students available to remove." << std::endl;
        return;
    }
    
    int index = selectStudent();
    if (index < 0) {
        return; 
    }
    
    if (dataManager.removeStudent(index)) {
        std::cout << "Student removed successfully." << std::endl;
    } else {
        std::cout << "Failed to remove student." << std::endl;
    }
}

void UserInterface::addTest() {
    std::string courseName = getInput("Enter course name: ");
    std::string testName = getInput("Enter test name: ");
    std::string date = getInput("Enter date (YYYY.MM.DD): ");
    
    if (dataManager.addTest(courseName, testName, date)) {
        std::cout << "Test added successfully." << std::endl;
    } else {
        std::cout << "Failed to add test." << std::endl;
    }
}

void UserInterface::editTest() {
    auto& tests = dataManager.getTests();
    if (tests.empty()) {
        std::cout << "No tests available to edit." << std::endl;
        return;
    }
    
    int index = selectTest();
    if (index < 0) {
        return;  
    }
    
    std::string courseName = getInput("Enter new course name: ");
    std::string testName = getInput("Enter new test name: ");
    std::string date = getInput("Enter new date (YYYY.MM.DD): ");
    
    if (dataManager.editTest(index, courseName, testName, date)) {
        std::cout << "Test updated successfully." << std::endl;
    } else {
        std::cout << "Failed to update test." << std::endl;
    }
}

void UserInterface::removeTest() {
    auto& tests = dataManager.getTests();
    if (tests.empty()) {
        std::cout << "No tests available to remove." << std::endl;
        return;
    }
    
    int index = selectTest();
    if (index < 0) {
        return;  
    }
    
    if (dataManager.removeTest(index)) {
        std::cout << "Test removed successfully." << std::endl;
    } else {
        std::cout << "Failed to remove test." << std::endl;
    }
}

void UserInterface::addTestResult() {
    auto& students = dataManager.getStudents();
    auto& tests = dataManager.getTests();
    
    if (students.empty()) {
        std::cout << "No students available." << std::endl;
        return;
    }
    
    if (tests.empty()) {
        std::cout << "No tests available." << std::endl;
        return;
    }
    
    int studentIndex = selectStudent();
    if (studentIndex < 0) {
        return; 
    }
    
    int studentId = students[studentIndex].getId();
    int testIndex = selectTestForStudent(studentId);
    
    if (testIndex < 0) {
        return;  // Back was selected or no tests available
    }
    
    std::string grade = getInput("Enter grade: ");
    
    if (dataManager.addTestResult(studentIndex, testIndex, grade)) {
        std::cout << "Test result added successfully." << std::endl;
    } else {
        std::cout << "Failed to add test result." << std::endl;
    }
}

void UserInterface::editTestResult() {
    auto& students = dataManager.getStudents();
    
    if (students.empty()) {
        std::cout << "No students available." << std::endl;
        return;
    }
    
    int studentIndex = selectStudent();
    if (studentIndex < 0) {
        return;  
    }
    
    int studentId = students[studentIndex].getId();
    
    // tests this student has taken
    auto& allTests = dataManager.getTests();
    std::vector<int> takenTestIndices;
    
    for (size_t i = 0; i < allTests.size(); ++i) {
        if (dataManager.studentHasTakenTest(studentId, allTests[i].getId())) {
            takenTestIndices.push_back(i);
        }
    }
    
    if (takenTestIndices.empty()) {
        std::cout << "This student has not taken any tests." << std::endl;
        return;
    }
    
    std::cout << "\nSelect a test:" << std::endl;
    for (size_t i = 0; i < takenTestIndices.size(); ++i) {
        std::cout << (i + 1) << ". " << allTests[takenTestIndices[i]].getShortDetails() << std::endl;
    }
    std::cout << (takenTestIndices.size() + 1) << ". Back" << std::endl;
    
    int testChoice = getMenuChoice(1, takenTestIndices.size() + 1);
    if (testChoice == takenTestIndices.size() + 1) {
        return;  
    }
    
    int testIndex = takenTestIndices[testChoice - 1];
    
    std::string grade = getInput("Enter new grade: ");
    
    if (dataManager.editTestResult(studentIndex, testIndex, grade)) {
        std::cout << "Test result updated successfully." << std::endl;
    } else {
        std::cout << "Failed to update test result." << std::endl;
    }
}

void UserInterface::removeTestResult() {
    auto& students = dataManager.getStudents();
    
    if (students.empty()) {
        std::cout << "No students available." << std::endl;
        return;
    }
    
    int studentIndex = selectStudent();
    if (studentIndex < 0) {
        return; 
    }
    
    int studentId = students[studentIndex].getId();
    
    //  tests this student has taken
    auto& allTests = dataManager.getTests();
    std::vector<int> takenTestIndices;
    
    for (size_t i = 0; i < allTests.size(); ++i) {
        if (dataManager.studentHasTakenTest(studentId, allTests[i].getId())) {
            takenTestIndices.push_back(i);
        }
    }
    
    if (takenTestIndices.empty()) {
        std::cout << "This student has not taken any tests." << std::endl;
        return;
    }
    
    std::cout << "\nSelect a test:" << std::endl;
    for (size_t i = 0; i < takenTestIndices.size(); ++i) {
        std::cout << (i + 1) << ". " << allTests[takenTestIndices[i]].getShortDetails() << std::endl;
    }
    std::cout << (takenTestIndices.size() + 1) << ". Back" << std::endl;
    
    int testChoice = getMenuChoice(1, takenTestIndices.size() + 1);
    if (testChoice == takenTestIndices.size() + 1) {
        return;  
    }
    
    int testIndex = takenTestIndices[testChoice - 1];
    
    if (dataManager.removeTestResult(studentIndex, testIndex)) {
        std::cout << "Test result removed successfully." << std::endl;
    } else {
        std::cout << "Failed to remove test result." << std::endl;
    }
}

void UserInterface::showAllInfo() {
    std::cout << "\n" << dataManager.getAllInfo() << std::endl;
}

int UserInterface::selectStudent() {
    auto& students = dataManager.getStudents();
    
    std::cout << "\nSelect a student:" << std::endl;
    for (size_t i = 0; i < students.size(); ++i) {
        std::cout << (i + 1) << ". " << students[i].getShortDetails() << std::endl;
    }
    std::cout << (students.size() + 1) << ". Back" << std::endl;
    
    int choice = getMenuChoice(1, students.size() + 1);
    if (choice == students.size() + 1) {
        return -1; 
    }
    
    return choice - 1;
}

int UserInterface::selectTest() {
    auto& tests = dataManager.getTests();
    
    std::cout << "\nSelect a test:" << std::endl;
    for (size_t i = 0; i < tests.size(); ++i) {
        std::cout << (i + 1) << ". " << tests[i].getShortDetails() << std::endl;
    }
    std::cout << (tests.size() + 1) << ". Back" << std::endl;
    
    int choice = getMenuChoice(1, tests.size() + 1);
    if (choice == tests.size() + 1) {
        return -1; 
    }
    
    return choice - 1;
}

int UserInterface::selectTestForStudent(int studentId) {
    auto& tests = dataManager.getTests();
    
    if (tests.empty()) {
        std::cout << "No tests available." << std::endl;
        return -1;
    }
    
    // Don't filter tests - show all tests for selection
    std::cout << "\nSelect a test:" << std::endl;
    for (size_t i = 0; i < tests.size(); ++i) {
        std::cout << (i + 1) << ". " << tests[i].getShortDetails() << std::endl;
    }
    std::cout << (tests.size() + 1) << ". Back" << std::endl;
    
    int choice = getMenuChoice(1, tests.size() + 1);
    if (choice == tests.size() + 1) {
        return -1;  // Back was selected
    }
    
    return choice - 1;
}
