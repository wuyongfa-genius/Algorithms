//C++ program to perform huffman coding
/*algorithm,
Steps to build Huffman Tree
1.Input is an array of unique characters along with their frequency of occurrences and output is Huffman Tree. 
2.Create a leaf node for each unique character and build a min heap of all leaf nodes (Min Heap is used as a 
    priority queue. The value of frequency field is used to compare two nodes in min heap. Initially, the least 
    frequent character is at root)
3.Extract two nodes with the minimum frequency from the min heap.
4.Create a new internal node with a frequency equal to the sum of the two nodes frequencies. Make the first
    extracted node as its left child and the other extracted node as its right child. Add this node to the min heap.
    Repeat steps#2 and #3 until the heap contains only one node. The remaining node is the root node and the 
    tree is complete.
Steps to print codes from Huffman Tree:
    Traverse the tree formed starting from the root. Maintain an auxiliary array. While moving to the left child, 
    write 0 to the array. While moving to the right child, write 1 to the array. Print the array when a leaf node is 
    encountered.
*/
#include<bits/stdc++.h>
using namespace std;

struct HuffmanNode
{
    char c; //'$ means this node is a auxilary node
    int freq;
    HuffmanNode *left, *right;
    HuffmanNode(char _c = '$', int f = 0, HuffmanNode *l = nullptr, HuffmanNode *r = nullptr) : c(_c), freq(f), left(l), right(r) {}
};

struct myCompare
{ 
    bool operator()(HuffmanNode*h1, HuffmanNode*h2){return h1->freq>h2->freq;}
};


void print_codes(HuffmanNode *root, string s)
{
    if (root)
    {
        if (root->c != '$')
            cout << root->c << " : " << s << endl;
        print_codes(root->left, s + '0');
        print_codes(root->right, s + '1');
    }
}

HuffmanNode *huffman_tree(const vector<char>&L, const vector<int>&F)
{
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, myCompare>pq;
    for(int i=0;i<L.size();++i)
        pq.emplace(new HuffmanNode(L[i], F[i]));
    while(pq.size()>1){
        HuffmanNode*smaller=pq.top();
        pq.pop();
        HuffmanNode*bigger=pq.top();
        pq.pop();
        HuffmanNode*dummy=new HuffmanNode('$', smaller->freq+bigger->freq);
        dummy->left = smaller;
        dummy->right = bigger;
        pq.emplace(dummy);
    }
    return pq.top();
}

// Driver Code
int main()
{

    vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> freqs = {5, 9, 12, 13, 16, 45};
    HuffmanNode*root = huffman_tree(letters, freqs);
    print_codes(root, "");

    return 0;
}