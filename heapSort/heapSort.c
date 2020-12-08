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

void heapSort(int n, int array[])
{
    for (int i = n/2 - 1; i >= 0; i--)
        {
            screen(i, n, array);
        }
    for (int i = n - 1; i > 0; i--)
    {
        int temp = array[i];
        array[i] = array[0];
        array[0] = temp;
        screen(0, i, array);
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
    heapSort(n, array);
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
