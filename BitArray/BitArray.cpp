#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
for i = 1 to N - 1
a[i] = a[i - 1] * P + Q(modulo 2 ^ 31)
*/
unsigned long N, S, P, Q, mod;
unsigned long updateFunction(unsigned long Ain)
{
    unsigned long long Aout;
    Aout = (unsigned long long)Ain * P;
    Aout += Q;
    Aout %= mod;
    return (unsigned long)Aout;
}

class TortoiseAndHare
{
    vector<unsigned long> diffElements;
    unsigned long* tort;
    unsigned long* hare;

public:
    void Floyds_Algorithm(long long);
};

void TortoiseAndHare::Floyds_Algorithm(long long nextDiff)
{
    //find the pattern in the difference a[i] - a[i-1] and use this to solve the rest of N 

    //call updateFunction() until a cycle is found

    //get start of circle

    //find length of circle

}

// TODO - implemenet Floyd's and Brent's algorithms
/*
def floyd(f, x0) :
    # Main phase of algorithm : finding a repetition x_i = x_2i.
    # The hare moves twice as quickly as the tortoise and
    # the distance between them increases by 1 at each step.
    # Eventually they will both be inside the cycle and then,
    # at some point, the distance between them will be
    # divisible by the period λ.
    tortoise = f(x0) # f(x0) is the element / node next to x0.
    hare = f(f(x0))
    while tortoise != hare:
tortoise = f(tortoise)
hare = f(f(hare))

# At this point the tortoise position, ν, which is also equal
# to the distance between hare and tortoise, is divisible by
# the period λ.So hare moving in circle one step at a time,
#and tortoise(reset to x0) moving towards the circle, will
# intersect at the beginning of the circle.Because the
# distance between them is constant at 2ν, a multiple of λ,
# they will agree as soon as the tortoise reaches index μ.

# Find the position μ of first repetition.
mu = 0
tortoise = x0
while tortoise != hare:
tortoise = f(tortoise)
hare = f(hare)   # Hare and tortoise move at same speed
mu += 1

# Find the length of the shortest cycle starting from x_μ
# The hare moves one step at a time while tortoise is still.
# lam is incremented until λ is found.
lam = 1
hare = f(tortoise)
while tortoise != hare:
hare = f(hare)
lam += 1

return lam, mu
*/

int main() 
{
    mod = 2147483648;
    cin >> N >> S >> P >> Q;
    while (N > 100000000 || S > mod || P > mod || Q > mod || N < 1)
    {
        cout << "Incorrect input, try again" << endl;
        cin >> N >> S >> P >> Q;
    }

    std::vector<unsigned long> A;
    std::size_t ind = 0;

    //first element added to vector
    A.push_back(S % mod);

    //iterate through the other elements
    //this is where floyds algorithm needs to be used for speed optimisation
    for (ind = 0; ind < N - 1; ind++)
    {
        A.push_back(updateFunction(A[ind]));
    }

    std::sort(A.begin(), A.end());

    vector<unsigned long>::iterator ptr;

    long uniqueElementsInArray = 1;
    for (ptr = A.begin() + 1; ptr < A.end(); ptr++)
    {
        if (*ptr != *(ptr - 1))
            uniqueElementsInArray++;
    }

    cout << uniqueElementsInArray << endl;

    return 0;
}

