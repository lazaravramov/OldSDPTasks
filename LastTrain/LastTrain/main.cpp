#include <iostream>
#include<vector>
#include<queue>
#include<stack>
#include<string>
using namespace std;
template <typename T>
struct Node{
    T data;
    Node* next;
    Node(T data,Node* next=nullptr):data(data),next(next){};
};
struct Tree {
    string data;
    Tree* left;
    Tree* right;

    Tree() = default;
    Tree(string data, Tree* left = nullptr, Tree* right = nullptr) : data(data), left(left), right(right) {}
};

double calculate(Tree* tree) {
    if (!tree)
        return 0;
    if (tree->data[0] >= '0' && tree->data[0] <= '9')
        return stod(tree->data);
    switch (tree->data[0]) {
    case '+':
        return calculate(tree->left) + calculate(tree->right);
    case '-':
        return calculate(tree->left) - calculate(tree->right);
    case '/':
        return calculate(tree->left) / calculate(tree->right);
    case '*':
        return calculate(tree->left) * calculate(tree->right);
    }
    return 0;
}
template <typename T>
void printL(Node<T>* ll){
    Node<T>* iter=ll;
    while(iter){
        cout<<iter->data;
        iter=iter->next;
    }
}
template <typename T>
void free(Node<T>* ll){
    if(!ll)
        return;
    while(ll){
        Node<T>* toDelete=ll;
        ll=ll->next;
        delete toDelete;
    }
}
template <typename T>
void pushFront(Node<T>*& ll,T data){
    if(!ll){
        ll=new Node(data);
        return ;
    }
    Node<T>* toInsert=new Node(data,ll);
    ll=toInsert;
}
template <typename  T>
void reverseLst(Node<T>*& ll){
    if(!ll||!ll->next){
        return ;
    }
    Node<T>* newList=nullptr;
    Node<T>* iter=ll;
    while(iter){
        pushFront(newList, iter->data);
        iter=iter->next;
    }
    ll=newList;
}
template <typename T>
void swapNodes(Node<T>*& fst,Node<T>*& snd){
    T data=fst->data;
    fst->data=snd->data;
    snd->data=data;
}
template <typename T>
void sort(Node<T>*& ll){
    if(!ll&&!ll->next)
        return ;
    Node<T>* iter=ll;
    while(true){
        bool isSwapped=false;
        while(iter->next){
            if(iter->data>iter->next->data){
                swapNodes(iter, iter->next);
                isSwapped=true;
            }
            iter=iter->next;
        }
        iter=ll;
        if(!isSwapped){
            break;
        }
    }
}
struct Cloth {
    char color;
    double price;

    Cloth() = default;
    Cloth(char color, double price) : color(color), price(price) {}
};
void getSizeVector(vector<stack<Cloth>> v,vector<int>& k){
    for(size_t i=0;i<v.size();i++){
        
    }
}
void printShelf(vector<stack<Cloth>> shelf){
    for(size_t i=0;i<shelf.size();i++){
        
    }
}
bool hasSameColorOnTheBottom(vector<Cloth> v1,vector<Cloth> v2){
    return v1[0].color==v2[0].color;
}
void onlyLegitPrice(vector<Cloth>& pile,int minPrice,int maxPrice){
    for(int i=0;i<pile.size();i++){
        if(pile[i].price<minPrice||pile[i].price>maxPrice){
            for(int j =i ;j<pile.size()-1;j++)
                pile[j]=pile[j+1];
                pile.pop_back();
        }
    }
   if( pile[pile.size()-1].price<minPrice||pile[pile.size()-1].price>maxPrice)
    pile.pop_back();
}
bool isLegitColorCloth(Cloth v,vector<char> validColors){
    for(size_t i =0;i<validColors.size();i++){
        if(v.color==validColors[i])
            return true;
    }
    return false;
}
void onlyLegitColor(vector<Cloth>& pile,vector<char> validColors){
    for(int i=0;i<pile.size();i++){
        if(!(isLegitColorCloth(pile[i], validColors))){
            for(int j =i ;j<pile.size()-1;j++)
                pile[j]=pile[j+1];
                pile.pop_back();
        }
    }
    if(!(isLegitColorCloth(pile[pile.size()-1], validColors)))
       pile.pop_back();
      
}
int main(int argc, const char * argv[]) {
    Cloth c1('y', 5.5);
        Cloth c2('r', 10.5);
        Cloth c3('b', 45.5);
        Cloth c4('y', 5.5);
        Cloth c5('g',65.5);
        Cloth c6('o', 1.5);
        Cloth c7('y', 2.5);
        Cloth c8('y', 5.5);
        Cloth c9('y', 5.5);
        Cloth c10('y', 5.5);
        Cloth c11('y', 5.5);

        vector<Cloth> kup1;
        kup1.push_back(c1);
        kup1.push_back(c2);
        kup1.push_back(c3);
        kup1.push_back(c4);
        vector<Cloth> kup2;
        kup2.push_back(c5);
        kup2.push_back(c6);
        kup2.push_back(c7);
        vector<Cloth> kup3;
        kup3.push_back(c8);
        kup3.push_back(c9);
        kup3.push_back(c10);
        kup3.push_back(c11);
     
    
}
