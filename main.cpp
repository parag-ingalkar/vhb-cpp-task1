#include <iostream>
#include <string>

class Course {

};

class Person {
    std::string surname;
    std::string first_name;
    std::string email;

    public:
    Person(std::string srname, std::string fname, std::string email) : surname(srname), first_name(fname), email(email){}

    virtual ~Person() {}

};

class Lecturer : public Person {
    std::string academic_title;
};

class Student : public Person {
    std::string matriculation_number;
    std::string university;
};
