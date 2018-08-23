#include<iostream>
#include<cstdlib>
#include<cstring>

#include<stdarg.h>
using namespace std;



void bubble_s(char* cmp,...);

bool comp(char*,int , int );

int main(int argc, char* argv[])
{
	//string args=  str(argv[1]);
	// one for a.out , asce or descending size  not  for this program
	if(argc <4)
		cout<<"this is not the right way to fo it please fo it again";

	else
	{
		
		
		cout<<"This is the size you entered:"<<argc-2;	
		int arr[argc-2];
		cout<<argv[2]<<endl;
		for(int i=2 ;i<argc;++i)
		{
			arr[i-2]=atoi(argv[i]);

		}
		cout<<"This is the array\n ";

		for(int i=0;i<argc-2;i++)
			cout<<arr[i]<<" ";
		
		bubble_s(argv[2],argc-2,arr);

		cout<<"This is the array after sorting:\n";
                 for(int i=0;i<argc-2;i++)
                       cout<<arr[i]<<" ";
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


void bubble_s(char * cmp,...)
{
	int temp;

        va_list Array;
        va_start(Array,cmp);
        
	int n=va_arg(Array,int);

	int *arr=va_arg(Array,int*);
        cout<<"this is the address"<<*arr;
	va_end(Array);

	for(int i=0;i<n;i++)
		for(int j=1;j<n-i;j++)
			if(comp(cmp,arr[j-1],arr[j]))
			{
				temp=arr[j-1];
				arr[j-1]=arr[j];
				arr[j]=temp;	
			}

}
