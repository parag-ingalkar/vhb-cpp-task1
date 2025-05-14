#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "person.hpp"
#include "course.hpp"

int main()
{
    std::vector<Course> courses = {
        Course("Programming", std::make_shared<Lecturer>("Dr.", "Frank", "Vance", "frank.vance@uni.edu")),
        Course("Databases", std::make_shared<Lecturer>("Prof.", "Kenji", "Tanaka", "kenji.tanaka@uni.edu")),
        Course("Software Engineering", std::make_shared<Lecturer>("Dr.", "Alex", "Fince", "alex.finch@uni.edu"))};

    std::vector<std::shared_ptr<Student>> students;

    while (true)
    {
        std::cout << "\n=== Course Management Menu ===" << std::endl;
        std::cout << "1. Register for a course" << std::endl;
        std::cout << "2. Show one/all courses with participants" << std::endl;
        std::cout << "3. Show courses not fully booked" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1)
        {
            std::cout << "\nAvailable Courses:" << std::endl;
            for (size_t i = 0; i < courses.size(); ++i)
            {
                std::cout << i + 1 << ". " << courses[i].getName() << std::endl;
            }

            std::cout << "\nEnter course number: ";
            int course_choice;
            std::cin >> course_choice;
            std::cin.ignore();

            if (course_choice < 1 || static_cast<size_t>(course_choice) > courses.size())
            {
                std::cout << "Invalid course number." << std::endl;
                continue;
            }

            std::string first_name, last_name, email, matriculation_number, university;
            std::cout << "Enter student first name: ";
            std::getline(std::cin, first_name);
            std::cout << "Enter student surname: ";
            std::getline(std::cin, last_name);
            std::cout << "Enter email: ";
            std::getline(std::cin, email);
            std::cout << "Enter matriculation number: ";
            std::getline(std::cin, matriculation_number);
            std::cout << "Enter university: ";
            std::getline(std::cin, university);

            // Student student(matriculation_number, university, first_name, last_name, email);
            std::shared_ptr<Student> student = std::make_shared<Student>(matriculation_number, university, first_name, last_name, email);
            courses[course_choice - 1].addStudent(student);
            students.push_back(student);
        }
        else if (choice == 2)
        {
            std::cout << "\nCourse Details" << std::endl;
            for (size_t i = 0; i < courses.size(); ++i)
            {
                std::cout << i + 1 << ". " << courses[i].getName() << std::endl;
            }
            std::cout << courses.size() + 1 << ". Show all courses' details" << std::endl;

            int course_choice;
            std::cout << "Choice: ";
            std::cin >> course_choice;
            std::cin.ignore();

            if (course_choice >= 1 && course_choice <= courses.size())
            {
                std::cout << "----------------------------------------" << std::endl;
                courses[course_choice - 1].displayInfo();
                courses[course_choice - 1].displayParticipants();
                if (!courses[course_choice - 1].willTakePlace())
                {
                    std::cout << "\nThis course will not take place" << std::endl;
                }
                std::cout << "----------------------------------------" << std::endl;
            }
            else if (course_choice == static_cast<int>(courses.size()) + 1)
            {
                for (auto &course : courses)
                {
                    std::cout << "----------------------------------------" << std::endl;
                    course.displayInfo();
                    course.displayParticipants();
                    if (!course.willTakePlace())
                    {
                        std::cout << "\nThis course will not take place" << std::endl;
                    }
                    std::cout << "----------------------------------------" << std::endl;
                }
            }
        }
        else if (choice == 3)
        {
            std::cout << "\nShowing available courses" << std::endl;
            for (auto &course : courses)
            {
                if (!course.isFull())
                {
                    std::cout << "----------------------------------------" << std::endl;
                    course.displayInfo();
                    std::cout << "----------------------------------------" << std::endl;
                }
            }
        }
        else if (choice == 4)
        {
            for (auto &course : courses)
            {
                if (!course.willTakePlace())
                {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Course " << course.getName() << " is cancelled." << std::endl;
                    std::cout << "Notifying Participants" << std::endl;
                    course.displayParticipants();
                    std::cout << "----------------------------------------" << std::endl;
                }
            }
            break;
        }
        else
        {
            std::cout << "\nInvalid option. Try again." << std::endl;
        }
    }

    return 0;
}
