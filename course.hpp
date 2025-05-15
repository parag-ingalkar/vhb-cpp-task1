#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "person.hpp"

/**
 * Course class representing a university course
 * Manages course details, lecturer, and enrolled students
 */
class Course
{
    std::string _course_name;
    std::shared_ptr<Lecturer> _lecturer;
    std::string _offering_university;
    std::vector<std::shared_ptr<Person>> _participants; // Both lecturer and students
    static const int MAX_PARTICIPANTS = 2;              // Maximum number of students allowed
    static const int MIN_PARTICIPANTS = 1;              // Minimum number of students required for course to run

public:
    // Constructor initializing course with name, university, and lecturer
    Course(std::string course_name, std::string offering_university, const std::shared_ptr<Lecturer> &lecturer)
        : _course_name(course_name), _lecturer(lecturer), _offering_university(offering_university)
    {
        // Lecturer is automatically added as a participant
        _participants.push_back(_lecturer);
    }

    // Checks if course has reached maximum capacity
    bool isFull() const { return (_participants.size() - 1) >= MAX_PARTICIPANTS; }

    // Returns number of available slots for students
    int getFreeSlots() const { return MAX_PARTICIPANTS - static_cast<int>((_participants.size() - 1)); }

    // Returns total number of participants (including lecturer)
    int getNumberOfParticipants() const { return static_cast<int>(_participants.size()); }

    // Returns course name
    std::string getName() const { return _course_name; }

    // Returns pointer to course lecturer
    std::shared_ptr<Lecturer> getLecturer() const { return _lecturer; }

    // Returns list of all participants (lecturer and students)
    std::vector<std::shared_ptr<Person>> getParticipants() const { return _participants; }

    // Checks if course has minimum required number of students to run
    bool willTakePlace() const { return (_participants.size() - 1) >= MIN_PARTICIPANTS; }

    /**
     * Attempts to add a student to the course
     * Performs various checks before enrollment:
     * - Checks if course is full
     * - Checks if student is already registered
     * - Checks external university student enrollment limits
     */
    void addStudent(const std::shared_ptr<Student> &student)
    {
        std::cout << "----------------------------------------" << std::endl;

        // Check if course is already at capacity
        if (isFull())
        {
            std::cout << "Could not register student. Course is already full." << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            return;
        }

        // Check if student is already registered for this course
        for (const auto &existing_student : _participants)
        {
            if (existing_student->getEmail() == student->getEmail())
            {
                std::cout << "Student already registered." << std::endl;
                std::cout << "----------------------------------------" << std::endl;
                return;
            }
        }

        // External university students can't register for more than one course
        if ((student->getUniversity() != _offering_university) && (student->getNumCoursesEnrolled() >= 1))
        {
            std::cout << "External University student cannot register to more than one course." << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            return;
        }

        // Successful enrollment
        student->enrollToCourse();
        _participants.push_back(student);
        std::cout << "Student " << student->getName() << " successfully enrolled in " << _course_name << "." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }

    // Displays basic course information
    void displayInfo() const
    {
        std::cout << "Course: " << _course_name << std::endl;
        std::cout << "Lecturer: " << _lecturer->getName() << std::endl;
        std::cout << getFreeSlots() << " out of " << MAX_PARTICIPANTS << " slots are available." << std::endl;
    }

    // Displays list of all participants in the course
    void displayParticipants() const
    {
        for (const auto &participant : _participants)
        {
            std::cout << "\t" << participant->getName() << " (" << participant->getEmail() << ")" << std::endl;
        }
    }
};