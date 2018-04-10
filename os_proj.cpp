#include<bits/stdc++.h>
#include<fcntl.h>
#include<unistd.h>
#include<semaphore.h>
#include<sys/types.h>
#include<pthread.h>
using namespace std;
#define MAX_RESOURCES 5
int available_resources=MAX_RESOURCES
int increase_count()
{
	available_resources+=count;
}
int decrease_count(int count)
{
	if(available_resources<count)
	return(-1);
	else
	{
		available_resources-=count;
		return(0);
	}
}
void * process1(int count)
{
	while(decrease_count(count)==-1);
	
	decrease_count(count);
	
	sleep(0);
	
	increase_count(count);
}


int main()
{
	int n;
	pthread_t t[20];
	cout<<"Enter how many process you want to create: "<<endl;
	cin>>n;
	
	int resource[20];
	
	for(int i=0;i<n;i++)
	cin>>resource[i];
	
	for(int i=0;i<n;i++)
	{
		pthread_create(&t[i],NULL,process1,resource[i]);
		pthread_join(t[i],NULL);
	}
	
}
