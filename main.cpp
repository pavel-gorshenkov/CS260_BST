#include "student.h"
#include "table.h"
#include <cstring>

using namespace std;

void addStudent(Table &aTable)
{

    char gNumber[MAX_CHAR], programName[MAX_CHAR], studentName[MAX_CHAR];
    int standing;

    cout << "Enter G-number: ";
    cin.getline(gNumber, 50);

    cout << "Enter program: ";
    cin.getline(programName, 100);

    cout << "Enter student name: ";
    cin.getline(studentName, 200);

    cout << "Enter academic standing: ";
    cin >> standing;

    Student aStudent(programName, gNumber, studentName, standing);
    aTable.add(aStudent);
}

void removeProgram(Table &aTable)
{

    char programName[MAX_CHAR];
    Student aStudent;

    cout << "Which program would you like to remove? ";
    cin.getline(programName, 100);

    aTable.remove(programName, aStudent);
}

void removeByG(Table &aTable)
{

    char gNumber[MAX_CHAR];
    Student aStudent;

    cout << "Which G-number would you like to remove? ";
    cin.getline(gNumber, 100);

    aTable.removeByG(gNumber, aStudent);
}

void retrieveByStudentG(Table &aTable)
{

    char gNumber[MAX_CHAR];
    retrieval r;

    cout << "Which G-number would you like to retrieve? ";
    cin.getline(gNumber, 100);

    aTable.retrieveByG(gNumber, r);

    cout << gNumber << ": "
         << r.programName
         << ", " << r.studentName
         << ", " << r.standing
         << endl;
}

void getHeight(Table &aTable)
{

    cout << "Current size: " << aTable.getSizeOf() << endl;
    cout << "Current height: " << aTable.getHeight() << endl;

    if (aTable.getHeight() > 2 * log2(aTable.getSizeOf()))
    {
        cout << "Tree is unbalanced... " << endl;
    }
    else
    {
        cout << "Tree is balanced!" << endl;
    }
}

int main()
{

    Table aTable;

    int choice;

    aTable.loadFromFile("theTable.txt");
    cout << aTable;

    do
    {
        cout << endl
             << "1. Add Student based on G-Number\n"
             << "2. Retrieve Students by G-Number\n"
             << "3. Remove Student by G-number\n"
             << "4. Remove Students by Program\n"
             << "5. Display All Students\n"
             << "6. Monitor Tree Status" << endl
             << "0. Exit\n"
             << "Choose an option: ";

        cin >> choice;
        cin.ignore(100, '\n');

        switch (choice)
        {

        case 1:
            addStudent(aTable);
            break;
        case 2:
            retrieveByStudentG(aTable);
            break;

        case 3:
            removeByG(aTable);
            break;

        case 5:
            cout << aTable;
            break;

        case 6:
            getHeight(aTable);
            break;
        case 4:
            removeProgram(aTable);
            break;
        }

    } while (choice != 0);

    return 0;
}