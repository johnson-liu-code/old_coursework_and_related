#include<fstream>
#include<iostream>
#include<string>

using namespace std;


class Node
{
public:
    // Default constructor.
    Node()
    {
        college_ID = 0;
        college_name = "";
        next = nullptr;
    }

    // Print function.
    // void Print();s

    // Function to set college_ID and college_name.
    void setCollege(int college_ID, string college_name)
    {
        this->college_ID = college_ID;
        this->college_name = college_name;
    }
    // Function to set college_ID.
    void set_ID(int college_ID)
    {
        this->college_ID = college_ID;
    }
    // Function to get college_ID.
    int get_ID()
    {
        return this->college_ID;
    }
    // Function to set college_name.
    void set_name(string college_name)
    {
        this->college_name = college_name;
    }
    // Function to get college_name.
    string get_name()
    {
        return this->college_name;
    }
    // Function to set next;
    void set_next(Node *next)
    {
        this->next = next;
    }
    // Function to get next.
    Node* get_next()
    {
        return this->next;
    }

    // Function to print college_ID and college_name.
    void printMe()
    {
        cout << endl << "---------------------------------------------" << endl;
        cout << "College ID: " << college_ID << endl;
        cout << "College Name: " << college_name << endl;
    }

// Private variables.
private:
    int college_ID;
    string college_name;
    Node *next;
};

// Array.
class UnsortedListArray
{
public:
	// Constructor
	UnsortedListArray();

    // Empty out the list.
	void MakeEmpty();

    // Returns whether or not the array is full.
	bool IsFull() const;

    // Returns the number of elements in the list.
	int GetLength() const;

    // Gets the element in the list with matching college_ID.
	Node GetItem(int college_ID);

    // Adds an item to the list.
	void PutItem(int college_ID, string college_name);

    // Deletes an item in the list.
	void DeleteItem(int college_ID);

    // Resets the list.
	void ResetList();

    // Get the next item.
    Node GetNextItem();

    // Print the list.
    void PrintList();

private:
	int length;
    Node info[20];
	int currentPos;
};

// Constructor.
UnsortedListArray::UnsortedListArray()
{
	length = 0;
}
// Returns whether or not the array is full.
bool UnsortedListArray::IsFull() const
{
	return (length == 20);
}
// Returns the number of elements in the list.
int UnsortedListArray::GetLength() const
{
	return length;
}
// Gets the element in the list with matching college_ID.
Node UnsortedListArray::GetItem(int college_ID)
{
	int location = 0;
	bool found = false;
	Node item;

	do {
		item = info[location];
		found = info[location].get_ID() == college_ID;
		location++;
	} while (location < length && !found);

	return item;
}
// Empty out the list.
void UnsortedListArray::MakeEmpty()
{
	length = 0;
}
// Adds an item to the list.
void UnsortedListArray::PutItem(int college_ID, string college_name)
{
	info[length].setCollege(college_ID, college_name);
	length++;
}
// Deletes an item in the list.
void UnsortedListArray::DeleteItem(int key)
{
	int location = 0;

	while (info[location].get_ID() != key)
		location++;

	info[location] = info[length - 1];
	length--;
}
// Resets the list.
void UnsortedListArray::ResetList()
{
	currentPos = -1;
}
// Get the next item.
Node UnsortedListArray::GetNextItem()
{
	currentPos++;
	return info[currentPos];
}
// Print the list.
void UnsortedListArray::PrintList()
// Pre:  list has been initialized.
//       dataFile is open for writing.
// Post: Each component in list has been written to dataFile.
//       dataFile is still open.
{
    int length;
	Node item;
	ResetList();
	length = GetLength();
	if (length == 0)
		cout << "List is empty." << endl;
	else
		for (int counter = 1; counter <= length; counter++)
		{
			item = GetNextItem();
			item.printMe();
		}
}

// Linked list.
class UnsortedListLinked
{
public:
    // Constructor.
	UnsortedListLinked();

    // Destructor.
    ~UnsortedListLinked();

    // Delete each element in the list.
	void MakeEmpty();

    // Gets the number of elements in the list.
	int GetLength();

    // Gets the element with matching college_ID.
	Node GetItem(int college_ID);

    // Add an element to the list.
	void PutItem(int college_ID, string college_name);

    // Remove an element from the list.
	void DeleteItem(int college_ID);

    // Print the list.
    void PrintList();

// Private variables.
private:
	int length;
    Node *first;
};
// Constructor.
UnsortedListLinked::UnsortedListLinked()
{
	length = 0;
	first = NULL;
}
// Destructor.
UnsortedListLinked::~UnsortedListLinked()
{
	Node* tempPtr;

	while (first != NULL)
	{
		tempPtr = first;
		first = first->get_next();
		delete tempPtr;
	}
}
// Gets the number of elements in the list.
int UnsortedListLinked::GetLength()
{
    length = 0;
    Node* tempPrt;
    while (first != NULL)
    {
        tempPrt = first;
        first = first->get_next();
        length++;
    }
    return length;
}
// Gets the element with matching college_ID.
Node UnsortedListLinked::GetItem(int college_ID)
{
    Node* tempPrt;
    Node item;
    while (first != NULL)
    {
        if(first->get_ID() == college_ID)
        {
            item = *first;
        }
        tempPrt = first;
        first = first->get_next();
    }

    return item;
}
// Delete each element in the list.
void UnsortedListLinked::MakeEmpty()
{
	Node* tempPtr;
	while (first != NULL)
	{
		tempPtr = first;
		first = first->get_next();
		delete tempPtr;
	}
	length = 0;
}
// Add an element to the list.
void UnsortedListLinked::PutItem(int college_ID, string college_name)
{
	Node* location;

	location = new Node();
	location->set_ID(college_ID);
    location->set_name(college_name);
	location->set_next(first);
	first = location;
}
// Remove an element from the list.
void UnsortedListLinked::DeleteItem(int college_ID)
{
	Node* location = first;
	Node* tempLocation;

	if (first->get_ID() == college_ID)
	{
		tempLocation = location;
		first = first->get_next();
	}
	else
	{
		while (location->get_next()->get_ID() != college_ID)
			location = location->get_next();

		tempLocation = location->get_next();
		location->set_next( location->get_next()->get_next() );
	}
	delete tempLocation;
	length--;
}
// Print the list.
void UnsortedListLinked::PrintList()
{
    while (first != NULL)
    {
        first->printMe();
        first = first->get_next();
    }
}


int main()
{
    // Unsorted list implemented using and array.
    // #####################################################################
	UnsortedListArray my_list_array;

    // Add 5 colleges.
	my_list_array.PutItem(1, "Taylor");
    my_list_array.PutItem(2, "Swift");
    my_list_array.PutItem(3, "Twice");
    my_list_array.PutItem(4, "Dahyun");
    my_list_array.PutItem(5, "Sana");

    // Print all colleges.
    my_list_array.PrintList();

    // Delete 2 colleges.
    my_list_array.DeleteItem(3);
    my_list_array.DeleteItem(2);

    // Get a college.
    my_list_array.GetItem(1).printMe();

    // Print all colleges.
    my_list_array.PrintList();

    // Add 4 colleges.
    my_list_array.PutItem(6, "Chaeyoung");
    my_list_array.PutItem(7, "Nayeon");
    my_list_array.PutItem(8, "Tzuyu");
    my_list_array.PutItem(9, "Jihyo");

    // Change 2 colleges.
    my_list_array.GetItem(1).set_name("Johnson");
    my_list_array.GetItem(9).set_name("Liu");

    // Print all colleges.
    my_list_array.PrintList();

    // Add 1 college.
    my_list_array.PutItem(10, "Fancy");

    // Print all colleges.
    my_list_array.PrintList();

    cout << "#####################################################################" << endl;

    // #####################################################################
    // Unsorted list implemented using linked list.
    // #####################################################################

    UnsortedListLinked linkedlist;

    // Add 5 colleges.
    linkedlist.PutItem(1, "Taylor");
    linkedlist.PutItem(2, "Swift");
    linkedlist.PutItem(3, "Twice");
    linkedlist.PutItem(4, "Dahyun");
    linkedlist.PutItem(5, "Sana");

    // Having more than one call of PrintList() leads
    // to a Segmentation Fault, but I don't know why.
    // linkedlist.PrintList();

    // Delete 2 colleges.
    linkedlist.DeleteItem(3);
    linkedlist.DeleteItem(2);

    // The GetItem function messes something up but I don't know what's happening.
    // linkedlist.GetItem(1).printMe();

    // Having more than one call of PrintList() leads
    // linkedlist.PrintList();

    // Add 4 colleges.
    linkedlist.PutItem(6, "Chaeyoung");
    linkedlist.PutItem(7, "Nayeon");
    linkedlist.PutItem(8, "Tzuyu");
    linkedlist.PutItem(9, "Jihyo");

    // The GetItem function messes something up but I don't know what's happening.
    // linkedlist.GetItem(1).set_name("Johnson");
    // linkedlist.GetItem(9).set_name("Liu");

    // Having more than one call of PrintList() leads
    // to a Segmentation Fault, but I don't know why.
    // linkedlist.PrintList();

    // Add 1 college.
    linkedlist.PutItem(10, "Fancy");

    // Print all colleges.
    linkedlist.PrintList();

    // Empty out the list.
    linkedlist.MakeEmpty();

    // Destruct the list.
    linkedlist.~UnsortedListLinked();

    return 0;
}
