#include <iostream>
#include<stdexcept>
using namespace std;
template <class T>
struct QueueNode{
    T data;
    QueueNode<T>* next;
    QueueNode(T data):data(data),next(nullptr){}
};
template<class T>
class LinkedQueue{
    QueueNode<T>* head;
    QueueNode<T>* tail;
    void free(){
        QueueNode<T>* iter=head;
        while(iter!=nullptr){
            QueueNode<T>* toDelete=iter;
            iter=iter->next;
            delete toDelete;
        }
    }
    void copyFrom(const LinkedQueue<T>& other){
        QueueNode<T>* iter=other.head;
        while(iter!=nullptr){
            enqueue(iter->data);
            iter=iter->next;
        }
    }
public:
    LinkedQueue(){
        head=nullptr;
        tail=nullptr;
    }
    LinkedQueue(const LinkedQueue<T>& other){
        copyFrom(other);
    }
    LinkedQueue<T>& operator=(const LinkedQueue<T>& other){
        if(this!=&other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    void enqueue(const T& value){
        QueueNode<T>* newNode=new QueueNode<T>(value);
        if(isEmpty()){
            tail=newNode;
            head=newNode;
        }
        else{
            tail->next=newNode;
            tail=newNode;
        }
    }
    T front(){
        if(isEmpty()){
            std::logic_error("You want element from empty Queue");
        }
        return head->data;
    }
    void dequeue(){
        if(isEmpty()){
            std::logic_error("You want to remove element from empty Queue");
        }
        if(head==tail){
            delete head;
            head=nullptr;
            tail=nullptr;
        }
        else {
            QueueNode<T>* toDelete=head;
            head=head->next;
            delete toDelete;
        }
    }
    bool isEmpty(){
        return head==nullptr;
    }
    ~LinkedQueue(){
        free();
    }
};
int main() {
    LinkedQueue<int> q;
       q.enqueue(1);
       q.enqueue(2);
       q.enqueue(3);
       q.enqueue(4);
       q.enqueue(5);

       std::cout << q.front() << std::endl; q.dequeue();
       std::cout << q.front() << std::endl; q.dequeue();
       std::cout << q.front() << std::endl; q.dequeue();
       std::cout << q.front() << std::endl; q.dequeue();
       std::cout << q.front() << std::endl; q.dequeue();
    }
