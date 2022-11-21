#include <stdio.h>

void fifo( )
{

	int pageFaults = 0;
	int no_of_frames, m, n, s, no_of_pages;
	
	printf("Enter number of frames: ");
	scanf("%d", & no_of_frames);
	printf("Enter number of pages: ");
	scanf("%d", & no_of_pages);
	
	int incomingStream[no_of_pages];
	printf("Enter page reference string: ");
	for (int i = 0; i < no_of_pages; ++i) {
		scanf("%d", & incomingStream[i]);
	}
	int temp[no_of_frames];
	for (m = 0; m < no_of_frames; m++) {
		temp[m] = -1;
	}
	for (m = 0; m < no_of_pages; m++) 
	{
		s = 0;
		for (n = 0; n < no_of_frames; n++) 
		{
			if (incomingStream[m] == temp[n]) {
				s++;
				pageFaults--;
			}
		}
		pageFaults++;
		if ((pageFaults <= no_of_frames) && (s == 0)) {
			temp[m] = incomingStream[m];
		} else if (s == 0) {
			temp[(pageFaults - 1) % no_of_frames] = incomingStream[m];
		}
		printf("\n");
		printf("%d\t\t\t", incomingStream[m]);
		for (n = 0; n < no_of_frames; n++) {
			if (temp[n] != -1)
				printf(" %d\t", temp[n]);
			else
				printf(" - \t");
		}
	
	}
	printf("\nTotal Page Faults:%d\n", pageFaults);
}


void lru()
{

	int m, n, position, k, l, total_pages;
	int a = 0, b = 0, page_fault = 0;
	printf("Enter the no of pages\n");
	scanf("%d", & total_pages);
	int pages[total_pages];
	printf("Enter the page sequence:\n");
	
	for (int i = 0; i < total_pages; i++) {
		scanf("%d", & pages[i]);
	}
	int total_frames = 3;
	int frames[total_frames];
	int temp[total_frames];
	for (m = 0; m < total_frames; m++) {
		frames[m] = -1;
	}
	for (n = 0; n < total_pages; n++) 
	{
		printf("%d: ", pages[n]);
		a = 0, b = 0;
		for (m = 0; m < total_frames; m++) 
		{
			if (frames[m] == pages[n]) 
			{
				a = 1;
				b = 1;
				break;
			}
		}
		if (a == 0) 
		{
			for (m = 0; m < total_frames; m++) 
			{
				if (frames[m] == -1)
				{
					frames[m] = pages[n];
					b = 1;
					page_fault++;
					break;
				}	
			}
		}
		if (b == 0) 
		{
			for (m = 0; m < total_frames; m++) 
			{
				temp[m] = 0;
			}
			for (k = n - 1, l = 1; l <= total_frames - 1; l++, k--) 
			{
				for (m = 0; m < total_frames; m++) 
				{
					if (frames[m] == pages[k])
					{
						temp[m] = 1;		
					}	
				}
			}
			for (m = 0; m < total_frames; m++)
			{
				if (temp[m] == 0)
					position = m;
			}
			frames[position] = pages[n];
			page_fault++;
		}
		for (m = 0; m < total_frames; m++) 
		{
			if (frames[m] == -1) {
				printf("-\t");
			} else {
				printf("%d\t", frames[m]);
			}	
		}
		printf("\n");
	}
	
	printf("\nTotal Number of Page Faults:\t%d\n", page_fault);
	
}


void optimal()
{

	int no_of_frames, no_of_pages, frames[10], pages[30], temp[10], flag1,
	flag2, flag3, i, j, k, pos,
	max, faults = 0;
	printf("Enter number of frames: ");
	scanf("%d", & no_of_frames);
	printf("Enter number of pages: ");
	scanf("%d", & no_of_pages);
	printf("Enter page reference string: ");
	
	for (i = 0; i < no_of_pages; ++i) {
		scanf("%d", & pages[i]);
	}
	for (i = 0; i < no_of_frames; ++i) {
		frames[i] = -1;
	}
	for (i = 0; i < no_of_pages; ++i) 
	{
		flag1 = flag2 = 0;
		for (j = 0; j < no_of_frames; ++j) {
			if (frames[j] == pages[i]) {
				flag1 = flag2 = 1;
				break;
			}
	
		}
		if (flag1 == 0) {
			for (j = 0; j < no_of_frames; ++j) {
				if (frames[j] == -1) {
					faults++;
					frames[j] = pages[i];
					flag2 = 1;
					break;
				}
			}
		}
		if (flag2 == 0) {
			flag3 = 0;
			for (j = 0; j < no_of_frames; ++j) {
				temp[j] = -1;
				for (k = i + 1; k < no_of_pages; ++k) {
					if (frames[j] == pages[k]) {
						temp[j] = k;
						break;
					}
				}
			}
			for (j = 0; j < no_of_frames; ++j) {
				if (temp[j] == -1) {
					pos = j;
					flag3 = 1;
					break;
				}
			}
			if (flag3 == 0) {
				max = temp[0];
				pos = 0;
				for (j = 1; j < no_of_frames; ++j) {
					if (temp[j] > max) {
						max = temp[j];
						pos = j;
					}
				}
			}
			frames[pos] = pages[i];
			faults++;
		}
		printf("\n");
		for (j = 0; j < no_of_frames; ++j) {
			if (frames[j] == -1) {
				printf("-\t");
			} else {
				printf("%d\t", frames[j]);
			}
		}
	}
	printf("\n\nTotal Page Faults = %d\n", faults);


}


int main()
{

	int ch=0 ;
	while( ch!=4 )
	{
		printf("1. fifo\n2. lru\n3. optimal\n4. exit\n");
		printf("Choice : \n ");
		scanf("%d" , &ch );
		
		switch( ch )
		{
			case 1 : 
				fifo();
				break;
			case 2 :
				lru();
				break;
			case 3 :
				optimal();
				break;
			case 4 :
				printf("Program ended !");
				break;
		}
	
	}
	return 0;
	

}






















