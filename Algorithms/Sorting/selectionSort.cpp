#include<iostream>

void selectionSort(int arr[], int n){
    for(int i=0; i<n-1 ;i++)
        for(int j=i+1; j<n; j++)
            if(arr[i]>arr[j]){
                int temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
}

void print(int arr[], int n){
    for(int i=0; i<n; i++)
        std::cout<<arr[i]<<' ';
}

int main(){
    int arr[]={6,4,3,2,8}, n=5;
    selectionSort(arr, n);
    print(arr, n);
    return 0;
}

