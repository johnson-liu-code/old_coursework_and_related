#include<iostream>
#include<fstream>
#include<string>


class MansionRental
{
public:
    // Constructor
    MansionRental()
    {
        this->rentalID = 0;
        this->start_week = "";
        this->end_week = "";
        this->next_rental = nullptr;
    }
    // Overload Constructor
    MansionRental(int rentalID, std::string start_week, std::string end_week, MansionRental* next_rental)
    {
        this->rentalID = rentalID;
        this->start_week = start_week;
        this->end_week = end_week;
        this->next_rental = next_rental;
    }

    // Print info
    void printMe()
    {
        std::cout << "              #####################################" << std::endl;
        std::cout << "              ### Printing info for rental " << this->rentalID << " ###" << std::endl;
        std::cout << "              Year       of rental: " << this->start_week[0] << this->start_week[1] << this->start_week[2] << this->start_week[3] << std::endl;
        std::cout << "              Month      of rental: " << this->start_week[4] << this->start_week[5] << std::endl;
        std::cout << "              Start week of rental: " << this->start_week[4] << this->start_week[5] << "..." << this->start_week[6] << std::endl;
        std::cout << "              End   week of rental: " << this->end_week[4] << this->end_week[5] << "..." << this->end_week[6] << std::endl;
        std::cout << std::endl;
    }

    // Setters and getters
    void setID(int rentalID)
    {
        this->rentalID = rentalID;
    }
    int getID()
    {
        return this->rentalID;
    }
    void setStartWeek(std::string start_week)
    {
        this->start_week = start_week;
    }
    std::string getStartWeek()
    {
        return this->start_week;
    }
    void setEndWeek(std::string end_week)
    {
        this->end_week = end_week;
    }
    std::string getEndWeek()
    {
        return this->end_week;
    }
    void setNext(MansionRental* next_rental)
    {
        this->next_rental = next_rental;
    }
    MansionRental* getNext()
    {
        return this->next_rental;
    }
private:
    // Private members
    int rentalID;
    std::string start_week, end_week;
    MansionRental* next_rental;
};

class Mansion
{
public:
    // Constructor
    Mansion()
    {
        this->rental_length = 0;
        this->first_rental = nullptr;
        this->mansionID = 0;
        this->next_mansion = nullptr;
    }

    // Destructor
    ~Mansion();

    // Various functions
    bool CheckValidRental(int rentalID, std::string start_week, std::string end_week);
    void AddRental(int rentalID, std::string start_week, std::string end_week);
    void CheckAvailability(int rentalID, std::string check_week);
    void PrintRentalInWeek(std::string check_week);
    void DeleteRental(int rentalID);
    void DeleteAllRentals();

    // Print all rentals for a mansion
    void PrintList();

    // Setters and getters
    void setID(int mansionID)
    {
        this->mansionID = mansionID;
    }
    int getID()
    {
        return this->mansionID;
    }
    void setNext(Mansion* next_mansion)
    {
        this->next_mansion = next_mansion;
    }
    Mansion* getNext()
    {
        return this->next_mansion;
    }

private:
    // Private members
    int mansionID, rental_length;
    MansionRental* first_rental;
    Mansion* next_mansion;
};
// Destructor
Mansion::~Mansion()
{
    MansionRental* tempPrt;
    while(first_rental != nullptr)
    {
        tempPrt = first_rental;
        first_rental = first_rental->getNext();
        delete tempPrt;
    }
}
// Check if a rental is valid given the dates of the current rentals
bool Mansion::CheckValidRental(int rentalID, std::string start_week, std::string end_week)
{
    bool valid = true;
    MansionRental* current = first_rental;
    if(rental_length == 0)
    {
        return valid;
    }
    else
    {
        std::string present_start_week;
        std::string present_end_week;
        while( current != nullptr)
        {
            // std::cout << "hello" << std::endl;
            present_start_week = current->getStartWeek();
            present_end_week = current->getEndWeek();
            if( ((start_week >= present_start_week) && (start_week <= present_end_week)) || ((end_week >= present_end_week) && (end_week <= present_end_week)) )
            {
                valid = false;
                std::cout << "This mansion (" << mansionID << ") cannot be rented (" << rentalID << ") at this particular time frame ... : Start(" << start_week << ") End(" << end_week << ")" << std::endl << std::endl;
            }
            current = current->getNext();
        }
        return valid;
    }
}
// Add a rental to a mansion
void Mansion::AddRental(int rentalID, std::string start_week, std::string end_week)
{
    bool valid = CheckValidRental(rentalID, start_week, end_week);
    // std::cout << valid << std::endl;
    // bool valid = true;
    if(valid == true)
    {
        MansionRental* newNode = new MansionRental();
        newNode->setID(rentalID);
        newNode->setStartWeek(start_week);
        newNode->setEndWeek(end_week);

        if( first_rental == nullptr || first_rental->getID() >= newNode->getID() )
        {
            newNode->setNext(first_rental);
            first_rental = newNode;

        }
        else
        {
            MansionRental* current = first_rental;
            while( current->getNext() != nullptr && current->getNext()->getID() < newNode->getID() )
            {
                current = current->getNext();
            }
            newNode->setNext(current->getNext());
            current->setNext(newNode);
        }
        rental_length++;
    }
}
// Check if a mansion is available during a certain week
void Mansion::CheckAvailability(int rentalID, std::string check_week)
{
    MansionRental* current = first_rental;
    bool available = true;
    {
        std::string present_start_week;
        std::string present_end_week;
        while( current != nullptr)
        {
            present_start_week = current->getStartWeek();
            present_end_week = current->getEndWeek();
            if( ( (check_week >= present_start_week) && (check_week <= present_end_week) )  )
            {
                available = false;
                std::cout << "RENT_ID (" << rentalID << "): This mansion (" << mansionID << ") is not available the week of " << check_week << std::endl << std::endl;
            }
            current = current->getNext();
        }
    }
    if(available)
    {
        std::cout << "RENT_ID (" << rentalID << "): This mansion (" << mansionID << ") is available the week of " << check_week << std::endl << std::endl;
    }
}
// Print all rentals for a mansion during a certain week
void Mansion::PrintRentalInWeek(std::string check_week)
{
    MansionRental* current = first_rental;
    bool found_a_rental = false;
    std::string present_start_week;
    std::string present_end_week;
    int currentID;
    while( current != nullptr)
    {
        present_start_week = current->getStartWeek();
        present_end_week = current->getEndWeek();
        if( check_week == present_start_week )
        {
            currentID = current->getID();
            std::cout << "There is a rental (" << currentID << ") in the week of " << check_week << std::endl << std::endl;
            found_a_rental = true;
        }
        current = current->getNext();
    }
    if(found_a_rental == false)
    {
        std::cout << "No rentals found in the week of " << check_week << std::endl << std::endl;
    }
}
// Delete a rental for a mansion
void Mansion::DeleteRental(int rentalID)
{
    MansionRental* current = first_rental;
    MansionRental* temp_location;
    if(first_rental->getID() == rentalID)
    {
        temp_location = current;
        first_rental = first_rental->getNext();
    }
    else
    {
        while(current->getNext()->getID() != rentalID)
        {
            current = current->getNext();
        }
        temp_location = current->getNext();
        current->setNext(current->getNext()->getNext());
    }
    delete temp_location;
    rental_length--;
}
// Delete all rentals for a mansion
void Mansion::DeleteAllRentals()
{
    MansionRental* tempPrt;
    while(first_rental != nullptr)
    {
        tempPrt = first_rental;
        first_rental = first_rental->getNext();
        delete tempPrt;
    }
}
// Print all rentals for a mansion
void Mansion::PrintList()
{
    MansionRental* current = first_rental;

    std::cout << "#############################################################" << std::endl;
    std::cout << "Printing info for mansion " << this->mansionID << std::endl;

    while(current != nullptr)
    {
        current->printMe();
        current = current->getNext();
    }
}

class SortedListLinked
{
public:
    // Various functions
    SortedListLinked();
    ~SortedListLinked();
    void AddMansion(int mansionID);
    Mansion* GetMansion(int mansionID);
    void PrintRentalsInWeek(std::string check_week);

    void PrintList();

private:
    // Private members
    int mansion_length;
    Mansion* first_mansion;
};
// Constructor
SortedListLinked::SortedListLinked()
{
    mansion_length = 0;
    first_mansion = nullptr;
}
// Destructor.
SortedListLinked::~SortedListLinked()
{
    Mansion* tempPrt;
    while(first_mansion != nullptr)
    {
        first_mansion->DeleteAllRentals();
        tempPrt = first_mansion;
        first_mansion = first_mansion->getNext();
        delete tempPrt;
    }
}
// Add a mansion to the list
void SortedListLinked::AddMansion(int mansionID)
{
    Mansion* newNode = new Mansion();
    newNode->setID(mansionID);

    if( first_mansion == nullptr || first_mansion->getID() >= newNode->getID() )
    {
        newNode->setNext(first_mansion);
        first_mansion = newNode;
    }
    else
    {
        Mansion* current = first_mansion;
        while( current->getNext() != nullptr && current->getNext()->getID() < newNode->getID() )
        {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }
    mansion_length++;
}
// Retrieve a mansion from the list
Mansion* SortedListLinked::GetMansion(int mansionID)
{
    int current = first_mansion->getID();
    Mansion* next_mansion = first_mansion->getNext();
    if(current == mansionID)
    {
        return first_mansion;
    }
    while(current != mansionID)
    {
        current = next_mansion->getID();
        if(current == mansionID)
        {
            return next_mansion;
        }
        next_mansion = next_mansion->getNext();
    }
}
// Print all rentals in a certain week for all mansions
void SortedListLinked::PrintRentalsInWeek(std::string check_week)
{
    Mansion* current_mansion = first_mansion;
    while(current_mansion != nullptr)
    {
        current_mansion->PrintRentalInWeek(check_week);
        current_mansion = current_mansion->getNext();
    }
}
// Print all rentals across all mansions
void SortedListLinked::PrintList()
{
    std::cout << "**************************************************************************" << std::endl;
    std::cout << "Printing all rentals in every mansion ... " << std::endl;
    std::cout << "**************************************************************************" << std::endl;

    Mansion* current = first_mansion;
    while(current != nullptr)
    {
        current->PrintList();
        current = current->getNext();
    }
}

int main()
{
    // Open input file
    std::ifstream inFile;
    std::string inFileName = "input.txt";
    inFile.open(inFileName);

    if (!inFile)
    {
        std::cout << "File not found: " << inFileName << std::endl;
    }

    // Open output file
    std::ofstream outFile;
    std::string outFileName = "output.txt";
    outFile.open(outFileName);

    bool quit = false;
    std::string command;
    inFile >> command;

    SortedListLinked mansions;
    int mansionID;
    int rentalID;
    std::string check_week;

    // Read input file and write to screen and output file
    while(quit == false)
    {
        if(command == "ADD_MANSION")
        {
            inFile >> mansionID;
            std::cout << "Adding mansion (" << mansionID << ") ... " << std::endl << std::endl;
            outFile << "Adding mansion (" << mansionID << ") ... " << std::endl << std::endl;
            mansions.AddMansion(mansionID);
        }
        else if(command == "ADD_RENTAL")
        {
            std::string start_week;
            std::string end_week;
            inFile >> mansionID;
            inFile >> rentalID;
            inFile >> start_week;
            inFile >> end_week;
            std::cout << "Adding rental (" << rentalID << ") ... " << std::endl << std::endl;
            outFile << "Adding rental (" << rentalID << ") ... " << std::endl << std::endl;
            mansions.GetMansion(mansionID)->AddRental(rentalID, start_week, end_week);
        }
        else if(command == "DELETE_RENTAL")
        {
            inFile >> mansionID;
            inFile >> rentalID;
            std::cout << "Deleting rental (" << rentalID << ") ... " << std::endl << std::endl;
            outFile << "Deleting rental (" << rentalID << ") ... " << std::endl << std::endl;
            mansions.GetMansion(mansionID)->DeleteRental(rentalID);
        }
        else if(command == "CHECK_AVAILABILITY")
        {
            inFile >> mansionID;
            inFile >> rentalID;
            inFile >> check_week;
            std::cout << "Checking availability of mansion (" << mansionID << ") for the week of " << check_week << std::endl;
            outFile << "Checking availability of mansion (" << mansionID << ") for the week of " << check_week << std::endl;
            mansions.GetMansion(mansionID)->CheckAvailability(rentalID, check_week);
        }
        else if(command == "PRINT_RENTALS_IN_WEEK")
        {
            inFile >> check_week;
            std::cout << "Printing all rentals for the week of " << check_week << std::endl;
            outFile << "Printing all rentals for the week of " << check_week << std::endl;
            mansions.PrintRentalsInWeek(check_week);
        }
        else if(command == "PRINT_RENTALS_FOR_MANSION")
        {
            inFile >> mansionID;
            std::cout << "Printing all rentals for mansion (" << mansionID << ") ... " << std::endl;
            outFile << "Printing all rentals for mansion (" << mansionID << ") ... " << std::endl;
            mansions.GetMansion(mansionID)->PrintList();
        }
        else if(command == "PRINT_ALL_RENTALS")
        {
            std::cout << "Printing all rentals ... (BONUS) " << std::endl;
            outFile << "Printing all rentals ... (BONUS) " << std::endl;
            mansions.PrintList();
        }

        else if(command == "QUIT")
        {
            quit = true;
            std::cout << "#####################################################################" << std::endl;
            std::cout << "Quiting ..." << std::endl;
            outFile << "Quiting ..." << std::endl;
        }
        inFile >> command;
    }

    // mansions.AddMansion(1000);
    // mansions.GetMansion(1000)->AddRental(1001, "2019041", "2019042");
    // mansions.GetMansion(1000)->AddRental(1002, "2019051", "2019053");
    // mansions.GetMansion(1000)->AddRental(1003, "2019011", "2019012");
    // mansions.GetMansion(1000)->AddRental(1004, "2019061", "2019062");
    // mansions.AddMansion(2000);
    // mansions.GetMansion(2000)->AddRental(2001, "2019041", "2019042");
    //
    // mansions.GetMansion(1000)->DeleteRental(1003);
    // mansions.GetMansion(1000)->DeleteRental(1002);
    //
    // mansions.GetMansion(1000)->CheckAvailability(1010, "2019012");
    //
    // mansions.GetMansion(1000)->AddRental(1006, "2019041", "2019042");
    // mansions.GetMansion(1000)->AddRental(1007, "2019121", "2019122");
    //
    // mansions.PrintRentalsInWeek("2019041");
    //
    // mansions.GetMansion(1000)->DeleteRental(1001);
    //
    // mansions.GetMansion(1000)->PrintList();
    //
    // mansions.PrintList();
    //
    // mansions.AddMansion(3000);
    // mansions.GetMansion(3000)->AddRental(3001, "2019091", "2019094");
    // mansions.GetMansion(3000)->AddRental(3002, "2019021", "2019034");
    // mansions.GetMansion(3000)->AddRental(3003, "2019011", "2019014");
    //
    // mansions.GetMansion(3000)->DeleteRental(3001);
    //
    // mansions.PrintList();

    mansions.~SortedListLinked();

    return 0;
}
