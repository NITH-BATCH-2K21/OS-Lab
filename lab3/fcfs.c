#include<stdio.h>
#include<stdlib.h>

void func(int *wait, int *turnAround, int *processes, int *burst_time, int n);

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

void func(int *wait, int *turnAround, int* processes, int *burst_time, int n)
{
	wait[0] = 0;
	turnAround[0] = burst_time[0];

	int i = 1;
	for(;i<n;++i)
	{
		wait[i] = wait[i - 1] + burst_time[i - 1];
		turnAround[i] = wait[i] + burst_time[i];
	}

	//  printing out the details of all the processes
	printf("Process \tWait Times \tTurnaround Time \tBurst Time\n");
	for(i=0;i<n;++i)
	{
		printf("%d \t\t%d \t\t\t%d \t\t\t%d\n", processes[i], wait[i], turnAround[i], burst_time[i]);
	}
}