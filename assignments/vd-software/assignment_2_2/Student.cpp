#include "student.h"

Student::Student(int id, const std::string& name, int age, int attendance)
    : id(id), name(name), age(age), attendance(attendance) {}

int Student::getId() const {
    return id;
}

std::string Student::getName() const {
    return name;
}

int Student::getAge() const {
    return age;
}

int Student::getAttendance() const {
    return attendance;
}
