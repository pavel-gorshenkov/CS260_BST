#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
using namespace std;
#include <cstring>

const int MAX_CHAR = 101;

class Student
{

public:
    Student(); // constructor
               // parameterized constructor
    Student(const char *programName,
            const char *gNumber,
            const char *studentName,
            int academicStanding);
    Student(const Student &aStudent);
    ~Student(); // destructor

    void setProgramName(const char *programName); // setters
    void setGNumber(const char *gNumber);
    void setStudentName(const char *studentName);
    void setAcademicStanding(int academicStanding);

    const char *getProgramName() const; // getters
    const char *getGNumber() const;
    const char *getStudentName() const;
    int getStanding() const;

    const Student &operator=(const Student &aStudent);
    friend ostream &operator<<(ostream &out, const Student &aStudent);

private:
    char *programName;
    char *gNumber;
    char *studentName;
    int academicStanding;

    void init(const char *programName,
              const char *gNumber,
              const char *studentName,
              int academicStanding);
};

bool operator<(const Student &student1, const Student &student2);

#endif