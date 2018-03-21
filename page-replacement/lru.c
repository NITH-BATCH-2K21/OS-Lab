#include<stdio.h>

int num_of_frames, frame[100], hit = 0, miss = 0, freqs[100];
static int index = 1;

void disp();
void sched(int page_no);

int main()
{
	printf("This program simulates the LFU Page replacement algorithm\n\n");
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
		printf("%d\n", frame[i]);
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
		freqs[page_no] = index;
		++hit;
		printf("Access to page-%d is a hit\nHits = %d\nMiss = %d\n", page_no, hit, miss);
		disp();
		++index;
		return;
	}

	miss++;
	printf("Access to page-%d is a miss\nHits = %d\nMiss = %d\n", page_no, hit, miss);	
	
	// finding the page with lowest value of index, using the last_used array
	int tmp = 1e9, pos = -1;
	// finding the victim frame

	for(i=0;i<num_of_frames;++i)
	{
		if(freqs[frame[i]] < tmp)
		{
			tmp = freqs[frame[i]];
			pos = i;
		}
	}

	printf("Frame-%d is the victim, it is written to the secondary memory\n", pos);
	freqs[page_no] = index;
	frame[pos] = page_no;
	
	disp();
	++index;
}