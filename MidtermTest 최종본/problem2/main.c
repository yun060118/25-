#include <stdio.h>

int SS(int mp, int range)
{
    if (mp >= 50)
    {
        if (range > 10)
        {
            printf("���ΰ� : �ʴ� ������ ȹ���߳�?\n");
        }
    }
    return 0; 
}

int main()
{
    int mp = 150;
    int range = 20;
    SS(mp, range);

    return 0;
}