#include<iostream>
using namespace std;
struct Node {
    int data;
    struct Node *left, *right;
    Node(int data)
    {
        this->data = data;
        left = right = NULL;
    }
};
void printPostorder(struct Node* node)
{
    if (node == NULL)
        return;
 
    // first recur on left subtree
    printPostorder(node->left);
 
    // then recur on right subtree
    printPostorder(node->right);
 
    // now deal with the node
    cout << node->data << " ";
}
 
/* Given a binary tree, print its nodes in inorder*/
void printInorder(struct Node* node)
{
    if (node == NULL)
        return;
 
    /* first recur on left child */
    printInorder(node->left);
 
    /* then print the data of node */
    cout << node->data << " ";
 
    /* now recur on right child */
    printInorder(node->right);
}
 
/* Given a binary tree, print its nodes in preorder*/
void printPreorder(struct Node* node)
{
    if (node == NULL)
        return;
 
    /* first print data of node */
    cout << node->data << " ";
 
    /* then recur on left sutree */
    printPreorder(node->left);
 
    /* now recur on right subtree */
    printPreorder(node->right);
}

int main()
{
    struct Node* root = new Node(57);
    root->left = new Node(40);
    root->right = new Node(63);
    root->left->left = new Node(54);
    root->right->left = new Node(60);
    root->right->left->right = new Node(61);
    root->right->right = new Node(80);
    root->right->right->left = new Node(64);
    root->right->right->right = new Node(90);
    root->right->right->right->right = new Node(92);
    printPostorder(root);
    return 0;
} 