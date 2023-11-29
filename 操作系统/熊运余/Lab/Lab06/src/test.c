#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define DATA_SIZE 10

int buf1[DATA_SIZE];
int buf2[DATA_SIZE];
int CountReader = 0;
int CountWriter = 0;
pthread_rwlock_t readlock;
pthread_rwlock_t writelock;

void* readDataFromFile(void* filename) {
    CountReader++;

    // 为写线程加锁
    pthread_rwlock_rdlock(&writelock);

    char* fname = (char*)filename;
    FILE* file = fopen(fname, "r");

    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    int i = 0;
    if (filename == "1.dat") {
        while (fscanf(file, "%d", &buf1[i]) != EOF) {
            i++;
        }
    } else {
        while (fscanf(file, "%d", &buf2[i]) != EOF) {
            i++;
        }
    }

    fclose(file);

    CountReader--;
    // 为写线程解锁
    pthread_rwlock_unlock(&writelock);

    pthread_exit(NULL);
}

void* processData() {
    // 为写线程加锁
    CountWriter++;
    pthread_rwlock_wrlock(&writelock);

    int sum;
    int mult;

    for (int i = 0; i < DATA_SIZE; i++) {
        // 打印和
        printf("第%d组：加法结果为%d\t", i, buf1[i] + buf2[i]);
        // 打印积
        printf("乘法结果为%d\n", buf1[i] * buf2[i]);
    }

    CountWriter--;
    if(CountWriter == 0){
        pthread_rwlock_unlock(&writelock);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2, thread3;
    char* filename1 = "1.dat";
    char* filename2 = "2.dat";

    // 初始化读写锁
    pthread_rwlock_init(&writelock, NULL);

    // 创建读取数据的线程
    pthread_create(&thread1, NULL, readDataFromFile, (void*)filename1);
    pthread_create(&thread2, NULL, readDataFromFile, (void*)filename2);
    // 创建写数据的线程
    pthread_create(&thread3, NULL, processData, NULL);

    // 等待所有线程执行完毕
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    pthread_rwlock_destroy(&writelock);

    return 0;
}
