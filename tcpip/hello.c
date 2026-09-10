#include <stdio.h>
#define PI 3.14159
#include <unistd.h>

int main(int argc, char * argv[])
{	while(1){
		sleep(1);
		printf("Hello World! %d, %.5lf\n",BUFSIZ,PI);
}	
	return 0;
}
