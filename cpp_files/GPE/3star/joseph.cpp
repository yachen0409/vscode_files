#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
//約瑟夫環問題
int main(){
    vector<long long>prime(4000);
    vector<long long>visit(35000, 0);
    //build prime table for at least 3501 prime number (max value about 35000)
    //埃拉托斯特尼篩法->find prime number
    //!https://edisonx.pixnet.net/blog/post/61448119-%5Bc&++%5D-%E6%B7%B1%E5%85%A5%E8%B3%AA%E6%95%B8-(2-n)---%E5%9F%83%E6%8B%89%E6%89%98%E6%96%AF%E7%89%B9%E5%B0%BC%E7%AF%A9%E6%B3%95
    long long prime_tag = 0;
    for(long long i = 2; i < 35000; ++i){
        if(!visit[i]){
            // cout << prime_tag << " " << i << ") ";
            prime[prime_tag++] = i;
            for(long long j = i*i; j < 35000; j += i){
                visit[j] =  1;
            }
        }
    }
    //約瑟夫環問題
    //!https://blog.csdn.net/tingyun_say/article/details/52343897
    long long n;
    while(cin >> n){
        if (n==0) break;
        long long kill_pos = 0;
        for(long long i = 2; i <= n; ++i){
            //公式
            //J(i+1) = (J(i)+q)%n
            //q=每數q個人殺1次, n=一桌n個人
            kill_pos = (kill_pos+prime[n-i])%i;
        }
        //被殺的最後一個人的下個位置->活下來
        cout << kill_pos+1 << endl;
    }
    return 0;
}