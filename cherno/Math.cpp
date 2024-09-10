#include <iostream>
#include "Log.h"

static int Multiply(int a, int b) {
    Log("Multiply:");
    return a * b;
}

int main() {
    std::cout << Multiply(6,8) << std::endl;
    std::cin.get();
}