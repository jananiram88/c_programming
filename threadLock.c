#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

sem_t mutex;

void getValue() {
    int value; 
    sem_getvalue(&mutex, &value); 
    printf("The value of the semaphore is %d\n", value);
}


void* delayFunc(void* var) {
    
    //Lock the semaphore
    sem_wait(&mutex);
    getValue();

    for(int i=0; i<60; i++) {
    sleep(1); 
    printf("Countdown :: %d seconds\n",i);
    }

    //Release the semaphore
    sem_post(&mutex);
    getValue();

    return NULL; 
}

void* dateTime(void* var) {
    getValue();
    sem_wait(&mutex);
    getValue();

    time_t currentTime;
    time(&currentTime);

    printf("%s\n", ctime(&currentTime));
    sem_post(&mutex);
    getValue();
}

int main() {
    //Initialize a sempahore
    //arg1- sempahore to initialize
    //arg2- 0 (shared between threads)
    //arg3- Value to assign to this binary semphore; 0 - locked, 1 - unlocked
    sem_init(&mutex, 0, 1); 

    //Current value of the semaphore
    getValue();

    //Create two variables thread1 and thread2 both of type pthread_t
    pthread_t thread1, thread2;

    //pthread_create takes in the following args, arg1- pointer to pthread variable
    //arg2- attributes to be passed in for pthread
    //arg3- Pointer to function to be called for the thread
    //arg4- Pointer passed in as an argument to the function
    pthread_create(&thread1,NULL,delayFunc,NULL);

    pthread_create(&thread2,NULL,dateTime,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    sem_destroy(&mutex);
    
    exit(0);
}

