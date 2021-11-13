#include<iostream>

using namespace std;

class Node{
    private:
        int value; 
        Node* next;
    public:
        Node():value(0), next(0){};
        Node(int a): value(a), next(0){};
        friend class linkedlist;
};

class linkedlist{
    private:
        Node* first;
    public:
        linkedlist():first(0){};
        void printlist(){
            if (first == 0){
                cout << "Empty!!" << endl;
                return;
            }
            Node* current = first;
            while(current != 0){
                cout << current->value << " ";
                current = current->next;
            }
            cout << endl;
        }
        void push_front(int x){
            Node* newnode = new Node(x);
            newnode->next = first;
            first = newnode;
        }
        void push_back(int x){
            Node* newnode = new Node(x);  //allocate new memory
            if(first == 0){
                first = newnode;
                return;
            }
            Node* current = first;
            while(current->next != 0){  //traversal
                current = current->next;
            }
            current->next = newnode;
        }
        void deletenode(int x){
            Node* current = first,
                * previous = 0;
            while(current != 0 && current->value != x){
                previous = current;
                current = current->next;
            }
            if (current == 0){
                cout << "No node!!" << endl;
                //return;
            }
            else if (current == first){
                first = current->next;
                delete current;
                current = 0;
            }
            else{
                previous->next = current->next;
                delete current;
                current = 0;
            }
        }
};

int main(){
    linkedlist a;
    a.push_front(21);
    a.push_front(3);
    a.push_back(4);
    a.printlist();


    return 0;
}