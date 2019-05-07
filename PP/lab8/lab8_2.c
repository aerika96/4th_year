#include <omp.h>
#include <stdlib.h>
#include <stdio.h>


void main()
{

    int i;
    omp_set_num_threads(4);

    printf("Folosim 4 threaduri, si 4 iteratii la for\n");
    printf("Varianta cu \"for\" separat\n");

#pragma omp parallel
#pragma omp for
    for (i = 0; i<4 ; i++)
    {
        printf("Hello nr: %d from thread: %d\n", i, omp_get_thread_num());
    }

    printf("Varianta cu \"parallel for\"\n");

#pragma omp parallel for
    for(i=0; i<4; i++)
    {
        printf("Hello nr: %d from thread : %d\n", i, omp_get_thread_num());
    }

    printf("Varianta cu \"parallel\" si \"for\" \n");

#pragma omp parallel private(i)
    {
        for (i=0; i<4; i++)
        {
            printf("Hello nr: %d from thread: %d\n", i, omp_get_thread_num());
        }
    }

    printf("...done\n");
}