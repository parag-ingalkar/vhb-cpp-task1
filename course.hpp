#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "person.hpp"

class Course
{
    std::string _course_name;
    std::shared_ptr<Lecturer> _lecturer;
    std::string _offering_university;
    std::vector<std::shared_ptr<Person>> _participants;
    static const int MAX_PARTICIPANTS = 2;
    static const int MIN_PARTICIPANTS = 1;

public:
    Course(std::string course_name, const std::shared_ptr<Lecturer> &lecturer, std::string offering_university = "FAU")
        : _course_name(course_name), _lecturer(lecturer), _offering_university(offering_university)
    {
        _participants.push_back(_lecturer);
    }

    bool isFull() const { return (_participants.size() - 1) >= MAX_PARTICIPANTS; }

    int getFreeSlots() const { return MAX_PARTICIPANTS - static_cast<int>((_participants.size() - 1)); }

    int getNumberOfParticipants() const { return static_cast<int>(_participants.size()); }

    std::string getName() const { return _course_name; }

    std::shared_ptr<Lecturer> getLecturer() const { return _lecturer; }

    std::vector<std::shared_ptr<Person>> getParticipants() const { return _participants; }

    bool willTakePlace() const { return (_participants.size() - 1) >= MIN_PARTICIPANTS; }

    void addStudent(const std::shared_ptr<Student> &student)
    {
        std::cout << "----------------------------------------" << std::endl;

        if (isFull())
        {
            std::cout << "Course is already full." << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            return;
        }

        for (const auto &existing_student : _participants)
        {
            if (existing_student->getEmail() == student->getEmail())
            {
                std::cout << "Student already registered." << std::endl;
                std::cout << "----------------------------------------" << std::endl;
                return;
            }
        }

        if ((student->getUniversity() != _offering_university) && (student->getNumCoursesEnrolled() >= 1))
        {
            std::cout << "Cannot register to more than one course." << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            return;
        }

        student->enrollToCourse();
        _participants.push_back(student);

        std::cout << "Student " << student->getName() << " successfully enrolled in " << _course_name << "." << std::endl;
        std::cout << "number of course enrolled " << student->getNumCoursesEnrolled() << std::endl;
        std::cout << "student from university" << student->getUniversity() << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }

    void displayInfo() const
    {
        std::cout << "Course: " << _course_name << std::endl;
        std::cout << "Lecturer: " << _lecturer->getName() << std::endl;
        std::cout << getFreeSlots() << " out of " << MAX_PARTICIPANTS << " slots are available." << std::endl;
    }

    void displayParticipants() const
    {
        std::cout << "\nParticipants:" << std::endl;
        for (const auto &participant : _participants)
        {
            std::cout << "\t" << participant->getName() << " (" << participant->getEmail() << ")" << std::endl;
        }
    }
};
