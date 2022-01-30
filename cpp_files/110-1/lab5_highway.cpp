#include<iostream>
#include<vector>
#include<string>
using namespace std;
long long numoftime, n, m, k, f, s, mstfastnum, mstslownum, mstallnum;
vector<pair<long long, long long>>fastedge, slowedge, alledge;
vector<long long>disjoint;

int find(int x) {return x == disjoint[x] ? x : (disjoint[x] = find(disjoint[x]));}

void merge(int x, int y) {disjoint[find(x)] = find(y);}

long long kruskal(char t){
    long long count = 0;
    for(long long a = 0; a < n; ++a) disjoint[a] = a;
    if(t == 'A'){
        long long e = alledge.size();
        for(long long b = 0; b < e; ++b){
            if(find(alledge[b].first)==find(alledge[b].second)) continue;
            merge(alledge[b].first, alledge[b].second);
            count++;
        }
    }
    else if(t == 'F'){
        long long e = fastedge.size();
        for(long long b = 0; b < e; ++b){
            if(find(fastedge[b].first)==find(fastedge[b].second)) continue;
            merge(fastedge[b].first, fastedge[b].second);
            count++;
        }
    }
    else{
        long long e = slowedge.size();
        for(long long b = 0; b < e; ++b){
            if(find(slowedge[b].first)==find(slowedge[b].second)) continue;
            merge(slowedge[b].first, slowedge[b].second);
            count++;
        }
    }
    return count;
}
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    cin >> numoftime;
    for(long long i = 0; i < numoftime; ++i){
        cin >> n >> m >> k >> f >> s;
        alledge.clear();
        fastedge.clear();
        slowedge.clear();
        disjoint.resize(n);

        for(long long j = 0; j < m; ++j){
            long long point1, point2;
            char roadtype;
            cin >> point1 >> point2 >> roadtype;
            if(roadtype == 'F'){
                fastedge.push_back(make_pair(point1, point2));
            } 
            else{
                slowedge.push_back(make_pair(point1, point2));
            }
            alledge.push_back(make_pair(point1, point2));
        }
        mstallnum = kruskal('A');
        if(mstallnum != n-1){
            cout << "No\n";
            continue;
        } 
        mstfastnum = kruskal('F');
        mstslownum = kruskal('S');
        
        bool find = false;
        for(long long j = mstfastnum; j >= n-1-mstslownum; --j){
            long long minslow = n-1-j;
            if(minslow > mstslownum) break;
            long long temp = minslow*s+j*f;
            if(temp == k){
                find = true;
                break;
            }    
        }
        if(find) cout << "Yes\n";
        else cout << "No\n";
    } 
    
    return 0;
}