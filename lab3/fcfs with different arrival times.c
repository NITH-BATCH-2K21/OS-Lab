#include<stdio.h>
#include<stdlib.h>

void func(int *wait, int *turnAround, int *processes, int *burst_time, int *arrTime, int n);

int main()
{
   
    int n;
    printf("Enter the number of processes\n");
    scanf("%d", &n);
    
    int wait[n], turnAround[n], burst_time[n], processes[n], i, arrTime[n];

    for(i=0;i<n;++i)
    {
    	processes[i] = i + 1;
    	printf("Enter the burst time of process - %d\n", i + 1);
    	scanf("%d", &burst_time[i]);

        printf("Enter the arrival time of process - %d\n", i + 1);
        scanf("%d", &arrTime[i]);
    }

    //sort(processes, arrTime,burst_time);
    
    func(wait, turnAround, processes, burst_time, arrTime, n);

  
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

void func(int *wait, int *turnAround, int* processes, int *burst_time, int *arrTime, int n)
{
	wait[0] = 0;
	turnAround[0] = burst_time[0];

    int currBurst = 1000, i;

    // currBurst = minimum arrival time
    for(i=0;i<n;++i)
    {
        if(arrTime[i] < currBurst)
            currBurst = arrTime[i];
    }

	i = 1;
    currBurst += burst_time[0];
	for(;i<n;++i)
	{
		wait[i] = currBurst - arrTime[i];
        if(wait[i] < 0)
            wait[i] = 0;
        currBurst += burst_time[i];
		turnAround[i] = wait[i] + currBurst;
	}

	//  printing out the details of all the processes
	printf("Process \tWait Times \tTurnaround Time \tBurst Time\tArrival Time\n");
	for(i=0;i<n;++i)
	{
		printf("%d \t\t%d \t\t\t%d \t\t\t%d\t\t\t%d\n", processes[i], wait[i], turnAround[i], burst_time[i], arrTime[i]);
	}
}