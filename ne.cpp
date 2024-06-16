#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class Course {
public:
    std::string courseName;

    Course(const std::string &name) : courseName(name) {}
};

class Student {
public:
    std::string studentId;
    std::string name;
    std::vector<std::string> courses;
    Student* next;

    Student(const std::string &id, const std::string &name) : studentId(id), name(name), next(nullptr) {}

    void addCourse(const std::string &courseName) {
        courses.push_back(courseName);
    }
};

class StudentLinkedList {
private:
    Student* head;
    std::vector<Course> coursesAvailable;

public:
    StudentLinkedList() : head(nullptr) {}

    void addCourse(const Course &course) {
        coursesAvailable.push_back(course);
    }

    bool isCourseAvailable(const std::string &courseName) {
        for (const auto &course : coursesAvailable) {
            if (course.courseName == courseName) {
                return true;
            }
        }
        return false;
    }

    void addStudent(Student* student) {
        if (!head) {
            head = student;
        } else {
            Student* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = student;
        }
    }

    void enrollStudentInCourse(const std::string &studentId, const std::string &courseName) {
        if (!isCourseAvailable(courseName)) {
            std::cout << "Course " << courseName << " is not available." << std::endl;
            return;
        }

        Student* current = head;
        while (current) {
            if (current->studentId == studentId) {
                current->addCourse(courseName);
                return;
            }
            current = current->next;
        }
        std::cout << "Student with ID " << studentId << " not found." << std::endl;
    }

    void saveToCSV(const std::string &filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing." << std::endl;
            return;
        }

        file << "Student ID,Name,Courses\n";
        Student* current = head;
        while (current) {
            file << current->studentId << "," << current->name << ",";
            for (size_t i = 0; i < current->courses.size(); ++i) {
                file << current->courses[i];
                if (i < current->courses.size() - 1) {
                    file << "; ";
                }
            }
            file << "\n";
            current = current->next;
        }

        file.close();
    }

    Student* searchStudent(const std::string &studentId) {
        Student* current = head;
        while (current) {
            if (current->studentId == studentId) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    ~StudentLinkedList() {
        Student* current = head;
        while (current) {
            Student* nextStudent = current->next;
            delete current;
            current = nextStudent;
        }
    }
};

int main() {
    StudentLinkedList studentList;

    while (true) {
        std::cout << "1. Add Course\n";
        std::cout << "2. Add Student\n";
        std::cout << "3. Enroll Student in Course\n";
        std::cout << "4. Search Student\n";
        std::cout << "5. Save to CSV\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter the number of courses you want to add: ";
            int numCourses;
            std::cin >> numCourses;
            std::cin.ignore(); // to ignore the newline character left by std::cin

            for (int i = 0; i < numCourses; ++i) {
                std::cout << "Enter course name #" << (i + 1) << ": ";
                std::string courseName;
                std::getline(std::cin, courseName);
                studentList.addCourse(Course(courseName));
            }
            std::cout << "Courses added successfully.\n";
        } else if (choice == 2) {
            std::cout << "Enter student ID: ";
            std::string studentId;
            std::cin >> studentId;
            std::cout << "Enter student name: ";
            std::string studentName;
            std::cin.ignore();
            std::getline(std::cin, studentName);

            Student* student = new Student(studentId, studentName);

            std::cout << "Enter the number of courses the student wants to enroll in: ";
            int numCourses;
            std::cin >> numCourses;
            std::cin.ignore();

            for (int i = 0; i < numCourses; ++i) {
                std::cout << "Enter course name #" << (i + 1) << ": ";
                std::string courseName;
                std::getline(std::cin, courseName);
                if (studentList.isCourseAvailable(courseName)) {
                    student->addCourse(courseName);
                } else {
                    std::cout << "Course " << courseName << " is not available.\n";
                }
            }

            studentList.addStudent(student);
            std::cout << "Student added successfully.\n";
        } else if (choice == 3) {
            std::cout << "Enter student ID: ";
            std::string studentId;
            std::cin >> studentId;
            std::cout << "Enter course name: ";
            std::string courseName;
            std::cin.ignore();
            std::getline(std::cin, courseName);
            studentList.enrollStudentInCourse(studentId, courseName);
        } else if (choice == 4) {
            std::cout << "Enter student ID: ";
            std::string studentId;
            std::cin >> studentId;
            Student* student = studentList.searchStudent(studentId);
            if (student) {
                std::cout << "Found student: " << student->name << ", Courses: ";
                for (const auto &course : student->courses) {
                    std::cout << course << " ";
                }
                std::cout << "\n";
            } else {
                std::cout << "Student not found.\n";
            }
        } else if (choice == 5) {
            std::cout << "Enter filename to save: ";
            std::string filename;
            std::cin >> filename;
            studentList.saveToCSV(filename);
            std::cout << "Data saved to " << filename << "\n";
        } else if (choice == 6) {
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}




