#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>

typedef struct Limits{
	long int low;
	long int high;
}Limit;




#define limit 10000

double count=0,pcount=0;

void * Monte_Pi(void * Para);



int main(int argc, char const *argv[])
{
	pthread_t tid[4];
	pthread_attr_t attr;



	
	Limit *l[4];
	int i;

	for (int i = 0; i < 4; ++i)
	{
	l[i]=(Limit *) malloc (sizeof(Limit));
		/* code */
	}

	l[0]->low=0,l[0]->high=limit/4,l[1]->low=l[0]->high+1,l[1]->high=l[0]->high*2,l[2]->low=l[1]->high+1,l[2]->high=l[0]->high*3,l[3]->low=l[2]->high+1,l[3]->high=limit;// creating the limits
	
	// for ( i = 0; i < 4; ++i)
	// {
	// 	printf("Low :%d  High:%d",l[i]->low,l[i]->high);
	// }

	for (i = 0; i < 4; ++i)
	{
		pthread_attr_init(&attr);
	pthread_create(&tid[i],&attr,Monte_Pi,(void *)l[i]);
		/* code */
	}

	for (i = 0; i < 4; ++i)
	{
	pthread_join(tid[i],NULL);
		/* code */
	}

	double pi =(double)(4 * count) /pcount;
	printf("\nOverall value estimated by the program %lf", pi );


	return 0;
}


void * Monte_Pi(void * Para)
{
	Limit * l= (Limit *) Para;
	
	double c=0,pc=0,d;
	long int number;
	srand(time(NULL));
	double rand_x, rand_y;
	printf("%s\n","in Function" );
	  
	for ( number= l->low; number <= l->high * l->high; ++number)
	{
	
		rand_x = (double)(rand() % (limit + 1)) / limit; 
        rand_y = (double)(rand() % (limit + 1)) / limit;

        d= rand_x * rand_x + rand_y * rand_y; 		
		
	   if(d<=1)
	      	{
	      	
	      		count++;
	      		c++;
	      	}

	    pcount++,pc++;

	}
	double pi =(double)(4 * count) /pcount;
	

	printf("%s\n %lf","this is ", pi );
   pthread_exit(0);
}