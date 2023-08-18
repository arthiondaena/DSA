#include<iostream>
#include<list>
#include<stack>
#include<map>

class Edge{
    public:
    int from, to, cost;

    Edge(int f, int t, int c): from(f), to(t), cost(c){}
};

int dfs(int at, bool visited[], std::map<int, std::list<Edge>> graph){
    if(visited[at]) return 0;

    int count=1;
    visited[at]=1;
    std::list<Edge> edges= graph[at];
    for(auto e:edges){
        count+=dfs(e.to, visited, graph);
    }

    return count;
}

void addDirectedEdge(std::map<int, std::list<Edge>> &graph, int from, int to, int cost){
    Edge newedge(from, to, cost);
    graph[from].push_back(newedge);
}

int main(){
    int numNodes = 5;
    std::map<int, std::list<Edge>> graph;
    addDirectedEdge(graph, 0, 1, 4);
    addDirectedEdge(graph, 0, 2, 5);
    addDirectedEdge(graph, 1, 2, -2);
    addDirectedEdge(graph, 1, 3, 6);
    addDirectedEdge(graph, 2, 3, 1);
    addDirectedEdge(graph, 2, 2, 10); // Self loop
    bool visited[numNodes]= {0};
    long nodeCount = dfs(0, visited, graph);
    std::cout<<"\nDfs node count starting at node 0: "<<nodeCount;
    
    bool visited1[numNodes]= {0};
    nodeCount = dfs(4, visited1, graph);
    std::cout<<"\nDfs node count starting at node 4: "<<nodeCount;
    return 0;
}