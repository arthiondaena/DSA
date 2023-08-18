#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>

class TSPiterative{
    private:
        const int n, start;
        std::vector<std::vector<double>> distance;
        std::vector<int>tour;
        double minTourCost=std::numeric_limits<double>::infinity();
        bool solved=false;

        void combination(int set, int at, int r, int n, std::vector<int>&subsets){
            int elementsLeftToPick=n-at;
            if(elementsLeftToPick<r) return;

            if(r==0)
                subsets.push_back(set);
            else{
                for(int i=at; i<n; i++){
                    set^=(1<<i);
                    combination(set, i+1, r-1, n, subsets);
                    set^=(1<<i);
                }
            }
        }

        bool notIn(int elem, int subset){
            return ((1<<elem)&subset)==0;
        }

    public:
        //constructors
        TSPiterative(int start, std::vector<std::vector<double>>distance)
            : n(distance.size()), start(start), distance(distance){}

        TSPiterative(std::vector<std::vector<double>>distance)
            :TSPiterative(0, distance){}

        std::vector<int> combinations(int r, int n){
            std::vector<int>subsets;
            combination(0, 0, r, n, subsets);
            return subsets;
        }   

        void solve(){
            if(solved) return;

            int endState=(1<<n)-1;
            std::vector<std::vector<double>> memo (n, std::vector<double>(1<<n, 0.0));

            //adding all outgoing edges from starting node to memo table
            for(int end=0; end<n; end++){
                if(end==start) continue;
                memo[end][(1<<start) | (1<<end)] = distance[start][end];
            }

            for(int r=3; r<=n; r++){

                for(int subset: combinations(r, n)){
                    if(notIn(start, subset)) continue;

                    for(int next=0; next<n; next++){
                        if(next==start||notIn(next, subset)) continue;
                        int subsetWithoutNext=subset^(1<<next);
                        double minDist=std::numeric_limits<double>::infinity();

                        for(int end=0; end<n; end++){
                            if(end==start||end==next||notIn(end, subset)) continue;

                            double newDistance = memo[end][subsetWithoutNext] + distance[end][next];
                            if(newDistance<minDist)
                                minDist=newDistance;
                        }
                        memo[next][subset]=minDist;
                    }
                }
            }

            //connecting tour back to the starting node, minimizing the tour cost
            for(int i=0; i<n; i++){
                if(i==start) continue;
                double tourCost=memo[i][endState]+distance[i][start];
                if(tourCost<minTourCost)
                    minTourCost=tourCost;
            }

            int lastIndex=start;
            int state=endState;
            tour.push_back(start);

            //reversing the tour to find tour with min cost
            for(int i=1; i<n; i++){
                int bestIndex=-1;
                double bestDist=std::numeric_limits<double>::infinity();

                for(int j=0; j<n; j++){
                    if(j==start||notIn(j, state)) continue;
                    double dist=memo[j][endState]+distance[j][lastIndex];
                    if(dist<bestDist){
                        bestDist=dist;
                        bestIndex=j;
                    }
                }
                lastIndex=bestIndex;
                state^=(1<<bestIndex);
                tour.push_back(bestIndex);
            }

            tour.push_back(start);
            std::reverse(tour.begin(), tour.end());

            solved=true;
        }

        double getTourCost(){
            if(!solved) solve();
            return minTourCost;
        }

        std::vector<int> getTour(){
            if(!solved) solve();
            return tour;
        }
        
};

void print(std::vector<int> tour){
    std::cout<<"[ ";
    for(auto u: tour)
        std::cout<<u<<' ';
    std::cout<<']'<<std::endl;
}

int main(){
    int n=6;
    std::vector<std::vector<double>> distanceMatrix(n, std::vector<double>(n, 10000));
    distanceMatrix[5][0] = 10;
    distanceMatrix[1][5] = 12;
    distanceMatrix[4][1] = 2;
    distanceMatrix[2][4] = 4;
    distanceMatrix[3][2] = 6;
    distanceMatrix[0][3] = 8;

    int startNode=0;
    TSPiterative solver(startNode, distanceMatrix);
    std::cout<<"Tour: ";
    print(solver.getTour());
    std::cout<<"TourCost: "<<solver.getTourCost();

    return 0;
}