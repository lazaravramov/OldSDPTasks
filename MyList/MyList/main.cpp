#include <iostream>
using namespace std;
template<class T>
struct LinkedListNote{
    T data;
    LinkedListNote<T>* next;
    LinkedListNote(const T& d,LinkedListNote<T>* n=nullptr): data {d},next{n}{}
};
template<class T>
void printList(const LinkedListNote<T>* ll ){
    while(ll != nullptr){
        cout<<ll->data<<" ";
        ll=ll->next;
        
    }
}
template<class T>
void freeList(LinkedListNote<T>* ll){
    while(ll!=nullptr){
        LinkedListNote<T>* toDelete=ll;
        ll=ll->next;
        delete toDelete;
    }
}
template<class T>
void pushFront(LinkedListNote<T>& ll,const T& elem){
    LinkedListNote<T>* toInsert=new LinkedListNote<T>(elem);
    toInsert->next=ll;
    ll=toInsert;
}
int main(int argc, const char * argv[]) {
    using Node=LinkedListNote<int>;
    Node* ll=new Node(1,new Node(2,new Node(3,new Node(4))));
    printList(ll);
    int a=10;
    pushFront(ll,a);
    printList(ll);
}
