#include<stdio.h>
#include<math.h>  // useless for this file
#include<stdlib.h>

// mathematical functions operating on floating point numbers are in math.h, those on integeres are in stdlib.h 

int main()
{
	int n, i, curr, orig_curr, dist = 0;
	printf("Enter total number of requests\n");
	scanf("%d", &n);

	printf("Enter the current position of disk\n");
	scanf("%d", &orig_curr);

	curr = orig_curr;
	printf("Enter %d track numbers\n", n);
	int a[n];
	for(i=0;i<n;++i)
	{
		scanf("%d", &a[i]);
		dist += abs(curr - a[i]);
		curr = a[i];
	}

	printf("Path of serving requests:\n");
	printf("Original Position of head = %d\n", orig_curr);
	for(i=0;i<n;++i)
		printf("%d ", a[i]);
	printf("\n");

	printf("Total distance = %d\n", dist);

	return 0;
}