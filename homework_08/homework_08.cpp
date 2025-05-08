#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>

class Node
{
public:
    Node(int race_time, std::string name)
    {
        this->race_time = race_time;
        this->name = name;
        this->left = nullptr;
        this->right = nullptr;
    }

    int race_time;
    std::string name;
    Node* left;
    Node* right;
};

void addNode(Node* root, int race_time, std::string name)
{
    if (race_time < root->race_time)
    {
        if (root->left == nullptr)
        {
            root->left = new Node(race_time, name);
        }
        else
        {
            addNode(root->left, race_time, name);
        }
    }
    else
    {
        if (root->right == nullptr)
        {
            root->right = new Node(race_time, name);
        }
        else
        {
            addNode(root->right, race_time, name);
        }
    }
}

Node* emptyTree(Node* root)
{
    if (root != nullptr)
    {
        emptyTree(root->left);
        emptyTree(root->right);
        delete root;
    }
    return nullptr;
}

void printNodes(Node* root)
{
    if (root == nullptr)
    {
        return;
    }
    if (root->left != nullptr)
    {
        printNodes(root->left);
    }
    std::cout << "Racer " << root->name << " has a race time of " << root->race_time << std::endl;
    if (root->right != nullptr)
    {
        printNodes(root->right);
    }
}

Node* getMinimum(Node* root)
{
    if ( (root == nullptr) || (root->left == nullptr) )
    {
        return root;
    }
    return getMinimum(root->left);
}

Node* getMaximum(Node* root)
{
    if ( (root == nullptr) || (root->right == nullptr) )
    {
        return root;
    }
    return getMaximum(root->right);
}

Node* deleteNode(Node* root, int race_time)
{
    if (root == nullptr)
    {
        return root;
    }

    if (race_time < root->race_time)
    {
        root->left = deleteNode(root->left, race_time);
    }
    else if (race_time > root->race_time)
    {
        root->right = deleteNode(root->right, race_time);
    }
    else
    {
        if (root->left == nullptr)
        {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = getMinimum(root->right);
        root->race_time = temp->race_time;
        root->name = temp->name;
        root->right = deleteNode(root->right, temp->race_time);
    }

    return root;
}

void findPreSuc(Node* root, Node*& pre, Node*& suc, int race_time)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->race_time == race_time)
    {
        if (root->left != nullptr)
        {
            pre = getMaximum(root->left);
        }
        if (root->right != nullptr)
        {
            suc = getMinimum(root->right);
        }

        return;
    }

    if (root->race_time > race_time)
    {
        suc = root;
        findPreSuc(root->left, pre, suc, race_time);
    }
    else
    {
        pre = root;
        findPreSuc(root->left, pre, suc, race_time);
    }
}

void printBestFive(Node* root)
{
    Node* pre;
    Node* suc;
    Node* first_node = getMinimum(root);
    findPreSuc(root, pre, suc, first_node->race_time);
    Node* second_node = suc;
    findPreSuc(root, pre, suc, second_node->race_time);
    Node* third_node = suc;
    findPreSuc(root, pre, suc, third_node->race_time);
    Node* fourth_node = suc;
    findPreSuc(root, pre, suc, fourth_node->race_time);
    Node* fifth_node = suc;

    std::cout << "The best five racers are ..." << std::endl;
    std::cout << first_node->name << " with a race time of " << first_node->race_time << std::endl;
    std::cout << second_node->name << " with a race time of " << second_node->race_time << std::endl;
    std::cout << third_node->name << " with a race time of " << third_node->race_time << std::endl;
    std::cout << fourth_node->name << " with a race time of " << fourth_node->race_time << std::endl;
    std::cout << fifth_node->name << " with a race time of " << fifth_node->race_time << std::endl;

}

// int printBestFive(Node* root, int count)
// {
//     if ( (root == nullptr) || (count > 5))
//     {
//         return count;
//     }
//
//     std::cout << count << std::endl;
//
//     count = printBestFive(root->left, count);
//     count = printBestFive(root->left, count);
//
//     return count;
// }

// int printBestFive(Node* root, int count)
// {
//     if ( (root == nullptr) || (count > 5) )
//     {
//         return count;
//     }
//     std::cout << "hello" << endl;
//     count++;
//     count = printBestFive(root->right, count);
//     count = printBestFive(root->left, count);
//
//     return count;
// }

// void printBestFive(Node* root)
// {
//     int first = 0, second = 0, third = 0, fourth = 0, fifth = 0;
//
//     if (root == nullptr)
//     {
//         return;
//     }
//
//     if (root->race_time > first)
//     {
//         third = second;
//         second = first;
//         first = root->race_time;
//     }
//
//
// }


int main()
{

    std::ifstream infile;
    std::string infile_name = "meet.txt";
    infile.open(infile_name);

    std::ofstream outfile;
    std::string outfile_name = "output.txt";
    outfile.open(outfile_name);

    bool quit = false;
    std::string command;
    infile >> command;

    std::string name;
    int race_time;

    Node* root = nullptr;

    while (quit == false)
    {
        if (command == "ADD")
        {
            infile >> name;
            infile >> race_time;

            std::cout << "Adding racer " << name << " with a race time of " << race_time << "..." << std::endl;
            outfile << "Adding racer " << name << " with a race time of " << race_time << "..." << std::endl;

            if (root == nullptr)
            {
                root = new Node(race_time, name);
            }
            else
            {
                addNode(root, race_time, name);
            }
        }
        else if (command == "DELETE")
        {
            infile >> name;
            infile >> race_time;

            std::cout << "Deleting racer " << name << std::endl;
            outfile << "Deleting racer " << name << std::endl;

            deleteNode(root, race_time);
        }

        else if (command == "BEST")
        {
            std::cout << "Printing the top racers ... " << std::endl;
            outfile << "Printing the top racers ... " << std::endl;

            printBestFive(root);
        }

        infile >> command;

        if (command == "QUIT")
        {
            std::cout << "Quiting ... " << std::endl;
            outfile << "Quiting ... " << std::endl;

            quit = true;
        }

    }

    emptyTree(root);

    infile.close();
    outfile.close();

    char exit;
    std::cin >> exit;

    return 0;
}
