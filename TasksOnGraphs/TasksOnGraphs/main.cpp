#include <iostream>
#include<vector>
#include<queue>
#include<map>
#include<string>
using namespace std;
bool hasCycleRec(const vector<vector<int>>& graph,int start,vector<bool>& visited){
    visited[start]=true;
    for(const auto& vertex:graph[start]){
        if(visited[vertex])
            return true;
        if(hasCycleRec(graph, vertex, visited))
            return true;
    }
    visited[start]=false;
    return false;
}
bool hasCycle(const vector<vector<int>>& graph,int start){
    vector<bool> visited(graph.size(),false);
    for(int i=0;i<graph.size();i++){
        if(!visited[i]&& !hasCycleRec(graph,i,visited)){
            return true;
        }
    }
    return false;
}
bool canFinish(int numCourses,vector<pair<int,int>>& prerequisites){
    vector<vector<int>> graph(numCourses);
    for(const auto& edgePair:prerequisites){
        graph[edgePair.first].push_back(edgePair.second);
    }
    vector<int> inDegree(numCourses,0);
    for(int i=0;i<numCourses;i++){
        for(const auto& vertex:graph[i]){
            inDegree[vertex]++;
        }
    }
    queue<int> q;
    for(int i=0;i<numCourses;i++){
        if(inDegree[i]==0)
            q.push(i);
    }
    while(!q.empty()){
        int currNode=q.front();
        q.pop();
        for(const auto& n:graph[currNode]){
            inDegree[n]--;
            if(inDegree[n]==0){
                q.push(n);
            }
        }
    }
    for(const auto& n:inDegree){
        if(n!=0){
            return false;
        }
    }
    return true;
}
bool canRead(const multimap<char,char>& graph,const string& word,size_t at){
    if(at==word.length()-1){
        return true;
    }
    auto succesors=graph.find(word[at]);
    if(succesors==graph.end()){
        return false;
    }
    while(succesors!=graph.end()&&(*succesors).first==word[at]){
        if((*succesors).second==word[at+1]){
            return (canRead(graph, word, at+1));
        }
        ++succesors;
    }
    return false;
}
int main(int argc, const char * argv[]) {
    std::multimap<char, char> graph;

        graph.insert({'a', 'c'});
        graph.insert({'a', 'd'});
        graph.insert({'c', 'b'});
        graph.insert({'b', 'd'});
        graph.insert({'d', 'k'});
        graph.insert({'d', 'c'});
        graph.insert({'d', 'a'});
        
        std::map<char, bool> visited;
        std::string word = "cbda";

        std::cout << canRead(graph, word, 0);
}
