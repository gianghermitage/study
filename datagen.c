#include<stdio.h>
#include<time.h>

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
