#include<iostream>
#include<string>
using namespace std;



class to_do
{
public:
    to_do()
    {
        this->length = 0;
    }
    ~to_do();

    void top();
    void pop();
    void push(string task);

    void print_me()
    {
        for (int i = 0; i < length; i++)
        {
            cout << info[i] << endl;
        }
    }

private:
    int length;
    string info[100];
};

to_do::~to_do()
{
    length = 0;
}
void to_do::top()
{
    cout << "top: " << info[length-1] << endl;
}
void to_do::pop()
{
    length--;
}
void to_do::push(string task)
{
    info[length] = task;
    length++;
}

int main()
{

    to_do my_stack;

    my_stack.push("Do homework");
    my_stack.push("Do research");
    my_stack.push("Study");

    // my_stack.print_me();
    my_stack.top();
    my_stack.top();

    my_stack.pop();
    my_stack.pop();

    // my_stack.print_me();

    my_stack.push("Eat");
    my_stack.push("Sleep");
    my_stack.push("Buy groceries");
    my_stack.push("TA");

    my_stack.pop();

    my_stack.top();

    my_stack.push("Tutor");
    my_stack.push("Meeting");

    my_stack.top();

    // my_stack.print_me();

    my_stack.~to_do();

    return 0;
}
