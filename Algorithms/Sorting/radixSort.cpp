#include<iostream>
#include<cstdlib>
#include<random>


long get_max(long arr[], int n){
    long max=0;
    for(int i=0; i<n; i++)
        if(max<arr[i]) 
            max=arr[i];

    return max;
}

void countSort(long arr[], int n, int exp){
    int output[n], base=64;
    int count[base]={0};

    for(int i=0; i<n; i++)
        count[(arr[i]/exp)%base]++;

    for(int i=1; i<base; i++)
        count[i]+=count[i-1];
    
    for(int i=n-1; i>=0; i--){
        output[count[(arr[i]/exp)%base]-1] = arr[i];
        count[(arr[i]/exp)%base]--;
    }

    for(int i=0; i<n; i++)
        arr[i]=output[i];
}

void radixSort(long arr[], int n){
    long m=get_max(arr, n);

    for(int exp=1; m/exp!=0; exp*=64)
        countSort(arr, n, exp);
    
}

void print(long arr[], int n){
    for(int i=0; i<n; i++)
        std::cout<<arr[i]<<' ';
}

int main(){

  /* Seed */
    std::random_device rd;

  /* Random number generator */
    std::default_random_engine generator(rd());

  /* Distribution on which to apply the generator */
     std::uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);

    int n=100000;
    long arr[n];
    for(int i=0; i<n; i++){
        arr[i]=distribution(generator)%1000000;
    }

    //std::cout<<get_max(arr, n);
    // Function Call
    radixSort(arr, n);
    //print(arr, n);
    return 0;
}