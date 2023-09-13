#include <iostream>
#include<vector>
using namespace std;
template <typename T>
struct Node{
    T data;
    Node* left;
    Node* right;
    Node(const T& data,Node* left=nullptr,Node* right=nullptr):data(data),left(left),right(right){}
};
template <typename T>
class BinarySearchTree{
private:
    Node<T>* root;
    Node<T>* createBSTFromArray(T* arr,int size){
        if(size<1){
            return nullptr;
        }
        int mid = size/2;
        Node<T>* newRoot=new Node<T>(arr[mid]);
        newRoot->left=createBSTFromArray(arr,mid);
        newRoot->right=createBSTFromArray(arr+mid+1, size-mid-1);
        return newRoot;
    }
    Node<T>* clone(Node<T>* tree)const{
        if(tree==nullptr){
            return nullptr;
        }
        return new Node<T>(tree->data,clone(tree->left),clone(tree->right));
    }
    void free(Node<T>*& tree){
        if(!tree){
            return ;
        }
        free(tree->left);
        free(tree->right);
        delete tree;
    }
    Node<T>* min(Node<T>* tree){
        if(!tree)
            return nullptr;
        while(tree->left){
            tree=tree->left;
        }
        return tree;
    }
    Node<T>* max(Node<T>* tree){
        if(!tree)
            return nullptr;
        while(tree->right){
            tree=tree->right;
        }
        return tree;
    }
    bool contains(Node<T>* tree,const T& x)const{
        if(!tree){
            return false;
        }
        if(tree->data==x){
            return true;
        }
        return contains(tree->left, x)||contains(tree->right, x);
    }
    void insert(Node<T>*& tree,const T& x){
        if(tree==nullptr)
            tree=new Node(x);
        else if(x==tree->data){
            
        }
        else if (x<tree->data){
            insert(tree->left, x);
        }
        else{
            insert(tree->right,x);
        }
    }
    void remove(Node<T>*& tree,const T& x){
        if(!tree)
            return ;
        if(x<tree->data){
            remove(tree->left, x);
        }
        else if(x>tree->Data){
            remove(tree>right,x);
        }
        else{
            if(!tree->left&&!tree->right){
                delete tree;
                tree=nullptr;
            }
            else if(tree->left&&tree->right){
                tree->data=min(tree->right)->data;
                remove(tree->right,tree->data);
            }
            else {
                Node<T>* oldNode=tree;
                tree=tree->left ? tree->left:tree->right;
                delete oldNode;
            }
        }
    }
public:
    BinarySearchTree():root(nullptr){}
    BinarySearchTree(T* arr, int size){
        createBSTFromArray(arr, size);
    }
    BinarySearchTree(const BinarySearchTree<T>& other){
        clone(other);
    }
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other){
        if(this!=other){
            free(root);
            this->root=clone(other.root);
        }
        return *this;
    }
    ~BinarySearchTree(){
        free(root);
    }

    const T& min() const{
        Node<T>* minNode=min(root);
        if(!minNode){
            throw std::runtime_error("Empty tree");
        }
        return minNode->data;
    }
    const T& max() const{
        Node<T>* maxNode=max(root);
        if(!maxNode){
            throw std::runtime_error("Empty tree");
        }
        return maxNode->data;
    }

    bool contains(const T& x) const{
        return contains(root, x);
    }
    void insert(const T& x){
        insert(root, x);
    }
    void remove(const T& x){
        remove(root, x);
    }

    bool empty() const{
        if(root==nullptr){
            return true;
        }
        return false;
    }
        void print(std::ostream& out = std::cout) const;
};
template <typename T>
void insertElement(Node<T>*& tree,const T& el){
    if(!tree){
        tree=new Node(el);
    }
    else if (el<tree->data){
        insertElement(tree->left, el);
    }
    else if (el==tree->data){
        
    }
    else {
        insertElement(tree->right, el);
    }
}
template <typename  T>
T maxElem(Node<T>* tree){
    T value=tree->data;
    if(!tree->left){
        value=max(value,maxElem(tree->left));
    }
    if(!tree->right){
        value=max(value,maxElem(tree->right));
    }
    return value;
}
template <typename T>
int maxHeight(Node<T>* tree){
    if(!tree){
        return 0;
    }
    int lHeight=maxHeight(tree->left);
    int rHeight=maxHeight(tree->right);
    return (lHeight>rHeight) ? lHeight+1 :rHeight+1;
}
template <typename  T>
bool isBST(Node<T>* tree){
    if(!tree){
        return true;
    }
    if(tree->left && tree->left->data>tree->data){
        return false;
    }
    if(tree->right && tree->right->data<tree->data){
        return false;
    }
    return isBST(tree->left)&&isBST(tree->right);
}
template <typename T>
bool areTreesSame(Node<T>* fst,Node<T>* snd){
    if(!fst&&!snd){
        return true;
    }
    if((fst&&!snd)||(!fst&&snd)||fst->data!=snd->data){
        return false;
    }
    return areTreesSame(fst->left, snd->left)&&areTreesSame(fst->right, snd->right);
}
template <typename T>
void leftRotation(Node<T>*& tree){
    Node<T>* originalRight=tree->right;
    tree->right=originalRight->left;
    originalRight->left=tree;
    tree=originalRight;
}
int countElementsBetween(Node<int>* root,int x,int y){
    if(root==nullptr){
        return 0;
    }
    if(root->data>=x&& root->data<=y){
        return 1+countElementsBetween(root->left, x, y)+countElementsBetween(root->right, x, y);
    }
    else{
        return countElementsBetween(root->left, x, y)+countElementsBetween(root->right, x, y);
    }
}
int sumOfElementsINrange(Node<int>* root,int x ,int y){
    if(root==nullptr)
        return 0;
    if(countElementsBetween(root, x, y)%2==1){
        return root->data+sumOfElementsINrange(root->left,x,y)+sumOfElementsINrange(root->right,x,y);
    }
    else
        return sumOfElementsINrange(root->left,x,y)+sumOfElementsINrange(root->right,x,y);
    
}
int sumOfElOnLevel(Node<int>* root,int lvl){
    if(!root){
        return 0;
    }
    if(lvl==0){
        return root->data;
    }
    return sumOfElOnLevel(root->left, lvl-1)+sumOfElOnLevel(root->right, lvl-1);
}
int counterOfElements(Node<int>* tree){
    if(!tree){
        return 0;
    }
    return counterOfElements(tree->left)+counterOfElements(tree->right)+1;
}
template<typename T>
T myMin(Node<int>* t){
    assert(!t);
    while(t->left){
        t=t->left;
    }
    return t->data;
}
template <typename  T>
void removeElem(Node<T>*& t, T el){
    if(!t){
        return;
        
    }
    if(t->data>el){
        removeElem(t->left, el);
    }
    else if(t->data<el){
        removeElem(t->right, el);
    }
    else {
        if(!t->left&&t->right){
            delete t;
            t=nullptr;
        }
        else if (t->left&&t->right){
            t->data=myMin(t->right)->data;
            removeElem(t->right, t->data);
        }
        else {
            Node<T>* toDelete=t;
            t=t->left ? t->left :t->right;
            delete toDelete;
        }
    }
    
}
template <typename T>
bool searchInLevel(Node<T>* root, T itemSearched, int level) {
    if (root == nullptr)
        return false;
    if (root->data == itemSearched && level == 0)
        return true;
    else
        return searchInLevel(root->left, itemSearched, level - 1) || searchInLevel(root->right, itemSearched, level - 1);
}

template <typename T>
bool isSameLevel(Node<T>* root1, Node<T>* root2,int wantedLevel, int level =0 ) {
    if (root1 == nullptr || level > wantedLevel)
        return true;
    else if (level == wantedLevel)
        return searchInLevel(root2, root1->data, wantedLevel);
    else
        return isSameLevel(root1->left, root2, wantedLevel, level + 1) && isSameLevel(root1->right, root2, wantedLevel, level + 1);
}

template <typename T>
bool checkIfSameLevel(Node<T>* root1, Node<T>* root2, int level) {
    return isSameLevel(root1, root2, level) && isSameLevel(root2, root1, level);
}
template <typename  T>
void rotateLeft(Node<T>*& root){
    Node<T>* originalRight=root->right;
    root->right=originalRight->left;
    originalRight->left=root;
    root=originalRight;
}
Node<int>* kSmallestHelper(Node<int>* root,int& i,int k){
    if(!root){
        return nullptr;
    }
    Node<int>* left=kSmallestHelper(root->left, i, k);
    if(left){
        return left;
    }
    i++;
    if(i==k){
        return root;
    }
    return kSmallestHelper(root->right, i, k);
}
int kSmallest(Node<int>* root,int k){
    int i=0;
    Node<int>* smallest=kSmallestHelper(root, i, k);
    return smallest ? smallest->data : throw std::runtime_error("There is no kth smallest");
    
}
int counterOfNumbersInInterval(Node<int>* tree,int x,int y){
    if(!tree){
        return 0;
    }
    if(tree->data>=x&& tree->data<=y){
        return 1+counterOfNumbersInInterval(tree->left, x, y)+counterOfNumbersInInterval(tree->right, x, y);
    }
    return counterOfNumbersInInterval(tree->left, x, y)+counterOfNumbersInInterval(tree->right, x, y);
}
int sumOfElementsInInterval(Node<int>* tree,int x,int y){
    if(!tree){
        return 0;
    }
    bool oddElements=(counterOfNumbersInInterval(tree, x, y)%2==1);
    if(oddElements){
        return tree->data+sumOfElementsInInterval(tree->left, x, y)+(sumOfElementsInInterval(tree->right, x, y));
    }
    return sumOfElementsInInterval(tree->left, x, y)+sumOfElementsInInterval(tree->right, x, y);
}
bool containsElementOnLevel(Node<int>* tree,int el,int level){
    if(!tree){
        return false;
    }
    if(tree->data==el&& level==0){
        return true;
    }
    return containsElementOnLevel(tree->left, el, level-1)||containsElementOnLevel(tree->right, el, level-1);
}
bool treeHaveSameElementsOnLevels(Node<int>* fst,Node<int>* snd,int wantedLevel,int level=0) {
    if(!fst&& level>wantedLevel){
        return true;
    }
    if(wantedLevel==level){
        return containsElementOnLevel(snd, fst->data, wantedLevel);
    }
    else {
       return  treeHaveSameElementsOnLevels(fst->left, snd, wantedLevel,level +1) && treeHaveSameElementsOnLevels(fst->right, snd, wantedLevel,level+1);
    }
}
bool treeHaveEqualElementsOnLevels(Node<int>* fst,Node<int>* snd,int level){
    return treeHaveSameElementsOnLevels(fst,snd,level)&&treeHaveSameElementsOnLevels(snd,fst,level);
}
Node<int>* kSmallestHelpers(Node<int>* t,int& i,int k){
    if(!t){
        return nullptr;
    }
    Node<int>* left=kSmallestHelpers(t->left, i, k);
    if(left){
        return left;
    }
    i++;
    if(i==k){
        return t;
    }
    return kSmallestHelpers(t->right, i, k);
}
int kSmallestNumber(Node<int>* t,int k){
    int i=0;
    Node<int>* root=kSmallestHelpers(t, i, k);
    return root ? root->data :throw std::runtime_error("K is bigger then number of elem");
}
template <typename  T>
void insertEl(Node<T>* t,const T& el){
    if(!t){
        t=new Node<T>(el);
    }
    if(t->data>el){
        insertEl(t->left, el);
    }
    else if(t->data<el){
        insertEl(t->right, el);
    }
    else {
        
    }
}
int main(int argc, const char * argv[]) {
    Node<int>* tree=new Node<int>(3,new Node<int>(2),new Node<int>(5,nullptr,new Node<int>(6)));
    cout<<kSmallestNumber(tree,4);
}
