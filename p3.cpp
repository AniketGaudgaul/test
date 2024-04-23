#include <iostream>
#include <omp.h>

using namespace std;

int minval(int arr[], int n){

    int min = arr[0];

    #pragma omp parallel for reduction(min:minval)
    for(int i=0; i<n; i++){
        if(arr[i]<min){
            min = arr[i];
        }
    }

    return min;
}

int maxval(int arr[], int n){

    int max = arr[0];

    #pragma omp parallel for reduction(max:maxval)
    for(int i=0; i<n; i++){
        if(arr[i]>max){
            max = arr[i];
        }
    }

    return max;
}

int sum(int arr[], int n){

    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i<n; i++){
        sum = sum + arr[i];
    }

    return sum;
}

double average(int arr[], int n){

    double sum = 0;
    double avg = 0;

    #pragma omp parallel for reduction(avg:average)
    for(int i=0; i<n; i++){
        sum = sum + arr[i];
    }

    avg = sum/n;

    return avg;
}

int main(){

    int n = 7;
    int arr[] = {12,15,9,4,8,17};

    cout<<"Minimum value: "<<minval(arr,n)<<endl;
    cout<<"Maximum value: "<<maxval(arr,n)<<endl;
    cout<<"Summation: "<<sum(arr,n)<<endl;
    cout<<"Average: "<<average(arr,n)<<endl;

    return 0;
}