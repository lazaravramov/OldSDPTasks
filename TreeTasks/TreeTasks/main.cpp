#include <iostream>
#include<vector>
#include<string>
using namespace std;
template <class T>
struct Tree{
    T data;
    Tree* left;
    Tree* right;
    Tree(T data,Tree<T>* l=nullptr,Tree<T>* r=nullptr):data(data),left(l),right(r){}
};
template<class T>
void free(Tree<T>* t){
    if(t==nullptr)
        return;
    free(t->left);
    free(t->right);
    delete t;
}
template<class T>
void insertInBST(Tree<T>* t,const T& elem,bool hasDuplicates=true){
    if(t==nullptr){
        t=new Tree(elem);
        return;
    }
    else if(t->data<elem){
        insertInBST(t->right,elem,hasDuplicates);
    }
    else if(t->data>elem){
        insertInBST(t->left, elem,hasDuplicates);
    }
}
template<class T>
const Tree<T>* getMinNode(const Tree<T>* t){
    assert(t!=nullptr);
    const Tree<T>* iter=t;
    while(iter->left){
        iter=iter->left;
    }
    return iter;
}
template<class T>
const Tree<T>* getMaxNode(const Tree<T>* t){
    assert(t!=nullptr);
    const Tree<T>* iter=t;
    while(iter->right)
        iter=iter->right;
    return iter;
}
template<class T>
bool removeElem(Tree<T>* t,const T& elem){
    if(t==nullptr){
        return false;
    }
    if(t->data>elem){
        removeElem(t->left, elem);
    }
    else if(t->data<elem){
        removeElem(t->right, elem);
    }
    if(!t->left&&!t->right){
        delete t;
        t=nullptr;
    }
    else if(!t->left && t->right){
        Tree<T>* toDelete=t;
        t=t->right;
        delete toDelete;
    }
    else if(!t->right&& t->left){
        Tree<T>* toDelete =t;
        t=t->left;
        delete toDelete;
    }
    else{
        T newData=getMinNode(t->right)->data;
        t->data=newData;
        removeElem(t->right, newData);
    }
    return true;
}
template<class T>
bool contains(Tree<T>* t,const T& elem){
    if(t==nullptr){
        return false;
    }
    if(t->data==elem){
        return true;
    }
    if(t->data<elem)
        contains(t->right, elem);
    return contains(t->left, elem);
}
template <class T>
void printBT(const std::string& prefix,const Tree<T>* node,bool isLeft){
    if(node!=nullptr){
        std::cout<<prefix;
        std::cout<<(isLeft ? ":--":"`--");
        std::cout<<node->data<<endl;
        printBT(prefix + (isLeft ? "|  ":"  "),node->left,true);
        printBT(prefix + (isLeft ? "|  ":"  "),node->right,false);
        
    }
}
template <class T>
void printTree(const Tree<T>* tree){
    printBT("", tree, false);
}
template <class T>
T maxBST(Tree<T>* t){
    while(t->right)
        t=t->right;
    return t->data;
}
template <class T>
T max_elem(Tree<T>* tree){
    T res=tree->data;
    if(tree->left!=nullptr){
        res=std::max(res,max_elem(tree->left));
    }
    if(tree->right!=nullptr){
        res=std::max(res,max_elem(tree->right));
    }
    return res;
}
template <class T>
int height(Tree<T>* t){
    if(t==nullptr){
        return 0;
    }
    else {
        int lDepth=height(t->left);
        int rDepth=height(t->right);
        if(lDepth<rDepth){
            return rDepth+1;
        }
        return lDepth+1;
    }
}
template<class T>
void inOrderTraversal(Tree<T>* t){
    if(t==nullptr)
        return;
    inOrderTraversal(t->left);
    cout<<t->data<<" ";
    inOrderTraversal(t->right);
}
template <class T>
void preOrderTraversal(Tree<T>* t){
    if(t==nullptr)
        return;
    cout<<t->data<<" ";
    preOrderTraversal(t->left);
    preOrderTraversal(t->right);
}
template <class T>
int countLeaves(Tree<T>* t){
    if(t==nullptr){
        return 0;
    }
    if(!t->left && !t->right){
        return 1;
    }
    return countLeaves(t->left)+countLeaves(t->right);
}
template <class T>
int sumOfTree(Tree<T>* t){
    if(!t){
        return 0;
    }
    return t->data +sumOfTree(t->left)+sumOfTree(t->right);
}
template <class T>
int countElements(Tree<T>* t){
    if(!t){
        return 0;
    }
    return 1+ countElements(t->left)+countElements(t->right);
}
template <class T>
Tree<T>* treeFromElement(Tree<T>* t,const T& elem){
    if(t==nullptr){
        return nullptr;
    }
    if(t->data==elem){
        return t;
    }
    Tree<T>* sub=treeFromElement(t->left, elem);
    return sub ? sub:treeFromElement(t->right, elem);
}
template <class T>
void printNumbersOnLevel(Tree<T>* t,int n){
    if(t==nullptr){
        return ;
    }
    if(n==0){
        cout<<t->data<<" ";
    }
    printNumbersOnLevel(t->left, n-1);
    printNumbersOnLevel(t->right, n-1);
}
template <class T>
bool checkIfTheTreeIsBinary(Tree<T>* t,int min,int max){
    if(t==nullptr){
        return true;
    }
    if(t->data<min || t->data>max)
        return false;
    return checkIfTheTreeIsBinary(t->left,min,t->data)&&checkIfTheTreeIsBinary(t->right,t->data,max);
}
template <class T>
bool checkIfTreeIsBT(Tree<T>* t){
    return checkIfTheTreeIsBinary(t, INT_MIN, INT_MAX);
}
template <class T>
Tree<T>* buildFromVector(const vector<T>& v,int start ,int end){
    if(start>end){
        return nullptr;
    }
    int mid=(start+ end)/2;
    Tree<T>* root=new Tree(v[mid]);
    root->left=buildFromVector(v, start, mid-1);
    root->right=buildFromVector(v, mid+1, end);
    return root;
}
template <class T>
bool isSameTree(const Tree<T>* fst,const Tree<T>* snd){
    if(!fst&& !snd){
        return true;
    }
    if((fst&&!snd)||(!fst&&snd)||(fst->data!=snd->data))
        return false;
    return isSameTree(fst->left, snd->left)&&isSameTree(fst->right, snd->right);
}
template <class T>
void rotateLeft(Tree<T>*& tree){
    assert(tree->right!=nullptr);
    Tree<T>* originalRight=tree->right;
    tree->right=originalRight->left;
    originalRight->left=tree;
    tree=originalRight;
}
template <class T>
void rotateRight(Tree<T>*& tree){
    assert(tree->left!=nullptr);
    Tree<T>* originalLeft=tree->left;
    tree->left=originalLeft->right;
    originalLeft->right=tree;
    tree=originalLeft;
}
template<class T>
Tree<T>* kSmallestHelper(Tree<T>* tree,int &i,int k){
    if(tree==nullptr){
        return nullptr;
    }
    Tree<T>* left=kSmallestHelper(tree->left, i, k);
    if(left){
        return left;
    }
    i++;
    if(i==k){
        return tree;
    }
    return kSmallestHelper(tree->right, i, k);
}
template <class T>
T kSmallets(Tree<T>* tree,int k){
    int i=0;
    Tree<T>* root = kSmallestHelper(tree,i, k);
    return root ? root->data : throw std::logic_error("There are fewer nodes then k");
}
template <class T>
T kSmallest(Tree<T>* tree,int k){
    Tree<T>* kTree=kSmallestHelper(tree, k);
    return kTree? kTree->data : throw std::runtime_error("k exceeds tree nodes count");
}
template <class T>
Tree<T>* helper(Tree<T>* tree,Tree<T>* x,Tree<T>* y){
    if(tree==nullptr){
        return nullptr;
    }
    if(tree->data>std::max(x->data,y->data)){
        return helper(tree->left,x,y);
    }
    if(tree->data<std::min(x->data,y->data)){
        return helper(tree->right,x,y);
    }
    return tree;
}
template <class T>
T getLeastCommonAncsestor(Tree<T>* tree,Tree<T>* x,Tree<T>* y){
    Tree<T>* node=helper(tree,x,y);
    return node ? node->data : throw std::runtime_error("exception");
}

int maxValue(Tree<int>* tree){
    if(!tree){
        return INT_MIN;
    }
    int leftMaxValue=maxValue(tree->left);
    int rightMaxValue=maxValue(tree->left);
    int value=INT_MIN;
    if(leftMaxValue>rightMaxValue){
        value=leftMaxValue;
    }
    else{
        value=rightMaxValue;
    }
    if(value<tree->data){
        value=tree->data;
    }
    return value;
}
int minValue(Tree<int>* tree){
    if(!tree){
        return INT_MAX;
    }
    int leftMinValue=minValue(tree->left);
    int rightMinValue=minValue(tree->left);
    int value=INT_MAX;
    if(leftMinValue<rightMinValue){
        value=leftMinValue;
    }
    else{
        value=rightMinValue;
    }
    if(value>tree->data){
        value=tree->data;
    }
    return value;
}
bool checkIfBST(Tree<int>* tree){
    if(!tree){
        return true;
    }
    if(!tree->left&& maxValue(tree->left)>tree->data){
        return false;
    }
    if(!tree->right&& minValue(tree->right)<tree->data){
        return false;
    }
    if(!checkIfBST(tree->left)||!checkIfBST(tree->right)){
        return false;
    }
       return true;
}
template <class T>
Tree<T>* buildFromVector(vector<T> vec,int start ,int end){
    if(start>end){
        return nullptr;
    }
    int mid=(start+end)/2;
    Tree<T>* root=new Tree(vec[mid]);
    root->left=buildFromVector(vec, start, mid-1);
    root->right=buildFromVector(vec, mid+1, end);
    return root;
}
template <class T>
bool isSameBST(const Tree<T>* fst,const Tree<T>* snd) {
    if(!fst&& !snd){
        return true;
    }
    if((!fst&&snd)||(!snd&&fst)||fst->data!=snd->data){
        return false;
    }
    return isSameBST(fst->left, snd->left)&&isSameBST(fst->right, snd->right);
}
template <class T>
void leftRotation(Tree<T>*& tree){
    if(!tree){
        return ;
    }
    Tree<T>* originalRight=tree->right;
    tree->right=originalRight->left;
    originalRight->left=tree;
    tree=originalRight;
}
template <class T>
void rightRotataion(Tree<T>*& tree){
    if(!tree){
        return ;
    }
    Tree<T>* originalLeft=tree->left;
    tree->left=originalLeft->right;
    originalLeft->right=tree;
    tree=originalLeft;
}
template <class T>
std::pair<int, int> findSumHelper(Tree<T>* tree,int x ,int y){
    if(!tree){
        return std::make_pair(0, 0);
    }
    std::pair<int,int> l=std::make_pair(0, 0);
    std::pair<int,int> r=std::make_pair(0, 0);
    if(tree->data>=x){
        l=findSumHelper(tree->left, x, y);
    }
    if(tree->data<=y){
        r=findSumHelper(tree->right, x, y);
    }
    bool oddChildren((l.second+r.second)%2);
    int sum =l.first+r.first;
    int count=l.second+r.second+(tree->data>=x && tree->data<=y);
    if(oddChildren){
        sum+=tree->data;
    }
    return std::make_pair(sum,count);
}
template <class T>
int findSum(Tree<T>* tree,int x,int y){
    return findSumHelper(tree, x, y).first;
}

int countElementsInInterval(Tree<int>* t,int x,int y){
    if(!t){
        return 0;
    }
    if(t->data>=x && t->data<=y){
        return 1 + countElementsInInterval(t->left, x, y) + countElementsInInterval(t->right, x, y);
    }
    return countElementsInInterval(t->left, x, y)+ countElementsInInterval(t->right, x, y);
}


int main(int arg, const char * argv[]) {
    Tree<int> *regularTree = new Tree<int>(1,new Tree<int>(2,new Tree<int>(4),new Tree<int>(5,new Tree<int>(8))),new Tree<int>(3,new Tree<int>(6),new Tree<int>(7,new Tree<int>(9),new Tree<int>(10))));
    cout<<height(regularTree)<<endl;
    cout<<max_elem(regularTree)<<endl;
    inOrderTraversal(regularTree);
    cout<<endl;
    preOrderTraversal(regularTree);
    cout<<endl;
    cout<<countLeaves(regularTree);
    cout<<endl;
    cout<<sumOfTree(regularTree)<<" "<<countElements(regularTree);
    cout<<endl;
    cout<<kSmallets(regularTree, 4);

}
