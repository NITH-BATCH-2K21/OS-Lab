#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h> // sleep function

sem_t stick[5];

void *phi(void *arg);

int main()
{
  int i; 
  pthread_t p[5];
  for(i=0;i<5;++i)
    sem_init(&stick[i],0,1);
  
  for(i=0;i<=4;i++)
  {
    pthread_create(&p[i],NULL,phi,(void *)i);
  }
  for(i=0;i<=4;i++)
  {
    pthread_join(p[i],NULL);
  }

  return 0;
}


void *phi(void *arg)
{
  int i = (int)arg;
  int j;
  for(j=0;j>=0;--j)
  {
    if(i==4)
    {
      printf("Philosopher %d is hungry\n", i);
      
      sem_wait(&(stick[(i+1) % 5])); 
      printf("Philosopher %d has obtained stick - %d\n", i, i + 1);
      sem_wait(&stick[i]);
      printf("Philosopher %d has obtained stick - %d\n", i, i);

      printf("Philosopher %d is eating with sticks %d and %d\n", i, i, i + 1);
      /* eat */
      
      sem_post(&(stick[(i+1) % 5])); 
      printf("Philosopher %d has kept back stick - %d\n", i, i + 1);
      sem_post(&stick[i]);
      printf("Philosopher %d has kept back stick - %d\n", i, i);

      printf("Philosopher %d is thinking\n", i);
      return;
    }


    printf("Philosopher %d is hungry\n", i);
    sem_wait(&stick[i]);
    printf("Philosopher %d has obtained stick - %d\n", i, i);
    sem_wait(&(stick[(i+1) % 5])); 
    printf("Philosopher %d has obtained stick - %d\n", i, i + 1);

    printf("Philosopher %d is eating with sticks %d and %d\n", i, i, i + 1);
    /* eat */
    sem_post(&stick[i]);
    printf("Philosopher %d has kept back stick - %d\n", i, i);
    sem_post(&(stick[(i+1) % 5])); 
    printf("Philosopher %d has kept back stick - %d\n", i, i + 1);

    printf("Philosopher %d is thinking\n", i);
  }
}