#ifndef TEST_RESULT_H
#define TEST_RESULT_H

#include <string>

class TestResult {
private:
    int studentId;
    int testId;
    std::string grade;

public:
    TestResult(int studentId, int testId, const std::string& grade);
    
    // Getters
    int getStudentId() const;
    int getTestId() const;
    std::string getGrade() const;
    
    // Setters
    void setGrade(const std::string& grade);
};

#endif // TEST_RESULT_H
