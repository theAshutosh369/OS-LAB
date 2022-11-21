#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

sem_t x,y;
int readercount = 0 , var = 1 ;

void *reader(void* arg)
{
    int rno = *(int*)arg ;
    while( 1 )
    {
    	sleep(2);
    	
    	sem_wait(&x);
    	readercount++;
    	if(readercount==1)
        	sem_wait(&y);
    	sem_post(&x);
    	
    	printf("reader %d read variable as %d \n",rno , var );
    	
    	sem_wait(&x);
    	readercount--;
    	if(readercount==0)
        	sem_post(&y);
    	sem_post(&x);
    }

}

void *writer(void* arg)
{
    int wno = *(int*)arg;
    while(1)
    {
    	sleep(5);
    	
    	sem_wait(&y);
    	var++;
    	printf("writer %d modified variable to %d \n",wno , var );
    	sem_post(&y);
    	if( var == 20 ) 
    	{
    		exit(0);
    	}
    }
}

int main()
{
    int n,i;
    printf("Enter the number of readers:");
    scanf("%d",&n);

    pthread_t readerthreads[n] , writerthreads[n] ;
    
    sem_init(&x,0,1);
    sem_init(&y,0,1);
    
    for(i=0;i<n;i++)
    {
        pthread_create( &readerthreads[i],NULL, reader, &i );
    }
    for(i=0;i<n;i++)
    {
        pthread_create( &writerthreads[i],NULL, writer, &i );
    }
    for(i=0;i<n;i++)
    {
        pthread_join( readerthreads[i],NULL);
    }
    for(i=0;i<n;i++)
    {
        pthread_join( writerthreads[i],NULL);
    }
    return 0;
}
