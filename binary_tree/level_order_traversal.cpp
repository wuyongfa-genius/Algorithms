// C++ program to print level order traversal(BFS traversal)
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

void level_order(TreeNode* root){
    if(!root)return;
    queue<TreeNode*>q;
    q.emplace(root);
    while(!q.empty()){
        TreeNode*cur=q.front();
        q.pop();
        cout<<cur->data<<',';
        if(cur->left)q.emplace(cur->left);
        if(cur->right)q.emplace(cur->right);
    }
}

// Driver program to test above functions
int main()
{
    // Let us create binary tree shown in above diagram
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
 
    cout << "Level Order traversal of binary tree is \n";
    level_order(root);
    return 0;
}