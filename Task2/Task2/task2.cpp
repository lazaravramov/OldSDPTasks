#include <iostream>
using namespace std;
template <typename T>
struct Node{
    T data;
    Node* next;
    Node(const T& data,Node* n=nullptr):data(data),next(n){}
};
template<typename T>
void free(Node<T>* ll){
    Node<T>* iter=ll;
    while(iter){
        Node<T>* toDelete=iter;
        iter=iter->next;
        delete toDelete;
    }
}
bool areNumbersConsecutive(int a,int b){
    return ((a-1)==b)||((a+1)==b);
}
bool isTotal(Node<int>* ll){
    if(!ll || !ll->next){
        return false;
    }
    Node<int>* iter=ll;
    while(iter&& iter->next){
        if(!areNumbersConsecutive(iter->data, iter->next->data)){
            return false;
        }
        iter=iter->next;
    }
    return true;
}
template <typename T>
void printList(Node<T>* ll){
    Node<T>* iter=ll;
    while(iter){
        cout<<iter->data<<" ";
        iter=iter->next;
    }
}
bool hasConsecutive(Node<int>* ll){
    Node<int>* iter=ll;
    while(iter&& iter->next){
        if(areNumbersConsecutive(iter->data,iter->next->data)){
            return true;
        }
        iter=iter->next;
    }
    return false;
}
bool makeTotal(Node<int>*& ll){
    if(isTotal(ll)){
        return true;
    }
    else{
        Node<int>* iter=ll;
        Node<int>* newList=nullptr;
        Node<int>* newListIter=nullptr;
        while(iter&&iter->next){
            if(areNumbersConsecutive(iter->data, iter->next->data)){
                if(newListIter==nullptr){
                    newListIter=iter;
                    newList=iter;
                }
                else{
                    newListIter->next=iter->next;
                    newListIter=newListIter->next;
                    iter=iter->next;
                }
            }
            else{
                if(newListIter==nullptr){
                    newListIter=iter;
                    newList=iter;
                }
                else{
                    newListIter->next=iter;
                    newListIter=newListIter->next;
                    iter=iter->next;
                }
            }
        }
        newListIter->next=nullptr;
        ll=newList;
        return false;
        }
    }
int main(int argc, const char * argv[]) {
    Node<int>* l1=new Node(2,new Node(1,new Node(2,new Node(3,new Node(4,new Node(3))))));
    cout<<makeTotal(l1);
    free(l1);
    
}
