#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define MAX 100

pthread_mutex_t lock; // mutex


typedef struct M_Sorter
{
	
	
	// left right middle stuff as they have to be sent as para in call
	int l;
	//int m;
	int r;
}M;


void Merge(); // normal
void *Merge_Sort(void * Par); // runner

int arr[MAX]; // global array as threads have to access it independently

int main()
{
	M *A=(M*)malloc(sizeof(M));
	int size;

	if (pthread_mutex_init(&lock, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    }

	printf("%s\n","\n Enter the size of the array" );
	scanf("%d",&size);

	int i;
	
	printf("%s\n","Enter the array elements" );


	for (i = 0; i < size; ++i)
	{
		scanf("%d",&arr[i]);
	}
	
	// assigning the left and right for starting the algo
	A->l=0,A->r=size-1;

	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,Merge_Sort,(void *)A); // starter thread

	pthread_join(tid,NULL); 

	printf("%s\n"," this is sorted" );
	for (i = 0; i < size; ++i)
	{
		printf("%d ",arr[i]);
	}


	pthread_mutex_destroy(&lock); 
	return(0);
}
	
void Merge(int l , int m , int r)
{
	int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
  	pthread_mutex_lock(&lock);
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 

    pthread_mutex_unlock(&lock); //unlocking the lock
}

void *Merge_Sort(void * Par)
{
	M * A= (M*) Par;
	int i;

	M *As=(M*)malloc(sizeof(M));
	if(A->l<A->r)
	{
		int m=A->l+ (A->r-A->l)/2;
		
		
		 pthread_t tid[2];
         pthread_attr_t attr;
         
         pthread_attr_init(&attr);
         
         //for the left part
         
         As->l=A->l,As->r=m;

		 // as address space matters so for every thread
		 // we create a sperate variable so that overlap write 
		 // or inproper read doesnt happen
		 M *As1=(M*)malloc(sizeof(M));
		 
		 As1->l = m+1;  As1->r = A->r;
         pthread_create(&tid[0],&attr,Merge_Sort,(void *)As);

         //for the right part
         
         pthread_create(&tid[1],&attr,Merge_Sort,(void *)As1);

        


		
		// only after joining them we can merge the thread

		 for (i = 0; i < 2; ++i)
		{
			pthread_join(tid[i],NULL);
		
		}

		Merge(As->l,m,A->r);

	}

	free(As);
	
}
