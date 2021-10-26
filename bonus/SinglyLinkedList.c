#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void addFront(LinkedList *list, int value)
{
    Node *node = calloc(1, sizeof(Node));

    node->rear = list->head;
    node->data = value;
    node->front = NULL;
    list->head = node;
    list->size++;
}

void addIndex(LinkedList *list, int index, int value)
{
    if (index < 0 || index > list->size)
        return;

    Node *cur = list->head;
    for (int i = 0; i < index; i++)
        cur = cur->rear;
    if (cur)
    {
        if (cur->front)
        {
            Node *node = calloc(1, sizeof(Node));
            node->data = value;
            node->front = cur->front;
            cur->front->rear = node;
            node->rear = cur;
            cur->front = node;
        }
        else
            addFront(list, value);
    }
    else
        addBack(list, value);

    list->size++;
}

void deleteIndex(LinkedList *list, int index)
{
    if (index < 0 || index >= list->size)
        return;

    Node *cur = list->head;
    for (int i = 0; i < index; i++)
        cur = cur->rear;
    if (cur == list->head)
    {
        if (cur->rear)
        {
            list->head = cur->rear;
            list->head->front = NULL;
        }
        else
        {
            list->head = NULL;
        }
    }
    else if (cur == list->tail)
    {
        list->tail = cur->front;
        list->tail->rear = NULL;
    }
    else
    {
        cur->front->rear = cur->rear;
        cur->rear->front = cur->front;
    }
    free(cur);
    list->size--;
}

void printList(LinkedList *list)
{
    Node *cur = list->head;
    int first = 1;
    while (cur)
    {
        printf("%d-->", cur->data);
        cur = cur->rear;
    }
    printf("null");
}

int main()
{
    char command[15];
    LinkedList *list = calloc(1, sizeof(LinkedList));
    while (strcmp(command, "exit") != 0)
    {
        scanf("%12s", command);
        if (strcmp(command, "addBack") == 0)
        {
            int value;
            scanf("%d", &value);
            addBack(list, value);
        }
        else if (strcmp(command, "addFront") == 0)
        {
            int value;
            scanf("%d", &value);
            addFront(list, value);
        }
        else if (strcmp(command, "addIndex") == 0)
        {
            int index, value;
            scanf("%d %d", &index, &value);
            addIndex(list, index, value);
        }
        else if (strcmp(command, "deleteIndex") == 0)
        {
            int index;
            scanf("%d", &index);
            deleteIndex(list, index);
        }
    }
    printList(list);

    return 0;
}