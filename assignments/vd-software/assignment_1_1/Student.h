#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    int id;
    std::string name;
    std::string email;

public:
    Student(int id, const std::string& name, const std::string& email);
    
    // Getters
    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    
    // Setters
    void setName(const std::string& name);
    void setEmail(const std::string& email);
    
    // Display method
    std::string getDetails() const;
    std::string getShortDetails() const;
};

#endif // STUDENT_H
