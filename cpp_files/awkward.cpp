#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
long long n, count = 0;
vector<long long> seniority;
vector <long long int*> position;
vector<long long>inorder, postorder;
long long awk = 0;
/*Tree building function*/
void buildTree(long long * inbegin, long long * inend, long long * postbegin, long long *postend){
    if(inbegin == inend){
        return;
    }
    long long* root = position[*postend]; //inorder position
    long long leftsize = root - inbegin;   
    long long rightsize = inend - root;
    if(leftsize != 0){
        long long *leftroot = postbegin + leftsize - 1;
        if (seniority[*leftroot-1] > seniority[*root-1]){
            awk++;
        }
        buildTree(inbegin, root-1, postbegin, postbegin + leftsize - 1);
    }
    if(rightsize!=0){
        long long *rightroot = postend - 1;
        if(seniority[*rightroot-1] > seniority[*root-1]){
            awk++;
        }
        buildTree(root+1, inend, postbegin + leftsize , postend-1);
    }
}

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    cin >> n;
    seniority.resize(n);
    for(long long i = 0; i < n; ++i){
        long long age;
        cin >> age;
        seniority[i] = age;
    }
    inorder.resize(n);
    postorder.resize(n);
    position.resize(n+1);
    for(long long j = 0; j < n; ++j){
        long long temp;
        cin >> temp;
        inorder[j] = temp;//RESIZE
        position[temp] = &inorder[j];
    }
    for(long long j = 0; j < n; ++j){
        long long temp;
        cin >> temp;
        postorder[j] = temp;  //RESIZE
    }
    buildTree(&inorder[0], &inorder[n-1], &postorder[0], &postorder[n-1]);
    cout << awk;
    return 0;
}
