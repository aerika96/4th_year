#include "stdio.h"
#include "stdlib.h"
#include <omp.h>


int main() {

    int ID;
    int numThreads;
    int newThreads = 8;


    numThreads = omp_get_max_threads();
    printf("Implicit sunt disponibile :: %d :: threaduri\n", numThreads);

    printf("Schimbam nr de threaduri disponibile la: %d\n", newThreads);
    omp_set_num_threads(newThreads);

    numThreads = omp_get_max_threads();
    printf("Implicit sunt disponibile :: %d :: threaduri\n", numThreads);

    printf("Lansam threadurile in paralel ... \n");

#pragma omp parallel private(ID)
    {
        ID = omp_get_thread_num();
        printf("Hello world from thread %d!\n", ID);

    }

    printf("..done\n");
}