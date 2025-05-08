#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <fstream>

// Most of the code below is taken from Professor Nehoran's example code.

class Node
{
public:
    Node()
    {
    }
    Node(int rank, std::string name, int age, int goals, int salary)
    {
        this->rank = rank;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0;
        this->name = name;
        this->age = age;
        this->goals = goals;
        this->salary = salary;
    }

    int rank;
    Node* left;
    Node* right;
    int height;
    std::string name;
    int age;
    int goals;
    int salary;
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
    void PutItem(Node* player);
    void RemoveItem(Node* player);
    void printTree();
    void plotTree();
    void printHigherRank(int rank);
    void printLowerRank(int rank);
    void printFindRank(int rank);
    void printRemoveRank(int rank);

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
    void Insert(Node* &T, Node* player);
    void RemoveItem(Node* &T, Node* player);
    void plotTree(Node* T, int level, int indentSpace);
	void inOrder(Node* t);
    void HigherRank(Node* t, int rank);
    void LowerRank(Node* t, int rank);
    void findRank(Node* t, int rank);
    void removeRank(Node* t, int rank);

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
void AVL::Insert(Node* &T, Node* player)
// Inserts item into tree.
//It returns root of the modified subtree.
{
	if (T == NULL)
	{// Insertion place found.
		T = new Node;
		T->right = NULL;
		T->left = NULL;
		T->rank = player->rank;
		T->height = 0;
        T->name = player->name;
        T->age = player->age;
        T->goals = player->goals;
        T->salary = player->salary;
	}

	else if (player->rank < T->rank)
    {
		Insert(T->left, player);    // Insert in left subtree.
		T->left = balance(T->left);
	}

	else
    {
		Insert(T->right, player);   // Insert in right subtree.
		T->right = balance(T->right);
	}

	T = balance(T);
}
void AVL::PutItem(Node* player)
// Calls recursive function Insert to insert item into tree.
{
	std::cout << "\nInserting ........... player " << player->name << " with a rank of " << player->rank << std::endl;
	Insert(root, player);

	//root = balance(root);
}
// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
void AVL::RemoveItem(Node* &T, Node* player)
{
	if (T == NULL)
		return;

	if (player->rank < T->rank) // Left branch
		RemoveItem(T->left, player);
	else if (player->rank > T->rank) // Right branch
		RemoveItem(T->right, player);
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
void AVL::RemoveItem(Node* player)
{
	std::cout << "\nDeleting ........... player " << player->name << " with a rank of " << player->rank << std::endl;
	RemoveItem(root, player);
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
void AVL::HigherRank(Node* T, int rank)
{
    if (T == NULL)
		return;
	HigherRank(T->left, rank);
    if (T->rank < rank)
        std::cout << "Player " << T->name << " with a rank of " << T->rank << " has a higher (smaller number) rank than " << rank << std::endl;
	HigherRank(T->right, rank);
}
void AVL::printHigherRank(int rank)
{
    if (root == NULL)
	{
		return;
	}
	std::cout << "\nPrinting players with a higher rank than " << rank << ":" << std::endl;
	HigherRank(root, rank);
	std::cout << std::endl << std::endl;
}
void AVL::LowerRank(Node* T, int rank)
{
    if (T == NULL)
        return;
    LowerRank(T->left, rank);
    if (T->rank > rank)
        std::cout << "Player " << T->name << " with a rank of " << T->rank << " has a lower (larger number) rank than " << rank << std::endl;
	LowerRank(T->right, rank);
}
void AVL::printLowerRank(int rank)
{
    if (root == NULL)
	{
		return;
	}
	std::cout << "\nPrinting players with a lower rank than " << rank << ":" << std::endl;
	LowerRank(root, rank);
	std::cout << std::endl << std::endl;
}
void AVL::findRank(Node* T, int rank)
{
    if (T == NULL)
        return;
    findRank(T->left, rank);
    if (T->rank == rank)
        std::cout << "Player " << T->name << " has a rank of " << T->rank << std::endl;
    findRank(T->right, rank);
}
void AVL::printFindRank(int rank)
{
    if (root == NULL)
	{
		return;
	}
	std::cout << "\nPrinting players with a rank of " << rank << ":" << std::endl;
	findRank(root, rank);
	std::cout << std::endl << std::endl;
}
void AVL::removeRank(Node* T, int rank)
{
    if (T == NULL)
        return;
    removeRank(T->left, rank);
    if (T->rank == rank)
        {
            std::cout << "Player " << T->name << " has a rank of " << T->rank << " and will be removed" << std::endl;
            RemoveItem(T);
        }
    removeRank(T->right, rank);
}
void AVL::printRemoveRank(int rank)
{
    if (root == NULL)
	{
		return;
	}
	std::cout << "\nRemoving players with a rank of " << rank << ":" << std::endl;
	removeRank(root, rank);
	std::cout << std::endl << std::endl;
}


int main()
{

    std::cout << "Most of this code is taken from Professor Nehoran's example code." << std::endl;

    std::ifstream inFile;
    std::string inFileName = "soccer.txt";
    inFile.open(inFileName);

    if (!inFile)
    {
        std::cout << "File not found: " << inFileName << std::endl;
    }

    std::ofstream outFile;
    std::string outFileName = "soccer_output.txt";   // name of output file
    outFile.open(outFileName);                  // open output file

    bool quit = false;
    std::string command;
    inFile >> command;

    int rank;
    std::string name;
    int age;
    int goals;
    int salary;

    AVL players;

    while (quit == false)
    {
        if (command == "ADD")
        {
            inFile >> rank;
            inFile >> name;
            inFile >> age;
            inFile >> goals;
            inFile >> salary;
            Node* player = new Node(rank, name, age, goals, salary);
            players.PutItem(player);
            players.printTree();
            players.plotTree();
            outFile << "Adding player with rank " << rank << std::endl;
        }

        else if (command == "HIGHER")
        {
            inFile >> rank;
            players.printHigherRank(rank);
            outFile << "Printing players with ranks higher than " << rank << std::endl;
        }

        else if (command == "LOWER")
        {
            inFile >> rank;
            players.printLowerRank(rank);
            outFile << "Printing players with ranks lower than " << rank << std::endl;
        }

        else if (command == "FIND")
        {
            inFile >> rank;
            players.printFindRank(rank);
            outFile << "Finding players with rank " << rank << std::endl;
        }

        else if (command == "REMOVE")
        {
            inFile >> rank;
            players.printRemoveRank(rank);
            outFile << "Removing players with rank " << rank << std::endl;
        }

        else if (command == "QUIT")
        {
            quit = true;
            outFile << "Quitting" << std::endl;
        }

    inFile >> command;
    }



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
