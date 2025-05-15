#pragma once

#include <iostream>
#include <string>

/**
 * Base class representing a person in the university system
 * Contains basic personal information like name and email
 */
class Person
{
    std::string _first_name;
    std::string _surname;
    std::string _email;

public:
    // Constructor to initialize person with basic details
    Person(std::string first_name, std::string surname, std::string email)
        : _first_name(first_name), _surname(surname), _email(email) {}

    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~Person() {}

    // Returns full name of the person
    // Virtual method that can be overridden by derived classes
    virtual std::string getName() const { return _first_name + " " + _surname; }

    // Returns email address
    std::string getEmail() const { return _email; }

    // Displays person's information to console
    // Virtual method that can be overridden by derived classes
    virtual void print() const
    {
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Email: " << getEmail() << std::endl;
    }
};

/**
 * Lecturer class extending Person with academic details
 * Represents a university lecturer/professor
 */
class Lecturer : public Person
{
    std::string _academic_title;

public:
    // Constructor adding academic title to person information
    Lecturer(std::string academic_title, std::string first_name, std::string surname, std::string email)
        : Person(first_name, surname, email), _academic_title(academic_title) {}

    // Returns academic title (e.g., "Dr.", "Prof.")
    std::string getAcademicTitle() const { return _academic_title; }

    // Override getName to include academic title
    std::string getName() const override { return _academic_title + " " + Person::getName(); }

    // Override print to show lecturer-specific information
    void print() const override
    {
        std::cout << "Lecturer: " << getName() << std::endl;
        std::cout << "Email: " << getEmail() << std::endl;
    }
};

/**
 * Student class extending Person with student-specific details
 * Contains university and enrollment information
 */
class Student : public Person
{
    std::string _matriculation_number; // Student ID
    std::string _university;           // University name
    int _num_of_courses_enrolled = 0;  // Counter for enrolled courses

public:
    // Constructor initializing student with university-specific details
    Student(const std::string &matriculation_number, const std::string &university,
            const std::string &first_name, const std::string &surname, const std::string &email)
        : Person(first_name, surname, email),
          _matriculation_number(matriculation_number),
          _university(university) {}

    // Returns the university name
    std::string getUniversity() const { return _university; }

    // Returns student's matriculation/ID number
    std::string getMatriculationNumber() const { return _matriculation_number; }

    // Checks if student is from FAU university (considered "home" student)
    bool isHomeStudent() const { return _university == "FAU"; }

    // Returns number of courses student is enrolled in
    int getNumCoursesEnrolled() const { return _num_of_courses_enrolled; }

    // Increments the enrolled courses counter when student registers for a course
    void enrollToCourse() { _num_of_courses_enrolled++; }

    // Override print to show student-specific information
    void print() const override
    {
        std::cout << "Student: " << getName() << std::endl;
        std::cout << "Email: " << getEmail() << std::endl;
        std::cout << "Matriculation Number: " << _matriculation_number << std::endl;
        std::cout << "University: " << _university << std::endl;
        std::cout << "Enrolled Courses: " << _num_of_courses_enrolled << std::endl;
    }
};