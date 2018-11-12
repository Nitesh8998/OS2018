#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>

#define MAX 100
#define med 2
#define first 1
#define third 3
#define smallest 0

#define largest 4

float plot_out[5]={-99,-99,-99,-99,-99};

typedef struct Array
{
	int size;
	int arr[MAX];
	//int low;
	//int high;
}array;

void Box_Plot(array *A);
void bubbleSort(int arr[], int n);
void swap(int *xp, int *yp);

void * Quartile(void * Par);


int main(int argc, char const *argv[])
{
	

	int i ;
	array *A;
	A=(array *) malloc (sizeof(array));
	printf("%s\n","\n Enter the size of the array#" );
	scanf("%d",&A->size);

	
	printf("%s\n","Enter the array elements#" );


	for (i = 0; i < A->size; ++i)
	{
		scanf("%d",&A->arr[i]);
	}


	printf("\n%s","un sorted ?" );
	for (i = 0; i < A->size; ++i)
	{
		printf("%d ",A->arr[i]);
	}


	bubbleSort(A->arr,A->size);

	printf("\n%s\n","sorted " );
	for (i = 0; i < A->size; ++i)
	{
		printf("%d ",A->arr[i]);
	}
	Box_Plot(A);
	//pthread_create(&tid[0],&attr,Median,(void *)A);
	printf("\n%s\n","Here is the box plot paramaeters#" );

	printf("\n The smallest is : %.2f",plot_out[smallest]);
	printf("\n The first quartile: %.2f",plot_out[first]);
	printf("\n The Second quartile: %.2f",plot_out[med]);
	
	printf("\n The Third quartile: %.2f",plot_out[third]);
	printf("\n The Largest is : %.2f",plot_out[largest]);
	return 0;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
 
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}

void * Quartile(void * Par)
{
	array *A=(array *)Par;

	

	if(plot_out[med]==-99)
		{
			if(A->size%2==0)
				plot_out[med]=(A->arr[A->size/2]+A->arr[(A->size/2) +1])/2;

			else
			plot_out[med]=A->arr[A->size/2];
		}

	else if(plot_out[first]==-99 )
	{
		
		int larr_size=A->size/2;
		if((larr_size)%2==0)
			plot_out[first]=(float)(A->arr[larr_size/2]+A->arr[larr_size/2] -1)/2;
		else
			plot_out[first]=A->arr[larr_size/2];
	}

	else if (plot_out[third]==-99 )
	{
		int rlow;
		if(A->size%2==0)
			rlow=(A->size/2) + 1;
		else
			rlow=A->size/2;
		int rsize=(A->size-rlow);

		if(rsize%2==0)
				plot_out[third]=(float)(A->arr[rsize/2]+A->arr[(rsize/2) +1])/2;

			else
			plot_out[third]=A->arr[rsize/2];
	}

	else if(plot_out[smallest]==-99)
		plot_out[smallest]=A->arr[0];

	else if(plot_out[largest]==-99)
		plot_out[largest]=A->arr[A->size-1];


	pthread_exit(0);
}

void Box_Plot(array *A)
{
	pthread_t tid[5];
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	for (int i = 0; i < 5; ++i)
	{
	pthread_create(&tid[i],&attr,Quartile,(void*)A);	/* code */
	}
	
	for (int i = 0; i < 5; ++i)
	{
		pthread_join(tid[i],NULL);
		/* code */
	}
	

}