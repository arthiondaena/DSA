#include <iostream>
#include <vector>
using namespace std;

class BinaryHeap{
    
    private:
        vector<int> heap;

        //functions
        bool less(int i, int j){
            return heap[i]<heap[j];
        }

        void swap(int i, int j){
            int temp=heap[i];
            heap[i]=heap[j];
            heap[j]=temp;
        }

        void swim(int k){
            int parent=(k-1)/2;
            while(k>0 && less(k, parent)){
                swap(k, parent);
                k=parent;
                parent=(k-1)/2;
            }
        }

        void sink(int i){
            int sz=size();
            while(true){
                int left=2*i+1, right=2*i+2;
                int small=left;
                if(right<sz && less(right, left)) small=right;

                if((left>=sz) || less(i, small)) break;

                swap(i, small);
                i=small;
            }
        }

        int removeAt(int i){
            if(isEmpty()) return -1;

            int deletedEle=heap[i];
            int lastEleIndex=size()-1;
            swap(i, lastEleIndex);
            heap.erase(heap.begin()+lastEleIndex);
            
            if(i==lastEleIndex) return deletedEle;
            int ele=heap[i];

            sink(i);
            if(ele==heap[i]) swim(i);
            return deletedEle;
        }
    
    public:
        //constructors
        BinaryHeap()=default;
        BinaryHeap(int sz){
            heap.resize(sz);
        }
        BinaryHeap(vector<int>T){
            heap=T;
            for(int i=max(0, (int)(heap.size()/2)-1); i>=0; i--)
                sink(i);
        }

        //functions
        int size(){
            return heap.size();
        }

        bool isEmpty(){
            return size()==0;
        }

        void clear(){
            heap.clear();
        }

        int peek(){
            if (isEmpty()) return -1;
            return heap[0];
        }

        int poll(){
            return removeAt(0);
        }

        void add(int ele){
            heap.push_back(ele);
            int lastEleIndex=size()-1;
            swim(lastEleIndex);
        }

        bool contains(int ele){
            for(int i=0; i<size(); i++){
                if(heap[i]==ele) return true;
            }
            return false;
        }

        bool remove(int ele){
            for(int i=0; i<size(); i++){
                if(ele==heap[i]){
                    removeAt(i);
                    return true;
                }
            }
            return false;
        }

        bool isMinHeap(int k){
            int heapSize=size();
            if(k>heapSize) return true;
            
            int left=k*2+1, right=k*2+1;
            if(left<heapSize && less(left, k)) return false;
            if(right<heapSize && less(right, k)) return false;

            return isMinHeap(left) && isMinHeap(right);
        }

};

int main(){
    BinaryHeap PQ({89,33,23,54,67});
    cout<<PQ.peek();
    return 0;
}