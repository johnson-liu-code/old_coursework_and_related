// AVL trees
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <deque>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>
#include <math.h>

using namespace std;
struct TreeNode
{
	int data;
	TreeNode* left;
	TreeNode* right;
	int height;
};

class AVL
{
	TreeNode* root;
public:
	// Constructor and Destructor
	AVL();
	~AVL();
	// ADT Functions
	void makeEmpty(TreeNode* t);
	void PutItem(int key);
	void RemoveItem(int key);
	void printTree();
	void plotTree();

private:
	// Tree Rotations and Balance
	TreeNode * right_rotation(TreeNode * parent);
	TreeNode * left_rotation(TreeNode * parent);
	TreeNode * lr_rotation(TreeNode * parent);
	TreeNode * rl_rotation(TreeNode * parent);
	TreeNode * balance(TreeNode * t);

	// Internal BST Functions
	int diff(TreeNode * t);
	TreeNode * findMin(TreeNode * t);
	TreeNode * findMax(TreeNode * t);
	int height(TreeNode * t);

	// Internal AVL Functions
	void Insert(TreeNode *& T, int key);
	void RemoveItem(TreeNode *& T, int key);
	void plotTree(TreeNode * T, int level, int indentSpace);
	void inOrder(TreeNode * t);

	// Internal Plotting Funcitons
	void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue);
	void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue);
	void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue);
	string intToString(int val);
};

AVL::AVL()
{
	root = NULL;
}

AVL::~AVL()
{
	makeEmpty(root);
}


int AVL::height(TreeNode* t)
{
	return (t == NULL ? -1 : t->height);
}

void AVL::makeEmpty(TreeNode* T) {
	if (T == NULL)
		return;
	makeEmpty(T->left);
	makeEmpty(T->right);
	delete T;
}

TreeNode *AVL::right_rotation(TreeNode *T)
{
	TreeNode* S = T->left;
	TreeNode* B = S->right;
	S->right = T;
	T->left = B;
	T->height = max(height(T->left), height(T->right)) + 1;
	S->height = max(height(S->left), S->height) + 1;
	return S;
}

/*
* Left- Left Rotation
*/
TreeNode *AVL::left_rotation(TreeNode *T)
{
	TreeNode* S = T->right;
	TreeNode* B = S->left;
	S->left = T;
	T->right = B;
	T->height = max(height(T->left), height(T->right)) + 1;
	S->height = max(height(S->left), S->height) + 1;
	return S;
}

/*
* Left - Right Rotation
*/
TreeNode *AVL::lr_rotation(TreeNode *T)
{
	TreeNode* S = T->left;
	T->left = left_rotation(S);
	return right_rotation(T);
}

/*
* Right- Left Rotation
*/
TreeNode *AVL::rl_rotation(TreeNode *T)
{
	TreeNode *S = T->right;
	T->right = right_rotation(S);
	return left_rotation(T);
}

int AVL::diff(TreeNode *T)
{
	int l_height = height(T->left);
	int r_height = height(T->right);
	int b_factor = l_height - r_height;
	return b_factor;
}

TreeNode *AVL::balance(TreeNode *T)
{
	TreeNode *new_t = T;
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
	T->height = max(height(T->left), height(T->right)) + 1;
	return new_t;
}

void AVL::Insert(TreeNode*& T, int key)
// Inserts item into tree.
//It returns root of the modified subtree.
{
	if (T == NULL)
	{// Insertion place found.
		T = new TreeNode;
		T->right = NULL;
		T->left = NULL;
		T->data = key;
		T->height = 0;
	}
	else if (key < T->data) {
		Insert(T->left, key);    // Insert in left subtree.
		T->left = balance(T->left);
	}
	else {
		Insert(T->right, key);   // Insert in right subtree.
		T->right = balance(T->right);
	}
	T = balance(T);
}

void AVL::PutItem(int key)
// Calls recursive function Insert to insert item into tree.
{
	cout << "\nInserting ..........." << key << endl;
	Insert(root, key);
	//root = balance(root);
	plotTree();

}

TreeNode* AVL::findMin(TreeNode* T)
{
	if (T == NULL)
		return NULL;
	if (T->left == NULL)
		return T;
	return findMin(T->left);
}

TreeNode* AVL::findMax(TreeNode* T)
{
	if (T == NULL)
		return NULL;
	if (T->right == NULL)
		return T;

	return findMax(T->right);
}

void AVL::inOrder(TreeNode* T)
{
	if (T == NULL)
		return;
	inOrder(T->left);
	cout << T->data << " ";
	inOrder(T->right);
}

void AVL::printTree()
{
	if (root == NULL)
	{
		cout << "\n****\nEmpty Tree: No tree to print" << endl;
		return;
	}
	cout << "\nInorder printing of the tree: " << endl;
	inOrder(root);
	cout << endl << endl;
}

void AVL::plotTree()
{
	plotTree(root, 3, 6);
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
void AVL::RemoveItem(TreeNode*& T, int key)
{
	if (T == NULL)
		return;

	if (key < T->data) // Left branch
		RemoveItem(T->left, key);
	else if (key > T->data) // Right branch
		RemoveItem(T->right, key);
	else // Item found
	{
		// node with only one child or no child
		if ((T->left == NULL) || (T->right == NULL))
		{
			TreeNode *temp = T->left ? T->left : T->right;

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
			TreeNode* temp = findMin(T->right);

			// Copy the inorder successor's data to this node
			T->data = temp->data;

			// Delete the inorder successor
			RemoveItem(T->right, temp->data);
		}
	}

	// If the tree had only one node then return
	if (T == NULL)
		return;

	T = balance(T);
}

void AVL::RemoveItem(int key)
{
	cout << "\nDeleting ..........." << key << endl;
	RemoveItem(root, key);
	plotTree(root, 3, 6);
}

int main()
{
	AVL t;
	t.PutItem(19);
	t.PutItem(80);
	t.PutItem(14);
	t.PutItem(74);
	t.printTree();
	t.PutItem(62);
	t.PutItem(81);
	t.PutItem(59);
	t.PutItem(68);
	t.printTree();
	t.PutItem(4);
	t.PutItem(22);
	t.PutItem(103);
	t.PutItem(9);
	t.PutItem(21);
	t.RemoveItem(68);
	t.PutItem(73);
	t.PutItem(78);
	t.PutItem(75);
	t.RemoveItem(62);
	t.PutItem(23);
	t.PutItem(25);
	t.RemoveItem(9);
	t.RemoveItem(59);
	t.RemoveItem(21);
	t.RemoveItem(62);
	t.RemoveItem(103);
	t.RemoveItem(23);
	t.PutItem(9);
	t.RemoveItem(68);
	t.RemoveItem(81);
	t.printTree();
	t.RemoveItem(74);
	t.RemoveItem(25);
	t.RemoveItem(22);
	t.RemoveItem(80);
	t.RemoveItem(9);
	t.RemoveItem(14);
	t.RemoveItem(4);
	t.RemoveItem(19);
	t.printTree();

	char exit;
	cin >> exit;
}

// -------------------------------------- BLACK BOX ----------------------------------------------------------
// ****************** Beyond this point is a set of functions to plot a formatted tree  ***********************
// ************************************************************************************************************
// (It is blackbox, no need to understand the code below)
// Print the arm branches (eg, /    \ ) on a line
void AVL::printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue) {
	deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel / 2; i++) {
		cout << ((i == 0) ? setw(startLen - 1) : setw(nodeSpaceLen - 2)) << "" << ((*iter++) ? "/" : " ");
		cout << setw(2 * branchLen + 2) << "" << ((*iter++) ? "\\" : " ");
	}
	cout << endl;
}

// Print the branches and node (eg, ___10___ )
void AVL::printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue) {
	deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++) {
		cout << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
		cout << setw(branchLen + 2) << ((*iter) ? intToString((*iter)->data) : "");
		cout << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
	}
	cout << endl;
}

// Print the leaves only (just for the bottom row)
void AVL::printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue) {
	deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++) {
		cout << ((i == 0) ? setw(indentSpace + 2) : setw(2 * level + 2)) << ((*iter) ? intToString((*iter)->data) : "");
	}
	cout << endl;
}


// Convert an integer value to string
string AVL::intToString(int val) {
	ostringstream ss;
	ss << val;
	return ss.str();
}

void AVL::plotTree(TreeNode *T, int level, int indentSpace) {
	if (T == NULL) {
		cout << "\n****\nEmpty Tree: No tree to plot" << endl;
		return;
	}
	int h = T->height + 1;
	int nodesInThisLevel = 1;

	int branchLen = 2 * ((int)pow(2.0, h) - 1) - (3 - level)*(int)pow(2.0, h - 1);  // eq of the length of branch for each node of each level
	int nodeSpaceLen = 2 + (level + 1)*(int)pow(2.0, h);  // distance between left neighbor node's right arm and right neighbor node's left arm
	int startLen = branchLen + (3 - level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)

	deque<TreeNode*> nodesQueue;
	nodesQueue.push_back(root);
	for (int r = 1; r < h; r++) {
		printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
		branchLen = branchLen / 2 - 1;
		nodeSpaceLen = nodeSpaceLen / 2 + 1;
		startLen = branchLen + (3 - level) + indentSpace;
		printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);

		for (int i = 0; i < nodesInThisLevel; i++) {
			TreeNode *currNode = nodesQueue.front();
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
