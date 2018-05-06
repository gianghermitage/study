#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define size 200

FILE *f;
FILE *f2;

int checkID(int idData[])
{
    int n;
    n = rand() % 9999;
    for (int i = 0; i < size; i++)
    {
        if (n == idData[i])
            checkID(idData);
        else
            return n;
    }
}

long int checkPhone(long int phoneData[])
{
    long int n;
    n = rand() % 999999999;
    for (int i = 0; i < size; i++)
    {
        if (n == phoneData[i])
            checkPhone(phoneData);
        else
            return n;
    }
}

char *getFirstName(char fullname[])
{
    int n = strlen(fullname);
    int i;
    char *name = (char *)malloc(sizeof(char));
    for (i = 0; i < n + 1; i++)
    {
        if (fullname[i] == ' ')
        {
            *(name + i) = '\0';
            break;
        }
        *(name + i) = fullname[i];
    }
    return name;
    free(name);
}

char *getLastName(char fullname[])
{
    int n = strlen(fullname);
    int i;
    int checkSpace = 0;
    char *name = (char *)malloc(sizeof(char));
    for (i = n - 1; i >= 0; i--)
    {
        if (fullname[i] == ' ')
        {
            checkSpace = 1;
            int j = 0;
            int k = i;
            while (k < n + 1)
            {
                *(name + j) = fullname[k];
                j++;
                k++;
            }
            break;
        }
    }
    if (checkSpace == 0)
    {
        for (i = 0; i < n + 1; i++)
        {
            *(name + i) = fullname[i];
        }
    }
    return name;
    free(name);
}

int main()
{
    int i;

    int n = 0;
    int name1 = 0;
    int name2 = 0;
    int idData[size];
    long int phoneData[size];

    for (i = 0; i < size; i++)
    {
        idData[i] = -1;
        phoneData[i] = -1;
    }

    char nameData[size][size];
    char fullname[size];
    char *email = (char *)malloc(sizeof(char));
    char *phone = (char *)malloc(sizeof(char));
    
    srand(time(NULL));

    f = fopen("fullname.txt", "w+");
    f2 = fopen("name.txt", "r");

    for (i = 0; i <= size; i++)
    {
        fscanf(f2, "%s", nameData[i]);
    }

    for (i = 0; i <= 120; i++)
    {
        name1 = rand() % 200;
        name2 = rand() % 200;
        fprintf(f, "%s %s\n", nameData[name1], nameData[name2]);
    }

    fclose(f);
    fclose(f2);

    f = fopen("fullname.txt", "r");
    f2 = fopen("phonebook.txt", "w+");

    for (i = 0; i <= 120; i++)
    {
        fscanf(f, "%[^\n]%*c", fullname);
        fprintf(f2,"%s\n",fullname);
        email = getFirstName(fullname);
        *email = *email + 32; //convert first letter from indent to normal
        int idTemp = checkID(idData);
        char temp[size];
        sprintf(temp,"%d",idTemp);
        strcat(email, temp);
        strcat(email, "@gmail.com");
        fprintf(f2,"%s\n",email);
        strcpy(phone,"0");
        long int phoneTemp = checkPhone(phoneData);
        sprintf(temp,"%ld",phoneTemp);
        strcat(phone,temp);
        fprintf(f2,"%s\n",phone);
    }

    fclose(f);
    fclose(f2);
    free(email);
    free(phone);
}
