#include<iostream>

void swap(int &i, int &j){
    int temp=i;
    i=j;
    j=temp;
}

void print(int arr[], int n){
    for(int i=0; i<n; i++)
        std::cout<<arr[i]<<' ';
}

void bubbleSort(int arr[], int n){

    for(int i=n-1; i>=0; i--){
        bool flag=true;

        for(int j=0; j<i; j++)
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
                flag=false;
            }

        if(flag) break;
    }
}

int main(){
    int arr[]={5,3,3,5,6,8}, n=6;
    bubbleSort(arr, n);
    print(arr, n);
    return 0;
}