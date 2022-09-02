#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void main(){
	printf("Before");
	fork();
	printf("forsy");
	fork();
	printf("second");
	fork();
	printf("After third");
}
