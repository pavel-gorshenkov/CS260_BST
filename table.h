#ifndef TABLE_H
#define TABLE_H
#include "student.h"
#include <fstream>
#include "retrieval.h"

class Table
{

public:
    Table();
    Table(const Table &aTable);
    ~Table();

    void add(const Student &aStudent);
    void remove(const char *gNumber, Student &aStudent);
    void removeByG(const char *gNumber, Student &aStudent);
    void retrieveByG(const char *gNumber, retrieval &r);
    int getHeight();
    int getSizeOf() const;

    const Table &operator=(const Table &aTable);
    friend ostream &operator<<(ostream &out, const Table &aTable);

    // need to add retrieve and getSize functions

    void loadFromFile(const char *fileName);
    void saveToFile(const char *fileName) const;

private:
    struct Node
    {
        Node(const Student &aStudent)
        {
            data = aStudent;
            left = right = nullptr;
        };

        Student data;
        Node *left;
        Node *right;
    };

    Node *root;
    int size;

    void add(Node *&currRoot, const Student &aStudent);
    void remove(Node *&currRoot, const char *gNumber, Student &aStudent);
    void removeByG(Node *&currRoot, const char *gNumber, Student &aStudent);
    void deleteNode(Node *&target);
    void destroy(Node *&currRoot);
    void copy(Node *srcRoot, Node *&destRoot);
    void display(ostream &out, Node *currRoot) const;
    void displayPreOrder(ostream &out, Node *currRoot) const;
    void displayInOrder(ostream &out, Node *currRoot) const;
    void displayPostOrder(ostream &out, Node *currRoot) const;
    void saveToFile(ostream &out, Node *currRoot) const;
    int numericGValue(const char *gNumber);
    void retrieveByG(Node *&currRoot, const char *gNumber, retrieval &r);
    int getHeight(Node *&currRoot);
    int getSize() const { return size; }
};

#endif