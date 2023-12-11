#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX 100000
typedef unsigned int uint;

void random(int array[MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        array[i] = rand() % 1000 + 1;
    }
}

void ibubblesort(int *array, const uint length)
{
    bool hasPermuted = true;
    while (hasPermuted)
    {
        hasPermuted = false;
        for (int i = 0; i < length - 1; i++)
        {
            if (array[i] > array[i + 1])
            {
                int c = array[i];
                array[i] = array[i + 1];
                array[i + 1] = c;
                hasPermuted = true;
            }
        }
    }
}

int _ipartition(int *array, const int low, const int high)
{
    int pivot = array[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {
            int copy = array[++i];
            array[i] = array[j];
            array[j] = copy;
        }
    }
    int copy = array[i + 1];
    array[i + 1] = array[high];
    array[high] = copy;

    return i + 1;
}

void _iquicksort(int *array, const int low, const int high)
{
    if (low < high)
    {
        int pivot = _ipartition(array, low, high);
        _iquicksort(array, low, pivot - 1);
        _iquicksort(array, pivot + 1, high);
    }
}

void iquicksort(int *array, const uint length)
{
    _iquicksort(array, 0, length - 1);
}

int main()
{
    int array[MAX];
    uint choice;
    clock_t start, end;
    double cpu_time_used;
    bool flag = true;
    while (flag)
    {
        srand((unsigned)time(NULL));
        random(array);
        printf("+--------------------------------------+\n");
        printf("| 1: Tri à bulles                      |\n");
        printf("| 2: Tri rapide                        |\n");
        printf("+--------------------------------------+\n");
        printf("Nous proposons deux algorithmes de tri : \n");
        printf("> # ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            start = clock();
            ibubblesort(array, MAX);
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf(" Le tri à bulles a pris %f seconds\n", cpu_time_used);
            break;
        case 2:
            start = clock();
            iquicksort(array, MAX);
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf(" Le tri rapide a pris %f seconds\n", cpu_time_used);
            break;
        default:
            flag = false;
            break;
        }
    }

    return 0;
}