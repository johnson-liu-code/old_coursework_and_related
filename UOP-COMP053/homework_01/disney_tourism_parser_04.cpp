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

    int get_total_price ()
    {
        return flight_price + number_of_nights * price_per_night;
    }

private:
    string promotion;
    string from;
    string to;
    string airline;
    int flight_price;
    int number_of_nights;
    int price_per_night;
    int total_price;

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

    inFile >> command;
    int numCommands = 1;

    bool first_promotion = true;
    int number_of_blocks = 100;

    promotion_specs promotion_list[number_of_blocks];
    bool activation_list[number_of_blocks];
    for (int i = 0; i < number_of_blocks; i++)
    {
        activation_list[i] = false;
    }

    bool quit = false;

    while (quit == false)
    {
        // cout << endl << numCommands << " ) " << command << " - ";

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

            if (command == "ADD")
            {
                bool found_empty_spot = false;
                int loc = 0;
                while (found_empty_spot == false)
                {
                    // cout << loc << endl;
                    // cout << "found_empty_spot: " << found_empty_spot << endl;
                    if (activation_list[loc] == false)
                    {
                        // cout << "hello" << endl;
                        found_empty_spot = true;
                        // cout << "found_empty_spot: " << found_empty_spot << endl;
                        cout << "Adding " << promotion << endl;
                        promotion_list[loc] = promotion_specs(promotion, from, to, airline, flight_price, number_of_nights, price_per_night);
                        activation_list[loc] = true;

                        outFile << "ADD " << promotion << " from " << from << " to " << to << ", ";
                    }
                    else
                    {
                        // cout << "else" << endl;
                        loc++;
                    }
                };

            }
            else if (command == "CHANGE")
            {
                cout << "Changing " << promotion << endl;
                bool found_promotion = false;
                int loc = 0;
                while (found_promotion == false)
                {
                    if (promotion_list[loc].get_promotion() == promotion)
                    {
                        promotion_list[loc] = promotion_specs(promotion, from, to, airline, flight_price, number_of_nights, price_per_night);
                        found_promotion = true;
                        outFile << "CHANGE " << promotion << " from " << from << " to " << to << ", ";
                    }
                    else
                    {
                        loc++;
                    }
                };
            }
            outFile << "Airline: " << airline << ", $" << flight_price << ", ";
            outFile << "Nights: " << number_of_nights << ", ";
            outFile << "Price per night: $" << price_per_night << endl;
        }

        else if (command == "PRINT")
        {
            cout << "Printing ..." << endl;
            outFile << "PRINT" << endl;

            for (int i = 0; i < number_of_blocks; i++)
            {
                if (promotion_list[i].get_promotion() != "")
                {
                    outFile << promotion_list[i].get_promotion();
                    outFile << " from " << promotion_list[i].get_from();
                    outFile << " to " << promotion_list[i].get_to() << ", ";
                    outFile << "Airline: " << promotion_list[i].get_airline();
                    outFile << ", $" << promotion_list[i].get_flight_price() << ", ";
                    outFile << "Nights: " << promotion_list[i].get_number_of_nights() << ", ";
                    outFile << "Price per night: $" << promotion_list[i].get_price_per_night() << endl;
                }
            }
        }

        else if (command == "PRINT_FROM")
        {
            string from;
            inFile >> from;
            outFile << "PRINT_FROM " << from << endl;
            for (int i = 0; i < number_of_blocks; i++)
            {
                if (promotion_list[i].get_from() == from)
                {
                    outFile << promotion_list[i].get_promotion();
                    outFile << " from " << promotion_list[i].get_from();
                    outFile << " to " << promotion_list[i].get_to() << ", ";
                    outFile << "Airline: " << promotion_list[i].get_airline();
                    outFile << ", $" << promotion_list[i].get_flight_price() << ", ";
                    outFile << "Nights: " << promotion_list[i].get_number_of_nights() << ", ";
                    outFile << "Price per night: $" << promotion_list[i].get_price_per_night() << endl;
                }
            }
            cout << "Printing promotions originating from " << from << endl;
        }

        else if (command == "PRINT_TO")
        {
            string to;
            inFile >> to;
            outFile << "PRINT_TO " << to << endl;
            for (int i = 0; i < number_of_blocks; i++)
            {
                if (promotion_list[i].get_to() == to)
                {
                    outFile << promotion_list[i].get_promotion();
                    outFile << " from " << promotion_list[i].get_from();
                    outFile << " to " << promotion_list[i].get_to() << ", ";
                    outFile << "Airline: " << promotion_list[i].get_airline();
                    outFile << ", $" << promotion_list[i].get_flight_price() << ", ";
                    outFile << "Nights: " << promotion_list[i].get_number_of_nights() << ", ";
                    outFile << "Price per night: $" << promotion_list[i].get_price_per_night() << endl;
                }
            }
            cout << "Printing promotions arriving at " << to << endl;
        }

        else if (command == "DELETE")
        {
            string promotion;
            inFile >> promotion;
            outFile << "DELETE " << promotion << endl;
            for (int i = 0; i < number_of_blocks; i++)
            {
                if (promotion_list[i].get_promotion() == promotion)
                {
                    promotion_list[i] = promotion_specs();
                }
            }
            cout << "Deleting " << promotion << endl;
        }

        else if (command == "PRINT_ON_BUDGET")
        {
            int budget;
            inFile >> budget;
            outFile << "PRINT_ON_BUDGET " << budget << endl;
            for (int i = 0; i < number_of_blocks; i++)
            {
                if (promotion_list[i].get_total_price() <= budget && promotion_list[i].get_total_price() > 0)
                {
                    outFile << promotion_list[i].get_promotion();
                    outFile << " from " << promotion_list[i].get_from();
                    outFile << " to " << promotion_list[i].get_to() << ", ";
                    outFile << "Airline: " << promotion_list[i].get_airline();
                    outFile << ", $" << promotion_list[i].get_flight_price() << ", ";
                    outFile << "Nights: " << promotion_list[i].get_number_of_nights() << ", ";
                    outFile << "Price per night: $" << promotion_list[i].get_price_per_night() << ", ";
                    outFile << "Total price: " << promotion_list[i].get_total_price() << endl;
                }
            }
            cout << "Printing promotions costing at most " << budget << endl;
        }

        else if (command == "QUIT")
        {
            quit = true;
            cout << "Quiting ..." << endl;
            outFile << "QUIT" << endl;
        }

        else
        {
            cout << "Unknown command" << endl;
        }
        numCommands++;
        inFile >> command;
    };


    cout << endl;

    inFile.close();       // close the input file
    outFile.close();      // close the output file

    char exit;
    cin >> exit;

    return 0;
}
