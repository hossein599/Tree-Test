#include <iostream>

using namespace std;

struct Student 
{
    int id;
    int grade;
    Student* left;
    Student* right;

    Student(int id, int grade) : id(id), grade(grade), left(nullptr), right(nullptr) {}
};

Student* insertStudent(Student* root, int id, int grade) 
{
    if (root == nullptr) 
    {
        return new Student(id, grade);
    }

    if (grade < root->grade) 
    {
        root->left = insertStudent(root->left, id, grade);
    } 
    else 
    {
        root->right = insertStudent(root->right, id, grade);
    }

    return root;
}

void printDescending(Student* root) 
{
    if (root == nullptr) 
    {
        return;
    }

    printDescending(root->right);
    cout << "Student ID: " << root->id << ", Grade: " << root->grade << endl;
    printDescending(root->left);
}

Student* deleteStudent(Student* root, int grade) 
{
    if (root == nullptr) 
    {
        return root;
    }

    if (grade < root->grade) 
    {
        root->left = deleteStudent(root->left, grade);
    } 
    else if (grade > root->grade) 
    {
        root->right = deleteStudent(root->right, grade);
    } 
    else 
    {
        if (root->left == nullptr && root->right==nullptr) 
        {
            Student* temp = root->right;
            
            return temp;
        } 
        else if (root->right == nullptr) 
        {
            Student* temp = root->left;
            delete root;
            return temp;
        }

        Student* minNode = root->right;
        while (minNode->left != nullptr) 
        {
            minNode = minNode->left;
        }
        root->id = minNode->id;
        root->grade = minNode->grade;
        root->right = deleteStudent(root->right, minNode->grade);
    }

    return root;
}

int main() 
{
    Student* root = nullptr;
    int numStudents;
    bool exit = false;
    char per;

    while(!exit)
    {
        int id, grade;
        cout << "Enter Student ID: ";
        cin >> id;
        cout << "Enter Grade: ";
        cin >> grade;
        root = insertStudent(root, id, grade);

        cout << "Exit?(Y/N): ";
        cin >> per;
        if(per == 'y' || per == 'Y')
        {
            exit = true;
        }
    }

    cout << "Descending Order of Grades:" << endl;
    printDescending(root);

    int deleteGrade;
    cout << "Enter the grade to delete: ";
    cin >> deleteGrade;
    root = deleteStudent(root, deleteGrade);

    cout << "Descending Order of Grades (After Deletion):" << endl;
    printDescending(root);

    string x;
    cin >> x;

    return 0;
}