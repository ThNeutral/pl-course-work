#include "student.hpp"
#include "student_registry.hpp"
#include <iostream>
#include <string>

int main() {
    StudentRegistry* registry = new StudentRegistry();
    std::string action;
    while (true) {
        std::cout << "Select action: ";
        std::cin >> action;
        if (action == "help") {
            std::cout << "Actions: help\texit\tprint\tadd\taverage-grade-all\thighest-average-group\tprint-student\tstore-data" << std::endl;
        } else if(action == "exit") {
            exit(0);
        } else if (action == "print") {
            registry->PrintStudents();
        } else if (action == "add") {
            registry->AddStudent(new StudentWithGrades());
        } else if (action == "average-grade-all") {
            registry->PrintStudentsAverageGrade();
        } else if (action == "highest-average-group") {
            int groupNumber;
        GROUP_NUMBER:
            std::cout << "\twrite group number: ";
            std::cin >> groupNumber;
            if (std::cin.fail()) {
                std::cout << "\t\trecieved data is not an integer" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                goto GROUP_NUMBER;
            }
            registry->PrintHighestAverageGradeForGivenGroup(groupNumber);
        } else if (action == "print-student") {
            int facultyNumber;
        FACULTY_NUMBER:
            std::cout << "\twrite student faculty number: ";
            std::cin >> facultyNumber;
            if (std::cin.fail()) {
                std::cout << "\t\trecieved data is not an integer" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                goto FACULTY_NUMBER;
            }
            StudentWithGrades* student = registry->GetStudentWithGivenFacultyNumber(facultyNumber);
            if (student == nullptr) {
                std::cout << "No student found with given faculty number\n";
            } else {
                student->PrintSelf();
            }
        } else if (action == "store-data") {
            std::string filename;
            std::cout << "\twrite filename: ";
            std::cin >> filename;
            int res = registry->WriteToFile(filename);
            if (res != 0) {
                std::cout << "Failed to write data\n";
            }
        } else {
            std::cout << "Unkown action\n";
        }
    }
}