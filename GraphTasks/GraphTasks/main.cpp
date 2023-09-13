#include <iostream>
#include<queue>
#include<stack>
using namespace std;
class Graph{
    int vertices;
    vector<vector<int>> adjList;
public:
    Graph(int vertices):vertices(vertices),adjList(vertices,vector<int>()){}
    Graph(int vertices, std::vector<std::pair<int, int>> edges):Graph(vertices){
        int size=edges.size();
        for(int i=0;i<size;i++){
            adjList[edges[i].first].push_back(edges[i].second);
            adjList[edges[i].second].push_back(edges[i].first);
        }
    }
    double bfsSum(vector<bool>& visited,int start){
        double sum=0;
        int count=0;
        queue<int> q;
        q.push(start);
        visited[start]=true;
        while(!q.empty()){
            int current=q.front();
            q.pop();
            sum+=current;
            count++;
            for(int i=0;i<adjList[current].size();i++){
                if(!visited[adjList[current][i]]){
                    visited[adjList[current][i]]=true;
                    q.push(adjList[current][i]);
                    }
            }
        }
        return sum/count;
    }
    double getSum(){
        double result=0;
        vector<bool> visited(vertices,false);
        for(int i=0;i<vertices;i++){
            if(!visited[i]){
                result+=bfsSum(visited, i);
            }
        }
        return result;
    }
    bool existsVertex(int vertex) const
    {
        return vertex >= 0 && vertex < vertices;
    }
    int getVerticesCount() const
    {
        return vertices;
    }

};
void DFS(const Graph& g, int start, std::vector<int>& order)
{
    if (!g.existsVertex(start))
    {
        return;
    }

    std::stack<int> st;
    std::vector<bool> visited(g.getVerticesCount());

    st.push(start);

    while (!st.empty())
    {
        int current = st.top();
        st.pop();

        if (visited[current])
        {
            continue;
        }

        visited[current] = true;

        // order.push_back(current);

        std::vector<std::pair<int, int>> successors;
        //g.getSuccessors(current, successors); напиши обхождане

        for (int i = 0; i < successors.size(); i++)
        {
            st.push(successors[i].first);
        }
    }
}

void DFS_rec(const Graph& g, int start, std::vector<bool>& visited)
{
    visited[start] = true;

    std::vector<std::pair<int, int>> successors;
    //g.getSuccessors(start, successors);

    for (int i = 0; i < successors.size(); i++)
    {
        if (!visited[successors[i].first])
        {
            DFS_rec(g, successors[i].first, visited);
        }
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
        vector<bool> visited(n,false);
        std::cout << g.getSum();
}
