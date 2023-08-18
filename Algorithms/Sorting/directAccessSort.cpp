#include<iostream>

void directAccessSort(int arr[], int n){
    int maxElement=0;
    for(int i=0; i<n; i++)
        maxElement=std::max(maxElement, arr[i]);

    //using pointers;
    int **newArr=new int*[maxElement+1];
    for(int i=0; i<=maxElement; i++){
        *(newArr+i)=NULL;
    }
    for(int i=0; i<n; i++){
        *(newArr+arr[i])=new int;
        **(newArr+arr[i])=arr[i];
    }
    int j=0;
    for(int i=0; i<=maxElement; i++){
        if(*(newArr+i)!=NULL){
            arr[j]=**(newArr+i);
            j++;
        }
    }
    delete newArr;

    //using arrays;
    // int *newArr[maxElement+1]={};
    // for(int i=0; i<n; i++){
    //     newArr[arr[i]]=new int;
    //     **(newArr+arr[i])=arr[i];
    // }
    // int j=0;
    // for(int i=0; i<=maxElement; i++){
    //     if(newArr[i]!=NULL){
    //         arr[j]=*(newArr[i]);
    //         j++;
    //     }
    // }
}

int main(){
    int arr[5]={5,4,3,6,8}, n=5;
    directAccessSort(arr, n);
    for(int i=0; i<n; i++)
        std::cout<<arr[i]<<" ";
    return 0;
}