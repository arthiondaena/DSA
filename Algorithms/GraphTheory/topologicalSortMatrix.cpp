#include<iostream>
#include<vector>
#include<limits>

class TopologicalSortMatrix{
    private:
        int visit(std::vector<std::vector<double>> adj,std::vector<int> &ans, bool visited[], int u, int index){
            int n=adj.size();
            if(visited[u]) return index;
            visited[u]=1;

            for(int v=0; v<n; v++)
                if(adj[u][v]!=0 && !visited[v]) index=visit(adj, ans, visited, v, index);

            ans[index--]=u;
            return index;
        }

    public:
        std::vector<int> TopologicalSort(std::vector<std::vector<double>>adj){
            int n=adj.size();
            bool visited[n]{0};
            int index=n-1;
            std::vector<int> ans(n);

            for(int u=0; u<n; u++) index=visit(adj, ans, visited, u, index);

            return ans;
        }

        std::vector<double> dagShortestPath(std::vector<std::vector<double>> adj, int start){
            int n=adj.size();
            std::vector<double> dist(n, std::numeric_limits<double>::infinity());
            dist[start]=0.0;

            for(auto u: TopologicalSort(adj))
                for(int v=0; v<n; v++)
                    if(adj[u][v]!=0)
                        dist[v]=std::min(dist[v], dist[u]+adj[u][v]);
            
            return dist;
        }
};

int main(){
    int n=7;
    std::vector<std::vector<double>> adj(n, std::vector<double>(n, 0));

    adj[0][1] = 3.0;
    adj[0][2] = 2.0;
    adj[0][5] = 3.0;

    adj[1][3] = 1.0;
    adj[1][2] = 6.0;

    adj[2][3] = 1.0;
    adj[2][4] = 10.0;

    adj[3][4] = 5.0;

    adj[5][4] = 7.0;

    TopologicalSortMatrix solution;
    std::vector<int> ans;
    ans= solution.TopologicalSort(adj);
    for(int i=0; i<n; i++) std::cout<<ans[i]<<" ";
    std::cout<<'\n';

    std::vector<double> dist=solution.dagShortestPath(adj, 0);
    for(auto i: dist) std::cout<<i<<" ";
    return 0;
}