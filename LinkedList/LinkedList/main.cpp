#include <iostream>
using namespace std;
#include <stdexcept>
template<class T>
class LinkedList{

    struct LinkedListNode{
        T data;
        LinkedListNode* next;
        LinkedListNode(T data): data(data),next(nullptr){}
    };
    void copyFrom(const LinkedList<T>& other){
        LinkedList* iter=other.head;
        while(iter!=nullptr){
            pushBack(iter->data);
            iter=iter->next;
        }
        sizeOfList=other.sizeOfList;
    }
    void free(){
        while(head!= nullptr){
            LinkedListNode* toDelete=head;
            head=head->next;
            delete toDelete;
        }
        sizeOfList=0;
    }
    LinkedListNode* head;
    LinkedListNode* tail;
    size_t sizeOfList;
public:
    class Iterator{
    private:
        LinkedListNode* currentNode;
        Iterator(LinkedList* arg):currentNode(arg){}
    public:
        Iterator& operator++(){
            if(currentNode==nullptr){
                return* this;
            }
            currentNode=currentNode->next;
            return *this;
        }
        Iterator& operator++(int){
            Iterator temp=*this;
            ++(*this);
            return temp;
        }
        T& operator*(){
            return *this->data;
        }
        bool operator==(const Iterator& other){
            return currentNode=other.currentNode;
        }
        bool operator!=(const Iterator& other){
            return !(*this==other);
        }
        friend class LinkedList;
    };
    LinkedList(){
        sizeOfList=0;
        head=nullptr;
        tail=nullptr;
    }
    bool isEmpty(){
        return sizeOfList==0;
    }
    void pushBack(const T& value){
        LinkedListNode* newNode=new LinkedListNode(value);
        if(isEmpty()){
            head=newNode;
            tail=newNode;
        }
        else{
            tail->next=newNode;
            tail=newNode;
            
        }
        sizeOfList++;
    }
    void popBack(){ 
        if(isEmpty()){
            throw std::logic_error("You want to remove item from empty string");
        }
        if(tail==head){
            delete tail;
            tail==nullptr;
            head=nullptr;
            sizeOfList--;
        }
        else{
            LinkedListNode* newTail=head;
            while(newTail!=tail){
                newTail=newTail->next;
            }
            delete tail;
            tail=newTail;
            tail->next=nullptr;
        }
    }
    void pushFront(const T& value){
        LinkedListNode* newNode=new LinkedListNode(value);
        if(isEmpty()){
            head=newNode;
            tail=newNode;
        }
        else{
            head=value;
        }
        sizeOfList++;
    }
    void popFront(){
        if(isEmpty()){
            throw std::logic_error("You want to remove item from empty string");
        }
        if(head==tail){
            delete head;
            head=tail==nullptr;
            sizeOfList--;
        }
        else{
            LinkedListNode* toDelete=head;
            head=head->next;
            delete toDelete;
            sizeOfList--;
        }
    }
    size_t getSizeOfList()const{
        return sizeOfList;
    }
    T front(){
        if(isEmpty()){
            throw std::logic_error("You want to see element in empty List");
        }
        return head->data;
    }
    T back(){
        if(isEmpty()){
            throw std::logic_error("You want to see element in empty List");
        }
        return tail->data;
    }
    ~LinkedList(){
        free();
    }
    LinkedList& operator=(const LinkedList& other){
        if(this!=&other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    LinkedList(const LinkedList& other){
        copyFrom(other);
    }
};
int main(){
    
}
