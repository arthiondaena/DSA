#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>

class Edge{
    public:
        int to, from, cost;
        Edge(int f, int t, int c): to(t), from(f), cost(c){}
};

class BreadthFirstSearchIterative{
    private:
        std::vector<int>prev;
        std::vector<std::vector<Edge>> graph;
        int n;

        void bfs(int start){
            std::fill(prev.begin(), prev.end(), -1);
            bool visited[n] {0};
            std::queue<int> q;
            q.push(start);
            visited[start]=1;

            while(!q.empty()){
                int node=q.front();
                q.pop();
                for(auto e: graph[node]){
                    if(!visited[e.to]){
                        visited[e.to]=1;
                        prev[e.to]=node;
                        q.push(e.to);
                    }
                }
            }

        }

    public:
        BreadthFirstSearchIterative(std::vector<std::vector<Edge>> graph){
            this->graph= graph;
            this->n=graph.size();
            prev.resize(n);
        }

        std::vector<int> reconstructPath(int start, int end){
            std::vector<int> path;
            bfs(start);

            for(int i=end; i!=-1; i=prev[i]) path.push_back(i);
            std::reverse(path.begin(), path.end());

            if(path[0]!=start) path.clear();
            return path;
        }

};

void addDirectedEdge(std::vector<std::vector<Edge>> &graph, int from, int to, int cost){
    Edge edge(from, to, cost);
    graph[from].push_back(edge);
}

void addUndirectedEdge(std::vector<std::vector<Edge>> &graph, int from, int to, int cost){
    addDirectedEdge(graph, from, to, cost);
    addDirectedEdge(graph, to, from, cost);
}

void addUnweightedUndirectedEdge(std::vector<std::vector<Edge>> &graph, int from, int to){
    addUndirectedEdge(graph, from, to, 0);
}

int main(){
    int n=13;
    std::vector<std::vector<Edge>> graph(n);

    addUnweightedUndirectedEdge(graph, 0, 7);
    addUnweightedUndirectedEdge(graph, 0, 9);
    addUnweightedUndirectedEdge(graph, 0, 11);
    addUnweightedUndirectedEdge(graph, 7, 11);
    addUnweightedUndirectedEdge(graph, 7, 6);
    addUnweightedUndirectedEdge(graph, 7, 3);
    addUnweightedUndirectedEdge(graph, 6, 5);
    addUnweightedUndirectedEdge(graph, 3, 4);
    addUnweightedUndirectedEdge(graph, 2, 3);
    addUnweightedUndirectedEdge(graph, 2, 12);
    addUnweightedUndirectedEdge(graph, 12, 8);
    addUnweightedUndirectedEdge(graph, 8, 1);
    addUnweightedUndirectedEdge(graph, 1, 10);
    addUnweightedUndirectedEdge(graph, 10, 9);
    addUnweightedUndirectedEdge(graph, 9, 8);

    BreadthFirstSearchIterative solver(graph);

    int start=10, end=5;
    std::vector<int> path= solver.reconstructPath(start, end);
    std::cout<<"The shorted path from "<<start<<" to "<<end<<" is: \n";
    for(auto c: path)
        std::cout<<c<<" "; 
    return 0;
}