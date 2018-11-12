#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include <unistd.h>

int Mat[50][50];
int temp[50][50];

pthread_mutex_t lock,lock2;


typedef struct pars
{
	int p;
	int q;
	int n;

}Pars;

int Det_Mat(int Mat[50][50], int n);
void *Get_Cof(void * Par);

int main(int argc, char const *argv[])
{
	int n;
	printf("\n Enter the size of the square matrix");
	scanf("%d",&n);

	printf("\n%s %d","Enter the Matrix of size ",n );

	//int Mat[n][n];
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			scanf("%d",&Mat[i][j]);
		}
	}

	if (pthread_mutex_init(&lock, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    }

    if (pthread_mutex_init(&lock2, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    }

	printf("\n Sending to find determinant");

	printf("\n This is the determinant of the mattrix :%d\n",Det_Mat(Mat,n));
	
	pthread_mutex_destroy(&lock); 

	pthread_mutex_destroy(&lock2);
	return 0;
}

void *Get_Cof(void * Par)
{
	pthread_mutex_lock(&lock);
	Pars * P=(Pars *)Par;

	int row=0,col=0;

	for (int i = 0; i < P->n; ++i)
	{
		for (int j = 0; j < P->n; ++j)
		{
			if(i!=P->p && j!=P->q)
			{
				temp[row][col++]=Mat[i][j];
			}

			if(col==P->n-1)
			{
				col=0;
				row++;
			}
		}
	}
	
	pthread_mutex_unlock(&lock);
	pthread_exit(0);
}



int Det_Mat(int Mat[50][50], int n)
{
	
	int D=0;
	
	if(n==1)
		return Mat[0][0];

	Pars *P= (Pars *)malloc(sizeof(Pars)*n);

	// for (int i = 0; i < n; ++i)
	// {
	// 	P[i]=(Pars )malloc(sizeof(Pars));
	// }

	int s=1;
	pthread_t tid;
	pthread_attr_t attr;

	for (int i = 0; i < n; ++i)
	{
		(P+i)->p=0,(P+i)->q=i,(P+i)->n=n;

		pthread_attr_init(&attr);	
		
		//pthread_mutex_lock(&lock);
		pthread_create(&tid,&attr,Get_Cof,(void *)(P+i));
		


		printf("%s\n %d : %d","Det till now",D,i );
		

		D+=s* Mat[0][i]* Det_Mat(temp,n-1);
		//Get_Cof(Mat,temp,0,i,n);
		
		s=-s;

		//pthread_mutex_unlock(&lock);
		pthread_join(tid,NULL);
	}

	// for (int i = 0; i < n; ++i)
	// {
	// pthread_join(tid[i],NULL);
	// 	/* code */
	// }

	return D;
}