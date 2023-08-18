#include<iostream>
#include<vector>
#include<stack>
#include<map>

class TarjanScc{
    private:
        int n;
        std::vector<std::vector<int>> graph;

        int id, sccCount;
        std::vector<int>ids, low, sccs;
        std::vector<bool>onStack;
        bool solved=0;
        std::stack<int> stack;
        const int UNVISITED =-1;

        void dfs(int at){
            ids[at]=low[at]=id++;
            stack.push(at);
            onStack[at]=true;

            for(auto to:graph[at]){
                if(ids[to]==UNVISITED)
                    dfs(to);
                if(onStack[to])
                    low[at]=std::min(low[at], low[to]);
            }

            //during callback, start of SCC
            if(low[at]==ids[at]){
                for(int node=stack.top(); ;node=stack.top()){
                    stack.pop();
                    onStack[node]=false;
                    sccs[node]=sccCount;
                    if(node==at) break;
                }
                sccCount++;
            }
        }
    
    public:
        TarjanScc(std::vector<std::vector<int>> graph, int n){
            this->graph=graph;
            this->n=n;
        }

        int get_sccCount(){
            if(!solved) solve();
            return sccCount;
        }

        std::vector<int> getSccs(){
            if(!solved) solve();
            return sccs;
        }

        void solve(){
            if(solved) 
            id=sccCount=0;
            ids.resize(n, UNVISITED);
            low.resize(n);
            sccs.resize(n);
            onStack.resize(n);
            
            for(int i=0; i<n; i++)
                if(ids[i]==UNVISITED)
                    dfs(i);
            
            solved=1;

        }

};

void addEdge(std::vector<std::vector<int>> &graph, int from, int to){
    graph[from].push_back(to);
}

int main(){
    int n=8;
    std::vector<std::vector<int>>graph(n);

    addEdge(graph, 6, 0);
    addEdge(graph, 6, 2);
    addEdge(graph, 3, 4);
    addEdge(graph, 6, 4);
    addEdge(graph, 2, 0);
    addEdge(graph, 0, 1);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 6);
    addEdge(graph, 3, 7);
    addEdge(graph, 7, 5);
    addEdge(graph, 1, 2);
    addEdge(graph, 7, 3);
    addEdge(graph, 5, 0);

    TarjanScc solver(graph, n);
    std::vector<int> sccs=solver.getSccs();
    std::map<int, std::vector<int>> multimap;
    for(int i=0; i<sccs.size(); i++){
        multimap[sccs[i]].push_back(i);
    }

    for(auto vec: multimap){
        std::cout<<"[ ";
        for(auto ele: vec.second)
            std::cout<<ele<<" ";
        std::cout<<"]"<<std::endl;
    }
    return 0;
}