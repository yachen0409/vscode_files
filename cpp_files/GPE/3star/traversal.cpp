#include <iostream>
#include <vector>
using namespace std;
vector<char>inorder;
vector<char>preorder;
// A utility function to search x in arr[] of size n
// int search(vector<char> arr, char x, int n)
// {
//     for (int i = 0; i < n; i++)
//         if (arr[i] == x)
//             return i;
//     return -1;
// }
 
// Prints postorder traversal from given
// inorder and preorder traversals
void printPostOrder(long long pre_left, long long pre_right, long long in_left, long long in_right)
{   
    long long parent_pos, leftsize, rightsize;
    for(parent_pos = in_left; parent_pos <= pre_right; ++parent_pos){
        if(inorder[parent_pos] == preorder[pre_left]) break;
    }
    leftsize = parent_pos - in_left;
    rightsize = in_right - parent_pos;
    // The first element in pre[] is always root, search it
    // in in[] to find left and right subtrees
    // int root = search(inorder, preorder[0], n);
 
    // If left subtree is not empty, print left subtree
    if (leftsize > 0)
        printPostOrder(pre_left + 1, pre_left + leftsize, in_left, parent_pos-1);
 
    // If right subtree is not empty, print right subtree
    if (rightsize > 0)
        printPostOrder(pre_left + leftsize + 1, pre_right, parent_pos + 1, in_right);
 
    // Print root
    if(inorder[parent_pos] == preorder[0]){
        cout << inorder[parent_pos];
    }
    else{
        cout << inorder[parent_pos] << " ";
    }
    
}
 
// Driver program to test above functions
int main()
{
    long long n;
    cin >> n;
    while(n--){
        long long size;
        cin >> size;
        // cout << size << endl;
        
        inorder.clear(); preorder.clear();
        inorder.resize(size); preorder.resize(size); 
        // vector<long long>preorder(size, 0);
        for(long long i = 0; i < size; ++i){
            cin >> preorder[i];
            // cout << "i=" << i << endl;
        }
        
        for(long long i = 0; i < size; ++i){
            cin >> inorder[i];
            // cout << "j=" << i << endl;
        }
        // for(long long i = 0; i < size; ++i){
        //     cout << preorder[i] << " ";
        // }
        // cout << endl;
        // for(long long i = 0; i < size; ++i){
        //     cout << inorder[i] << " ";
        // }
        // cout << search(preorder[0], size);
        printPostOrder(0, size-1, 0, size-1);
        cout << endl;
    }
    
    return 0;
}