#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *front;
    struct Node *rear;
    int data;
} Node;

typedef struct
{
    int size;
    Node *head;
    Node *tail;
} LinkedList;

void addBack(LinkedList *list, int value)
{
    Node *node = calloc(1, sizeof(Node));

    node->rear = NULL;
    node->data = value;
    if (list->size++)
    {
        node->front = list->tail;
        list->tail->rear = node;
        list->tail = node;
    }
    else
    {
        node->front = NULL;
        list->head = node;
        list->tail = node;
    }
}

void printTree(int *tree, int nodeAmount, int index)
{
    if (2 * index <= nodeAmount)
        printTree(tree, nodeAmount, 2 * (index + 1) - 1);
    printf("%d ", tree[index]);
    if (2 * index + 1 <= nodeAmount)
        printTree(tree, nodeAmount, 2 * (index + 1));
}

int main()
{
    int t;
    LinkedList *list = calloc(1, sizeof(LinkedList));

    while (scanf("%d", &t) == 1)
        addBack(list, t);

    int tree[9999] = {-1};

    // traverse the list and build the tree
    Node *node = list->head;
    int index = 0;
    while (node)
    {
        tree[index] = node->data;
        node = node->rear;
        index++;
    }

    printTree(tree, list->size, 0);
    return 0;
}