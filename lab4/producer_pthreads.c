#include <stdio.h>
#include <pthread.h>

#define MAX 10			/* Numbers to produce */
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;

void* producer(void *ptr) {
  int i;

  for (i = 1; i <= MAX; i++) {
    pthread_mutex_lock(&the_mutex);	/* protect buffer */
    while (buffer != 0)		       /* If there is something 
					  in the buffer then wait */
      {
        pthread_cond_wait(&condp, &the_mutex);
        //printf("Sleeping the producer and releasing the mutex\n");
      }
    buffer = i;
    printf("Producer produced item %d\n", buffer);
    pthread_cond_signal(&condc);	/* wake up consumer */
    pthread_mutex_unlock(&the_mutex);	/* release the buffer */
  }
  pthread_exit(0);
}

void* consumer(void *ptr) {
  int i;

  for (i = 1; i <= MAX; i++) {
    pthread_mutex_lock(&the_mutex);	/* locks the mutex from being used by other threads */
    while (buffer == 0)			/* If there is nothing in 
					   the buffer then wait */
     {
       pthread_cond_wait(&condc, &the_mutex);
       //printf("Sleeping the consumer and releasing the mutex\n");
     }
    buffer = 0;
    printf("Consumer has consumed the item %d\n", i);
    pthread_cond_signal(&condp);	/* wake up producer */
    pthread_mutex_unlock(&the_mutex);	/* release the buffer */
  }
  pthread_exit(0);
}

int main(int argc, char **argv) {
  pthread_t pro, con;

  // NULL implies default arguments
  pthread_mutex_init(&the_mutex, NULL);	// pthread_mutex_init(pthread_mutex_t *mutex,pthread_mutexattr_t *attr); 
  pthread_cond_init(&condc, NULL);		
  pthread_cond_init(&condp, NULL);		
  // Create the threads
  pthread_create(&con, NULL, consumer, NULL);
  pthread_create(&pro, NULL, producer, NULL);


  pthread_join(&con, NULL);
  pthread_join(&pro, NULL);

 
  pthread_mutex_destroy(&the_mutex);	
  pthread_cond_destroy(&condc);
  pthread_cond_destroy(&condp);		

}