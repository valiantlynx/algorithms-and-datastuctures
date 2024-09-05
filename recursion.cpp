#include <iostream>
using namespace std;
int fibonacci(int n) {
    if (n==1 || n==2)
        return n;
    else
        return fibonacci(n-1)+fibonacci(n-2);
}

int main() {
    int fibNumber = fibonacci(40);
    cout<<fibNumber;
}