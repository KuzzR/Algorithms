#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

void screen(int top, int n, int array[])
{
    int nxt = top * 2 + 1;
    if (nxt < n)
    {
        if (nxt + 1 < n && array[nxt + 1] > array[nxt])
        {
            nxt++;
        }
        if (array[nxt] > array[top])
        {
            int temp = array[nxt];
            array[nxt] = array[top];
            array[top] = temp;
            screen(nxt, n, array);
        }
    }
}

void heapSort(int beg, int end, int array[])
{
    for (int i = (end - beg)/2 - 1; i >= 0; i--)
    {
        screen(beg + i, end, array);
    }
    for (int i = end - 1; i > beg; i--)
    {
        int temp = array[i];
        array[i] = array[beg];
        array[beg] = temp;
        screen(beg, i, array);
    }
}

void introSort(int step, int swap_point, int beg, int end, int array[])
{
    if (end - beg > 1)
    {
        if (step < swap_point)
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
            introSort(step + 1, swap_point, 0, mid, array);
            introSort(step + 1, swap_point, mid + 1, end, array);
        }
        else
        {
            heapSort(beg, end, array);
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

    struct timeval stop, start;

    int swap_point = log(n);

    gettimeofday(&start, NULL);
    introSort(0, swap_point, 0, n, array);
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
