#include<bits/stdc++.h>
using namespace std;

void get_longest_proper_prefix(const string&pat, int*lps)
{
    int prev_prefix_len=0;//previous lps
    lps[0] = 0; //first element is always 0
    int i=1; //start from the index 1
    while(i<pat.size())
    {
        if(pat[i]==pat[prev_prefix_len]) //prev_prefix_len is actually (prev_prefix_len-1)+1 here
        {
            lps[i] = ++prev_prefix_len;
            ++i;
        }
        else
        {
            if(prev_prefix_len!=0) //we know there is a prefix whose length>0, search from the next char to its end.
            {
                // re-search starting from lps[len-1]
                //consider pat[:i] is like "(prefix1,suffix1), pat[len],...(prefix2,suffix2)pat[i]..."
                //when pat[i]!=pat[len], we can re-search starting from the char next to prefix1
                //this is because prefix1==suffix2.
                prev_prefix_len = lps[prev_prefix_len-1];
                //NOTE THAT we haven't get lps[i] here, so we can not increment i
            }
            else
            {
                lps[i] = 0;
                ++i;
            }
        }
    }
}

void KMPSearch(const string&txt, const string&pat)
{
    int n=txt.size(), m=pat.size();
    int lps[m];
    get_longest_proper_prefix(pat, lps);
    int i=0, j=0;
    while(i<n)
    {
        if(pat[j]==txt[i])//macth, we can match next char
        {
            ++j;
            ++i;
        }
        if(j==m)//we have found one match
        {
            cout<<"Found match at index "<<i-m<<endl;
            j = lps[m-1]; //re search from lps[m-1].
        }
        else if(i<n && pat[j]!=txt[i]) //mismatch
        {
            if(j!=0)
                j = lps[j-1];
            else // can not match the first char in pat, we need to increment i to continue
                ++i;
        }
    }
}

// Driver program to test above function
int main()
{
    string txt = "ABABDABACDABABCABAB";
    string pat = "ABABCABAB";
    KMPSearch(txt, pat);
    return 0;
}