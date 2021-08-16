// C++ program to find all k-sum paths in BT
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

void print_path(const vector<int> &a, int start = 0)
{
    for (int i = start; i < a.size(); ++i)
        cout << a[i] << ',';
    cout << endl;
}

void find_k_sum_paths_from_root_to_leaf(TreeNode *root, int rest, vector<int> &path)
{
    if (!root)
        return;
    path.emplace_back(root->data);
    rest -= root->data;
    if (rest != 0 || root->left || root->right)
    {
        find_k_sum_paths_from_root_to_leaf(root->left, rest, path);
        find_k_sum_paths_from_root_to_leaf(root->right, rest, path);
    }
    else
        print_path(path);
    path.pop_back();
}

void find_k_sum_paths_from_root(TreeNode *root, int rest, vector<int> &path)
{
    if (!root)
        return;
    path.emplace_back(root->data);
    rest -= root->data;
    if (rest == 0)
    {
        cout << "path found: ";
        print_path(path, 0); //there may be negative values , so wo can't return here
    }
    //recursively find in left subtree and right subtree
    if (root->left)
        find_k_sum_paths_from_root(root->left, rest, path);
    if (root->right)
        find_k_sum_paths_from_root(root->right, rest, path);
    path.pop_back();
}

void find_all_k_sum_paths(TreeNode *root, int target, vector<int> &path)
{
    //traverse in preorder, find all possible paths that sum to target from root.
    if (!root)
        return;
    path.emplace_back(root->data);
    int sum = 0;
    for (int i = path.size() - 1; i >= 0; --i)
    {
        sum += path[i];
        if (sum == target)
        {
            print_path(path, i);
        }
    }
    //find in left subtree and right subtree
    if (root->left)
        find_all_k_sum_paths(root->left, target, path);
    if (root->right)
        find_all_k_sum_paths(root->right, target, path);

    path.pop_back();
}

int num_k_sum_paths(TreeNode *root, int target, int cur_sum, unordered_map<int, int> &um)
{
    /*compute number of k-sum paths. Use a hash map to record trie_value and its repeated times.
    we only need to count all "trie_value1-trie_value2=target".*/
    if (!root)
        return 0; // terminate condition
    int paths = 0;
    cur_sum += root->data;
    paths += um[cur_sum - target]; // add all possible "trie_value1-trie_value2=target" paths
    um[cur_sum] += 1;              //use root to update hash map
    //recursively find in left subtree and right subtree
    paths += num_k_sum_paths(root->left, target, cur_sum, um);
    paths += num_k_sum_paths(root->right, target, cur_sum, um);
    um[cur_sum] -= 1; //backtrack
    return paths;
}

// Driver program
int main()
{
    /*  10
            /     \
        28     13
      /          /     \
 -1          14     15
    \         / \     / \
    1      21 22 23 24*/
    TreeNode *root = new TreeNode(10);
    root->left = new TreeNode(28);
    root->left->left = new TreeNode(-1);
    root->left->left->right = new TreeNode(1);
    root->right = new TreeNode(13);

    root->right->left = new TreeNode(14);
    root->right->right = new TreeNode(15);

    root->right->left->left = new TreeNode(21);
    root->right->left->right = new TreeNode(22);
    root->right->right->left = new TreeNode(23);
    root->right->right->right = new TreeNode(24);

    int sum = 28;
    vector<int> path;

    // find_k_sum_paths_from_root(root, sum, path);
    // find_all_k_sum_paths(root, 28, path);

    unordered_map<int, int> um;
    um[0] = 1;
    cout<<"there are "<<num_k_sum_paths(root, sum, 0, um)<<"  "<<sum<<"-sum paths."<<endl;
    cout<<"they are :"<<endl;
    find_all_k_sum_paths(root, sum, path);
    return 0;
}