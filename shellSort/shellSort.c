#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void shellSort(int n, int array[])
{
    int step[50] = { 1 }, p1 = 2, p2 = 1, curr_num;
    for (curr_num = 0; 3 * step[curr_num] < n; curr_num++)
    {
        if ((curr_num + 1) % 2 == 0)
        {
            step[curr_num + 1] = 9 * p1 - 9 * p2 + 1;
        }
        else
        {
            p2 *= 2;
            step[curr_num + 1] = 8 * p1 - 6 * p2 + 1;
        }
        p1 *= 2;
    }

    int temp;
    for (curr_num -= 1; curr_num >= 0; curr_num--)
    {
        for (int i = 0; i < step[curr_num]; i++)
        {
            for (int j = 1; j < n / step[curr_num]; j++)
            {
                for (int h = (j-1) * step[curr_num]; array[h] > array[h + step[curr_num]] && h >= 0; h -= step[curr_num])
                {
                    temp = array[h];
                    array[h] = array[h + step[curr_num]];
                    array[h + step[curr_num]] = temp;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    FILE* fin = fopen(argv[1], "r");
    int n;
    fscanf(fin, "%d", &n);

    int *array = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        fscanf(fin, "%d", &array[i]);
    }
    fclose(fin);

    clock_t t0 = clock();
    shellSort(n, array);
    clock_t t1 = clock();

    FILE* fout = fopen(argv[2], "w+");
    fprintf(fout, "%g\n", (double)(t1-t0) / CLOCKS_PER_SEC * 1000);
    for (int i = 0; i < n; i++)
    {
        fprintf(fout, "%d\n", array[i]);
    }
    fclose(fout);
    free(array);
    return 0;
}
