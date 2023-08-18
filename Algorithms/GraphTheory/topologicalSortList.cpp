#include<iostream>
#include<limits>
#include<vector>
#include<map>

class Edge{
    public:
        int from, to, cost;
        Edge(int f, int t, int c): from(f), to(t), cost(c){}
};

class TopologicalSortList{
    private:
        int dfs(std::map<int, std::vector<Edge>> graph, std::vector<int> &ordering, bool visited[], int i, int at){
            //if(visited[at]) return i;
            visited[at]=1;

            std::vector<Edge> edges=graph[at];
            for(auto edge: edges)
                if(!visited[edge.to]) i=dfs(graph, ordering, visited, i, edge.to);
            
            ordering[i--]=at;
            return i;
        }

    public:
        std::vector<int> TopologicalSort(std::map<int, std::vector<Edge>> graph, int numNodes){
            int n=numNodes;
            bool visited[n] {0};
            std::vector<int> ordering(n);
            int index=n-1;

            for(int i=0; i<n; i++){
                if(!visited[i]){
                    visited[i]=1;
                    index=dfs(graph, ordering, visited, index, i);
                }
            }

            return ordering;
        }

        std::vector<double> shortestPath(std::map<int, std::vector<Edge>>graph, int start, int numNodes){
            std::vector<int>topsort=TopologicalSort(graph, numNodes);
            std::vector<double>dist(numNodes, std::numeric_limits<double>::infinity());
            dist[start]=0;
            for(int i=0; i<numNodes; i++){
                int nodeIndex=topsort[i];
                auto adjacentEdges=graph[nodeIndex];
            
                for(auto edge: adjacentEdges){
                    dist[edge.to]=std::min(dist[edge.to], dist[nodeIndex]+edge.cost);
                }
            }

            return dist;
        }
};

void addEdge(int from, int to, int cost, std::vector<Edge> &edges){
    Edge edge(from, to, cost);
    edges.push_back(edge);
}

int main(){
    int n=7;
    std::map<int, std::vector<Edge>> graph;

    addEdge(0,1,3,graph[0]);
    addEdge(0,2,2,graph[0]);
    addEdge(0,5,3,graph[0]);
    addEdge(1,3,1, graph[1]);
    addEdge(1,2,6, graph[1]);
    addEdge(2,3,1, graph[2]);
    addEdge(2,4,10, graph[2]);
    addEdge(3,4,5, graph[3]);
    addEdge(5,4,7, graph[5]);

    TopologicalSortList solution;
    std::vector<int> order=solution.TopologicalSort(graph, n);
    for(auto c: order) std::cout<<c<<" ";

    std::cout<<"\n";

    for(auto c: solution.shortestPath(graph, 0, n))
        std::cout<<c<<" ";

    return 0;
}
