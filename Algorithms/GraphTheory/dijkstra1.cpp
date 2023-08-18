#include<iostream>
#include<utility>
#include<limits>
#include<vector>
#include<queue>

typedef std::pair<int, int> iPair;

void shortestPath(std::vector<iPair>adj[], int src, int v){
    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;
    std::vector<int> dist(v, std::numeric_limits<int>::max());
    pq.push({0, src});
    dist[src]=0;

    while(!pq.empty()){
        int node=pq.top().second;
        pq.pop();

        for(auto pair:adj[node]){
            int dis=pair.first, x=pair.second;
            if(dist[x]>dist[node]+dis){
                dist[x]=dist[node]+dis;
                pq.push(std::make_pair(dist[x], x));
            }
        }
    }
    std::cout<<"Distance from source "<<src<<" = ";
    for(auto d:dist)
        std::cout<<d<<" ";
}

void addEdge(std::vector<iPair>adj[], int u, int v, int cost){
    adj[u].push_back(std::make_pair(cost, v));
    adj[v].push_back(std::make_pair(cost, u));
}

int main(){
    int V = 11;
    std::vector<iPair> adj[V];
 
    // making above shown graph
    addEdge(adj, 0, 1, 4);
    addEdge(adj, 0, 7, 8);
    addEdge(adj, 1, 2, 8);
    addEdge(adj, 1, 7, 11);
    addEdge(adj, 2, 3, 7);
    addEdge(adj, 2, 8, 2);
    addEdge(adj, 2, 5, 4);
    addEdge(adj, 3, 4, 9);
    addEdge(adj, 3, 5, 14);
    addEdge(adj, 4, 5, 10);
    addEdge(adj, 5, 6, 2);
    addEdge(adj, 6, 7, 1);
    addEdge(adj, 6, 8, 6);
    addEdge(adj, 7, 8, 7);
    addEdge(adj, 10, 9, 1);

    shortestPath(adj, 0, V);
    return 0;
}