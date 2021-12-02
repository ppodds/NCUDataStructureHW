#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int priority;
    char *data;
} Node;

typedef struct MaxHeap
{
    int size;
    int capacity;
    Node *root;
} MaxHeap;

MaxHeap *createMaxHeap(int capacity)
{
    MaxHeap *maxHeap = (MaxHeap *)malloc(sizeof(MaxHeap));
    maxHeap->size = 0;
    maxHeap->capacity = capacity;
    maxHeap->root = (Node *)calloc(capacity, sizeof(Node));
    return maxHeap;
}

void insert(MaxHeap *maxHeap, int priority, char *data)
{
    if (maxHeap->size >= maxHeap->capacity)
    {
        fprintf(stderr, "Overflow: Could not insertKey\n");
        exit(1);
    }

    int i = maxHeap->size;
    while (i && priority > maxHeap->root[(i - 1) / 2].priority)
    {
        maxHeap->root[i] = maxHeap->root[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    maxHeap->root[i].priority = priority;
    maxHeap->root[i].data = data;
    maxHeap->size++;
}

void popLargest(MaxHeap *maxHeap)
{
    if (maxHeap->size <= 0)
    {
        fprintf(stderr, "Underflow: Could not popLargest\n");
        exit(1);
    }

    free(maxHeap->root[0].data);

    int i = 0;
    maxHeap->root[0] = maxHeap->root[maxHeap->size - 1];
    maxHeap->size--;
    while (i < maxHeap->size / 2)
    {
        int child = 2 * i + 1;

        // compare with left child and right child
        if (child + 1 < maxHeap->size && maxHeap->root[child + 1].priority > maxHeap->root[child].priority)
            child++;
        if (maxHeap->root[i].priority > maxHeap->root[child].priority)
            break;
        // swap child and parent
        Node temp = maxHeap->root[i];
        maxHeap->root[i] = maxHeap->root[child];
        maxHeap->root[child] = temp;
        i = child;
    }
}

int main()
{
    int thingAmount;
    scanf("%d", &thingAmount);

    MaxHeap *maxHeap = createMaxHeap(thingAmount);

    for (int i = 0; i < thingAmount; i++)
    {
        char buffer[100];
        int priority;
        scanf("%100s %d", buffer, &priority);
        char *thing = (char *)calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(thing, buffer);
        insert(maxHeap, priority, thing);
    }

    printf("%s\n", "First three things to do:");
    for (int i = 0; i < 3; i++)
    {
        printf("%s\n", maxHeap->root[0].data);
        popLargest(maxHeap);
    }
    return 0;
}