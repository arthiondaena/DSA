#include<iostream>
#include<utility>
#include<vector>
#include<limits>

typedef std::pair<int, double> idpair;

void addEdge(std::vector<idpair> adj[], int u, int v, double cost){
    adj[u].push_back(std::make_pair(v, cost));
    return ;
}

std::vector<double> BellmanFord(std::vector<idpair> adj[], int v, int start){
    std::vector<double> dist(v, std::numeric_limits<double>::infinity());
    dist[start]=0;

    for(int i=0; i<v-1; i++)
        for(int j=0; j<v; j++)
            for(auto edge: adj[j])
                if(dist[j]+edge.second<dist[edge.first])
                    dist[edge.first]=dist[j]+edge.second;
    
    for(int i=0; i<v-1; i++)
        for(int j=0; j<v; j++)
            for(auto edge: adj[j])
                if(dist[j]+edge.second<dist[edge.first])
                    dist[edge.first]=-std::numeric_limits<double>::infinity();
    
    return dist;
}

int main(){
    int e=10, v=9, start=0;
    std::vector<idpair> graph [v];
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 2, 4, 1);
    addEdge(graph, 4, 3, -3);
    addEdge(graph, 3, 2, 1);
    addEdge(graph, 1, 5, 4);
    addEdge(graph, 1, 6, 4);
    addEdge(graph, 5, 6, 5);
    addEdge(graph, 6, 7, 4);
    addEdge(graph, 5, 7, 3);

    std::vector<double> dist=BellmanFord(graph, v, start);
    for(int i=0; i<dist.size(); i++)
        std::cout<<"dist from "<<start<<" to "<< i<< " = "<< dist[i]<<"\n";
    return 0;
}
