#include <iostream>
using namespace std;
template <typename T>
class MyStack{
    T* data;
    size_t capacity;
    size_t size;
    void resize(){
        capacity*=2;
        T* resizedData=new T[capacity];
        for(unsigned i=0;i<size;i++){
            resizedData[i]=data[i];
        }
        delete[] data;
        data=resizedData;
    }
    void copyFrom(const MyStack<T>& other){
        capacity=other.capacity;
        size=other.size;
        data=new T[capacity];
        for(unsigned i=0;i<size;i++){
            data[i]=other.data[i];
        }
    }
    void free(){
        delete[] data;
    };
public:
    MyStack(){
        capacity=4;
        data=new T[capacity];
        size=0;
    }
    MyStack<T>(const MyStack<T>& other){
        copyFrom(other);
    }
    MyStack<T>& operator=(const MyStack<T>& other){
        if(this!=other){
            free();
            copyFrom(other);
        }
        return *this;
    }
    ~MyStack(){
        free();
    }
    void push(const T& obj){
        if(size==capacity)
            resize();
        data[size++]=obj;
    }
    void pop(){
        if(size==0)
            throw "Error 404";
        else size--;
    }
    T& top(){
        if(size==0)
            throw "Exception";
        return data[size-1];
    }
};
int main() {
    MyStack<int> a;
    a.push(4);
   cout<< a.top();
    a.push(3);
    a.push(2);
    cout<<a.top();
    a.pop();
    a.pop();
    a.pop();
    a.pop();
}
