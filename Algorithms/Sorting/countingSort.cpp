#include <iostream>
#include <random>

void countingSort(int arr[], int n){
    //finding max element for newArr size
    int maxElement=0;
    for(int i=0; i<n; i++)
        if(arr[i]>maxElement)
            maxElement=arr[i];
    
    //counting no of times a number has appeared
    int newArr[maxElement+1]={0};
    for(int i=0; i<n; i++){
        newArr[arr[i]]++;
    }

    //reassigning to original array
    int j=0;
    for(int i=0; i<=maxElement; i++){
        while(newArr[i]!=0){
            arr[j]=i;
            newArr[i]--;
            j++;
        }
    }
    
}

void print(int arr[], int n){
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
    int arr[n];
    for(int i=0; i<n; i++){
        arr[i]=distribution(rd)%1000000;
    }
    countingSort(arr, n);
    //print(arr, n);
    return 0;
}