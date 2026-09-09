#include <stdio.h>
#include "input.h"
#include "output.h"
int main(){
	int n=input();
	if(!(output(n)))
		printf("Good bye!\n");
	return 0;
}

