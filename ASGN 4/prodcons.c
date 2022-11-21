#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

#define buffersize 5 

int in = 0 , out = 0 , itemno = 0 ;
sem_t empty , full;
pthread_mutex_t mutex;
int buff[ buffersize ] ;

void *producer( void *i )
{
	int val;
	sem_getvalue( &empty , &val );
	
	if( val<=0 ){
		printf("Producer waiting ........ \n " );
		return NULL;
	}
	sem_wait( &empty );
	pthread_mutex_lock( &mutex );
	buff[in] = itemno ;
	itemno++;
	printf("Producer %ld : Inserted item %d at %d \n " , (long)i , buff[in] , in );
	in = (in+1) % buffersize ;
	pthread_mutex_unlock( &mutex );
	sem_post( &full );
}

void *consumer( void *i )
{
	int val;
	sem_getvalue( &full , &val );
	if( val<=0 ){
		printf("Consumer waiting ........ \n " );
		return NULL;
	}
	sem_wait( &full );
	pthread_mutex_lock( &mutex );
	
	printf("Consumer %ld : Consumed item %d at %d \n " , (long)i , buff[out] , out );
	out = (out+1) % buffersize ;
	pthread_mutex_unlock( &mutex );
	sem_post( &empty );
}

int main()
{
	long int i = 0 , j=0;
	int prod = 5 , cons = 5 , ch , t ;
	
	pthread_mutex_init( &mutex , NULL );
	sem_init( &empty , 0 , buffersize );
	sem_init( &full , 0 , 0 );
	
	pthread_t producers[prod] , consumers[cons] ;
	
	while( 1 )
	{
		printf("Enter 0 for consumer\n");
        	printf("Enter 1 for producer\n");
        	scanf("%d", &ch);

       		switch (ch)
        	{
        		case 0:

           			t = pthread_create(&consumers[i], NULL, consumer, (void *)i);
            			if (t != 0)
               				printf("Error in thread creation : %d\n", t);

            			t = pthread_join(consumers[i], NULL);
           			if (t != 0)
                			printf("Error while joining threads : %d\n", t);

            			i++;
            			break;

        		case 1:

           			 t = pthread_create(&producers[j], NULL, producer, (void *)j );
            			if (t != 0)
              				  printf("Error in thread creation : %d\n", t);

           			 t = pthread_join(producers[j], NULL);
           			 if (t != 0)
                			printf("Error while joining threads : %d\n", t);

            			j++;
            			break;

        		default:
           			return 0;	
            			break;
        	}	
	}
	
	pthread_mutex_destroy( &mutex );
	sem_destroy ( &empty );
	sem_destroy( &full );
	
	return 0;

}

