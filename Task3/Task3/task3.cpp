#include <iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;
bool isSymbolLegit(char a,string word){
    unsigned long wordLen=word.length();
    for(int i=0;i<wordLen;i++){
        if(a== word[i]){
            return true;
        }
    }
    return false;
}
int counterOfOccurences(char a ,string word){
    unsigned counter=0;
    unsigned long wordLen=word.length();
    for(int i=0;i<wordLen;i++){
        if(a==word[i]){
            counter++;
        }
    }
    return counter;
}
void reverseQueue(queue<char>& q){
    stack<char> tempStack;
    queue<char> reverseQueue;
    while(!q.empty()){
        tempStack.push(q.front());
        q.pop();
    }
    while(!tempStack.empty()){
        reverseQueue.push(tempStack.top());
        tempStack.pop();
    }
    q=reverseQueue;
}
bool canWordBeRead(queue<char>& q,string word){
    string myWord="";
    queue<char> newQ;
    while(!q.empty()){
        if(isSymbolLegit(q.front(), word) && ((counterOfOccurences(q.front(),myWord))!=(counterOfOccurences(q.front(),word)))){
            myWord+=q.front();
            q.pop();
        }
        else{
                newQ.push(q.front());
                q.pop();
        }
    }
    reverseQueue(newQ);
    if(myWord==word){
        q=newQ;
        return true;
    }
    q=newQ;
    return false;
}
int main(int argc, const char * argv[]) {
    string word="mom";
    queue<char> q;
    q.push('m');
    q.push('f');
    q.push('o');
    q.push('o');
    q.push('m');
    cout<<canWordBeRead(q, word);
    cout<<q.front();
    q.pop();
    cout<<q.front();
}
