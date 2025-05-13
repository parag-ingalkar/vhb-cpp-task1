#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Person
{
    std::string _first_name;
    std::string _surname;
    std::string _email;

public:
    Person(std::string first_name, std::string surname, std::string email)
        : _first_name(first_name), _surname(surname), _email(email) {}

    virtual ~Person() = default;

    virtual std::string get_name() const
    {
        return _first_name + " " + _surname;
    }

    virtual std::string get_email() const
    {
        return _email;
    }

    virtual void print() const
    {
        std::cout << "Name: " << _first_name << " " << _surname << std::endl;
        std::cout << "Email: " << _email << std::endl;
    }
};
std::ostream &operator<<(std::ostream &out, const Person &person)
{
    out << person.get_name() << "\n";
    out << person.get_email() << std::endl;
    return out;
}

class Lecturer : public Person
{
    std::string _academic_title;

public:
    Lecturer(std::string title, std::string first_name, std::string surname, std::string email)
        : Person(first_name, surname, email), _academic_title(title) {}

    void print() const override
    {
        std::cout << _academic_title << " " << this->get_name() << std::endl;
        std::cout << this->get_email() << std::endl;
    }
};

class Student : public Person
{
    std::string _matriculation_number;
    std::string _university;

public:
    int _num_of_courses_enrolled = 0;
    Student(std::string matriculation_number, std::string university, std::string first_name, std::string surname, std::string email)
        : Person(first_name, surname, email), _matriculation_number(matriculation_number), _university(university) {}

    std::string get_university() { return _university; }
    int get_num_courses_enrolled() { return _num_of_courses_enrolled; }

    void print() const override
    {
        std::cout << "Matriculation Number: " << _matriculation_number << std::endl;
        std::cout << "University: " << _university << std::endl;
        std::cout << "Name:  " << this->get_name() << std::endl;
        std::cout << this->get_email() << std::endl;
    }
};

class Course
{
    std::string _course_name;
    Lecturer _lecturer;
    std::string _offering_university;
    std::vector<Student> _participants;
    const int _max_participants = 2;
    const int _min_participants = 1;

public:
    Course(std::string course_name, Lecturer lecturer, std::string _offering_university = "FAU") : _course_name(course_name), _lecturer(lecturer) {}

    bool isFull() { return _participants.size() >= _max_participants; }
    int free_solts() { return _max_participants - _participants.size(); }
    int number_of_participants() { return _participants.size(); }
    std::string get_name() { return _course_name; }
    void add_student(Student student)
    {
        if (isFull())
        {
            std::cout << "Course is already full." << std::endl;
            return;
        }

        for (auto s : _participants)
        {
            if (s.get_email() == student.get_email())
            {
                std::cout << "Student already registered." << std::endl;
                return;
            }
        }

        if ((student.get_university() != _offering_university) && (student._num_of_courses_enrolled >= 1))
        {
            std::cout << "Cannot register to more than One course" << std::endl;
            return;
        }

        _participants.push_back(student);
        student._num_of_courses_enrolled++;
        std::cout << "Student registered succesfully." << std::endl;
    }
};

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
            std::cout << "Available Courses" << std::endl;
            for (size_t i = 0; i < courses.size(); ++i)
            {
                std::cout << i + 1 << ". " << courses[i].get_name() << std::endl;
            }

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
            getline(std::cin, first_name);
            std::cout << "Enter student surname: ";
            getline(std::cin, last_name);
            std::cout << "Enter email: ";
            getline(std::cin, email);
            std::cout << "Enter matriculation number: ";
            getline(std::cin, matriculation_num);
            std::cout << "Enter university: ";
            getline(std::cin, university);

            Student student = Student(matriculation_num, university, first_name, last_name, email);
            courses[course_choice - 1].add_student(student);
            students.push_back(student);
        }
        else if (choice == 2)
        {
            std::cout << "Course Details" << std::endl;
            for (size_t i = 0; i < courses.size(); ++i)
            {
                std::cout << i + 1 << ". " << courses[i].get_name() << std::endl;
            }
            std::cout << courses.size() + 1 << ".  Show all courses' details" << std::endl;

            int course_choice;
            std::cin >> course_choice;
            std::cin.ignore();

            if (course_choice >= 1 && course_choice <= courses.size())
            {
                std::cout << courses[course_choice - 1].get_name() << std::endl;
                continue;
            }
            else if (course_choice == (courses.size() + 1))
            {
                for (size_t i = 0; i < courses.size(); ++i)
                {
                    std::cout << i + 1 << ". " << courses[i].get_name() << std::endl;
                }
            }
        }
        else if (choice == 3)
        {
            std::cout << "Showing available Courses" << std::endl;
            for (auto course : courses)
            {
                if (!course.isFull())
                {
                    std::cout << course.get_name() << std::endl;
                }
            }
        }
        else if (choice == 4)
        {
            std::cout << "Exiting" << std::endl;
            break;
        }
        else
        {
            std::cout << "Invalid option. Try Again." << std::endl;
        }
    }
}
