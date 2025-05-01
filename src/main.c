#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 1000

int original_array[MAX_SIZE];
int sorted_array[MAX_SIZE];
int SIZE;

typedef struct
{
    int start;
    int end;
} ThreadArgs;

void bubble_sort(int start, int end)
{
    for (int i = start; i < end - 1; i++)
    {
        for (int j = start; j < end - 1 - (i - start); j++)
        {
            if (original_array[j] > original_array[j + 1])
            {
                int temp = original_array[j];
                original_array[j] = original_array[j + 1];
                original_array[j + 1] = temp;
            }
        }
    }
}

void *sort_thread(void *args)
{
    ThreadArgs *arg = (ThreadArgs *)args;
    bubble_sort(arg->start, arg->end);
    pthread_exit(NULL);
}

void *merge_thread(void *args)
{
    int i = 0;
    int j = SIZE / 2;
    int k = 0;

    while (i < SIZE / 2 && j < SIZE)
    {
        if (original_array[i] < original_array[j])
        {
            sorted_array[k++] = original_array[i++];
        }
        else
        {
            sorted_array[k++] = original_array[j++];
        }
    }

    while (i < SIZE / 2)
    {
        sorted_array[k++] = original_array[i++];
    }

    while (j < SIZE)
    {
        sorted_array[k++] = original_array[j++];
    }

    pthread_exit(NULL);
}

int main()
{
    printf("Enter the number of elements (max %d): ", MAX_SIZE);
    scanf("%d", &SIZE);

    if (SIZE <= 0 || SIZE > MAX_SIZE || SIZE % 2 != 0)
    {
        printf("Invalid size. Must be a positive even number and <= %d.\n", MAX_SIZE);
        return 1;
    }

    printf("Enter %d integers:\n", SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        scanf("%d", &original_array[i]);
    }

    pthread_t thread1, thread2, thread_merge;
    ThreadArgs args1 = {0, SIZE / 2};
    ThreadArgs args2 = {SIZE / 2, SIZE};

    pthread_create(&thread1, NULL, sort_thread, &args1);
    pthread_create(&thread2, NULL, sort_thread, &args2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_create(&thread_merge, NULL, merge_thread, NULL);
    pthread_join(thread_merge, NULL);

    printf("Sorted array:\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", sorted_array[i]);
    }
    printf("\n");

    return 0;
}
