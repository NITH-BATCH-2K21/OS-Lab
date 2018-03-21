#include<stdio.h>

int num_of_frames, frame[100], hit = 0, miss = 0, pages[100], num_of_pages;
static int index = 0;

void disp();
void sched(int page_no);

int main()
{
	printf("This program simulates the FIFO Page replacement algorithm\n\n");
	printf("Enter the total number of frames\n");

	scanf("%d", &num_of_frames);

	printf("Enter the total number of page requests\n");
	scanf("%d", &num_of_pages);

	// IMP: initialize the frmaes with -1 initially, what if a page number 0 request is performed!!
	int i;
	for(i=0;i<num_of_frames;++i)
		frame[i] = -1;

	for(i=0;i<num_of_pages;++i)
		scanf("%d", &pages[i]);

	int page_no;
	for(i=0;i<num_of_pages;++i)
		sched(pages[i]);

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
		++hit;
		printf("Access to page-%d is a hit\nHits = %d\nMisses = %d\n", page_no, hit, miss);
		disp();
		return;
	}

	miss++;
	printf("Access to page-%d is a miss\nTotal number of hits till now = %d\nTotal misses = %d\n", page_no, hit, miss);
	int j;
	// checking for empty slot
	for(j=0;j<num_of_frames;++j)
	{
		if(frame[j] == -1)
		{
			frame[j] = page_no;
			++index;
			disp();
			return;
		}
	}
	
	int tmp[100];
	for(j=0;j<100;++j)
		tmp[j] = 1e9;
	
	j = hit + miss - 1;

	for(;j<num_of_pages;++j)
	{
		if(tmp[pages[j]] > j)
			tmp[pages[j]] = j;
	}

	printf("index = %d\n", index);
	printf("tmp array:\n");
	for(j=0;j<10;++j)
		printf("%d ", tmp[j]);
	printf("\n");

	// finding the maximum valoue among those present in the frames
	int pos = -1, maxi = -1;
	for(j=0;j<num_of_frames;++j)
	{
		if(tmp[frame[j]] > maxi)
		{
			maxi = tmp[frame[j]];
			pos = j;
		}
	}

	frame[pos] = page_no;
	++index;
	disp();
}