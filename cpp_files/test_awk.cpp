#include<iostream>
#include<vector>
using namespace std;
vector<int> in;
vector<int> post;
vector<int> address;
vector<int> arr;
vector<int> num;
int build(int posts,int poste,int ins,int ine){
 int ans=0;
 if(ine-ins>1){
  int root=post.back();
     post.pop_back();
     int position;
     position=address[root]-1;
     //cout<<"address:"<<address[root];
     int llen=position-ins;
     int rlen=ine-position;
     //cout<<"llen:"<<llen <<endl<<"rlen"<<rlen<<endl<<"position:"<<position<<endl;
  int lposts,lposte,lins,line,rposts,rposte,rins,rine;
     if(llen!=0){
      lposts=posts;
         //cout << "lposts: " << lposts << endl;
         lposte=lposts+llen-1;
         //cout<<"lposte:"<<lposte<<endl;
         lins=ins;
         //cout<<"lins:"<<lins<<endl;
         line=lins+llen-1;
         //cout<<"line:"<<line<<endl;
  }
  if(rlen!=0){
   rposts=posts+llen;
         //cout<<"rposts:"<<rposts<<endl;
         rposte=rposts+rlen-1;
         //cout<<"rposte:"<<rposte<<endl;
         rins=position+1;
         //cout<<"rins:"<<rins<<endl;
         rine=ine;
         //cout<<"rine:"<<rine<<endl;
         
  }
     if(arr[root-1]<arr[post[rposte]-1]){
      ans+=1;
  }
  if(arr[root-1]<arr[post[lposte]-1]){
   ans+=1;
  }
  ans+=build(rposts,rposte,rins,rine);
  ans+=build(lposts,lposte,lins,line);
 }
 return ans;
}

int main(){
 int n,temp1,temp2,temp3;
 cin>>n;
 post.resize(n);
 in.resize(n);
 arr.resize(n);
 address.resize(n+1);
 num.resize(n);
 address[0]=0;
 for(int i=0;i<n;i++){
  cin>>arr[i];
 }

 for(int i=0;i<n;i++){
  cin>>in[i];
  num[i]=i+1;
 }
 for(int i=0;i<n;i++){
  cin>>post[i];
 }
 for(int i=0;i<n;i++){
  address[in[i]]=num[i];
 }
 for(int i=0;i<n;i++){
  cout<<address[i];
 }
 cout<<build(0,n-1,0,n-1);
 return 0;
}