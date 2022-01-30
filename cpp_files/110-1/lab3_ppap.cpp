#include <iostream>
#include <map>
#include <cmath>
#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <iomanip>
using namespace std;
class Node {
public:
    string val;
    long long freq;
    Node* lchild;
    Node* rchild;

    Node(string _val, long long _freq, Node* _lchild, Node* _rchild) {
        val = _val;
        freq = _freq;
        lchild = _lchild;
        rchild = _rchild;
    }
};
class comp{
    public:
        bool operator ()(Node* a, Node* b) {
            if(a->freq != b->freq){
                return a->freq > b->freq;
            }
            else{
                return a->val > b->val;
            }
        }
};
map <string, long long> wordfreq;
map <string, long long > huffmanbyte;
vector<map<string, long long>> wordfreqaline;
vector<long long> wordnumaline;
vector <string> linelist;
priority_queue<Node*, vector<Node*>, comp> huffman;
void coding(Node* ptr, string s) {
    if(ptr->lchild == nullptr || ptr->rchild == nullptr) {
        huffmanbyte[ptr->val] = s.length();
        return;
    }
    if(ptr->lchild) coding(ptr->lchild, string(s + "0"));
    if(ptr->rchild) coding(ptr->rchild, string(s + "1"));
}

int main(){
    cout << fixed << setprecision(20);
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long N;
    string line;
    
    cin >> N;
    linelist.resize(N);
    wordfreqaline.resize(N);
    wordnumaline.resize(N, 0);
    getline(cin, line);
    for (long long i = 0; i < N ; ++i){
        getline(cin, line);
        linelist[i] = line;
        stringstream input(line);
        string tempword;
        while(input>>tempword){
            wordfreqaline[i][tempword] += 1;
            wordfreq[tempword] += 1;
            wordnumaline[i]++;
        }
    }
    long double b = ceil(log2(wordfreq.size()));//wordfreq.size()
    for(auto it = wordfreq.begin(); it != wordfreq.end(); it++){
        huffman.push(new Node(it->first, it->second, nullptr, nullptr));
    }
    for(long long i = 0; i < wordfreq.size()-1; i++) {
        Node* ptr1 = huffman.top(); huffman.pop();
        Node* ptr2 = huffman.top(); huffman.pop();
        Node* parentNode = new Node(ptr1->val, ptr1->freq + ptr2->freq, ptr1, ptr2);
        if(ptr1->val > ptr2->val)
        parentNode->val = ptr2->val;
        huffman.push(parentNode);
    }
    coding(huffman.top(), string(""));
    long long i = 0;
    for(auto a = linelist.begin(); a != linelist.end(); a++){
        
        long double numofbyteorigin = b * wordnumaline[i];
        long double numofbytehuffman = 0.0;
        stringstream tempss(*a);
		string temp;
        while (getline(tempss, temp, ' ')) {
			numofbytehuffman += huffmanbyte[temp];
		}
        cout << numofbytehuffman / numofbyteorigin << "\n";
        i++;
    }
    return 0;
}