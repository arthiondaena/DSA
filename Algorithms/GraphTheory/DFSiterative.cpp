#include <iostream>
#include <map>
#include <list>
#include <stack>

class Edge{
    public:
    int from, to, cost;

    Edge(int f, int t, int c): from(f), to(t), cost(c){}

};

int dfs(std::map<int, std::list<Edge>> graph, int start, int n){
    int count=0;
    bool visited[n]={0};
    for(int i=0; i<n; i++){
        visited[i]=0;
    } 
    //check later
    std::stack <int> st;

    st.push(start);
    visited[start]=1;
    while(!st.empty()){
        int node=st.top();
        st.pop();
        count++;

        std::list<Edge> edges = graph[node];
        for(auto e:edges){
            if(!visited[e.to]){
                st.push(e.to);
                visited[e.to]=1;
            }
        }
        
    }
    return count;
}

void addDirectedEdge(std::map<int, std::list<Edge>> &graph, int from, int to, int cost){
    Edge newedge(from, to, cost);
    graph[from].push_back(newedge);
}

int main(){
    std::map<int, std::list<Edge>> graph;

    int numNodes=5;
    addDirectedEdge(graph, 0, 1, 4);
    addDirectedEdge(graph, 0, 2, 5);
    addDirectedEdge(graph, 1, 2, -2);
    addDirectedEdge(graph, 1, 3, 6);
    addDirectedEdge(graph, 2, 3, 1);
    addDirectedEdge(graph, 2, 2, 10); // Self loop

    int nodeCount=dfs(graph, 0, numNodes);
    std::cout<<"\nDfs node count starting at node 0: "<<nodeCount;
    nodeCount= dfs(graph, 4, numNodes);
    std::cout<<"\nDfs node count starting at node 4: "<<nodeCount;
    return 0;
}
