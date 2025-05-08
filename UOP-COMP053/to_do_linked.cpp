#include<iostream>
#include<string>
using namespace std;



class node
{
public:
    node()
    {
        task = "";
        next = nullptr;
    }

    void print_me()
    {
        cout << this->task << endl;
    }

    void set_task(string task)
    {
        this->task = task;
    }
    string get_task()
    {
        return this->task;
    }
    node* get_next()
    {
        return this->next;
    }
    void set_next(node* next)
    {
        this->next = next;
    }

private:
    string task;
    node* next;
};

class to_do
{
public:
    to_do()
    {
        this->length = 0;
        this->first = nullptr;
    }
    ~to_do();

    void print_me();
    void top();
    void pop();
    void push(string task);

private:
    int length;
    string info;
    node* first;
};
to_do::~to_do()
{
    node* tempPrt;
    while (first != NULL)
    {
        tempPrt = first;
        first = first->get_next();
        delete tempPrt;
    }
}
void to_do::print_me()
{
    // for(node* element = this->first; element != nullptr; element = element->get_next())
    // {
    //     element->print_me();
    // }
    node* current;
    current = first;
    while(current != nullptr)
    {
        current->print_me();
        current = current->get_next();
    }
}
void to_do::top()
{
    cout << "top: " << first->get_task() << endl;
}
void to_do::pop()
{
    node* tempPrt;
    tempPrt = first;
    first = first->get_next();
    delete tempPrt;
}
void to_do::push(string task)
{
    node* newNode = new node();
    newNode->set_task(task);

    if (first ==  nullptr)
    {
        first = newNode;
    }
    else
    {
        newNode->set_next(first);
        first = newNode;
    }
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
    //
    // my_stack.print_me();
    //
    my_stack.push("Eat");
    my_stack.push("Sleep");
    my_stack.push("Buy groceries");
    my_stack.push("TA");

    // my_stack.print_me();

    my_stack.pop();
    //
    my_stack.top();
    //
    my_stack.push("Tutor");
    my_stack.push("Meeting");

    my_stack.top();

    // my_stack.print_me();

    my_stack.~to_do();

    return 0;
}
