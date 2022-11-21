#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

int compare( const void * a , const void * b )
{
	return ( *(int *) a - *(int *)b  );
}


void sstf( int n , int arr[] , int l , int cur )
{
	bool done[n] ;
	int sum = 0 ;
	for( int i= 0 ; i<n ; i++ )
	{
		int min = INT_MAX , ind ;
		for( int j = 0 ; j<n ; j++ )
		{
			if( abs( arr[j] - cur ) < min &&  !done[j] )
			{
				min = abs( arr[j] - cur );
				ind = j ;
			}
		}
		sum = sum + min ;
		done[ind] = true;
		cur = arr[ind] ;
		printf("%d -> " , cur ) ;
		
	}
	
	printf("Total head movement is : %d \n \n" , sum ) ;
	
	


}


void scan( int n , int arr[n] , int l , int cur )
{

	qsort( arr , n , sizeof(int) , compare );
	printf("%d -> " , cur );
	for( int i =0 ; i< n ; i++ )
	{
		if( arr[i]> cur ){
		 	printf("%d -> " , arr[i] );
		}
	}
	
	for( int i = n-1 ; i>=0 ; i-- )
	{
		if( arr[i]< cur ){
			printf("%d -> " , arr[i] );
		}
	}
	printf("\n") ;

	// calculation of movement 
	int sum =  ( l-1 - cur ) + ( l-1 - arr[0] ) ;
	printf("total head movement : %d \n \n " , sum );

}


void clook( int n , int arr[n] , int l , int cur )
{

	qsort( arr , n , sizeof(int) , compare );
	printf("%d -> " , cur );
	for( int i =0 ; i< n ; i++ )
	{
		if( arr[i]> cur ){
		 	printf("%d -> " , arr[i] );
		}
	}
	
	int last = 0;
	for( int i = 0 ; i<n  ; i++ )
	{
		if( arr[i]< cur ){
			printf("%d -> " , arr[i] );
			last = arr[i];
		}
	}
	printf("\n") ;

	// calculation of movement 
	int sum =  ( arr[n-1]-cur ) + ( arr[n-1]-arr[0] ) + ( last - arr[0] ) ;
	printf("total head movement : %d \n \n " , sum );
	


}


int main()
{
	int n , ch=0 , l , cur ;
	printf("Enter the number of requests : \n " ) ;
	scanf("%d" , &n );
	
	int arr[n] ;	
	/*printf("enter the values line by line :\n " ) ;
	for( int i = 0 ; i< n ; i++ )
	{
		scanf(" %d" , &arr[i] );
	}*/
	
	arr[0] = 82;
	arr[1] = 170;
	arr[2] = 43;
	arr[3] = 140;
	arr[4] = 24;
	arr[5] = 16;
	arr[6] = 190;
	
	
	printf("Enter the length of track : \n " ) ;
	scanf("%d" , &l );
	
	printf("Enter current position : \n " ) ;
	scanf("%d" , &cur );
	
	
	
	while( ch != 4 )
	{	
		printf("---------------------------------------------- \n") ;
		printf("1. sstf \n2. scan \n3. clook \n4. exit\n " );
		printf("---------------------------------------------- \n") ;
		
		printf("choice : " );
		scanf("%d" , &ch) ;
		
		switch( ch ) 
		{
			case 1 :
				sstf( n , arr , l , cur );
				break;
				
			case 2 :
				scan( n , arr , l , cur );
				break;
				
			case 3 :
				clook( n , arr , l , cur );
				break;
				
			case 4 :
				printf("program ended !! \n" );
				break;	
		}
		
	}
	
	return 0;
	
	
}
	
	
	
	
