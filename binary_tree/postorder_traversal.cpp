// C++ program to print postorder traversal
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

void postorder(TreeNode *root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << endl;
    }
}

void iterative_postorder(TreeNode *root)
{
    /* algorithm
    1.1 Create an empty stack
    2.1 Do following while root is not NULL
        a) Push root's right child and then root to stack.
        b) Set root as root's left child.
    2.2 Pop an item from stack and set it as root.
        a) If the popped item has a right child and the right child 
        is at top of stack, then remove the right child from stack,
        push the root back and set root as root's right child.
        b) Else print root's data and set root as NULL.
    2.3 Repeat steps 2.1 and 2.2 while stack is not empty.
    */
    stack<TreeNode *> s;
    while(root||!s.empty())
    {
        while (root)
        { //push root and right nodes in a stack
            if (root->right)
                s.push(root->right);
            s.push(root);
            root = root->left;
        }
        //Now root is NULL, pop a node out
        root = s.top();
        s.pop();
        if (root->right &&!s.empty() && root->right == s.top())
        { //there is still right node
            s.pop();
            s.push(root);
            root = root->right;
        }
        else
        { // we are now at rightmost.
            cout << root->data << endl;
            root = NULL;
        }
    }
}

void reverse_right(TreeNode* root, bool print=false){
    //helper func to reverse the path from left subtree root to root's inorder predecessor.
    if(!root)return;
    TreeNode* prev=NULL, *post;
    while(root){
        post = root->right;
        if(print)cout<<root->data<<endl;
        root->right = prev;
        prev = root;
        root = post;
    }
}

void Morris_postorder(TreeNode* root, bool writable=true){
    /* algorithm
    ONLY SUPPORT WRITABLE TREE
    1)Create a dummy node and make the root as it’s left child.
    2)Initialize current with dummy node.
    3)While current is not NULL 
        a)If the current does not have a left child traverse the right child(current = current->right)
        b)Otherwise, 
            Find the rightmost child in the left subtree.
            If rightmost child’s right child is NULL
                Make current as the right child of the rightmost node.
                Traverse the left child, current = current->left
            Otherwise, 
                Set the rightmost child’s right pointer to NULL.
                From current’s left child, traverse along with the right children until the rightmost child and reverse the pointers.
                Traverse back from rightmost child to current’s left child node by reversing the pointers and printing the elements.
                Traverse the right child, current = current->right
    */
    if(!writable)return;
    TreeNode* cur = new TreeNode(-1);
    cur->left = root;
    while(cur){
        if(!cur->left)
            cur = cur->right; //directly go to right subtree
        else{
            TreeNode* pre=cur->left; //find inorder predecessor of cur
            while(pre->right&&pre->right!=cur){
                pre = pre->right;
            }
            if(!pre->right){
                pre->right = cur; //link predecessor to cur
                cur = cur->left; //go to left subtree
            }
            else{
                pre->right = NULL; // remove the created link
                TreeNode* next=cur->right; // record next position(right subtree root)
                reverse_right(cur->left); //reverse path from left subtree root to predecessor
                reverse_right(pre, true); //reverse back and traverse
                cur = next; //go to right subtree
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
    Morris_postorder(root);
    return 0;
}