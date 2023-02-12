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

struct tray {
    struct pair pairs[150000];
    int index_last;
    int index_first;
};

struct tray intervals;

double func(double x)
{
    return sqrt(x);
}

void do_lab()
{
    clock_t start = clock();

    // Initialize tray
    intervals.index_first = 0;
    intervals.index_last  = 0;

    // Read values from file
    FILE *f = fopen("intervals.txt", "r");

    if (f == NULL) {
        printf("Error opening File!\n");
    }

    int a;
    int b;

    while (fscanf(f, "%d %d", &a, &b) != EOF) {
        intervals.pairs[intervals.index_last].first = a;
        intervals.pairs[intervals.index_last].second = b;
        ++intervals.index_last;
    }

    fclose(f);

    // Calculate integral
    const int c_n = 100000;

    while(!(intervals.index_first == intervals.index_last)) {

        int a = intervals.pairs[intervals.index_first].first;
        int b = intervals.pairs[intervals.index_first].second;
        ++intervals.index_first;

        size_t i;
        double h = (double)(b - a) / c_n;
        double sum = 0.0;
        double x;

        for (i = 0; i < c_n; ++i) {
            x = h * i;
            sum += func(x);
        }
        sum = h * sum;
    }

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time=%.16f sec\n", time);
}

int main()
{
    do_lab();

    return 0;
}

