#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

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
    matrix.elements = new Element[totalRow * totalCol];
    return matrix;
}

void addElement(SparseMatrix *matrix, int row, int col, int val)
{
    Element *element = &matrix->elements[matrix->totalElement];
    element->row = row;
    element->column = col;
    element->value = val;
    matrix->totalElement++;
}

void setElement(SparseMatrix *matrix, int pos, int row, int col, int val)
{
    Element *element = &matrix->elements[pos];
    element->row = row;
    element->column = col;
    element->value = val;
}

/**
 * Print Matrix
 */
void printMatrix(SparseMatrix *matrix)
{
    cout << matrix->totalRow << " " << matrix->totalColumn << " " << matrix->totalElement << endl;
    for (size_t i = 0; i < matrix->totalElement; i++)
    {
        Element element = matrix->elements[i];
        cout << element.row << " " << element.column << " " << element.value << endl;
    }
}

void deleteMatrix(SparseMatrix *matrix)
{
    delete[] matrix->elements;
}

/**
 * Matrix transpose
 */
SparseMatrix fastTranspose(SparseMatrix *matrix)
{
    SparseMatrix transposedMatrix = initMatrix(matrix->totalColumn, matrix->totalRow);
    transposedMatrix.totalElement = matrix->totalElement;
    int *rowTerms = new int[matrix->totalColumn]();
    int *startingPos = new int[matrix->totalColumn]();
    if (matrix->totalElement > 0)
    {
        // collect element amount of certain column
        for (size_t i = 0; i < matrix->totalElement; i++)
            rowTerms[matrix->elements[i].column] += 1;
        for (size_t i = 1; i < matrix->totalColumn; i++)
            startingPos[i] = startingPos[i-1] + rowTerms[i-1];
        for (size_t i = 0; i < matrix->totalElement; i++)
        {
            Element element = matrix->elements[i];
            int j = startingPos[element.column];
            setElement(&transposedMatrix, j, element.column, element.row, element.value);
            startingPos[matrix->elements[i].column] += 1;
        }
    }
    delete[] rowTerms;
    delete[] startingPos;
    return transposedMatrix;
}

SparseMatrix multiply(SparseMatrix *a, SparseMatrix *b)
{
    if (a->totalColumn != b->totalRow)
    {
        throw invalid_argument("Matrix A's column must equal to Matrix B's row");
    }
    SparseMatrix transposedB = fastTranspose(b);
    SparseMatrix matrix = initMatrix(a->totalRow, b->totalColumn);

    int **mul = new int*[a->totalRow];
    // init mul
    for (size_t i = 0; i < a->totalRow; i++)
        mul[i] = new int[transposedB.totalRow]();

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
        delete[] mul[i];
    delete[] mul;
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
        cin >> row >> col;
        matrixes[m] = initMatrix(row, col);
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                int tmp;
                cin >> tmp;
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