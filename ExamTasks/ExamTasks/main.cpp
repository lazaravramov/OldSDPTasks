#include <iostream>
#include<vector>
#include<string>
#include<queue>
#include<string>
using namespace std;
struct List{
    int data;
    List* next;
    List(int data,List* next=nullptr):data(data),next(next){}
};
template <typename T>
struct DLList{
    T data;
    DLList<T>* next,prev;
};
template <typename T>
struct Node
{
    T data;
    Node *left, *right;
    Node(T data,Node* left=nullptr,Node* right=nullptr):data(data),left(left),right(right){}
};
class Graph
{
    int vertices;
    std::vector<std::vector<int>> adjList;

public:
    Graph(int vertices) : vertices(vertices), adjList(vertices, std::vector<int>()) {}

    Graph(int vertices, std::vector<std::pair<int, int>> edges) : Graph(vertices)
    {
        int edgesCount = edges.size();
        for (int i = 0; i < edgesCount; i++)
        {
            adjList[edges[i].first].push_back(edges[i].second);
            adjList[edges[i].second].push_back(edges[i].first);
        }
    }
    void BFS(int start, std::vector<bool>& visited, int& sum, int& vertexCount){
        std::queue<int> q;
            q.push(start);
            visited[start] = true;

            while (!q.empty())
            {
                int currentVertex = q.front();
                q.pop();

                sum += currentVertex;
                vertexCount++;
                
                int size=adjList[currentVertex].size();
                for (int i = 0; i < size; i++)
                {
                    int neighbour=adjList[currentVertex][i];
                    if (!visited[neighbour])
                    {
                        visited[neighbour] = true;
                        q.push(neighbour);
                    }
                }
            }
    }
    double getAverageOfConnectedComponents(){
        vector<bool> visited(adjList.size(),false);
        double result=0;
        for(int i=0;i<adjList.size();i++){
            if(!visited[i]){
                int vertexCount=0,sum=0;
                BFS(i,visited,sum,vertexCount);
                result+=((double) sum/vertexCount);
            }
        }
        return result;
    }
    void getEvenSumOddSum(int start, int& odd, int& even)
    {
        std::queue<std::pair<int, bool>> q; // true -> even
        std::vector<bool> visited(vertices, false);

        q.push({start, true});
        visited[start] = true;

        while (!q.empty())
        {
            std::pair<int, bool> current = q.front();
            q.pop();

            if (current.second)
            {
                even += current.first;
            }
            else
            {
                odd += current.first;
            }

            int size = adjList[current.first].size();
            for (int i = 0; i < size; i++)
            {
                int neightbour = adjList[current.first][i];
                if (!visited[neightbour])
                {
                    q.push(std::make_pair(neightbour, !current.second));
                    visited[neightbour] = true;
                }
            }
        }
    }
    vector<int> bfs(int start,vector<bool>& visited){
        vector<int> currentComp;
        queue<int> q;
        q.push(start);
        while(!q.empty()){
            int current=q.front();
            q.pop();
            if(visited[current]){
                continue;
            }
            currentComp.push_back(current);
            visited[current]=true;
            for(int i=0;i<adjList[current].size();i++){
                if(!visited[adjList[current][i]]){
                    q.push(adjList[current][i]);
                }
            }
        }
        return currentComp;
    }
    int bfss(int start,vector<bool>& visited){
        int currentMax=INT_MIN;
        queue<int> q;
        q.push(start);
        while(!q.empty()){
            int current=q.front();
            q.pop();
            currentMax=max(currentMax,current);
            if(visited[current]){
                continue;
            }
            visited[current]=true;
            for(int i=0;i<adjList[current].size();i++){
                if(!visited[adjList[current][i]]){
                    q.push(adjList[current][i]);
                }
            }
        }
        return currentMax;
    }
    int sumOfConnectedComponents(){
        vector<bool> visited(vertices,false);
        int result=0;
        for(int i=0;i<vertices;i++){
            if(!visited[i]){
                result+=bfss(i, visited);
            }
        }
        return result;
    }
    vector<vector<int>> getConnectedComponents(){
        vector<bool> visited(vertices,false);
        vector<vector<int>> connectedComponents;
        for(int i=0;i<vertices;i++){
            if(!visited[i]){
                vector<int> current=bfs(i,visited);
                connectedComponents.push_back(current);
            }
        }
        return connectedComponents;
    }
};

void storeWords(Node<char>* root,vector<string>& words){
    if(!root){
        return;
    }
    queue<Node<char>*> q;
    q.push(root);
    while(!q.empty()){
        int size=q.size();
        string level;
        for(int i=0;i<size;i++){
            Node<char>* current=q.front();
            q.pop();
            level.push_back(current->data);
            if(current->left){
                q.push(current->left);
            }
            if(current->right){
                q.push(current->right);
            }
        }
        words.push_back(level);
    }
    
}

template<typename T>
void zigZag(Node<T>* root,vector<vector<T>>& levels){
    if(!root){
        return;
    }
    queue<Node<T>*> q;
    q.push(root);
    int levelCheck=0;
    while(!q.empty()){
        int size=q.size();
        vector<T> level;
        for(int i=0;i<size;i++){
            Node<T>* current=q.front();
            q.pop();
            if(levelCheck){
                level.insert(level.begin(), current->data);
            }
            else{
                level.push_back(current->data);
            }
            if(current->left){
                q.push(current->left);
            }
            if(current->right){
                q.push(current->right);
            }
        }
        levels.push_back(level);
        levelCheck++;
    }
}
int getRootToLeafSum(Node<int>* root){
    if(!root){
        return 0;
    }
    if(!root->left && !root->right){
        return root->data;
    }
    int left=0;
    if(root->left &&  root->left->data<root->data){
        left+=getRootToLeafSum(root->left);
    }
    int right=0;
    if(root->right &&  root->right->data<root->data){
        right+=getRootToLeafSum(root->right);
    }
    return (left > right? left : right) + root->data;
}
void rightLook(Node<int>* root,int level,int* maxLevel,vector<int>& result){
    if(!root){
        return;
    }
    if(*maxLevel<level){
        result.push_back(root->data);
        *maxLevel=level;
    }
    rightLook(root->right, level+1, maxLevel, result);
    rightLook(root->left, level+1, maxLevel, result);
}
vector<int> rightView(Node<int>* root){
    vector<int> result;
    int maxLevel=0;
    rightLook(root,1,&maxLevel, result);
    return result;
}
template <typename T>
void getAllPathsHelper(Node<T>* root,vector<vector<T>>& result,vector<T> current){
    if(!root){
        return;
    }
    if(root->left||root->right){
        current.push_back(root->data);
    }
    else{
        current.push_back(root->data);
        result.push_back(current);
    }
    getAllPathsHelper(root->left, result, current);
    getAllPathsHelper(root->right, result, current);
}
template <typename T>
vector<vector<T>> allPaths(Node<T>* root){
    vector<vector<T>> result;
    vector<T> curr;
    getAllPathsHelper(root,result, curr);
    return result;
}
template <typename T>
void getLevels(Node<T>* root,vector<vector<T>>& result){
    if(!root){
        return ;
    }
    queue<Node<T>*> q;
    q.push(root);
    while(!q.empty()){
        int size=q.size();
        vector<T> level;
        for(int i=0;i<size;i++){
            Node<T>* current=q.front();
            q.pop();
            level.push_back(current->data);
            if(current->left){
                q.push(current->left);
            }
            if(current->right){
                q.push(current->right);
            }
        }
        result.push_back(level);
    }
}
template <typename T>
void sortAllVectors(vector<vector<T>>& v1){
    for(int i=0;i<v1.size();i++){
        vector<int> toSort=v1[i];
        sort(toSort.begin(),toSort.end());
        v1[i]=toSort;
    }
}

bool sameLeveles(Node<int>* r1,Node<int>* r2){
    vector<vector<int>> l1;
    vector<vector<int>> l2;
    getLevels(r1, l1);
    getLevels(r2, l2);
    sortAllVectors(l1);
    sortAllVectors(l2);
    if(l1.size()!=l2.size()){
        return false;
    }
    for(int i=0;i<l1.size();i++){
        if(l1[i]!=l2[i]){
            return false;
        }
    }
    return true;
}
void getAllLeftOriented(const Node<int>* root,bool madeRightMove,vector<vector<int>>& result,vector<int>& path){
    if(!root){
        return;
    }
    path.push_back(root->data);
    if(!root->left && !root->right){
        result.push_back(path);
        path.pop_back();
        return;
    }
    getAllLeftOriented(root->left, madeRightMove, result, path);
    if(!madeRightMove){
        getAllLeftOriented(root->right, true, result, path);
    }
}
List* getMid(List* head){
    List* slow=head;
    List* fast=head;
    while(slow && fast && fast->next){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
    
}
void printList(List* head){
    if(!head){
        return;
    }
    while(head){
        cout<<head->data<<" ";
        head=head->next;
    }
}
void reverseLL(List*& head){
    List* next=nullptr;
    List* prev=nullptr;
    List* iter=head;
    while(iter){
        next=iter->next;
        iter->next=prev;
        prev=iter;
        iter=next;
    }
    head=prev;
}
int countNodes(List* head){
    int count=0;
    List* iter=head;
    while(iter){
        count++;
        iter=iter->next;
    }
    return count;
}
int getAccumNumber(List* begin, List* end)
{
    int number = 0;

    while (begin != end)
    {
        (number *= 10) += begin->data;
        begin = begin->next;
    }

    return number;
}
void storeValuesInVector( Node<char>* root,vector<vector<char>>& levels){
    if(!root){
        return ;
    }
    queue<Node<char>*> q;
    q.push(root);
    while(!q.empty()){
        int size=q.size();
        vector<char> level;
        for(int i=0;i<size;i++){
            Node<char>* current=q.front();
            q.pop();
            level.push_back(current->data);
            if(current->left){
                q.push(current->left);
            }
            if(current->right){
                q.push(current->right);
            }
        }
        levels.push_back(level);
    }
}
size_t minLevel( Node<char>* root){
    vector<vector<char>> res;
    size_t answer;
    storeValuesInVector(root, res);
    for(int i=res.size()-1;i>-1;i--){
        bool hasBroken=false;
        for(int y=0;y<res[i].size()-1;y++){
            if(res[i][y]<res[i][y+1]){
                hasBroken=true;
                break;
            }
        }
        if(!hasBroken){
            answer=i;
            break;
        }
    }
    return answer+1;
}
bool canWeSplitWord(const char* word){
    if(strlen(word)<4)
        return false;
    return true;
}
bool isNextSymbolLegit(const Node<char>* t,char c){
    if(!t->left&&!t->right){
        return false;
    }
    else if (t->left&&!t->right){
        return t->left->data==c;
    }
    else if(t->left&&t->right){
        return t->left->data==c||t->right->data==c;
    }
    else{
        return t->right->data==c;
    }
}
bool canYouReadWordHalfHelper(const Node<char>* t,size_t& currentPos,const char* word){
    if(currentPos==strlen(word)){
        return true;
    }
    if(t->data!=word[currentPos]){
        return false;
    }
    currentPos++;
    if(!isNextSymbolLegit(t, word[currentPos])){
            return false;
        }
    else {
            if(t->left->data==word[currentPos]){
                currentPos++;
                return canYouReadWordHalfHelper(t->left, currentPos, word);
            }
            else{
                currentPos++;
                return  canYouReadWordHalfHelper(t->right, currentPos, word);
            }
        }
}
void canYouReadWord(const Node<char>* t,const char* word){
    size_t wordSize=strlen(word);
    if(wordSize<4){
        //return false;
    }
    size_t s1=0;
    size_t s2=0;
    char word1[wordSize/2];
    char word2[wordSize/2+1];
    for(int i=0;i<wordSize/2;i++){
        word1[i]=word[i];
    }
    word1[wordSize/2]='\0';
    for(int i=wordSize/2, j=0;i<wordSize,j<wordSize/2+1;i++,j++){
        word2[j]=word[i];
    }
    word2[wordSize/2+1]='\0';
    cout<<canYouReadWordHalfHelper(t->left, s1, word2);
    if(canYouReadWordHalfHelper(t->left, s1, word2)&& canYouReadWordHalfHelper(t->right, s2, word1)){
       // return true;
    }
    //return false;
}
template <typename T>
void insertInEnd(DLList<T>* head,DLList<T>* tail,T data){
    DLList<T>* toInsert=new Node(data);
    if(!head){
        head=tail=toInsert;
        head->prev=nullptr;
        tail->next=nullptr;
    }
    else{
        tail->next=toInsert;
        toInsert->prev=tail;
        tail=toInsert;
        tail->next=nullptr;
    }
}
int main(int argc, const char * argv[]) {
    int n = 9;
        int m = 8;
        std::vector<std::pair<int, int>> edges =
        {{7, 8},
        {4, 5}, {4, 6}, {5, 6},
        {2, 1}, {0, 3}, {0, 1}, {2, 3}};

        Graph g(n, edges);
    cout<<g.sumOfConnectedComponents();
    
}
