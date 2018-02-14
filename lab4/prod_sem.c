#include<stdio.h>
#include<stdlib.h>

void prod();
void consumer();

int x = 0, mutex = 1, full = 0, empty = 3;
// mutex is used to ensure only one of producer or consumer is in the critical section
// x is the data being produced/consumed
// full = 0 indicates empty, full = max_capacity indicates that the buffer is full
// empty = 0 indicates that the buffer is empty
// actions of producer and consumer on full and empty must coordinate properly

int wait(int);
int signal(int);

int main()
{
	int n;
	while(1)
	{
		printf("1.Producer\n2.Consumer\n3.Exit\n");
		scanf("%d",&n);

		switch(n)
		{
			case 1:
			if(mutex==1 && empty!=0)
				prod();
			else
				printf("Buffer is full\n");
			break;

			case 2:
			if(mutex==1 && full!=0)
				consumer();
			else
				printf("Buffer is empty\n");
			break;

			case 3:
			exit(1);
		}

	}

	return 0;
}

int wait(int s)
{
	return (--s);
}

int signal(int s)
{
	return (++s);
}

void prod()
{
	mutex = wait(mutex);
	full = signal(full);
	empty = wait(empty);
	x++;
	printf("Producer has produced %d\n", x);
	mutex = signal(mutex);
	return;
}

void consumer()
{
	mutex = wait(mutex);
	full = wait(full);
	empty = signal(empty);
	printf("Consumer has consumed %d\n", x);
	x--;
	mutex = signal(mutex);
	return;
}