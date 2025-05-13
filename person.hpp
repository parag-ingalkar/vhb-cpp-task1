#pragma once

#include <iostream>
#include <string>

class Person
{
    std::string _first_name;
    std::string _surname;
    std::string _email;

public:
    Person(std::string first_name, std::string surname, std::string email)
        : _first_name(first_name), _surname(surname), _email(email) {}

    virtual ~Person() {}

    virtual std::string get_name() const { return _first_name + " " + _surname; }

    std::string get_email() const { return _email; }

    virtual void print() const
    {
        std::cout << "Name: " << get_name() << std::endl;
        std::cout << "Email: " << get_email() << std::endl;
    }
};

// std::ostream &operator<<(std::ostream &out, const Person &person)
// {
//     out << person.get_name() << "\n";
//     out << person.get_email() << std::endl;
//     return out;
// }

class Lecturer : public Person
{
    std::string _academic_title;

public:
    Lecturer(std::string title, std::string first_name, std::string surname, std::string email)
        : Person(first_name, surname, email), _academic_title(title) {}

    std::string get_academic_title() const { return _academic_title; }
    std::string get_name() const override { return _academic_title + " " + Person::get_name(); }

    void print() const override
    {
        std::cout << "Lecturer: " << get_name() << std::endl;
        std::cout << "Email: " << get_email() << std::endl;
    }
};

class Student : public Person
{
    std::string _matriculation_number;
    std::string _university;
    int _num_of_courses_enrolled = 0;

public:
    Student(const std::string &matriculation_number, const std::string &university, const std::string &first_name, const std::string &surname, const std::string &email)
        : Person(first_name, surname, email), _matriculation_number(matriculation_number), _university(university) {}

    std::string get_university() const { return _university; }
    std::string getMatriculationNumber() const { return _matriculation_number; }
    bool is_home_student() const { return _university == "FAU"; }
    int get_num_courses_enrolled() const { return _num_of_courses_enrolled; }
    void enroll_to_course() { _num_of_courses_enrolled++; }

    void print() const override
    {
        std::cout << "Student: " << get_name() << std::endl;
        std::cout << "Email: " << get_email() << std::endl;
        std::cout << "Matriculation Number: " << _matriculation_number << std::endl;
        std::cout << "University: " << _university << std::endl;
        std::cout << "Enrolled Courses: " << _num_of_courses_enrolled << std::endl;
    }
};