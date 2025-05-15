#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

struct Student {
    string name;
    string id;
    vector<string> subjects;
    vector<string> grades;
};


void displayMenu();
void addStudent(deque<Student>& records);
void searchStudent(const deque<Student>& records);
void updateStudent(deque<Student>& records);
void generateReports(const deque<Student>& records);
void deleteStudent(deque<Student>& records);
void saveToFile(const deque<Student>& records);
void loadFromFile(deque<Student>& records);
void displayDesignLine();

int main() {
    deque<Student> studentRecords;
    loadFromFile(studentRecords);

    int choice;
    do {
        displayMenu();
        
        
        while (!(cin >> choice)) {
            cout << "\n|==============================================|";
            cout << "\n|            Invalid input!                    |";
            cout << "\n|      Please enter a number (1-6):            |";
            cout << "\n|==============================================|\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            displayMenu();
        }
        cin.ignore(); 

        switch (choice) {
            case 1:
                addStudent(studentRecords);
                break;
            case 2:
                searchStudent(studentRecords);
                break;
            case 3:
                updateStudent(studentRecords);
                break;
            case 4:
                generateReports(studentRecords);
                break;
            case 5:
                deleteStudent(studentRecords);
                break;
            case 6:
                cout << "\n|==============================================|";
                cout << "\n|             Exiting program...               |";
                cout << "\n|==============================================|\n";
                break;
            default:
                cout << "\n|==============================================|";
                cout << "\n|      Invalid choice. Please try again.       |";
                cout << "\n|==============================================|\n";
        }
    } while (choice != 6);

    return 0;
}

void displayDesignLine() {
    cout << "\n|==============================================|\n";
}

void displayMenu() {
    displayDesignLine();
    cout << "|        Student Records Management System     |";
    displayDesignLine();
    cout << "|          1. Add New Student                  |" << endl;
    cout << "|          2. Search for Student               |" << endl;
    cout << "|          3. Update Student Information       |" << endl;
    cout << "|          4. Generate Reports                 |" << endl;
    cout << "|          5. Delete Student Record            |" << endl;
    cout << "|          6. Exit                             |";
    displayDesignLine();
    cout << "|   Enter your choice (1-6): ";
}

void addStudent(deque<Student>& records) {
    Student newStudent;
    displayDesignLine();
    cout << "|   Enter student name: ";
    getline(cin, newStudent.name);
    cout << "|   Enter student ID: ";
    getline(cin, newStudent.id);

    // Check if ID already exists
    for (const auto& student : records) {
        if (student.id == newStudent.id) {
            displayDesignLine();
            cout << "|   Student with this ID already exists!      |";
            displayDesignLine();
            return;
        }
    }

    int numSubjects;
    cout << "|   Enter number of subjects: ";
    while (!(cin >> numSubjects)) {
        cout << "|   Invalid input! Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    for (int i = 0; i < numSubjects; i++) {
        string subject, grade;
        cout << "|   Enter subject name " << i + 1 << ": ";
        getline(cin, subject);
        cout << "|   Enter grade for " << subject << ": ";
        getline(cin, grade);
        newStudent.subjects.push_back(subject);
        newStudent.grades.push_back(grade);
    }

    records.push_back(newStudent);
    saveToFile(records);
    displayDesignLine();
    cout << "|   Student record added successfully!         |";
    displayDesignLine();
}

void searchStudent(const deque<Student>& records) {
    string searchTerm;
    displayDesignLine();
    cout << "|   Enter student name or ID to search: ";
    getline(cin, searchTerm);

    bool found = false;
    for (const auto& student : records) {
        if (student.name == searchTerm || student.id == searchTerm) {
            displayDesignLine();
            cout << "|   Student Information:                       |" << endl;
            cout << "|   Name: " << student.name << endl;
            cout << "|   ID: " << student.id << endl;
            cout << "|   Subjects and Grades:                       |" << endl;
            for (size_t i = 0; i < student.subjects.size(); i++) {
                cout << "|   " << student.subjects[i] << ": " << student.grades[i] << endl;
            }
            displayDesignLine();
            found = true;
            break;
        }
    }

    if (!found) {
        displayDesignLine();
        cout << "|   Student not found!                        |";
        displayDesignLine();
    }
}

void updateStudent(deque<Student>& records) {
    string id;
    displayDesignLine();
    cout << "|   Enter student ID to update: ";
    getline(cin, id);

    bool found = false;
    for (auto& student : records) {
        if (student.id == id) {
            found = true;
            displayDesignLine();
            cout << "|   Current Information:                      |" << endl;
            cout << "|   Name: " << student.name << endl;
            cout << "|   ID: " << student.id << endl;
            cout << "|   Subjects and Grades:                     |" << endl;
            for (size_t i = 0; i < student.subjects.size(); i++) {
                cout << "|   " << i + 1 << ". " << student.subjects[i] << ": " << student.grades[i] << endl;
            }

            displayDesignLine();
            cout << "|   What would you like to update?           |" << endl;
            cout << "|   1. Name                                  |" << endl;
            cout << "|   2. Add Subject                          |" << endl;
            cout << "|   3. Update Grade                         |" << endl;
            displayDesignLine();
            cout << "|   Enter choice (1-3): ";

            int updateChoice;
            while (!(cin >> updateChoice) || updateChoice < 1 || updateChoice > 3) {
                cout << "|   Invalid input! Please enter 1-3: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();

            switch (updateChoice) {
                case 1: {
                    cout << "|   Enter new name: ";
                    getline(cin, student.name);
                    break;
                }
                case 2: {
                    string subject, grade;
                    cout << "|   Enter new subject name: ";
                    getline(cin, subject);
                    cout << "|   Enter grade for " << subject << ": ";
                    getline(cin, grade);
                    student.subjects.push_back(subject);
                    student.grades.push_back(grade);
                    break;
                }
                case 3: {
                    int subjectNum;
                    cout << "|   Enter subject number to update grade: ";
                    while (!(cin >> subjectNum) || subjectNum < 1 || subjectNum > static_cast<int>(student.subjects.size())) {
                        cout << "|   Invalid input! Please enter a valid subject number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore();
                    cout << "|   Enter new grade for " << student.subjects[subjectNum - 1] << ": ";
                    getline(cin, student.grades[subjectNum - 1]);
                    break;
                }
            }

            saveToFile(records);
            displayDesignLine();
            cout << "|   Record updated successfully!             |";
            displayDesignLine();
            break;
        }
    }

    if (!found) {
        displayDesignLine();
        cout << "|   Student with ID " << id << " not found.        |";
        displayDesignLine();
    }
}

void generateReports(const deque<Student>& records) {
    if (records.empty()) {
        displayDesignLine();
        cout << "|   No student records found!                  |";
        displayDesignLine();
        return;
    }

    displayDesignLine();
    cout << "|   Student Reports                            |";
    displayDesignLine();
    cout << "|   ID        Name        Subjects   Average   |";
    displayDesignLine();

    for (const auto& student : records) {
        double total = 0;
        int count = 0;
        for (const auto& grade : student.grades) {
            try {
                total += stod(grade);
                count++;
            } catch (...) {
                
            }
        }
        
        double average = count > 0 ? total / count : 0;
        cout << "   " << left << setw(10) << student.id 
             << setw(12) << student.name 
             << setw(10) << student.subjects.size() 
             << setw(9) << fixed << setprecision(2) << average << "" << endl;
    }
    displayDesignLine();
}

void deleteStudent(deque<Student>& records) {
    string id;
    displayDesignLine();
    cout << "|   Enter student ID to delete: ";
    getline(cin, id);

    auto it = remove_if(records.begin(), records.end(),
        [id](const Student& s) { return s.id == id; });

    if (it != records.end()) {
        records.erase(it, records.end());
        saveToFile(records);
        displayDesignLine();
        cout << "|   Student record deleted successfully!       |";
        displayDesignLine();
    } else {
        displayDesignLine();
        cout << "|   Student with ID " << id << " not found.        |";
        displayDesignLine();
    }
}

void saveToFile(const deque<Student>& records) {
    ofstream outFile("students.txt");
    for (const auto& student : records) {
        outFile << student.name << "\n";
        outFile << student.id << "\n";
        outFile << student.subjects.size() << "\n";
        for (size_t i = 0; i < student.subjects.size(); i++) {
            outFile << student.subjects[i] << "\n";
            outFile << student.grades[i] << "\n";
        }
        outFile << "-----\n"; 
    }
    outFile.close();
}

void loadFromFile(deque<Student>& records) {
    ifstream inFile("students.txt");
    if (!inFile) return;

    records.clear();
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        Student student;
        student.name = line;
        
        getline(inFile, line);
        student.id = line;
        
        getline(inFile, line);
        int numSubjects = stoi(line);
        
        for (int i = 0; i < numSubjects; i++) {
            getline(inFile, line);
            student.subjects.push_back(line);
            
            getline(inFile, line);
            student.grades.push_back(line);
        }
        
        
        getline(inFile, line);
        records.push_back(student);
    }
    inFile.close();
}