#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void bs(vector<int> & arr){

    int n = arr.size();

    for(int i=0; i<n-1; i++){

        #pragma omp parallel for
        for(int j=0; j<n-i-1; j++){

            if(arr[j]>arr[j+1]){

                #pragma omp critical
                swap(arr[j],arr[j+1]);

            }

        }

    }

}

int main(){

    vector<int> arr = {12,15,8,4,17,9,2};

    for(int i=0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    bs(arr);
    for(int i=0; i<arr.size(); i++){
        cout<<endl<<arr[i]<<" ";
    }

    return 0;
}