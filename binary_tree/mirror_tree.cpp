// C++ program mirror trees
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

bool areMirror(TreeNode *a, TreeNode *b)
{
    if (!a || !b)
        return true; // two NULL trees
    if (!a || !b)
        return false; // one NULL, the other not NULL
    //both are non-empty
    return a->data == b->data && areMirror(a->left, b->right) && areMirror(a->right, b->left);
}

bool areIdentical(TreeNode *a, TreeNode *b)
{
    if (!a || !b)
        return true; // two NULL trees
    if (!a || !b)
        return false; // one NULL, the other not NULL
    //both are non-empty
    return a->data == b->data && areIdentical(a->left, b->left) && areIdentical(a->right, b->right);
}

bool iterative_areMirror(TreeNode *a, TreeNode *b)
{
    stack<TreeNode *> s1, s2;
    while (1)
    { // inorder traverse a, mirror traverse b
        while (a && b)
        {
            if (a->data != b->data)
                return false;
            s1.emplace(a);
            s2.emplace(b);
            //mirror traversal
            a = a->left;
            b = b->right;
        }
        if (!(!a && !b))
            return false;
        if (!s1.empty() && !s2.empty())
        {
            a = s1.top()->right; // left subtree has been traversed
            s1.pop();
            b = s2.top()->left; //mirror traversal
            s2.pop();
        }
        else
            break;
    }
    return true;
}

void mirror_tree(TreeNode *root)
{
    //convert a tree to its mirror one
    if (root)
    {
        mirror_tree(root->left);
        mirror_tree(root->right);
        swap(root->left, root->right);
    }
}

void iterative_mirror_tree(TreeNode *root)
{// convert a tree to its mirror one in BFS way
    if (!root)
        return;
    queue<TreeNode *> q;
    q.emplace(root);
    while (!q.empty())
    {
        TreeNode *cur = q.front();
        q.pop();
        swap(cur->left, cur->right); //swap left subtree and right subtree
        if (cur->left)
            q.emplace(cur->left);
        if (cur->right)
            q.emplace(cur->right);
    }
}

/* Driver program to test areMirror() */
int main()
{
    TreeNode *a = new TreeNode(1);
    TreeNode *b = new TreeNode(1);
    a->left = new TreeNode(2);
    a->right = new TreeNode(3);
    a->left->left = new TreeNode(4);
    a->left->right = new TreeNode(5);

    b->left = new TreeNode(3);
    b->right = new TreeNode(2);
    b->right->left = new TreeNode(5);
    b->right->right = new TreeNode(4);

    iterative_mirror_tree(a);
    areIdentical(a, b) ? cout << "Yes" : cout << "No";

    return 0;
}