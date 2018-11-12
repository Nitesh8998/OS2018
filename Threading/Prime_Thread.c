#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>

typedef struct Limits{
	int low;
	int high;
}Limit;


int count=0;
void * PrimeCal(void * Para);

int main(int argc, char const *argv[])
{
	pthread_t tid[4];
	pthread_attr_t attr;

	if (argc !=2)
	{
		fprintf(stderr, "%s\n","error" );
	}

	if (atoi(argv[1])<0)

	{
		fprintf(stderr, "%s\n","enter correct value" );
	}

	int limit=atoi(argv[1]);
	int l1=limit/4;
	int l2=l1*2,l3=l1*3;

	Limit *l[4];

	for (int i = 0; i < 4; ++i)
	{
	l[i]=(Limit *) malloc (sizeof(Limit));
		/* code */
	}

	l[0]->low=2,l[0]->high=limit/4,l[1]->low=l[0]->high+1,l[1]->high=l[0]->high*2,l[2]->low=l[1]->high+1,l[2]->high=l[0]->high*3,l[3]->low=l[2]->high+1,l[3]->high=limit;// creating the limits
	
	for ( int i = 0; i < 4; ++i)
	{
		printf("Low :%d  High:%d",l[i]->low,l[i]->high);
	}

	pthread_attr_init(&attr);
	for (int i = 0; i < 4; ++i)
	{
		
	pthread_create(&tid[i],&attr,PrimeCal,(void *)l[i]);
		/* code */
	}

	//pthread_join(tid,NULL);
	for (int i = 0; i < 4; ++i)
	{
	pthread_join(tid[i],NULL);
		/* code */
	}

	printf("\ncounbt %d",count);
	return 0;
}


void * PrimeCal(void * Para)
{
	Limit * l= (Limit *) Para;
	int prime=1;
	int number;
	for ( number= l->low; number <= l->high; ++number)
	{
			
		prime =1;
		for(int i = 2; i <=number/2; i++) {
	      if((number % i) == 0) {
	         prime = 0;
	         break;
	      }

	      
	   }
	   if(prime)
	      	{
	      		printf("\n %d",number);
	      		count++;
	      	}
	}
   pthread_exit(0);
}