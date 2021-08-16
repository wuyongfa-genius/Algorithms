/*The Two Water Jug Puzzle
Difficulty Level : Hard
You are on the side of the river. You are given a m liter jug and a n liter jug where 0 < m < n. 
Both the jugs are initially empty. The jugs don’t have markings to allow measuring smaller quantities. 
You have to use the jugs to measure d liters of water where d < n. Determine the minimum no of
operations to be performed to obtain d liters of water in one of jug. 
The operations you can perform are: 
a)Empty a Jug
b)Fill a Jug
c)Pour water from one jug to the other until one of the jugs is either empty or full.*/

// C++ program to count minimum number of steps
// required to measure d litres water using jugs
// of m liters and n liters capacity.
#include <bits/stdc++.h>
using namespace std;

// Utility function to return GCD of 'a'
// and 'b'.
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

/* fromCap -- Capacity of jug from which
              water is poured
   toCap   -- Capacity of jug to which
              water is poured
   d       -- Amount to be measured */
int pour(int fromCap, int toCap, int d, vector<pair<int, int>> &states)
{
    states.emplace_back(0, 0);
    // Initialize current amount of water
    // in source and destination jugs
    int from = fromCap;
    int to = 0;
    states.emplace_back(from, to);

    // Initialize count of steps required
    int steps = 1; // Needed to fill "from" Jug

    // Break the loop when either of the two
    // jugs has d litre water
    while (from != d && to != d)
    {
        int temp = min(from, toCap - to); //maximum pour litre from "from" to "to"
        //pour water
        from -= temp;
        to += temp;
        states.emplace_back(from, to);
        ++steps;
        // early stop
        if (from == d || to == d)
            break;
        //make "from" full if it is empty
        if (from == 0)
        {
            from = fromCap;
            states.emplace_back(from, to);
            ++steps;
        }
        //empty "to" if it is full
        if (to == toCap)
        {
            to = 0;
            states.emplace_back(from, to);
            ++steps;
        }
    }
    return steps;
}

void print_steps(const vector<pair<int, int>> &states, bool swapCap=false){
    for(auto& i:states){
        if(!swapCap)
            cout<<'('<<i.first<<','<<i.second<<")-->";
        else
            cout<<'('<<i.second<<','<<i.first<<")-->";
    }
    cout<<endl;
}

int pour_steps(int jug1Cap, int jug2Cap, int targetCap){
    if(targetCap>max(jug1Cap, jug2Cap))
        return -1;
    if(targetCap%gcd(jug1Cap, jug2Cap)!=0)
        return -1;
    vector<pair<int, int>>states1, states2;
    int steps1, steps2;
    steps1 = pour(jug1Cap, jug2Cap, targetCap, states1);
    steps2 = pour(jug2Cap, jug1Cap, targetCap, states2);
    if(steps1<steps2){
        cout<<"We need "<<steps1<<" step to get "<<targetCap<<" litre water, as follws:"<<endl;
        print_steps(states1);
    }
    else{
        cout<<"We need "<<steps2<<" step to get "<<targetCap<<" litre water, as follws:"<<endl;
        print_steps(states2, true);
    }
    return min(steps1, steps2);
}

// Driver code to test above
int main()
{
    int n = 3, m = 5, d = 4;
 
    pour_steps(n, m, d);
 
    return 0;
}