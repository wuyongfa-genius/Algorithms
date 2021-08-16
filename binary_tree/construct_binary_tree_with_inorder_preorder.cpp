// C++ program to construct tree from given inorder and preorder traversal
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

void inorder(TreeNode *root)
{
    if (root)
    {
        inorder(root->left);
        cout << root->data << ',';
        inorder(root->right);
    }
}

TreeNode *bulid_tree(vector<int> &in, vector<int> &pre,
                               int in_left, int in_right, unordered_map<int, int> &mp)
{
    /* preorder: root, left_subtree, right_subtree
        inorder: left_subtree, root, right_subtree */
    static int pre_root = 0; //use static variable to increment pre_root whenever construct a node.
    if (in_left > in_right)
        return NULL;
    // construct current root node and increment pre_root
    int pre_root_data = pre[pre_root++];
    TreeNode *root = new TreeNode(pre_root_data);
    // if root has no chlid, return
    if (in_left == in_right)
        return root;
    int in_root = mp[pre_root_data]; // find in_root
    // bulid left subtree
    root->left = bulid_tree(in, pre, in_left, in_root - 1, mp);
    root->right = bulid_tree(in, pre, in_root + 1, in_right, mp);
    return root;
}

TreeNode *iterative_build_tree(vector<int> &in, vector<int> &pre)
{
    int n = in.size(), m = pre.size(), inorder_index = 0;
    if (n == 0 || n != m)
        return NULL;
    TreeNode *root = new TreeNode(pre[0]);
    stack<TreeNode *> s;
    s.emplace(root);
    for (int i = 1; i < n; ++i)
    {
        int preorder_val = pre[i];
        TreeNode *node = s.top();
        if (node->data != in[inorder_index])
        {//have not reached leftmost node
            node->left = new TreeNode(preorder_val);//construct left nodes
            s.emplace(node->left);
        }
        else
        {//reached leftmost node, go back and construct right nodes.
            while (!s.empty() && s.top()->data == in[inorder_index])
            {//reverse inorder is identical to preorder at left path.
                node = s.top();
                s.pop();
                ++inorder_index;
            }
            node->right = new TreeNode(preorder_val);
            s.emplace(node->right);
        }
    }
    return root;
}

/* Driver program to test above functions */
int main()
{
    vector<int> pre = {3, 9, 20, 15, 7}; //
    vector<int> in = {3, 9, 20, 15, 7};  //3,9,20,15,7
    //construct map from inorder to inorder_index
    // unordered_map<int, int> mp;
    // for (int i = 0; i < inorder.size(); ++i)
    //     mp[inorder[i]] = i;
    // TreeNode *root = bulid_tree(in, pre, 0, inorder.size() - 1, mp);
    TreeNode*root=iterative_build_tree(in, pre);
    /* Let us test the built tree by printing
      Inorder traversal */
    cout << "Inorder traversal of the constructed tree is \n";
    inorder(root);
}
