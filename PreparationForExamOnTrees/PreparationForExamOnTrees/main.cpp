#include <iostream>
#include <vector>
#include <string>
using namespace std;
template <class T>
struct Tree{
    T data;
    Tree* left;
    Tree* right;
    Tree(T data,Tree* left=nullptr,Tree* right=nullptr):data(data),left(left),right(right){}
};
template <class T>
void free(Tree<T>* tree){
    if(!tree){
        return ;
    }
    free(tree->left);
    free(tree->right);
    delete tree;
}
template <class T>
void printHelper(const Tree<T>* tree,const std::string& prefix,bool isLeft){
    if(tree){
        cout<<prefix;
        cout<<(isLeft ? "|--":"`--");
        cout<<tree->data<<endl;
        printHelper(tree->left,prefix+(isLeft ? "|  ":"  "),true);
        printHelper(tree->right,prefix+(isLeft ? "|  ":"  "),false);
    }
    
}
template <class T>
void printTree(const Tree<T>* tree){
    printHelper(tree, "", false);
}
int sumOfElements(Tree<int>* tree){
    if(!tree){
        return 0;
    }
    return sumOfElements(tree->left)+sumOfElements(tree->right)+tree->data;
}
template <class T>
bool contains(Tree<T>* tree,T& elem){
    if(!tree){
        return false;
    }
    if(tree->data==elem)
        return true;
    return contains(tree->left, elem)||contains(tree->right, elem);
}
template <class T>
int counterOfElements(Tree<T>* tree){
    if(!tree){
        return 0;
    }
    return counterOfElements(tree->left)+counterOfElements(tree->right)+1;
}
int getMax(Tree<int>* tree){
    if(!tree){
        return INT_MIN;
    }
    int value=tree->data;
    int lMax=getMax(tree->left);
    int rMax=getMax(tree->right);
    if(lMax>value){
        value=lMax;
    }
    if (rMax>value){
        value=rMax;
    }
    return value;
}
int getMin(Tree<int>* tree){
    if(!tree){
        return INT_MAX;
    }
    int value=tree->data;
    int lMin=getMin(tree->left);
    int rMin=getMin(tree->right);
    if(lMin<value){
        value=lMin;
    }
    if(rMin<value){
        value=rMin;
    }
    return value;
}
template <class T>
int countLeaves(Tree<T>* tree){
    if(!tree){
        return 0;
    }
    if(!tree->left&&!tree->right){
        return 1;
    }
    return countLeaves(tree->left)+countLeaves(tree->right);
}
template <class T>
Tree<T>* treeFromElement(Tree<T>* tree,T elem){
    if(!tree){
        return nullptr;
    }
    if(tree->data==elem){
        return tree;
    }
    Tree<T>* newTree=treeFromElement(tree->left, elem);
    return newTree ? newTree : treeFromElement(tree->right, elem);
}
int sumOfElementsOnNthLevel(Tree<int>* tree ,int n){
    if(!tree)
        return 0;
    if(n==0){
        return tree->data;
    }
    return sumOfElementsOnNthLevel(tree->left, n-1)+sumOfElementsOnNthLevel(tree->right,n-1);
}
template <class T>
void printElementsOnNthLevel(Tree<int>* tree,int n){
    if(!tree){
        return;
    }
    if(n==0)
        cout<<tree->data<<" ";
    printElementsOnNthLevel<T>(tree->left,n-1);
    printElementsOnNthLevel<T>(tree->right,n-1);
}
template<class T>
int getHeightOfTree(Tree<T>* tree){
    if(!tree){
        return 0;
    }
    else{
        int lHeight=getHeightOfTree(tree->left);
        int rHeight=getHeightOfTree(tree->right);
        if(lHeight>rHeight){
            return lHeight+1;
        }
        else{
            return  rHeight+1;
        }
    }
}
int main(int argc, const char * argv[]) {
    Tree<int>* tree=new Tree<int>(3,new Tree<int>(2,new Tree<int>(1)),new Tree<int>(4,nullptr,new Tree<int>(6)));
}
