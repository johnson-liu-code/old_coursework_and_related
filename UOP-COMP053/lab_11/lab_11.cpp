#include<iostream>
#include<string>


// Student class
class student
{
public:
    int ID;
    std::string name;
    bool deleted;

    // Constructors
    student()
    {
        this->ID = 0;
        this->name = "";
        this->deleted = false;
    }
    student(int ID, std::string name)
    {
        this->ID = ID;
        this->name = name;
        this->deleted = false;
    }

};

// Advisor class
class advisor
{
public:
    int num;
    std::string name;

    // Constructors
    advisor()
    {
        this->num = 10;
        this->name = "";
    }
    advisor(int num, std::string name)
    {
        this->num = num;
        this->name = name;
    }
    // Setters
    void set_num(int num)
    {
        this->num = num;
    }
    void set_name(std::string name)
    {
        this->name = name;
    }
};

// Hash table class
class HashTable
{
public:
    int table_size;
    int num_advisors;
    int num_students_per_advisor;
    student* table;
    advisor* advisor_list;

    // Constructor
    HashTable(int table_size, int num_advisors, int num_students_per_advisor)
    {
        this->table_size = table_size;
        this->num_students_per_advisor = num_students_per_advisor;

        // Create table
        table = new student[table_size];

        for(int i = 0; i < table_size; i++)
        {
            table[i] = student();
        }

        // Set up advisors
        advisor_list = new advisor[num_advisors];
        // advisor_list[0] = advisor(0, "Advisor01");
        advisor_list[0].set_num(0);
        advisor_list[0].set_name("Advisor01");
        advisor_list[1].set_num(1);
        advisor_list[1].set_name("Advisor02");
        advisor_list[2].set_num(2);
        advisor_list[2].set_name("Advisor03");
        advisor_list[3].set_num(3);
        advisor_list[3].set_name("Advisor04");
        advisor_list[4].set_num(4);
        advisor_list[4].set_name("Advisor05");
    }

    // Hash function
    int HashFunction(int ID)
    {
        int key = ID % table_size;
        return key;
    }

    // Add a student to the table
    void allocateStudent(int ID, std::string name)
    {
        // Get the student's key
        int key = HashFunction(ID);

        // Find an available spot in the table
        while( (table[key].name != "") && (table[key].deleted != true) )
        {
            key++;
        }
        table[key].ID = ID;
        table[key].name = name;
    }

    // Print the students in the table
    void printTable()
    {
        std::cout << "Printing the students in the table: " << std::endl;
        for(int i = 0; i < table_size; i++)
        {
            std::cout << i << ": ";
            // Print the students' information
            if(table[i].name != "")
            {
                std::cout << table[i].ID << ", " << table[i].name;
            }
            std::cout << std::endl;
        }
    }

    // Prints all of the students for the specified advisor
    void printStudents(int num)
    {
        // The start location of the table that belongs to the advisor
        int begin = num*num_students_per_advisor;
        // The end location of the table that belongs to the advisor
        int end = (num+1)*num_students_per_advisor - 1;

        std::cout << "Printing the students for " << advisor_list[num].name << ": " << std::endl;

        // Print the student names
        for(int i = begin; i <= end; i++)
        {
            std::cout << table[i].name << std::endl;
        }
    }

    // Remove a student from the table
    void removeStudent(int ID)
    {
        // Get the student's key
        int key = HashFunction(ID);

        // Find the student and reset that location in the table
        for(int i = key; i < table_size; i++)
        {
            if(table[i].ID == ID)
            {
                table[i].ID = 0;
                table[i].name = "";
                table[i].deleted = true;
                break;
            }
        }
    }

    // Print the advisor for a specific student
    void printAdvisor(int ID)
    {
        // Get the student's key
        int key = HashFunction(ID);
        // Look for the student's location
        for(int i = key; i < table_size; i++)
        {
            if(table[i].ID == ID)
            {
                std::cout << table[i].name << ", ID: " << table[i].ID << " has ";
                // Get the advisor
                int advisor_num = table_size/i;
                std::cout << advisor_list[advisor_num].name << " as their advisor" << std::endl << std::endl;
                break;
            }
        }
    }

};



int main()
{
    // Initiallize variables
    int table_size = 15;
    int num_advisors = 5;
    int num_students_per_advisor = 3;

    // Create has table
    HashTable* my_table = new HashTable(table_size, num_advisors, num_students_per_advisor);

    // Allocate students
    my_table->allocateStudent(100, "Student01");
    my_table->allocateStudent(200, "Student02");
    my_table->allocateStudent(58, "Student03");
    my_table->allocateStudent(22, "Student04");
    my_table->allocateStudent(16, "Student05");
    my_table->allocateStudent(250, "Student06");
    my_table->allocateStudent(60, "Student07");
    my_table->allocateStudent(66, "Student08");

    // Print the table
    my_table->printTable();

    // Print the students for each of the advisors
    my_table->printStudents(0);
    my_table->printStudents(1);
    my_table->printStudents(2);
    my_table->printStudents(3);
    my_table->printStudents(4);

    // Remove students
    my_table->removeStudent(60);
    my_table->removeStudent(250);

    // Print the advisor of a specific student
    my_table->printAdvisor(200);

    // Print the table
    my_table->printTable();

    // Delete the table
    delete my_table;

    // Exit program
    char exit;
    std::cin >> exit;

    return 0;
}
