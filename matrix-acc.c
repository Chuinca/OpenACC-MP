#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 1000

float a[SIZE][SIZE];
float b[SIZE][SIZE];
float c[SIZE][SIZE];

//pgcc -acc -Minfo=accel matrix-acc.c

int main()
{
    int i, j, k;

    double time_spent;
    clock_t begin, end;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            a[i][j] = (float)i + j;
            b[i][j] = (float)i - j;
            c[i][j] = 0.0f;
        }
    }

    begin = clock();

    #pragma acc kernels copyin(a,b), copy(c)
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            for (k = 0; k < SIZE; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("OpenAAC tempo: %f segundos\n", time_spent);

    return 0;
}
