#include<stdio.h>
#include<stdlib.h>

void func(int *wait, int *turnAround, int *processes, int *burst_time, int n, int quant);

int main()
{
   
    int n, quant;
    printf("Enter the number of processes\n");
    scanf("%d", &n);
    printf("Enter the quantum of time for eviction of a process\n");
    scanf("%d", &quant);
    printf("Enter the burst times of processes\n");
    int wait[n], turnAround[n], burst_time[n], processes[n], i;

    for(i=0;i<n;++i)
    {
    	processes[i] = i + 1;
    	printf("Enter the burst time of process - %d\n", i + 1);
    	scanf("%d", &burst_time[i]);
    }
    
    func(wait, turnAround, processes, burst_time, n, quant);

  
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

// send a copy of the burst times
void func(int *wait, int *turnAround, int* processes, int *burst_time, int n, int quant)
{
	int t = 0, i, count = 0, orig_burst[n], j;


    for(i=0;i<n;++i)
    {
        orig_burst[i] = burst_time[i];
        //totTime += burst_time[i];
    }


    for(i=0;1;++i)
    {
        if(burst_time[i] > 0)
        {
            if(burst_time[i] > quant)
            {
                burst_time[i] -= quant;
                t += quant;
            }
            else
            {
                t += (burst_time[i]); 
                wait[i] = t - orig_burst[i];
                turnAround[i] = orig_burst[i] + wait[i];
                burst_time[i] = 0;
                count++;
            }

            if(i == (n - 1))
                i = -1;

            if(count == n) 
                break;
        }       
    }

    printf("Statistics:\n");
    printf("Process ID \t\t Burst Time \t\t Turn Around Time \t\t Wait Time\n");
    for(i=0;i<n;++i)
    {
        printf("\t%d\t\t\t%d\t\t\t  %d\t\t\t\t%d\n", processes[i], orig_burst[i], turnAround[i], wait[i]);
    }
}