#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <vector>
#include <map>
#include "Student.h"
#include "Test.h"
#include "TestResult.h"

class DataManager {
private:
    std::vector<Student> students;
    std::vector<Test> tests;
    std::vector<TestResult> testResults;
    
    int nextStudentId;
    int nextTestId;

public:
    DataManager();
    
    // Student operations
    bool addStudent(const std::string& name, const std::string& email);
    bool editStudent(int index, const std::string& name, const std::string& email);
    bool removeStudent(int index);
    
    // Test operations
    bool addTest(const std::string& courseName, const std::string& testName, const std::string& date);
    bool editTest(int index, const std::string& courseName, const std::string& testName, const std::string& date);
    bool removeTest(int index);
    
    // Test result operations
    bool addTestResult(int studentIndex, int testIndex, const std::string& grade);
    bool editTestResult(int studentIndex, int testIndex, const std::string& grade);
    bool removeTestResult(int studentIndex, int testIndex);
    
    // Helper methods
    std::vector<Student>& getStudents();
    std::vector<Test>& getTests();
    std::vector<TestResult>& getTestResults();
    
    Student* getStudentById(int id);
    Test* getTestById(int id);
    TestResult* findTestResult(int studentId, int testId);
    
    bool studentHasTakenTest(int studentId, int testId) const;
    std::vector<Test> getTestsNotTakenByStudent(int studentId);
    
    std::string getAllInfo() const;

    // Helper method to make sure removed entities are still tracked
    std::vector<TestResult> getAllTestResults() const { return testResults; }
};

#endif // DATA_MANAGER_H
