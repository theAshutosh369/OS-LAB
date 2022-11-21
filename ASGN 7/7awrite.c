#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>

int main()
{
	FILE * tfd;
	int fd1 , fd2 ;
	char * f1loc = "fifo1";
	char * f2loc = "fifo2";
	char temp[200] , buff[100] ;
	
	
	
	fd1 = open( f1loc , O_RDONLY ) ;
	if( read( fd1 , buff , 100 ) == -1 )
	{
		printf( "error while reading fifo1 from process 2\n" );
		return 1;
	}
	close( fd1 );
	printf( " message in fifo1 from process 1 : \n %s \n  " , buff );
	
	
	int i=0 , w=1 , l =1 , c=0 ;
	while( buff[i]!='\0' )
	{
		if( buff[i] == '.' ) l++ ;
		if( buff[i] == ' ' ) w++ ;
		c++;
		i++;
	} 
	c--;
	
	printf("Information about the entered string\n");
 	printf("No of lines: %d\n", l);
 	printf("No of words: %d\n", w);
 	printf("No of characters: %d\n", c);
 
 
	tfd = fopen( "text.txt", "w");
 	fprintf(tfd, "Data written in txt file\nInformation about the entered string\n");
 	fprintf(tfd, "No of lines: %d\n", l);
 	fprintf(tfd, "No of words: %d\n", w);
 	fprintf(tfd, "No of characters: %d\n", c);
 	fclose(tfd);
	
	
	
	
	tfd = fopen( "text.txt" , "r" );
	i=0 ;
	while( 1 )
	{
		if( feof( tfd ) ) {
			break;
		}
		temp[i++] = fgetc( tfd );
	}
	temp[i++] = '\0' ;
	fclose( tfd );
	
	
	
	
	
	mkfifo( f2loc , 0666 );
	
	fd2 = open( f2loc , O_WRONLY );
	if( write( fd2 , temp , strlen( temp ) + 1 )  == - 1 )
	{
		printf( "error while writing to fifo2 from process 2 \n");
		return 1;
	}
	close( fd2 ) ;
	
	
	
	
	
	return 0;
	
	
	
}











