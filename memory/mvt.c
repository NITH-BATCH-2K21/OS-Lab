#include<stdio.h>
#include<string.h>

struct process
{
	int pid, size, left, right, alloc;
};

struct process proc[100];
int usedMem = 0, totalMemory, num_proc = 0;
int base[10000];

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
}


int main()
{
	int i, tmp_size, j, dealloc_pid;
	for(i=0;i<10000;++i)
		base[i] = -1;

	printf("Enter the total memory\n");
	scanf("%d",&totalMemory);

	printf("before alloc:\n");
	for(j = 0;j<totalMemory;++j)
		printf("%d ",base[j]);
	printf("\n");


	
	num_proc = 1;
	
	
	while(1)
	{	
		//disp();
		printf("Enter the size of the process\n");
		scanf("%d", &proc[num_proc].size);
		proc[num_proc].pid = num_proc;
		proc[num_proc].alloc = 0;

		if(proc[num_proc].size > (totalMemory - usedMem))
		{
			printf("Insufficient Memory. Cannot allocate. Choose a process to deallocate\n");
			scanf("%d", &dealloc_pid);
			dealloc(dealloc_pid);
		}

		sched(num_proc);
		disp();
		++num_proc;
		printf("Total Free Space = %d\n", totalExternalFrag());
		printf("Base array:\n");

		for(j = 0;j<totalMemory;++j)
			printf("%d ",base[j]);
		printf("\n");
	}
	
	return 0;
}