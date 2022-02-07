#include "encrypt.h"

int prime(long int pr)
{
    int i;
    long int j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

long int encryption_key()
{
    int x = 3;
    int y = 71;
    int t = (x - 1) * (y - 1);
    int k = 0;
    long int e[50];
    long int d[50];
    for (int i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        long int flag = prime(i);
        if (flag == 1 && i != x && i != y)
        {
            e[k] = i;
            flag = cd(e[k], 140);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
    return e[0];
}
long int cd(long int a, int f)
{
    long int k = 1;
    while (1)
    {
        k = k + f;
        if (k % a == 0)
            return (k / a);
    }
}

//function to encrypt the message
char *encrypt_pswd(char *msg)
{   
    long int key = encryption_key();
    long int len = strlen(msg);
    int m[len];
    for (int i = 0; msg[i]; i++)
        m[i] = msg[i];
    int x = 3;
    long int en[50];
    int y = 71;
    int n = x * y;
    long int pt, ct, k;
    long int temp[50];
    int i = 0;
    
    while (i != len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (long int j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    char * result = malloc(i);
    for (i = 0; en[i] != -1; i++)
        result[i] = en[i];
    return result;
}

