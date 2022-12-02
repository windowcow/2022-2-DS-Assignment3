#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct data
{
    int priority;
    char *c;
} data;

typedef struct linkedListNode
{
    data *data;
    struct linkedListNode *next;
} linkedListNode;

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

data *makeRandomData(void)
{
    data *d = (data *)malloc(sizeof(data));

    d->priority = rand() % 1000;
    d->c = generateRandomString();

    return d;
}

linkedListNode *makeLinkedNode(void)
{
    linkedListNode *linkedNodePointer = (linkedListNode *)malloc(sizeof(linkedListNode));

    linkedNodePointer->data = makeRandomData();
    linkedNodePointer->next = NULL;

    return linkedNodePointer;
}

void insertNodeToLinkedList(linkedListNode **headPointer)
{
    linkedListNode *newNode = makeLinkedNode();
    // printf("%d ", newNode->data->priority);
    linkedListNode *temp = *headPointer;

    if (*headPointer == NULL)
    {
        *headPointer = newNode;
    }
    else
    {
        *headPointer = newNode;
        newNode->next = temp;
    }
}

void deleteTopPriorityFromLinkedList(linkedListNode **headPointer)
{
    linkedListNode *temp = *headPointer;
    linkedListNode *temp2 = *headPointer;
    linkedListNode *tempMax = *headPointer;

    if (*headPointer == NULL)
    {
    }
    else
    {
        while (temp != NULL)
        {
            if (temp->data->priority > tempMax->data->priority)
            {
                tempMax = temp;
            }
            temp = temp->next;
        }
        if (tempMax == *headPointer)
        {
            *headPointer = (*headPointer)->next;
        }
        else
        {
            while (temp2->next != tempMax)
            {
                temp2 = temp2->next;
            }
            temp2->next = tempMax->next;
        }
    }
}

int main(void)
{
    srand(time(NULL));
    double insertTime, popTime, totalTime;

    clock_t start, end;
    linkedListNode *head = NULL;

    int arraySize;
    scanf("%d", &arraySize);

    // insert
    start = clock();
    printf("Insert : ");
    for (int i = 0; i < arraySize; i++)
    {
        insertNodeToLinkedList(&head);
    }
    end = clock();

    insertTime = (double)(end - start);
    printf("\nInsert에 소요 시간: %lfms\n", insertTime);

    // pop
    printf("\npop: ");

    start = clock();
    for (int i = 0; i < arraySize; i++)
    {
        deleteTopPriorityFromLinkedList(&head);
    }
    end = clock();
    popTime = (double)(end - start);
    printf("\nPop에 소요 시간: %lfms", popTime);

    // total
    totalTime = insertTime + popTime;
    printf("\n\n전체 소요 시간: %lfms", totalTime);

    return 0;
}
