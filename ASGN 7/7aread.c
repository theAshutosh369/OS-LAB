#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<sys/types.h>
#include<sys/stat.h> 
#include<fcntl.h>

int main()
{
	int fd1 , fd2 ; 
	char * f1loc = "fifo1";
	char * f2loc = "fifo2";
	char str[100] , buffer[200];
	
	mkfifo( f1loc , 0666 );
	printf("Enter the string : \n " );
	fgets( str , 100 , stdin );
	
	fd1 = open( f1loc , O_WRONLY );
	if( write( fd1 , str , strlen( str )+1 ) == -1  )
	{
		printf("Error while writing to fifo 1 from process 1\n " );
		return 1;
	}
	close( fd1 );
	
	fd2 = open( f2loc , O_RDONLY );
	if( read( fd2 , buffer , 150 ) == -1 ) 
	{
		printf("Error while reading the fifo 2 from process 1\n " );
		return 1;
	}
	close( fd2 );
	
	printf("message in fifo 2 from process 2 : \n %s  \n " , buffer );
	return 0;
	
}	
