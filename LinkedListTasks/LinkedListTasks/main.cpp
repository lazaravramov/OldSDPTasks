#include <iostream>
#include<vector>
#include<queue>
#include<stack>
#include<string>
using namespace std;
template <typename T>
struct Node{
    T value;
    Node<T>* next;
    Node(const T& value,Node<T>* next=nullptr):value(value),next(next){}
};
template <typename T>
int countNodes(Node<T>* ll){
    int count=0;
    while(ll){
        count++;
        ll=ll->next;
    }
    return count;
}
template <typename T>
void insertAtBeg(Node<T>*& ll,T value){
    Node<T>* toInsert=new Node(value);
    toInsert->next=ll;
    ll=toInsert;
}
template <typename T>
void insertAtEnd(Node<T>*& ll,T value){
    Node<T>* toInsert=new Node(value);
    if(!ll){
        ll=toInsert;
        return;
    }
    Node<T>* iter=ll;
    while(iter->next){
        iter=iter->next;
    }
    iter->next =toInsert;
}
template<typename T>
void printLL(Node<T>* ll){
    while(ll){
        cout<<ll->value<<" ";
        ll=ll->next;
    }
}
template<typename T>
bool hasCycle(Node<T>* ll){
    Node<T>* slow=ll;
    Node<T>* fast=ll;
    bool hasCycle=false;
    while(slow && fast && fast->next){
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast){
            return hasCycle=true;
        }
    }
    return hasCycle;
}
template<typename T>
void reverseLL(Node<T>*& ll){
    Node<T>* next=nullptr;
    Node<T>* prev=nullptr;
    while(ll){
        next=ll->next;
        ll->next=prev;
        prev=ll;
        ll=next;
    }
    ll=prev;
    
}
template <typename T>
Node<T>* findMiddle(Node<T>* ll){
    T mid=ll->value;
    Node<T>* slow=ll;
    Node<T>* fast=ll;
    while(slow && fast && fast->next){
        slow=slow->next;
        fast=fast->next->next;
        mid=slow->value;
    }
    return slow;
}
template <typename T>
void reorderLL(Node<T>*& ll){
    if(!ll && !ll->next){
        return;
    }
    Node<T>* iter=ll;
    Node<T>* mid=findMiddle(ll);
    Node<T>* newLL=nullptr;
    reverseLL(mid);
    while(mid->next){
        insertAtBeg(newLL, iter->value);
        iter=iter->next;
        insertAtBeg(newLL, mid->value);
        mid=mid->next;
    }
    insertAtBeg(newLL, mid->value);
    reverseLL(newLL);
    ll=newLL;
}
template <typename T>
void shufflee(Node<T>*& ll){
    if(!ll && !ll->next){
        return ;
    }
    Node<T>* iter=ll;
    Node<T>* mid=findMiddle(ll);
    Node<T>* newLL=nullptr;
    int nodesCount=countNodes(ll);
    if(nodesCount%2==0){
        nodesCount/=2;
        while(nodesCount!=0){
            insertAtEnd(newLL, iter->value);
            iter=iter->next;
            insertAtBeg(newLL, mid->value);
            mid=mid->next;
            nodesCount--;
        }
        ll=newLL;
    }
    else{
        nodesCount/=2;
        mid=mid->next;
        while(nodesCount!=0){
            insertAtEnd(newLL, iter->value);
            iter=iter->next;
            insertAtBeg(newLL, mid->value);
            mid=mid->next;
            nodesCount--;
        }
        insertAtEnd(newLL, iter->value);
        ll=newLL;
    }
}
template <typename T>
T nthElementBeforeEnd(Node<T>* ll,int n){
    reverseLL(ll);
    while(n!=0){
        ll=ll->next;
        n--;
    }
    return ll->value;
}
template <typename T>
void removeDuplicates(Node<T>* ll){
    Node<T>* iter=ll;
    while(iter && iter->next){
        if(iter->value==iter->next->value){
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
template <typename T>
void rearrange(Node<T>*& ll){
    Node<T>* iter=ll;
    Node<T>* evenStart=nullptr;
    Node<T>* evenIter=nullptr;
    Node<T>* oddStart=nullptr;
    Node<T>* oddItter=nullptr;
    while(iter){
        if(iter->value%2==0){
            if(evenStart==nullptr){
                evenStart=evenIter=iter;
            }
            else{
                evenIter->next=iter;
                evenIter=iter;
            }
        }
        else{
            if(oddStart==nullptr){
                oddStart=oddItter=iter;
            }
            else{
                oddItter->next=iter;
                oddItter=iter;
            }
        }
        iter=iter->next;
    }
    if(evenIter){
        evenIter->next=oddStart;
    }
    if(oddItter){
        oddItter->next=nullptr;
    }
    if(evenIter){
    ll=evenStart;
    }
    else{
    ll=oddStart;
    }
}
template <typename T>
void mergeLinkedLists(Node<T>*& l1,Node<T>* l2){
    if(l1==nullptr){
        l1=l2;
        return;
    }
    Node<T>* iter=l1;
    while(iter->next){
        iter=iter->next;
    }
    iter->next=l2;
}
template <typename T>
void reverseKGroup(Node<T>*& ll,int k){
    int counter=0;
    Node<T>* iter=ll;
    Node<T>* toInsert=nullptr;
    Node<T>* newLL=nullptr;
    while(iter){
        insertAtBeg(toInsert, iter->value);
        counter++;
        if(counter==k){
            counter=0;
            mergeLinkedLists(newLL, toInsert);
            toInsert=nullptr;
        }
        iter=iter->next;
    }
    mergeLinkedLists(newLL, toInsert);
    ll=newLL;
}
template <typename T>
Node<T>* mergeTwoSortedLists(Node<T>* l1,Node<T>* l2){
    Node<T>* newLL=nullptr;
    Node<T>* iter1=l1;
    Node<T>* iter2=l2;
    while(iter1 || iter2){
        if(!iter1){
            insertAtEnd(newLL, iter2->value);
            iter2=iter2->next;
        }
        else if(!iter2){
            insertAtEnd(newLL, iter1->value);
            iter1=iter1->next;
        }
        else{
            if(iter2->value>iter1->value){
                insertAtEnd(newLL, iter1->value);
                iter1=iter1->next;
                }
            else{
                insertAtEnd(newLL, iter2->value);
                iter2=iter2->next;
            }
        }
        
    }
    return newLL;
}
template<typename T>
void insertInListButKeepSort(Node<T>*& ll,T value){
    if(!ll){
        Node<T>* toInsert=new Node(value);
        toInsert->next=ll;
        ll=toInsert;
        return;
    }
    Node<T>* iter=ll;
    while(iter && iter->next){
        if(iter->next->value>value && iter->value<value ){
            Node<T>* toInsert=new Node(value);
            toInsert->next=iter->next;
            iter->next=toInsert;
            return;
        }
        iter=iter->next;
    }
    insertAtBeg(ll, value);
}
int sumOfLits(vector<Node<int>*> lists){
    int sum=0;
    for(int i=0;i<lists.size();i++){
        Node<int>* l=lists[i];
        if(!l){
            continue;
        }
        Node<int>* iter=l;
        int count=0;
        while(iter){
            sum+=iter->value*pow(10,count);
            count++;
            iter=iter->next;
        }
        count=0;
        reverseLL(l);
        iter=l;
        while(iter){
            sum+=iter->value*pow(10,count);
            count++;
            iter=iter->next;
        }
    }
    return sum;
}
template <typename T>
bool isQueueSorted(queue<T> q){
    if(q.empty()){
        return true;
    }
    T lastComparedElem=q.front();
    q.pop();
    while(!q.empty()){
        T currentElem=q.front();
        q.pop();
        if(lastComparedElem>currentElem){
            return false;
        }
        lastComparedElem=currentElem;
    }
    return true;
}
template <typename T>
void balanceTwoLists(Node<T>*& l1,Node<T>*& l2,int l1size,int l2size){
    if(l1size>l2size){
        while(l1size-l2size>1){
            insertAtEnd(l2, l1->value);
            Node<T>* toDelete=l1;
            l1=l1->next;
            delete toDelete;
            l1size--;
            l2size++;
        }
    }
    else{
        while(l2size-l1size>1){
            insertAtEnd(l1, l2->value);
            Node<T>* toDelete=l2;
            l2=l2->next;
            delete toDelete;
            l1size++;
            l2size--;
        }
    }
}
template <typename T>
void concatenateQueues(queue<T>& q1,queue<T> q2){
    while(q2.empty()){
        q1.push(q2.front());
        q2.pop();
    }
}
template <typename T>
void balanceQueues(queue<T>& q1,queue<T>&q2,int l1size,int l2size){
    if(l1size>l2size){
        while(l1size-l2size>1){
            T elementToReplace=q1.front();
            q1.pop();
            q2.push(elementToReplace);
            l1size--;
            l2size++;
        }
    }
    else{
        while(l2size-l1size>1){
            T elementToReplace=q2.front();
            q2.pop();
            q1.push(elementToReplace);
            l1size++;
            l2size--;
        }
    }
}
template <typename T>
void fixOurLists(Node<queue<T>>*& ll){
    if(!ll || !ll->next){
        return;
    }
    Node<queue<T>>* iter=ll;
    while(iter->next){
        queue<T> q1=iter->value;
        queue<T> q2=iter->next->value;
        cout<<q1.size();
        if(q1.size()==q2.size()){
            concatenateQueues(q1, q2);
            iter->value=q1;
            if(countNodes(iter)>2){
                iter->next=iter->next->next;
            }
            else{
                iter->next=nullptr;
            }
        }
        else if(max(q1.size(),q2.size())-min(q1.size(),q2.size())>1){
            balanceQueues(q1, q2, q1.size(), q2.size());
            iter->value=q1;
            iter->next->value=q2;
            continue;
        }
        iter=iter->next;
    }
}
bool shouldUnite(string& lhs,string& rhs){
    if(rhs==""||lhs==""){
        return false;
    }
    return lhs[lhs.size()-1]==rhs[0];
}
void absord(Node<string>* lhs,Node<string>* rhs){
    lhs->value.append("->");
    lhs->value.append(rhs->value);
    lhs->next=rhs->next;
    delete rhs;
}
void unite(Node<string>* ll){
    Node<string>* first=ll;
    Node<string>* lexMin=first;
    bool shouldFinish=false;
    do{
        if(ll->next==first){
            shouldFinish=true;
        }
        if(shouldUnite(ll->value, ll->next->value)){
            absord(ll, ll->next);
        }
        else{
            ll=ll->next;
            if(ll->value<lexMin->value){
                lexMin=ll;
            }
        }
    }
    while(!shouldFinish);
}
template <typename T>
int sizeOfStacks(Node<stack<T>>* ll){
    Node<stack<T>>* iter=ll;
    int count=0;
    while(iter){
        stack<T> s=iter->value;
        count+=s.size();
        iter=iter->next;
    }
    return count;
}
template <typename T>
void equalize(Node<stack<T>>*& ll){
    queue<T> elementsToInsert;
    Node<stack<T>>* iter=ll;
    int averageSize=sizeOfStacks(ll)/countNodes(ll);
    while(iter){
        stack<T> current=iter->value;
        while(current.size()>averageSize){
            elementsToInsert.push(current.top());
            current.pop();
        }
        iter->value=current;
        iter=iter->next;
    }
    iter=ll;
    while(!elementsToInsert.empty()){
        stack<T> current=iter->value;
        while(current.size()<averageSize){
            current.push(elementsToInsert.front());
            elementsToInsert.pop();
        }
        iter->value=current;
        iter=iter->next;
    }
}
int main(int argc, const char * argv[]) {
    //Node<int>* n2 = new Node<int>(5,new Node<int>(7,new Node<int>(9,new Node<int>(23,new Node<int>(22)))));
    //Node<int>* n4=new Node<int>(9,new Node<int>(1));

    stack<int> s1;
    s1.push(5);
    s1.push(4);
    s1.push(3);
    s1.push(2);
    s1.push(1);
    
    stack<int> s2;
    s2.push(7);
    s2.push(6);
    
    stack<int> s3;
    s3.push(11);
    s3.push(10);
    s3.push(9);
    s3.push(8);
    
    stack<int> s4;
    s4.push(12);
    
    Node<stack<int>>* ll=new Node<stack<int>>(s1,new Node<stack<int>>(s2,new Node<stack<int>>(s3,new Node<stack<int>>(s4))));
    equalize(ll);
    cout<<"Fixed the texting";
    cout<<"Abrakadbra";
}
