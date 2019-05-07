#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>


#define NUM_THREADS 8


int verify_if_prime(int number)
{
    for(int i=2; i<sqrt(number); i++)
    {
        if(number%i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void main()
{
    long int A, B;
    printf("The interval [A, B] is:\n");
    scanf("%ld", &A);
    scanf("%ld", &B);

    long int * result = (long int*)malloc(50*sizeof(long int));
    int index = 0;


    for(long int i=2; i<sqrt(B); i++)
    {
        for(long int j=2; j<=i; j++)
        {
            long int res = (long int) pow((double)i,(double)j) + (long int)pow((double)j,(double)i);
            if(res > B)
            {
                break;
            }
            if(A <= res  && verify_if_prime(res))
            {
                result[index] = res;
                index++;
            }

        }
    }

    for(int i=0; i<index; i++)
    {
        printf("%ld  ", result[i]);
    }

}
