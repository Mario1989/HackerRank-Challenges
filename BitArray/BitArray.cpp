/* BitArray.cpp :

This source code contains the full solution for the Hackerrank practice problem here:

https://www.hackerrank.com/challenges/bitset-1/problem

Bit Arrays

-------------------------------------------------------------------------------------------------------
Problem that was solved is summarised below. See link for input constraints
-------------------------------------------------------------------------------------------------------
You are given four integers: N, S, P, Q. You will use them in order to create the sequence  with the following pseudo-code.

a[0] = S (modulo 2^31)
for i = 1 to N-1
    a[i] = a[i-1]*P+Q (modulo 2^31)

Your task is to calculate the number of distinct integers in the sequence .

*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class BitArray
{
    unsigned long N, S, P, Q, modVal;
    vector<unsigned long> elements;
    vector<unsigned long>::iterator tort;
    vector<unsigned long>::iterator hare;
    vector<unsigned long>::iterator itr;    //itr performs temp iterator actions
    
public:
    BitArray(unsigned long N, unsigned long S, unsigned long P, unsigned long Q, unsigned long mod) : N(N), S(S), P(P), Q(Q), modVal(mod)
    {
        elements.push_back(S);
    }
    void updateFunction(int);
    unsigned long Floyds_Algorithm(void);
};

void BitArray::updateFunction(int numOfUpdates)
{
    for(int i = 0; i < numOfUpdates; ++i)
    { 
        unsigned long Ain;
        unsigned long Aout;
        itr = elements.end() - 1;
        Ain = *itr;
        Aout = Ain * P;
        Aout += Q;
        Aout %= modVal;
        elements.push_back(Aout);
    }
}

unsigned long BitArray::Floyds_Algorithm(void)
{
    int elemDistToStartLoop = 0;
    int elemLoopLength = 0;
    hare = elements.begin(); //after push_back as we need an element to begin with
    tort = elements.begin();
    do 
    {
        for (int i = 0; i < 2 && hare != elements.end(); i++)
        {
            hare++;
        }
        tort++;
        if (hare == elements.end())
        {
            return (unsigned long)(elements.end() - elements.begin());
        }
    } while (*tort != *hare);

    //get start of circle
    tort = elements.begin();
    while (*tort != *hare)
    {
        tort++;
        elemDistToStartLoop++;
    }

    //find length of circle
    do
    {
        tort++;
        elemLoopLength++;
    } while (*tort != *hare);

    return (elemDistToStartLoop + elemLoopLength);
}

int main() 
{
    unsigned long N, S, P, Q, mod;
    mod = 2147483648;
    cin >> N >> S >> P >> Q;
    while (N > 100000000 || S > mod || P > mod || Q > mod || N < 1)
    {
        cout << "Incorrect input, try again" << endl;
        cin >> N >> S >> P >> Q;
    }

    std::vector<unsigned long> A;
    std::size_t ind = 16;
    std::size_t total = 0;

    //first element added to vector
    BitArray* M = new BitArray(N, S, P, Q, mod);

    long uniqueElementsInArray = 0;    

    while(total < N - 1)
    {
        ind = min((size_t)N - total - 1, ind);
        total += ind;
        M->updateFunction(ind);
        uniqueElementsInArray = M->Floyds_Algorithm();
        if (uniqueElementsInArray < total)
        {
            break;
        }
        ind *= 3; // double the update count for next loop iteration
        if (uniqueElementsInArray > 10000) //bit of a hack choosing 10k - unlikely to have repeating loops after 10000 elements
        {
            uniqueElementsInArray = N;
            break;
        }
    }   

    
    cout << uniqueElementsInArray << endl;
    return 0;
}
