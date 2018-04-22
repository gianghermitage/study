#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define size 500

void insertionsort(int list[size], int n);
void selectionsort(int list[size], int n);
void heapsort(int list[size], int n);
void swap(int *a, int *b);
void heapify(int list[size], int n, int i);

int main()
{
    int list_insertion[size];
    int list_selection[size];
    int list_heap[size];
    int random;
    clock_t start, end;
    double time_used;
    printf("Initial list\n");
    for (int i = 0; i < size; i++)
    {
        random = rand() % 999;
        list_insertion[i] = random;
        list_heap[i] = random;
        list_selection[i] = random;
        printf("%5d", list_insertion[i]);
    }
    printf("\n");
    printf("\nInsertion sort:\n");
    start = clock();
    insertionsort(list_insertion, size);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    for (int i = 0; i < size; i++)
    {
        printf("%5d", list_insertion[i]);
    }
    printf("\nTime used: %lf\n", time_used);
    printf("\n");

    printf("Selection sort:\n");
    start = clock();
    selectionsort(list_selection, size);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    for (int i = 0; i < size; i++)
    {
        printf("%5d", list_selection[i]);
    }
    printf("\nTime used: %lf\n", time_used);
    printf("\n");

    printf("Heap sort:\n");
    start = clock();
    heapsort(list_heap, size);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    for (int i = 0; i < size; i++)
    {
        printf("%5d", list_heap[i]);
    }
    printf("\nTime used: %lf\n", time_used);
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void insertionsort(int list[size], int n)
{
    int temp, i, j;
    for (i = 1; i < n; i++)
    {
        temp = list[i];
        for (j = i - 1; j >= 0 && list[j] > temp; j--)
        {
            list[j + 1] = list[j];
        }
        list[j + 1] = temp;
    }
}

void selectionsort(int list[size], int n)
{
    int min, i, j;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (list[j] < list[min])
                min = j;
        }
        swap(&list[i], &list[min]);
    }
}

void heapify(int list[size], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && list[left] > list[largest])
        largest = left;

    if (right < n && list[right] > list[largest])
        largest = right;

    if (largest != i)
    {
        swap(&list[i], &list[largest]);
        heapify(list, n, largest);
    }
}

void heapsort(int list[size], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(list, n, i);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        swap(&list[0], &list[i]);
        heapify(list, i, 0);
    }
}
