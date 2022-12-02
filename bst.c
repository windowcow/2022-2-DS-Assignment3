#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node *treePointer;

typedef struct data
{
    int priority;
    char *c;
} data;

typedef struct node
{
    data data;
    treePointer leftChild;
    treePointer rightChild;
} node;

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

treePointer makeTreeNode(void)
{
    treePointer treePointerPointer = (treePointer)malloc(sizeof(node));

    treePointerPointer->data = *makeRandomData();
    treePointerPointer->leftChild = NULL;
    treePointerPointer->rightChild = NULL;

    return treePointerPointer;
}

int insertTreeNode(treePointer *root, treePointer insertedNode)
{
    if (*root == NULL)
    {
        *root = insertedNode;
    }
    else
    {
        if (insertedNode->data.priority >= (*root)->data.priority)
        {
            insertTreeNode(&(*root)->rightChild, insertedNode);
        }
        else
        {
            insertTreeNode(&(*root)->leftChild, insertedNode);
        }
    }
    return insertedNode->data.priority;
}

void deleteMaxPriorityNode(treePointer *root)
{
    // 오른 자식이 없으면 루트가 가장 큰거임.
    if ((*root)->rightChild == NULL)
    {
        int result = (*root)->data.priority;
        treePointer temp = *root;
        *root = (*root)->leftChild;
        printf("%d ", result);
    }
    // 오른 자식이 있는 경우 그 오른자식을 재귀적으로 계속 타고가서 없앰
    else
    {
        deleteMaxPriorityNode(&((*root)->rightChild));
    }
}

int main(void)
{
    srand(time(NULL));
    double insertTime, popTime, totalTime;

    clock_t start, end;
    treePointer root = NULL;

    // insert
    start = clock();
    ////
    printf("\ninsert:  ");
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", insertTreeNode(&root, makeTreeNode()));
    }
    end = clock();

    insertTime = (double)(end - start);
    printf("\n\nInsert에 소요 시간: %lfms\n", insertTime);

    // pop
    printf("\npop: ");

    start = clock();
    for (int i = 0; i < 100; i++)
    {
        deleteMaxPriorityNode(&root);
    }
    end = clock();
    popTime = (double)(end - start);
    printf("\n\nPop에 소요 시간: %lfms\n", popTime);

    // total
    totalTime = insertTime + popTime;
    printf("\n\n전체 소요 시간: %lfms", totalTime);

    return 0;
}
