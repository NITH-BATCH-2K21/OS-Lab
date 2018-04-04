#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define mem_size 30

struct file
{
	int id, size, start, valid, alloc;
};

int numFiles = 0, mem[mem_size]; //  mem has blocks of memory
void add();
void remove_file(int);
int space();
void fit();
void disp();
void disp_mem();
void search();

struct file f[1000];
int blockSize, numBlocks;

int main()
{
	int total, i;
	for(i=0;i<mem_size;++i)
		mem[i] = -1;

	printf("Enter the total memory\n");
	scanf("%d", &total);

	printf("Enter the size of each block\n");
	scanf("%d", &blockSize);

	numBlocks = total/blockSize;
	printf("Number of blocks = %d\n", numBlocks);

	while(1)
	{
		printf("\n\nEnter your choice\n1. ADD\n2. remove_file\n3. Search\n");
		int c;
		scanf("%d", &c);

		if(c == 1)
		{
			add();
			fit();
		}
		else if(c == 2)
		{
			printf("Enter the index of the file to be removed\n");
			int tmp;
			scanf("%d", &tmp);
			remove_file(tmp);
		}
		else
			search();

		disp();
	}
	return 0;
}

void fit()
{
	int i;
	for(i=0;i<numFiles;++i)
	{
		if(f[i].alloc == 0 && f[i].valid == 1) // this file needs to be allocated
		{
			int reqBlocks = f[i].size;
			int freeSpace = space();
			if(reqBlocks > freeSpace)
			{
				printf("Cannot allocate file - %d due to lack of memory\n", i);
				

				if(freeSpace > reqBlocks)
					printf("External fragmentation = %d\n", freeSpace);

				disp_mem();
				continue;
			}

			int j = 0, flag = 0; // traverse through the memory
			for(j=0;j<numBlocks;++j)
			{
				if(mem[j] == -1)
				{
					int p;
					p = j;
					while(mem[p] == -1 && p < numBlocks)
					++p;

					if(p - j >= reqBlocks)
					{
						flag = 1;
						break;
					}
				}
			}

			if(flag == 0)
			{
				printf("Cannot allocate file - %d due to lack of memory\n", i);
				int freeSpace = space();

				if(freeSpace > reqBlocks)
					printf("External fragmentation = %d\n", freeSpace);

				disp_mem();
				continue;
			}

			f[i].start = j;
			f[i].alloc = 1;
			printf("File - %d has been allocated starting from block - %d\n", i,  j);

			// setting the memory to index-i
			int p = 0;
			for(;p<f[i].size;++p, ++j)
				mem[j] = i;

			disp_mem();
		}
	}
}

void remove_file(int index)
{
	f[index].valid = 0;
	f[index].alloc = 0;
	f[index].start = -1;

	// --numFiles; =========> DONOT DECREMENT THE NUMBER OF FILES -  KEEP TRACK OF ALL FILES
	int j;
	for(j = 0;j < mem_size;++j)
	{
		if(mem[j] == index)
			mem[j] = -1;
	}

	disp_mem();
}

void add()
{
	printf("Enter the size of the new file - %d\n", numFiles);
	scanf("%d", &f[numFiles].size);
	f[numFiles].size = ceil(f[numFiles].size/blockSize);
	f[numFiles].valid = 1;
	f[numFiles].alloc = 0;
	f[numFiles].start = -1;
	f[numFiles].id = numFiles;

	++numFiles;
}

int space()
{
	int i, sum = 0;
	for(i=0;i<numBlocks;++i)
	{
		if(mem[i] == -1)
			++sum;
	}

	printf("SPACE function: Number of free blocks = %d\n", sum);
	return sum;
}

void disp()
{
	int i;
	printf("\nFile Table:\n");
	for(i=0;i<numFiles;++i)
	{
		printf("FileID = %d\tSize = %d\tValid? = %d\tAllocated? = %d\tStart Block = %d\n", f[i].id, f[i].size, f[i].valid, f[i].alloc, f[i].start);
	}
}

void disp_mem()
{
	int i;
	printf("\nmemory:\n");
	for(i=0;i<numBlocks;++i)
		printf("%d ", mem[i]);
	printf("\n");
}

void search()
{
	printf("Enter the index of file to be searched\n");
	int i;
	scanf("%d", &i);

	if(i > numFiles || i < 0)
	{
		printf("invalid input\n");
		return;
	}
	printf("FileID = %d\tSize = %d\tValid? = %d\tAllocated? = %d\tStart Block = %d\n", f[i].id, f[i].size, f[i].valid, f[i].alloc, f[i].start);
}