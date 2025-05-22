#include "TestResult.h"

TestResult::TestResult(int studentId, int testId, const std::string& grade)
    : studentId(studentId), testId(testId), grade(grade) {
}

int TestResult::getStudentId() const {
    return studentId;
}

int TestResult::getTestId() const {
    return testId;
}

std::string TestResult::getGrade() const {
    return grade;
}

void TestResult::setGrade(const std::string& grade) {
    this->grade = grade;
}
