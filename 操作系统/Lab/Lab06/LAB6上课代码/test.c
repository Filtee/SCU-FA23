#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define DATA_SIZE 10

int buf1[DATA_SIZE];
int buf2[DATA_SIZE];
int result[DATA_SIZE];

void* readDataFromFile(void* filename) {
    char* fname = (char*)filename;
    FILE* file = fopen(fname, "r");

    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    int i = 0;
    while (fscanf(file, "%d", &buf1[i]) != EOF) {
        i++;
    }

    fclose(file);
    pthread_exit(NULL);
}

void* processAdd() {
    for (int i = 0; i < DATA_SIZE; i++) {
        result[i] = buf1[i] + buf2[i];
    }

    pthread_exit(NULL);
}

void* processMult

int main() {
    pthread_t thread1, thread2, thread3;
    char* filename1 = "1.dat";
    char* filename2 = "2.dat";

    // Create threads to read data from files
    pthread_create(&thread1, NULL, readDataFromFile, (void*)filename1);
    pthread_create(&thread2, NULL, readDataFromFile, (void*)filename2);

    // Wait for the file reading threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Create a thread to process the data
    pthread_create(&thread3, NULL, processAdd, NULL);
    pthread_join(thread3, NULL);

    // Display the result
    printf("Addition Result:\n");
    for (int i = 0; i < DATA_SIZE; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
