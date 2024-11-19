#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>

class Student {
protected:
    std::string name;
    std::string course;
    int facultyNumber;
    int groupNumber;
public:
    Student() {
        std::cout << "Creating new student" << std::endl;
        std::cout << "\twrite name: ";
        std::cin >> this->name;
    
        std::cout << "\twrite course: ";
        std::cin >> this->course;
    
    FACULTY_NUMBER:
        std::cout << "\twrite faculty number: ";
        std::cin >> this->facultyNumber;
        if (std::cin.fail()) {
            std::cout << "\t\trecieved data is not an integer" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto FACULTY_NUMBER;
        }

    GROUP_NUMBER:
        std::cout << "\twrite group number: ";
        std::cin >> this->groupNumber;
        if (std::cin.fail()) {
            std::cout << "\t\trecieved data is not an integer" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto GROUP_NUMBER;
        }
    }

    int GetFacultyNumber() {
        return this->facultyNumber;
    }

    std::string GetName() {
        return this->name;
    }

    int GetGroupNumber() {
        return this->groupNumber;
    }

    virtual void PrintSelf() {
        std::cout << "Student {\n\tname: " << this->name << "\n\tcourse: " << this->course << "\n\tfacultyNumber: " << this->facultyNumber <<"\n\tgroupNumber: " << this->groupNumber << "\n}" << std::endl; 
    }

    friend std::ostream& operator<<(std::ostream& os, Student& student) {
        student.PrintSelf();
        return os;
    } 
};

class StudentWithGrades : public Student {
protected:
    std::vector<std::vector<int>> grades;
public:
    StudentWithGrades() : Student() {
        int numberOfSemesters;
    GROUP_NUMBER:
        std::cout << "\twrite number of semesters this student took part in: ";
        std::cin >> numberOfSemesters;
        if (std::cin.fail()) {
            std::cout << "\t\trecieved data is not an integer" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto GROUP_NUMBER;
        }
        int currentGrade;
        for (int i = 0; i < numberOfSemesters; i++) {
            std::cout << "\tcreating marks for semester " << i + 1 << std::endl;
            std::vector<int> gradesSemester;
            for (int j = 0; j < 5; j++) {
            SEMESTER_GRADES_INNER:
                std::cout << "\t\twrite " << j + 1 << " mark: ";
                std::cin >> currentGrade; 
                if (std::cin.fail()) {
                    std::cout << "\t\t\trecieved data is not an integer" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    goto SEMESTER_GRADES_INNER;
                }
                gradesSemester.push_back(currentGrade);
            }
            grades.push_back(gradesSemester);
        }
    }

    virtual void PrintSelf() {
        std::cout << "Student {\n\tname: " << this->name << "\n\tcourse: " << this->course << "\n\tfacultyNumber: " << this->facultyNumber <<"\n\tgroupNumber: " << this->groupNumber << "\n";
        for (int i = 0; i < this->grades.size(); i++) {
            std::cout << "\tgrades for semester " << i + 1 << "\n";
            for (int j = 0; j < 5; j++) {
                std::cout << "\t\tgrade " << j + 1 << ": " << grades[i][j] << "\n";    
            }
        } 
        std::cout << "}" << std::endl;
    }

    float GetAverageGradeForGivenSemester(int semesterNumber) {
        int sumLocal = 0;
        for (int j = 0; j < 5; j++) {
            sumLocal += grades[semesterNumber][j];    
        }
        return (float)sumLocal / 5.0;
    }

    float GetAverageGradeAmongstAllSemesters() {
        int numberOfSemesters = this->grades.size();
        int sumGlobal = 0;
        for (int i = 0; i < numberOfSemesters; i++) {
            sumGlobal += this->GetAverageGradeForGivenSemester(i);
        }
        return (float)sumGlobal / (float)numberOfSemesters;
    }

    void PrintAverageGrades() {
        std::cout << "Average grades of student " << this->name << std::endl;
        for (int i = 0; i < this->grades.size(); i++) {
            std::cout << "\tsemester " << i + 1 << ": " << this->GetAverageGradeForGivenSemester(i) << std::endl;
        } 
        std::cout << "\toverall: " << this->GetAverageGradeAmongstAllSemesters() << std::endl; 
    }

    
    std::string StringifySelf() {
        std::string str = this->name + "," + this->course + "," + std::to_string(this->facultyNumber) + "," + std::to_string(this->groupNumber) + "," + std::to_string(this->grades.size()) + ",";
        for (int i = 0; i < this->grades.size(); i++) {
            str += std::to_string(5) + ",";
            for (int j = 0; j < 5; j++) {
                str += std::to_string(this->grades[i][j]) + ",";
            }
        }
        str[str.size() - 1] = ';';
        return str;
    }

    friend std::ostream& operator<<(std::ostream& os, StudentWithGrades* student) {
        if (student == nullptr) {
            os << "null" << std::endl;
        } else {
            student->PrintSelf();
        }
        return os;
    };
};