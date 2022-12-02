#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct data
{
    int priority;
    char *c;
} data;

char *generateRandomString(void)
{
    char *s = (char *)malloc(100);
    for (int i = 0; i < 100; i++)
    {
        s[i] = rand() % 26 + 'a';
    }
    s[99] = '\0';
    return s;
}

data *makeNode(void)
{
    data *n = malloc(sizeof(data));
    n->priority = rand() % 1000;
    n->c = generateRandomString();
    return n;
}

data **makeArray(void)
{
    data **array = (data **)malloc(100 * sizeof(data *));

    return array;
}

void insertNodeToArray(data **array, data *n)
{
    int i = 0;
    while (array[i] != NULL)
    {
        i++;
    }
    printf("%d ", n->priority);
    array[i] = n;
}

void popBiggestPriority(data **array)
{
    int maxIndex;
    int maxIndexNotNullflag = 0;

    for (int i = 0; i < 100; i++)
    {
        if (array[i] != NULL)
        {
            if (maxIndexNotNullflag == 0)
            {
                maxIndex = i;
                maxIndexNotNullflag = 1;
            }
            else
            {
                if (array[i]->priority > array[maxIndex]->priority)
                {
                    maxIndex = i;
                }
            }
        }
    }

    printf("%d ", array[maxIndex]->priority);
    free(array[maxIndex]);
    array[maxIndex] = NULL;
}

int main(void)
{
    srand(time(NULL));
    double insertTime, popTime, totalTime;

    clock_t start, end;

    data **array = makeArray();
    printf("Insert : ");
    start = clock();
    for (int i = 0; i < 100; i++)
    {

        data *n = makeNode();
        insertNodeToArray(array, n);
    }
    end = clock();

    insertTime = (double)(end - start);
    printf("\nInsert에 소요 시간: %lfms\n", insertTime);

    printf("\nPop : ");
    start = clock();
    for (int i = 0; i < 100; i++)
    {
        data *n = makeNode(); // 같은 조건을 위해서 넣었습니다.
        popBiggestPriority(array);
    }

    end = clock();
    popTime = (double)(end - start);
    printf("\nPop에 소요 시간: %lfms\n", popTime);

    totalTime = insertTime + popTime;
    printf("\n전체 소요 시간!: %lfms", totalTime);

    return 0;
}