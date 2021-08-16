// C++ program to print preorder traversal
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
        cout << root->data << endl;
        preorder(root->left);
        preorder(root->right);
    }
}

void iterative_preorder(TreeNode *root)
{
    /* algorithm:
    1) Create an empty stack S.
    2) Initialize current node as root
    3) Push the current node to S and set current = current->left until current is NULL
    4) If current is NULL and stack is not empty then 
        a) Pop the top item from stack.
        b) Print the popped item, set current = popped_item->right 
        c) Go to step 3.
    5) If current is NULL and stack is empty then we are done.
    */
    stack<TreeNode *> s;
    TreeNode *cur = root;
    while (cur || !s.empty())
    {
        //reach the leftmost node
        while (cur)
        {
            cout<<cur->data<<endl; //traverse cur
            if(cur->right)s.push(cur->right); 
            cur = cur->left; //go to left subtree
        }
        //Now cur is NULL, start to pop elements from stack
        if(!s.empty()){
            cur = s.top();
            s.pop();
        }
    }
}

void Morris_preorder(TreeNode *root, bool writable=true)
{
    /* algorithm
    ONLY SUPPORT WRITABLE TREE
    1. Initialize current as root 
    2. While current is not NULL
    If the current does not have left child
        a) Print current’s data
        b) Go to the right, i.e., current = current->right
    Else
        a) Find rightmost node in current left subtree OR
                node whose right child == current.
            If we found right child == current
                a) Update the right child as NULL of that node whose right child is current
                b) Go to the right, i.e. current = current->right
            Else
                a) Make current as the right child of that rightmost 
                    node we found; and 
                b) Print current’s data
                c) Go to this left child, i.e., current = current->left
    */
   if(!writable){
       cout<<"Only support writable tree !!!"<<endl;
       return;
   }
    TreeNode *cur = root;
    while (cur)
    {
        if (!cur->left)
        {   // only cur and right subtree.
            cout << cur->data << endl; //traverse cur
            cur = cur->right;          //go to right subtree
        }
        else
        {
            //find inorder predecessor of cur(rightmost of left subtree)
            TreeNode *pre = cur->left;
            while (pre->right && pre->right != cur)
            {
                pre = pre->right;
            }
            if (!pre->right)
            {
                pre->right = cur; // link predecessor to cur
                cout << cur->data << endl; //traverse cur.
                cur = cur->left;  // go to left subtree
            }
            else
            {
                pre->right = NULL;         // cut the created link
                cur = cur->right;          //go to right subtree
            }
        }
    }
}

/* Driver program to test above functions*/
int main()
{
    /* Constructed binary tree is
              1
            /   \
          2      3
        /  \
      4     5
    */
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    Morris_preorder(root);
    return 0;
}