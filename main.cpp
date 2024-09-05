#include <iostream>       
#include <algorithm>      
using namespace std;
using std::cout;

int main() {
    int myNum[10] = {10, 3, 2, 6, 4, 1, 8, 7, 5, 9};
    int len = sizeof(myNum)/sizeof(myNum[0]);

    cout<<"Before sorting array : ";
    for(int i=0; i<len; i++)
    {
        cout<<" "<<myNum[i];
    }
    cout<<"\nMinimum in the array : " << min( {10, 3, 2, 6, 4, 1, 8, 7, 5, 9}, 
    [](const int& a, const int& b) 
    {  
        return a < b;  
    }); 

    std::sort(myNum, myNum + len);//Sorting demo array
     
    cout<<"\n\nAfter sorting array : ";
    for(int i=0; i<len; i++)
    {
        cout<<" "<<myNum[i];
    }
    return 0;
        cout<<"\nMaximum in the array : " << min( {10, 3, 2, 6, 4, 1, 8, 7, 5, 9}, 
    [](const int& a, const int& b) 
    {  
        return a < b;  
    }); 
}