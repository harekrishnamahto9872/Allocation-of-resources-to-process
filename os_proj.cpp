#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<semaphore.h>
#include<sys/types.h>
#include<pthread.h>
#define MAX_RESOURCES 5 //Maximum resource of System
sem_t sem;         // Semaphore to prevent race condition
int available_resources=MAX_RESOURCES;   
int increase_count(int count)     // After process completion increments resource count
{
	available_resources+=count;
	return(0);
}
int decrease_count(int count) // Decrements resource count after allocating resource to process
{
	if(available_resources<count)
	return(-1);
	else
	{
		available_resources-=count;
		return(0);
	}
}
int k=0;
void * process1(void *c) //function run during processs
{
	k++;
	int j=k;
	int count=(int)c;
	
	sem_wait(&sem); // locking semaphore

	while(decrease_count(count)==-1);
	
	decrease_count(count);
	printf("\n\nProcess %d running by taking %d no.of resources\nAvailable Resources Now: %d",j,count,available_resources);

	
	sleep(1);
	
	increase_count(count);
	sem_post(&sem); //unlocking semaphore
	
	printf("\n\nProcess %d finished releasing %d no.of resources\nAvailable Resources Now: %d",j,count,available_resources);
}


int main()
{
	sem_init(&sem,0,5); //initalizing semaphore
	int n,i;
	pthread_t t[20];
	printf("Enter how many peocess u want: "); //taking no. of process to run concurrently
	scanf("%d",&n);
	
	int resource[20];
	
	for(i=0;i<n;i++)
	{
		printf("Enter no.of resources for process %d: ",i+1); // Taking need of each process
		scanf("%d",&resource[i]);
	} 
	printf("\nMAX RESOURCES AVAILABLE: %d",MAX_RESOURCES);  // Printing MAX resources Resources before start of any process
	for(i=0;i<n;i++)
	{
		pthread_create(&t[i],NULL,process1,(void *)(resource[i]));
	}
	for(i=0;i<n;i++)
	{
		pthread_join(t[i],NULL);
	}
	
	printf("\n\nAVAILABLE RESOURCES AFTER ALL PROCESS HAVE FINISHED : %d",available_resources); // Printing Available Resources after completion of all process
	
}
