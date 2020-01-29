
#include<iostream>
#include<string>
#include<stdlib.h>


class Node
{
public:
    Node(int index, int num)
    {
        this->index = index;
        this->num = num;
        this->left = nullptr;
        this->right = nullptr;
    }

    int index;
    int num;
    Node* left;
    Node* right;
};

void printNodes(Node* root)                             // function to print the values of the nodes in the tree
{
    if (root == nullptr)                                // if there is no tree, return nothing
    {
        return;
    }
    if (root->left != nullptr)                          // if left spot is not empty, recurse into that node
    {
        printNodes(root->left);
    }
    std::cout << "node " << root->index << " has a value of " << root->num << std::endl;    // print the index and num of current node
    if (root->right != nullptr)                         // if right spot is not empty, resurse into that node
    {
        printNodes(root->right);
    }
}

void addNode(Node* root, int index, int num)            // function to add a node to the tree
{
    if (num < root->num)                                // if num is less than the num at the current node
    {
        if (root->left == nullptr)                      // if left spot is empty, create a node there
        {
            root->left = new Node(index, num);
        }
        else                                            // else, recurse with left node being the root
        {
            addNode(root->left, index, num);
        }
    }
    else                                                // if num is greater than the num at the current node
    {
        if (root->right == nullptr)                     // if right spot is empty, create a node there
        {
            root->right = new Node(index, num);
        }
        else                                            // else, recurse with right node being the root
        {
            addNode(root->right, index, num);
        }
    }
}

Node* emptyTree(Node* root)                             // function to delete node
{
    if (root != nullptr)                                // if the tree is not empty
    {
        emptyTree(root->left);                          // delete left descendents
        emptyTree(root->right);                         // delete right descendents
        delete root;                                    // delete root
    }
	return nullptr;
}

void printLessThan(Node* root, int k)                   // function to print all nodes with values less than k
{
    if (root->left != nullptr)                          // if left spot is not empty
    {
        printLessThan(root->left, k);
    }
    if (root->num < k)                                  // if node's num is less than k
    {
        std::cout << "This node has a value less than " << k << ": " << root->index << ", value = " << root->num << std::endl;
    }
    if (root->right != nullptr)                         // if the right spot is not empty
    {
        printLessThan(root->right, k);
    }
}

int printEqualTo(Node* root, int k, int total)          // function to find number of nodes with values equal to k
{
    if (root->left != nullptr)                          // if the left spot is not empty
    {
        total = printEqualTo(root->left, k, total);
    }
    if (root->num == k)                                 // if the node's value is equal to k, all 1 to total
    {
        total++;
    }
    if (root->right != nullptr)                         // if the right spot is not empty
    {
        total = printEqualTo(root->right, k, total);
    }

    return total;
}

int getSum(Node* root, int sum)                         // function to get the sum of the values of all of the nodes
{
    if (root->left != nullptr)                          // if the left spot is not empty
    {
        sum = getSum(root->left, sum);
    }

    sum += root->num;                                   // add the node's value to the sum

    if (root->right != nullptr)                         // if the right spot is not empty
    {
        sum = getSum(root->right, sum);
    }
    return sum;
}

int main()
{

    Node* root = new Node(0, 3);

    for (int i = 0; i < 20; i++)
    {
        addNode(root, i, rand()%6);
    }
    printNodes(root);

    printLessThan(root, 3);

    int total = printEqualTo(root, 3, 0);
    std::cout << "Total number of 3's: " << total << std::endl;

    int sum = getSum(root, 0);
    std::cout << "The sum is: " << sum << std::endl;

    emptyTree(root);

    return 0;
}
