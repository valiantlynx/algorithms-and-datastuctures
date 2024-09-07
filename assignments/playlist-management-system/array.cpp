#include <iostream>
using namespace std;
int activityTask(){
    //Define an array
    int myList[10] = {10, 3, 2, 6, 4, 1, 8, 7, 5, 9};
    //Print array elements before sorting
    cout<<"Unsorted list: "<<endl;
    int maximum = -1;
    for(int elem:myList){
        cout<<elem<<" ";
        if(elem >= maximum)
            maximum = elem;
    }
    cout<<"\n Maximum is: "<<maximum<<endl;
    //Sort array elements, use two nested loops with swap function
    for(int i=0;i<10;i++){
        for(int j=i+1;j<10;j++){
            if(myList[i] > myList[j]) //Compare two elements
                swap(myList[i],myList[j]);
        }
    }
    //Print array elements after sorting
    cout<<"\n Sorted list: "<<endl;
    for(int elem:myList){
        cout<<elem<<" ";
    }
    cout<<"\n Maximum is: "<<myList[9]<<endl;
}
int main(){
    int numbers[90];
    for(int i=0;i<9;){
        numbers[i] = i*i;
        i++;
        cout<<i<<" is stored on address "<<&numbers[i]<<endl;
    }
    cout<<sizeof(int)<<endl;
    cout<<sizeof(numbers)<<endl;
    activityTask();
}
