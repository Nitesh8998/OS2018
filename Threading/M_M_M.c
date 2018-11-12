#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>

#define MAX 100

typedef struct Array
{
	int size;
	int arr[MAX];
}array;

void * Median(void* Par);
void * Mean(void * Par);
void * Mode(void * Par);
void bubbleSort(int arr[], int n);
void swap(int *xp, int *yp);

int main(int argc, char const *argv[])
{
	pthread_t tid[3];
	pthread_attr_t attr;

	int i ;
	array *A;
	A=(array *) malloc (sizeof(array));
	printf("%s\n","\n Enter the size of the array" );
	scanf("%d",&A->size);

	
	printf("%s\n","Enter the array elements" );


	for (i = 0; i < A->size; ++i)
	{
		scanf("%d",&A->arr[i]);
	}


	pthread_attr_init(&attr);
	pthread_create(&tid[0],&attr,Mean,(void*)A);
	pthread_create(&tid[1],&attr,Median,(void *)A);
	pthread_create(&tid[2],&attr,Mode,(void *)A);
	

	for (i = 0; i < 3; ++i)
	{
		pthread_join(tid[i],NULL);
		/* code */
	}

	return (0);
}

//void * Median(void* Par)

void *Mean(void * Par)
{
	array *A= (array*) Par;

	int sum=0;

	int i;

	for ( i = 0; i < A->size; ++i)
	{
		sum+=A->arr[i];
	}

	printf("%s\n %f","this is the Mean",(float)sum/(float)A->size );
}


void * Median(void * Par)
{
	array *B= (array*) Par;

	int i,j;

	bubbleSort(B->arr,B->size);

	printf("%s\n %d","\nthis is the Median of the array",B->arr[B->size/2] );

	pthread_exit(0);
}

void * Mode(void * Par)
{
	array *B= (array*) Par;
	printf("%s\n","Hello" );

	int maxValue = 0, maxCount = 0, i, j;

   for (i = 0; i < B->size; ++i) {
      int count = 0;
      
      for (j = 0; j < B->size; ++j) {
         if (B->arr[j] == B->arr[i])
         ++count;
      }
      
      if (count > maxCount) {
         maxCount = count;
         maxValue = B->arr[i];
      }
   }

   printf("\n %s\n %d","This is the Mode of the array",maxValue );

   pthread_exit(0);
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

