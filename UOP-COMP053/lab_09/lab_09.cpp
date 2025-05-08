#include<iostream>
#include<fstream>
#include<string>


class patient
{
public:
    patient()
    {
        this->name = "";
        this->age = 0;
        this->sex = "";
        this->pain_level = 0;
        this->disease_level = 0;
        this->injury_level = 0;
        this->condition_level = 0;
    }
    patient(std::string name, int age, std::string sex, int pain_level, int disease_level, int injury_level)
    {
        this->name = name;
        this->age = age;
        this->sex = sex;
        this->pain_level = pain_level;
        this->disease_level = disease_level;
        this->injury_level = injury_level;
        this->condition_level = pain_level + disease_level + injury_level;
    }

    std::string get_name()
    {
        return this->name;
    }

    void set_condition_level(int condition_level)
    {
        this->condition_level = condition_level;
    }

    int get_condition_level()
    {
        return this->condition_level;
    }

private:
    std::string name;
    int age;
    std::string sex;
    int pain_level;
    int disease_level;
    int injury_level;
    int condition_level;
};


class Maxheap
{
public:
    Maxheap()
    {

    }
    Maxheap(int cap);
    void swap(int i, int j);
    void checkIn(patient node);
    void Maxheapify(int i);
    patient admitPatient();

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

    void print_harr()
    {
        std::cout << "############################" << std::endl;

        for(int i = 0; i < this->capacity; i++)
        {
            std::cout << harr[i].get_name() << std::endl;
        }
    }

private:patient
    int heap_size;
    int capacity;
    patient* harr;
};
Maxheap::Maxheap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new patient[cap];

    for(int i = 0; i < capacity; i++)
    {
        harr[i] = patient();
    }
}
void Maxheap::swap(int i, int j)
{
    patient temp = harr[i];
    harr[i] = harr[j];
    harr[j] = temp;
}
void Maxheap::checkIn(patient node)
{
    heap_size++;
    int i = heap_size;
    harr[i-1] = node;

    while(i != 1 && ( harr[parent(i)-1].get_condition_level() < harr[i-1].get_condition_level() ) )
    {
        swap(i-1, parent(i)-1);
        i = parent(i);
    }
}

void Maxheap::Maxheapify(int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;

    if( (l < heap_size) && (harr[l-1].get_condition_level() > harr[i-1].get_condition_level() ) )
    {
        largest = l;
    }
    if( (r < heap_size) && (harr[r-1].get_condition_level() > harr[i-1].get_condition_level() ) )
    {
        largest = r;
    }
    if(largest != i)
    {
        swap(i, largest);
        Maxheapify(largest);
    }
}

patient Maxheap::admitPatient()
{
    if(heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    patient root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    Maxheapify(0);

    return root;
}


int main()
{
    Maxheap* all_patients = new Maxheap(20);
    patient patient01("Person04", 25, "Male", 1, 1, 1);
    patient01.set_condition_level(4);
    all_patients->checkIn(patient01);

    all_patients->print_harr();

    patient patient02("Person01", 19, "Male", 2, 2, 2);
    patient02.set_condition_level(1);
    all_patients->checkIn(patient02);

    all_patients->print_harr();

    patient patient03("Person10", 21, "Female", 1, 2, 1);
    patient03.set_condition_level(10);
    all_patients->checkIn(patient03);

    all_patients->print_harr();

    patient patient04("Person20", 20, "Male", 1, 1, 8);
    all_patients->checkIn(patient04);
    patient patient05("Person100", 22, "Female", 2, 2, 3);
    all_patients->checkIn(patient05);
    patient patient06("Person02", 20, "Male", 2, 3, 2);
    all_patients->checkIn(patient06);
    patient patient07("Person07", 20, "Female", 3, 6, 2);
    all_patients->checkIn(patient07);
    patient patient08("Person08", 20, "Female", 1, 1, 1);
    all_patients->checkIn(patient08);
    patient patient09("Person09", 20, "Female", 4, 1, 1);
    all_patients->checkIn(patient09);
    patient patient10("Person10", 20, "Male", 8, 2, 3);
    all_patients->checkIn(patient10);
    patient patient11("Person11", 24, "Female", 4, 1, 1);
    all_patients->checkIn(patient11);
    patient patient12("Person12", 20, "Male", 2, 4, 2);
    all_patients->checkIn(patient12);
    patient patient13("Person13", 22, "Female", 3, 2, 1);
    all_patients->checkIn(patient13);
    patient patient14("Person14", 5, "Female", 1, 8, 8);
    all_patients->checkIn(patient14);
    patient patient15("Person15", 29, "Male", 6, 2, 3);
    all_patients->checkIn(patient15);
    patient patient16("Person16", 29, "Female", 2, 3, 4);
    all_patients->checkIn(patient16);
    patient patient17("Person17", 20, "Male", 2, 4, 4);
    all_patients->checkIn(patient17);
    patient patient18("Person18", 20, "Male", 3, 2, 1);
    all_patients->checkIn(patient18);
    patient patient19("Person19", 20, "Female", 4, 1, 8);
    all_patients->checkIn(patient19);
    patient patient20("Person20", 20, "Female", 3, 3, 3);
    all_patients->checkIn(patient20);

    // all_patients->print_harr();
    //
    // // std::cout<< "hello" << std::endl;
    // patient admit01 = all_patients->admitPatient();
    // std::cout << "Admitting patient " << admit01.get_name() << std::endl;
    //
    patient admit02 = all_patients->admitPatient();
    patient admit03 = all_patients->admitPatient();
    patient admit04 = all_patients->admitPatient();
    patient admit05 = all_patients->admitPatient();

    all_patients->print_harr();

    all_patients = new Maxheap();
    delete all_patients;

    return 0;
}
