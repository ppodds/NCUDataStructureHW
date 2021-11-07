#include <iostream>
#include <list>

using namespace std;

typedef struct
{
    long long int coefficient;
    long long int power;
} PolynomailTerm;

typedef struct
{
    long long int termAmount;
    list<PolynomailTerm> terms;
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
        cin >> terms;
        list<PolynomailTerm> termsList;
        for (long long int j = 0; j < terms; j++)
        {
            // set term info
            long long int coefficient, power;
            cin >> coefficient >> power;
            termsList.push_back({ coefficient, power });
        }
        Polynomail polynomial = {terms, termsList};
        polynomails[i] = polynomial;
    }

    // add polynomail
    Polynomail answer;

    long long int added[2] = {0, 0};
    answer.termAmount = polynomails[0].termAmount + polynomails[1].termAmount;
    list<PolynomailTerm> answerTermsList;
    auto answerTermsListIterator = answerTermsList.begin();
    auto term1 = polynomails[0].terms.begin();
    auto term2 = polynomails[1].terms.begin();
    while (added[0] < polynomails[0].termAmount && added[1] < polynomails[1].termAmount)
    {
        switch (compare(term1->power, term2->power))
        {
        case 1:
            if (answerTermsList.size() != 0 && answerTermsListIterator->power == term1->power)
                answerTermsListIterator->coefficient += term1->coefficient;
            else
            {
                answerTermsList.push_back({ term1->coefficient, term1->power });
                answerTermsListIterator++;
            }
            added[0]++;
            term1++;
            break;
        case 0:
        {
            // add same power term
            long long int coefficient = term1->coefficient + term2->coefficient;
            if (answerTermsList.size() != 0 && answerTermsListIterator->power == term1->power)
                answerTermsListIterator->coefficient += coefficient;
            else
            {
                answerTermsList.push_back({ coefficient, term1->power });
                answerTermsListIterator++;
            }
            added[0]++;
            added[1]++;
            term1++;
            term2++;
            break;
        }
        case -1:
            if (answerTermsList.size() != 0 && answerTermsListIterator->power == term2->power)
                answerTermsListIterator->coefficient += term2->coefficient;
            else
            {
                answerTermsList.push_back({ term2->coefficient, term2->power });
                answerTermsListIterator++;
            }
            added[1]++;
            term2++;
            break;
        }
    }
    list<PolynomailTerm>::iterator needToAdd;
    if (added[0] != polynomails[0].termAmount)
        needToAdd = term1;
    else 
        needToAdd = term2;

    for (int i=0; i<2; i++)
        for (; added[i] < polynomails[i].termAmount; added[i]++)
        {
            if (answerTermsList.size() != 0 && answerTermsListIterator->power == needToAdd->power)
                answerTermsListIterator->coefficient += needToAdd->coefficient;
            else
            {
                answerTermsList.push_back({ needToAdd->coefficient, needToAdd->power });
                answerTermsListIterator++;
            }
        }
    answer.terms = answerTermsList;
    // print answer
    bool hasPrinted = false;
    for (auto term : answer.terms)
    {
        if (hasPrinted) cout << " ";
        else hasPrinted = true;
        cout << term.coefficient << " " << term.power;
    }
    cout << endl;
    return 0;
}