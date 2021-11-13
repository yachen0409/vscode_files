




class Node{
    public:
    Node* left;
    Node* right;
    Node* parent;
    int key;
    Node(int a):left(0), right(0), parent(0), key(a){};
    friend class BST;
};
class BST{
    public:
    Node* root;
    BST():root(0){};
    void insert(int key){
        Node* y = 0; //parent
        Node* x = 0; //current
        Node* insertNode = new Node(key);

        x = root;

        while(x!=NULL){
            y = x;
            if(insertNode->key < x->key){
                x = x->left; 
            }
            else{
                x = x->right;
            }
        }

        insertNode->parent = y;

        if(y==NULL){
            this->root = insertNode;
        }
        else if(insertNode->key < y->key){
            y->left = insertNode;
        }
        else{
            y->right = insertNode;
        }
    }
};
void Postorder(Node *current){
        if (current) {                         // if current != NULL
            Postorder(current->left);     // L
            Postorder(current->right);    // R
            std::cout << current->key << endl;  // V
        }
    }
int main(){
    BST bst;
    int a;
    while(cin >> a){
        bst.insert(a);
    }
    Postorder(bst.root);
    return 0;
}