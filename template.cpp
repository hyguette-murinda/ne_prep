#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Course {
    string courseName;
    bool isAvailable;

    Course(string name, bool available) : courseName(name), isAvailable(available) {}
};

struct Student {
    string name;
    int age;
    vector<string> courses;
    Student* next;

    Student(string studentName, int studentAge) : name(studentName), age(studentAge), next(nullptr) {}
};

Student* head = nullptr;

void addStudent(string name, int age, vector<string> courses) {
    Student* newStudent = new Student(name, age);
    newStudent->courses = courses;
    newStudent->next = head;
    head = newStudent;
}

void displayStudentsFromCSV(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, ageStr, course;
            vector<string> courses;

            getline(ss, name, ',');
            getline(ss, ageStr, ',');
            int age = stoi(ageStr);

            while (getline(ss, course, ',')) {
                courses.push_back(course);
            }

            cout << "Name: " << name << ", Age: " << age << ", Courses: ";
            for (const auto& course : courses) {
                cout << course << " ";
            }
            cout << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

void saveToCSV(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        Student* temp = head;
        while (temp != nullptr) {
            file << temp->name << "," << temp->age;
            for (const auto& course : temp->courses) {
                file << "," << course;
            }
            file << endl;
            temp = temp->next;
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

bool isCourseAvailable(const vector<Course>& courses, const string& courseName) {
    for (const auto& course : courses) {
        if (course.courseName == courseName) {
            return course.isAvailable;
        }
    }
    return false;
}

void enrollStudent(const vector<Course>& courses, const string& name, int age, const vector<string>& studentCourses) {
    vector<string> validCourses;
    for (const auto& course : studentCourses) {
        if (isCourseAvailable(courses, course)) {
            validCourses.push_back(course);
        } else {
            cout << "Course " << course << " is not available." << endl;
        }
    }
    addStudent(name, age, validCourses);
}
int main() {
    vector<Course> courses = {
        Course("Math", true),
        Course("Science", true),
        Course("History", false),
        Course("Art", true)
    };

    char choice;
    do {
        string name;
        int age;
        vector<string> studentCourses;
        string course;

        cout << "Enter student name: ";
        cin >> ws;
        getline(cin, name);

        cout << "Enter student age: ";
        cin >> age;

        cout << "Enter courses (type 'done' to finish): ";
        while (true) {
            cin >> course;
            if (course == "done") break;
            studentCourses.push_back(course);
        }

        enrollStudent(courses, name, age, studentCourses);

        cout << "Do you want to add another student? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    saveToCSV("students.csv");

    cout << "Displaying students from CSV file:" << endl;
    displayStudentsFromCSV("students.csv");

    return 0;
}
