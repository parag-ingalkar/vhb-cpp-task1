#pragma once

#include <iostream>
#include <string>
#include "person.hpp"
#include <vector>

class Course
{
    std::string _course_name;
    Lecturer _lecturer;
    std::string _offering_university;
    std::vector<Student> _participants;
    static const int MAX_PARTICIPANTS = 2;
    static const int MIN_PARTICIPANTS = 1;

public:
    Course(std::string course_name, Lecturer lecturer, std::string _offering_university = "FAU") : _course_name(course_name), _lecturer(lecturer)
    {
        // _participants.push_back(_lecturer);
    }

    bool is_full() { return _participants.size() >= MAX_PARTICIPANTS; }
    int get_free_slots() const { return MAX_PARTICIPANTS - _participants.size(); }
    int get_number_of_participants() const { return _participants.size(); }
    std::string get_name() const { return _course_name; }
    std::string get_lecturer() const { return _lecturer.get_name(); }
    void add_student(Student student)
    {
        std::cout << "----------------------------------------" << std::endl;
        if (is_full())
        {
            std::cout << "Course is already full." << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            return;
        }

        for (auto s : _participants)
        {
            if (s.get_email() == student.get_email())
            {
                std::cout << "Student already registered." << std::endl;
                std::cout << "----------------------------------------" << std::endl;
                return;
            }
        }

        if ((student.get_university() != _offering_university) && (student.get_num_courses_enrolled() >= 1))
        {
            std::cout << "Cannot register to more than One course" << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            return;
        }

        _participants.push_back(student);
        student.enroll_to_course();
        std::cout << "Student " << student.get_name() << " succesfully enrolled in " << _course_name << "." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
    bool will_take_place() { return _participants.size() >= MIN_PARTICIPANTS; }
    const std::vector<Student> get_participants() const { return _participants; }

    void display_info()
    {
        std::cout << "Course: " << _course_name << std::endl;
        std::cout << "Lecturer: " << get_lecturer() << std::endl;
        std::cout << get_free_slots() << " out of " << MAX_PARTICIPANTS << " slots are available." << std::endl;
    }

    void display_participants()
    {
        std::cout << "\nParticipants:" << std::endl;
        for (auto participant : _participants)
        {
            std::cout << "\t" << participant.get_name() << "(" << participant.get_email() << ")" << std::endl;
        }
    }
};
