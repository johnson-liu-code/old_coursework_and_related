
#include<math.h>
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
    bool conv = false;
    double fact = -1, sum = 0, i = 1;
    double old_sum, diff;
    while (!conv)
    {
        old_sum = sum;
        sum += fact / i;
        printf("%g   %.20g\n", i, sum);
        i++;
        fact *= -1;
        diff = abs(sum - old_sum);
        if (diff < 1.e-6)
        {
            conv = true;
        }
    }

    // cout << sum << endl;

    return 0;
}
