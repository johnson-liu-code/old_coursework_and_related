
// 20190927
// Implementing sorted lists using an array and a linked list.

#include<iostream>

using namespace std;


// Create a class called 'Mansion'.
class Mansion
{
public:
    // Default constructor.
    Mansion()
    {
        this->mansion_ID = 0;
        this->weekly_price = 0;
        this->available = false;
        this->next = nullptr;
    }
    // Overload constructor.
    Mansion(int mansion_ID, int weekly_price, bool available, Mansion* next)
    {
        this->mansion_ID = mansion_ID;
        this->weekly_price = weekly_price;
        this->available = available;
        this->next = next;
    }

    // Print function.
    void printMe()
    {
        cout << "####################################" << endl;
        cout << "Printing info for mansion " << this->mansion_ID << endl;
        cout << "Weekly rent: " << this->weekly_price << endl;
        cout << "Availability: " << this->available << endl;
    }

    // Setters and getters.
    void setID(int mansion_ID)
    {
        this->mansion_ID = mansion_ID;
    }
    int getID()
    {
        return this->mansion_ID;
    }
    void setWeeklyPrice(int weekly_price)
    {
        this->weekly_price = weekly_price;
    }
    int getWeeklyPrice()
    {
        return this->weekly_price;
    }
    void setAvailability(bool available)
    {
        this->available = available;
    }
    bool getAvailability()
    {
        return this->available;
    }
    void setNext(Mansion* next)
    {
        this->next = next;
    }
    Mansion* getNext()
    {
        return this->next;
    }

// Private variables.
private:
    int mansion_ID;
    int weekly_price;
    bool available;
    Mansion* next;
};

// Creating a class called 'SortedListArray' to implement a sorted list using an array.
class SortedListArray
{
public:
    // Various functions.
    SortedListArray();
    void MakeEmpty();
    void AddItem(int mansion_ID, int weekly_price, bool available);
    void DeleteItem(int mansion_ID);
    void GetItem(int mansion_ID);
    void ModifyItem(int mansion_ID, int weekly_price, bool available);
    void PrintList();

// Private variables.
private:
    int length;
    Mansion info[20];
    int current_position;
};
// Constructor.
SortedListArray::SortedListArray()
{
    length = 0;
}
// Destructor.
void SortedListArray::MakeEmpty()
{
    length = 0;
}
// Add an item.
void SortedListArray::AddItem(int mansion_ID, int weekly_price, bool available)
{
    if(length == 0)
    {
        info[0] = Mansion();
        info[0].setID(mansion_ID);
        info[0].setWeeklyPrice(weekly_price);
        info[0].setAvailability(available);
    }
    else
    {
        bool hit_end_of_array = true;
        for(int i = 0; i < length; i++)
        {
            if(mansion_ID < info[i].getID())
            {
                for(int j = length; j > i; j--)
                {
                    info[j] = info[j-1];
                    hit_end_of_array = false;
                }
                info[i].setID(mansion_ID);
                info[i].setWeeklyPrice(weekly_price);
                info[i].setAvailability(available);
                break;
            }
        }
        if(hit_end_of_array)
        {
            info[length] = Mansion();
            info[length].setID(mansion_ID);
            info[length].setWeeklyPrice(weekly_price);
            info[length].setAvailability(available);
        }
    }
    length++;
}
// Delete an item.
void SortedListArray::DeleteItem(int mansion_ID)
{
    int location = 0;
    while(info[location].getID() != mansion_ID)
    {
        location++;
    }
    for(int i = location + 1; i < length; i++)
    {
        info[i-1] = info[i];
    }
    length--;
}
// Return an item.
void SortedListArray::GetItem(int mansion_ID)
{
    int location = 0;
    bool found = false;
    Mansion item;
    do {
        found = info[location].getID() == mansion_ID;
        location++;
    } while(location < length && !found);
    info[location].printMe();
}
// Modify an item.
void SortedListArray::ModifyItem(int mansion_ID, int weekly_price, bool available)
{
    int location = 0;
    bool found = false;
    Mansion item;
    do {
        found = info[location].getID() == mansion_ID;
        location++;
    } while(location < length && !found);
    info[location-1].setWeeklyPrice(weekly_price);
    info[location-1].setAvailability(available);
}
// Print all members of the list.
void SortedListArray::PrintList()
{
    for(int i = 0; i < length; i++)
    {
        info[i].printMe();
    }
}

// Create a class called 'SortedListLinked' to implement a sorted list using a linked list.
class SortedListLinked
{
public:
    // Various functions.
    SortedListLinked();
    ~SortedListLinked();
    void AddItem(int mansion_ID, int weekly_price, bool available);
    void DeleteItem(int mansion_ID);
    void GetItem(int mansion_ID);
    void ModifyItem(int mansion_ID, int weekly_price, bool available);
    void PrintList();
    int GetLength();

// Private variables.
private:
    int length;
    Mansion* first;
};
// Constructor.
SortedListLinked::SortedListLinked()
{
    length = 0;
    first = nullptr;
}
// Destructor.
SortedListLinked::~SortedListLinked()
{
    Mansion* tempPrt;
    while(first != nullptr)
    {
        tempPrt = first;
        first = first->getNext();
        delete tempPrt;
    }
}
// Add an item.
void SortedListLinked::AddItem(int mansion_ID, int weekly_price, bool available)
{
    Mansion* newNode = new Mansion();
    newNode->setID(mansion_ID);
    newNode->setWeeklyPrice(weekly_price);
    newNode->setAvailability(available);

    if( first == nullptr || first->getID() >= newNode->getID() )
    {
        newNode->setNext(first);
        first = newNode;
    }
    else
    {
        Mansion* current = first;
        while( current->getNext() != nullptr && current->getNext()->getID() < newNode->getID() )
        {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }
    // length++;
}
// Delete an item.
void SortedListLinked::DeleteItem(int mansion_ID)
{
    Mansion* current_location = first;
    Mansion* temp_location;

    if(first->getID() == mansion_ID)
    {
        temp_location = current_location;
        first = first->getNext();
    }
    else
    {
        while(current_location->getNext()->getID() != mansion_ID)
        {
            current_location = current_location->getNext();
        }
        temp_location = current_location->getNext();
        current_location->setNext(current_location->getNext()->getNext());
    }
    delete temp_location;
    length--;
}
// Get an item.
void SortedListLinked::GetItem(int mansion_ID)
{
    int current = first->getID();
    Mansion* next = first->getNext();
    if(current == mansion_ID)
    {
        first->printMe();
    }
    while(current != mansion_ID)
    {
        current = next->getID();
        if(current == mansion_ID)
        {
            next->printMe();
        }
        next = next->getNext();
    }
}
// Modify an item.
void SortedListLinked::ModifyItem(int mansion_ID, int weekly_price, bool available)
{
    int current = first->getID();
    Mansion* next = first->getNext();
    if(current == mansion_ID)
    {
        first->setWeeklyPrice(weekly_price);
        first->setAvailability(available);
    }
    while(current != mansion_ID)
    {
        current = next->getID();
        if(current == mansion_ID)
        {
            next->setWeeklyPrice(weekly_price);
            next->setAvailability(available);
        }
        next = next->getNext();
    }
}
// Print all members of the list.
void SortedListLinked::PrintList()
{
    Mansion* current = first;
    while(current != nullptr)
    {
        current->printMe();
        current = current->getNext();
    }
}
// Get length of the list.
int SortedListLinked::GetLength()
{
    return this->length;
}

int main()
{
    // Make a sorted list (array).
    SortedListArray my_list_array;

    cout << "##############################################" << endl;
    cout << "Sorted list implemented using an array" << endl;
    cout << "##############################################" << endl;

    // Add 5 items.
    cout << "Adding 5 items" << endl;
    my_list_array.AddItem(1001, 1000, true);
    my_list_array.AddItem(2001, 2000, true);
    my_list_array.AddItem(1501, 1000, true);
    my_list_array.AddItem(0001, 500, true);
    my_list_array.AddItem(3001, 3000, true);
    cout << endl;

    // Print the list.
    cout << "Printing list:" << endl;
    my_list_array.PrintList();
    cout << endl;

    // Delete 3 items.
    cout << "Deleting 3 items" << endl;
    my_list_array.DeleteItem(2001);
    my_list_array.DeleteItem(0001);
    my_list_array.DeleteItem(1001);
    cout << endl;

    // Get information on an item.
    cout << "Getting information on an item:" << endl;
    my_list_array.GetItem(3001);
    cout << endl;

    // Print the list.
    cout << "Printing list:" << endl;
    my_list_array.PrintList();
    cout << endl;

    // Add 3 items.
    cout << "Adding 3 items" << endl;
    my_list_array.AddItem(3501, 3000, true);
    my_list_array.AddItem(4001, 4000, true);
    my_list_array.AddItem(5001, 5000, true);
    cout << endl;

    // Modify 2 items.
    cout << "Modifying 2 items" << endl;
    my_list_array.ModifyItem(3001, 5000, true);
    my_list_array.ModifyItem(1501, 3000, true);
    cout << endl;

    // Print the list.
    cout << "Printing list:" << endl;
    my_list_array.PrintList();
    cout << endl;

    // Modify 1 item.
    cout << "Modifying 1 item" << endl;
    my_list_array.ModifyItem(5001, 10000, true);
    cout << endl;

    // Add 3 items.
    cout << "Adding 3 items" << endl;
    my_list_array.AddItem(6001, 6000, true);
    my_list_array.AddItem(6501, 6000, true);
    my_list_array.AddItem(7001, 7000, true);
    cout << endl;

    // Print the list.
    cout << "Printing list:" << endl;
    my_list_array.PrintList();
    cout << endl;

    cout << "##############################################" << endl;
    cout << "Sorted list implemented using a linked list" << endl;
    cout << "##############################################" << endl;

    // Make a sorted list (linked list).
    SortedListLinked my_list_linked;

    // Add 5 items.
    cout << "Adding 5 items" << endl;
    my_list_linked.AddItem(5001, 1000, true);
    my_list_linked.AddItem(1001, 1000, true);
    my_list_linked.AddItem(3001, 1000, true);
    my_list_linked.AddItem(2001, 1000, true);
    my_list_linked.AddItem(4001, 1000, true);
    cout << endl;

    // Print the list.
    cout << "Printing list:" << endl;
    my_list_linked.PrintList();
    cout << endl;

    // Delete 3 items.
    cout << "Deleting 3 items" << endl;
    my_list_linked.DeleteItem(5001);
    my_list_linked.DeleteItem(1001);
    my_list_linked.DeleteItem(4001);
    cout << endl;

    // Get information on an item.
    cout << "Getting information on an item:" << endl;
    my_list_linked.GetItem(3001);
    cout << endl;

    // Print a list.
    cout << "Printing list:" << endl;
    my_list_linked.PrintList();
    cout << endl;

    // Add 3 items.
    cout << "Adding 3 items" << endl;
    my_list_linked.AddItem(6001, 6000, true);
    my_list_linked.AddItem(7001, 7000, true);
    my_list_linked.AddItem(6501, 6000, true);
    cout << endl;

    // Modify 2 items.
    cout << "Modifying 2 items" << endl;
    my_list_linked.ModifyItem(6001, 10000, true);
    my_list_linked.ModifyItem(6501, 10000, true);
    cout << endl;

    // Print the list.
    cout << "Printing list:" << endl;
    my_list_linked.PrintList();
    cout << endl;

    // Modify an item.
    cout << "Modifying 1 item" << endl;
    my_list_linked.ModifyItem(7001, 5000, true);
    cout << endl;

    // Add 3 items.
    cout << "Adding 3 items" << endl;
    my_list_linked.AddItem(0001, 1000, true);
    my_list_linked.AddItem(1501, 1000, true);
    my_list_linked.AddItem(7501, 5000, true);
    cout << endl;

    // Print the list.
    cout << "Printing list:" << endl;
    my_list_linked.PrintList();
    cout << endl;

    // Destroy the list.
    my_list_linked.~SortedListLinked();

    // Exit.
    char exit;
    cin >> exit;

    return 0;
}
