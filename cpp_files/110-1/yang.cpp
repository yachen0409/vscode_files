#include<iostream>
#include<vector>
using namespace std;

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long int T;
    cin>>T;
    for(long long int i=0;i<T;i++){
        vector<long long int> val;
        long long int arr[8];
        long long int N;
        long long int amount[7]={0};
        val.clear();
        cin>>N;
        int flag=1;
        for(long long int t=0;t<N;t++){
        cin>>arr[0]>>arr[1]>>arr[2]>>arr[3]>>arr[4]>>arr[5]>>arr[6]>>arr[7];
        if(arr[1]*1000+arr[2]*500+arr[3]*100+arr[4]*50+arr[5]*10+arr[6]*5+arr[7]*1==arr[0]){
            amount[0]+=arr[1];
            amount[1]+=arr[2];
            amount[2]+=arr[3];
            amount[3]+=arr[4];
            amount[4]+=arr[5];
            amount[5]+=arr[6];
            amount[6]+=arr[7];
        }
        else{
            amount[0]+=arr[1];
            amount[1]+=arr[2];
            amount[2]+=arr[3];
            amount[3]+=arr[4];
            amount[4]+=arr[5];
            amount[5]+=arr[6];
            amount[6]+=arr[7];
            long long int num=arr[1]*1000+arr[2]*500+arr[3]*100+arr[4]*50+arr[5]*10+arr[6]*5+arr[7]-arr[0];
            val.push_back(num);
        }
        }
        for(long long int t=0;t<val.size();t++){
            
                if(val[t]>=1000){
                    long long int count1000=val[t]/1000;
                    if(amount[0]>=count1000){
                    amount[0]=amount[0]-count1000;
                    val[t]=val[t]-1000*count1000; 
                    }
                    else{
                    val[t]=val[t]-1000*amount[0];
                    amount[0]=0;
                    }
                }
                if(val[t]>=500){
                    long long int count500=val[t]/500;
                    if(amount[1]>=count500){
                    amount[1]=amount[1]-count500;
                    val[t]=val[t]-500*count500;
                    }
                    else{
                    val[t]=val[t]-500*amount[1];
                    amount[1]=0;
                    }
                }
                if(val[t]>=100){
                    long long int count100=val[t]/100;
                    if(amount[2]>=count100){
                    amount[2]=amount[2]-count100;
                    val[t]=val[t]-100*count100;
                    }
                    else{
                    val[t]=val[t]-100*amount[2];
                    amount[2]=0;
                    }
                }
                if(val[t]>=50){
                    long long int count50=val[t]/50;
                    if(amount[3]>=count50){
                    amount[3]=amount[3]-count50;
                    val[t]=val[t]-50*count50;
                    }
                    else{
                    val[t]=val[t]-50*amount[3];
                    amount[3]=0;
                    }
                }
                if(val[t]>=10){
                    long long int count10=val[t]/10;
                    if(amount[4]>=count10){
                    amount[4]=amount[4]-count10;
                    val[t]=val[t]-10*count10;
                    }
                    else{
                    val[t]=val[t]-10*amount[4];
                    amount[4]=0;
                    }
                }
                if(val[t]>=5){
                    long long int count5=val[t]/5;
                    if(amount[5]>=count5){
                    val[t]=val[t]-5*count5;
                    amount[5]=amount[5]-count5;
                    
                    }
                    else{
                    val[t]=val[t]-5*amount[5];
                    amount[5]=0;
                    }
                }
                if(val[t]>=1){
                    long long int count1=val[t];
                    if(amount[6]>=count1){
                    val[t]=val[t]-count1;
                    amount[6]=amount[6]-count1;
                    }
                    else{
                    val[t]=val[t]-amount[6];
                    amount[6]=0;
                    }
                }
                if(val[t]==0){
                    break;
                }
            
            if(val[t]!=0){
                cout<<"No"<<'\n';
                flag=0;
                break;
            }
        }
        if(flag){
        cout<<"Yes"<<'\n';
        }
        else{
        continue;
        }
    }
    return 0;
}