#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct tree
{
    phonebook data;
    struct tree *left;
    struct tree *right;
} node;

//stack
node *stack[size];
int top = -1;

//queue
node *queue[size];
int front = -1;
int rear = -1;

//binary tree function
node *search(node *r, char key[size]);
node *insert(node *r, phonebook list);
node *deletenode(node *r, char key[size]);
node *findleftmostnodeofright(node *r);
node *freetree(node *r);
void preordertraversing(node *r);
void inordertraversing(node *r);
void postordertraversing(node *r);

//get data from file
void getdata(char *fn, phonebook *list);

//stack function
void push(node *r);
node *pop(node *s[size]);
void inorderwithstack(node *r);

//queue function
int checkemptyq();
int checkfullq();
void enQ(node *r);
node *deQ();
void BFS(node *r);

int main()
{
    node *root = NULL;
    phonebook list[size];
    getdata("phonebook.txt", list);
    int choice;
    int n;
    char email[emailsize];
    node *emailtemp;
    char del[size];
    node *deltemp;
    do
    {
        printf("\n\n Menu \n\n");
        printf("1.Add data to BST\n");
        printf("2.Search data in BST\n");
        printf("3.Delete a node in BST\n");
        printf("4.Delete tree\n");
        printf("5.Show tree(pre - order)\n");
        printf("6.Show tree(in - order) - Stack method\n");
        printf("7.Show tree(post - order)\n");
        printf("8.Breadth first search\n");
        printf("9.Quit\n");
        printf("\nYour choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            n = rand() % 99;
            printf("%s\n", list[n].name);
            root = insert(root, list[n]);
            break;
        case 2:
            printf("Enter the email you want to search:");
            scanf("%s%*c", email);
            emailtemp = search(root, email);
            if (emailtemp == NULL)
                printf("Cant find that person\n");
            else
                printf("%s    %s    %s\n", emailtemp->data.name, emailtemp->data.email, emailtemp->data.phone);
            break;
        case 3:
            printf("Enter the email you want to delete:");
            scanf("%s%*c", del);
            root = deletenode(root, del);
            break;
        case 4:
            if (root == NULL)
                printf("Tree is already empty\n");
            else
            {
                root = freetree(root);
                printf("Deleted\n");
            }
            break;
        case 5:
            preordertraversing(root);
            break;
        case 6:
            inorderwithstack(root);
            break;
        case 7:
            postordertraversing(root);
            break;
        case 8:
            BFS(root);
            break;
        case 9:
            printf("Quit\n");
            break;
        default:
            printf("Please choose from 1 to 9 only\n");
            break;
        }
    } while (choice != 9);
}

void getdata(char *fn, phonebook *list)
{
    char s[size];
    FILE *f;
    f = fopen(fn, "r");
    for (int i = 0; i < 100; i++)
    {
        fscanf(f, "%s", s);
        strcpy((list + i)->name, s);
        fscanf(f, "%s", s);
        strcpy((list + i)->email, s);
        fscanf(f, "%s", s);
        strcpy((list + i)->phone, s);
    }
    fclose(f);
}

node *insert(node *r, phonebook list)
{
    node *temp;
    temp = r;
    if (temp == NULL)
    {
        temp = (node *)malloc(sizeof(node));
        temp->data = list;
        temp->left = NULL;
        temp->right = NULL;
        r = temp;
        return r;
    }
    else
    {
        if (strcmp(temp->data.email, list.email) > 0)
            r->left = insert(r->left, list);
        else if (strcmp(temp->data.email, list.email) < 0)
            r->right = insert(r->right, list);
    }
    return r;
}

node *search(node *r, char key[size])
{
    if (r != NULL)
    {
        if (strcmp(r->data.email, key) == 0)
            return r;
        if (strcmp(r->data.email, key) > 0)
            return search(r->left, key);
        if (strcmp(r->data.email, key) < 0)
            return search(r->right, key);
    }
    return NULL;
}

node *findleftmostnodeofright(node *r)
{
    if (r->left == NULL)
        return r;
    r->left = findleftmostnodeofright(r->left);
}

node *deletenode(node *r, char key[size])
{
    if (r == NULL)
        return NULL;
    if (r != NULL)
    {
        if (strcmp(r->data.email, key) > 0)
            r->left = deletenode(r->left, key);
        else if (strcmp(r->data.email, key) < 0)
            r->right = deletenode(r->right, key);
        else
        {
            if (r->right == NULL)
            {
                node *temp;
                temp = r->left;
                free(r);
                return temp;
            }
            else if (r->left == NULL)
            {
                node *temp;
                temp = r->right;
                free(r);
                return temp;
            }
            else
            {
                node *temp;
                temp = findleftmostnodeofright(r->right);
                r->data = temp->data;
                r->right = deletenode(r->right, temp->data.email);
                printf("lul\n");
            }
        }
        return r;
    }
}
node *freetree(node *r)
{
    if (r != NULL)
    {
        freetree(r->left);
        freetree(r->right);
        r = NULL;
    }
    return r;
}

void preordertraversing(node *r)
{
    if (r != NULL)
    {
        printf("%s    %s     %s\n", r->data.name, r->data.email, r->data.phone);
        preordertraversing(r->left);
        preordertraversing(r->right);
    }
}

void inordertraversing(node *r)
{
    char s[200];
    if (r != NULL)
    {
        inordertraversing(r->left);
        printf("%s    %s     %s\n", r->data.name, r->data.email, r->data.phone);
        inordertraversing(r->right);
    }
}

void inorderwithstack(node *r)
{
    while (1)
    {
        while (r != NULL)
        {
            push(r);
            r = r->left;
        }
        if (top == -1)
            break;
        r = pop(stack);
        if (r == NULL)
            break;
        printf("%s    %s     %s\n", r->data.name, r->data.email, r->data.phone);
        r = r->right;
    }
}

void push(node *r)
{
    top++;
    stack[top] = r;
}

node *pop(node *s[size])
{
    node *temp;
    temp = s[top];
    top--;
    return temp;
}

void postordertraversing(node *r)
{
    if (r != NULL)
    {
        postordertraversing(r->left);
        postordertraversing(r->right);
        printf("%s    %s     %s\n", r->data.name, r->data.email, r->data.phone);
    }
}

int checkemptyq()
{
    if (front == -1 || front > rear)
        return 1;
    else
        return 0;
}

void enQ(node *r)
{
    if (front == -1)
        front = 0;
    rear++;
    queue[rear] = r;
}

node *deQ()
{
    node *temp;
    temp = queue[front];
    front++;
    return temp;
}

void BFS(node *r)
{
    if (r != NULL)
    {
        enQ(r);
        while (checkemptyq() != 1)
        {
            r = deQ();
            printf("%s    %s     %s\n", r->data.name, r->data.email, r->data.phone);
            if (r->left != NULL)
                enQ(r->left);
            if (r->right != NULL)
                enQ(r->right);
        }
    }
}
