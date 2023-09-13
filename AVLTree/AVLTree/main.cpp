#include <iostream>
using namespace std;
template<class T>
class AVLTree{
private:
    struct Node{
        T data;
        Node* left;
        Node* right;
        int height;
        static int getHeight(const Node* r){
            if(!r){
                return 0;
            }
            return r->height;
        }
        static void rotateLeft(Node*& r){
            assert(!r->right);
            Node* originalRight=r->right;
            r->right=originalRight->left;
            originalRight->left=r;
            r=originalRight;
        }
        static void rotateRight(Node*& r){
            assert(!r->left);
            Node* orignalLeft=r->left;
            r->left=orignalLeft->right;
            orignalLeft->right=r;
            r=orignalLeft;
        }
        static void updateHeight(Node*& r){
            if(!r){
                return;
            }
            r->height=std::max(getHeight(r->left),getHeight(r->right))+1;
        }
        static int getBalanceFactor(Node*& r){
            if(!r){
                return 0;
            }
            return getHeight(r->right)-getHeight(r->left);
        }
        static void balanceLeft(Node*& r){
            assert(r);
            int rootBalance=getBalanceFactor(r);
            int leftBalance=getBalanceFactor(r->left);
            
            if(rootBalance==-2){
                if(leftBalance==-1){
                    rotateRight(r->left);
                    updateHeight(r->left->left);
                    updateHeight(r->left);
                }
                rotateLeft(r);
                updateHeight(r->left);
                updateHeight(r);
            }
        }
        static void balanceRight(Node*& r){
            assert(r);
            int rootBalance=getBalanceFactor(r);
            int rightBalance=getBalanceFactor(r->right);
            if(rootBalance==-2){
                if(rightBalance==-1){
                    rotateLeft(r->right);
                    updateHeight(r->right->right);
                    updateHeight(r->right);
                }
                rotateRight(r);
                updateHeight(r->left);
                updateHeight(r);
            }
        }
        Node(const T& d, Node* l, Node* r, int h) : data{ d }, left{ l }, right{ r }, height{ h } {}
    };
    Node* root;
    size_t size;
    Node* findMinNode(Node* r){
        if(r->left==nullptr){
            return r;
        }
        return findMinNode(r->left);
    }
    void freeRec(Node* r){
        if(r==nullptr){
            return ;
        }
        freeRec(r->left);
        freeRec(r->right);
        delete r;
    }
    void insertRec(Node*& r,const T& elem){
        if(!r){
            root=new Node(r,nullptr,nullptr,1);
            size++;
            return;
        }
        if(r->data<elem){
            insertRec(r->right, elem);
            Node::updateHeight(r->right);
            Node::balanceRight(r);
        }
        else if(r->data>elem){
            insertRec(r->left,elem);
                Node::updateHeight(r->left);
                Node::balanceLeft(r);
        }
    }
    bool removeRec(Node*& r,const T& elem){
        if(!r){
            return false;
        }
        if(r->data<elem){
            removeRec(r->right, elem);
            Node::updateHeight(r);
            Node::balanceLeft(r);
        }
        else if(r->data>elem){
            remove(r->left,elem);
            Node::updateHeight(r);
            Node::balanceRight(r);
        }
        else {
            if(!r->left&&!r->right){
                delete r;
                r=nullptr;
                return true;
            }
            else if(r->left&&r->right){
                root->data=findMinNode(r->right)->data;
                removeRec(r->right, r->data);
                Node::updateHeight(r);
                Node::balanceRight(r);
            }
            else if(r->left&&!r->right){
                Node* toDelete=r;
                r=r->left;
                delete toDelete;
            }
            else {
                Node* toDelete=r;
                r=r->right;
                delete toDelete;
            }
            return true;
        }
    }
};
int main(int argc, const char * argv[]) {
}
