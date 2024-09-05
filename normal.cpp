#include <iostream>
using namespace std;

int main() {
    int fib1 = 0;
    int fib2 = 1;
    int nFib = 0;
    int n = 40;
    for (int i = 1; i <= n; i++)
    {
        nFib = fib1 + fib2;
        fib1 = fib2;
        fib2 = nFib;
    }
    cout<<nFib;
}