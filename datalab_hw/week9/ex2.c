#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 100

typedef struct tree
{
    int count;
    char text[size];
    struct tree *left;
    struct tree *right;
} node;

node * newnode(char text[size]);
node *insert(node *r, char text[size]);
void inordertraversing(node *r);

int main()
{
    char s[size];
    char *text;
    node *root;
    const char space[] = " ,.-";
    printf("Enter the string:");
    scanf("%[^\n]%*c", s);
    text = strtok(s, space);
    while (text != NULL)
    {
        root = insert(root, text);
        text = strtok(NULL, space);
    }
    printf("\nWord counter: \n");
    inordertraversing(root);
}

node *newnode(char text[size])
{
    node *temp;
    temp = (node *)malloc(sizeof(node));
    temp->count = 1;
    strcpy(temp->text, text);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

node *insert(node *r, char text[size])
{
    node *temp;
    temp = newnode(text);
    if (r == NULL)
        return temp;
    if (strcmp(r->text, text) > 0)
        r->left = insert(r->left, text);
    else if (strcmp(r->text, text) < 0)
        r->right = insert(r->right, text);
    else if (strcmp(r->text, text) == 0)
        r->count = r->count + 1;
    return r;
}

void inordertraversing(node *r)
{
    if (r != NULL)
    {
        inordertraversing(r->left);
        printf("%-10s%-10d\n", r->text, r->count);
        inordertraversing(r->right);
    }
}