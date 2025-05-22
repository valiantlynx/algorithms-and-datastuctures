#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    int id;
    std::string name;
    int age;
    int attendance;

public:
    // Constructor
    Student(int id, const std::string& name, int age, int attendance);
    
    // Getters
    int getId() const;
    std::string getName() const;
    int getAge() const;
    int getAttendance() const;
};

#endif // STUDENT_H
