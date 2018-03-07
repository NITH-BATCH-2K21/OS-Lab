#include<stdio.h>
#include<string.h>

struct process
{
	int pid, size, left, right, alloc;
};

struct process proc[100];
int usedMem = 0, totalMemory, num_proc = 0;
int base[10000], flag = 0;

void disp()
{
	int i;
	printf("PID\talloc?\tSize\tLeft\tRight\n");
	for(i=1;i<=num_proc;++i)
	{
		printf("%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].alloc, proc[i].size, proc[i].left, proc[i].right);
	}
}

int totalExternalFrag()
{
	return (totalMemory - usedMem);
}

// function for debugging purposes only
void disp_base(){
	int i;
	for(i=0;i<totalMemory;++i)
		printf("%d ", base[i]);
	printf("\n");
}

void sched(int index)
{
	printf("Scheduling process %d\n", index);
	int i, j;
	int size = proc[index].size;
	for(i=0;i<totalMemory;++i)
	{
		if(base[i] == -1)
		{
			j = i;
			while(base[j] == -1 && j < totalMemory)
				++j;

			if((j - i) >= size)
			{
				proc[index].alloc = 1;
				usedMem += size;
				proc[index].left = i;
				proc[index].right = i + size;
				int k;
				for(k = proc[index].left;k<proc[index].right;++k)
					base[k] = index;

				printf("Process %d has been allocated\n", index);
				return;
			}
		}
	}

	printf("Process %d cannot be allocated\n. Total external fragment = %d\n", index, totalExternalFrag());
	return;
}

void best_sched(int index)
{
	printf("Scheduling process %d\n", index);
	int i, j;
	int size = proc[index].size;
	int best = -1, pos_l = -1, pos_r = -1;
	for(i=0;i<totalMemory;++i)
	{
		if(base[i] == -1)
		{
			j = i;
			while(base[j] == -1 && j < totalMemory)
				++j;

			if((j - i) >= size && (j - i) > best)
			{
				best = j - i;
				pos_l = i;
				pos_r = pos_l + size;
				
			}
		}
	}

	if(pos_l == -1)
		printf("Process %d cannot be allocated\n. Total external fragment = %d\n", index, totalExternalFrag());
	else
	{
		proc[index].alloc = 1;
		usedMem += size;
		proc[index].left = pos_l;
		proc[index].right = pos_l + size;
		int k;
		for(k = proc[index].left;k<proc[index].right;++k)
			base[k] = index;

		printf("Process %d has been allocated\n", index);
	}

	return;
}

void dealloc(int pid)
{
	int i;
	proc[pid].alloc = 0;
	usedMem -= proc[pid].size;

	for(i=0;i<totalMemory;++i)
	{
		if(base[i] == pid)
			base[i] = -1;
	}

	printf("Process %d has been deallocated\n", pid);
	disp();
}


int main()
{
	int i, tmp_size, j, dealloc_pid, c;
	for(i=0;i<10000;++i)
		base[i] = -1;

	printf("Enter the total memory\n");
	scanf("%d",&totalMemory);

	printf("\n");


	
	num_proc = 1;
	
	
	while(1)
	{	
		//disp();
		printf("Enter 1 for insert and 2 for deletion\n");
		scanf("%d", &c);
		if(c == 1)
		{
			printf("Enter the size of the process\n");
			scanf("%d", &proc[num_proc].size);
			proc[num_proc].pid = num_proc;
			proc[num_proc].alloc = 0;

			if(proc[num_proc].size > (totalMemory - usedMem))
			{
				printf("Insufficient Memory. Cannot allocate. Choose a process to deallocate\n");
				flag = 1;
				scanf("%d", &dealloc_pid);
				dealloc(dealloc_pid);
			}

			if(flag == 0)
				sched(num_proc);
			else
				best_sched(num_proc);

			disp();
			++num_proc;
			printf("Total Free Space = %d\n", totalExternalFrag());

			printf("\n");
		}
		else if(c == 2)
		{
			printf("Enter a process ID for dealloc\n");
			flag = 1;
			scanf("%d", &c);
			dealloc(c);
			disp();
		}
	}
	
	return 0;
}
