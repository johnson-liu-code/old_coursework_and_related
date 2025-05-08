
my_function(int n)
{
    int y = 0;
    for(int i = 0; i < n; i++)
    {
        for(j = n; j >1; j=j/2)
        {
            y = y + j;
        }
    }
    for(int k = 0; k < n*n; k++)
    {
        y = y + k;
    }
}

in_common(int *ar1, int *ar2, int *result)
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(ar1[i] == ar2[j])
            {
                result[i] = ar1[i];
            }
        }
    }
}
