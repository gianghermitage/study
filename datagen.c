#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define namesize 100
#define emailsize 100
#define phonesize 10


FILE * f;

int main(){
	srand(time(NULL));
	int i;
	f = fopen("phonebook.txt","w+");
	for(i = 0; i < 120; i++){
		fprintf(f,"User #%05d\n",i+1);
		fprintf(f,"%05d@gmail.com\n",i+1);
		fprintf(f,"%010d\n",rand()%999999999);
	}
	fclose(f);
	return 0;
}