#include <iostream>
#include<stack>
#include<string>
using namespace std;
void task1(string toChange){
    stack<char> helper;
    for(int i=0;i<toChange.size();i++){
        if(toChange[i]!='*'){
            helper.push(toChange[i]);
        }
        else{
            helper.pop();
        }
    }
    string result(helper.size(),'\0');
    size_t idx=helper.size()-1;
    while(!helper.empty()){
        result[idx--]=helper.top();
        helper.pop();
    }
    cout<<result;
}
bool isBalanced(string s){
    stack<char> helper;
    for(int i=0;i<s.size();i++){
        if(s[i]!=')')
            helper.push(s[i]);
        else{
            if(helper.empty()){
                return false;
            }
            else
                helper.pop();
        }
    }
    return true;
};
void NInstructions(int number){
    int currentMax=INT_MIN;
    int secondMax=INT_MIN;
    stack<int> st;
    int instuction;
    int numberToInsert;
    while(number>0){
        cin>>instuction;
        switch(instuction){
            case 1:
                cin>>numberToInsert;
                if(numberToInsert>=currentMax&& currentMax>=secondMax){
                    secondMax=currentMax;
                    currentMax=numberToInsert;
                    
                }
                else if(st.size()==0){
                    currentMax=secondMax=numberToInsert;
                }
                else if(st.size()==1 && currentMax>numberToInsert){
                    secondMax=numberToInsert;
                }
                st.push(numberToInsert);
                break;
            case 2:
                if(st.size()==1){
                    currentMax=secondMax=INT_MIN;
                }
                if(currentMax==st.top()&& st.size()>1){
                    currentMax=secondMax;
                }
                if(st.size()==0){
                    break;
                }
                st.pop();
                break;
            case 3:
                cout<<currentMax;
                break;
        }
            }
}
void reverseText(string text){
    stack<string> st;
    string word="";
    for(int i=0;i<text.size();i++){
        if(text[i]==' '){
            word+=" ";
            st.push(word);
            word="";
        }
        else{
            word+=text[i];
        }
        if(i==text.size()-1){
            word+=" ";
            st.push(word);
        }
    }
    string result="";
    while(!st.empty()){
        result+=st.top();
        st.pop();
    }
    cout<<result;
}
int main(int argc, const char * argv[]) {
    reverseText("Az sum Lazar");
}
