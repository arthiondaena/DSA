#include<iostream>
#include<vector>
using namespace std;

class UnionFind{
    private:
        int size;
        vector<int> sz;
        vector<int> id;
        int numComponents=0;
    
    public:
        UnionFind(int s){
            this->size=numComponents=s;
            sz.resize(size);
            id.resize(size);
            for(int i=0; i<size; i++){
                sz[i]=1;
                id[i]=i;
            }
        }

        int find(int p){
            int root =p;
            while(id[root]!=root) root=id[root];

            //compressing the path
            while(p!=root){
                int next=id[p];
                id[p]=root;
                p=next;
            }

            return root;
        }
        
        bool connected(int p, int q){
            return find(p)==find(q);
        }

        int componentSize(int p){
            return sz[find(p)];
        }

        int len(){
            return this->size;
        }

        int components(){
            return numComponents;
        }

        void unify(int p, int q){

            if(connected(p, q)) return;

            int root1=find(p), root2=find(q);
            if(sz[root1]<sz[root2]){
                sz[root2]+=sz[root1];
                id[root1]=root2;
                sz[root1]=0;
            }
            else{
                sz[root1]+=sz[root2];
                id[root2]=root1;
                sz[root2]=0;
            }
            numComponents--;
        }

};

int main(){
    UnionFind s(10);
    cout<<s.components()<<endl;
    for(int i=3; i<10; i+=2){
        s.unify(i-2, i);
        cout<<i<<"st unify: "<<s.components()<<endl;
    }
    for(int i=0; i<10; i++)
        cout<<i<<" component size: "<< s.componentSize(i)<<endl;
    return 0;
}