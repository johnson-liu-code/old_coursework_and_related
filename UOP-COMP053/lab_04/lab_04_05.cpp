#include<fstream>
#include<iostream>
#include<string>

using namespace std;


class Node
{
public:
    Node()
    {
        college_ID = 0;
        college_name = "";
        next = nullptr;
    }

    void Print();

    void setCollege(int college_ID, string college_name)
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
    void set_next(Node *next)
    {
        this->next = next;
    }
    Node* get_next()
    {
        return this->next;
    }

    void printMe()
    {
        cout << endl << "---------------------------------------------" << endl;
        cout << "College ID: " << college_ID << endl;
        cout << "College Name: " << college_name << endl;
    }

private:
    int college_ID;
    string college_name;
    Node *next;
};

void Node::Print()
// pre:  out has been opened.
// post: value has been sent to the stream out.
{
	cout << "College ID: " << college_ID << endl;
    cout << "College Name: " << college_name << endl << endl;
}

// void add_item(int age)
// {
//     Node *newNode;
//     newNode = new Node();
//     newNode->info = age;
//     newNode->next = ageList;
//     ageList = newNode;
// }
//
// class linkedlList
// {
// public:
//     linkedList()
//     {
//         first = nullptr;
//     }
//     ~linkedList()
//     {
//         temp = first;
//         while(temp != nullptr)
//         {
//             first = first->next;
//             delete temp;
//             temp = first;
//         }
//     }
//
// private:
//     Node *first;
//     int length;
// };

// linkedList::add_item(int age)
// {
//     Node *newNode = new Node();
//     newNode->next = first;
//     first->newNode;
// }

// linkedList::empty_list()
// {
//     temp = first;
//     while(temp != nullptr)
//     {
//         first = first->next;
//         delete temp;
//         temp = first;
//     }
// }

class UnsortedListArray
{
public:
	UnsortedListArray();
	// Constructor

	void MakeEmpty();
	// Function: Returns the list to the empty state.
	// Post:  List is empty.

	bool IsFull() const;
	// Function:  Determines whether list is full.
	// Pre:  List has been initialized.
	// Post: Function value = (list is full)

	int GetLength() const;
	// Function: Determines the number of elements in list.
	// Pre:  List has been initialized.
	// Post: Function value = number of elements in list

	Node GetItem(int college_ID);
	// Function: Retrieves list element whose key matches item's key (if
	//           present).
	// Pre:  List has been initialized.
	//       Key member of item is initialized.
	// Post: If there is an element someItem whose key matches
	//       item's key, then found = true and someItem is returned.
	// 	 otherwise found = false and item is returned.
	//       List is unchanged.

	void PutItem(int college_ID, string college_name);
	// Function: Adds item to list.
	// Pre:  List has been initialized.
	//       List is not full.
	//       item is not in list.
	// Post: item is in list.

	void DeleteItem(int college_ID);
	// Function: Deletes the element whose key matches item's key.
	// Pre:  List has been initialized.
	//       Key member of item is initialized.
	//       One and only one element in list has a key matching item's key.
	// Post: No element in list has a key matching item's key.

	void ResetList();
	// Function: Initializes current position for an iteration through the list.
	// Pre:  List has been initialized.
	// Post: Current position is prior to list.

    Node GetNextItem();
	// Function: Gets the next element in list.
	// Pre:  List has been initialized and has not been changed since last call.
	//       Current position is defined.
	//       Element at current position is not last in list.
	//
	// Post: Current position is updated to next position.
	//       item is a copy of element at current position.

    void PrintList();
    // Function: Prints the list.

private:
	int length;
    Node info[20];
	int currentPos;
};

UnsortedListArray::UnsortedListArray()
{
	length = 0;
}

bool UnsortedListArray::IsFull() const
{
	return (length == 20);
}

int UnsortedListArray::GetLength() const
{
	return length;
}

Node UnsortedListArray::GetItem(int college_ID)
// Pre:  Key member(s) of item is initialized.
// Post: If found, item's key matches an element's key in the
//       list and a copy of that element has been returned;
//       otherwise, item is returned.
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

void UnsortedListArray::MakeEmpty()
// Post: list is empty.
{
	length = 0;
}

void UnsortedListArray::PutItem(int college_ID, string college_name)
// Post: item is in the list.
{
	info[length].setCollege(college_ID, college_name);
	length++;
}

void UnsortedListArray::DeleteItem(int key)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
{
	int location = 0;

	while (info[location].get_ID() != key)
		location++;

	info[location] = info[length - 1];
	length--;
}

void UnsortedListArray::ResetList()
// Post: currentPos has been initialized.
{
	currentPos = -1;
}

Node UnsortedListArray::GetNextItem()
// Pre:  ResetList was called to initialized iteration.
//       No transformer has been executed since last call.
//       currentPos is defined.
// Post: item is current item.
//       Current position has been updated.
{
	currentPos++;
	return info[currentPos];
}

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

class UnsortedListLinked
{
public:
	UnsortedListLinked();
	// Constructor

    ~UnsortedListLinked();

	void MakeEmpty();
	// Function: Returns the list to the empty state.
	// Post:  List is empty.

	int GetLength();
	// Function: Determines the number of elements in list.
	// Pre:  List has been initialized.
	// Post: Function value = number of elements in list

	void GetItem(int college_ID);
	// Function: Retrieves list element whose key matches item's key (if
	//           present).
	// Pre:  List has been initialized.
	//       Key member of item is initialized.
	// Post: If there is an element someItem whose key matches
	//       item's key, then found = true and someItem is returned.
	// 	 otherwise found = false and item is returned.
	//       List is unchanged.

	void PutItem(int college_ID, string college_name);
	// Function: Adds item to list.
	// Pre:  List has been initialized.
	//       List is not full.
	//       item is not in list.
	// Post: item is in list.

	void DeleteItem(int college_ID);
	// Function: Deletes the element whose key matches item's key.
	// Pre:  List has been initialized.
	//       Key member of item is initialized.
	//       One and only one element in list has a key matching item's key.
	// Post: No element in list has a key matching item's key.

    void PrintList();
    // Function: Prints the list.

private:
	int length;
    Node *first;
};

UnsortedListLinked::UnsortedListLinked()  // Class constructor
{
	length = 0;
	first = NULL;
}

UnsortedListLinked::~UnsortedListLinked()
// Post: List is empty; all items have been deallocated.
{
	Node* tempPtr;

	while (first != NULL)
	{
		tempPtr = first;
		first = first->get_next();
		delete tempPtr;
	}
}

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

void UnsortedListLinked::GetItem(int college_ID)
{
    Node* tempPrt;
    while (first != NULL)
    {
        if(first->get_ID() == college_ID)
        {
            first->printMe();
        }
        tempPrt = first;
        first = first->get_next();
        length++;
    }
}

void UnsortedListLinked::MakeEmpty()
// Post: List is empty; all items have been deallocated.
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

void UnsortedListLinked::PutItem(int college_ID, string college_name)
// item is in the list; length has been incremented.
{
	Node* location;			// Declare a pointer to a node

	location = new Node();		// Get a new node
	location->set_ID(college_ID);		// Store the item in the node
    location->set_name(college_name);
	location->set_next(first);	// Store address of first node
						  //   in next field of new node
	first = location;		// Store address of new node into
						  //   external pointer
	length++;				// Increment length of the list
}

void UnsortedListLinked::DeleteItem(int college_ID)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
{
	Node* location = first;
	Node* tempLocation;

	// Locate node to be deleted.
	if (first->get_ID() == college_ID)
	{
		tempLocation = location;
		first = first->get_next();		// Delete first node.
	}
	else
	{
		while (location->get_next()->get_ID() != college_ID)
			location = location->get_next();

		// Delete node at location->next
		tempLocation = location->get_next();
		location->set_next( location->get_next()->get_next() );
	}
	delete tempLocation;
	length--;
}


int main()
{
	// UnsortedListArray my_list_array;
    //
	// my_list_array.PutItem(1, "Taylor");
    // my_list_array.PutItem(2, "Swift");
    // my_list_array.PutItem(3, "Twice");
    // my_list_array.PutItem(4, "Dahyun");
    // my_list_array.PutItem(5, "Sana");
    //
    // my_list_array.PrintList();
    //
    // my_list_array.DeleteItem(3);
    // my_list_array.DeleteItem(2);
    //
    // my_list_array.GetItem(1).printMe();
    //
    // my_list_array.PrintList();
    //
    // my_list_array.PutItem(6, "Chaeyoung");
    // my_list_array.PutItem(7, "Nayeon");
    // my_list_array.PutItem(8, "Tzuyu");
    // my_list_array.PutItem(9, "Jihyo");
    //
    // my_list_array.GetItem(1).set_name("Johnson");
    // my_list_array.GetItem(9).set_name("Liu");
    //
    // my_list_array.PrintList();

    // my_list_array.PutItem(10, "Fancy");

    // my_list_array.PrintList();





    // Node *ageList = nullptr;
    // ageList = new Node();
    // ageList->set_age(13);

    // add_item(50);


    return 0;
}
