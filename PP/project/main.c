#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    int th_number;
    int step_size;
    long long  start;
    long long  end;
}params;

int is_prime(long long number)
{
    long long  sqr = (long long)sqrt((double)number);

    for(long long i=2; i<= sqr; i++)
    {
        if(number % i == 0)
        {
            return 0;
        }
    }
    return  1;
}

void* calculate_leyland(void* attr)
{
    params parameters = *(params*)attr;
    long long A = parameters.start;
    long long B = parameters.end;
    int thread_num = parameters.th_number;
    int step = parameters.step_size;
    long long sqr = (long long)sqrt((double)B);
    long long res;


    //printf("%ld %ld %d %d \n", A, B, thread_num, step);



    for(long long i=2+(long long)thread_num; i<sqr; i+=step)
    {
        for(long long j=2; j<=i; j++)
        {
            res = (long long)pow((double)i,(double)j) + (long long)pow((double)j,(double)i);
            if(res > B)
            {
                break;
            }
            if(res>=A && is_prime(res))
            {
                printf("Found Leyland prime: %lld \n", res);
            }
        }
    }
    return 0;
}

int main() {

    long long A, B;
    int n;
    pthread_t *threads;
    params* parameters;
    time_t time_start, time_end;
    double cpu_time_used;

    printf("Enter start and end of the interval: \n A = ");
    scanf("%lld", &A);
    printf("\n B = ");
    scanf("%lld", &B);

    printf("\nEnter the number of threads: \nn = ");
    scanf("%d", &n);

    threads = (pthread_t*)malloc(n * sizeof(pthread_t));
    parameters = (params*)malloc(n * sizeof(params));

    time_start = time(NULL);

    for(int i=0; i<n; i++)
    {
        parameters[i].th_number = i;
        parameters[i].step_size = n;
        parameters[i].start = A;
        parameters[i].end = B;
        pthread_create(&threads[i], NULL,calculate_leyland,(void*)&parameters[i]);
    }

    for(int i=0; i<n; i++)
    {
        pthread_join(threads[i],NULL);
    }

    time_end =  time(NULL);
    cpu_time_used = ((double) (time_end - time_start));

    printf("Time taken with %d threads: %lf\n", n, cpu_time_used);

    return 0;
}