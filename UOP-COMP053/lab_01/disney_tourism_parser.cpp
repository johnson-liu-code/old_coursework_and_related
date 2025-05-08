#include <iostream>    // for cin, cout, etc
#include <fstream>     // for file handling
#include <string>      // for using strings
#include <cctype>      // for handling characters
#include <cstring>     // for handling strings and arrays

using namespace std;



int main()
{
    char exit;

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

            outFile << promotion << " from " << from << " to " << to;
            outFile << ", Airline: " << airline << ", $" << flight_price;
            outFile << ", Nights: " << number_of_nights;
            outFile << ", Price per night: $" << price_per_night << endl;

            if (command == "ADD")
            {
                cout << "Adding " << promotion;
            }
            else if (command == "CHANGE")
            {
                cout << "Changing " << promotion;
            }
        }

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

        else
        {
            cout << "Unknown command";
        }

        numCommands++;
        inFile >> command;
    };

    cout << endl << numCommands + 1 << " ) QUIT - Quiting..." << endl;
    cout << endl;

    outFile << "QUIT";

    inFile.close();       // close the input file
    outFile.close();      // close the output file

    cin >> exit;

    return 0;
}
