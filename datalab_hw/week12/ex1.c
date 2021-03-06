#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define size 100
#define namesize 30
#define emailsize 20
#define phonesize 10

typedef struct data
{
    char name[namesize];
    char email[emailsize];
    char phone[phonesize];
} phonebook;

//get data from file
void getdata(char *fn, phonebook *list);

void insertionsort(phonebook list[], int n);
void selectionsort(phonebook list[], int n);
void heapsort(phonebook list[], int n);
void swap(phonebook *list1, phonebook *list2);
void heapify(phonebook list[], int n, int i);
void merge(phonebook list[], int left, int mid, int right);
void mergesort(phonebook list[], int left, int right);

int main()
{
    int n;
    phonebook temp[size];
    phonebook list[10];
    phonebook list2[10];
    phonebook list3[10];
    phonebook list4[10];
    clock_t start, end;
    double time_used;
    getdata("phonebook.txt", temp);
    for (int i = 0; i < 10; i++)
    {
        n = rand() % 99;
        list[i] = temp[n];
        list2[i] = temp[n];
        list3[i] = temp[n];
        list4[i] = temp[n];
        printf("%-30s\n", list[i].name);
    }
    printf("\nInsertion sort\n");
    start = clock();
    insertionsort(list, 10);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    for (int i = 0; i < 10; i++)
    {
        printf("%-30s\n", list[i].name);
    }
    printf("Time taken: %lf\n", time_used);
    printf("\nSelection sort\n");
    start = clock();
    selectionsort(list2, 10);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (int i = 0; i < 10; i++)
    {
        printf("%-30s\n", list2[i].name);
    }
    printf("Time taken: %lf\n", time_used);
    printf("\nHeap sort\n");
    start = clock();
    heapsort(list3, 10);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    for (int i = 0; i < 10; i++)
    {
        printf("%-30s\n", list3[i].name);
    }
    printf("Time taken: %lf\n", time_used);

    printf("\nMerge sort\n");
    start = clock();
    mergesort(list4, 0, 9);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    for (int i = 0; i < 10; i++)
    {
        printf("%-30s\n", list4[i].name);
    }
    printf("Time taken: %lf\n", time_used);
}

void getdata(char *fn, phonebook *list)
{
    char s[size];
    FILE *f;
    f = fopen(fn, "r");
    for (int i = 0; i < 100; i++)
    {
        fscanf(f, "%[^\n]%*c", s);
        strcpy((list + i)->name, s);
        fscanf(f, "%[^\n]%*c", s);
        strcpy((list + i)->email, s);
        fscanf(f, "%[^\n]%*c", s);
        strcpy((list + i)->phone, s);
    }
    fclose(f);
}

void insertionsort(phonebook list[10], int n)
{
    int i, j;
    phonebook next;
    for (i = 1; i < n; i++)
    {
        next = list[i];
        for (j = i - 1; j >= 0 && strcmp(next.name, list[j].name) < 0; j--)
            list[j + 1] = list[j];
        list[j + 1] = next;
    }
}

void selectionsort(phonebook list[10], int n)
{
    int i, j, min;
    //phonebook temp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(list[j].name, list[min].name) < 0)
                min = j;
        }
        swap(&list[i], &list[min]);
    }
}
void swap(phonebook *list1, phonebook *list2)
{
    phonebook temp;
    temp = *list1;
    *list1 = *list2;
    *list2 = temp;
}

void heapify(phonebook list[10], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && strcmp(list[left].name, list[largest].name) > 0)
        largest = left;
    if (right < n && strcmp(list[right].name, list[largest].name) > 0)
        largest = right;
    if (largest != i)
    {
        swap(&list[i], &list[largest]);
        heapify(list, n, largest);
    }
}

void heapsort(phonebook list[10], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(list, n, i);
    for (int i = n - 1; i >= 0; i--)
    {
        swap(&list[0], &list[i]);
        heapify(list, i, 0);
    }
}

void merge(phonebook list[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    phonebook L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = list[left + i];
    for (j = 0; j < n2; j++)
        R[j] = list[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (strcmp(L[i].name, R[j].name) <= 0)
        {
            list[k] = L[i];
            i++;
        }
        else
        {
            list[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        list[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        list[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(phonebook list[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergesort(list, left, mid);
        mergesort(list, mid + 1, right);

        merge(list, left, mid, right);
    }
}
