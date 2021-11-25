// Given a string, a partitioning of the string is a palindrome partitioning if every
// substring of the partition is a palindrome. For example, “aba|b|bbabb|a|b|aba” is
// a palindrome partitioning of “ababbbabbababa”. Determine the fewest cuts needed
// for a palindrome partitioning of a given string.
#include<bits/stdc++.h>
using namespace std;

int min_palin_partition(const string&s)
{
    int n=s.size();
    int C[n];// to store min cuts for s[:i]
    bool isPalin[n][n];// to indicate whether s[i:j] is a palindrome
    for(int i=0;i<n;++i)
    {
        isPalin[i][i] = true;// single char is palindrome
        C[i] = i;// initial cut is set to max
    }
    //first find all palindromes
    for(int i=1;i<n;++i){
        for(int j=0;j<i;++j){
            if(i-j==1)
                isPalin[j][i] = s[i]==s[j];
            else
                isPalin[j][i] = isPalin[j+1][i-1]&&(s[j]==s[i]);
        }
    }
    //calculate all min cuts for s[0:i]
    for(int i=0;i<n;++i){
        if(isPalin[0][i])
            C[i] = 0;//already a palindrome, no need to cut
        else{
            for(int j=0;j<i;++j)// try every possible cut
                if(isPalin[j+1][i] && C[j]+1<C[i])// s[j+1:i] is a palindrome, we only need a cut between j and j+1
                    C[i] = C[j]+1; 
        }
    }
    return C[n-1];
}

// Driver program to test above function
int main()
{
    string str = "ababbbabbababa";
    printf("Min cuts needed for Palindrome Partitioning is %d",
           min_palin_partition(str));
    return 0;
}