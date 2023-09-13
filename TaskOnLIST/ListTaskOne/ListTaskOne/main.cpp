#include <iostream>
using namespace std;
#include <stack>
#include<queue>
#include<list>
template <typename T>
struct Node{
    Node* next;
    T data;
    Node(const T& data,Node<T>* n=nullptr):data(data),next(n){}
};
template <typename T>
void printLinkedList( Node<T>* ll){
    Node<T>* iterator=ll;
    while(iterator){
        cout<<iterator->data;
        iterator=iterator->next;
    }
}
template <typename T>
void addElement(Node<T>*& first,const T& data){
    Node<T>* newFirst=new Node(data,first);
    first=newFirst;
}
template<typename T>
void freeList(Node<T>* ll){
    Node<T>* iterator=ll;
    while(iterator){
        Node<T>* toDelete=iterator;
        iterator=iterator->next;
        delete toDelete;
    }
}
template <typename T>
Node<T>* findLastElement(Node<T>* ll){
    Node<T>* iter=ll;
    while(iter->next){
        iter=iter->next;
    }
    return iter;
}
template<typename T>
Node<T>* findLastElementBeforeLastElement(Node<T>* ll,Node<T>* last){
    Node<T>* iter=ll;
    while(iter->next!=last){
        iter=iter->next;
    }
    return iter;
}
template<typename T>
void reverseList(Node<T>*& ll){
    Node<T>* previous=nullptr;
    Node<T>* next=nullptr;
    Node<T>* iterate=ll;
    while(iterate){
        next=iterate->next;
        iterate->next=previous;
        previous=iterate;
        iterate=next;
    }
    ll=previous;
}
template <typename T>
Node<T>* findMiddle( Node<T>* ll){
    Node<T>* slowIt=ll;
    Node<T>* fastIt=ll;
    while(fastIt && fastIt->next){
        slowIt=slowIt->next;
        fastIt=fastIt->next->next;
    }
    return slowIt;
}
template<typename T>
void reorderList(Node<T>* ll){
  if(!ll || !ll->next)
      return;
    Node<T>* mid=findMiddle(ll);
    reverseList(mid);
    Node<T>* firstHalf=ll;
    Node<T>* currentPair=nullptr;
    Node<T>* backOfList=nullptr;
    while(mid){
        currentPair=firstHalf;
        firstHalf=firstHalf->next;
        if(!firstHalf){
            backOfList->next=currentPair;
            backOfList=backOfList->next;
            break;
        }
        currentPair->next=mid;
        mid=mid->next;
        if(backOfList)
            backOfList->next=currentPair;
        backOfList=currentPair->next;
    }
    backOfList->next=nullptr;
}
template<typename T>
unsigned numberOfEl(Node<T>* ll){
    unsigned counter=0;
    Node<T>* iter=ll;
    while(iter){
        counter++;
        iter=iter->next;
    }
    return counter;
}
template<typename T>
bool  hasCycle(Node<T>* ll){
    Node<T>* slowIter=ll;
    Node<T>* FastIter=ll;
    while(slowIter&& FastIter &&FastIter->next){
        slowIter=slowIter->next;
        FastIter=FastIter->next->next;
        if(slowIter==FastIter){
            return true;
        }
    }
    return false;
}
template <typename T>
T nthElementBeforeTail(Node<T>* head,unsigned n){
    unsigned numberOfElements=numberOfEl(head);
    unsigned k=numberOfElements-n;
    while(k!=1){
        head=head->next;
        k--;
    }
    return head->data;
        
    
}
template<typename T>
void removeDuplicates(Node<T>* ll){
    if(!ll || !ll->next){
        return;
    }
    Node<T>* iter=ll;
    while(iter && iter->next){
        if(iter->data==iter->next->data){
            if(iter->next->next){
                Node<T>* toDelete=iter->next;
                iter->next=iter->next->next;
                delete toDelete;
            }
            else{
                Node<T>* toDelete=iter->next;
                iter->next=nullptr;
                delete toDelete;
            }
        }
        else{
            iter=iter->next;
        }
        
    }
}
template<typename  T>
void myReverse(Node<T>*& ll){
    Node<T>* iter=ll;
    Node<T>* next=nullptr;
    Node<T>* prev=nullptr;
    while(iter){
        next=iter->next;
        iter->next=prev;
        prev=iter;
        iter=next;
    }
    ll=prev;
}
template<typename T>
Node<T>* combinedList(Node<T>* l1,Node<T>* l2){
    if(!l1){
        return l2;
    }
    if(!l2){
        return l1;
    }
    Node<T>* start=nullptr;
    Node<T>* iter=nullptr;
    while(l1 && l2){
        Node<T>*& toInsert=(l1->data > l2->data) ? l2:l1;
            if(iter==nullptr){
                start=toInsert;
                iter=toInsert;
            }
            else{
                iter->next=toInsert;
                iter=iter->next;
            }
        toInsert=toInsert->next;
            
        }
    Node<T>* rest=(l1==nullptr) ? l2:l1;
    while(rest){
        iter->next=rest;
        iter=iter->next;
        rest=rest->next;
    }
    iter->next=nullptr;
    return start;
    
}
template<typename  T>
Node<T>* rearrange(Node<T>* ll){
    if(!ll || !ll->next){
        return ll;
    }
    Node<T>* evenStart=nullptr;
    Node<T>* evenIter=nullptr;
    
    Node<T>* oddStart=nullptr;
    Node<T>* oddIter=nullptr;
    while(ll){
        if(ll->data % 2 == 0){
            if(evenIter==nullptr){
                evenStart=ll;
                evenIter=ll;
            }
            else{
                evenIter->next=ll;
                evenIter=evenIter->next;
            }
        }
        else{
            
            if(oddIter==nullptr){
                oddStart=ll;
                oddIter=ll;
            }
            else{
                oddIter->next=ll;
                oddIter=oddIter->next;
            }
        }
        ll=ll->next;
    }

    if(evenIter==nullptr){
        return oddStart;
    }
    
    evenIter->next=oddStart;
    if (oddIter!=nullptr){
        oddIter->next=nullptr;
    }
    return evenStart;
    
    
}
template <typename T>
bool isPalindrome(Node<T>* ll){
    bool hasOddNumberOfElements=(numberOfEl(ll)%2==1);
    Node<T>* middle=findMiddle(ll);
    reverseList(middle);
    Node<T>* iter=ll;
    if(hasOddNumberOfElements){
        while(middle->next){
            if(iter->data!= middle->data)
                return false;
            else{
                middle=middle->next;
                iter=iter->next;
            }
            
        }
        return true;
    }
    else{
        while(middle){
            if(iter->data!= middle->data)
                return false;
            else{
                middle=middle->next;
                iter=iter->next;
            }
        }
        return true;
    }
}
template <typename T>
Node<T>* getNext(Node<T>* head,int k){
    while(k && head){
        head=head->next;
        k--;
    }
    return head;
}
void equalize(Node<stack<int>>* ll){
    stack<int> temp;
    Node<stack<int>>* iter=ll;
    while(iter){
        while(!iter->data.empty()){
            temp.push(iter->data.top());
            iter->data.pop();
        }
        iter=iter->next;
    }
    iter=ll;
    while(!temp.empty()){
        if(iter==nullptr){
            iter=ll;
        }
        iter->data.push(temp.top());
        temp.pop();
        iter=iter->next;
    }
}
void concat(queue<int>& to,queue<int>& from){
    while(!from.empty()){
        to.push(from.front());
        from.pop();
    }
}
bool all(queue<int> q,bool (*pred)(int)){
    while(!q.empty()){
        if(!pred(q.front()))
            return false;
        q.pop();
    }
    return true;
}
void  concatSimilarQue(Node<queue<int>>* ll,bool (*pred)(int)){
    if(!ll|| !ll->next){
        return;
    }
    Node<queue<int>>* iter=ll;
    while(iter && iter->next){
        if(all(iter->data,pred)){
            while(iter->next && all(iter->next->data,pred)){
                Node<queue<int>>* toDelete=iter->next;
                iter->next=iter->next->next;
                concat(iter->data, iter->next->data);
                delete toDelete;
            }
        }
        iter=iter->next;
    }
}
template<typename T>
void anotherReverese(Node<T>*& ll){
    if(!ll||!ll->next){
        return;
    }
    Node<T>* next=nullptr;
    Node<T>* prev=nullptr;
    Node<T>* iter=ll;
    while(iter){
        next=iter->next;
        iter->next=prev;
        prev=iter;
        iter=next;
    }
    ll=prev;
}
template<typename T>
void insertElAtBeg(Node<T>*& ll,T& el){
    Node<T>* toInsert=new Node(el,ll);
    ll=toInsert;
    
}
template<typename T>
void shuffle(Node<T>*& ll){
    if(!ll||!ll->next){
        return;
    }
    Node<T>* firstHalf=ll;
    Node<T>* mid=findMiddle(ll);
    Node<T>* secondHalf=mid;
    myReverse(secondHalf);
    Node<T>* newStart=secondHalf;
    while(secondHalf->next){
        secondHalf=secondHalf->next;
    }
    while(firstHalf!=mid){
        secondHalf->next=firstHalf;
        secondHalf=secondHalf->next;
        firstHalf=firstHalf->next;
    }
    secondHalf->next=nullptr;
    ll=newStart;
    
}
template<class T>
void insertSorted(Node<T>*& ll,T& ele){
    Node<T>* toInsert=new Node(ele);
    if(!ll){
        ll=toInsert;
    }
    else if(ll->data>ele){
        toInsert->next=ll;
        ll=toInsert;
    }
    else if(ll->next==nullptr){
        ll->next=toInsert;
    }
    else{
        Node<T>* iter=ll;
        while(iter->next){
            if(iter->next->data>ele){
                Node<T>* nNext=iter->next;
                iter->next=toInsert;
                toInsert->next=nNext;
                return;
            }
        }
        iter->next=toInsert;
    }
}
Node<int>* partition(Node<int>* ll,int x){
    if(!ll||!ll->next){
        return ll;
    }
    Node<int>* smallListStart=nullptr;
    Node<int>* smallListIter=nullptr;
    Node<int>* bigListStart=nullptr;
    Node<int>* bigListIter=nullptr;
    Node<int>* iter=ll;
    while(iter){
        if(iter->data<x){
            if(smallListIter==nullptr){
                smallListStart=iter;
                smallListIter=iter;
            }
            else{
                smallListIter->next=iter;
                smallListIter=smallListIter->next;
            }
        }
        else{
            if(bigListIter==nullptr){
                bigListIter=iter;
                bigListStart=iter;
            }
            else{
                bigListIter->next=iter;
                bigListIter=bigListIter->next;
            }
        }
        iter=iter->next;
    }
    if(!smallListStart){
        bigListIter->next=nullptr;
        return bigListStart;
    }
    if(!bigListStart){
        smallListIter->next=nullptr;
        return smallListStart;
    }
    smallListIter->next=bigListStart;
    bigListIter->next=nullptr;
    return smallListStart;
    
}
template <typename T>
void nthReverse(Node<T>*& ll){
    Node<T>* iter=ll;
    Node<T>* next=nullptr;
    Node<T>* prev=nullptr;
    while(iter){
        next=iter->next;
        iter->next=prev;
        prev=iter;
        iter=next;
    }
    ll=prev;
}
void reverseEvenElements(Node<int>*& ll){
    if(!ll && !ll->next){
        return;
    }
    Node<int>* iter=ll;
    
    Node<int>* oddStart=nullptr;
    Node<int>* oddIter=nullptr;
    
    Node<int>* evenStart=nullptr;
    Node<int>* evenIter=nullptr;
    
    while(iter){
        if(iter->data%2 ==0){
            if(evenIter==nullptr){
                evenIter=iter;
                evenStart=iter;
            }
            else{
                evenIter->next=iter;
                evenIter=evenIter->next;
            }
        }
        else{
            if(oddIter==nullptr){
                oddIter=iter;
                oddStart=iter;
            }
            else{
                oddIter->next=iter;
                oddIter=oddIter->next;
            }
        }
        iter=iter->next;
    }
    if(!oddIter){
        evenIter->next=nullptr;
        myReverse(evenStart);
        ll=evenStart;
    }
    if(!evenIter){
        oddIter->next=nullptr;
        ll=oddStart;
    }
    evenIter->next=nullptr;
    myReverse(evenStart);
    oddIter->next=evenStart;
    ll=oddStart;
    
}
bool isNumber(char ch){
    return ch>='0'&& ch<='9';
}
bool isOperation(char ch){
    return (ch=='+')||(ch=='-')||(ch=='/')||(ch=='*');
}
int calculate(int x ,int y ,char op){
    int number=0;
    switch(op){
        case '+':
            number=x+y;
            break;
        case '-':
            number=x-y;
            break;
        case'*':
            number= x*y;
            break;
        case '/':
            number=x/y;
            break;
    }
    return number;
}
void calculateQueue(queue<char>& q){
    stack<int> temp;
    while(!q.empty()){
        if(isOperation(q.front())){
            int y=temp.top();
            temp.pop();
            int x=temp.top();
            temp.pop();
            temp.push(calculate(x, y, q.front()));
        }
        else{
            temp.push(q.front()-'0');
        }
        q.pop();
    }
    q.push(temp.top()+'0');
    temp.pop();
}
bool calculateListOfQueus(Node<queue<char>>* ll){
    Node<queue<char>>* iter=ll;
    while(iter){
        calculateQueue(iter->data);
        iter=iter->next;
    }
    return isPalindrome(ll);
}
template <typename T>
bool isThereCycle(Node<T>* ll){
    Node<T>* slowiter=ll;
    Node<T>* fastIter=ll;
    while(slowiter&& fastIter && fastIter->next){
        slowiter=slowiter->next;
        fastIter=fastIter->next->next;
        if(slowiter==fastIter)
            return true;
    }
    return false;
}
template<typename  T>
class LinkedList{
    struct ListNode{
        T data;
        ListNode* next;
        ListNode* prev;
        ListNode(T& data):data(data),next(nullptr),prev(nullptr){};
    };
    ListNode* first;
    ListNode* last;
    void free(){
        ListNode* iter=first;
        while(iter){
            ListNode* toDelete=iter;
            iter=iter->next;
            delete toDelete;
        }
    }
    void copyFrom(const LinkedList& other){
        ListNode* iter=other.first;
        while(iter){
            pushBack(iter->data);
            iter=iter->next;
        }
    }
    class Iterator{
        ListNode* cur;
        Iterator(ListNode* c=nullptr): cur{c}{}
    public:
        Iterator& operator++(){
            if(cur==nullptr){
                return* this;
            }
            cur=cur->next;
            return cur;
        }
        Iterator& operator++(int){
            if(cur==nullptr){
                return *this;
            }
            Iterator* tmp=*this;
            cur=cur->next;
            return tmp;
        }
        Iterator& operator--(){
            if(cur==nullptr){
                return *this;
            }
            cur=cur->prev;
            return cur;
        }
        Iterator& operator--(int){
            if(cur==nullptr){
                return *this;
            }
            Iterator tmp=*this;
            cur=cur->prev;
            return tmp;
        }
        bool operator==(const Iterator& other){
            return cur==other.cur;
        }
        bool operator!=(const Iterator& other){
            return !(*this==other);
        }
        friend class LinkedList;
    };
public:
    void pushBack(const T& data){
        ListNode toInsert=new ListNode(data);
        if(last==nullptr){
            last=toInsert;
            first=toInsert;
        }
        else{
            toInsert->prev=last;
            last->next=toInsert;
            last=toInsert;
            
        }
    }
    Iterator begin(){
        return Iterator(first);
        
    }
    Iterator end(){
        return Iterator(last);
    }
    void insert(Iterator at,const T& elem){
        
    }
    LinkedList(){
        first=nullptr;
        last=nullptr;
    }
    ~LinkedList(){
        free();
    }
};
template <typename T>
void deleteNode(Node<T>*& ll,const T& value){
    Node<T>* iter=ll;
    Node<T>* prev=nullptr;
    if(iter&& iter->data==value){
        ll=iter->next;
        delete iter;
        return;
    }
    else{
        while(iter&& iter->data!=value){
            prev=iter;
            iter=iter->next;
        }
        if(iter==nullptr){
            return;
        }
        prev->next=iter->next;
        delete iter;
    }
}
template <typename T>
T findMinElem(Node<T>* ll){
    if(!ll){
        throw std::logic_error("You want to find element in empty array");
    }
    Node<T>* iter=ll;
    T minElem=iter->data;
    while(iter){
        if(minElem>iter->data){
            minElem=iter->data;
        }
        iter=iter->next;
    }
    return minElem;
}
void example() {
    Node<int>* l1 = new Node(1, new Node(2,new Node(3,new Node(4,new Node(5,new Node(6))))));
    deleteNode(l1, 7);
    printLinkedList(l1);
    freeList(l1);
}
int main(int argc, const char * argv[]) {
    example();
}
