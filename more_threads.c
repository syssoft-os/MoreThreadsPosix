#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Function that each thread will execute
void *counter_function(void *id) {
    for (int i = 1; i <= 50; i++) {
        printf("Thread %ld: %d\n", (long) id, i);
        usleep(100000); // 100 milliseconds delay
    }
    return NULL;
}

int main() {
    int num_threads = 5; // Example: create 5 threads
    pthread_t threads[num_threads];

    // Create threads
    for (long i = 0; i < num_threads; i++) {
        if (pthread_create(&threads[i], NULL, counter_function, (void *) i) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    printf("All threads completed.\n");
    return 0;
}

