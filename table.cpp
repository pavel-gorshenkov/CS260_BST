#include "table.h"

Table::Table() : root(nullptr), size(0)
{
}
Table::Table(const Table &aTable) : root(nullptr), size(0)
{
    *this = aTable;
}

Table::~Table()
{
    destroy(root);
}

void Table::destroy(Node *&currRoot)
{
    if (currRoot)
    {
        destroy(currRoot->left);
        destroy(currRoot->right);
        delete currRoot;
        currRoot = nullptr;
    }
}
void Table::add(const Student &aStudent)
{
    add(this->root, aStudent);
}
void Table::add(Node *&currRoot, const Student &aStudent)
{

    if (!currRoot)
    {
        currRoot = new Node(aStudent); // case of leaf node
        size++;
        return;
    }

    int currNum = numericGValue(currRoot->data.getGNumber());
    int newNum = numericGValue(aStudent.getGNumber());


    if (newNum < currNum)
    {
        add(currRoot->left, aStudent);
    }
    else
    {
        add(currRoot->right, aStudent);
    }
}

const Table &Table::operator=(const Table &tableSrc)
{

    if (this == &tableSrc)
        return *this;
    if (this->root)
    {
        destroy(this->root);
    }
    size = tableSrc.size;
    copy(tableSrc.root, this->root);
    return *this;
}

void Table::copy(Node *srcRoot, Node *&destRoot)
{

    if (srcRoot)
    {
        destRoot = new Node(srcRoot->data);
        copy(srcRoot->left, destRoot->left);
        copy(srcRoot->right, destRoot->right);
    }
    else
    {

        destRoot = nullptr;
    }
}
ostream &operator<<(ostream &out, const Table &srcTable)
{

    out << endl
        << "Displaying the tree ..." << endl;
    srcTable.display(out, srcTable.root);
    return out;
}
void Table::display(ostream &out, Node *currRoot) const
{
    out << endl
        << "Pre-order showing the tree..." << endl;
    displayPreOrder(out, currRoot);
    out << endl
        << "In-order showing the tree..." << endl;
    displayInOrder(out, currRoot);
    out << endl
        << "Post-order showing the tree..." << endl;
    displayPostOrder(out, currRoot);
}

void Table::displayPreOrder(ostream &out, Node *currRoot) const
{
    if (currRoot)
    {

        out << currRoot->data.getGNumber() << " "
            << currRoot->data.getProgramName() << " "
            << currRoot->data.getStudentName() << " "
            << currRoot->data.getStanding() << endl;
        displayPreOrder(out, currRoot->left);
        displayPreOrder(out, currRoot->right);
    }
}
void Table::displayInOrder(ostream &out, Node *currRoot) const
{
    if (currRoot)
    {
        displayInOrder(out, currRoot->left);
        out << currRoot->data.getGNumber() << " "
            << currRoot->data.getProgramName() << " "
            << currRoot->data.getStudentName() << " "
            << currRoot->data.getStanding() << " "
            << endl;
        displayInOrder(out, currRoot->right);
    }
}
void Table::displayPostOrder(ostream &out, Node *currRoot) const
{
    if (currRoot)
    {
        displayPostOrder(out, currRoot->left);
        displayPostOrder(out, currRoot->right);
        out << currRoot->data.getGNumber() << " "
            << currRoot->data.getProgramName() << " "
            << currRoot->data.getStudentName() << " "
            << currRoot->data.getStanding() << " "
            << endl;
    }
}

void Table::loadFromFile(const char *fileName)
{

    ifstream in;
    Student currStudent;
    const int MAX_CHAR = 101;
    char currProgramName[MAX_CHAR],
        currGNum[MAX_CHAR],
        currStudenName[MAX_CHAR];
    int currAcademicStanding;

    in.open(fileName);
    if (!in)
    {

        cerr << "Fail to open" << fileName << " for reading! " << endl;
        exit(1);
    }

    while (in.get(currProgramName, MAX_CHAR, ','))
    {
        in.ignore(100, ',');

        in.get(currGNum, MAX_CHAR, ',');
        in.ignore(100, ',');
        in.get(currStudenName, MAX_CHAR, ',');
        in.ignore(100, ',');
        in >> currAcademicStanding;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        currStudent.setProgramName(currProgramName);

        currStudent.setGNumber(currGNum);
        currStudent.setStudentName(currStudenName);
        currStudent.setAcademicStanding(currAcademicStanding);
        add(currStudent);

        currProgramName[0] = '\0';
        currGNum[0] = '\0';
        currStudenName[0] = '\0';
    }

    in.close();
}

void Table::saveToFile(const char *fileName) const
{

    ofstream out;

    out.open(fileName);
    if (!out)
    {

        cerr << "Fail to open" << fileName << " for writing!" << endl;
        exit(1);
    }

    saveToFile(out, this->root);
    out.close();
}

void Table::saveToFile(ostream &out, Node *currRoot) const
{
    if (currRoot)
    {
        out << currRoot->data.getGNumber() << ';'
            << currRoot->data.getProgramName() << ';'
            << currRoot->data.getStudentName() << ';'
            << currRoot->data.getStanding() << ';'
            << endl;
        saveToFile(out, currRoot->left);
        saveToFile(out, currRoot->right);
    }
}
void Table::remove(const char *programName, Student &aStudent)
{

    remove(this->root, programName, aStudent);
}

void Table::remove(Node *&currRoot, const char *programName, Student &aStudent)
{

    if (!currRoot)
    {
        return;
    }
    remove(currRoot->left, programName, aStudent);
    remove(currRoot->right, programName, aStudent);

    if (strcmp(programName, currRoot->data.getProgramName()) == 0)
    {

        aStudent = currRoot->data;
        deleteNode(currRoot);
        size--;
    }
}

void Table::removeByG(const char *gNumber, Student &aStudent)
{
    removeByG(this->root, gNumber, aStudent);
}

void Table::removeByG(Node *&currRoot, const char *gNumber, Student &aStudent)
{

    if (!currRoot)
    {
        return;
    }

    int targetNum = numericGValue(gNumber);
    int currNum = numericGValue(currRoot->data.getGNumber());

    if (targetNum < currNum)
    {

        removeByG(currRoot->left, gNumber, aStudent);
    }

    else if (targetNum > currNum)
    {

        removeByG(currRoot->right, gNumber, aStudent);
    }

    else
    {
        aStudent = currRoot->data;
        deleteNode(currRoot);
        size--;
    }
}

void Table::deleteNode(Node *&target)
{
    // target to delete Node is a leaf

    if (!target->left && !target->right)
    {

        delete target;
        target = nullptr;
    }
    else if (!target->right)
    {
        Node *temp = target; // target only has left child
        target = target->left;
        delete temp;
    }
    else if (!target->left)
    {
        Node *temp = target;
        target = target->right; // target only has right child
        delete temp;
    }
    else
    {
        // target has two children
        // method using inorder successor
        Node *prev = target;
        Node *curr = target->right;

        while (curr->left)
        {
            prev = curr;
            curr = curr->left; // go all the way to the left
        }
        target->data = curr->data;

        if (prev->left == curr)
        {
            prev->left = curr->right;
        }
        else
        {
            prev->right = curr->right;
        }

        delete curr;
    }
}

// g_number numeric comparrison helper function

int Table::numericGValue(const char *gNumber)
{
    return atoi(gNumber + 1);
}

void Table::retrieveByG(const char *gNumber, retrieval &r)
{
    retrieveByG(this->root, gNumber, r);
}

void Table::retrieveByG(Node *&currRoot, const char *gNumber, retrieval &r)
{

    if (!currRoot)
    {
        return;
    }

    int targetNum = numericGValue(gNumber);
    int currNum = numericGValue(currRoot->data.getGNumber());

    if (targetNum < currNum)
    {

        retrieveByG(currRoot->left, gNumber, r);
    }

    else if (targetNum > currNum)
    {

        retrieveByG(currRoot->right, gNumber, r);
    }

    else
    {
        strcpy(r.programName, currRoot->data.getProgramName());
        strcpy(r.studentName, currRoot->data.getStudentName());
        r.standing = currRoot->data.getStanding();
    }
}

int Table::getHeight()
{

    return getHeight(root);
}

int Table::getHeight(Node *&currRoot)
{

    if (!currRoot)
    {
        return 0;
    }

    int leftHeight = getHeight(currRoot->left);
    int rightHeight = getHeight(currRoot->right);

    return 1 + max(leftHeight, rightHeight); // recursive height calculation
}

int Table::getSizeOf() const
{
    return getSize();
}
