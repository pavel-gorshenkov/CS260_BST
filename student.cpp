#include "student.h"

Student::Student() : programName(nullptr),
                     gNumber(nullptr),
                     studentName(nullptr),
                     academicStanding(0), 
                     size(0)
{
}
Student::Student(const char *programName,
                 const char *gNumber,
                 const char *studentName,
                 int academicStanding,
                 int size)
{

    init(programName, gNumber, studentName, academicStanding, size);
}
void Student::init(const char *programName,
                   const char *gNumber,
                   const char *studentName,
                   int academicStanding,
                   int size)
{
    this->programName = new char[strlen(programName) + 1];
    strcpy(this->programName, programName);
    this->gNumber = new char[strlen(gNumber) + 1];
    strcpy(this->gNumber, gNumber);
    this->studentName = new char[strlen(studentName) + 1];
    strcpy(this->studentName, studentName);
    this->academicStanding = academicStanding;
    this->size = size;
}

Student::Student(const Student &aStudent) : programName(nullptr),
                                            gNumber(nullptr),
                                            studentName(nullptr),
                                            academicStanding(0),
                                            size(0)
{
    *this = aStudent;
}
Student::~Student()
{
    if (this->programName)
    {
        delete[] this->programName;
    }
    this->programName = nullptr;

    if (this->gNumber)
    {
        delete[] this->gNumber;
    }
    this->gNumber = nullptr;

    if (this->studentName)
    {
        delete[] this->studentName;
    }
    this->studentName = nullptr;
}

void Student::setProgramName(const char *programName)
{
    if (this->programName)
    {
        delete[] this->programName;
    }
    this->programName = new char[strlen(programName) + 1];
    strcpy(this->programName, programName);
}
void Student::setGNumber(const char *gNumber)
{
    if (this->gNumber)
    {
        delete[] this->gNumber;
    }
    this->gNumber = new char[strlen(gNumber) + 1];
    strcpy(this->gNumber, gNumber);
}
void Student::setStudentName(const char *studentName)
{
    if (this->studentName)
    {
        delete[] this->studentName;
    }
    this->studentName = new char[strlen(studentName) + 1];
    strcpy(this->studentName, studentName);
}
void Student::setAcademicStanding(int academicStanding) { this->academicStanding = academicStanding; }
void Student::setSize(int size) { this->size = size; }
const char *Student::getProgramName() const { return programName; }
const char *Student::getGNumber() const { return gNumber; }
const char *Student::getStudentName() const { return studentName; }
int Student::getStanding() const { return academicStanding; }

const Student &Student::operator=(const Student &aStudent)
{
    if (this == &aStudent)
    {
        return *this;
    }

    setProgramName(aStudent.programName);
    setGNumber(aStudent.gNumber);
    setStudentName(aStudent.studentName);
    setAcademicStanding(aStudent.academicStanding);
    setSize(aStudent.size);
    return *this;
}

ostream &operator<<(ostream &out, const Student &aStudent)
{
    out << aStudent.gNumber << '\t' << aStudent.programName << '\t' << aStudent.studentName << '\t' << aStudent.academicStanding << endl;
    return out;
}

bool operator<(const Student &student1, const Student &student2)
{

    int compareResult = strcmp(student1.getGNumber(), student2.getGNumber());
    return compareResult < 0;
}
