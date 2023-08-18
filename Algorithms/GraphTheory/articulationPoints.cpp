#include <iostream>
#include <vector>

class ArticulationPoints{
    private:
        std::vector<std::vector<int>> graph;
        std::vector<bool> visited, isArticulationPoint;
        std::vector<int> low, ids;
        int id, n, rootNodeOutcomingEdgeCount;
        bool solved=0;

        void dfs(int root, int at, int parent){
            if(parent==root) rootNodeOutcomingEdgeCount++;

            visited[at]=true;
            low[at]=ids[at]=id++;

            for(auto to: graph[at]){
                if(to==parent)continue;
                if(!visited[to]){
                    dfs(root, to, at);
                    low[at]=std::min(low[at], low[to]);
                    //Articulation point found via the bridge
                    if(ids[at]<low[to])
                        isArticulationPoint[at]=1;
                    //Articulation point found via the cycle
                    if(ids[at]==low[to])
                        isArticulationPoint[at]=1;
                }
                else 
                    low[at]=std::min(low[at], ids[to]);
            }
        }

    public:
        ArticulationPoints(std::vector<std::vector<int>>graph, int n){
            this->graph=graph;
            this->n=n;
        }

        std::vector<bool> findArticulationPoints(){
            if(solved) return isArticulationPoint;

            visited.resize(n, false);
            isArticulationPoint.resize(n, false);
            low.resize(n, 0);
            ids.resize(n, 0);
            id=0;

            for(int i=0; i<n; i++){
                if(!visited[i]){
                    rootNodeOutcomingEdgeCount=0;
                    dfs(i, i, -1);    
                    isArticulationPoint[i]=rootNodeOutcomingEdgeCount>1;
                }
            }

            solved=1;
            return isArticulationPoint;
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

    ArticulationPoints solver(graph, n);
    std::vector<bool> aPoints=solver.findArticulationPoints();

    for(int i=0; i<aPoints.size(); i++){
        if(aPoints[i])
            std::cout<<"\nArticulation is at node : "<<i;
    }
    return 0;
}