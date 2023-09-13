#include <iostream>
using namespace std;
#include <stack>
bool closing(char a){
    return (a == ')')||(a == '}')|| (a==']');
}
bool isNumber(char a){
    return a>='1'&& a<='9';
}
bool isBalanced(string niz){
    stack<char> aba;
    for(int i=0;i<niz.length();i++){
        if(closing(niz[i])){
            if(aba.empty())
                return false;
            aba.pop();
        }
        else{
            aba.push(niz[i]);
        }
    }
    if(aba.empty())
        return true;
    return false;
}
int calculate(string number){
    stack<int> resultToPrint;
    resultToPrint.push(number[0]-'0');
    int result=0;
    for(int i=0;i<number.length();i++){
        
    }

}
int main(int argc, const char * argv[]) {
}
