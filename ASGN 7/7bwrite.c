#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>

int main()
{

	int shmid ;
	char buff[100];
	void *shm ;
	
	// get shmid and created shared memory 
	shmid = shmget( (key_t)2345 , 1024 , 0666 | IPC_CREAT ) ;
	shm = shmat( shmid , NULL , 0 );
	
	
	// write the data to shared memory 
	printf("read data : \n ");
	read( 0 , buff , 100 ) ;
	strcpy( shm , buff ) ;
	
	
	
	printf("you wrote : \n %s " , (char *)shm ) ; 
	
} 
