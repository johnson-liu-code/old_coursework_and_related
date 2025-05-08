#include<iostream>

using namespace std;




void drawShape(int n)
{
    cout << n << endl;

    if (n%2 == 0)
    {
        cout << "even" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << "* ";
            }
            cout << endl;
        }
        cout << "----------------------" << endl;
    }
    else
    {
        cout << "odd" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = -1; j < i; j++)
            {
                cout << "* ";
            }
            cout << endl;
        }
        cout << "----------------------" << endl;
    }


    return;
}



int main()
{
    drawShape(2);
    drawShape(5);
    drawShape(10);

    return 0;
}
