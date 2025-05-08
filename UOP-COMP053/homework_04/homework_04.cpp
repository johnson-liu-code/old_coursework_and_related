
// 20190924
// Code to read a grades.txt file and prints information to screen and to an grades_output.txt file.

// Include libraries.
#include<iostream>
#include<fstream>
#include<string>
#include<typeinfo>
using namespace std;

// Make a class called StudentNode.
class StudentNode
{
public:
    // Constructor to initialize variables.
    StudentNode()
    {
        this->student_ID = 0;
        this->student_name = "";
        this->hw1_score = 0;
        this->hw2_score = 0;
        this->next = nullptr;
    }

    // Print function to print out variables.
    void printMe()
    {
        cout << "ID: " << this->student_ID << endl;
        cout << "Name: " << this->student_name << endl;
        cout << "HW1 score: " << this->hw1_score << endl;
        cout << "HW2 score: " << this->hw2_score << endl;
        cout << "Mean score: " << mean_score << endl << endl;
    }

    // get and set functions.
    int getID()
    {
        return this->student_ID;
    }
    void setID(int student_ID)
    {
        this->student_ID = student_ID;
    }
    string getName()
    {
        return this->student_name;
    }
    void setName(string student_name)
    {
        this->student_name = student_name;
    }
    int getHW1()
    {
        return this->hw1_score;
    }
    void setHW1(int hw1_score)
    {
        this->hw1_score = hw1_score;
    }
    int getHW2()
    {
        return this->hw2_score;
    }
    void setHW2(int hw2_score)
    {
        this->hw2_score = hw2_score;
    }
    StudentNode* getNext()
    {
        return this->next;
    }
    void setNext(StudentNode* next)
    {
        this->next = next;
    }

// Variables of StudentNode.
private:
    int student_ID;
    string student_name;
    int hw1_score;
    int hw2_score;
    float mean_score = (hw1_score + hw2_score)/2;
    StudentNode* next;
};

// Make a class called StudentList, which is a list of StudentNodes.
class StudentList
{
public:
    // Constructor.
    StudentList()
    {
        this->length = 0;
        this->first = nullptr;      // Start an empty list.
    }

    // Destructor.
    ~StudentList();

    // Function to print every node in the list.
    void printList()
    {
        for(StudentNode* element = this->first; element != nullptr; element = element->getNext())
        {
            element->printMe();
        }
    }

    // Functions.
    void addStudent(int student_ID, string student_name);
    void addHW1(int student_ID, int hw1_score);
    void addHW2(int student_ID, int hw2_score);
    StudentNode getStudent(int student_ID);
    void deleteStudent(int student_ID);
    int getLength();

private:
    int length;
    StudentNode* first;
};

// Destructor. Move the first pointer to the second node then delete the first node.
StudentList::~StudentList()
{
    StudentNode* tempPtr;

    while (first != NULL)
    {
        tempPtr = first;
        first = first->getNext();
        delete tempPtr;
    }
}

// Function to add a student to the list.
void StudentList::addStudent(int student_ID, string student_name)
{
    StudentNode* newNode = new StudentNode();
    newNode->setID(student_ID);
    newNode->setName(student_name);

    if(this->first == nullptr)
    {
        this->first = newNode;
    }
    else
    {
        newNode->setNext(this->first);
        this->first = newNode;
    }

    this->length++;
}

// Function to add a grade for HW1 for a student.
void StudentList::addHW1(int student_ID, int hw1_score)
{
    StudentNode* current_location = first;
    bool found = false;

    while(found == false)
    {
        if(current_location->getID() == student_ID)
        {
            current_location->setHW1(hw1_score);
            found = true;
        }
        else
        {
            current_location = current_location->getNext();
        }
    }
}

// Function to add a grade for HW2 for a student.
void StudentList::addHW2(int student_ID, int hw2_score)
{
    StudentNode* current_location = first;
    bool found = false;

    while(found == false)
    {
        if(current_location->getID() == student_ID)
        {
            current_location->setHW2(hw2_score);
            found = true;
        }
        else
        {
            current_location = current_location->getNext();
        }
    }
}

// Function to find a student.
StudentNode StudentList::getStudent(int student_ID)
{
    StudentNode* tempPrt;
    StudentNode item;
    while (first != NULL)
    {
        if(first->getID() == student_ID)
        {
            item = *first;
        }
        tempPrt = first;
        first = first->getNext();
    }

    return item;
}

// Function to delete a student.
void StudentList::deleteStudent(int student_ID)
{
    StudentNode* current_location = first;
    StudentNode* temp_location;

    if(first->getID() == student_ID)
    {
        temp_location = current_location;
        first = first->getNext();
    }
    else
    {
        while(current_location->getNext()->getID() != student_ID)
        {
            current_location = current_location->getNext();
        }
        temp_location = current_location->getNext();
        current_location->setNext(current_location->getNext()->getNext());
    }
    delete temp_location;
    length--;
}

// Function to get the length of the list.
int StudentList::getLength()
{
    return this->length;
}


int main()
{
    // Create a list.
    StudentList my_list;

    // Open input file.
    ifstream inFile;
    string inFileName = "grades.txt";
    inFile.open(inFileName);

    if (!inFile)
    {
        cout << "File not found: " << inFileName << endl;
    }

    // Open output file.
    ofstream outFile;
    string outFileName = "grades_output.txt";   // name of output file
    outFile.open(outFileName);                  // open output file

    // Iterate over the commands of the input file.
    bool quit = false;
    string command;
    inFile >> command;

    int student_ID;

    while(quit == false)
    {
        // Add a student to the list.
        if(command == "ADD_STUDENT")
        {
            string student_name;
            inFile >> student_ID;
            inFile >> student_name;

            cout << "#####################################################################" << endl;
            cout << "Adding student " << student_ID << " " << student_name << endl;
            outFile << "Adding student " << student_ID << " " << student_name << endl;

            my_list.addStudent(student_ID, student_name);
        }

        // Add a grade for a student in the list.
        else if(command == "ADD_GRADE")
        {
            int grade;
            string homework;
            inFile >> student_ID;
            inFile >> homework;
            inFile >> grade;

            if(homework == "HW1")
            {
                cout << "#####################################################################" << endl;
                cout << "Adding HW1 grade for student " << student_ID << ": " << grade << endl;
                outFile << "Adding HW1 grade for student " << student_ID << ": " << grade << endl;
                my_list.addHW1(student_ID, grade);
            }
            else if(homework == "HW2")
            {
                cout << "#####################################################################" << endl;
                cout << "Adding HW2 grade for student " << student_ID << ": " << grade << endl;
                outFile << "Adding HW2 grade for student " << student_ID << ": " << grade << endl;
                my_list.addHW2(student_ID, grade);
            }
        }

        // Change a grade for a student in the list.
        else if(command == "CHANGE_GRADE")
        {
            string homework;
            int grade;

            inFile >> student_ID;
            inFile >> homework;
            inFile >> grade;

            int current = my_list.first->getID();
            StudentNode* next = my_list.first;

            while(current != student_ID)
            {
                next = next->getNext();
                current = next->getID();
            }
            if(homework == "HW1")
            {
                cout << "#####################################################################" << endl;
                cout << "Changing HW1 grade for student " << student_ID << ": " << grade << endl << endl;
                outFile << "Changing HW1 grade for student " << student_ID << ": " << grade << endl;
                next->setHW1(grade);
            }
            else if(homework == "HW2")
            {
                cout << "#####################################################################" << endl;
                cout << "Changing HW2 grade for student " << student_ID << ": " << grade << endl << endl;
                outFile << "Changing HW2 grade for student " << student_ID << ": " << grade << endl;
                next->setHW2(grade);
            }
        }

        // Print the information on a student in the list.
        else if(command == "PRINT_STUDENT")
        {
            inFile >> student_ID;
            int sum_score;
            float mean_score;

            cout << "#####################################################################" << endl;
            cout << "Printing info on student " << student_ID << endl;
            outFile << "Printing info on student " << student_ID << endl;

            int current = my_list.first->getID();
            StudentNode* next = my_list.first->getNext();
            while(current != student_ID)
            {
                current = next->getID();
                if(current == student_ID)
                {
                    sum_score = next->getHW1() + next->getHW2();
                    mean_score = sum_score / 2;
                    next->printMe();
                    cout << "Mean score: " << mean_score << endl;
                    outFile << "Student name: " << next->getName() << endl;
                    outFile << "HW1 grade: " << next->getHW1() << endl;
                    outFile << "HW2 grade: " << next->getHW2() << endl;
                    outFile << "Mean score: " << mean_score << endl;
                }
                next = next->getNext();
            }
        }

        // Print the grades for a specific assignment.
        else if(command == "PRINT_ASSIGNMENT")
        {
            float total_score = 0;
            int length = my_list.getLength();
            float hw1_mean, hw2_mean;

            string homework;
            inFile >> homework;

            if(homework == "HW1")
            {
                cout << "#####################################################################" << endl;
                cout << "Printing HW1 ..." << endl << endl;
                outFile << "Printing HW1 ..." << endl;
                total_score += my_list.first->getHW1();
                cout << "Student " << my_list.first->getID() << " has a HW1 grade of " << my_list.first->getHW1() << endl;
                outFile << "Student " << my_list.first->getID() << " has a HW1 grade of " << my_list.first->getHW1() << endl;
                StudentNode* next = my_list.first->getNext();
                while(next != nullptr)
                {
                    total_score += next->getHW1();
                    cout << "Student " << next->getID() << " has a HW1 grade of " << next->getHW1() << endl;
                    outFile << "Student " << my_list.first->getID() << " has a HW1 grade of " << my_list.first->getHW1() << endl;
                    next = next->getNext();
                }
                hw1_mean = total_score/length;
                cout << "The average grade for HW1 is " << hw1_mean << endl << endl;
                outFile << "The average grade for HW1 is " << hw1_mean << endl;
            }
            else if(homework == "HW2")
            {
                cout << "#####################################################################" << endl;
                cout << "Printing HW2 ..." << endl << endl;
                outFile << "Printing HW2 ..." << endl;
                total_score += my_list.first->getHW2();
                cout << "Student " << my_list.first->getID() << " has a HW2 grade of " << my_list.first->getHW2() << endl;
                outFile << "Student " << my_list.first->getID() << " has a HW2 grade of " << my_list.first->getHW2() << endl;
                StudentNode* next = my_list.first->getNext();
                while(next != nullptr)
                {
                    total_score += next->getHW2();
                    cout << "Student " << next->getID() << " has a HW2 grade of " << next->getHW2() << endl;
                    outFile << "Student " << next->getID() << " has a HW2 grade of " << next->getHW2() << endl;
                    next = next->getNext();
                }
                hw2_mean = total_score/length;
                cout << "The average grade for HW2 is " << hw2_mean << endl << endl;
                outFile << "The average grade for HW2 is " << hw2_mean << endl;
            }
        }

        // Print the student with the highest grade on a specific assignment.
        else if(command == "PRINT_TOP_STUDENT")
        {
            int high_score;
            string student, homework;
            inFile >> homework;

            if(homework == "HW1")
            {
                cout << "#####################################################################" << endl;
                cout << "Printing top student for HW1 ..." << endl << endl;
                outFile << "Printing top student for HW1 ..." << endl;
                high_score = my_list.first->getHW1();
                student = my_list.first->getName();
                StudentNode* next = my_list.first->getNext();
                while(next != nullptr)
                {

                    if(next->getHW1() > high_score)
                    {
                        high_score = next->getHW1();
                        student = next->getName();
                    }
                    next = next->getNext();
                }
                cout << "The student with the highest score on HW1 is " << student
                        << " with a score of "<< high_score << endl << endl;
                outFile << "The student with the highest score on HW1 is " << student
                                << " with a score of "<< high_score << endl;
            }
            else if(homework == "HW2")
            {
                cout << "#####################################################################" << endl;
                cout << "Printing top student for HW2 ..." << endl << endl;
                outFile << "Printing top student for HW2 ..." << endl;
                high_score = my_list.first->getHW2();
                student = my_list.first->getName();
                StudentNode* next = my_list.first->getNext();
                while(next != nullptr)
                {
                    if(next->getHW2() > high_score)
                    {
                        high_score = next->getHW2();
                        student = next->getName();
                    }
                    next = next->getNext();
                }
                cout << "The student with the highest score on HW2 is " << student
                        << " with a score of "<< high_score << endl << endl;
                outFile << "The student with the highest score on HW2 is " << student
                                << " with a score of "<< high_score << endl;
            }
        }

        // Delete a student from the list.
        else if(command == "DELETE_STUDENT")
        {
            inFile >> student_ID;

            cout << "#####################################################################" << endl;
            cout << "Deleting student " << student_ID << endl;
            outFile << "Deleting student " << student_ID << endl;
            my_list.deleteStudent(student_ID);
        }

        // Print the information on all of the students in the list.
        else if(command == "PRINT")
        {
            cout << "#####################################################################" << endl;
            cout << "Printing the list of students ..." << endl << endl;
            outFile << "Printing the list of students ..." << endl;
            my_list.printList();

            outFile << "Student name: " << my_list.first->getName() << endl;
            outFile << "HW1 grade: " << my_list.first->getHW1() << endl;
            outFile << "HW2 grade: " << my_list.first->getHW2() << endl;
            StudentNode* next = my_list.first->getNext();
            while(next != nullptr)
            {
                outFile << "Student name: " << next->getName() << endl;
                outFile << "HW1 grade: " << next->getHW1() << endl;
                outFile << "HW2 grade: " << next->getHW2() << endl;
                next = next->getNext();
            }
        }

        // Quit.
        else if(command == "QUIT")
        {
            quit = true;

            cout << "#####################################################################" << endl;
            cout << "Quiting ..." << endl;
            outFile << "QUIT" << endl;
        }

        inFile >> command;
    }

    // Destroy the list.
    my_list.~StudentList();

    // Close the input and output files.
    inFile.close();       // close the input file
    outFile.close();      // close the output file

    // Pause before exiting.
    char exit;
    cin >> exit;

    return 0;
}
