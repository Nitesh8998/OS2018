#include<iostream>

#include<pthread.h>
#include<math.h>

using namespace std;


struct Det
{
	int ** mat;
	int n;
	int ans;
	
};

// void * GetCof( void * args)
// {

// }

void * determinant(void * args)
{
	Det * M = (Det *) args;
	if(M->n==2)
	{
	//cout<<"JI";
		M->ans=((M->mat[0][0] *M->mat[1][1])+ (M->mat[0][1]*-1*M->mat[1][0]));
	}


	else
	{
			Det *calc= new Det;
			calc->mat = new int * [M->n-1];
			for(int i = 0; i < M->n-1; ++i)
	      		calc->mat[i] = new int[M->n-1];
			calc->n = M->n-1;
			calc->ans=0;

			pthread_t *tid= new pthread_t  [M->n];

			pthread_attr_t attr;

			pthread_attr_init(&attr);
		
		for (int c = 0; c < M->n; c++)
        {

        	int row = 0,col = 0 ;
				// making the cofactor
				for (int i = 0; i < M->n; ++i)
				{
					for (int j = 0; j < M->n; ++j)
					{
						if(i != 0 && j != c)
						{
							calc->mat[row][col++] = M->mat[i][j];

							if (col == M->n-1)
							{
								col = 0;
								row++;
							}
						}
					}
				}

			pthread_create(&tid[c],&attr,&determinant, (void *) calc);
			M->ans = M->ans + (pow(-1,c) * M->mat[0][c]* calc->ans);

		}

		for (int i = 0; i < M->n; ++i)
		{
			 pthread_join(tid[i],NULL);
		}


	}

	pthread_exit(NULL);

}

int main(int argc, char const *argv[])
{
	
	Det * M = new Det ;
	cout<<"\n Enter the size of the square matrix"<<endl;
	cin>>M->n;
	 cout<<endl<<M->n;
	
	M->mat= new int *[M->n];
	for(int i = 0; i < M->n; ++i)
      M->mat[i] = new int[M->n];

	

	 M->mat= new int * [M->n];
	 for(int i = 0; i < M->n; ++i)
 		M->mat[i] = new int[M->n];

  cout<<"\n Enter the matrice"<<endl;

  for (int i = 0; i < M->n; ++i)

  {
  	for (int j = 0; j < M->n; ++j)
  	{
  		cin>>M->mat[i][j];
  	}
  }

  cout<<"\n THis is the matric you entered"<<endl;
  for (int i = 0; i < M->n; ++i)

  {
  	for (int j = 0; j < M->n; ++j)
  	{
  		cout<<M->mat[i][j]<< " ";
  	}
  	cout<<endl;
  }


  M->ans = 0;
  cout<<M->ans<<endl;
	cout<<" Sending to find determinant";

	// cout<<"HIIHI";
	
	// cout<<M->ans;

	pthread_t tid;

	pthread_attr_t attr;

		//pthread_attr_init(&attr);

	pthread_attr_init(&attr);

	// cout<<"HIIHI";

	pthread_create(&tid,&attr,&determinant,(void *)(M));

	pthread_join(tid,NULL);

	int D = M->ans;
	cout<<"\nmThis is the matrix determinant "<<M->ans;


 return (0);
}


