#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    char studentNumber[10];
    int score;
    int inputOrder;
} Student;

int main(void)
{
    int amount;
    scanf("%d", &amount);
    // student array
    Student *students = calloc(amount, sizeof(Student));
    for (int i = 0; i < amount; i++)
    {
        scanf("%9s", &((students + i)->studentNumber));
        scanf("%d", &((students + i)->score));
        (students + i)->inputOrder = i;
    }

    // selection sort
    for (int i = 0; i < amount; i++)
    {
        int index = i;

        // find maxest number
        for (int j = i; j < amount; j++)
        {
            if ((students + j)->score > (students + index)->score)
                index = j;
            else if (((students + j)->score == (students + index)->score) && ((students + j)->inputOrder < (students + index)->inputOrder))
                index = j;
        }

        // swap
        Student temp = *(students + index);
        *(students + index) = *(students + i);
        *(students + i) = temp;
    }

    for (int i = 0; i < amount; i++)
        printf("%s\n", ((students + i)->studentNumber));

    free(students);
    return 0;
}