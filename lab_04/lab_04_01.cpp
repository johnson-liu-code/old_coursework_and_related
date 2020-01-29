#include<iostream>
#include<string>


using namespace std;


class College
{
public:
    College()
    {
        this->college_ID = 0;
        this->college_name = "";
    }
    College(int college_ID, string college_name)
    {
        this->college_ID = college_ID;
        this->college_name = college_name;
    }

    void set_ID(int college_ID)
    {
        this->college_ID = college_ID;
    }
    int get_ID()
    {
        return this->college_ID;
    }
    void set_name(string college_name)
    {
        this->college_name = college_name;
    }
    string get_name()
    {
        return this->college_name;
    }

    void print_me()
    {
        cout << endl << "---------------------------------------------" << endl;
        cout << "College ID: " << college_ID << endl;
        cout << "College Name: " << college_name << endl;
    }

    College *next;



private:
    int college_ID;
    string college_name;
};


int main()
{
    int array_length = 2;
    College *college_array[array_length];

    for(int i = 0; i < array_length; i++)
    {
        college_array[i] = nullptr;
    }

    college_array[0] = new College(1, "Taylor");
    college_array[1] = new College(2, "Swift");

    // for(int i = 0; i < array_length; i++)
    // {
    //     college_array[i]->print_me();
    // }

    for(int i = 0; i < array_length; i++)
    {
        delete college_array[i];
    }

    College *first = new College(1, "Taylor");
    first->next = NULL;
    College *second = new College(2, "Nayeon");
    second->next = first;
    College *third = new College(3, "Dahyun");
    third->next = second;
    College *fourth = new College(4, "Sana");
    fourth->next = third;
    College *fifth = new College(5, "Chaeyoung");
    fifth->next = fourth;

    first->print_me();
    second->print_me();
    third->print_me();
    fourth->print_me();
    fifth->print_me();

    

    return 0;
}
