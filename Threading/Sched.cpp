#include <iostream> 
#include <pthread.h>
#include <cstdlib> 
using namespace std; 


void* Execing(void * args)
{
	char * str=(char*) args;

	cout<<"Executing the executable using system"<<endl;
	system(str);

	pthread_exit("bye");
}



int main(int argc, char const *argv[])
{
	pthread_t tid[5];

	char * str;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	if(pthread_attr_setshedpolicy(&attr,PROCESS_SCOPE_SYSTEM)<0)
		cout<<"THreading not possible";


	pthread_create(&tid[0],&attr,Execing,"ls -a");
	pthread_create(&tid[1],&attr,Execing,"ping google.com -c 8");
	pthread_create(&tid[2],&attr,Execing,"vim etc");
	pthread_create(&tid[3],&attr,Execing,"sleep 10");
	
	for (int i = 0; i < 4; ++i)
	{
		pthread_join(tid[i],&str);
		cout<<"THis is from THread "<<i<<" "<<str<<endl;
	}



	return 0;
}