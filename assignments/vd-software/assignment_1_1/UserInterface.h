#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "DataManager.h"
#include <string>

class UserInterface {
private:
    DataManager dataManager;
    
    void displayMenu();
    int getMenuChoice(int minValue, int maxValue);
    
    // Student operations
    void addStudent();
    void editStudent();
    void removeStudent();
    
    // Test operations
    void addTest();
    void editTest();
    void removeTest();
    
    // Test result operations
    void addTestResult();
    void editTestResult();
    void removeTestResult();
    
    // Display information
    void showAllInfo();
    
    // Helper functions
    int selectStudent();
    int selectTest();
    int selectTestForStudent(int studentId);
    
    std::string getInput(const std::string& prompt);
    
public:
    UserInterface();
    void run();
};

#endif // USER_INTERFACE_H
