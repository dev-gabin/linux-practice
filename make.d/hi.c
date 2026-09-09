#include <stdio.h>
int input();
int output(int);
int main() 
{
	int n = input();
	if(!(output(n)))
		printf("Good bye\n");
	return 0;
}

int input()
{
	int num;
	printf("Enter a number? ");
	scanf("%d",&num);
	
	return num;
}

int output(int num)
{
	int i;
	for (i=0;i<num;i++)
		printf("Hi!\n");
	return 0;
} 
