
#include<iostream>
#include<string>
using namespace std;


class TreeNode
{
public:
    TreeNode(string name, float gpa)
    {
        this->name = name;
        this->gpa = gpa;
        this->left = nullptr;
        this->right = nullptr;
    }

    string name;
    float gpa;
    TreeNode *left;
    TreeNode *right;
};

void printInOrder(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->left != nullptr)
    {
        printInOrder(root->left);
    }
    cout << root->name << ": " << root->gpa << endl;

    if (root->right != nullptr)
    {
        printInOrder(root->right);
    }
}

void addNode(TreeNode *root, string name, float gpa)
{
    if (gpa < root->gpa)
    {
        if (root->left == nullptr)
        {
            root->left = new TreeNode(name, gpa);
        }
        else
        {
            addNode(root->left, name, gpa);
        }
    }
    else
    {
        if (root->right == nullptr)
        {
            root->right = new TreeNode(name, gpa);
        }
        else
        {
            addNode(root->right, name, gpa);
        }
    }
}


int main()
{
    string entered_name;
    float entered_gpa;

    TreeNode *root = nullptr;


    for (int i = 0; i < 10; i++)
    {
        cout << "\n\nPlease enter the name of the student (q for exit): ";
        cin >> entered_name;

        if (entered_name == "q")
        {
            break;
        }

        cout << "Please enter the GPA of the student: ";
        cin >> entered_gpa;

        if (root == nullptr)
        {
            root = new TreeNode(entered_name, entered_gpa);
        }
        else
        {
            addNode(root, entered_name, entered_gpa);
        }

        cout << "\n\nHere is the tree\n";
        cout << "=======================\n";
        printInOrder(root);
        cout << "---- end of tree ----";

    }

    cout << "Done\n";

    char exit;
    cin >> exit;
    return 0;
}
