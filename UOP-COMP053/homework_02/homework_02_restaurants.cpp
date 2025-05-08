#include <iostream>    // for cin, cout, etc
#include <fstream>     // for file handling
#include <string>      // for using strings
#include <cctype>      // for handling characters
#include <cstring>     // for handling strings and arrays

using namespace std;


class restaurant
{
public:
    restaurant()
    {
        this->rest_id = "";
        this->name = "";
        this->specialty = "";
        this->open = "";
        this->close = "";
        this->num_of_tables = 0;
    }
    restaurant(string rest_id, string name, string specialty, string open, string close, int num_of_tables)
    {
        this->rest_id = rest_id;
        this->name = name;
        this->specialty = specialty;
        this->open = open;
        this->close = close;
        this->num_of_tables = num_of_tables;
    }

    void set_rest_id(string rest_id)
    {
        this->rest_id = rest_id;
    }
    string get_rest_id()
    {
        return this->rest_id;
    }
    void set_name(string name)
    {
        this->name = name;
    }
    string get_name()
    {
        return this->name;
    }
    void set_specialty(string specialty)
    {
        this->specialty = specialty;
    }
    string get_specialty()
    {
        return this->specialty;
    }
    void set_open(string open)
    {
        this->open = open;
    }
    string get_open()
    {
        return this->open;
    }
    void set_close(string close)
    {
        this->close = close;
    }
    string get_close()
    {
        return this->close;
    }
    void set_num_of_tables(int num_of_tables)
    {
        this->num_of_tables = num_of_tables;
    }
    int get_num_of_tables()
    {
        return this->num_of_tables;
    }

    void print_me()
    {
        cout << endl << "---------------------------------------------" << endl;
        cout << "Restaurant ID: " << rest_id << endl;
        cout << "Restaurant name: " << name << endl;
        cout << "Restaurant specialty: " << specialty << endl;
        cout << "Open time: " << open << endl;
        cout << "Closing time: " << close << endl;
        cout << "Number of tables: " << num_of_tables << endl;
        cout << "---------------------------------------------" << endl;
    }

private:
    string rest_id;
    string name;
    string specialty;
    string open;
    string close;
    int num_of_tables;
};

int main()
{
    ifstream inFile;

    string inFileName = "input_file.txt";
    // string inFileName = "../homework_01/tourism.txt";
    inFile.open(inFileName);

    if (!inFile)
    {
        cout << "File not found: " << inFileName << endl;
    }

    int num_blocks = 100;
    restaurant *restaurant_array[num_blocks];

    for (int i = 0; i < num_blocks; i++)
    {
        restaurant_array[i] = nullptr;
    }

    string command;

    inFile >> command;
    int numCommands = 1;
    bool quit = false;

    while(quit == false)
    {
        cout << numCommands << " ) " << command << " - ";

        string rest_id, name, specialty, open, close;
        int num_of_tables;

        if(command == "ADD" || command == "CHANGE")
        {
            inFile >> rest_id;
            inFile >> name;
            inFile >> specialty;
            inFile >> open;
            inFile >> close;
            inFile >> num_of_tables;

            cout << rest_id << endl;

            if(command == "ADD")
            {
                for(int i = 0; i < num_blocks; i++)
                {
                    if(restaurant_array[i] == nullptr)
                    {
                        restaurant_array[i] = new restaurant(rest_id, name, specialty, open, close, num_of_tables);
                        break;
                    }
                }
            }
            else if(command == "CHANGE")
            {
                for(int i = 0; i < num_blocks; i++)
                {
                    if(restaurant_array[i] != nullptr && restaurant_array[i]->get_rest_id() == rest_id)
                    {
                        restaurant_array[i] = new restaurant(rest_id, name, specialty, open, close, num_of_tables);
                        break;
                    }
                }
            }
        }

        else if(command == "REMOVE")
        {
            inFile >> rest_id;
            cout << rest_id << endl;

            for(int i = 0; i < num_blocks; i++)
            {
                if(restaurant_array[i] != nullptr && restaurant_array[i]->get_rest_id() == rest_id)
                {
                    delete restaurant_array[i];
                    restaurant_array[i] = nullptr;
                }
            }
        }

        else if(command == "SEARCH")
        {
            inFile >> rest_id;
            cout << rest_id;

            bool found = false;

            for(int i = 0; i < num_blocks; i++)
            {
                if(restaurant_array[i] != nullptr && restaurant_array[i]->get_rest_id() == rest_id)
                {
                    found = true;
                    restaurant_array[i]->print_me();
                }
            }

            if(found == false)
            {
                cout << "NULL" << endl;
            }
        }

        else if(command == "PRINT")
        {
            for(int i = 0; i < num_blocks; i++)
            {
                if(restaurant_array[i] != nullptr)
                {
                    restaurant_array[i]->print_me();
                }
            }
        }

        else if(command == "QUIT")
        {
            quit = true;
        }

        numCommands++;
        inFile >> command;

    }

    for (int i = 0; i < num_blocks; i++)
    {
        delete restaurant_array[i];
    }

    char exit;
    cin >> exit;

    return 0;
}
