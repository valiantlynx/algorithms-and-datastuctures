#include <iostream>
#include <string>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>

class Student {
public:
    int id;
    std::string name;
    std::string email;
    int year;

    Student(int id, const std::string& name, const std::string& email, int year)
        : id(id), name(name), email(email), year(year) {}

    void display() const {
        std::cout << "id: " << id << ", name: " << name << ", email: " << email << ", year: " << year;
    }
};

class StudentDatabase {
private:
    SQLite::Database db;

public:
    StudentDatabase(const std::string& dbPath) : db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
        // Create students table. if it doesn't exist
        db.exec("CREATE TABLE IF NOT EXISTS students ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "name TEXT, "
                "email TEXT, "
                "year INTEGER)");
    }

    std::vector<Student> getAllStudents() {
        std::vector<Student> students;
        SQLite::Statement query(db, "SELECT id, name, email, year FROM students");
        
        while (query.executeStep()) {
            int id = query.getColumn(0);
            std::string name = query.getColumn(1).getString();
            std::string email = query.getColumn(2).getString();
            int year = query.getColumn(3);
            
            students.emplace_back(id, name, email, year);
        }
        
        return students;
    }

    Student* getStudentById(int id) {
        SQLite::Statement query(db, "SELECT id, name, email, year FROM students WHERE id = ?");
        query.bind(1, id);
        
        if (query.executeStep()) {
            int studentId = query.getColumn(0);
            std::string name = query.getColumn(1).getString();
            std::string email = query.getColumn(2).getString();
            int year = query.getColumn(3);
            
            return new Student(studentId, name, email, year);
        }
        
        return nullptr;
    }

    bool addStudent(const std::string& name, const std::string& email, int year) {
        try {
            SQLite::Statement query(db, "INSERT INTO students (name, email, year) VALUES (?, ?, ?)");
            query.bind(1, name);
            query.bind(2, email);
            query.bind(3, year);
            
            query.exec();
            return true;
        } catch (SQLite::Exception& e) {
            std::cerr << "SQLite error: " << e.what() << std::endl;
            return false;
        }
    }

    bool editStudent(int id, const std::string& name, const std::string& email, int year) {
        try {
            SQLite::Statement query(db, "UPDATE students SET name = ?, email = ?, year = ? WHERE id = ?");
            query.bind(1, name);
            query.bind(2, email);
            query.bind(3, year);
            query.bind(4, id);
            
            query.exec();
            return query.getChanges() > 0;
        } catch (SQLite::Exception& e) {
            std::cerr << "SQLite error: " << e.what() << std::endl;
            return false;
        }
    }

    bool removeStudent(int id) {
        try {
            SQLite::Statement query(db, "DELETE FROM students WHERE id = ?");
            query.bind(1, id);
            
            query.exec();
            return query.getChanges() > 0;
        } catch (SQLite::Exception& e) {
            std::cerr << "SQLite error: " << e.what() << std::endl;
            return false;
        }
    }

    std::vector<Student> searchStudents(const std::string& searchName) {
        std::vector<Student> students;
        SQLite::Statement query(db, "SELECT id, name, email, year FROM students WHERE name LIKE ?");
        query.bind(1, searchName);
        
        while (query.executeStep()) {
            int id = query.getColumn(0);
            std::string name = query.getColumn(1).getString();
            std::string email = query.getColumn(2).getString();
            int year = query.getColumn(3);
            
            students.emplace_back(id, name, email, year);
        }
        
        return students;
    }

    int getLastInsertId() {
        return static_cast<int>(db.getLastInsertRowid());
    }
};

void displayMenu() {
    std::cout << "\n==== Student Management System ====\n";
    std::cout << "1. Read all students\n";
    std::cout << "2. Get student by id\n";
    std::cout << "3. Add student\n";
    std::cout << "4. Edit student\n";
    std::cout << "5. Remove student\n";
    std::cout << "6. Search\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

int getMenuChoice() {
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    return choice;
}

void readAllStudents(StudentDatabase& db) {
    std::vector<Student> students = db.getAllStudents();
    
    if (students.empty()) {
        std::cout << "No students found" << std::endl;
        return;
    }
    
    for (const auto& student : students) {
        student.display();
        std::cout << std::endl;
    }
}

void getStudentById(StudentDatabase& db) {
    int id;
    std::cout << "Enter student ID: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    Student* student = db.getStudentById(id);
    
    if (student) {
        student->display();
        std::cout << std::endl;
        delete student; //free  memory
    } else {
        std::cout << "Student not found" << std::endl;
    }
}

void addStudent(StudentDatabase& db) {
    std::string name, email;
    int year;
    
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter email: ";
    std::getline(std::cin, email);
    
    std::cout << "Enter year: ";
    std::cin >> year;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (db.addStudent(name, email, year)) {
        int id = db.getLastInsertId();
        std::cout << "Added student: id: " << id << ", name: " << name << ", email: " << email << ", year: " << year << std::endl;
    } else {
        std::cout << "Failed to add student" << std::endl;
    }
}

void editStudent(StudentDatabase& db) {
    int id;
    
    std::cout << "Enter student ID: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Check if student exists first, if not, exit early- this was a pain. one of the test checks needs this //DONT DELETE to pass
    Student* student = db.getStudentById(id);
    if (!student) {
        std::cout << "Student not found" << std::endl;
        return;
    }
    delete student;  // Free memory since we only needed to check existence
    
    std::string name, email;
    int year;
    
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter email: ";
    std::getline(std::cin, email);
    
    std::cout << "Enter year: ";
    std::cin >> year;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (db.editStudent(id, name, email, year)) {
        std::cout << "Student was edited successfully" << std::endl;
    } else {
        std::cout << "Student not found" << std::endl;
    }
}

void removeStudent(StudentDatabase& db) {
    int id;
    std::cout << "Enter student ID: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (db.removeStudent(id)) {
        std::cout << "Student was removed successfully" << std::endl;
    } else {
        std::cout << "Student not found" << std::endl;
    }
}

void searchStudents(StudentDatabase& db) {
    std::string searchName;
    std::cout << "Enter search term: ";
    std::getline(std::cin, searchName);
    
    std::vector<Student> students = db.searchStudents(searchName);
    
    if (students.empty()) {
        std::cout << "No students found" << std::endl;
        return;
    }
    
    for (const auto& student : students) {
        student.display();
        std::cout << std::endl;
    }
}

int main() {
    try {
        StudentDatabase db("school.sqlite");
        bool running = true;
        
        while (running) {
            displayMenu();
            int choice = getMenuChoice();
            
            switch (choice) {
                case 1:
                    readAllStudents(db);
                    break;
                case 2:
                    getStudentById(db);
                    break;
                case 3:
                    addStudent(db);
                    break;
                case 4:
                    editStudent(db);
                    break;
                case 5:
                    removeStudent(db);
                    break;
                case 6:
                    searchStudents(db);
                    break;
                case 7:
                    std::cout << "Exiting program. Goodbye!" << std::endl;
                    running = false;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    } catch (SQLite::Exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
