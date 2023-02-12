#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

struct pair {
    int first;
    int second;
};

const int c_tray_size = 500000;
int8_t g_EOF = 0;

struct tray {
    struct pair pairs[150000];
    int index_last;
    int index_first;
};

struct tray intervals;

pthread_mutex_t tray_mutex;
pthread_cond_t cond_variable;

void* read_from_file(void* arg)
{
    FILE *f = fopen("intervals.txt", "r");

    if (f == NULL) {
        printf("Error opening File!\n");
    }

    int a;
    int b;

    while (fscanf(f, "%d %d", &a, &b) != EOF) {


        pthread_mutex_lock(&tray_mutex);

        intervals.pairs[intervals.index_last].first = a;
        intervals.pairs[intervals.index_last].second = b;
        ++intervals.index_last;

        pthread_cond_broadcast(&cond_variable);

        pthread_mutex_unlock(&tray_mutex);


    }

    g_EOF = 1;

    fclose(f);

    pthread_exit(NULL);
}

double func(double x)
{
    return sqrt(x);
}

void* calculate(void* arg)
{
    const int c_n = 100000;

    while(!(g_EOF == 1 && intervals.index_first == intervals.index_last)) {

        pthread_mutex_lock(&tray_mutex);

        while(intervals.index_first == intervals.index_last) {
            pthread_cond_wait(&cond_variable,&tray_mutex);
        }

        int a = intervals.pairs[intervals.index_first].first;
        int b = intervals.pairs[intervals.index_first].second;
        ++intervals.index_first;

        //pthread_cond_broadcast(&cond_variable);

        pthread_mutex_unlock(&tray_mutex);


        size_t i;
        double h = (double)(b - a) / c_n;
        double sum = 0.0;
        double x;

        for (i = 0; i < c_n; ++i) {
            x = h * i;
            sum += func(x);
        }
        sum = h * sum;

        //printf("%lf\n", sum);

    }

    pthread_exit(NULL);;
}

void do_lab()
{
    clock_t start = clock();

    const int c_consumer_number = 4;

    // Initialize tray
    intervals.index_first = 0;
    intervals.index_last  = 0;

    pthread_t producer;
    pthread_t consumer[c_consumer_number];

    int result;
    void* t_return;

    // Initialize mutext and cond
    result = pthread_mutex_init(&tray_mutex, NULL);

    if(result != 0) {
        perror("\nMutex initialization failed");
        exit(EXIT_FAILURE);
    }

    result = pthread_cond_init(&cond_variable, NULL);

    if(result != 0) {
        perror("\nCondition variable initialization failed");
        exit(EXIT_FAILURE);
    }

    // Create threads
    result = pthread_create(&producer, NULL, read_from_file, NULL);

    if(result != 0) {
        perror("\nThread creation failed");
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < c_consumer_number; ++i) {
        result = pthread_create(&consumer[i], NULL, calculate, NULL);

        if(result != 0) {
            perror("\nThread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    // Join threads
    for(size_t i = 0; i < c_consumer_number; ++i) {
        result = pthread_join(consumer[i], &t_return);

        if(result != 0) {
            perror("\nThread join failed");
            exit(EXIT_FAILURE);
        }
    }

    result = pthread_join(producer, &t_return);

    if(result != 0) {
        perror("\nThread join failed");
        exit(EXIT_FAILURE);
    }

    // Destroy mutex and cond
    pthread_mutex_destroy(&tray_mutex);
    pthread_cond_destroy(&cond_variable);

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time=%.16f sec\n", time);
}

int main()
{
    do_lab();

    return 0;
}

