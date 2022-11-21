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
	
	// get shmid and create shared memory 
	shmid = shmget( (key_t)2345 , 1024 , 0666 ) ;
	shm = shmat( shmid , NULL , 0 );


	// read from the shared memory
	printf("Shared memory read : \n %s " , (char *)shm ) ; 
	
} 
