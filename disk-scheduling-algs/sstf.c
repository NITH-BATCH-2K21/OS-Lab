#include<stdio.h>
#include<math.h>  // useless for this file
#include<stdlib.h>

// mathematical functions operating on floating point numbers are in math.h, those on integeres are in stdlib.h 

int main()
{
	int n, i, curr, orig_curr, dist = 0, cnt = 0;
	printf("Enter total number of requests\n");
	scanf("%d", &n);

	printf("Enter the current position of disk\n");
	scanf("%d", &orig_curr);

	curr = orig_curr;
	printf("Enter %d track numbers\n", n);
	int a[n], valid[n];
	for(i=0;i<n;++i)
	{
		scanf("%d", &a[i]);
		valid[i] = 1;
	}

	printf("Path of serving requests:\n");
	printf("Original Position of head = %d\n", orig_curr);

	while(cnt < n)
	{
		// finding the nearest request
		int j, nearest = 1e9, pos = -1;
		for(j=0;j<n;++j)
		{
			if(valid[j] == 0)
				continue;

			if(abs(a[j] - curr) < nearest)
			{
				nearest = abs(a[j] - curr);
				pos = j;
			}
		}

		printf("%d ", a[pos]);
		valid[pos] = 0;
		curr = a[pos];
		dist += nearest;
		++cnt;
	}

	printf("\n");

	printf("Total distance = %d\n", dist);

	return 0;
}