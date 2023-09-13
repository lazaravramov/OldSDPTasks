#include <iostream>
using namespace std;
#include <stack>
int main() {
    stack<char> abb;
    char str[100];
    cin.getline(str,100);
    unsigned i=0;
    unsigned count=0;
    while(str[i]!=0){
        if(str[i]=='*'){
            abb.pop();
            count--;
        }
        else{
            abb.push(str[i]);
            count++;
        }
        i++;
    }
    i=0;
    int iter=0;
    char reverseResult[100];
    char result[100];
    while(!abb.empty()){
        reverseResult[i++]=abb.top();
        abb.pop();
    }
    i--;
    while(i!=-1){
        result[iter++]=reverseResult[i--];
    }
    cout<<result;
    
}
