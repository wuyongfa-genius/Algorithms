 // C++ program to find binary trees with given inorder
#include <bits/stdc++.h>
using namespace std;

/* A binary tree TreeNode has data, pointer to left child
   and a pointer to right child */
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int data)
    {
        this->data = data;
        left = right = NULL;
    }
};

void preorder(TreeNode *root)
{
    if (root)
    {
        cout << root->data << ',';
        preorder(root->left);
        preorder(root->right);
    }
}

vector<TreeNode*> getTrees(const vector<int>& inorder, int start, int end){
    vector<TreeNode*> trees;
    if(start>end){
        trees.push_back(NULL); //can not use emplace_back
        return trees;
    }
    for(int i=start;i<=end;++i){
        vector<TreeNode*>ltrees=getTrees(inorder, start, i-1);
        vector<TreeNode*>rtrees=getTrees(inorder, i+1, end);
        for(int j=0;j<ltrees.size();++j)
            for(int k=0;k<rtrees.size();++k){
                TreeNode*root=new TreeNode(inorder[i]);
                root->left = ltrees[j];
                root->right = rtrees[k];
                trees.emplace_back(root);
            }
    }
    return trees;
}

// Driver Program to test above functions
int main()
{
    vector<int>inorder={4,5,7};
    vector<TreeNode *> trees = getTrees(inorder, 0, inorder.size()-1);
 
    cout << "Preorder traversals of different "
         << "possible Binary Trees are \n";
    for (int i = 0; i < trees.size(); i++)
    {
        preorder(trees[i]);
        cout<<endl;
    }
    return 0;
}