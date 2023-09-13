#include <iostream>
#include<vector>
#include<queue>
#include<list>
#include<stack>
#include<algorithm>
using namespace std;
class MatrixGraph{
public:
    using vertex_t=unsigned int;
    using weight_t=unsigned int;
private:
    vector<vector<weight_t>> data;
public:
    MatrixGraph(size_t v){
        data=vector<vector<weight_t>>(v,vector<weight_t>(v,0));
    }
    void addVertex(){
        for(auto& v:data){
            v.push_back(0);
        }
        data.push_back(vector<weight_t>());
    }
    void removeVertex(vertex_t toDelete){
        if(!validVertex(toDelete)){
            throw "Invalid vertex";
        }
        data.erase(data.begin()+toDelete);
        
        for(auto& vertex:data){
            vertex.erase(vertex.begin()+toDelete);
        }
    }

    void addDirectedEdge(vertex_t from, vertex_t to, weight_t w){
        if(!validVertex(from)||validVertex(to)){
            throw "Invalide vertex";
        }
        data[from][to]=w;
    }
    void addEdge(vertex_t from, vertex_t to, weight_t w){
        if(!validVertex(from)||validVertex(to)){
            throw "Invalide vertex";
        }
        addDirectedEdge(from, to, w);
        addDirectedEdge(to, from, w);
    }
    void removeEdge(vertex_t from, vertex_t to){
        if(!validVertex(from)||validVertex(to)){
            throw "Invalide vertex";
        }
        data[from][to]=0;
    }
    
    bool validVertex(vertex_t v) const{
        return v< data.size();
    }
    weight_t getWeight(vertex_t from,vertex_t to) const{
        if(!validVertex(from)||validVertex(to)){
            throw "Invalide vertex";
        }
        return data[from][to];
    }

    size_t vertexCount() const{
        return data.size();
    }
    bool adjacent(vertex_t from, vertex_t to) const{
        if(!validVertex(from)||validVertex(to)){
            throw "Invalide vertex";
        }
        return data[from][to]>0;
    }

    std::vector<vertex_t> getSuccessors(vertex_t from) const{
        if(!validVertex(from)){
            throw "Invalid Vertex";
        }
        std::vector<vertex_t> result;
        for(size_t i=0;i<data.size();i++){
            if(data[i][from]>0){
                result.push_back(i);
            }
        }
        return result;
    }
    std::vector<vertex_t> getPredecessors(vertex_t from) const{
        if(!validVertex(from))
               throw "Invalid vertex";

           std::vector<vertex_t> result;

           for (size_t i = 0; i < data.size(); i++)
               if(data[i][from] > 0)
                   result.push_back(i);

           return result;
    }
    // Same as getSuccessors, here for interface purposes.
    std::vector<vertex_t> adjacent(vertex_t from ) const{
        return getSuccessors(from);
    }
};

class AdjListGraph {
    public:
    using vertex_t = unsigned int;
    using weight_t = unsigned int;

    private:
    struct Edge {
        vertex_t to;
        weight_t weight;
    };

    std::vector<std::list<Edge>> data;

    public:
    AdjListGraph(size_t vertexCount){
        data=vector<list<Edge>>(vertexCount,list<Edge>());
    }

    void addVertex(){
        data.push_back(list<Edge>());
    }
    void removeVertex(vertex_t toDelete){
        if(!validVertex(toDelete))
            throw "Invalide vertex";
        data.erase(data.begin()+toDelete);
        for(auto& vertexList:data){
            vertexList.remove_if([&](Edge e)->bool{return e.to==toDelete;});
            for(Edge& e:vertexList){
                if(e.to>toDelete){
                    e.to--;
                }
            }
        }
    }
    bool validVertex(vertex_t v) const{
        return data.size()>v;
    }

    void addEdge(vertex_t to, vertex_t from, weight_t w){
        if(!validVertex(to)||!validVertex(from)){
            throw "Invalid vertex";
        }
        data[from].push_back({to,w});
        data[to].push_back({from,w});
    }
    void removeEdge(vertex_t to, vertex_t from){
        if(!validVertex(to)||!validVertex(from)){
            throw "Invalid vertex";
        }
        data[from].remove_if([&](Edge e) -> bool {return e.to == to; });
        data[to].remove_if([&](Edge e) -> bool {return e.to == from; });
    }

    weight_t getWeight(vertex_t to, vertex_t from) const{
        if(!validVertex(to)||!validVertex(from)){
            throw "Invalid vertex";
        }
        for(const Edge& e : data[from]){
            if(e.to==to){
                return e.weight;
            }
        }
        return 0;
    }
    bool hasEdge(vertex_t to, vertex_t from) const{
        if(!validVertex(to)||!validVertex(from)){
            throw "Invalid vertex";
        }
        for(const Edge& e : data[from]){
            if(e.to==to){
                return true;
            }
        }
        return false;
    }

    size_t vertexCount() const{
        return data.size();
    }

    std::vector<Edge> adjacent(vertex_t v) const{
        return vector<Edge>(data[v].begin(),data[v].end());
    }
};
void BFS(const MatrixGraph& g,MatrixGraph::vertex_t start){
    vector<bool> visited(g.vertexCount(),false);
    queue<MatrixGraph::vertex_t> q;
    q.push(start);
    while(q.empty()){
        MatrixGraph::vertex_t current=q.front();
        q.pop();
        if(visited[current])
            continue;
        visited[current]=true;
        cout<<current<<" ";
        auto succesors=g.getSuccessors(current);
        for(const auto& currentVertex: succesors){
            if(!visited[currentVertex]){
                q.push(currentVertex);
            }
        }
    }
}
void DFSRec(vector<bool>& visited,const AdjListGraph& g,AdjListGraph::vertex_t start){
    visited[start]=true;
    auto child=g.adjacent(start);
    std::cout<<"Visited"<<start<<endl;
    for (const auto& currChild:child){
        if(!visited[currChild.to]){
            DFSRec(visited, g, currChild.to);
        }
    }
}
void DFS(const AdjListGraph& g,AdjListGraph::vertex_t start){
    vector<bool> visited(g.vertexCount(),false);
    DFSRec(visited, g, start);
}
int main(int argc, const char * argv[]) {

    AdjListGraph g(5);
        g.addEdge(0, 2, 1);
        g.addEdge(0, 3, 1);
        g.addEdge(0, 1, 1);
        g.addEdge(2, 3, 1);
        g.addEdge(1, 4, 1);
        g.addEdge(3, 4, 1);
        g.addEdge(1, 3, 1);

        DFS(g, 0);
}
