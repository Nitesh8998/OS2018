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


// void * determinant(void * args)
// {
// 	Det * M = (Det *) args;
// 	if(M->n==2)
// 	{
// 	//cout<<"JI";
// 		M->ans=((M->mat[0][0] *M->mat[1][1])+ (M->mat[0][1]*-1*M->mat[1][0]));
// 	}


// 	else
// 	{
// 			Det *calc= new Det;
// 			calc->mat = new int * [M->n-1];
// 			for(int i = 0; i < M->n-1; ++i)
// 	      		calc->mat[i] = new int[M->n-1];
// 			calc->n = M->n-1;
// 			calc->ans=0;

// 			pthread_t *tid= new pthread_t  [M->n];

// 			pthread_attr_t attr;

// 			pthread_attr_init(&attr);
		
// 		for (int c = 0; c < M->n; c++)
//         {

//         	int row = 0,col = 0 ;
// 				// making the cofactor
// 				for (int i = 0; i < M->n; ++i)
// 				{
// 					for (int j = 0; j < M->n; ++j)
// 					{
// 						if(i != 0 && j != c)
// 						{
// 							calc->mat[row][col++] = M->mat[i][j];

// 							if (col == M->n-1)
// 							{
// 								col = 0;
// 								row++;
// 							}
// 						}
// 					}
// 				}

// 			pthread_create(&tid[c],&attr,&determinant, (void *) calc);
// 			M->ans = M->ans + (pow(-1,c) * M->mat[0][c]* calc->ans);

// 		}

// 		for (int i = 0; i < M->n; ++i)
// 		{
// 			 pthread_join(tid[i],NULL);
// 		}


// 	}

// 	pthread_exit(NULL);

// }


void *determinant(void * args)
{
	Det * M= (Det*) args;
	//cout<<M->ans<<" "<<M->n;
	if(M->n==2)
	{
	//cout<<"JI";
		M->ans=((M->mat[0][0] *M->mat[1][1])+ (M->mat[0][1]*-1*M->mat[1][0]));
	}
	else
	{
		cout<<M->ans<<" "<<M->n;
		pthread_t *tid= new pthread_t  [M->n];

		pthread_attr_t attr;

		pthread_attr_init(&attr);

		Det *calc= new Det;
		calc->mat = new int * [M->n-1];
		for(int i = 0; i < M->n-1; ++i)
      		calc->mat[i] = new int[M->n-1];
		calc->n = M->n-1;
		calc->ans=0;

		for (int c = 0; c < M->n; c++)
        {
			int row=0;
			for(int i = 1; i<M->n;i++)
			{

				int col = 0;
				for (int j = 0; j <M->n ; ++j)
				{
					if (c == j)
						continue;

					calc->mat[row][col]=M->mat[i][j];

					col++;
				}

				row++;

			}
			calc->ans = 0;
		pthread_create(&tid[c],&attr,&determinant, (void *) calc);
			pthread_join(tid[c],NULL);
		
		M->ans = M->ans + (pow(-1,c) * M->mat[0][c]* calc->ans);
		 
		//cout<<endl<<c<<" "<<M->ans<<endl;
		//cout<<"hi this";
		 //cout<<endl<<c<<" "<< M->ans;
		}

		// for (int i = 0; i < M->n; ++i)
		// {
		// 	 pthread_join(tid[i],NULL);
		// }


	}

	pthread_exit(0);
}

void  Adjoint(int **Adj , Det * M)
{
	

	if (M->n==1)
	{
		Adj[0][0] = 1;
		return;
	}

	else
	{
		int s= 1 ;
		pthread_t *tid= new pthread_t  [M->n * M->n];

		pthread_attr_t attr;

		pthread_attr_init(&attr);

		// Det *calc= new Det;
		// calc->mat = new int * [M->n];
		// for(int i = 0; i < M->n; ++i)
  //     		calc->mat[i] = new int[M->n-1];
		// calc->n = M->n-1;
		// calc->ans=0;

		int count = 0 ;
		for (int k = 0; k < M->n; ++k)
		{
			count = 0;
			for (int l = 0; l < M->n; ++l)
			{
				/* code */
			
				// making the resized matrice

				Det *calc= new Det;
					calc->mat = new int * [M->n];
					for(int i = 0; i < M->n; ++i)
			      		calc->mat[i] = new int[M->n-1];
					calc->n = M->n-1;
					calc->ans=0;
				int row = 0,col = 0 ;
				// making the cofactor
				for (int i = 0; i < M->n; ++i)
				{
					for (int j = 0; j < M->n; ++j)
					{
						if(i != k && j != l)
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


				// cout<<"\n This is adjoint of the matrice ";
					cout<<endl;
					for (int i = 0; i < M->n; ++i)

				  	{
				  		for (int j = 0; j < M->n; ++j)
				  		{
				  			cout<<calc->mat[i][j]<< " ";
				  		}
				  		cout<<endl;
				  	}

				s = ((l + k) % 2 == 0) ? 1 : -1 ;

				pthread_create(&tid[count++],&attr,&determinant,(void *) calc);

				for (int i = 0; i < count; ++i)
				{
					 pthread_join(tid[i],NULL);
				}

				cout<<endl<<" "<<calc->ans<<" " <<count << endl ;
				Adj[k][l] = s * calc->ans ;

			  
			}
		}


		// for (int i = 0; i < count; ++i)
		// {
		// 	 pthread_join(tid[i],NULL);
		// }


	}
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



	cout<<"\n Now trying the adjoint "<<endl;

	int **Adj;

	Adj = new int * [M->n];

	for(int i = 0 ; i < M->n ; ++i  )
		Adj[i] = new int [M->n];

	Adjoint(Adj,M);


	cout<<"\n This is adjoint of the matrice "<<endl;
	for (int i = 0; i < M->n; ++i)

  	{
  		for (int j = 0; j < M->n; ++j)
  		{
  			cout<<Adj[i][j]<< " ";
  			Adj[i][j]= (float)Adj[i][j]/(float)D;
  		}
  		cout<<endl;
  	}


  	if(!D)
  		{
  			cout<<"Determinant of  the matrix is Zero inverse not possible"<<endl;
  		return 0;
  		}
  		
	cout<<"\n This is ainverse of the matrice "<<endl;
	for (int i = 0; i < M->n; ++i)

  	{
  		for (int j = 0; j < M->n; ++j)
  		{
  			cout<<Adj[i][j]<< " ";
  			// Adj[i][j]= (float)Adj[i][j]/(float)D;
  		}
  		cout<<endl;
  	}

	return 0;
}


