#include<iostream>
#include<vector>
#include<list>

using std::vector;

class EulerianPathDirecteEdges{
    private:
        int n;
        int edgeCount;
        vector<int>in, out;
        std::list<int> path;
        vector<vector<int>> graph;

        void setup(){
            in.resize(n);
            out.resize(n);

            edgeCount=0;

            for(int from=0; from<n; from++){
                for(auto to: graph[from]){
                    out[from]++;
                    in[to]++;
                    edgeCount++;
                }
            }
        }

        bool hasEulerianPath(){
            if(edgeCount==0) return false;
            int startNodes=0, endNodes=0;
            for(int i=0; i<n; i++){
                if(out[i]-in[i]>1 || in[i]-out[i]>1) return false;
                if(out[i]-in[i]==1) startNodes++;
                if(in[i]-out[i]==1) endNodes++;
            }
            return (startNodes==0 && endNodes==0)||(startNodes==1 && endNodes==1);
        }

        int findStartingNode(){
            int start=0;
            for(int i=0; i<n; i++){
                //unique starting node
                if(out[i]-in[i]==1) return i;
                
                if(out[i]) start=i;
            }
            return start;
        }

        void dfs(int at){
            while(out[at]){
                int next= graph[at][--out[at]];
                dfs(next);
            }
            path.push_front(at);
        }


    public:
        EulerianPathDirecteEdges(vector<vector<int>>graph){
            n=graph.size();
            this->graph=graph;
        }

        vector<int> getEulerianPath(){
            setup();

            if(!hasEulerianPath()) return {};

            dfs(findStartingNode());

            if(path.size()!= edgeCount+1) return {};

            vector<int> soln(edgeCount+1);
            
            for(int i=0; !path.empty(); i++) {
                soln[i]=path.front();
                path.pop_front();
            }
            return soln;
        }

};

void addDirectedEdge(vector<vector<int>> &graph, int from, int to){
    graph[from].push_back(to);
}

int main(){
    int n=5;
    vector<vector<int>>graph(n);

    addDirectedEdge(graph, 0, 1);
    addDirectedEdge(graph, 1, 2);
    addDirectedEdge(graph, 1, 4);
    addDirectedEdge(graph, 1, 3);
    addDirectedEdge(graph, 2, 1);
    addDirectedEdge(graph, 4, 1);

    EulerianPathDirecteEdges solver(graph);
    vector<int> soln=solver.getEulerianPath();
    for(auto a:soln)
        std::cout<<a<<' ';
    return 0;
}