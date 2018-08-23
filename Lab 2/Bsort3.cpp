#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

template <class T>
void bubble_s(int n,T arr[],char* cmp);

template <class T>
bool comp(char*,T , T );

template <class X>
class Array{
	int size;
	X arr[20];

	public:
	Array(X args[],int s)
	{
		for(int i=0;i<s;i++)
			arr[i]=args[i+2];
	}
};

int main(int argc, char* argv[])

{
	//string args=  str(argv[1]);
	// one for a.out , asce or descending size  not  for this program
	if(argc <4)
		printf("this is not the right way to fo it please fo it again");

	else
	{
		
		//int n=atoi(argv[1]);
		printf("This is the size of the array u entered: %d",(argc-2));	
		
		Array<int>  arr(args,argc-2);
	//	printf("%s\n",argv[3]);

		printf("This is the array\n ");

		for(int i=0;i<argc-2;i++)
			
			cout<<arr.arr[i]<<" ";

		
		bubble_s(arr.s,arr.arr,argv[1]);

		printf("\nThis is the array after sorting:\n");
                 for(int i=0;i<argc-2;i++)
                           
			cout<<arr[i]<<" ";
	}



	
	return(0);
}

template <class T>
bool comp(char * order, T  a , T b)
{
	if(strcmp(order,"ASC"))
		return(a<b);
	else
		return!(a<b);
}

template <class T>
void bubble_s(int n,T arr[], char * cmp)
{
	T temp;
	for(int i=0;i<n;i++)
		for(int j=1;j<n-i;j++)
			if(comp(cmp,arr[j-1],arr[j]))
			{
				temp=arr[j-1];
				arr[j-1]=arr[j];
				arr[j]=temp;	
			}

}
