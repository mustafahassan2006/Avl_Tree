#include<iostream>
using namespace std;
class Node{
    public:
        Node* left;
        Node* right;
        int data;
        int height;
        Node(int val){
            left = right = nullptr;
            height=0;
            data=val;
        }

};
class Avl{
    private:
        Node* root;
        int getHeight(Node* node){
            if(node==nullptr){
                return -1;
            }
            return node->height;
        }
        int calculateBalanceFactor(Node* node){
            if(node==nullptr){
                return 0;
            }
            return getHeight(node->left)-getHeight(node->right);
        }
        Node* rotateRight(Node* Unbalanced){
            Node* newRoot=Unbalanced->left;
            Unbalanced->left=newRoot->right;
            newRoot->right=Unbalanced;
            Unbalanced->height=max(getHeight(Unbalanced->left),getHeight(Unbalanced->right))+1;
            newRoot->height=max(getHeight(newRoot->left),getHeight(newRoot->right))+1;
            return newRoot;
        }
        Node* rotateLeft(Node* Unbalanced){
            Node* newRoot=Unbalanced->right;
            Unbalanced->right=newRoot->left;
            newRoot->left=Unbalanced;
            Unbalanced->height=max(getHeight(Unbalanced->left), getHeight(Unbalanced->right))+1;
            newRoot->height=max(getHeight(newRoot->left),getHeight(newRoot->right))+1;
            return newRoot;
        }
        Node* insert(Node* curr, int val){
            if(curr==nullptr){
                return new Node(val);
            }
            if(val>curr->data){
                curr->right=insert(curr->right, val);
            }
            else if(val<curr->data){
                curr->left=insert(curr->left, val);
            }
            else{
                return curr;
            }

            curr->height=max(getHeight(curr->left), getHeight(curr->right))+1;

            int balanceFactor=calculateBalanceFactor(curr);
            //ll
            if(balanceFactor>1 && val<curr->left->data){
                return rotateRight(curr);
            }
            //rr
            if(balanceFactor<-1 && val>curr->right->data){
                return rotateLeft(curr);
            }
            //lr
            if(balanceFactor>1 && val>curr->left->data){
                curr->left=rotateLeft(curr->left);
                return rotateRight(curr);
            }
            //rl
            if(balanceFactor<-1 && val<curr->right->data){
                curr->right=rotateRight(curr->right);
                return rotateLeft(curr);
            }
            return curr;
        }
        bool search(Node* node, int val){
            if(node==nullptr){
                return false;
            }
            if(node->data==val){
                return true;
            }
            if(val<node->data){
                return search(node->left, val);
            }
            return search(node->right, val);
        }
        void inorder(Node* node){
            if(node==nullptr){
                return;
            }
            inorder(node->left);
            cout<<node->data<<"\t";
            inorder(node->right);
        }
        void preorder(Node* node){
            if(node==nullptr){
                return;
            }
            cout<<node->data<<"\t";
            preorder(node->left);
            preorder(node->right);
        }
        void postorder(Node* node){
            if(node==nullptr){
                return;
            }
            postorder(node->left);
            postorder(node->right);
            cout<<node->data<<"\t";
        }
    public:
        Avl(){
            root=nullptr;
        }
        void insert(int val){
            root = insert(root, val);
        }
        bool search(int val){
            return search(root, val);
        }
        void inorder(){
            inorder(root);
        }
        void preorder(){
            preorder(root);
        }
        void postorder(){
            postorder(root);
        }
};

int main(){
    Avl tree;
    
    
    tree.insert(10);
    tree.insert(20);
    tree.insert(30); 
    tree.insert(40);
    tree.insert(50); 
    tree.insert(25); 

    cout << "Inorder:  "; tree.inorder();  cout << endl;
    cout << "Preorder: "; tree.preorder(); cout << endl;

    cout << "Search 25: " << tree.search(25) << endl; 
    cout << "Search 99: " << tree.search(99) << endl; 


    return 0;
}