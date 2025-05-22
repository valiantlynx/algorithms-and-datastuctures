#ifndef TEST_H
#define TEST_H

#include <string>

class Test {
private:
    int id;
    std::string courseName;
    std::string testName;
    std::string date;

public:
    Test(int id, const std::string& courseName, const std::string& testName, const std::string& date);
    
    // Getters
    int getId() const;
    std::string getCourseName() const;
    std::string getTestName() const;
    std::string getDate() const;
    
    // Setters
    void setCourseName(const std::string& courseName);
    void setTestName(const std::string& testName);
    void setDate(const std::string& date);
    
    // Display methods
    std::string getDetails() const;
    std::string getShortDetails() const;
};

#endif // TEST_H
