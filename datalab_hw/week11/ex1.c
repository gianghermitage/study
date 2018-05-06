#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define size 100
#define namesize 100
#define emailsize 100
#define phonesize 20

typedef struct data
{
    char name[namesize];
    char email[emailsize];
    char phone[phonesize];
} phonebook;

typedef struct list
{
    phonebook e;
    struct list *next;
} node;





node *newnode(phonebook list)
{
    node *temp;
    temp = (node *)malloc(sizeof(node));
    temp->e = list;
    temp->next = NULL;
    return temp;
}

void insertafter(node ** root,node ** cur,phonebook list){
  node * link;
  link = newnode(list);
  if(*root == NULL){
    *root = link;
    *cur = *root;
  }
  else{
    link->next = (*cur)->next;
    (*cur)->next = link;
    (*cur) = (*cur)->next;
  }
}

node *lastNode(node *root)
{
    node *link = root;
    while (link->next != NULL)
        link = link->next;
    return link;
}
node *partition(node *start, node *end, node **newStart, node **newEnd)
{
    node *pivot = end;
    node *prev = NULL;
    node *cur = start;
    node *tail = pivot;

    while (cur != pivot)
    {
        if (strcmp(cur->e.name, pivot->e.name) < 0)
        {
            if ((*newStart) == NULL)
                (*newStart) = cur;
            prev = cur;
            cur = cur->next;
        }
        else
        {
            if (prev != NULL)
                prev->next = cur->next;
            node *temp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }
    if (*(newStart) == NULL)
        *(newStart) = pivot;
    (*newEnd = tail);
    return pivot;
}

node *quickSortRecur(node *start, node *end)
{
    if (!start || start == end)
        return start;
    node *newStart = NULL;
    node *newEnd = NULL;
    node *pivot = partition(start, end, &newStart, &newEnd);
    if (newStart != pivot)
    {
        node *temp = newStart;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = NULL;
        newStart = quickSortRecur(newStart, temp);
        temp = lastNode(newStart);
        temp->next = pivot;
    }
    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newStart;
}

void quickSort(node **root)
{
    (*root) = quickSortRecur(*root, lastNode(*root));
}
void printList(node * root){
    while (root != NULL)
    {
        printf("%-30s%-30s%-30s\n", root->e.name,root->e.email,root->e.phone);
        root = root->next;
    }
}


int main()
{
    phonebook list[size];
    node * root= NULL;
    node * cur = NULL;
    FILE *f;
    char s[100];
    int n;
    f = fopen("phonebook.txt", "r");
    for (int i = 0; i < size; i++)
    {
        fscanf(f, "%[^\n]%*c", s);
        strcpy(list[i].name, s);
        fscanf(f, "%[^\n]%*c", s);
        strcpy(list[i].email, s);
        fscanf(f, "%[^\n]%*c", s);
        strcpy(list[i].phone, s);
        printf("%-30s%-30s%-30s\n",list[i].name,list[i].email,list[i].phone);
    }
    fclose(f);
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        insertafter(&root,&cur,list[i]);
    }
    printf("\n\n");
    quickSort(&root);
    //printf("%s\n",root->e.name);
    printList(root);
}
