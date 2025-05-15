#pragma once

#include <iostream>
#include <string>
#include <map>
#include "person.hpp"
#include "course.hpp"

/**
 * University class managing the entire course system
 * Handles course registration, information display, and system interface
 */
class University
{
    std::string _university_name;
    std::vector<Course> _courses;
    std::map<std::string, std::shared_ptr<Student>> students; // Map of students indexed by email

public:
    // Constructor initializing university with name and creating default courses
    University(std::string university_name) : _university_name(university_name)
    {
        // Initialize with three default courses and their lecturers
        _courses = {
            Course("Programming", _university_name, std::make_shared<Lecturer>("Dr.", "Frank", "Vance", "frank.vance@uni.edu")),
            Course("Databases", _university_name, std::make_shared<Lecturer>("Prof.", "Kenji", "Tanaka", "kenji.tanaka@uni.edu")),
            Course("Software Engineering", _university_name, std::make_shared<Lecturer>("Dr.", "Alex", "Fince", "alex.finch@uni.edu"))};
    }

    /**
     * Handles the process of registering a student for a course
     * Prompts user for course selection and student details
     */
    void registerForCourse()
    {
        // Display available courses
        std::cout << "\nSelect a Course to Register:" << std::endl;
        for (size_t i = 0; i < _courses.size(); ++i)
        {
            std::cout << i + 1 << ". " << _courses[i].getName() << std::endl;
        }

        // Get course selection from user
        std::cout << "\nEnter course number: ";
        int course_choice;
        std::cin >> course_choice;
        std::cin.ignore();

        if (course_choice < 1 || static_cast<size_t>(course_choice) > _courses.size())
        {
            std::cout << "Invalid course number." << std::endl;
        }

        // Collect student information
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

        std::shared_ptr<Student> student;

        // Check if student already exists in system (by email)
        if (students.count(email))
        {
            student = students[email];
        }
        else
        {
            // Create new student if not found
            student = std::make_shared<Student>(matriculation_number, university, first_name, last_name, email);
            students[email] = student;
        }

        // Add student to selected course
        _courses[course_choice - 1].addStudent(student);
    }

    /**
     * Displays information about selected course(s)
     * Allows viewing details for one course or all courses
     */
    void displayCourseInfo()
    {
        int counter = 1;
        std::cout << "\nSelect Course to view Details" << std::endl;

        // List all available courses
        for (const auto &course : _courses)
        {
            std::cout << counter << ". " << course.getName() << std::endl;
            ++counter;
        }
        // Alternative for-loop approach left commented out
        // for (size_t i = 0; i < _courses.size(); ++i)
        // {
        //     std::cout << i + 1 << ". " << _courses[i].getName() << std::endl;
        // }

        // Option to show all courses
        std::cout << counter << ". Show all Courses' details" << std::endl;

        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Enter your choice (1-" << counter << "): ";
        int course_choice;
        std::cin >> course_choice;
        std::cin.ignore();

        // Display information for selected course
        if (course_choice >= 1 && course_choice <= _courses.size())
        {
            std::cout << "\n----------------------------------------" << std::endl;
            _courses[course_choice - 1].displayInfo();
            std::cout << "\nParticipants:" << std::endl;
            _courses[course_choice - 1].displayParticipants();
            if (!_courses[course_choice - 1].willTakePlace())
            {
                std::cout << "\nThis course will not take place" << std::endl;
            }
            std::cout << "----------------------------------------" << std::endl;
        }
        // Display information for all courses
        else if (course_choice == counter)
        {
            for (const auto &course : _courses)
            {
                std::cout << "\n----------------------------------------" << std::endl;
                course.displayInfo();
                std::cout << "Participants:" << std::endl;
                course.displayParticipants();
                if (!course.willTakePlace())
                {
                    std::cout << "\nThis course will not take place" << std::endl;
                }
                std::cout << "----------------------------------------" << std::endl;
            }
        }
    }

    /**
     * Displays all courses that still have open slots
     * Shows courses that aren't fully booked
     */
    void displayFreeCourses()
    {
        std::cout << "\nShowing available courses" << std::endl;
        for (const auto &course : _courses)
        {
            if (!course.isFull())
            {
                std::cout << "\n----------------------------------------" << std::endl;
                course.displayInfo();
                std::cout << "----------------------------------------" << std::endl;
            }
        }
    }

    /**
     * Identifies and displays information about courses that will be cancelled
     * Courses without minimum required students will not take place
     */
    void notifyCancelledCourse()
    {
        for (const auto &course : _courses)
        {
            if (!course.willTakePlace())
            {
                std::cout << "\n----------------------------------------" << std::endl;
                std::cout << "Course " << course.getName() << " is cancelled." << std::endl;
                std::cout << "Participants to notify" << std::endl;
                course.displayParticipants();
                std::cout << "----------------------------------------" << std::endl;
            }
        }
    }

    /**
     * Displays the main menu and handles user interaction with the system
     * Controls the flow of the program
     */
    void displayMenu()
    {
        int choice;
        bool exit = false;
        while (!exit)
        {
            // Display main menu options
            std::cout << "\n====== UNIVERSITY COURSE MANAGEMENT SYSTEM ======" << std::endl;
            std::cout << "1. Register for a course" << std::endl;
            std::cout << "2. Display course information" << std::endl;
            std::cout << "3. Display courses not fully booked" << std::endl;
            std::cout << "4. Exit program" << std::endl;
            std::cout << "=================================================" << std::endl;
            std::cout << "Enter your choice (1-4): ";

            std::cin >> choice;
            std::cin.ignore();

            // Process user selection
            switch (choice)
            {
            case 1:
                registerForCourse();
                break;
            case 2:
                displayCourseInfo();
                break;
            case 3:
                displayFreeCourses();
                break;
            case 4:
                notifyCancelledCourse(); // Show cancelled courses before exit
                exit = true;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 4: ";
            }
        }

        std::cout << "\nThank you for using the University Course Management System!\n"
                  << std::endl;
    }
};