#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define size 100

void initNamelist(char *namelist[])
{
    for (int i = 0; i < 25; i++)
        namelist[i] = (char *)malloc(sizeof(char));
}

void set_upNamelist(char *namelist[], char *filename)
{
    char s[size];
    FILE *f;
    f = fopen(filename, "r");
    for (int i = 0; i < 25; i++)
    {
        fscanf(f, "%[^\n]%*c", namelist[i]);
    }
}

int preceeding(char *first, char *second)
{
    int n1, n2;
    n1 = strlen(first);
    n2 = strlen(second);
    if (n1 < n2)
    {
        for (int i = 0; i < n1; i++)
        {
            if (first[i] < second[i])
                return -1;
            else if (first[i] > second[i])
                return 1;
        }
        return -1;
    }
    else if (n1 > n2)
    {
        for (int i = 0; i < n2; i++)
        {
            if (first[i] < second[i])
                return -1;
            else if (first[i] > second[i])
                return 1;
        }
        return 1;
    }
    else
    {
        for (int i = 0; i < n2; i++)
        {
            if (first[i] < second[i])
                return -1;
            else if (first[i] > second[i])
                return 1;
        }
        return 0;
    }
}

void swap(char *a, char *b)
{
    char *temp = (char *)malloc(sizeof(char));
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

int partition(char *list[], int low, int high)
{
    char *pivot = (char *)malloc(sizeof(char));
    strcpy(pivot, list[high]);
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (preceeding(list[j], pivot) <= 0)
        {
            i++;
            swap(list[i], list[j]);
        }
    }
    swap(list[i + 1], list[high]);
    return (i + 1);
}

void quickSort(char *list[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(list, low, high);
        quickSort(list, low, pi - 1);
        quickSort(list, pi + 1, high);
    }
}

int main()
{
    char *list[25];
    char *sortedList[25];

    initNamelist(list);
    initNamelist(sortedList);
    set_upNamelist(list, "fullname.txt");
    set_upNamelist(sortedList, "fullname.txt");

    printf("\n%-50s%-50s\n\n", "Initial list", "Sorted list");
    quickSort(sortedList, 0, 24);
    for (int i = 0; i < 25; i++)
    {
        printf("%-50s", list[i]);
        printf("%-50s\n", sortedList[i]);
    }
    printf("\n\n");
}