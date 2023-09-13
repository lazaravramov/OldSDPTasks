#include <iostream>
using namespace std;
template <typename T>
class MyQueue{
    T* data;
    size_t cap;
    size_t size;
    size_t get;
    size_t put;
    void free(){
        delete[] data;
    }
    void copyFrom(const MyQueue<T>& other){
        size=other.size;
        get=other.get;
        put=other.put;
        cap=other.cap;
        data=new T[cap];
        for(unsigned i=0;i<size;i++){
            data[i]=other.data[i];
        }
    }
    void resize(){
        cap*=2;
        T* resizedData=new T[cap];
        for(unsigned i=0;i<size;i++){
            resizedData[i]=data[get];
            (++get)%=size;
            
        }
        delete[] data;
        data=resizedData;
        get=0;
        put=size;
    }
public:
    MyQueue(){
        size=0;
        cap=4;
        get=put=0;
        data=new T[cap];
    }
    bool isEmpty(){
        return size==0;
    }
    size_t sizeOfQueue(){
        return size;
    }
    void push(const T& ele){
        if(size==cap)
            resize();
        data[put++]=ele;
        size++;
    }
    void pop(){
        if (put==get){
            cout<<"Queue is empty";
            return ;
        }
        for(unsigned i=0;i<put-1;i++){
            data[i]=data[i+1];
        }
        get--;
    }
    MyQueue<T>& operator=(const MyQueue<T>& other){
        if(this!= other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    MyQueue<T>(const MyQueue<T>& other){
        copyFrom(other);
    }
    ~MyQueue(){
        free();
    }
};
int main() {
    return 0;
}
