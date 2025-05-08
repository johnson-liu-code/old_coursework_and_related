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
    }
    Student(string name, int age, float grade)
    {
        this->name = name;
        this->age = age;
        this->grade = grade;
    }

    void setValues(string name, int age, float grade)
    {
        this->name = name;
        this->age = age;
        this->grade = grade;
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

private:
    string name;
    int age;
    float grade;
};

class Maxheap
{
public:
    Maxheap()
    {
    }
    Maxheap(int cap);
    void swap(int i, int j);
    void addStudent(Student node);
    void Maxheapify(int i);

    int parent(int i)
    {
        return i / 2;
    }
    int left(int i)
    {
        return 2*i;
    }
    int right(int i)
    {
        return 2*i+1;
    }

    void printLeaves()
    {
        // cout << "heap_size: " << heap_size << endl;
        for (int i = 1; i < capacity; i++)
        {
            // cout << i << " " << left(i) << " " << right(i) << endl;
            // cout << "left grade: " << harr[left(i)-1].get_grade() << " right grade: " << harr[right(i)-1].get_grade() << endl;
            // cout << "#############################################" << endl;
            if ( (i <= heap_size) && (harr[left(i)-1].get_grade() == 0) && (harr[right(i)-1].get_grade() == 0) )
            {
                cout << "This is a leaf:" << endl;
                harr[i-1].printValues();
                cout << "############################################" << endl;
            }
        }
    }

private:
    int heap_size;
    int capacity;
    Student* harr;
};
Maxheap::Maxheap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new Student[cap];

    for(int i = 0; i < capacity; i++)
    {
        harr[i] = Student();
    }
}
void Maxheap::swap(int i, int j)
{
    Student temp = harr[i];
    harr[i] = harr[j];
    harr[j] = temp;
}
void Maxheap::addStudent(Student node)
{
    heap_size++;
    int i = heap_size;
    harr[i-1] = node;

    while(i != 1 && ( harr[parent(i)-1].get_grade() < harr[i-1].get_grade() ) )
    {
        swap(i-1, parent(i)-1);
        i = parent(i);
    }
}




int main()
{

    Maxheap* all_students = new Maxheap(100);

    Student student01("Student01", 25, 3.85);
    all_students->addStudent(student01);
    Student student02("Student02", 22, 2.00);
    all_students->addStudent(student02);
    Student student03("Student03", 24, 1.50);
    all_students->addStudent(student03);
    Student student04("Student04", 21, 2.75);
    all_students->addStudent(student04);
    Student student05("Student05", 20, 2.00);
    all_students->addStudent(student05);
    Student student06("Student06", 18, 3.98);
    all_students->addStudent(student06);
    Student student07("Student07", 19, 3.00);
    all_students->addStudent(student07);
    Student student08("Student08", 18, 1.60);
    all_students->addStudent(student08);
    Student student09("Student09", 22, 2.80);
    all_students->addStudent(student09);
    Student student10("Student10", 22, 3.10);
    all_students->addStudent(student10);


    all_students->printLeaves();



    delete all_students;


    return 0;
}
