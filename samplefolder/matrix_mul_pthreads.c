#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Value depend on System core
#define THREAD_COUNT 4

// Maximum matrix size
#define MAX 4

pthread_t thread[THREAD_COUNT * 2];
pthread_mutex_t lock;
int mat_A[MAX][MAX], mat_B[MAX][MAX], ans[MAX][MAX];

// Printing of matrices
void print_matrix(int matrix[MAX][MAX])
{
    for (int i = 0; i < MAX; i++)
    {

        for (int j = 0; j < MAX; j++)
        {

            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Addition of a Matrix
void *addition(void *arg)
{

    int i, j;
    int *s = (int *)arg;
    int step = *s;
    pthread_mutex_lock(&lock);
    printf("Addition in step %d: ", step);
    // Each thread computes 1/THREAD_COUNTth of matrix addition
    for (i = step * MAX / THREAD_COUNT; i < (step + 1) * MAX / THREAD_COUNT; i++)
    {

        for (j = 0; j < MAX; j++)
        {

            // Compute Sum Row wise
            ans[i][j] = ans[i][j] + mat_A[i][j];
            printf("%d ", ans[i][j]);
        }
    }
    printf("\n");
    pthread_mutex_unlock(&lock);
}

// Subtraction of a Matrix
void *subtraction(void *arg)
{

    int i, j;
    int *s = (int *)arg;
    int step = *s;
    pthread_mutex_lock(&lock);
    printf("Subtraction in step %d: ", step);
    // Each thread computes 1/THREAD_COUNTth of matrix subtraction
    for (i = step * MAX / THREAD_COUNT; i < (step + 1) * MAX / THREAD_COUNT; i++)
    {

        for (j = 0; j < MAX; j++)
        {
            // Compute Subtract row wise
            ans[i][j] = ans[i][j] - mat_B[i][j];
            printf("%d ", ans[i][j]);
        }
    }
    printf("\n");
    pthread_mutex_unlock(&lock);
}

// Driver Code
int main()
{

    int i, j, step = 0;
    // Generating random values in mat_A and mat_B
    for (i = 0; i < MAX; i++)
    {

        for (j = 0; j < MAX; j++)
        {

            mat_A[i][j] = rand() % 10;
            mat_B[i][j] = rand() % 10;
            ans[i][j] = rand() % 10;
        }
    }

    // Displaying mat_A
    printf("\nMatrix A:\n");
    print_matrix(mat_A);

    // Displaying mat_B
    printf("\nMatrix B:\n");
    print_matrix(mat_B);

    // Displaying ans
    printf("\nMatrix ans:\n");
    print_matrix(ans);

    // Creating threads equal
    // to core size and compute matrix row
    for (i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&thread[i], NULL, &addition, (void *)&step);
        pthread_create(&thread[i + THREAD_COUNT], NULL, &subtraction, (void *)&step);
        pthread_join(thread[i], NULL);
        pthread_join(thread[i + THREAD_COUNT], NULL);
        // printf("%d\n", step);
        step++;
    }
    // Display Addition of mat_A and mat_B
    printf("\n Adding A and Sub B from ans:\n");
    print_matrix(ans);

    return 0;
}
