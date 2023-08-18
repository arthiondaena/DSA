#include<iostream>
#include<vector>
#include<limits>
#include<cstdlib>
#include<sstream>
#include<iterator>

const double INF=std::numeric_limits<double>::infinity();

class FloydWarshallSolve{
    private:
        int n;
        std::vector<std::vector<double>> dp;
        std::vector<std::vector<int>> next;
        bool solved=0;
        const int neg_cycle=-1;

    public:
        FloydWarshallSolve(std::vector<std::vector<double>> mat){
            n=mat.size();
            dp=mat;
            next.resize(n, std::vector<int>(n));

            for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    if(mat[i][j]!=INF) next[i][j]=j;
        }  

        //All pairs shortest path
        std::vector<std::vector<double>> getApspMatrix(){
            solve();
            return dp;
        }

        void solve(){
            if(solved) return;

            for(int k=0; k<n; k++)
                for(int i=0; i<n; i++)
                    for(int j=0; j<n; j++)
                        if(dp[i][k]+dp[k][j]<dp[i][j]){
                            dp[i][j]=dp[i][k]+dp[k][j];
                            next[i][j]=next[i][k];
                        }

            //identify negative cycle by checking if dp[k][k]<0
            for(int k=0; k<n; k++)
                for(int i=0; i<n; i++)
                    for(int j=0; j<n; j++)
                        if(dp[i][k]!=INF && dp[k][j]!=INF && dp[k][k]<0){
                            dp[i][j]=-INF;
                            next[i][j]=neg_cycle;
                        }
            
            solved=1;

        }

        std::vector<int> reconstructShortestPath(int start, int end){
            solve();
            std::vector<int>path;
            if(dp[start][end]==INF) return path;
            int at=start;

            for(; at!=end; at=next[at][end]){
                if(at==neg_cycle) {
                    path.clear();
                    path.push_back(-10e7);
                    return path;
                }
                path.push_back(at);
            }

            if(next[at][end]==neg_cycle){
                path.clear();
                path.push_back(-10e7);
                return path;
            }

            path.push_back(end);
            return path;
        }

};

std::vector<std::vector<double>> createGraph(int n){
    std::vector<std::vector<double>> graph (n, std::vector<double>(n, INF));
    for(int i=0; i<n; i++) graph[i][i]=0;
    return graph;
}

int main(){
    const int n=7;
    std::vector<std::vector<double>> m=createGraph(n);

    m[0][1] = 2;
    m[0][2] = 5;
    m[0][6] = 10;
    m[1][2] = 2;
    m[1][4] = 11;
    m[2][6] = 2;
    m[6][5] = 11;
    m[4][5] = 1;
    m[5][4] = -2;

    printf("The shortest distance between : \n");
    FloydWarshallSolve solver(m);
    std::vector<std::vector<double>> dist=solver.getApspMatrix();
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            printf("%d and %d = %.3lf\n", i, j, dist[i][j]);
    
    printf("\nThe shortest path between nodes: \n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            
            std::vector<int> path=solver.reconstructShortestPath(i, j);
            std::cout<<i<<" to "<<j<<" = ";

            if(path.empty())
                std::cout<<"path doesn't exist\n";
            else if(path[0]==-10e7)
                std::cout<<"Has inf no of loops! (negative cycle case)\n";
            else{
                std::ostringstream s;
                std::copy(path.begin(), path.end()-1, std::ostream_iterator<int>(s, "->"));
                s<<path.back();
                std::cout<<s.str()<<"\n";

            }
        }
    }
    return 0;
}