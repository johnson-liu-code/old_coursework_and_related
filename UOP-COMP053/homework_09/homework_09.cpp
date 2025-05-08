#include<iostream>
#include<fstream>
#include<string>

class customer
{
public:
    customer()
    {
        this->priority = 100;
        this->name = "";
        this->age = 0;
        this->money_spent = 0;
        this->type_of_last_room = "none";
    }
    customer(int priority, std::string name, int age, int money_spent, std::string type_of_last_room)
    {
        this->priority = priority;
        this->name = name;
        this->age = age;
        this->money_spent = money_spent;
        this->type_of_last_room = type_of_last_room;
    }

    void set_priority(int priority)
    {
        this->priority = priority;
    }
    int get_priority()
    {
        return this->priority;
    }
    std::string get_name()
    {
        return this->name;
    }
    int get_age()
    {
        return this->age;
    }
    int get_money_spent()
    {
        return this->money_spent;
    }
    std::string get_type_of_last_room()
    {
        return this->type_of_last_room;
    }

private:
    int priority;
    std::string name;
    int age;
    int money_spent;
    std::string type_of_last_room;
};

class Minheap
{
public:
    Minheap()
    {
    }
    Minheap(int cap);
    ~Minheap();
    void swap(int i, int j);
    void enqueue(customer node);
    void MinHeapify(int i);
    customer answer();
    void print_next_five_callers();

    int parent(int i)
    {
        return i / 2;
    }
    int left(int i)
    {
        return 2*i;
    }
    int right(int i)
    {
        return 2*i+1;
    }

    int get_cap()
    {
        return this->capacity;
    }
    void print_harr()
    {
        std::cout << "####################################################" << std::endl;
        std::cout << "##### Printing all callers on the waiting list #####" << std::endl;
        for(int i = 0; i < this->heap_size; i++)
        {
            std::cout << "Priority " << harr[i].get_priority() << ": " << harr[i].get_name()
                      << ", Age: " << harr[i].get_age() << ", Money spent: "
                      << harr[i].get_money_spent() << ", Previous room type: "
                      << harr[i].get_type_of_last_room() << std::endl;
        }
        std::cout << "####################################################" << std::endl;
    }

private:
    int heap_size;
    int capacity;
    customer* harr;
};

Minheap::Minheap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new customer[cap];

    for(int i = 0; i < capacity; i++)
    {
        harr[i] = customer();
    }
}

Minheap::~Minheap()
{
    delete (harr);
}

void Minheap::swap(int i, int j)
{
    customer temp = harr[i];
    harr[i] = harr[j];
    harr[j] = temp;
}

void Minheap::enqueue(customer node)
{
    heap_size++;
    int i = heap_size;
    harr[i-1] = node;

    while(i != 1 && ( harr[parent(i)-1].get_priority() > harr[i-1].get_priority() ) )
    {
        swap(i-1, parent(i)-1);
        i = parent(i);
    }
}

void Minheap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if( (l < heap_size) && (harr[l].get_priority() < harr[i].get_priority()) )
    {
        smallest = l;
    }
    if( (r < heap_size) && (harr[r].get_priority() < harr[smallest].get_priority()) )
    {
        smallest = r;
    }
    if(smallest != i)
    {
        swap(i, smallest);
        MinHeapify(smallest);
    }

}

customer Minheap::answer()
{
    customer root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);

    return root;
}

void Minheap::print_next_five_callers()
{
    std::cout << "##############################################################" << std::endl;
    std::cout << "##### Printing the next five callers on the waiting list #####" << std::endl;
    for(int i = 0; i < 5; i++)
    {
            std::cout << "Priority " << harr[i].get_priority() << ": " << harr[i].get_name()
                      << ", Age: " << harr[i].get_age() << ", Money spent: "
                      << harr[i].get_money_spent() << ", Previous room type: "
                      << harr[i].get_type_of_last_room() << std::endl;
    }
    std::cout << "##############################################################" << std::endl;
}

int main()
{
    std::ifstream inFile;
    std::string inFileName = "venetian.txt";
    inFile.open(inFileName);

    if (!inFile)
    {
        std::cout << "File not found: " << inFileName << std::endl;
    }

    std::ofstream outFile;
    std::string outFileName = "venetian_output.txt";   // name of output file
    outFile.open(outFileName);                  // open output file

    bool quit = false;
    std::string command;
    inFile >> command;

    Minheap* customer_heap = new Minheap(20);

    int priority;
    std::string name;
    int age;
    int money_spent;
    std::string type_of_last_room;
    customer node;

    while(quit == false)
    {
        if(command == "ADD_CUSTOMER")
        {
            inFile >> priority;
            inFile >> name;
            inFile >> age;
            inFile >> money_spent;
            inFile >> type_of_last_room;

            node = customer(priority, name, age, money_spent, type_of_last_room);
            customer_heap->enqueue(node);
        }

        else if(command == "ANSWER_CALL")
        {
            customer root = customer_heap->answer();
            std::cout << "Answering call from customer " << root.get_name() <<
                    ", Priority: " << root.get_priority() << ", Age: " << root.get_age() <<
                    ", Money spent: " << root.get_money_spent() << ", Type of previous room: "
                    << root.get_type_of_last_room() << std::endl;
            outFile << "Ansering call from customer " << root.get_name() << std::endl;
            // customer_heap->MinHeapify(0);
        }

        else if(command == "PRINT_HEAP")
        {
            customer_heap->print_harr();
            outFile << "Printing all callers on waiting list" << std::endl;
        }

        else if(command == "PRINT_NEXT_FIVE")
        {
            customer_heap->print_next_five_callers();
            outFile << "Printing the next five callers on the waiting list" << std::endl;
        }

        else if(command == "QUIT")
        {
            quit = true;
            outFile << "Quitting" << std::endl;
        }

        inFile >> command;
    }

    customer_heap = new Minheap();
    delete customer_heap;

    inFile.close();
    outFile.close();

    char exit;
    std::cin >> exit;

    return 0;
}
