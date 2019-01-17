#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define N_THREADS 3
#define N_BARRIERS 2

sem_t sem[N_BARRIERS];
pthread_mutex_t mut[N_BARRIERS];
int count[N_BARRIERS] = {0};

void barrier_wait(int bid, int sem_count) {
	pthread_mutex_lock(&mut[sem_count]);
	count[sem_count] += 1;
	pthread_mutex_unlock(&mut[sem_count]);

	if (count[sem_count] == bid) {
		sem_post(&sem[sem_count]);
	}

	sem_wait(&sem[sem_count]);
	pthread_mutex_lock(&mut[sem_count]);
	count[sem_count] -= 1;
	pthread_mutex_unlock(&mut[sem_count]);

	if (count[sem_count] != 0) {
		sem_post(&sem[sem_count]);
	}
}

void *my_thread(void *arg) {
	int i;
	int n = 0;
    for(i=50;i>0;i--) {
        puts("*");
        barrier_wait(N_THREADS, n);
        n = (n + 1) % N_BARRIERS;
        puts("\t+");
        barrier_wait(N_THREADS, n);
        n = (n + 1) % N_BARRIERS;
    }
    pthread_exit(EXIT_SUCCESS);
}

int main(void) {
	int i;
	pthread_mutex_init(&mut[N_BARRIERS], NULL);
	pthread_t tid[N_THREADS];

	for (i=0;i<N_BARRIERS;i++) {
		sem_init(&sem[i],0,0);
	}

	for (i=0;i<N_THREADS;i++)
		pthread_create(&tid[i],NULL,my_thread,NULL);

	for (i=0;i<N_THREADS;i++)
		pthread_join(tid[i],NULL);

	for (i=0;i<N_BARRIERS;i++) {
		sem_destroy(&sem[i]);
	}
	pthread_mutex_destroy(&mut[N_BARRIERS]);
	return EXIT_SUCCESS;
}
