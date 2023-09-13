#include <iostream>
#include<string>
#include<queue>
using namespace  std;
void printAllBinaryNumbers(int n){
    queue<string> q;
    q.push("1");
    while(n){
        string currentNumber=q.front();
        q.pop();
        cout<<currentNumber<<" ";
        q.push(currentNumber+"1");
        q.push(currentNumber+"0");
        n--;
    }
}
int main(int argc, const char * argv[]) {
    printAllBinaryNumbers(10);
    
}
