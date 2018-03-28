#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define size 120

long int generatenumber(long int n_old[size]){
	int j;
	long int n = rand()%99999999;
	for(j = 0; j < size; j++){
		if(n == n_old[j]){
			generatenumber(n_old);
		}
		else return n;
	}
}

FILE * f;

int main(){
	srand(time(NULL));
	int i;
	long int n = 0;
	long int n_old[size];
	f = fopen("phonebook.txt","w+");
	for(i = 0; i < size; i++){
		n_old[i] = -1;
	}
	for(i = 0; i < size; i++){
		n_old[i] = n;
		fprintf(f,"User #%05d\n",i+1);
		fprintf(f,"%05d@gmail.com\n",i+1);
		n = generatenumber(n_old);
		fprintf(f,"%010ld\n",n);
	}
	fclose(f);
	return 0;
}