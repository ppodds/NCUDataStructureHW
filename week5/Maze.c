#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int height;
    int width;
    int **map;
    int **discovered;
} Maze;

typedef struct
{
    int row;
    int column;
} Position;

typedef struct Node
{
    struct Node *front;
    struct Node *rear;
    Position data;
} Node;

typedef struct
{
    int size;
    Node *head;
    Node *tail;
} LinkedList;

typedef struct
{
    int size;
    LinkedList *items;
} Stack;

void append(LinkedList *list, Position data)
{
    Node *node = calloc(1, sizeof(Node));

    node->rear = NULL;
    node->data = data;
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

void removeTail(LinkedList *list)
{
    if (list->size--)
    {
        if (list->tail->front)
        {
            list->tail = list->tail->front;
            free(list->tail->rear);
            list->tail->rear = NULL;
        }
        else
        {
            // linked list size = 1
            free(list->tail);
            list->tail = NULL;
            list->head = NULL;
        }
    }
    else
    {
        fprintf(stderr, "Linked list SIZE = 0");
    }
}

Position getTail(LinkedList *list)
{
    if (list->size)
    {
        return list->tail->data;
    }
    else
    {
        fprintf(stderr, "Linked list is empty!");
    }
}

void push(Stack *stack, Position *pos)
{
    append(stack->items, *pos);
    stack->size++;
}

Position pop(Stack *stack)
{
    if (stack->size)
    {
        Position data = getTail(stack->items);
        removeTail(stack->items);
        stack->size--;
        return data;
    }
    else
        fprintf(stderr, "Stack size = 0!");
}

void initMazeMap(Maze *maze)
{
    maze->map = calloc(maze->height + 2, sizeof(int *));
    maze->discovered = calloc(maze->height + 2, sizeof(int *));
    for (int i = 0; i < maze->height + 2; i++)
    {
        maze->map[i] = calloc(maze->width + 2, sizeof(int));
        maze->discovered[i] = calloc(maze->width + 2, sizeof(int));
    }
    for (int i = 0; i < maze->width + 2; i++)
    {
        maze->map[0][i] = 1;
        maze->map[maze->height + 1][i] = 1;
        maze->discovered[0][i] = 1;
        maze->discovered[maze->height + 1][i] = 1;
    }
    for (int i = 0; i < maze->height + 2; i++)
    {
        maze->map[i][0] = 1;
        maze->map[i][maze->width + 1] = 1;
        maze->discovered[i][0] = 1;
        maze->discovered[i][maze->width + 1] = 1;
    }
}

void getPath(Maze *maze)
{
    Position exit = {.row = maze->height,
                     .column = maze->width};
    Stack stack;
    stack.items = calloc(1, sizeof(LinkedList));
    stack.size = 0;

    maze->discovered[1][1] = 1;
    Position entrance = {.row = 1, .column = 1};
    push(&stack, &entrance);
    int found = 0;
    Position currentPos;
    Position nextPos;
    while (stack.size > 0 && !found)
    {
        currentPos = pop(&stack);
        int dir = 0;

        while (dir < 4 && !found)
        {
            /*
                      0
                      |
                    3- -1
                      | 
                      2
                */
            switch (dir)
            {
            case 0:
                nextPos.row = currentPos.row - 1;
                nextPos.column = currentPos.column;
                break;
            case 1:
                nextPos.row = currentPos.row;
                nextPos.column = currentPos.column + 1;
                break;
            case 2:
                nextPos.row = currentPos.row + 1;
                nextPos.column = currentPos.column;
                break;
            case 3:
                nextPos.row = currentPos.row;
                nextPos.column = currentPos.column - 1;
                break;
            }
            if (nextPos.row == exit.row && nextPos.column == exit.column)
                found = 1;
            else if (!maze->map[nextPos.row][nextPos.column] && !maze->discovered[nextPos.row][nextPos.column])
            {
                maze->discovered[nextPos.row][nextPos.column] = 1;
                push(&stack, &currentPos);
                currentPos.row = nextPos.row;
                currentPos.column = nextPos.column;
                dir = 0;
            }
            else
                dir++;
        }
    }

    if (found)
    {
        int first = 1;
        Node *cur = stack.items->head;
        while (cur)
        {
            Position pos = cur->data;
            if (first)
                first = 0;
            else
                printf(" ");
            printf("(%d,%d)", pos.row - 1, pos.column - 1);
            cur = cur->rear;
        }
        printf(" (%d,%d) (%d,%d)\n", currentPos.row - 1, currentPos.column - 1, exit.row - 1, exit.column - 1);
    }
    else
        printf("Can't reach the exit!");
}

void printMaze(Maze *maze)
{
    for (int i = 0; i < maze->height + 2; i++)
    {
        for (int j = 0; j < maze->width + 2; j++)
        {
            printf("%d", maze->map[i][j]);
        }
        printf("\n");
    }
}

void setMazePos(Maze *maze, Position *pos, int value)
{
    maze->map[pos->row + 1][pos->column + 1] = value;
}

int main()
{
    Maze maze;
    scanf("%d %d", &(maze.height), &(maze.width));

    // init maze
    initMazeMap(&maze);

    // set maze according input
    for (int i = 0; i < maze.height; i++)
    {
        for (int j = 0; j < maze.width; j++)
        {
            int tmp;
            scanf("%d", &tmp);
            Position pos = {.row = i, .column = j};
            setMazePos(&maze, &pos, tmp);
        }
    }

    getPath(&maze);

    return 0;
}