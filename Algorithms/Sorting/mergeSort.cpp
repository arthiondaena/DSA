#include<iostream>

void merge(int a[], int start, int mid, int end){
    int i=start, j=mid;
    int arr[end-start], k=0;

    while(i<mid&&j<end){
        if(a[i]<a[j]){
            arr[k]=a[i];
            k++;
            i++;
        }
        else{
            arr[k]=a[j];
            j++;
            k++;
        }
    }

    if(i!=mid){
        for(; i<mid; i++, k++){
            arr[k]=a[i];
        }
    }

    if(j!=end){
        for(; j<end; j++, k++){
            arr[k]=a[j];
        }
    }
    
    for(int in=start; in<end; in++){
        a[in]=arr[in-start];
    }

}

void mergeSort(int arr[], int start, int end){
    if(end-start==1) return;

    int mid=(start+end)/2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid, end);
    merge(arr, start, mid, end);

}

void print(int arr[], int n){
    for(int i=0; i<n; i++)
        std::cout<<arr[i]<<' ';
}

int main(){
    int arr[]={6,4,3,7,8,1,2,9,53,43,23,45}, n=12;
    mergeSort(arr, 0, n);
    print(arr, n);
    return 0;
}