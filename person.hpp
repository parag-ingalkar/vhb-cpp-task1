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

    virtual std::string getName() const { return _first_name + " " + _surname; }

    std::string getEmail() const { return _email; }

    virtual void print() const
    {
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Email: " << getEmail() << std::endl;
    }
};

class Lecturer : public Person
{
    std::string _academic_title;

public:
    Lecturer(std::string academic_title, std::string first_name, std::string surname, std::string email)
        : Person(first_name, surname, email), _academic_title(academic_title) {}

    std::string getAcademicTitle() const { return _academic_title; }

    std::string getName() const override
    {
        return _academic_title + " " + Person::getName();
    }

    void print() const override
    {
        std::cout << "Lecturer: " << getName() << std::endl;
        std::cout << "Email: " << getEmail() << std::endl;
    }
};

class Student : public Person
{
    std::string _matriculation_number;
    std::string _university;
    int _num_of_courses_enrolled = 0;

public:
    Student(const std::string &matriculation_number, const std::string &university,
            const std::string &first_name, const std::string &surname, const std::string &email)
        : Person(first_name, surname, email),
          _matriculation_number(matriculation_number),
          _university(university) {}

    std::string getUniversity() const { return _university; }

    std::string getMatriculationNumber() const { return _matriculation_number; }

    bool isHomeStudent() const { return _university == "FAU"; }

    int getNumCoursesEnrolled() const { return _num_of_courses_enrolled; }

    void enrollToCourse() { _num_of_courses_enrolled++; }

    void print() const override
    {
        std::cout << "Student: " << getName() << std::endl;
        std::cout << "Email: " << getEmail() << std::endl;
        std::cout << "Matriculation Number: " << _matriculation_number << std::endl;
        std::cout << "University: " << _university << std::endl;
        std::cout << "Enrolled Courses: " << _num_of_courses_enrolled << std::endl;
    }
};
