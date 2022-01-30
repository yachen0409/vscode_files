#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
long long n, count = 0;
vector <long long int*> position; //store inorder's position
vector<long long>inorder, preorder;
/*Tree building function*/
void buildTree(long long * inbegin, long long * inend, long long * prebegin, long long *preend){
    long long* root = position[*prebegin]; //inorder root position by prebegin position
    long long leftsize = root - inbegin;   //preorder's left size by inorder
    long long rightsize = inend - root;     //postorder's right size by inorder
    
    if(leftsize > 1){
        buildTree(inbegin, root-1, prebegin+1, prebegin + leftsize);
    }
    if(leftsize==1){
        cout << *inbegin << " ";
    }
    // cout << "rightsize:"<<rightsize<<endl;
    if(rightsize > 1){
        buildTree(root+1, inend, prebegin+leftsize+1 , preend);
    }
    if(rightsize==1){
        cout << *inend << " ";
    }

    cout << *root << " ";


}

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    cin >> n;
    inorder.resize(n);
    preorder.resize(n);
    position.resize(n+1);
    for(long long j = 0; j < n; ++j){
        long long temp;
        cin >> temp;
        preorder[j] = temp;  //RESIZE
    }
    for(long long j = 0; j < n; ++j){
        long long temp;
        cin >> temp;
        inorder[j] = temp;//RESIZE
        position[temp] = &inorder[j];
    }
    buildTree(&inorder[0], &inorder[n-1], &preorder[0], &preorder[n-1]);
    return 0;
}