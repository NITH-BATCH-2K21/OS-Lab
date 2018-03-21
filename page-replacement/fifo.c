#include<stdio.h>

int num_of_frames, frame[100], hit = 0, miss = 0;
static int index = 0;

void disp();
void sched(int page_no);

int main()
{
	printf("This program simulates the FIFO Page replacement algorithm\n\n");
	printf("Enter the total number of frames\n");

	scanf("%d", &num_of_frames);

	// IMP: initialize the frmaes with -1 initially, what if a page number 0 request is performed!!
	int i;
	for(i=0;i<num_of_frames;++i)
		frame[i] = -1;

	int page_no;
	while(1)
	{
		printf("Enter the requested page number\n");
		scanf("%d", &page_no);
		if(page_no == -1)
			break;
		sched(page_no);
	}

	printf("Total number of Misses = %d\nTotal hits = %d\n\n", miss, hit);
	
}

void disp()
{
	int i;
	printf("Contents of the frame\n");
	for(i=0;i<num_of_frames;++i)
		printf("%d ", frame[i]);
	printf("\n");
}

void sched(int page_no)
{
	int i;
	// search for page_no in the frame

	for(i=0;i<num_of_frames;++i)
	{
		if(frame[i] == page_no)
			break;
	}

	if(i != num_of_frames)
	{
		++hit;
		printf("Access to page-%d is a hit\nTotal number of hits till now = %d\nTotal misses = %d\n", page_no, hit, miss);
		disp();
		return;
	}

	miss++;
	printf("Access to page-%d is a miss\nTotal number of hits till now = %d\nTotal misses = %d\n", page_no, hit, miss);
	
	frame[index%num_of_frames] = page_no;
	++index;
	disp();
}