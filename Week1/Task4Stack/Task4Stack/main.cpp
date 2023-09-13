#include <iostream>
#include<vector>
#include<stack>
using namespace std;
int getMinLeft(vector<int>& v,int index){
    stack<int> array;
    for(int i=0;i<index;i++){
        array.push(v[i]);
    }
                   while(true){
            if(array.empty())
                return -1;
            if(array.top()>v[index])
                return array.top();
            else{
                array.pop();
            }
        }
            
}
void sortStack(stack<int> oldStack){
    stack<int> newStack;
    newStack.push(oldStack.top());
    oldStack.pop();
    int tmp=oldStack.top();
    oldStack.pop();
    while(!oldStack.empty()){
        if(tmp>newStack.top()){
            int newTmp=newStack.top();
            newStack.pop();
            newStack.push(tmp);
            tmp=newTmp;
        }
        else{
            
            if(tmp<oldStack.top()){
                newStack.push(oldStack.top());
                oldStack.pop();
            }
            else{
                int newTmp=oldStack.top();
                oldStack.pop();
                newStack.push(tmp);
                tmp=newTmp;
            }
        }
    }
    newStack.push(tmp);
    int sizeOfStack=newStack.size();
    for(int i=0;i<sizeOfStack;i++){
        cout<<newStack.top()<<" ";
        newStack.pop();
    }
}
int main(int argc, const char * argv[]) {
    stack<int> v;
    v.push(1);
    v.push(4);
    v.push(3);
    v.push(8);
    v.push(7);
    v.push(12);
    sortStack(v);
}
