#include<stdio.h>
#include<stdlib.h>

void func(int *wait, int *turnAround, int *processes, int *burst_time, int n);

void sort(int *time, int n, int *processes); // sorts based on the burst times

int main()
{
   
    int n;
    printf("Enter the number of processes\n");
    scanf("%d", &n);
    printf("Enter the burst times of processes\n");
    int wait[n], turnAround[n], burst_time[n], processes[n], i;

    for(i=0;i<n;++i)
    {
    	processes[i] = i + 1;
    	printf("Enter the burst time of process - %d\n", i + 1);
    	scanf("%d", &burst_time[i]);
    }

    sort(burst_time, n, processes);
    
    
    func(wait, turnAround, processes, burst_time, n);

  
    double avgWait = 0, avgTurn = 0;
    for(i=0;i<n;++i)
    {
    	avgTurn += turnAround[i];
    	avgWait += wait[i];
    }
    avgWait /= n;
    avgTurn /= n;
    printf("Average Wait Time = %f \nAverage TurnAround Time = %f\n", avgWait, avgTurn);

    
    return 0;
}

void func(int *wait, int *turnAround, int *processes, int *burst_time, int n)
{
	wait[0] = 0;
	turnAround[0] = burst_time[0];

	int i = 1;
	for(;i<n;++i)
	{
		wait[i] = wait[i - 1] + burst_time[i - 1];
		turnAround[i] = wait[i] + burst_time[i];
	}

	printf("Order of execution of processes:\n\n");
	//  printing out the details of all the processes
	printf("Process \tWait Times \tTurnaround Time \tBurst Time\n");
	for(i=0;i<n;++i)
	{
		printf("%d \t\t%d \t\t\t%d \t\t\t%d\n", processes[i], wait[i], turnAround[i], burst_time[i]);
	}
}

void sort(int *a, int n, int *processes)
{
	int i = 0, j, temp;
	// selection sort
	for(;i<n;++i)
	{
		for(j=i+1;j<n;++j)
		{
			if(a[i] > a[j])
			{
				// swapping a[j] and a[i]
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;

				// swapping process ID's.
				temp = processes[i];
				processes[i] = processes[j];
				processes[j] = temp;
			}
		}
	}

/*
	printf("Final order after sorting according to burst times:\n");
	for(i=0;i<n;++i)
		printf("Process ID : %d \t Burst Time : %d\n", processes[i], a[i]);

*/
	
}