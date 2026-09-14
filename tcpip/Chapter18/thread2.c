#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
void* thread_main(void *arg);

//구조체 변수 선언
/*struct Data {
	int	thread_param;
	char *msg;
};
*/


typedef struct {
	int	thread_param;
	char *msg;
}Data;



int main(int argc, char *argv[]) 
{
		pthread_t t_id;
//		struct Data tdata={0,0};
// 		memset(&data, 0x00, sizeof(tdata));

		Data tdata={0,0};
		void * thr_ret;	
		tdata.thread_param=5;
		tdata.msg = malloc(sizeof(char) *50);
		if(pthread_create(&t_id, NULL, thread_main, (void*)&tdata)!=0)
		{
				puts("pthread_create() error");
				return 1;
		}; 	

		if(pthread_join(t_id, &thr_ret)!=0)
		{
				puts("pthread_join() error");
				return 2;
		};

		printf("Thread return message: %s \n", (char*)thr_ret);
		free(thr_ret);
		return 0;
}

void* thread_main(void *arg) 
{
		int i;
		int cnt=data->thread_param;
		Data *data= (Data *)arg;
//		char * msg=malloc(sizeof(char)*50);
		strcpy(data->msg, "Hello, I'am thread~ \n");

		for(i=0; i<cnt; i++)
		{
				sleep(1);  puts("running thread");	 
		}
		return (void*)data->msg;
}
