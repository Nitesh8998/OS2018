#include <stdio.h> 
#include <pthread.h>
#include <stdlib.h> 
 


void* Execing(void * args)
{
	char * str=(char*) args;

	printf("%s\n","Executing the executable using system");
	system(str);

	pthread_exit("bye");
}



int main(int argc, char const *argv[])
{
	pthread_t tid[5];

	char * str="ls-a";
	pthread_attr_t attr;

	pthread_attr_init(&attr);

	if(pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM)<0)
		{
			printf("%s\n","not happenening!!" );
			exit(1);
		}
	pthread_create(&tid[0],&attr,Execing,str);
	pthread_create(&tid[1],&attr,Execing,"ping google.com -c 8");
	pthread_create(&tid[2],&attr,Execing,"vim etc");
	pthread_create(&tid[3],&attr,Execing,"sleep 10");
	
	for (int i = 0; i < 4; ++i)
	{
		pthread_join(tid[i],NULL);
		printf("%s %d\n","THis is from THread ",i);
	}



	return 0;
}