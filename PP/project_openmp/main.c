#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h>

int is_prime(long number)
{
    long  sqr = (long)sqrt((double)number);

    for(long i=2; i<= sqr; i++)
    {
        if(number % i == 0)
        {
            return 0;
        }
    }
    return  1;
}

int main() {

    long A, B;
    int n;
    clock_t time_start, time_end;
    double cpu_time_used;

    printf("Enter start and end of the interval: \n A = ");
    scanf("%ld", &A);
    printf("\n B = ");
    scanf("%ld", &B);

    printf("\nEnter the number of threads: \nn = ");
    scanf("%d", &n);

    omp_set_num_threads(n);

    long sqr = (long)sqrt((double)B);
    long res;
    long i,j;

    time_start = clock();
#pragma  omp parallel for private(j, res)

    for(i=2; i<sqr; i++)
    {
        for(j=2; j<=i; j++)
        {
            res = (long)pow((double)i,(double)j) + (long)pow((double)j,(double)i);
            if(res > B)
            {
                break;
            }
            if(res>=A && is_prime(res))
            {
                printf("Found Leyland prime: %ld \n", res);
            }
        }
    }

    time_end =  clock();
    cpu_time_used = ((double) (time_end - time_start)) / CLOCKS_PER_SEC;

    printf("Time taken with %d threads: %f\n", n, cpu_time_used);

    return 0;
}