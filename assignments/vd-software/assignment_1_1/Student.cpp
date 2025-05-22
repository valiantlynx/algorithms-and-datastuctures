#include "Student.h"

Student::Student(int id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {
}

int Student::getId() const {
    return id;
}

std::string Student::getName() const {
    return name;
}

std::string Student::getEmail() const {
    return email;
}

void Student::setName(const std::string& name) {
    this->name = name;
}

void Student::setEmail(const std::string& email) {
    this->email = email;
}

std::string Student::getDetails() const {
    return "student id = " + std::to_string(id) + ", name = " + name + ", email = " + email;
}

std::string Student::getShortDetails() const {
    return std::to_string(id) + " - " + name;
}
