#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;


void bubble_s(int n,int arr[],char* cmp);

bool comp(char*,int , int );

int main(int argc, char* argv[])
{
	//string args=  str(argv[1]);
	// one for a.out , asce or descending size  not  for this program
	if(argc <4)
		printf("this is not the right way to fo it please fo it again");

	else
	{
		
		int n=atoi(argv[1]);
		printf("This is the size you entered: %d",n);	
		int arr[n];
		printf("%s\n",argv[3]);
		for(int i=3 ;i<argc;++i)
		{
			arr[i-3]=atoi(argv[i]);

		}
		printf("This is the array\n ");

		for(int i=0;i<n;i++)
			printf("%d ",arr[i]);
		
		bubble_s(n,arr,argv[2]);

		printf("This is the array after sorting:\n");
                 for(int i=0;i<n;i++)
                        printf("%d ",arr[i]);
	}



	
	return(0);
}


bool comp(char * order, int a , int b)
{
	if(strcmp(order,"ASC"))
		return(a<b);
	else
		return!(a<b);
}


void bubble_s(int n, int arr[], char * cmp)
{
	int temp;
	for(int i=0;i<n;i++)
		for(int j=1;j<n-i;j++)
			if(comp(cmp,arr[j-1],arr[j]))
			{
				temp=arr[j-1];
				arr[j-1]=arr[j];
				arr[j]=temp;	
			}

}
