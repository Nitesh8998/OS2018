#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include <unistd.h>

int Mat[50][50];
int temp[50][50];

pthread_mutex_t lock;


typedef struct pars
{
	int p;
	int q;
	int n;
	int *temp[50];
}Pars;

int Det_Mat(int *Mat[50], int n);
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

	printf("\n Sending to find determinant");

	printf("\n This is the determinant of the mattrix :%d\n",Det_Mat(Mat,n));
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
				P->temp[row][col++]=Mat[i][j];
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



int Det_Mat(int* Mat[50], int n)
{
	
	int D=0;
	
	if(n==1)
	{
		return Mat[0][0];
	}

	


	int s=1;
	pthread_t tid[n];
	pthread_attr_t attr;

	for (int i = 0; i < n; ++i)
	{
		Pars * P= (Pars * )malloc(sizeof(Pars));
		P->p=0,P->q=i,P->n=n;
		for (int j = 0; j < 50; j++)
			P->temp[j] = (int*)malloc(sizeof(int)*50);
		pthread_attr_init(&attr);	
		
		pthread_create(&tid[i],&attr,Get_Cof,(void *)P);
		
		pthread_join(tid[i],NULL);

		printf("%s\n %d : %d","Det till now",D,i );
		D+=s* Mat[0][i]* Det_Mat(P->temp,n-1);
		//Get_Cof(Mat,temp,0,i,n);
		s=-s;

	}

	/*for (int i = 0; i < n; ++i)
	{
	pthread_join(tid[i],NULL);
	}*/	/* code */

	return D;
}