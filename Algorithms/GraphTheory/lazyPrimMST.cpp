#include <iostream>
#include <vector>
#include<queue>
using std::vector;

class Edge{
    public:
        int from, to, cost;
        Edge(int f, int t, int c): from(f), to(t), cost(-c){}
        Edge():Edge(0, 0, 0){}
        int compareTo(Edge other){ return cost-other.cost;}

        friend bool operator<(Edge const& e1, Edge const& e2){
            return e1.cost<e2.cost;
        }

        friend bool operator>(Edge const& e1, Edge const& e2){
            return e1.cost>e2.cost;
        }

};

class LazyPrimMstAdjList{
    private:
        vector<vector<Edge>> graph;
        int n;
        vector<bool> visited;
        bool hasMst=0, solved=0;
        std::priority_queue<Edge> pq;

        long minCostSum=0;
        vector<Edge> mstEdges;

        void addEdges(int NodeIndex){
            visited[NodeIndex]=true;
            for(auto c: graph[NodeIndex]){
                if(!visited[c.to])
                    pq.push(c);
            }
        }

        void solve(){
            if(solved) return;
            solved=true;

            visited.resize(n);
            mstEdges.resize(n-1);
            int m=n-1, edgeCount=0;

            addEdges(0);
            while(!pq.empty()&&edgeCount!=m){
                Edge temp=pq.top();
                pq.pop();

                if(visited[temp.to]) continue;

                mstEdges[edgeCount++]=temp;
                minCostSum+=temp.cost;

                addEdges(temp.to);
            }

            hasMst=(edgeCount==m);
        }

    public:
        LazyPrimMstAdjList(vector<vector<Edge>> graph){
            this->graph=graph;
            this->n=graph.size();
        }

        vector<Edge> getMst(){
            solve();
            return mstEdges;
        }

        long getMstCost(){
            solve();
            return -minCostSum;
        }

};

void addDirectedEdge(vector<vector<Edge>> &graph, int from, int to, int cost){
    Edge edge(from, to, cost);
    graph[from].push_back(edge);
}

void addUndirectedEdge(vector<vector<Edge>> &graph, int from, int to, int cost){
    addDirectedEdge(graph, from, to, cost);
    addDirectedEdge(graph, to, from, cost);
}

int main(){
    int n=8;
    vector<vector<Edge>> g(n);

    addDirectedEdge(g, 0, 1, 10);
    addDirectedEdge(g, 0, 2, 1);
    addDirectedEdge(g, 0, 3, 4);

    addDirectedEdge(g, 2, 1, 3);
    addDirectedEdge(g, 2, 5, 8);
    addDirectedEdge(g, 2, 3, 2);
    addDirectedEdge(g, 2, 0, 1);

    addDirectedEdge(g, 3, 2, 2);
    addDirectedEdge(g, 3, 5, 2);
    addDirectedEdge(g, 3, 6, 7);
    addDirectedEdge(g, 3, 0, 4);

    addDirectedEdge(g, 5, 2, 8);
    addDirectedEdge(g, 5, 4, 1);
    addDirectedEdge(g, 5, 7, 9);
    addDirectedEdge(g, 5, 6, 6);
    addDirectedEdge(g, 5, 3, 2);

    addDirectedEdge(g, 4, 1, 0);
    addDirectedEdge(g, 4, 5, 1);
    addDirectedEdge(g, 4, 7, 8);

    addDirectedEdge(g, 1, 0, 10);
    addDirectedEdge(g, 1, 2, 3);
    addDirectedEdge(g, 1, 4, 0);

    addDirectedEdge(g, 6, 3, 7);
    addDirectedEdge(g, 6, 5, 6);
    addDirectedEdge(g, 6, 7, 12);

    addDirectedEdge(g, 7, 4, 8);
    addDirectedEdge(g, 7, 5, 9);
    addDirectedEdge(g, 7, 6, 12);

    LazyPrimMstAdjList solver(g);
    long cost=solver.getMstCost();

    if(cost==0)
        std::cout<<"MST doesn't exist\n";
    else{
        std::cout<<"MST cost: "<<cost<<"\n";
        for(auto c: solver.getMst()){
            std::cout<<c.from<<' '<<c.to<<"\n";
        }
    }
    return 0;
}