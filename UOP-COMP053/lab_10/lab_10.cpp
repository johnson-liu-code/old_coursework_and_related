#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>
#include <math.h>


// Most of the code below is taken from Professor Nehoran's example code.

class Node
{
public:
    Node()
    {
    }
    Node(int rank, std::string name, int ID)
    {
        this->rank = rank;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0;
        this->name = name;
        this->ID = ID;
    }

    int rank;
    Node* left;
    Node* right;
    int height;
    std::string name;
    int ID;
};

class AVL
{

public:
    Node* root;

    // Constructor and Destructor
    AVL();
    ~AVL();
    // ADT Functions
    void makeEmpty(Node* t);
    void PutItem(Node* candidate);
    void RemoveItem(Node* candidate);
    void printTree();
    void plotTree();
    void printAboveFive();
    //bool check_ID(Node* T, Node* candidate);
    int candID[1000];
    int len=0;

private:
    // Tree Rotations and Balance
    Node* right_rotation(Node* parent);
    Node* left_rotation(Node* parent);
    Node* lr_rotation(Node* parent);
    Node* rl_rotation(Node* parent);
    Node* balance(Node* t);

    // Internal BST Functions
    int diff(Node* t);
    Node* findMin(Node* t);
	Node* findMax(Node* t);
	int height(Node* t);

    // Internal AVL Functions
    void Insert(Node* &T, Node* candidate);
    void RemoveItem(Node* &T, Node* candidate);
    void plotTree(Node* T, int level, int indentSpace);
	void inOrder(Node* t);
    void inOrderFive(Node* t);

    // Internal Plotting Funcitons
	void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue);
	void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue);
	void printLeaves(int indentSpace, int level, int nodesInThisLevel, const std::deque<Node*>& nodesQueue);
	std::string intToString(int val);
};

AVL::AVL()
{
	root = NULL;
}
AVL::~AVL()
{
	makeEmpty(root);
}
void AVL::plotTree()
{
	plotTree(root, 3, 6);
}
void AVL::makeEmpty(Node* T) {
	if (T == NULL)
		return;
	makeEmpty(T->left);
	makeEmpty(T->right);
	delete T;
}
int AVL::height(Node* t)
{
	return (t == NULL ? -1 : t->height);
}
Node* AVL::findMin(Node* T)
{
	if (T == NULL)
		return NULL;
	if (T->left == NULL)
		return T;
	return findMin(T->left);
}
Node* AVL::findMax(Node* T)
{
	if (T == NULL)
		return NULL;
	if (T->right == NULL)
		return T;

	return findMax(T->right);
}
Node* AVL::right_rotation(Node* T)
{
    Node* S = T->left;
	Node* B = S->right;
	S->right = T;
	T->left = B;
	T->height = std::max(height(T->left), height(T->right)) + 1;
	S->height = std::max(height(S->left), S->height) + 1;
	return S;
}
Node *AVL::left_rotation(Node *T)
{
	Node* S = T->right;
	Node* B = S->left;
	S->left = T;
	T->right = B;
	T->height = std::max(height(T->left), height(T->right)) + 1;
	S->height = std::max(height(S->left), S->height) + 1;
	return S;
}
Node* AVL::lr_rotation(Node* T)
{
	Node* S = T->left;
	T->left = left_rotation(S);
	return right_rotation(T);
}
Node* AVL::rl_rotation(Node* T)
{
	Node* S = T->right;
	T->right = right_rotation(S);
	return left_rotation(T);
}
int AVL::diff(Node* T)
{
	int l_height = height(T->left);
	int r_height = height(T->right);
	int b_factor = l_height - r_height;
	return b_factor;
}
Node* AVL::balance(Node* T)
{
	Node* new_t = T;
	int T_balance = diff(T);
	if (diff(T) > 1)
	{
		if (diff(T->left) > 0)
			new_t = right_rotation(T);
		else
			new_t = lr_rotation(T);
	}

	else if (diff(T) < -1)
	{
		if (diff(T->right) < 0)
			new_t = left_rotation(T);
		else
			new_t = rl_rotation(T);
	}

	T->height = std::max(height(T->left), height(T->right)) + 1;
	return new_t;
}
void AVL::Insert(Node* &T, Node* candidate)
// Inserts item into tree.
//It returns root of the modified subtree.
{
	if (T == NULL)
	{// Insertion place found.
		T = new Node;
		T->right = NULL;
		T->left = NULL;
		T->rank = candidate->rank;
		T->height = 0;
	}

	else if (candidate->rank < T->rank)
    {
		Insert(T->left, candidate);    // Insert in left subtree.
		T->left = balance(T->left);
	}

	else
    {
		Insert(T->right, candidate);   // Insert in right subtree.
		T->right = balance(T->right);
	}

	T = balance(T);
}
void AVL::PutItem(Node* candidate)
// Calls recursive function Insert to insert item into tree.
{

    for(int i=0;i<len;i++)
    {
        if(candID[i]==candidate->ID)
        {
            std::cout<<"Candidate ID " << candidate->ID << " already exists"<<std::endl;
            return;
        }
    }
	std::cout << "\nInserting ........... candidate " << candidate->name << " with a rank of " << candidate->rank << std::endl;
    candID[len]=candidate->ID;
    len++;
	Insert(root, candidate);

	//root = balance(root);
}
// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
void AVL::RemoveItem(Node* &T, Node* candidate)
{
	if (T == NULL)
		return;

	if (candidate->rank < T->rank) // Left branch
		RemoveItem(T->left, candidate);
	else if (candidate->rank > T->rank) // Right branch
		RemoveItem(T->right, candidate);
	else // Item found
	{
		// node with only one child or no child
		if ((T->left == NULL) || (T->right == NULL))
		{
			Node* temp = T->left ? T->left : T->right;

			// No child case
			if (temp == NULL)
			{
				temp = T;
				T = NULL;
			}
			else // One child case
				*T = *temp; // Copy the contents of
							// the non-empty child
			delete temp;
		}
		else
		{
			// node with two children
			Node* temp = findMin(T->right);

			// Copy the inorder successor's rank to this node
			T->rank = temp->rank;

			// Delete the inorder successor
			RemoveItem(T->right, temp);
		}
	}

	// If the tree had only one node then return
	if (T == NULL)
		return;

	T = balance(T);
}
void AVL::RemoveItem(Node* candidate)
{
	std::cout << "\nDeleting ........... candidate " << candidate->name << " with a rank of " << candidate->rank << std::endl;
	RemoveItem(root, candidate);
    // plotTree(root, 3, 6);
}
void AVL::inOrder(Node* T)
{
	if (T == NULL)
		return;
	inOrder(T->left);
	std::cout << T->rank << " ";
	inOrder(T->right);
}
int trigger=0;
void AVL::inOrderFive(Node* T)
{
	if (T == NULL)
		return;
    trigger++;
	if(trigger<=5)
    {
        inOrderFive(T->left);
    	std::cout << T->rank << " ";
    	inOrderFive(T->right);
    }
}

void AVL::printAboveFive()
{
    // i++;
    // if (i > 5)
    //     return;
    // if (T == NULL)
	// 	return;
	// printAboveFive(T->left, i);
	// // std::cout << T->rank << " ";
	// printAboveFive(T->right, i);
    if (root == NULL)
	{
		std::cout << "\n****\nEmpty Tree: No tree to print" << std::endl;
		return;
	}
	std::cout << "\nInorder Five printing Top 5 of the tree: " << std::endl;
	inOrderFive(root);
	std::cout << std::endl << std::endl;

}
void AVL::printTree()
{
	if (root == NULL)
	{
		std::cout << "\n****\nEmpty Tree: No tree to print" << std::endl;
		return;
	}
	std::cout << "\nInorder printing of the tree: " << std::endl;
	inOrder(root);
	std::cout << std::endl << std::endl;
}

bool same = false;


int main()
{

    std::cout << "Most of this code is taken from Professor Nehoran's example code." << std::endl;

    AVL candidates;

    Node* candidate01 = new Node(1, "Person01", 00000);
    candidates.PutItem(candidate01);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate02 = new Node(2, "Person02", 11111);
    candidates.PutItem(candidate02);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate03 = new Node(3, "Person03", 22222);
    candidates.PutItem(candidate03);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate04 = new Node(4, "Person04", 33333);
    candidates.PutItem(candidate04);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate05 = new Node(5, "Person05", 44444);
    candidates.PutItem(candidate05);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate06 = new Node(6, "Person06", 55555);
    candidates.PutItem(candidate06);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate07 = new Node(7, "Person07", 44444);
    candidates.PutItem(candidate07);
    candidates.printTree();
    candidates.plotTree();

    candidates.RemoveItem(candidate05);
    candidates.printTree();
    candidates.plotTree();
    candidates.RemoveItem(candidate01);
    candidates.printTree();
    candidates.plotTree();

    Node* candidate08 = new Node(8, "Person08", 66666);
    candidates.PutItem(candidate08);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate09 = new Node(9, "Person09", 77777);
    candidates.PutItem(candidate09);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate10 = new Node(10, "Person10", 88888);
    candidates.PutItem(candidate10);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate11 = new Node(11, "Person11", 99999);
    candidates.PutItem(candidate11);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate12 = new Node(12, "Person12", 11010);
    candidates.PutItem(candidate12);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate13 = new Node(13, "Person13", 12020);
    candidates.PutItem(candidate13);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate14 = new Node(14, "Person14", 11010);
    candidates.PutItem(candidate14);
    candidates.printTree();
    candidates.plotTree();

    candidates.RemoveItem(candidate08);
    candidates.printTree();
    candidates.plotTree();
    candidates.RemoveItem(candidate02);
    candidates.printTree();
    candidates.plotTree();

    Node* candidate15 = new Node(15, "Person15", 13030);
    candidates.PutItem(candidate15);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate16 = new Node(16, "Person16", 14040);
    candidates.PutItem(candidate16);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate17 = new Node(17, "Person17", 15050);
    candidates.PutItem(candidate17);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate18 = new Node(18, "Person18", 16060);
    candidates.PutItem(candidate18);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate19 = new Node(19, "Person19", 17070);
    candidates.PutItem(candidate19);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate20 = new Node(20, "Person20", 18080);
    candidates.PutItem(candidate20);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate21 = new Node(21, "Person21", 19090);
    candidates.PutItem(candidate21);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate22 = new Node(22, "Person22", 10101);
    candidates.PutItem(candidate22);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate23 = new Node(23, "Person23", 11111);
    candidates.PutItem(candidate23);
    candidates.printTree();
    candidates.plotTree();
    Node* candidate24 = new Node(24, "Person24", 10101);
    candidates.PutItem(candidate24);
    candidates.printTree();
    candidates.plotTree();

    candidates.RemoveItem(candidate24);
    candidates.printTree();
    candidates.plotTree();

    std::cout << "Printing top five: " << std::endl;
    candidates.printAboveFive();
    std::cout << "This function doesn't work correctly, but I can't figure out why" << std::endl;

    trigger = 0;


	char exit;
	std::cin >> exit;



    return 0;
}


// The code below is taken from Professor Nehoran's example code.

// -------------------------------------- BLACK BOX ----------------------------------------------------------
// ****************** Beyond this point is a set of functions to plot a formatted tree  ***********************
// ************************************************************************************************************
// (It is blackbox, no need to understand the code below)
// Print the arm branches (eg, /    \ ) on a line
void AVL::printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue) {
	std::deque<Node*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel / 2; i++) {
		std::cout << ((i == 0) ? std::setw(startLen - 1) : std::setw(nodeSpaceLen - 2)) << "" << ((*iter++) ? "/" : " ");
		std::cout << std::setw(2 * branchLen + 2) << "" << ((*iter++) ? "\\" : " ");
	}
	std::cout << std::endl;;
}

// Print the branches and node (eg, ___10___ )
void AVL::printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue) {
	std::deque<Node*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++) {
		std::cout << ((i == 0) ? std::setw(startLen) : std::setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? std::setfill('_') : std::setfill(' '));
		std::cout << std::setw(branchLen + 2) << ((*iter) ? intToString((*iter)->rank) : "");
		std::cout << ((*iter && (*iter)->right) ? std::setfill('_') : std::setfill(' ')) << std::setw(branchLen) << "" << std::setfill(' ');
	}
	std::cout << std::endl;;
}

// Print the leaves only (just for the bottom row)
void AVL::printLeaves(int indentSpace, int level, int nodesInThisLevel, const std::deque<Node*>& nodesQueue) {
	std::deque<Node*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++) {
		std::cout << ((i == 0) ? std::setw(indentSpace + 2) : std::setw(2 * level + 2)) << ((*iter) ? intToString((*iter)->rank) : "");
	}
	std::cout << std::endl;;
}


// Convert an integer value to string
std::string AVL::intToString(int val) {
	std::ostringstream ss;
	ss << val;
	return ss.str();
}

void AVL::plotTree(Node* T, int level, int indentSpace) {
	if (T == NULL) {
		std::cout << "\n****\nEmpty Tree: No tree to plot" << std::endl;;
		return;
	}
	int h = T->height + 1;
	int nodesInThisLevel = 1;

	int branchLen = 2 * ((int)pow(2.0, h) - 1) - (3 - level)*(int)pow(2.0, h - 1);  // eq of the length of branch for each node of each level
	int nodeSpaceLen = 2 + (level + 1)*(int)pow(2.0, h);  // distance between left neighbor node's right arm and right neighbor node's left arm
	int startLen = branchLen + (3 - level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)

	std::deque<Node*> nodesQueue;
	nodesQueue.push_back(root);
	for (int r = 1; r < h; r++) {
		printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
		branchLen = branchLen / 2 - 1;
		nodeSpaceLen = nodeSpaceLen / 2 + 1;
		startLen = branchLen + (3 - level) + indentSpace;
		printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);

		for (int i = 0; i < nodesInThisLevel; i++) {
			Node* currNode = nodesQueue.front();
			nodesQueue.pop_front();
			if (currNode) {
				nodesQueue.push_back(currNode->left);
				nodesQueue.push_back(currNode->right);
			}
			else {
				nodesQueue.push_back(NULL);
				nodesQueue.push_back(NULL);
			}
		}
		nodesInThisLevel *= 2;
	}
	printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
	printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue);
}

// -------------------------------------- END BLACK BOX -----------------------------------------------------
