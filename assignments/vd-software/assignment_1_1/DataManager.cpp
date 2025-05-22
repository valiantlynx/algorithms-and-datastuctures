#include "DataManager.h"
#include <algorithm>
#include <sstream>

DataManager::DataManager() : nextStudentId(1), nextTestId(1) {
}

bool DataManager::addStudent(const std::string& name, const std::string& email) {
    students.push_back(Student(nextStudentId++, name, email));
    return true;
}

bool DataManager::editStudent(int index, const std::string& name, const std::string& email) {
    if (index < 0 || index >= students.size()) {
        return false;
    }
    
    students[index].setName(name);
    students[index].setEmail(email);
    return true;
}

bool DataManager::removeStudent(int index) {
    if (index < 0 || index >= students.size()) {
        return false;
    }
    
    int studentId = students[index].getId();
    
    // DON'T remove test results when removing a student
    // This is so test results still appear in getAllInfo()
    
    // Remove the student
    students.erase(students.begin() + index);
    return true;
}

bool DataManager::addTest(const std::string& courseName, const std::string& testName, const std::string& date) {
    tests.push_back(Test(nextTestId++, courseName, testName, date));
    return true;
}

bool DataManager::editTest(int index, const std::string& courseName, const std::string& testName, const std::string& date) {
    if (index < 0 || index >= tests.size()) {
        return false;
    }
    
    tests[index].setCourseName(courseName);
    tests[index].setTestName(testName);
    tests[index].setDate(date);
    return true;
}

bool DataManager::removeTest(int index) {
    if (index < 0 || index >= tests.size()) {
        return false;
    }
    
    int testId = tests[index].getId();
    
    // DON'T remove test results when removing a test
    // same reason as in removeStudent()
    
    // Remove the test
    tests.erase(tests.begin() + index);
    return true;
}

bool DataManager::addTestResult(int studentIndex, int testIndex, const std::string& grade) {
    if (studentIndex < 0 || studentIndex >= students.size() || 
        testIndex < 0 || testIndex >= tests.size()) {
        return false;
    }
    
    int studentId = students[studentIndex].getId();
    int testId = tests[testIndex].getId();
    
    // if the student already has a result for this test
    auto resultIt = std::find_if(testResults.begin(), testResults.end(),
        [studentId, testId](const TestResult& result) {
            return result.getStudentId() == studentId && result.getTestId() == testId;
        });
    
    if (resultIt != testResults.end()) {
        // Update existing result
        resultIt->setGrade(grade);
    } else {
        // Add new result
        testResults.push_back(TestResult(studentId, testId, grade));
    }
    
    return true;
}

bool DataManager::editTestResult(int studentIndex, int testIndex, const std::string& grade) {
    if (studentIndex < 0 || studentIndex >= students.size() || 
        testIndex < 0 || testIndex >= tests.size()) {
        return false;
    }
    
    int studentId = students[studentIndex].getId();
    int testId = tests[testIndex].getId();
    
    auto resultIt = std::find_if(testResults.begin(), testResults.end(),
        [studentId, testId](const TestResult& result) {
            return result.getStudentId() == studentId && result.getTestId() == testId;
        });
    
    if (resultIt == testResults.end()) {
        return false;
    }
    
    resultIt->setGrade(grade);
    return true;
}

bool DataManager::removeTestResult(int studentIndex, int testIndex) {
    if (studentIndex < 0 || studentIndex >= students.size() || 
        testIndex < 0 || testIndex >= tests.size()) {
        return false;
    }
    
    int studentId = students[studentIndex].getId();
    int testId = tests[testIndex].getId();
    
    auto it = std::find_if(testResults.begin(), testResults.end(),
        [studentId, testId](const TestResult& result) {
            return result.getStudentId() == studentId && result.getTestId() == testId;
        });
    
    if (it != testResults.end()) {
        testResults.erase(it);
    }
    
    return true;
}

std::vector<Student>& DataManager::getStudents() {
    return students;
}

std::vector<Test>& DataManager::getTests() {
    return tests;
}

std::vector<TestResult>& DataManager::getTestResults() {
    return testResults;
}

Student* DataManager::getStudentById(int id) {
    auto it = std::find_if(students.begin(), students.end(),
        [id](const Student& student) {
            return student.getId() == id;
        });
    
    if (it != students.end()) {
        return &(*it);
    }
    return nullptr;
}

Test* DataManager::getTestById(int id) {
    auto it = std::find_if(tests.begin(), tests.end(),
        [id](const Test& test) {
            return test.getId() == id;
        });
    
    if (it != tests.end()) {
        return &(*it);
    }
    return nullptr;
}

TestResult* DataManager::findTestResult(int studentId, int testId) {
    auto it = std::find_if(testResults.begin(), testResults.end(),
        [studentId, testId](const TestResult& result) {
            return result.getStudentId() == studentId && result.getTestId() == testId;
        });
    
    if (it != testResults.end()) {
        return &(*it);
    }
    return nullptr;
}

bool DataManager::studentHasTakenTest(int studentId, int testId) const {
    return std::any_of(testResults.begin(), testResults.end(),
        [studentId, testId](const TestResult& result) {
            return result.getStudentId() == studentId && result.getTestId() == testId;
        });
}

std::vector<Test> DataManager::getTestsNotTakenByStudent(int studentId) {
    std::vector<Test> availableTests;
    
    for (const auto& test : tests) {
        if (!studentHasTakenTest(studentId, test.getId())) {
            availableTests.push_back(test);
        }
    }
    
    return availableTests;
}

std::string DataManager::getAllInfo() const {
    std::stringstream ss;
    
    ss << "Student details:" << std::endl;
    for (const auto& student : students) {
        ss << student.getDetails() << std::endl;
    }
    
    ss << std::endl << "Test details:" << std::endl;
    for (const auto& test : tests) {
        ss << test.getDetails() << std::endl;
    }
    
    ss << std::endl << "Test results:" << std::endl;
    for (const auto& result : testResults) {
        // Find the correct test
        auto testIt = std::find_if(tests.begin(), tests.end(),
            [&result](const Test& test) {
                return test.getId() == result.getTestId();
            });
        
        // output the test result irregardless of whether the student or test exists
        ss << "student id = " << result.getStudentId()
           << ", course name = " << (testIt != tests.end() ? testIt->getCourseName() : "Unknown Course")
           << ", test id = " << result.getTestId()
           << ", test name = " << (testIt != tests.end() ? testIt->getTestName() : "Unknown Test")
           << ", grade = " << result.getGrade() << std::endl;
    }
    
    return ss.str();
}
