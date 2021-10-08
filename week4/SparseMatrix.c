#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int row;
    int column;
    int value;
} Element;

typedef struct
{
    int totalRow;
    int totalColumn;
    int totalElement;
    Element *elements;
} SparseMatrix;

SparseMatrix initMatrix(int totalRow, int totalCol)
{
    SparseMatrix matrix = {.totalRow = totalRow,
                           .totalColumn = totalCol,
                           .totalElement = 0};
    // init element memory space
    matrix.elements = calloc(totalRow * totalCol, sizeof(Element));
    return matrix;
}

void addElement(SparseMatrix *matrix, int row, int col, int val)
{
    Element *element = matrix->elements + matrix->totalElement;
    element->row = row;
    element->column = col;
    element->value = val;
    matrix->totalElement++;
}

void setElement(SparseMatrix *matrix, int pos, int row, int col, int val)
{
    Element *element = matrix->elements + pos;
    element->row = row;
    element->column = col;
    element->value = val;
}

/**
 * Print Matrix
 */
void printMatrix(SparseMatrix *matrix)
{
    printf("%d %d %d\n", matrix->totalRow, matrix->totalColumn, matrix->totalElement);
    for (size_t i = 0; i < matrix->totalElement; i++)
    {
        Element *element = matrix->elements + i;
        printf("%d %d %d\n", element->row, element->column, element->value);
    }
}

void deleteMatrix(SparseMatrix *matrix)
{
    free(matrix->elements);
}

/**
 * Matrix transpose
 */
SparseMatrix fastTranspose(SparseMatrix *matrix)
{
    SparseMatrix transposedMatrix = initMatrix(matrix->totalColumn, matrix->totalRow);
    transposedMatrix.totalElement = matrix->totalElement;
    int *rowTerms = calloc(matrix->totalColumn, sizeof(int));
    int *startingPos = calloc(matrix->totalColumn, sizeof(int));
    if (matrix->totalElement > 0)
    {
        // collect element amount of certain column
        for (size_t i = 0; i < matrix->totalElement; i++)
            *(rowTerms + matrix->elements[i].column) += 1;
        for (size_t i = 1; i < matrix->totalColumn; i++)
            *(startingPos + i) = *(startingPos + i - 1) + *(rowTerms + i - 1);
        for (size_t i = 0; i < matrix->totalElement; i++)
        {
            Element *element = (matrix->elements + i);
            int j = *(startingPos + element->column);
            setElement(&transposedMatrix, j, element->column, element->row, element->value);
            *(startingPos + (matrix->elements + i)->column) += 1;
        }
    }
    free(rowTerms);
    free(startingPos);
    return transposedMatrix;
}

SparseMatrix multiply(SparseMatrix *a, SparseMatrix *b)
{
    if (a->totalColumn != b->totalRow)
    {
        fprintf(stderr, "Can't multiply!\n");
        exit(1);
    }
    SparseMatrix transposedB = fastTranspose(b);
    SparseMatrix matrix = initMatrix(a->totalRow, b->totalColumn);

    int **mul = calloc(a->totalRow, sizeof(int *));
    // init mul
    for (size_t i = 0; i < a->totalRow; i++)
        mul[i] = calloc(transposedB.totalRow, sizeof(int));

    // calculate new matrix value
    for (size_t i = 0; i < a->totalElement; i++)
    {
        for (size_t j = 0; j < transposedB.totalElement; j++)
        {
            if (a->elements[i].column == transposedB.elements[j].column)
            {
                int *t = mul[a->elements[i].row];
                t[transposedB.elements[j].row] += a->elements[i].value * transposedB.elements[j].value;
            }
        }
    }

    // set new matrix value
    for (size_t i = 0; i < matrix.totalRow; i++)
    {
        for (size_t j = 0; j < matrix.totalColumn; j++)
        {
            if (mul[i][j])
            {
                addElement(&matrix, i, j, mul[i][j]);
            }
        }
    }

    // free mul memory
    for (size_t i = 0; i < a->totalRow; i++)
        free(mul[i]);
    free(mul);
    deleteMatrix(&transposedB);
    return matrix;
}

int main()
{
    // get input matrix
    SparseMatrix matrixes[2];
    for (size_t m = 0; m < 2; m++)
    {
        int row, col;
        scanf("%d %d", &row, &col);
        matrixes[m] = initMatrix(row, col);
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                int tmp;
                scanf("%d", &tmp);
                // check if tmp != 0
                if (tmp)
                    addElement(&matrixes[m], i, j, tmp);
            }
        }
    }

    SparseMatrix answer = multiply(&matrixes[0], &matrixes[1]);
    printMatrix(&answer);
    return 0;
}