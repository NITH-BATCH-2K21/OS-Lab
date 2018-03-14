#include<stdio.h>
#include<math.h>  // useless for this file
#include<stdlib.h>

// mathematical functions operating on floating point numbers are in math.h, those on integeres are in stdlib.h 
void sort(int *a);
int main()
{
	int n, i, curr, orig_curr, dist = 0, maxi, c;
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
	}

	printf("Enter left(0) or right(1)\n");
	scanf("%d", &c);

	//sort(a);

	printf("Path of serving requests:\n");
	printf("Original Position of head = %d\n", orig_curr);

	if(c == 0) // go left
	{
		while(curr >= 0)
		{
			int j;
			for(j=0;j<n;++j)
			{
				if(a[j] == curr && valid[j] == 1) // unserviced request
				{
					printf("%d ", curr);
					valid[j] = 0;
					break;
				}
			}
			--curr;
		}

		curr = orig_curr;

		while(curr <= maxi)
		{
			int j;
			for(j=0;j<n;++j)
			{
				if(a[j] == curr && valid[j] == 1) // unserviced request
				{
					printf("%d ", curr);
					valid[j] = 0;
					break;
				}
			}
			++curr;
		}

		printf("\n");
		printf("Total distance = %d\n", orig_curr + maxi);
	}
	else
	{
		while(curr <= maxi)
		{
			int j;
			for(j=0;j<n;++j)
			{
				if(a[j] == curr && valid[j] == 1) // unserviced request
				{
					printf("%d ", curr);
					valid[j] = 0;
					break;
				}
			}
			++curr;
		}
		
		curr = orig_curr;

		while(curr >= 0)
		{
			int j;
			for(j=0;j<n;++j)
			{
				if(a[j] == curr && valid[j] == 1) // unserviced request
				{
					printf("%d ", curr);
					valid[j] = 0;
					break;
				}
			}
			--curr;
		}

		printf("\n");
		printf("Total distance = %d\n", 2 * maxi - orig_curr);

	}

	return 0;
}

/*
void sort(int *a)
{

}
*/