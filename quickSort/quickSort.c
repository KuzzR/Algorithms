#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

void quickSort(int beg, int end, int array[])
{
    if (end - beg > 1)
    {
        int mid = end -1;
        int i = beg;
        while (i < mid)
        {
            if (array[i] > array[mid])
            {
                int temp = array[mid];
                array[mid] = array[i];
                array[i] = array[mid - 1];
                array[mid - 1] = temp;
                mid--;
            }
            else
            {
                i++;
            }
        }
        quickSort(beg, mid, array);
        quickSort(mid + 1, end, array);

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

    struct timeval stop, start;

    gettimeofday(&start, NULL);
    quickSort(0, n, array);
    gettimeofday(&stop, NULL);;

    FILE* fout = fopen(argv[2], "w+");
    fprintf(fout, "%lu\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);
    for (int i = 0; i < n; i++)
    {
        fprintf(fout, "%d\n", array[i]);
    }
    fclose(fout);
    free(array);
    return 0;
}
