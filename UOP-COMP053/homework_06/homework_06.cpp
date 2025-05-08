#include<iostream>
#include<fstream>
#include<string>


// Luggage contains a name that can be set and retrieve.
class luggage
{
public:
    luggage()
    {
        this->owner = "";
    }
    luggage(std::string owner)
    {
        this->owner = owner;
    }

    void set_owner(std::string owner)
    {
        this->owner = owner;
    }
    std::string get_owner()
    {
        return this->owner;
    }
private:
    std::string owner;
};
// Class for an stack.
class gate
{
public:
    gate()
    {
        this->length = 0;
    }
    void SetLength(int length)
    {
        this->length = length;
    }
    void Push(std::string owner);
    std::string Pop();
    void Top(int gate_number);
private:
    int length;
    luggage stack[100];
};
// Add an item to the stack.
void gate::Push(std::string owner)
{
    stack[length] = luggage(owner);
    length++;
}
// Remove the top item from the stack.
std::string gate::Pop()
{
    std::string name;
    name = stack[length-1].get_owner();
    stack[length] = luggage();
    length--;
    return name;
}
// Print the top item of the stack.
void gate::Top(int gate_number)
{
    std::cout << "The top luggage of this GATE " << gate_number << " belongs to " << stack[length-1].get_owner() << std::endl;
}
// Class for stack.
class plane
{
public:
    plane()
    {
        this->length = 0;
    }
    void SetLength(int length)
    {
        this->length = length;
    }
    void Push(std::string owner);
    std::string Pop();
    void Top(int plane_number);
private:
    int length;
    luggage stack[100];
};// Add an item to the stack.

// Add an item to the stack.
void plane::Push(std::string owner)
{
    stack[length] = luggage(owner);
    length++;
}
// Remove the top item from the stack.
std::string plane::Pop()
{
    std::string name;
    name = stack[length-1].get_owner();
    stack[length] = luggage();
    length--;
    return name;
}
// Print the top item of the stack.
void plane::Top(int plane_number)
{
    std::cout << "The top luggage of this plane " << plane_number << " belongs to " << stack[length-1].get_owner() << std::endl;
}
// An array to store the stacks.
class an_array
{
public:
    an_array()
    {
    }
    void PushIntoPlane(int plane_number, std::string owner);
    std::string PopFromPlane(int plane_number);
    void PrintPlane(int plane_number);
    void PushIntoGate(int gate_number, std::string owner);
    std::string PopFromGate(int gate_number);
    void PrintGate(int gate_number);
private:
    plane plane_stack[10];
    gate gate_stack[10];
};
// Add item to plane stack.
void an_array::PushIntoPlane(int plane_number, std::string owner)
{
    plane_stack[plane_number].Push(owner);
}
// Remove top item from plane stack.
std::string an_array::PopFromPlane(int plane_number)
{
    std::string name = plane_stack[plane_number].Pop();
    return name;
}
// Print the first item in the plane stack.
void an_array::PrintPlane(int plane_number)
{
    plane_stack[plane_number].Top(plane_number);
}
// Add item to gate stack.
void an_array::PushIntoGate(int gate_number, std::string owner)
{
    gate_stack[gate_number].Push(owner);
}
// Remove top item from gate stack.
std::string an_array::PopFromGate(int gate_number)
{
    std::string name = gate_stack[gate_number].Pop();
    return name;
}
// Print the first item in the gate stack.
void an_array::PrintGate(int gate_number)
{
    gate_stack[gate_number].Top(gate_number);
}


int main()
{
    // Create the array of stacks.
    an_array gates_and_planes;

    // Open input file.
    std::ifstream inFile;
    std::string inFileName = "airport.cpp";
    inFile.open(inFileName);

    if (!inFile)
    {
        std::cout << "File not found: " << inFileName << std::endl;
    }

    // Open output file.
    std::ofstream outFile;
    std::string outFileName = "airport_output.cpp";   // name of output file
    outFile.open(outFileName);                  // open output file

    // Read in commands.
    bool quit = false;
    std::string command;
    inFile >> command;

    while (quit == false)
    {
        // Add item to gate stack.
        if (command == "PUSH_GATE")
        {
            int gate_number;
            std::string owner;
            inFile >> gate_number;
            inFile >> owner;
            std::cout << "Adding luggage of " << owner << " to GATE " << gate_number << std::endl;
            gates_and_planes.PushIntoGate(gate_number, owner);
            outFile << "Adding luggage of " << owner << " to GATE " << gate_number << std::endl;
        }
        // Remove top item from gate stack.
        else if (command == "POP_GATE")
        {
            int gate_number;
            inFile >> gate_number;
            std::string name = gates_and_planes.PopFromGate(gate_number);
            std::cout << "Removing luggage of " << name << " from GATE " << gate_number << std::endl;
            outFile << "Removing luggage of " << name << " from GATE " << gate_number << std::endl;
        }
        // Print top item of gate stack.
        else if (command == "PRINT_GATE")
        {
            int gate_number;
            inFile >> gate_number;
            gates_and_planes.PrintGate(gate_number);
            outFile << "Printing the top luggage of GATE " << gate_number << std::endl;
        }
        // Add item to plane stack.
        else if (command == "PUSH_PLANE")
        {
            int plane_number;
            std::string owner;
            inFile >> plane_number;
            inFile >> owner;
            std::cout << "Adding luggage of " << owner << " to PLANE " << plane_number << std::endl;
            gates_and_planes.PushIntoPlane(plane_number, owner);
            outFile << "Adding luggage of " << owner << " to PLANE " << plane_number << std::endl;
        }
        // Remove top item from plane stack.
        else if (command == "POP_PLANE")
        {
            int plane_number;
            inFile >> plane_number;
            std::string name = gates_and_planes.PopFromPlane(plane_number);
            std::cout << "Removing luggage of " << name << " from PLANE " << plane_number << std::endl;
            outFile << "Removing luggage of " << name << " from PLANE " << plane_number << std::endl;
        }
        // Print top item of plane stack.
        else if (command == "PRINT_PLANE")
        {
            int plane_number;
            inFile >> plane_number;
            gates_and_planes.PrintPlane(plane_number);
            outFile << "Printing the top luggage of GATE " << plane_number << std::endl;
        }
        // Quit reading from input file.
        else if (command == "QUIT")
        {
            quit = true;

            std::cout << "#####################################################################" << std::endl;
            std::cout << "Quiting ..." << std::endl;
            outFile << "QUIT" << std::endl;
        }

        inFile >> command;
    }

    inFile.close();
    outFile.close();

    char exit;
    std::cin >> exit;


    return 0;
}


// gates_and_planes.PushIntoGate(0, "Johnson");
// gates_and_planes.PushIntoGate(0, "Twice");
// gates_and_planes.PrintGate(0);
// gates_and_planes.PopFromGate(0);
// gates_and_planes.PrintGate(0);
//
// gates_and_planes.PushIntoPlane(0, "Dahyun");
// gates_and_planes.PushIntoPlane(0, "Chaeyoung");
// gates_and_planes.PrintPlane(0);
// gates_and_planes.PopFromPlane(0);
// gates_and_planes.PrintPlane(0);
