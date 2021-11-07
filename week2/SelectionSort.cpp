#include <iostream>
#include <string>

using namespace std;

typedef struct
{
    string studentNumber;
    int score;
    int inputOrder;
} Student;

int main()
{
    int amount;
    cin >> amount;
    // student array
    Student *students = new Student[amount];
    for (int i = 0; i < amount; i++)
    {
        cin >> students[i].studentNumber >> students[i].score;
        students[i].inputOrder = i;
    }

    // selection sort
    for (int i = 0; i < amount; i++)
    {
        int index = i;

        // find maxest number
        for (int j = i; j < amount; j++)
        {
            if (students[j].score > students[index].score)
            {
                index = j;
            } else if (students[j].score == students[index].score && students[j].inputOrder < students[index].inputOrder)
            {
                index = j;
            }
        }

        // swap
        Student temp = students[index];
        students[index] = students[i];
        students[i] = temp;
    }

    for (int i = 0; i < amount; i++)
        cout << students[i].studentNumber << endl;

    delete[] students;
    return 0;
}