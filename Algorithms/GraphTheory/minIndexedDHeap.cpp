#include <iostream>
#include <vector>
#include <cstdlib>

template<typename T>
class MinIndexedDHeap{
    private:
        int sz=0, N, D;
        std::vector<int>parent, child;
        std::vector<int>pm, im;
        
        //im[NodeIndex] gives keyIndex
        //pm[keyIndex] gives NodeIndex
        //im[pm[keyIndex]] gives keyIndex
        std::vector<T>values;
        int min=0;

        bool less(int i, int j){
            return values[i]<values[j];

        }

        int minChild(int i){
            int index=-1, from=child[i], to=std::min(sz, child[i]+D);
            for(int j=from; j<to; j++)
                if(less(j, i)|| index==-1)
                    index=i=j;

            return index;
        }

        void swap(int i, int j){
            pm[im[i]]=j;
            pm[im[j]]=i;
            int temp=im[i];
            im[i]=im[j];
            im[j]=temp;
        }

        void swim(int i){
            while(less(i, parent[i]) && i>0){
                swap(i, parent[i]);
                i=parent[i];
            }
            min=values[im[0]];
        }

        void sink(int i){
            for(int j=minChild(i); j!=-1;){
                swap(i, j);
                i=j;
                j=minChild(j);
            }
            min=values[im[0]];
        }
    
        bool isMinHeap(int i){
            int from=child[i], to=std::min(child[i]+D, sz);
            for(int j=from; j<to; j++){
                if(!less(i, j)) return false;
                if(!isMinHeap(j)) return false;
            }
            return true;
        }

    public:
        MinIndexedDHeap(int degree, int size){
            D=degree;
            N=std::max(D+1, size);

            parent.resize(N);
            child.resize(N);
            pm.resize(N);
            im.resize(N);
            values.resize(N);

            for(int i=0; i<N; i++){
                parent[i]=(i-1)/D;
                child[i]=i*D+1;
                pm[i]=-1;
                im[i]=-1;
            }
        }

        int size(){
            return sz;
        }

        bool isEmpty(){
            return sz==0;
        }

        bool contains(int ki){
            return pm[ki]!=-1;
        }

        void increase(int ki, T val){
            if(val>values[ki]){
                values[ki]=val;
                sink(pm[ki]);
            }
        }

        void decrease(int ki, T val){
            if(val<values[ki]){
                values[ki]=val;
                swim(pm[ki]);
            }
        }

        void insert(int ki, T value){
            if(contains(ki)) return;
            pm[ki]=sz;
            im[sz]=ki;
            values[ki]=value;
            swim(sz++);
            min=values[im[0]];
        }

        T update(int ki, T value){
            int i=pm[ki];
            T oldval=values[ki];
            values[ki]=value;
            swim(i);
            sink(i);
            return oldval;
        }

        T remove(int ki){
            int i=pm[ki];
            swap(i, --sz);
            sink(i);
            swim(i);
            T oldval=values[ki];
            values[ki]=0;
            pm[ki]=im[sz]=-1;
            return oldval;
        }

        int peekMinKeyIndex(){
            return im[0];
        }
        
        int pollMinKeyIndex(){
            int index=peekMinKeyIndex();
            remove(index);
            return index;
        }

        T peekMinValue(){
            return values[im[0]];
        }

        T pollMinValue(){
            T oldval=peekMinValue();
            remove(im[0]);
            return oldval;
        }

        T valueof(int ki){
            return values[ki];
        }

        bool isMinHeap(){
            return isMinHeap(0);
        }

};

int main(){
    MinIndexedDHeap<int> test(4, 15);
    std::cout<<"insertion:";
    for(int i=0; i<10; i++){
        int a=(rand()%50+1)+25;
        std::cout<<" "<<a;
        test.insert(i, a);
    }
    std::cout<<"\nIs min Heap: "<<(test.isMinHeap()?"YES":"NO");
    int sz=test.size();

    std::cout<<"\nPoll Min value order: ";
    while(sz--){
    std::cout<<" "<<test.pollMinValue();
    }

    std::cout<<"\n";
    return 0;
}