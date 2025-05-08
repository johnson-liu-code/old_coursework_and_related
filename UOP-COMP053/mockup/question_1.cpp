#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
    Person()
    {
        this->name = "";
        this->age = 0;
        this->favorite_color = "";
        this->favorite_food = "";
        this->favorite_season = "";
        this->left = nullptr;
        this->right = nullptr;
    }
    Person(string name, int age, string favorite_color, string favorite_food, string favorite_season)
    {
        this->name = name;
        this->age = age;
        this->favorite_color = favorite_color;
        this->favorite_food = favorite_food;
        this->favorite_season = favorite_season;
        this->left = nullptr;
        this->right = nullptr;
    }

    void setValues()
    {
        this->name = "";
        this->age = 0;
        this->favorite_color = "";
        this->favorite_food = "";
        this->favorite_season = "";
        this->left = nullptr;
        this->right = nullptr;
    }

    void printValues()
    {
        cout << "Name: " << this->name << endl;
        cout << "Age: " << this->age << endl;
        cout << "Favorite color: " << this->favorite_color << endl;
        cout << "Favorite food: " << this->favorite_food << endl;
        cout << "Favorite season: " << this->favorite_season << endl << endl;
    }

    void set_name(string name)
    {
        this->name = name;
    }
    string get_name()
    {
        return this->name;
    }

    void set_age(int age)
    {
        this->age = age;
    }
    int get_age()
    {
        return this->age;
    }

    void set_color(string favorite_color)
    {
        this->favorite_color = favorite_color;
    }
    string get_color()
    {
        return this->favorite_color;
    }

    void set_food(string favorite_food)
    {
        this->favorite_food = favorite_food;
    }
    string get_food()
    {
        return this->favorite_food;
    }

    void set_season(string favorite_season)
    {
        this->favorite_season = favorite_season;
    }
    string get_season()
    {
        return this->favorite_season;
    }

    Person* left;
    Person* right;

private:
    string name;
    int age;
    string favorite_color;
    string favorite_food;
    string favorite_season;
};

void addPerson(Person* root, string name, int age, string favorite_color, string favorite_food, string favorite_season)
{
    if (age < root->get_age())
    {
        if (root->left == nullptr)
        {
            root->left = new Person(name, age, favorite_color, favorite_food, favorite_season);
        }
        else
        {
            addPerson(root->left, name, age, favorite_color, favorite_food, favorite_season);
        }
    }
    else
    {
        if (root->right == nullptr)
        {
            root->right = new Person(name, age, favorite_color, favorite_food, favorite_season);
        }
        else
        {
            addPerson(root->right, name, age, favorite_color, favorite_food, favorite_season);
        }
    }
}

Person* emptyTree(Person* root)
{
    if (root != nullptr)
    {
        emptyTree(root->left);
        emptyTree(root->right);
        delete root;
    }
    return nullptr;
}

void olderThan18(Person* root)
{
    if (root == nullptr)
    {
        return;
    }
    if (root->left != nullptr)
    {
        olderThan18(root->left);
    }

    if (root->get_age() > 18)
    {
        cout << "This person is older than 18:" << endl;
        root->printValues();
    }

    if (root->right != nullptr)
    {
        olderThan18(root->right);
    }
}


int main()
{
    Person* root = new Person("Person1", 25, "Black", "Ice cream", "Fall");
    addPerson(root, "Person2", 18, "White", "Noodles", "Winter");
    addPerson(root, "Person3", 20, "Red", "Eggs", "Winter");
    addPerson(root, "Person4", 12, "Blue", "Salad", "Fall");
    addPerson(root, "Person5", 16, "Purple", "McDonalds", "Summer");
    addPerson(root, "Person6", 22, "Green", "Fruits", "Summer");
    addPerson(root, "Person7", 24, "Grey", "Vegetables", "Spring");
    addPerson(root, "Person8", 14, "Cyan", "Meat", "Winter");

    olderThan18(root);

    emptyTree(root);


    return 0;
}
