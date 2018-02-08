#include <stdio.h>
#include <stdlib.h>

struct process
{
	int pid, arrTime, burstTime, priority, wait, turnAround;
	int v;
};

void sort(struct process *pr, int n);
void sort_arr(struct process *pr, int l, int r);
void func(struct process *pr, int n);
void arr(struct process *pr, int n);


int main()
{
	int n, i, j;
	printf("Enter the number of processes\n");
	scanf("%d", &n);
	struct process pr[n], final[n];

	for(i=0;i<n;++i)
	{
		printf("Process ID : %d. Enter Arrival Time, Burst Time and Priority\n", i);
		pr[i].pid = i;
		pr[i].v = 1;
		scanf("%d%d%d", &pr[i].arrTime, &pr[i].burstTime, &pr[i].priority);
	}

	sort(pr, n);

	int currTime = 0;
	for(i=0;i<n;++i)
	{
		if(pr[i].arrTime < currTime)
			currTime = pr[i].arrTime;
	}

	for(i=0;i<n;++i)
	{
		sort(pr, n);
		for(j=0;j<n;++j)
		{
			if(pr[j].v == 1 && pr[j].arrTime <= currTime)
			{
				pr[j].v = 0;
				final[i] = pr[j];
				currTime += final[i].burstTime;
			}
			else 
				++j;
		}
	}
	
	func(final, n);

	return 0;
}

void sort(struct process *pr, int n)
{
	int i, j;
	struct process t;

	for(i=0;i<n;++i)
	{
		for(j=i+1;j<n;++j)
		{
			if(pr[j].burstTime < pr[i].burstTime)
			{
				// swap the processes
				t = pr[i];
				pr[i] = pr[j];
				pr[j] = t;	
			}
		}
	}


}

void func(struct process *pr, int n)
{
	pr[0].wait = 0;
	pr[0].turnAround = pr[0].burstTime;

    int currBurst = 1000, i;

    // currBurst = minimum arrival time
    for(i=0;i<n;++i)
    {
        if(pr[i].arrTime < currBurst)
            currBurst = pr[i].arrTime;
    }

	i = 1;
    currBurst += pr[0].burstTime;
	for(;i<n;++i)
	{
		pr[i].wait = currBurst - pr[i].arrTime;
        if(pr[i].wait < 0)
            pr[i].wait = 0;
        currBurst += pr[i].burstTime;
		pr[i].turnAround = pr[i].wait + currBurst;
	}

	//  printing out the details of all the processes
	printf("Order of execution of processes\nPID\t\tArrTime\t\tPriority\tBurst Time\tWait\tTurnAround\n\n");
	for(i=0;i<n;++i)
	{
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pr[i].pid, pr[i].arrTime, pr[i].priority, pr[i].burstTime, pr[i].wait, pr[i].turnAround);
	}
	

	// printing out the analysis in func function itself:

	double avgWait = 0, avgTurn = 0;
    for(i=0;i<n;++i)
    {
    	avgTurn += pr[i].turnAround;
    	avgWait += pr[i].wait;
    }
    avgWait /= n;
    avgTurn /= n;
    printf("Average Wait Time = %f \nAverage TurnAround Time = %f\n", avgWait, avgTurn);
}

