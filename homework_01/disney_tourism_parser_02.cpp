#include <iostream>    // for cin, cout, etc
#include <fstream>     // for file handling
#include <string>      // for using strings
#include <cctype>      // for handling characters
#include <cstring>     // for handling strings and arrays

using namespace std;


class promotion_specs
{
public:
    promotion_specs ()
    {
        this->promotion = "";
        this->from = "";
        this->to = "";
        this->airline = "";
        this->flight_price = 0;
        this->number_of_nights = 0;
        this->price_per_night = 0;
    }

    promotion_specs (string promotion, string from, string to, string airline, int flight_price, int number_of_nights, int price_per_night)
    {
        this->promotion = promotion;
        this->from = from;
        this->to = to;
        this->airline = airline;
        this->flight_price = flight_price;
        this->number_of_nights = number_of_nights;
        this->price_per_night = price_per_night;
    }

    void set_promotion (string promotion)
    {
        this->promotion = promotion;
    }
    string get_promotion ()
    {
        return this->promotion;
    }

    void set_from (string from)
    {
        this->from = from;
    }
    string get_from ()
    {
        return this->from;
    }

    void set_to (string to)
    {
        this->to = to;
    }
    string get_to ()
    {
        return this->to;
    }

    void set_airline (string airline)
    {
        this->airline = airline;
    }
    string get_airline ()
    {
        return this->airline;
    }

    void set_flight_price (int flight_price)
    {
        this->flight_price = flight_price;
    }
    int get_flight_price ()
    {
        return this->flight_price;
    }

    void set_number_of_nights (int number_of_nights)
    {
        this->number_of_nights = number_of_nights;
    }
    int get_number_of_nights ()
    {
        return this->number_of_nights;
    }

    void set_price_per_night (int price_per_night)
    {
        this->price_per_night = price_per_night;
    }
    int get_price_per_night ()
    {
        return this->price_per_night;
    }

private:
    string promotion;
    string from;
    string to;
    string airline;
    int flight_price;
    int number_of_nights;
    int price_per_night;

};


int main()
{
    ifstream inFile;       // declare file to read from
    ofstream outFile;      // declare file to print to

    string inFileName = "tourism.txt";          // name of input file
    inFile.open(inFileName);                    // open input file

    if (!inFile)           // check if file was able to open
    {
        cout << "File not found: " << inFileName << endl;   // tell the user that the file does not exist
        return (2);
    }

    string outFileName = "tourism_output.txt";  // name of output file
    outFile.open(outFileName);                  // open output file

    string command;
    int numCommands;

    inFile >> command;
    numCommands = 1;

    bool first_promotion = false;

    int array_size = 1;
    promotion_specs array[1];
    promotion_specs new_array[2];

    while (command != "QUIT")
    {
        cout << endl << numCommands << " ) " << command << " - ";

        if (command == "ADD" || command == "CHANGE")
        {
            string promotion, from, to, airline;
            int flight_price, number_of_nights, price_per_night;
            inFile >> promotion;
            inFile >> from;
            inFile >> to;
            inFile >> airline;
            inFile >> flight_price;
            inFile >> number_of_nights;
            inFile >> price_per_night;

            outFile << promotion << " from " << from << " to " << to << ", ";
            outFile << "Airline: " << airline << ", $" << flight_price << ", ";
            outFile << "Nights: " << number_of_nights << ", ";
            outFile << "Price per night: $" << price_per_night << endl;

            if (command == "ADD")
            {
                if (first_promotion == false)
                {
                    array[0] = promotion_specs(promotion, from, to, airline, flight_price, number_of_nights, price_per_night);
                    first_promotion = true;
                }
                else
                {
                    for (int i = 0; i < array_size; i++)
                    {
                        new_array[i] = array[i];
                    }

                    new_array[array_size] = promotion_specs(promotion, from, to, airline, flight_price, number_of_nights, price_per_night);
                }

                // array_size += 1;
                // promotion_specs array[array_size];
                //
                // for (int i = 0; i < array_size; i++)
                // {
                //     array[i] = new_array[i];
                // }
                // promotion_specs new_array[array_size + 1];
            }
            else if (command == "CHANGE")
            {
                cout << "Changing " << promotion;
            }
        }
/*
        else if (command == "PRINT")
        {
            outFile << "PRINT" << endl;
            cout << "Printing ...";
        }

        else if (command == "PRINT_FROM")
        {
            string from;
            inFile >> from;
            outFile << "PRINT_FROM " << from << endl;
            cout << "Printing promotions originating from " << from;
        }

        else if (command == "PRINT_TO")
        {
            string to;
            inFile >> to;
            outFile << "PRINT_TO " << to << endl;
            cout << "Printing promotions arriving at " << to;
        }

        else if (command == "DELETE")
        {
            string promotion;
            inFile >> promotion;
            outFile << "DELETE " << promotion << endl;
            cout << "Deleting " << promotion;
        }

        else if (command == "PRINT_ON_BUDGET")
        {
            int budget;
            inFile >> budget;
            outFile << "PRINT_ON_BUDGET " << budget << endl;
            cout << "Printing promotions costing at most " << budget;
        }
*/
        else
        {
            cout << "Unknown command";
        }

        numCommands++;
        inFile >> command;
    }

    // cout << sizeof(array)/sizeof(*array);

    // for (int i = 0; i < sizeof(array)/sizeof(*array); i++)
    // {
        // cout << array[i].get_promotion();
    // }

    cout << endl;

    inFile.close();       // close the input file
    outFile.close();      // close the output file

    char exit;
    cin >> exit;

    return 0;
}
