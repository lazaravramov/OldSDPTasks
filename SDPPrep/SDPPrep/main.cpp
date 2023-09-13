#include <iostream>
#include<stack>
#include<queue>
#include<vector>
#include<string>
#include<deque>
#include<cmath>
using namespace std;
template <typename T>
struct Tree{
    T data;
    Tree* left;
    Tree* right;
    Tree(T data,Tree* left=nullptr,Tree* right = nullptr):data(data),left(left),right(right){}
};
template <typename  T>
struct Node{
    T data;
    Node* next;
    Node(T data,Node* next=nullptr):data(data),next(next){}
};
template <typename T>
struct DlNode{
    T data;
    DlNode* prev;
    DlNode* next;
    DlNode(T data,DlNode* prev=nullptr,DlNode* next=nullptr):data(data),prev(prev),next(next){}
};
class Graph{
    vector<vector<int>> adjList;
public:
    Graph(int V):adjList(V){}
    void addEdge(int start,int end){
        adjList[start].push_back(end);
        adjList[end].push_back(start);
    }
    void BFS(int start,vector<bool>& visited,int& sum,int& vertexCount){
        queue<int>q;
        q.push(start);
        visited[start]=true;
        while(!q.empty()){
            int curVertex=q.front();
            q.pop();
            sum+=curVertex;
            vertexCount++;
            for(size_t i=0;i<adjList[curVertex].size();i++){
                int neighbour = adjList[curVertex][i];
                if(visited[neighbour])
                    continue;
                visited[neighbour]=true;
                q.push(neighbour);
            }
        }
    }
    double getAverageOfConnectedComponents(){
        vector<bool> isVisited(adjList.size(),false);
        double result=0;
        for(int i=0;i<adjList.size();i++){
            if(!isVisited[i]){
                int sum=0;
                int vertexCount=0;
                BFS(i, isVisited, sum, vertexCount);
                result+=((double)sum/vertexCount);
            }
        }
        return result;
    }
    void getSumEvenSumOdd(int start,int& sumEven,int& sumOdd){
        queue<pair<int, bool>> q;
        vector<bool> isVisited(adjList.size(),false);
        q.push({start,true});
        isVisited[start]=true;
        
        while(!q.empty()){
            pair<int,bool> curVertex=q.front();
            q.pop();
            if(curVertex.second){
                sumEven+=curVertex.first;
            }
            else
                sumOdd+=curVertex.first;
            for(size_t i=0;i<adjList[curVertex.first].size();i++){
                int neighbour=adjList[curVertex.first][i];
                if(isVisited[neighbour])
                    continue;
                q.push({neighbour,!curVertex.second});
                isVisited[neighbour]= true;
            }
        }
    }
    
};
struct BigNode{
    BigNode(int value):value(value){}
    int value;
    vector<BigNode*> children;
    ~BigNode(){
        for(int i=0;i<children.size();i++){
            delete children[i];
        }
    }
};
int countElements(Node<int>* lst){
    int counter =0 ;
    Node<int>* iter =lst;
    while(iter){
        iter=iter->next;
        counter++;
    }
    return counter;
}
int evaluateNumber(Node<int>* lst){
    int newNumber=0;
    Node<int>* iter =lst;
    int counter=countElements(lst);
    while(counter){
        newNumber+=(iter->data)*pow(10,--counter);
        iter=iter->next;
    }
    return newNumber;
}
bool isBalanced(string str){
    size_t lenght=str.size();
    stack<char> openingBrackets;
    for(size_t i=0;i<lenght;i++){
        if(str[i]=='{' || str[i]=='[' || str[i]=='('){
            openingBrackets.push(str[i]);
            continue;
        }
        if(openingBrackets.empty()){
            return false;
        }
        if ((str[i] == ')' && openingBrackets.top() != '(') ||
                  (str[i] == '}' && openingBrackets.top() != '{') ||
                  (str[i] == ']' && openingBrackets.top() != '['))
              {
                  return false;
              }

              openingBrackets.pop();
    }
    return openingBrackets.empty();
};
template <typename  T>
stack<T> sortStack(stack<T> & input){
    stack<T> newStack;
    while(!input.empty()){
        T tmp=input.top();
        input.pop();
        while(!newStack.empty()&& newStack.top()<tmp){
            input.push(newStack.top());
            newStack.pop();
        }
        newStack.push(tmp);
    }
    return newStack;
}
string removeStars(const string& s){
    stack<char> st;
    for(size_t i =0;i<s.size();i++){
        if(s[i]=='*'){
            if(st.empty()){
                throw "Invalid expr";
            }
            else{
                st.pop();
            }
        }
        else
            st.push(s[i]);
    }
    string res(st.size(),'\0');
    size_t idx=st.size()-1;
    while(!st.empty()){
        res[idx--]=st.top();
        st.pop();
    }
    return res;
}
void printAllBinaryNumbers(int n){
    queue<string> q;
    q.push("1");
    while(n){
        string currentNumber=q.front();
        q.pop();
        cout<<currentNumber;
        q.push(currentNumber+"0");
        q.push(currentNumber+"1");
        n--;
    }
}
template <typename T>
void insertAtBeg(Node<T>*& head,T el){
    Node<T>* newHead=new Node(el);
    newHead->next=head;
    head=newHead;
}
template<typename  T>
void printLIst(Node<T>* head){
    Node<T>* iter = head;
    while(iter){
        cout<<iter->data<<" ";
        iter=iter->next;
    }
}
template<typename T>
void reverseLL(Node<T>*& head){
    Node<T>* iter = head;
    Node<T>* prev=nullptr;
    Node<T>* next=nullptr;
    while(iter){
        next=iter->next;
        iter->next=prev;
        prev=iter;
        iter=next;
    }
    head=prev;
    
}
template <typename  T>
Node<T>* findMiddle(Node<T>* ll){
    Node<T>* slow=ll;
    Node<T>* fast=ll;
    while(fast&&fast->next){
        fast=fast->next->next;
        slow=slow->next;
    }
    return slow;
}
template <typename  T>
void reorder(Node<T>* ll){
    if(!ll||!ll->next){
        return;
    }
    Node<T>* middle=findMiddle(ll);
    reverseLL(middle);
    Node<T>* firstHalf=ll;
    Node<T>* currentPair=nullptr;
    Node<T>* backOfList=nullptr;
    while(middle){
        currentPair=firstHalf;
        firstHalf=firstHalf->next;
        if(!firstHalf){
            backOfList->next=currentPair;
            backOfList=backOfList->next;
            break;
        }
        currentPair->next=middle;
        middle=middle->next;
        if(backOfList){
            backOfList->next=currentPair;
        }
        backOfList=currentPair->next;
    }
    backOfList->next=nullptr;
}
template<typename T>
unsigned countElements(Node<T>* ll){
    unsigned counter=0;
    while(ll){
        counter++;
        ll=ll->next;
    }
    return counter;
}
template<typename T>
void myShuffle(Node<T>*& ll){
    Node<T>* middle =findMiddle(ll);
    if(countElements(ll)%2!=0){
        middle=middle->next;
    }
    reverseLL(middle);
    Node<T>* middleIter=middle;
    while(middleIter->next){
        middleIter=middleIter->next;
    }
    Node<T>* iter=ll;
    unsigned elem=countElements(ll);
    for(unsigned i=0;i<elem/2;i++){
        iter=iter->next;
    }
    iter->next=nullptr;
    middleIter->next=ll;
    ll=middle;
    
}
bool canWeSkip(Node<int>* ll){
    return ll->next;
}
bool canWeSkipTwice(Node<int>* ll){
    return canWeSkip(ll) && ll->next->next;
}
Node<int>* getBegWithFirstSmallerEl(Node<int>* head,int x){
    Node<int>* iter =head;
    while(iter){
        if(iter->data<x){
            break;
        }
        iter=iter->next;
    }
    return iter;
}
Node<int>* getBegWithFirstBiggerrEl(Node<int>* head,int x){
    Node<int>* iter =head;
    while(iter){
        if(iter->data>=x){
            break;
        }
        iter=iter->next;
    }
    return iter;
}
template<typename T>
void insertOnLast(Node<T>*& ll,T el){
    if(ll==nullptr){
        ll= new Node(el);
        return;
    }
    Node<T>* iter=ll;
    while(iter->next){
        iter=iter->next;
    }
    iter->next=new Node(el);
}
void myPartition(Node<int>*& head,int x){
    if(!head){
        return;
    }
    Node<int>* smallList=nullptr;
    Node<int>* bigList=nullptr;
    Node<int>* iter=head;
    while(iter){
        if(iter->data<x)
            insertOnLast(smallList, iter->data);
        else{
            insertOnLast(bigList, iter->data);
        }
        iter=iter->next;
    }
    if(!smallList){
        head= bigList;
        return;
    }
    Node<int>* smallIter=smallList;
    while(smallIter->next){
        smallIter=smallIter->next;
    }
    smallIter->next=bigList;
    head=smallList;
    
}
template <typename  T>
bool hasCycle(Node<T>* head){
    Node<T>* slow =head;
    Node<T>* fast=head;
    while(fast&& fast->next){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow==fast;
}
template <typename  T>
bool isPalindrome(Node<T>* head){
    stack<T> temp;
    Node<T>* iter=head;
    while(iter){
        temp.push(iter->data);
        iter=iter->next;
    }
    while(head){
        if(head->data!=temp.top())
            return false;
        temp.pop();
        head=head->next;
    }
    return true;
}
template <typename T>
void printTree(Tree<T>* tree){
    if(!tree)
        return;
    printTree(tree->left);
    cout<<tree->data<<" ";
    printTree(tree->right);
}
template <typename T>
int height(Tree<T>* tree){
    if(!tree)
        return 0;
    return 1+ max(height(tree->left),height(tree->right));
}
template <typename  T>
bool contains(Tree<T>* tree,T el){
    if(!tree){
        return false;
    }
    if(tree->data==el)
        return true;
    return contains(tree->left, el)||contains(tree->right, el);
}
bool shouldUnite(Node<string>* first,Node<string>* second){
    if(first->data==""||second->data=="")
        return false;
    return first->data[first->data.size()-1]==second->data[0];
}
void absorb(Node<string>*& lhs,Node<string>* rhs){
    lhs->data+="-";
    lhs->data+=rhs->data;
    lhs->next=rhs->next;
    delete rhs;
}
void rearrange(Node<int>*& lst){
    if(!lst)
        return;
    Node<int>* evenList=nullptr;
    Node<int>* oddList=nullptr;
    Node<int>* iter=lst;
    while(iter->next){
        if(iter->data%2==0){
            insertOnLast(evenList, iter->data);
        }
        else
            insertOnLast(oddList, iter->data);
        iter=iter->next;
    }
    if(!evenList){
        lst=oddList;
        return;
    }
    Node<int>* evenIter=evenList;
    while(evenIter->next){
        evenIter=evenIter->next;
    }
    evenIter->next=oddList;
    lst=evenList;
}
template <typename  T>
T maxElem(Tree<T>* tree){
    T res = tree->data;

        if (tree->left != nullptr) {
            res = std::max(res, maxElem(tree->left));
        }
        if (tree->right != nullptr) {
            res = std::max(res, maxElem(tree->right));
        }

        return res;
}
template <typename  T>
void insertInBST(Tree<T>*& bst,const T& el){
    if(!bst){
        bst=new Tree(el);
        return;
    }
    if(bst->data<el){
        insertInBST(bst->right, el);
    }
    else {
        insertInBST(bst->left, el);
    }
}
template <typename T>
Tree<T>* buildBSTHelper(const vector<T>& v,int start,int end){
    if(end<start)
        return nullptr;
    int mid =(end-start)/2+ start;
    Tree<T>* tree=new Tree(v[mid]);
    tree->left=buildBSTHelper(v, start, mid-1);
    tree->right=buildBSTHelper(v, mid+1, end);
    return tree;
}
template <typename  T>
Tree<T>* buildBST(const vector<T>&v){
    return buildBSTHelper(v, 0, v.size()-1);
}
template <typename  T>
bool sameTree(Tree<T>* tree1,Tree<T>* tree2){
    if(!tree1&& !tree2){
        return true;
    }
    if(tree1&& !tree2){
        return false;
    }
    if(!tree1&& tree2){
        return false;
    }
    if(tree1->data!=tree2->data){
        return false;
    }
    return sameTree(tree1->left, tree2->right)&&sameTree(tree1->right, tree2->right);
}
template<typename  T>
Node<T>* myMerge(Node<T>* a,Node<T>* b){
    if(!a)
        return b;
    if(!b)
        return a;
    Node<T>* c=nullptr;
    if(a->data<b->data){
        c=a;
        c->next=myMerge(a->next, b);
    }
    else{
        c=b;
        c->next=myMerge(a, b->next);
    }
    return c;
}
template <typename  T>
Node<T>* mergeSort(Node<T>* ll){
    if(!ll||!ll->next)
        return ll;
    Node<T>* mid =findMiddle(ll);
    Node<T>* a =ll;
    Node<T>* b =mid->next;
    mid->next=nullptr;
    a=mergeSort(a);
    b=mergeSort(b);
    Node<T>* c = myMerge(a, b);
    return c;
}
Node<int>* filterSumZero(Node<int>* ll){
    Node<int>* iter = ll;
    stack<Node<int>*> st;
    while(iter){
        stack<Node<int>*> stCopy=st;
        int currSum=iter->data;
        bool deleted =false;
        while(!stCopy.empty()){
            Node<int>* temp=stCopy.top();
            stCopy.pop();
            currSum+=temp->data;
            if(currSum==0){
                deleted =true;
                if(temp==ll){
                    ll=iter->next;
                    iter=ll;
                }
                else{
                    stCopy.top()->next=iter->next;
                    iter=iter->next;
                }
                int deletedCount=0;
                while(temp!=iter){
                    Node<int>* toDelete=temp;
                    temp=temp->next;
                    deletedCount++;
                    delete toDelete;
                }
                for(int i =0;i<deletedCount-1;i++){
                    st.pop();
                }
                break;
            }
        }
        if (!deleted)
        {
            st.push(iter);
            iter = iter->next;
        }
    }
    return ll;
}
bool isTreeSeenTheSameFromBothSides(BigNode* root,vector<int>& view){
    vector<BigNode*> currentLevel={root};
    while(currentLevel.size()>=1){
        if(currentLevel[0]->value!=currentLevel[currentLevel.size()-1]->value){
            view.clear();
            return false;
        }
        view.push_back(currentLevel[0]->value);
        vector<BigNode*> nextLevel;
        for(int i=0;i<currentLevel.size();i++){
            nextLevel.insert(nextLevel.end(),std::make_move_iterator(currentLevel[i]->children.begin()),
                             std::make_move_iterator(currentLevel[i]->children.end()));
        }
        currentLevel=nextLevel;
    }
    return true;
}
void getLongestPrettyPath(BigNode* root,vector<int>& path){
    path.push_back(root->value);
    vector<int> longestPath;
    for(int i=0;i<root->children.size();i++){
        if(!root->children[i]->value||!root->value%root->children[i]->value){
            continue;
        }
        vector<int> subPath;
        getLongestPrettyPath(root->children[i], subPath);
        if(subPath.size()>path.size()){
            longestPath=subPath;
        }
    }
    path.insert(path.end(),longestPath.begin(),longestPath.end());
}

void getAllLeftOrientedHelper(Tree<int>* root,
    bool madeRightMove,
    vector<vector<int>>& result,
    vector<int>& path)
{
    if(!root){
        return;
    }
    path.push_back(root->data);
    if(!root->left&&!root->right){
        result.push_back(path);
        path.pop_back();
        return;
    }
    getAllLeftOrientedHelper(root->left, madeRightMove, result, path);
    if(!madeRightMove){
        getAllLeftOrientedHelper(root->right, true, result, path);
    }
    path.pop_back();
}
Node<int>* buildListFromNumber(int n){
    if(n==0)
        return nullptr;
    int numberIter=n;
    Node<int>* head=new Node(numberIter%10);
    numberIter/=10;
    while(numberIter){
        insertAtBeg(head, numberIter%10);
        numberIter/=10;
    }
    return head;
}
void inc(Node<int>*& head){
    if(!head)
        return;
    Node<int>* secondHalf=findMiddle(head);
    int numberOfFirstHalf=countElements(head)/2;
    Node<int>* iter=head;
    for(int i=0;i<numberOfFirstHalf-1;i++){
        iter=iter->next;
    }
    iter->next=nullptr;
    int firstHalfNumber=evaluateNumber(head)-1;
    int secondHalfNumber=evaluateNumber(secondHalf)+1;
    Node<int>* newHead=buildListFromNumber(firstHalfNumber);
    Node<int>* newMid=buildListFromNumber(secondHalfNumber);
    Node<int>* newHeadIter=newHead;
    while(newHeadIter->next){
        newHeadIter=newHeadIter->next;
    }
    newHeadIter->next=newMid;
    head=newHead;
}
void buildStringList(Tree<char>* root,vector<string>& levels){
    if(!root){
        return;
    }
    queue<Tree<char>*> q;
    q.push(root);
    while(!q.empty()){
        size_t size=q.size();
        string level="";
        for(int i=0;i<size;i++){
            Tree<char>* r = q.front();
            q.pop();
            level+=r->data;
            if(r->left){
                q.push(r->left);
            }
            if(r->right){
                q.push(r->right);
            }
        }
        levels.push_back(level);
    }
}
void storeElementsInLevelsVector(Tree<int>* root,vector<vector<int>>& v){
    if(!root){
        return ;
    }
    queue<Tree<int>*> q;
    q.push(root);
    while(!q.empty()){
        vector<int> level;
        size_t size=q.size();
        for(size_t i=0;i<size;i++){
            Tree<int>* r =q.front();
            q.pop();
            level.push_back(r->data);
            if(r->left){
                q.push(r->left);
            }
            if(r->right){
                q.push(r->right);
            }
        }
        v.push_back(level);
    }
}
Tree<int>* kSmallestHelper(Tree<int>* tree,int& i,int k){
    if(!tree)
        return nullptr;
    Tree<int>* left=kSmallestHelper(tree->left, i, k);
    if(left){
        return left;
    }
    i++;
    if(i==k)
        return tree;
    return kSmallestHelper(tree->right, i, k);
}
int kSmallest(Tree<int>* tree,int k){
    if(!tree){
        throw runtime_error("Empty tree");
    }
    int i =0;
    Tree<int>* root=kSmallestHelper(tree, i, k);
    return root->data;
}
int main(int argc, const char * argv[]) {
    Node<int>* ll = new Node(1,new Node(9,new Node(0,new Node(0,new Node(9,new Node(9,new Node(9,new Node(9))))))));
    Tree<char>* tree=new Tree('a',new Tree('b',new  Tree('d'),new Tree('e')),new Tree('c'));
    vector<string>levels;
    buildStringList(tree, levels);
    Tree<int>* root=new Tree(1,new Tree(2),new Tree(3));
    vector<vector<int>> v;
    storeElementsInLevelsVector(root, v);
}
