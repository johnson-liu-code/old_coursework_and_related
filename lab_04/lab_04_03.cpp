#include<iostream>
#include<string>

using namespace std;

struct NodeType
{
    ItemType info;
    NodeType* next;
}

class UnsortedType
{
public:
  UnsortedType();
  void MakeEmpty();
  bool IsFull() const;
  int GetLength() const;
  ItemType GetItem(ItemType item, bool& found);
  void PutItem(ItemType item);
  void DeleteItem(ItemType item);
  void ResetList();
  ItemType GetNextItem();

private:
  NodeType* listData;
  int length;
  NodeType* current Pos;
};

void UnsortedType::PutItem(ItemType item)
// item is in the list; length has been incremented.
{

  NodeType* location;              // Declare a pointer to a node

  location = new NodeType;         // Get a new node
  location->info = item;           // Store the item in the node
  location->next = listData;       // Store address of first node
                                   //   in next field of new node
  listData = location;             // Store address of new node
                                   //   into external pointer
  length++;                        // Increment length of the list
}
