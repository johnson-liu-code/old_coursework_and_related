// list.cpp
// simple linked list program

#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

// node object for the linked list
struct Node {
	int data;
	Node* next;
};

// implement a singly linked list
class LinkedList {
protected:
	Node* front;        // pointer to the front of the linked list
	int length;
public:
	// constructs an empty list
	LinkedList() {
		front = NULL;
		length = 0;
	}

	// search the list for a target value
	// return index if found or -1 if not found
	int Search(int targetVal) {
		Node* p;
		int count = 0;
		for (p = front; p != NULL; p = p->next) {
			if (p->data == targetVal) {
				return count;
			}
			count++;
		}
		return -1;
	}

	// deletes the list
	~LinkedList() {
		// remove objects from the list as long as list is not empty
		while (length > 0) {
			RemoveFront();
		}
	}

	// inserts a node at the front of the list
	void InsertFront(int newValue) {
		Node* newNode = new Node;
		newNode->data = newValue;
		if (front == NULL) {
			// list must be empty so make front & back point to new node
			front = newNode;
			newNode->next = NULL;
		}
		else {
			// list is not empty so insert between front and first node
			newNode->next = front;
			front = newNode;
		}
		length += 1;
	}

	// removes a node from the front of the list
	int RemoveFront() {
		int returnVal;
		Node *temp;
		if (front != NULL) {
			// list is not empty so remove & return first node
			returnVal = front->data;
			temp = front;
			front = front->next;
			length--;
		}
		else {
			// list is empty just return 0
			returnVal = 0;
		}
		return returnVal;
	}

	// outputs a string containing all the data values in the list
	void Output() {
		cout << "{";
		// loop through each node in the list until we find a null value
		for (Node* p = front; p != NULL; p = p->next) {
			cout << p->data;
			if (p->next != NULL)
				cout << ", ";
		}
		cout << "}\n\n";
	}

};

// use inheritance to create a Set class from the LinkedList class
class Set : public LinkedList {
public:
	// insert a new value only if it is unique (not already in the set)
	void Insert(int newValue) {
		int duplicate = Search(newValue);
		if (duplicate == -1)
			InsertFront(newValue);
	}

	// make this the union of two sets
	void Union(Set a, Set b) {
		for (Node* p = a.front; p != NULL; p = p->next)
			Insert(p->data);
		for (Node* p = b.front; p != NULL; p = p->next)
			Set::Insert(p->data);
	}

	// make this the intersection of two sets
	void Intersection(Set a, Set b) {
		for (Node* p = a.front; p != NULL; p = p->next)
			if (b.Search(p->data) != -1)
				Insert(p->data);
	}

	void Substraction(Set a, Set b) {
		for (Node* p = a.front; p != NULL; p = p->next)
			if (b.Search(p->data) == -1)
				Insert(p->data);
	}

};


int main() {
	Set setA, setB, setUnion, setIntersection, setDif;

	setA.Insert(5);
	setA.Insert(2);
	setA.Insert(3);
	setA.Insert(5);
	setA.Insert(2);
	setA.Insert(18);
	setA.Insert(21);

	cout << "Contents of setA: ";
	setA.Output();

	setB.Insert(1);
	setB.Insert(2);
	setB.Insert(4);
	setB.Insert(32);
	setB.Insert(18);
	setB.Insert(102);
	setB.Insert(2);
	setB.Insert(21);


	cout << "Contents of setB: ";
	setB.Output();

	setUnion.Union(setA, setB);
	cout << "Contents of setA union setB: ";
	setUnion.Output();

	setIntersection.Intersection(setA, setB);
	cout << "Contents of setA intersection setB: ";
	setIntersection.Output();

	setDif.Substraction(setA, setB);
	cout << "Contents of setA substraction setB: ";
	setDif.Output();


	char exit;
	cin >> exit;
	return 0;
}


