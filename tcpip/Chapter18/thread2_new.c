#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
void* thread_main(void *arg);

//thread_param, msg  구조체 변수 선언 
/*
struct Data {
	int thread_param;
	char * msg;
};
*/
typedef struct {
	int thread_param;
	char * msg;
}Data;

int main(int argc, char *argv[]) 
{
	pthread_t t_id;
	void * thr_ret;
//	struct Data tdata={0,0};
//  memset(&tdata, 0x00, sizeof(tdata));

	Data tdata={0,0};
//	int thread_param=5;
//	char * msg=(char *)malloc(sizeof(char)*50);
	tdata.thread_param = 5;
	tdata.msg = (char *)malloc(sizeof(char)*50);

//	if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param)!=0)
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
#if 0
	Data data=*((Data*)arg);
	strcpy(data.msg, "Hello, I'am thread~ \n");

	for(i=0; i<data.thread_param; i++)
	{
		sleep(1);  
		puts("running thread");	 
	}
	return (void*)data.msg;
#else
	Data * pdata = ((Data*)arg);
//	strcpy( (*pdata).msg , "Hello, I'am thread~ \n");
	strcpy( pdata->msg , "Hello, I'am thread~ \n");
//	for(i=0; i<(*pdata).thread_param; i++)
	for(i=0; i<pdata->thread_param; i++)
	{
		sleep(1);  
		puts("running thread");	 
	}
//	return (void*)(*pdata).msg;
	return (void*)pdata->msg;
#endif
}
