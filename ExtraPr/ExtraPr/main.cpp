#include <iostream>
#include <vector>
using namespace std;
struct Node{
    int value;
    vector<Node> chilren;
};
void findCheapestRec(Node* root,
int currSum,
vector<Node*>& currPath,
int& outMinSum,
vector<Node*>& outMinPath){
    if(!root)
        return;
    currSum+=root->value;
    currPath.push_back(root);
    if(root->chilren.empty()){
        if(currSum<outMinSum){
            outMinPath=currPath;
            outMinSum=currSum;
        }
    }
    else{
        for(size_t i=0;i<root->chilren.size();i++){
            Node& child=root->chilren[i];
            findCheapestRec(&child, currSum, currPath, outMinSum, outMinPath);
        }
    }
    currPath.pop_back();
}
vector<Node*> findCheapestPath(Node* root){
    if(!root)
        return {};
    vector<Node*> currPath;
    vector<Node*> minPAth;
    int minSum=numeric_limits<int>::max();
    findCheapestRec(root, 0, currPath,minSum,minPAth);
    return minPAth;
}
int main(int argc, const char * argv[]) {

}
