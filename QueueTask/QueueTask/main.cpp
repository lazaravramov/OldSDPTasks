#include <iostream>
#include<queue>
#include<deque>
#include<vector>
using namespace std;
void printAllBinNumbers(int n){
    queue<string> q;
    q.push("1");
    while(n){
        string curNumber=q.front();
        q.pop();
        cout<<curNumber<<" ";
        q.push(curNumber+"0");
        q.push(curNumber+"1");
        n--;
    }
}
void slidingWindowMaximum(vector<int> numbers,int k){
    deque<int> window;
    vector<int> result;
    for(int i=0;i<k;i++){
        while(!window.empty()&& window.back()<numbers[i]){
            window.pop_back();
        }
        window.push_back(numbers[i]);
    }
    
    result.push_back(window.front());

    for (size_t i = k; i < numbers.size(); i++) {
        if(window.front() == numbers[i - k]) {
            window.pop_front();
        }

        while(!window.empty() && window.back() < numbers[i]) {
            window.pop_back();
        }

        window.push_back(numbers[i]);
        result.push_back(window.front());
    }
    
}
int main(int argc, const char * argv[]) {
    printAllBinNumbers(10);
}
