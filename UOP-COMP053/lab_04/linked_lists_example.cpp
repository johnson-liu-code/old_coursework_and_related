// 20190923 Example of an implementation of a linked list.
#include<iostream>
#include<string>

using namespace std;


// A node is an object that has info and a pointer to the next node (or to NULL).
class MovieNode
{
public:
    MovieNode()
    {
        this->name = "";
        this->length = 0;
        this->budget = 0;
        this->next = nullptr;
    }

    void printMe()
    {
        cout << "Name: " << this->name << endl;
        cout << "Length: " << this->length << endl;
        cout << "Budget: " << this->budget << endl << endl;
    }

    string getName()
    {
        return this->name;
    }
    void setName(string name)
    {
        this->name = name;
    }
    int getLength()
    {
        return this->length;
    }
    void setLength(int length)
    {
        this->length = length;
    }
    int getBudget()
    {
        return this->budget;
    }
    void setBudget(int budget)
    {
        this->budget = budget;
    }
    MovieNode* getNext()
    {
        return this->next;
    }
    void setNext(MovieNode* next)
    {
        this->next = next;
    }

private:
    string name;
    int length;
    int budget;
    MovieNode* next;
};

class MovieList
{
public:
    MovieList()
    {
        this->length = 0;
        this->first = nullptr;      // Start an empty list.
    }

    void printList()
    {
        for(MovieNode* element = this->first; element != nullptr;
            element = element->getNext())
        {
            element->printMe();
        }
    }

    void addElement(string movie_name, int length, int budget);

    void deleteElement(string movie_name);

    int getLength();


    int length;
    MovieNode* first;
};

void MovieList::addElement(string movie_name, int length, int budget)
{
    MovieNode* newNode = new MovieNode();       // Make a new node.
    newNode->setName(movie_name);
    newNode->setLength(length);
    newNode->setBudget(budget);

    if(this->first == nullptr)
    {
        this->first = newNode;                  // Set pointer to the new node.
    }
    else
    {
        newNode->setNext(this->first);            // Set next pointer to the previous node.
        this->first = newNode;                  // Set pointer to the new node.
    }

    this->length++;
}

void MovieList::deleteElement(string movie_name)
{
    MovieNode* current_location = first;
    MovieNode* temp_location;

    if(first->getName() == movie_name)
    {
        temp_location = current_location;
        first = first->getNext();
    }
    else
    {
        while(current_location->getNext()->getName() != movie_name)
        {
            current_location = current_location->getNext();
        }
        temp_location = current_location->getNext();
        current_location->setNext(current_location->getNext()->getNext());
    }
    delete temp_location;
    length--;
}

int MovieList::getLength()
{
    return this->length;
}


int main()
{
    cout << "Hello" << endl;

    MovieList my_list;
    my_list.addElement("Movie1", 100, 1000000);
    // cout << my_list.getLength() << endl;
    my_list.addElement("Movie2", 90, 2000000);
    // cout << my_list.getLength() << endl;
    // my_list.addElement("Movie3", 110, 300000000);
    // cout << my_list.getLength() << endl;
    my_list.printList();
    my_list.deleteElement("Movie1");
    my_list.printList();


    char exit;
    cin >> exit;

    return 0;
}
