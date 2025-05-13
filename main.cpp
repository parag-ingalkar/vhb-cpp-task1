#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "person.hpp"
#include "course.hpp"

int main()
{
    std::vector<Course> courses = {
        Course("Programming", Lecturer("Dr.", "Frank", "Vance", "frank.vance@uni.edu")),
        Course("Databases", Lecturer("Prof.", "Kenji", "Tanaka", "kenji.tanaka@uni.edu")),
        Course("Software Engineering", Lecturer("Dr.", "Alex", "Fince", "alex.finch@uni.edu"))};

    std::vector<Student> students;

    while (true)
    {
        std::cout << std::endl
                  << "=== Course Management Menu ===" << std::endl;
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
                std::cout << i + 1 << ". " << courses[i].get_name() << std::endl;
            }

            std::cout << "\nEnter Course number: ";

            int course_choice;
            std::cin >> course_choice;
            std::cin.ignore();

            if (course_choice < 1 || course_choice > courses.size())
            {
                std::cout << "Invalid Course number." << std::endl;
                continue;
            }

            std::string first_name, last_name, email, matriculation_num, university;
            std::cout << "Enter student first name: ";
            std::getline(std::cin, first_name);
            std::cout << "Enter student surname: ";
            std::getline(std::cin, last_name);
            std::cout << "Enter email: ";
            std::getline(std::cin, email);
            std::cout << "Enter matriculation number: ";
            std::getline(std::cin, matriculation_num);
            std::cout << "Enter university: ";
            std::getline(std::cin, university);

            Student student = Student(matriculation_num, university, first_name, last_name, email);
            courses[course_choice - 1].add_student(student);
            students.push_back(student);
        }
        else if (choice == 2)
        {
            std::cout << "\nCourse Details" << std::endl;
            for (size_t i = 0; i < courses.size(); ++i)
            {
                std::cout << i + 1 << ". " << courses[i].get_name() << std::endl;
            }
            std::cout << courses.size() + 1 << ". Show all courses' details" << std::endl;

            int course_choice;
            std::cout << "Choice: ";
            std::cin >> course_choice;
            std::cin.ignore();

            if (course_choice >= 1 && course_choice <= courses.size())
            {
                std::cout << "----------------------------------------" << std::endl;
                courses[course_choice - 1].display_info();
                courses[course_choice - 1].display_participants();
                if (!(courses[course_choice - 1].will_take_place()))
                {
                    std::cout << "\nThis course will not take place" << std::endl;
                }
                std::cout << "----------------------------------------" << std::endl;
            }
            else if (course_choice == (courses.size() + 1))
            {
                for (auto course : courses)
                {
                    std::cout << "----------------------------------------" << std::endl;
                    course.display_info();
                    course.display_participants();
                    if (!(course.will_take_place()))
                    {
                        std::cout << "\nThis course will not take place" << std::endl;
                    }
                    std::cout << "----------------------------------------" << std::endl;
                }
            }
        }
        else if (choice == 3)
        {
            std::cout << "\nShowing available Courses" << std::endl;
            for (auto course : courses)
            {
                if (!course.is_full())
                {
                    std::cout << "----------------------------------------" << std::endl;
                    course.display_info();
                    std::cout << "----------------------------------------" << std::endl;
                }
            }
        }
        else if (choice == 4)
        {
            for (auto course : courses)
            {
                if (!(course.will_take_place()))
                {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Course " << course.get_name() << " is cancelled." << std::endl;
                    std::cout << "Notifying below  participants: " << std::endl;
                    for (auto participant : course.get_participants())
                    {
                        std::cout << participant.get_name() << "(" << participant.get_email() << ")" << std::endl;
                    }
                    std::cout << "----------------------------------------" << std::endl;
                }
            }
            break;
        }
        else
        {
            std::cout << "\nInvalid option. Try Again." << std::endl;
        }
    }
}
