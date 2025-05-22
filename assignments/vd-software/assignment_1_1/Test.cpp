#include "Test.h"

Test::Test(int id, const std::string& courseName, const std::string& testName, const std::string& date)
    : id(id), courseName(courseName), testName(testName), date(date) {
}

int Test::getId() const {
    return id;
}

std::string Test::getCourseName() const {
    return courseName;
}

std::string Test::getTestName() const {
    return testName;
}

std::string Test::getDate() const {
    return date;
}

void Test::setCourseName(const std::string& courseName) {
    this->courseName = courseName;
}

void Test::setTestName(const std::string& testName) {
    this->testName = testName;
}

void Test::setDate(const std::string& date) {
    this->date = date;
}

std::string Test::getDetails() const {
    return "test id = " + std::to_string(id) + ", course name = " + courseName + 
           ", test name = " + testName + ", date = " + date;
}

std::string Test::getShortDetails() const {
    return std::to_string(id) + " - " + courseName + " " + testName;
}
