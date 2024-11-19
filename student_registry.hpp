#pragma once
#include "student.hpp"
#include <string>
#include <fstream>
#include <iostream>

class StudentRegistry {
protected:
    std::vector<StudentWithGrades*> students;
public:
    StudentRegistry() {
        int numberOfStudents;
        STUDENTS_LABEL:
        std::cout << "Creating student registry. Enter number of students to create: ";
        std::cin >> numberOfStudents; 
        if (std::cin.fail()) {
            std::cout << "\trecieved data is not an integer" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto STUDENTS_LABEL;
        }
        for (int i = 0; i < numberOfStudents; i++) {
            std::cout << "Creating student number " << i+1 << std::endl;
            students.push_back(new StudentWithGrades());
        }
    }

    ~StudentRegistry() {
        for (int i = 0; i < students.size(); i++) {
            delete students[i];
        }
        students.clear();
    }

    void PrintStudents() {
        for (int i = 0; i < this->students.size(); i++) {
            this->students[i]->PrintSelf();
        }
    }

    void PrintStudentsAverageGrade() {
        for (int i = 0; i < this->students.size(); i++) {
            this->students[i]->PrintAverageGrades();
        }
    }

    void AddStudent(StudentWithGrades* student) {
        if (student == nullptr) {
            return;
        }
        this->students.push_back(student);
    }

    void PrintHighestAverageGradeForGivenGroup(int groupNumber) {
        StudentWithGrades* student = nullptr;
        float maximum = std::numeric_limits<float>::min();
        for (int i = 0; i < this->students.size(); i++) {
            if (this->students[i]->GetGroupNumber() != groupNumber) continue;
            float grade = this->students[i]->GetAverageGradeAmongstAllSemesters();
            if (grade > maximum) {
                student = this->students[i];
                maximum = grade;
            }
        }
        if (student == nullptr) {
            std::cout << "No student from given group was found" << std::endl;
        } else {
            std::cout << "Student " << student->GetName() << " has highest average mark of " << maximum << std::endl;
        }
    }

    StudentWithGrades* GetStudentWithGivenFacultyNumber(int facultyNumber) {
        for (int i = 0; i < this->students.size(); i++) {
            if (this->students[i]->GetFacultyNumber() == facultyNumber) {
                return this->students[i];
            }
        }
        return nullptr;
    }

    int WriteToFile(std::string filename) {
        std::string content = "";
        for (int i = 0; i < this->students.size(); i++) {
            content += this->students[i]->StringifySelf() + "\n";
        }
        
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << content;
            outFile.close();
            return 0;
        } else {
            return 1;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, StudentRegistry* registry) {
        if (registry == nullptr) {
            os << "null" << std::endl;
        } else {
            registry->PrintStudents();
        }
        return os;
    };
};