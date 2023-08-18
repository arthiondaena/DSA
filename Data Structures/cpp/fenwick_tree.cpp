#include<iostream>
#include<vector>

class FenwickTree{
    private:
        std::vector<long> tree;
        std::vector<long>::size_type N;

        int lsb(int i){
            return (i & -i);
        }

        long prefixSum(int i){
            long sum=0L;
            while(i!=0){
                sum+=tree[i];
                i&=~lsb(i);  //i-=lsb(i);
            }
            return sum;
        }
    
    public:
        FenwickTree(std::vector<long> values){
            values.insert(values.begin(), 0);
            N=values.size()+1;
            tree=values;
            for(int i=1; i<N; i++){
                int parent=i+lsb(i);
                if(parent<N) tree[parent]+=tree[i];
            }
        }

        long sum(int i, int j){
            if(i>j){
                std::cout<<"Make sure left<=right";
                return -1;
            }
            else
                return prefixSum(j)-prefixSum(i-1);
        }

        long get (int i){
            return sum(i, i);
        }

        void add(int i, long val){
            while(i<N){
                tree[i]+=val;
                i+=lsb(i);
            }
        }

        void set(int i, long val){
            add(i, val-sum(i, i));
        }

};

int lsb(int i){
    return (i & -i);
}

int main(){
    FenwickTree ft({1, 2, 3, 4, 5, 6, 7});
    std::cout<<ft.sum(1, 7)<<" ";
    return 0;
}