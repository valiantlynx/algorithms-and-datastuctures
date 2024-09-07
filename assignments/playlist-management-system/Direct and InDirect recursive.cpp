#include <iostream>
using namespace std;
class Recursive{
   public:
       void revString(string &str,int lIndex,int hIndex){
           if(lIndex<hIndex){
            swap(str[lIndex],str[hIndex]);
            revString(str,lIndex+1,hIndex-1);
           }
       }
       void reverArray(int arr[],int lIndex,int hIndex){
         if(lIndex<hIndex){
            swap(arr[lIndex],arr[hIndex]);
            reverArray(arr,lIndex+1,hIndex-1);
         }
       }
       int func1(int n1){
         if(n1==0)
            return 1;
         else
            return n1*func2(n1-1);

       }
       int func2(int n2){
        if(n2==0)
            return 1;
        else
            return n2*func3(n2-1);
       }
       int func3(int n3){
         if(n3==0)
            return 1;
         else
            return n3*func1(n3-1);
       }
};
int main(){
  Recursive recObject;
  int factNumber = recObject.func1(10);
  cout<<factNumber;



  /*
  string str = "welcome to UiA";
  recObject.revString(str,0,str.length());
  cout<<str;
  int arr[] = {2,3,4,5,6,7,8};
  recObject.reverArray(arr,0,sizeof(arr)/sizeof(arr[0])-1);
  for(int i:arr){
    cout<<i<<" ";
  }
  */
}
