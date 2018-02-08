// Non-Preemptive Scheduling using Arrival Time, Priority, Pid as yardsticks in that order
#include <stdio.h>
#include <stdlib.h>



struct process
{
	int pid, burst_time, priority, wait, turnAround, arrTime;
};

void sort_p(struct process *p, int a, int b);  // sorts based on the burst times, for records with equal arrival times



void func(struct process *ps, int n);
void sort(struct process *ps, int n);

int main()
{
	int n, i, j;
    printf("Enter the number of processes\n");
    scanf("%d", &n);

    struct process ps[n];
    
    for(i=0;i<n;++i)
    {
    	ps[i].pid = i + 1;
    	
    

    	printf("Enter the Burst Time of process - %d\n", i + 1);
    	scanf("%d", &ps[i].burst_time);

    	printf("Enter the Arrival Time of process - %d\n", i + 1);
    	scanf("%d", &ps[i].arrTime);

    	printf("Enter the Priority of process - %d\n", i + 1);
    	scanf("%d", &ps[i].priority);
    }

    sort(ps, n); // sorts the records based on arrival times first

    i = 0;
    // sorts based on the burst times, for records with equal arrival times
    while(i < n - 1)
	{
		if(ps[i].arrTime == ps[i + 1].arrTime)
		{
			j = i + 1;
			while(ps[i].arrTime == ps[j].arrTime && j < n) ++j;
			//printf("DEBUG INFO:\ni = %d\tj = %d\n", i, j);
			sort_p(ps, i, j); // sorts according to priority
			i = j;
		}
		else 
			++i;
	}


/*
    printf("Entered Information:\n");
    printf("Process ID\tBurst Time\tPriority\n");
    for(i=0;i<n;++i)
    	printf("\t%d\t\t%d\t\t%d\n", ps[i].pid, ps[i].burst_time, ps[i].priority);
*/   
     
	func(ps, n);
    double avgWait = 0, avgTurn = 0;
    for(i=0;i<n;++i)
    {
    	avgTurn += ps[i].turnAround;
    	avgWait += ps[i].wait;
    }
    avgWait /= n;
    avgTurn /= n;
    printf("Average Wait Time = %f \nAverage TurnAround Time = %f\n", avgWait, avgTurn);
   
	return 0;
}

void sort_p(struct process *ps, int a, int b)
{
	int i = a, j;
	struct process tmp;
	for(;i<b;++i)
	{
		for(j = i + 1;j<b;++j)
		{
			if(ps[i].priority < ps[j].priority)
			{
				tmp = ps[i];
				ps[i] = ps[j];
				ps[j] = tmp;
			}
		}
	}
}

void func(struct process *ps, int n)
{
	ps[0].wait = 0;
	ps[0].turnAround = ps[0].burst_time;
	int i = 1;
	for(;i<n;++i)
	{
		ps[i].wait = ps[i - 1].wait + ps[i - 1].burst_time;
		ps[i].turnAround = ps[i].wait + ps[i].burst_time;
	}

	//  printing out the details of all the processes
	printf("Process \tWait Times \tTurnaround Time \tBurst Time\t\tArrival Time\t\tPriority\n");
	for(i=0;i<n;++i)
	{
		printf("%d \t\t%d \t\t\t%d \t\t\t%d  \t\t\t%d \t\t\t%d\n", ps[i].pid, ps[i].wait, ps[i].turnAround, ps[i].burst_time, ps[i].arrTime, ps[i].priority);
	}
}

void sort(struct process *ps, int n)
{
	int i, j;
	struct process tmp;

	for(i=0;i<n;++i)
	{
		for(j=i+1;j<n;++j)
		{
			if(ps[i].arrTime > ps[j].arrTime)
			{
				tmp = ps[i];
				ps[i] = ps[j];
				ps[j] = tmp;
			}
		}
	}

/*
    printf("\n\nProcesses after sorting according to priority:\n\n");
    printf("Process ID\tBurst Time\tPriority\n");
    for(i=0;i<n;++i)
    	printf("\t%d\t\t%d\t\t%d\n", ps[i].pid, ps[i].burst_time, ps[i].priority);
*/

}