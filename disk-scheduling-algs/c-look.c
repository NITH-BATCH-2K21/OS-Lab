#include<stdio.h>
#include<math.h>  // useless for this file
#include<stdlib.h>

// mathematical functions operating on floating point numbers are in math.h, those on integeres are in stdlib.h 
void sort(int *a);
int main()
{
	int n, i, curr, orig_curr, dist = 0, maxi, c, c_max = -1, c_min = 1e9, last_served_request;
	printf("Enter total number of requests\n");
	scanf("%d", &n);

	printf("Enter the current position of disk\n");
	scanf("%d", &orig_curr);

	printf("Enter the maximum track number of disk\n");
	scanf("%d", &maxi);

	curr = orig_curr;
	printf("Enter %d track numbers\n", n);
	int a[n], valid[n];
	for(i=0;i<n;++i)
	{
		scanf("%d", &a[i]);
		valid[i] = 1;

		if(a[i] > c_max)
			c_max = a[i];

		if(a[i] < c_min)
			c_min = a[i];
	}

	printf("Enter left(0) or right(1)\n");
	scanf("%d", &c);

	//sort(a);

	printf("Path of serving requests:\n");
	printf("Original Position of head = %d\n", orig_curr);

	if(c == 0) // go left
	{
		while(curr >= c_min)
		{
			int j;
			for(j=0;j<n;++j)
			{
				if(a[j] == curr && valid[j] == 1) // unserviced request
				{
					printf("%d ", curr);
					valid[j] = 0;
					last_served_request = a[j];
					break;
				}
			}
			--curr;
		}

		if(c_max == orig_curr)
		{
			printf("\n");
			printf("Total distance = %d\n", orig_curr - c_min);
			exit(1);
		}

		curr = c_max;

		while(curr >= orig_curr)
		{
			int j;
			for(j=0;j<n;++j)
			{
				if(a[j] == curr && valid[j] == 1) // unserviced request
				{
					printf("%d ", curr);
					valid[j] = 0;
					last_served_request = a[j];
					break;
				}
			}
			--curr;
		}

		printf("\n");
		printf("Total distance = %d\n", orig_curr - c_min + c_max - last_served_request);
	}
	else
	{
		while(curr <= c_max)
		{
			int j;
			for(j=0;j<n;++j)
			{
				if(a[j] == curr && valid[j] == 1) // unserviced request
				{
					printf("%d ", curr);
					valid[j] = 0;
					last_served_request = a[j];
					break;
				}
			}
			++curr;
		}

		if(c_min == orig_curr)
		{
			printf("\n");
			printf("Total distance = %d\n", c_max - orig_curr);
			exit(1);
		}
		
		curr = c_min;

		while(curr <= orig_curr)
		{
			int j;
			for(j=0;j<n;++j)
			{
				if(a[j] == curr && valid[j] == 1) // unserviced request
				{
					printf("%d ", curr);
					valid[j] = 0;
					last_served_request = a[j];
					break;
				}
			}
			++curr;
		}

		printf("\n");
		printf("Total distance = %d\n", c_max - orig_curr + last_served_request - c_min);

	}

	return 0;
}
