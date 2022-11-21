#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int compare( const void *a , const void *b )
{
	return (  *(int*)a - *(int*)b   );
}

int Rcompare( const void *a , const void *b )
{
	return (  *(int*)b - *(int*)a   );
} 

void print( int arr[] , int n )
{
	for( int i= 0 ; i<n ; i++ )
	{
		printf("%d " , arr[i] );
	}
}
void forksorting( int arr[] , int n )
{
	pid_t pid = fork();
	if( pid!=0 )
	{
		printf("\n\n--------PARENT PROCESS STARTED-------------\n" );
		printf("id of Parent : %d \n" , pid );
		
		printf("sorted array in ascending order : \n" );
		qsort( arr , n , sizeof(int) , compare );
		print( arr , n );
		printf("\n");
		printf("--------PARENT PROCESS ENDED-------------\n" );
	}
	else{
		printf("\n\n--------CHILD PROCESS STARTED-------------\n" );
		printf("id of child : %d \n" , pid );
		
		printf("sorted array in descending order : \n" );
		qsort( arr , n , sizeof(int) , Rcompare );
		print( arr , n );
		printf("\n");
		printf("--------PARENT PROCESS ENDED-------------\n" );
	}

}

void orphan()
{
	int pid = fork();
	int x= 50 ;
	
	if( pid==0 )
	{
		printf("	In child process with pid : %d \n" , (int)getpid()  );
		printf("	Id of parent of child process : %d \n" , (int)getppid()  );
		x += 5;
		printf("	Value of x : %d \n" , x );
		printf("	child process going to sleep ! \n" );
		
		sleep( 10 );

		printf("	Resuming child process after wait ! \n" );
		x += 5;
		printf("	Value of x : %d \n" , x );
		printf("	In child process with pid changed to : %d \n",(int)getpid());
		printf("	Id of changed parent of child process : %d \n",(int)getppid());
		printf("	Exiting child process ! \n");
	}
	else{
	
		printf("In parent process with pid : %d \n" , (int)getpid()  );
		printf("Id of parent of parent process : %d \n" , (int)getppid()  );
		x += 100;
		printf("Value of x : %d \n" , x );
		printf("Parent process going to sleep ! \n" );
		
		sleep( 10 );

		printf("Resuming parent process after wait ! \n" );
		x += 100;
		printf("Value of x : %d \n" , x );
		printf("Exiting parent process ! \n");
		exit(0) ;
		
	}
}

void zombie()
{
	int pid = fork();
	int x = 50 ;
	
	if( pid==0 )
	{
		printf("	id of child process : %d \n" , (int)getpid() );
		printf("	id of parent of child process is : %d \n" , (int)getppid() );
		x=x+5;
		printf("	value of x : %d \n" , x );
		printf("	exiting child ! \n");
		exit( 0 );	
	}
	else
	{
		printf("id of parent process : %d \n" , (int)getpid());
		printf("id of parent of parent process : %d \n" , (int)getppid() );
		x=x+100 ;
		printf("value of x : %d \n" , x );
		printf("parent process is going to sleep \n");
		
		sleep(10);
		
		printf("Resuming parent process after wait !! \n");
		x=x+100 ;
		printf("value of x : %d \n" , x );
		printf("Exiting parent \n");		
	}
}


int main()
{
	int  n , arr[n] ;
	printf("Enter the number of items : \n " );
	scanf("%d" , &n );
	
	printf("Enter the elements line by line : \n " );
	for( int i = 0 ; i<n ; i++ )
	{
		scanf("%d" , &arr[i] );
	}
	
		int ch ;
		printf("\n\n");
    		printf("-------------------Menu---------------------\n");
    		printf("1. forksorting\n");
    		printf("2. Orphan process\n");
    		printf("3. Zombie process\n");
    		printf("4. Exit\n");
    
		printf("Enter choice : " );
		scanf("%d" , &ch );
		
		switch( ch ) 
		{
		
			case 1 :
				forksorting( arr , n );
				break;
			case 2 :
				orphan();
				break;
			case 3 : 
				zombie();
				break;
			default : 
				return 0 ;
				break;
		} 

	return 0;
}
