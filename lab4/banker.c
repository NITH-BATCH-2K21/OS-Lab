#include<stdio.h>

 
// Number of processes
int P, R;
 
// R = Number of resources

 
// Function to find the need of each process
void calculateNeed(int need[P][R], int maxm[P][R],
                   int allot[P][R])
{
    // Calculating Need of each P
    for (int i = 0 ; i < P ; i++)
        for (int j = 0 ; j < R ; j++)
 
            // Need of instance = maxm instance -
            //                    allocated instance
            need[i][j] = maxm[i][j] - allot[i][j];
}
 
// Function to find the system is in safe state or not
void isSafe(int processes[], int avail[], int maxm[][R],
            int allot[][R])
{
    int need[P][R];
 	int p, i;
    // Function to calculate need matrix
    calculateNeed(need, maxm, allot);
 
    // Mark all processes as infinish
    int finish[P];
    for(i=0;i<P;++i)
    	finish[i] = 0;
 
    // To store safe sequence
    int safeSeq[P];
 
    // Make a copy of available resources
    int work[R];
    for (i = 0; i < R ; i++)
        work[i] = avail[i];
 
    // While all processes are not finished
    // or system is not in safe state.
    int count = 0;
    while (count < P)
    {
        // Find a process which is not finish and
        // whose needs can be satisfied with current
        // work[] resources.
        int found = 0;

        
        for (p = 0; p < P; p++)
        {
            // First check if a process is finished,
            // if no, go for next condition
            if (finish[p] == 0)
            {
                // Check if for all resources of
                // current P need is less
                // than work
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;
 
                // If all needs of p were satisfied.
                if (j == R)
                {
                    // Add the allocated resources of
                    // current P to the available/work
                    // resources i.e.free the resources
                    for (int k = 0 ; k < R ; k++)
                        work[k] += allot[p][k];
 
                    // Add this process to safe sequence.
                    safeSeq[count++] = p;
 
                    // Mark this p as finished
                    finish[p] = 1;
 
                    found = 1;
                }
            }
        }
 
        // If we could not find a next process in safe
        // sequence.
        if (found == 0)
        {
            printf("System is not in safe state");
        }
    }
 
    // If system is in safe state then
    // safe sequence will be as below
    printf("System is in safe state.\nSafe sequence is: ");
    for (i = 0; i < P ; i++)
        printf("%d ", safeSeq[i]);
}
 
// Driver code
int main()
{
	printf("Enter the number of processes and the number of resources\n");
	scanf("%d%d",&P, &R);
		
	int i, j;
	int processes[P];
    
 	for(i=0;i<5;++i)
 		processes[i] = i;
    // Available instances of resources
    int avail[R], maxm[P][R], allot[P][R];

    printf("Enter the number of units of resources available\n");
    for(i=0;i<R;++i)
    	scanf("%d", &avail[i]);
 
    // Maximum R that can be allocated
    // to processes
    printf("Enter the maximum number of units of resources required by the processes\n");

    for(i=0;i<P;++i)
    {
    	for(j=0;j<R;++j)
    		scanf("%d",&maxm[i][j]);
    }
 
    // Resources allocated to processes
    printf("Enter the number of units of resources allocated\n");
   for(i=0;i<P;++i)
    {
    	for(j=0;j<R;++j)
    		scanf("%d",&allot[i][j]);
    }
    // Check system is in safe state or not
    isSafe(processes, avail, maxm, allot);
 
    return 0;
}