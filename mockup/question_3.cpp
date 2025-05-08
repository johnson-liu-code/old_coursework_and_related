#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
    Student()
    {
        this->name = "";
        this->age = 0;
        this->grade = 0;
        this->deleted = false;
    }
    Student(string name, int age, float grade)
    {
        this->name = name;
        this->age = age;
        this->grade = grade;
        this->deleted = false;
    }

    void setValues(string name, int age, float grade, bool deleted)
    {
        this->name = name;
        this->age = age;
        this->grade = grade;
        this->deleted = deleted;
    }

    void printValues()
    {
        cout << "Name: " << this->name << endl;
        cout << "Age: " << this->age << endl;
        cout << "Grade: " << this->grade << endl;
    }

    void set_name(string name)
    {
        this->name = name;
    }
    string get_name()
    {
        return this->name;
    }

    void set_age(int age)
    {
        this->age = age;
    }
    int get_age()
    {
        return this->age;
    }

    void set_grade(float grade)
    {
        this->grade = grade;
    }
    float get_grade()
    {
        return this->grade;
    }

    void set_deleted(bool deleted)
    {
        this->deleted = deleted;
    }
    bool get_deleted()
    {
        return this->deleted;
    }

private:
    string name;
    int age;
    float grade;
    bool deleted;
};


class HashTable
{
public:
    int table_size;
    int num_students;
    Student* table;

    // Constructor
    HashTable(int table_size)
    {
        this->table_size = table_size;
        // Create table
        table = new Student[table_size];

        for(int i = 0; i < table_size; i++)
        {
            table[i] = Student();
        }
    }

    // Hash function
    int HashFunction(int ID)
    {
        int key = ID % table_size;
        return key;
    }

    // Add a student to the table
    void allocateStudent(string name, int age, float grade)
    {
        // Get the student's key
        int key = HashFunction(grade);

        // Find an available spot in the table
        while( (table[key].get_name() != "") && (table[key].get_deleted() != true) )
        {
            key++;
        }
        table[key].set_name(name);
        table[key].set_age(age);
        table[key].set_grade(grade);
    }

    // Print the students in the table
    void printTable()
    {
        cout << "Printing the students in the table: " << endl;
        for(int i = 0; i < table_size; i++)
        {
            cout << i << ": ";
            // Print the students' information
            if(table[i].get_name() != "")
            {
                cout << "Name: " << table[i].get_name() << ", Age: " << table[i].get_age() << ", Grade: " << table[i].get_grade();
            }
            cout << endl;
        }
    }

    // Remove a student from the table
    void removeStudent(int grade)
    {
        // Get the student's key
        int key = HashFunction(grade);

        // Find the student and reset that location in the table
        for(int i = key; i < table_size; i++)
        {
            if(table[i].get_grade() == grade)
            {
                table[i].set_name("");
                table[i].set_age(0);
                table[i].set_grade(0);
                table[i].set_deleted(true);
                break;
            }
        }
    }
};

int main()
{

    int table_size = 11;

    HashTable* my_table = new HashTable(table_size);

    my_table->allocateStudent("Student01", 20, 2.5);
    my_table->allocateStudent("Student02", 22, 3.5);
    my_table->allocateStudent("Student03", 18, 3);
    my_table->allocateStudent("Student04", 25, 3.85);
    my_table->allocateStudent("Student05", 19, 2.75);

    my_table->printTable();


    return 0;
}
