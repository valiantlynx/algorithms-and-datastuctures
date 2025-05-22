#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <string>
#include "student.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    //  JSON file
    std::ifstream file("students.json");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file students.json" << std::endl;
        return 1;
    }
    
    // Parse JSON
    json studentsJson;
    try {
        file >> studentsJson;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return 1;
    }
    
    // list of Student pointers
    std::list<Student*> students;
    
    // Process each student from JSON
    for (const auto& studentJson : studentsJson) {
        int id = studentJson["id"];
        std::string name = studentJson["name"];
        int age = studentJson["age"];
        int attendance = studentJson["attendance"];
        
        // create and add student to the list
        students.push_back(new Student(id, name, age, attendance));
    }
    
    //youngest and oldest student
    auto ageComparator = [](const Student* a, const Student* b) {
        return a->getAge() < b->getAge();
    };
    
    auto youngest = *std::min_element(students.begin(), students.end(), ageComparator);
    auto oldest = *std::max_element(students.begin(), students.end(), ageComparator);
    
    std::cout << "Youngest: " << youngest->getName() << std::endl;
    std::cout << "Oldest: " << oldest->getName() << std::endl;
    
    // average age
    int totalAge = 0;
    for (const auto& student : students) {
        totalAge += student->getAge();
    }
    
    int averageAge = static_cast<int>(std::floor(static_cast<double>(totalAge) / students.size()));
    std::cout << "Average age: " << averageAge << std::endl;
    
    // Find students with low attendance
    for (const auto& student : students) {
        if (student->getAttendance() < 30) {
            std::cout << "Bad student: " << student->getName() << std::endl;
        }
    }
    
    // Clean up 
    for (auto student : students) {
        delete student;
    }
    
    return 0;
}
