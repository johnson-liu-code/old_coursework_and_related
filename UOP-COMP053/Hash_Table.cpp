#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include <iomanip>
using namespace std;
const int TABLE_SIZE = 15;

/*
* HashEntry Class Declaration
*/
class HashEntry
{
public:
	int key;
	int value;
	bool deleted;
	HashEntry(int key, int value)
	{
		this->key = key;
		this->value = value;
		this->deleted = false;
	}
};

void displayTable(HashEntry **table);


/*
* HashMap Class Declaration
*/
class HashMap
{
public:
	HashEntry **table;

	HashMap()
	{
		table = new HashEntry *[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			table[i] = NULL;
		}
	}
	/*
	* Hash Function
	*/
	int HashFunc(int key)
	{
		cout << key << " % " << TABLE_SIZE << " = " << key % TABLE_SIZE << endl;
		return key % TABLE_SIZE;
	}
	/*
	* Insert Element at a key
	*/
	void Insert(int key, int value)
	{
		cout << "\nInserting (" << key << ", " << value << ") " << endl;
		int hash = HashFunc(key);
		while (table[hash] != NULL && !table[hash]->deleted && table[hash]->key != key)
		{
			hash = HashFunc(hash + 1);
		}
		if (table[hash] != NULL)
			delete table[hash];
		table[hash] = new HashEntry(key, value);
	}
	/*
	* Search Element at a key
	*/
	int Search(int key)
	{
		cout << "\nSearching key: "  << key << endl;
		int  hash = HashFunc(key);
		while ((table[hash] != NULL && (table[hash]->deleted || table[hash]->key != key)
		{
			hash = HashFunc(hash + 1);
		}
		if (table[hash] == NULL) {
			cout << "Key not found" << endl;
			return -1;
		}
		else
			if (table[hash]->deleted) {
				cout << "Key not found" << endl;
				return -1;
			}
			else
				cout << "Key found: (" << key << ", " << table[hash]->value << ") " << endl;
				return table[hash]->value;
	}

	/*
	* Remove Element at a key
	*/
	void Remove(int key)
	{
		cout << "\nRemoving key: " << key << endl;
		int hash = HashFunc(key);
		while (table[hash] != NULL)
		{
			if (table[hash]->key == key)
				break;
			hash = HashFunc(hash + 1);
		}
		if (table[hash] == NULL)
		{
			cout << "No Element found at key " << key << endl;
			return;
		}
		else
		{
			table[hash]->deleted = true;
		}
		cout << "Element " << key << " Deleted" << endl;
	}

	~HashMap()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if (table[i] != NULL)
				delete table[i];
			delete[] table;
		}
	}


};
/*
* Main Contains Menu
*/
int main()
{
	HashMap hash;
	hash.Insert(81, 70);
	hash.Insert(100, 48);
	hash.Insert(83, 29);
	hash.Insert(101, 400);

	displayTable(hash.table);

	hash.Insert(19, 403);
	hash.Insert(4, 12);

	displayTable(hash.table);

	hash.Insert(20, 30);
	displayTable(hash.table);

	hash.Insert(34, 18);
	displayTable(hash.table);

	hash.Search(81);


	hash.Search(34) ;

	hash.Remove(20);
	displayTable(hash.table);

	hash.Remove(83);
	displayTable(hash.table);

	hash.Insert(23, 27);
	displayTable(hash.table);
	hash.Insert(38, -9);
	displayTable(hash.table);

	hash.Remove(38);
	displayTable(hash.table);

	hash.Insert(42, 102);
	displayTable(hash.table);

	hash.Remove(101);
	displayTable(hash.table);

	hash.Search(101);
	hash.Search(42);
	hash.Search(34);

    hash.~HashMap();

	char exit;
	cin >> exit;
	return (0);
}


// ********************************** BLACK BOX CODE BELOW THIS POINT ********************
//
//
void displayTable(HashEntry **table) {
	cout << "\n\n =========== Hash Table Display =============" << endl;
	cout << (char)201;
	for (int i = 0; i < TABLE_SIZE; i++) {
		for (int j = 0; j < 10; j++)
			cout << (char)205;
		if (i < TABLE_SIZE - 1)
			cout << (char)203;
	}
	cout << (char)187;
	cout << endl;
	cout << (char)186;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table[i] != NULL && !table[i]->deleted) {
			cout << "(";
			cout << setw(3) << table[i]->key << ", " << setw(3) << table[i]->value << ")";
		}
		else
			cout << "          ";
		if (i < TABLE_SIZE - 1)
			cout << (char)186;
	}
	cout << (char)186;
	cout << endl;
	cout << (char)200;
	for (int i = 0; i < TABLE_SIZE; i++) {
		for (int j = 0; j < 10; j++)
			cout << (char)205;
		if (i < TABLE_SIZE - 1)
			cout << (char)202;
	}
	cout << (char)188;
	cout << endl;
	for (int i = 0; i < TABLE_SIZE; i++)
		cout << "    " << setw(3) << i << "    ";
	cout << endl << endl << endl;
}
// ***************************** END OF BLACK BOX CODE **************************************
