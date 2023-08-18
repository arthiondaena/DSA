#include<iostream>
#include<vector>

class BridgeRecursive{
    private:
        int n, id=0;
        std::vector<int> ids, low;
        bool solved=0;
        std::vector<bool> visited;
        std::vector<std::vector<int>> graph;
        std::vector<int> bridges;

        int callback_token=-2;
    
    public:
        BridgeRecursive(std::vector<std::vector<int>> graph, int n){
            this->graph=graph;
            this->n=n;
        }
        
        std::vector<int> findBridges(){
            if(solved) return bridges;

            id=0;
            low.resize(n);
            ids.resize(n);
            visited.resize(n);
            std::fill(visited.begin(), visited.end(), 0);

            for(int i=0; i<n; i++) if(!visited[i]) dfs(i, -1, bridges);

            solved=true;
            return bridges;
        }
    private:
        void dfs(int at, int parent, std::vector<int>&bridges){
            visited[at]=true;
            ids[at]=low[at]=++id;

            for(auto to : graph[at]){
                if(to==parent) continue;
                if(!visited[to]){
                    dfs(to, at, bridges);
                    //this happens mostly after the main else block, and this happens on callback
                    low[at]=std::min(low[at], low[to]);
                    //this happens on callback, 2 -> 5, (right to left)
                    if(ids[at]<low[to]){
                        bridges.push_back(at);
                        bridges.push_back(to);
                    }
                }
                else{
                    //if the node reaches near starting node
                    //it happens in a circle mostly before the started node
                    low[at]=std::min(low[at], ids[to]);
                }
            }
        }
};

void addEdge(std::vector<std::vector<int>> &graph, int from, int to){
    graph[from].push_back(to);
    graph[to].push_back(from);
}

int main(){
    int n=9;
    std::vector<std::vector<int>>graph(n);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 5, 6);
    addEdge(graph, 6, 7);
    addEdge(graph, 7, 8);
    addEdge(graph, 8, 5);

    BridgeRecursive solver(graph, n);
    std::vector<int> bridges=solver.findBridges();

    for(int i=0; i<bridges.size()/2; i++){
        int node1=bridges[2*i];
        int node2=bridges[2*i+1];
        std::cout<<"\nBridge between nodes : "<<node1<<" and "<<node2;
    }
    return 0;
}