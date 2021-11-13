#include <iostream>

using namespace std;

struct Node {
    int val;
    Node *next;
    Node() : val(0), next(nullptr) {}
    Node(int x) : val(x), next(nullptr) {}
};

class LinkedList {
public:
    Node *root;
    int len;
    LinkedList() : root(nullptr), len(0) {}
    void push(int);
    void insert(int, int);
    int find(int);
    void remove(int);
    void print();
};

void LinkedList::push(int x){
	// your implementation
    Node* newnode = new Node(x);  //allocate new memory
    if(root == 0){
        root = newnode;
        len++;
        return;
    }

    Node* current = root;
    while(current->next != 0){  //traversal
        current = current->next;
    }
    current->next = newnode;
    len++;
}

void LinkedList::insert(int pos, int x){
	// your implementation 
    Node* current = root; // Initialize current
    if (pos > len){
        cout << "insert fail" << endl;
    }
    else{
        Node* newnode = new Node(x);
        if (pos == 0 && current == nullptr){
            root = new Node(x);
            len++;
            return;
        }
        if (pos == 0){
            newnode->next = current;
            root = newnode;
            len++;
        }
        else{
            for(int i = 0; i < pos-1; i++){
                current = current->next;
            }
            Node* next = current->next;
            current->next = newnode;
            newnode->next = next;
            len++;
        }
    }
}

int LinkedList::find(int x){
	// your implementation
    int count = 0;
    Node* current = root; // Initialize current 
    while (current != NULL) 
    { 
        if (current->val == x) 
            return count;
        count++;  
        current = current->next; 
    } 
    delete current;
    return -1; 
}

void LinkedList::remove(int pos){
	// your implementation
    Node* current = root,
        * previous = 0;
    if (pos > len-1){
        cout<<"remove fail"<<endl;
        return;
    }
    if (pos == 0){
        root = root->next;
        delete current;
        len--;
        return;
    }
    else if (pos == 1){
        current->next = current->next->next;
        len--;
        return;
    }
    for(int i = 0; i < pos; i++){ 
        previous = current; 
        current = current->next; 
    } 
    previous->next = current->next; 
    len--;

}

void LinkedList::print(){
    if(root == nullptr)
        return;

    Node *cur = root;
    while(cur->next != nullptr){
        cout << cur->val << ", ";
        cur = cur->next;
    }
    cout << cur->val << endl;
}

int main(){
    LinkedList mylist;
    
    int n, a, b;
    cin >> n;
    char c;
    for(int i = 0; i < n; i++){
        cin >> c;
        if(c == 'p'){
            cin >> a;
            mylist.push(a);
        }else if(c == 'i'){
            cin >> a >> b;
            mylist.insert(a, b);
        }else if(c == 'r'){
            cin >> a;
            mylist.remove(a);
        }else if(c == 'f'){
            cin >> a;
            cout << mylist.find(a) << endl;
        }else if(c == '?'){
            mylist.print();
        }
    }
    return 0;
}