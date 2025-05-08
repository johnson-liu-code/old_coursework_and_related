#include<iostream>
#include<string>


class Minheap
{
public:
    Minheap(int cap);
    ~Minheap();
    void swap(int i, int j);
    void enqueue(int k);

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
        std::cout << "############################" << std::endl;

        for(int i = 0; i < this->capacity; i++)
        {
            std::cout << harr[i] << std::endl;
        }
    }

private:
    int heap_size;
    int capacity;
    int* harr;
};

Minheap::Minheap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];

    for(int i = 0; i < capacity; i++)
    {
        harr[i] = 0;
    }
}

Minheap::~Minheap()
{
    delete (harr);
}

void Minheap::swap(int i, int j)
{
    int temp = harr[i];
    harr[i] = harr[j];
    harr[j] = temp;
}

void Minheap::enqueue(int k)
{
    heap_size++;
    int i = heap_size;
    harr[i-1] = k;

    while(i != 1 && (harr[parent(i)-1] > harr[i-1]))
    {
        swap(i-1, parent(i)-1);
        i = parent(i);
    }
}

int main()
{

    Minheap mytasks(8);

    mytasks.enqueue(4);
    mytasks.enqueue(7);
    mytasks.enqueue(3);
    mytasks.enqueue(6);
    mytasks.enqueue(4);
    mytasks.enqueue(1);
    mytasks.enqueue(6);
    mytasks.enqueue(2);
    mytasks.print_harr();

    mytasks.~Minheap();

    return 0;
}
