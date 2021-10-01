#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    long long int coefficient;
    long long int power;
} PolynomailTerm;

typedef struct
{
    long long int termAmount;
    PolynomailTerm *terms;
} Polynomail;

/**
 * compare two number
 *  
 * a = b -> 0
 * a > b -> 1
 * a < b -> -1
 */
long long int compare(long long int a, long long int b)
{
    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    else
        return 0;
}

int main()
{
    Polynomail polynomails[2];
    for (long long int i = 0; i < 2; i++)
    {
        // get term amount
        long long int terms;
        scanf("%lld", &terms);
        PolynomailTerm *polynomailTerms = (PolynomailTerm *)calloc(terms, sizeof(PolynomailTerm));
        for (long long int j = 0; j < terms; j++)
        {
            // set term info
            long long int coefficient, power;
            scanf("%lld %lld", &coefficient, &power);
            (polynomailTerms + j)->coefficient = coefficient;
            (polynomailTerms + j)->power = power;
        }
        Polynomail p = {.termAmount = terms, .terms = polynomailTerms};
        polynomails[i] = p;
    }

    // add polynomail
    Polynomail answer;

    long long int added[2] = {0, 0};
    answer.termAmount = polynomails[0].termAmount + polynomails[1].termAmount;
    PolynomailTerm *answerTerms = calloc(answer.termAmount, sizeof(PolynomailTerm));
    long long int addedTermAmount = 0;
    added[0] = 0;
    added[1] = 0;
    while (added[0] < polynomails[0].termAmount && added[1] < polynomails[1].termAmount)
    {
        switch (compare((polynomails[0].terms + added[0])->power, (polynomails[1].terms + added[1])->power))
        {
        case 1:
            if (addedTermAmount != 0 && (answerTerms + addedTermAmount - 1)->power == (polynomails[0].terms + added[0])->power)
                (answerTerms + addedTermAmount - 1)->coefficient += (polynomails[0].terms + added[0])->coefficient;
            else
            {
                (answerTerms + addedTermAmount)->coefficient = (polynomails[0].terms + added[0])->coefficient;
                (answerTerms + addedTermAmount)->power = (polynomails[0].terms + added[0])->power;
                addedTermAmount++;
            }
            added[0]++;
            break;
        case 0:
        {
            // add same power term
            long long int coefficient = (polynomails[0].terms + added[0])->coefficient + (polynomails[1].terms + added[1])->coefficient;
            if (addedTermAmount != 0 && (answerTerms + addedTermAmount - 1)->power == (polynomails[0].terms + added[0])->power)
                (answerTerms + addedTermAmount - 1)->coefficient += coefficient;
            else
            {
                (answerTerms + addedTermAmount)->coefficient = coefficient;
                (answerTerms + addedTermAmount)->power = (polynomails[0].terms + added[0])->power;
                addedTermAmount++;
            }
            added[0]++;
            added[1]++;
            break;
        }
        case -1:
            if (addedTermAmount != 0 && (answerTerms + addedTermAmount - 1)->power == (polynomails[1].terms + added[1])->power)
                (answerTerms + addedTermAmount - 1)->coefficient += (polynomails[1].terms + added[1])->coefficient;
            else
            {
                (answerTerms + addedTermAmount)->coefficient = (polynomails[1].terms + added[1])->coefficient;
                (answerTerms + addedTermAmount)->power = (polynomails[1].terms + added[1])->power;
                addedTermAmount++;
            }
            added[1]++;
            break;
        }
    }
    for (int i = 0; i < 2; i++)
        for (; added[i] < polynomails[i].termAmount; added[i]++)
        {
            if (addedTermAmount != 0 && (answerTerms + addedTermAmount - 1)->power == (polynomails[i].terms + added[i])->power)
                (answerTerms + addedTermAmount - 1)->coefficient += (polynomails[i].terms + added[i])->coefficient;
            else
            {
                (answerTerms + addedTermAmount)->coefficient = (polynomails[i].terms + added[i])->coefficient;
                (answerTerms + addedTermAmount)->power = (polynomails[i].terms + added[i])->power;
                addedTermAmount++;
            }
        }
    answer.terms = answerTerms;
    // print answer
    for (long long int i = 0; i < answer.termAmount; i++)
    {
        if ((answer.terms + i)->coefficient)
        {
            printf("%lld %lld", (answer.terms + i)->coefficient, (answer.terms + i)->power);
            if (i != answer.termAmount - 1)
                printf(" ");
        }
    }
    printf("\n");

    return 0;
}