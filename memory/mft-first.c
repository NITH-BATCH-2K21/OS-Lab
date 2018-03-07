#include<stdio.h>

struct partition
{
	int size, alloc, process_num;
};

struct process
{
	int pid, size, alloc, partition_num, frag;
};

int num_partitions,  num_process;
struct partition part[100];
struct process proc[100];

void disp()
{
	int i;
	printf("Part\tAlloc?\tProcessID\n");
	for(i=1;i<=num_partitions;++i)
	{
		printf("%d\t%d\t%d\n", part[i].size, part[i].alloc, part[i].process_num);
	}
}

void disp_proc()
{
	int i;
	printf("Proc\tAlloc?\tSize\tParti\tInternal Frag\n");
	for(i=1;i<=num_process;++i)
	{
		printf("%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].alloc, proc[i].size, proc[i].partition_num, proc[i].frag);
	}
}

int totalInternalFrag()
{
	int i, sum = 0;
	for(i=1;i<=num_process;++i)
	{
		if(proc[i].alloc == 0)
			continue;
		sum += proc[i].frag;
	}

	return sum;
}

int totalExternalFrag()
{
	int i, sum = 0;
	for(i=1;i<=num_partitions;++i)
	{
		if(part[i].alloc == 1)
			continue;
		sum += part[i].size;
	}

	return sum;
}

void sched()
{
	int i, j;
	printf("sched function has been called\n");
	
	// deallocating all partitions  and processes again
	for(i=1;i<=num_partitions;++i)
	{
		part[i].alloc = 0;
		part[i].process_num = -1;
	}

	for(i=1;i<=num_process;++i)
	{
		proc[i].alloc = 0;
		proc[i].partition_num = -1;
		proc[i].frag = -1;
	}

	for(i=1;i<=num_process;++i)
	{
		int pos = -1;
		for(j=1;j<=num_partitions;++j)
		{
			if(part[j].alloc)
				continue;

			if(part[j].size >= proc[i].size)
			{
				pos = j;
				break;
			}
		}

		if(pos != -1) 
		{
			proc[i].alloc = 1;
			proc[i].partition_num = pos;
			
			part[pos].alloc = 1;
			part[pos].process_num = i;

			proc[i].frag = part[pos].size - proc[i].size;
		}
	}

	printf("Completed scheduling\n");
	disp_proc();
	disp();
	printf("Total Internal Fragments = %d\n", totalInternalFrag());
	printf("Total External Fragments = %d\n", totalExternalFrag());
}

void first_sched()
{
	int i, j;
	for(i=1;i<=num_process;++i)
	{
		int pos = -1;
		for(j=1;j<=num_partitions;++j)
		{
			if(part[j].alloc)
				continue;

			if(part[j].size >= proc[i].size)
			{
				pos = j;
				break;
			}
		}

		if(pos != -1) 
		{
			proc[i].alloc = 1;
			proc[i].partition_num = pos;
			
			part[pos].alloc = 1;
			part[pos].process_num = i;

			proc[i].frag = part[pos].size - proc[i].size;
		}
	}

	printf("Completed scheduling\n");
	disp_proc();
	disp();
	printf("Total Internal Fragments = %d\n", totalInternalFrag());
	printf("Total External Fragments = %d\n", totalExternalFrag());
}


void sched_mod(int c, int tbs)
{
	/*
	Args:
	c : Partition that is freed from the process
	tbs : Process ID that must be scheduled

	This functions places the specified process in that partition slot
	*/

	printf("sched_mod function: Partition to free = %d\tProcess to be allocated = %d\n", c, tbs);

	if(proc[tbs].size <= part[c].size)
	{
		// schedule the damn thing
		proc[tbs].alloc = 1;
		proc[tbs].partition_num = c;
		proc[tbs].frag = part[c].size - proc[tbs].size;

		part[c].alloc = 1;
		part[c].process_num = tbs;
	}
	else
		sched();
	disp_proc();
	disp();
	// if the size requirement isn't satisfied, call the complete scheduling procedure again
}

int main()
{
	int i;
	printf("Enter number of partitions and processes\n");
	scanf("%d%d", &num_partitions, &num_process);

	for(i=1;i<=num_partitions;++i)
	{
		printf("Enter size of partition %d\n", i);
		scanf("%d", &part[i].size);
		part[i].alloc = 0;
		part[i].process_num = -1;
	}

	for(i=1;i<=num_process;++i)
	{
		printf("Enter size of process %d\n", i);
		proc[i].pid = i;
		scanf("%d", &proc[i].size);
		proc[i].alloc = 0;
		proc[i].partition_num = -1;
		proc[i].frag = -1;
	}

	first_sched();

	while(1)
	{
		int c = 0;
		printf("Do you want to continue? 1/0");
		scanf("%d", &c);

		if(c == 0)
			break;

		int tmp;

		if(totalExternalFrag() == 0)
		{
			printf("Not enough space. Which process must leave?\n");
			scanf("%d", &c);
			tmp = proc[c].partition_num;
			part[tmp].process_num = -1;
			part[tmp].alloc = 0;
			proc[c].alloc = 0;
			proc[c].partition_num = -1;
			proc[c].frag = -1;

			num_process++;
			i = num_process;
			printf("Enter size of new process %d\n", i);
			proc[i].pid = i;
			scanf("%d", &proc[i].size);
			proc[i].alloc = 0;
			proc[i].partition_num = -1;
			proc[i].frag = -1;

			sched_mod(tmp, num_process);
			continue;
		}


		num_process++;
		i = num_process;
		printf("Enter size of new process %d\n", i);
		proc[i].pid = i;
		scanf("%d", &proc[i].size);
		proc[i].alloc = 0;
		proc[i].partition_num = -1;
		proc[i].frag = -1;

		sched();	
	}

	return 0;
}