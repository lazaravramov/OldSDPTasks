#include <iostream>
#include<vector>
using namespace std;
template <typename T>
struct Tree{
    T value;
    Tree<T>* left;
    Tree<T>* right;
    Tree(T value,Tree* left=nullptr,Tree* right=nullptr):value(value),left(left),right(right){}
};

int sumOfElements(Tree<int>* t){
    if(!t){
        return 0;
    }
    return t->value+sumOfElements(t->left)+sumOfElements(t->right);
}
bool containtsEl(Tree<int>* t,int x){
    if(!t){
        return false;
    }
    return t->value==x || containtsEl(t->left, x) || containtsEl(t->right, x);
}
int countEl(Tree<int>* t){
    if(!t){
        return  false;
    }
    return 1+countEl(t->left)+countEl(t->right);
}
int findBiggestEl(Tree<int>* t){
    if(!t){
        throw runtime_error("empty Tree");
    }
    if(!t->left && !t->right){
        return t->value;
    }
    if(t->left && !t->right){
        return max(t->value,findBiggestEl(t->left));
    }
    if(!t->left && t->right){
        return max(t->value,findBiggestEl(t->right));
    }
    return max(t->value,max(findBiggestEl(t->left),findBiggestEl(t->right)));
}
template <typename T>
int countLeafs(Tree<T>* t){
    if(!t){
        return 0;
    }
    if(!t->left && !t->right){
        return 1 ;
    }
    return countLeafs(t->left)+countLeafs(t->right);
}
template <typename  T>
Tree<T>* treeWithXRoot(Tree<T>* t,T value){
    if(!t){
        return nullptr;
    }
    if(t->value==value){
        return  t;
    }
    Tree<T>* left=treeWithXRoot(t->left, value);
    Tree<T>* right=treeWithXRoot(t->right, value);
    if(left){
        return left;
    }
    return right;
}
template <typename T>
void printNLevelEl(Tree<T>* t,int n){
    if(!t){
        return;
    }
    if(n==1){
        cout<<t->value<<" ";
    }
    printNLevelEl(t->left, n-1);
    printNLevelEl(t->right, n-1);
}
template <typename T>
void printTree(Tree<T>* t){
    if(!t){
        return;
    }
    printTree(t->left);
    cout<<t->value<<" ";
    printTree(t->right);
}
template <typename T>
Tree<T>* buildBSTFromArray(T* arr,int size){
    if(size<1){
        return nullptr;
    }
    int mid = size / 2;

       Tree<T>* newRoot = new Tree<T>(arr[mid]);
       newRoot->left = createBSTFromArray(arr, mid);
       newRoot->right = createBSTFromArray(arr + mid + 1, size - mid - 1);

       return newRoot;
}
template <typename T>
bool isBST(Tree<T>* tree){
    if(!tree){
        return true;
    }
    if(tree->left && tree->left->value>tree->value){
        return false;
    }
    if(tree->right && tree->right->value<tree->value){
        return false;
    }
    return isBST(tree->left)&&isBST(tree->right);
}
template <typename T>
void insertInBST(Tree<T>*& tree,T x){
    if(!tree){
        Tree<T>* root=new Tree<T>(x);
        tree=root;
        return;
    }
    if(tree->value>x){
        insertInBST(tree->left, x);
    }
    else if(tree->value==x){
        
    }
    else{
        insertInBST(tree->right, x);
    }
}
template <typename T>
bool containsBST(Tree<T>*& root,T value){
    if(!root){
        return false;
    }
    if(root->value==value){
        return true;
    }
    else if(root->value>value){
        return containsBST(root->left, value);
    }
    else{
        return containsBST(root->right, value);
    }
}
template <typename T>
int heightOfTree(Tree<T>* t){
    if(!t){
        return 0;
    }
    return 1 + max(heightOfTree(t->left),heightOfTree(t->right));
}
template <typename T>
T findMin(Tree<T>* root){}
template <typename T>
void removeFromBST(Tree<T>*& t,T value){
    if(!t){
        return;
    }
    if(t->value>value){
        removeFromBST(t->left, value);
    }
    else if(t->value<value){
        removeFromBST(t->right, value);
    }
    else{
        if(!t->left && !t->right){
            delete t;
            t=nullptr;
        }
        else if(!t->left && t->right){
            Tree<T>* toDelete=t;
            t=t->right;
            delete toDelete;
        }
        else if(t->left && !t->right){
            Tree<T>* toDelete=t;
            t=t->left;
            delete toDelete;
        }
        else{
            t->value=findMin(t->right);
            removeFromBST(t->right,t->value);
            
        }
    }
}
template <typename T>
Tree<T>* findSmallestCommonAncestor(Tree<T>* t,Tree<T>* t1,Tree<T>* t2){
    if(t==nullptr){
        return nullptr;
    }
    if(t->value==t1->value||t->value==t2->value){
        return t;
    }
    Tree<T>* l1=findSmallestCommonAncestor(t->left, t1, t2);
    Tree<T>* r1=findSmallestCommonAncestor(t->right, t1, t2);
    if(!l1 && !r1){
        return t;
    }
    if(l1){
        return l1;
    }
    return r1;
}
std::pair<int, int> findSumHelper(const Tree<int>* t, int x, int y) {
    if(t == nullptr)
        return std::make_pair(0, 0);

    std::pair<int, int> l = std::make_pair(0, 0);
    std::pair<int, int> r = std::make_pair(0, 0);

    if(t->value >= x)
        l  = findSumHelper(t->left, x, y);

    if(t->value<= y)
        r = findSumHelper(t->right, x, y);

    bool oddChildren = ((l.second + r.second) % 2);

    int sum = l.first + r.first;
    int count = l.second + r.second + (t->value >= x && t->value <= y);

    if(oddChildren)
        sum += t->value;

    return std::make_pair(sum, count);
}

int findSum(const Tree<int>* t, int x, int y) {
    return findSumHelper(t, x, y).first;
}
template <typename T>
Tree<T>* kSmallestElHelper(Tree<T>* t,int k,int& i){
    if(!t){
        return nullptr;
    }
    Tree<T>* left=kSmallestElHelper(t->left,k,i);
    if(left){
        return left;
    }
    if(i==k){
        return t->left;
    }
    return kSmallestElHelper(t->right, k, i);
}
template <typename T>
T kSmallestEl(Tree<T>* t,int k){
    int i=0;
    Tree<T>* root=kSmallestElHelper(t, k, i);
    if(root){
        return root->value;
    }
    throw std::runtime_error("k exceeds tree nodes count");
}
void printRLR(Tree<int>* t){
    if(!t){
        return;
    }
    printRLR(t->right);
    printRLR(t->left);
    cout<<t->value;
}
int main(int argc, const char * argv[]) {
    Tree<int>* root=new Tree<int>(1,new Tree<int>(8,new Tree(3)),new Tree<int>(2,new Tree<int>(6),new Tree<int>(4)));
    printRLR(root);
}
