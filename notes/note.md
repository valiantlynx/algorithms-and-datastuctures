### abstract datasctrure
the define how a datastructure should behave and what methods it should have. but not the detail on how those methods should be implemented.
e.g
 - List
  - posible implementations
  - Dynamic Array
  - Linked List
 - Que
  - Linked List based Queue
  - Array based Queue
  - Stack based Queue
 - Map
  -  Tree Map
  - Hash Map / Hash Table
 - Vehicle
  - Golf Cart
  - Bicycle
  - Smart Car

## computational complexity
**How much time does thi salgorithm take to finish?**
**How much space does this algorithm need for its computation?**
**Big-0** notation gives an upper bound of the complexity in the worst case scenario, 
It helps in quantifying performance as the input size becomes arbitrarily large.
### Big-0 Notation
n - The size of the input

Complexities orderd in smallest to largerst:
 - Contant Time: 0(1)
 - Logarithmic Time: 0(log(n))
 - Linear Time: 0(n)
 - Linearithmic Time: 0(nlog(n))
 - Quadratic Time: 0(n²)
 - Cubic Time: 0(n³)
 - Exponential Time: 0(b^n), b > 1
 - Factorial Time: 0(n!)

Big 0 only care when stuff are big so always check to see if there is stuff that wont matter when the expression becomes big. 
a good practice might be for n = inf
this is only in the theoretical case

example: 
 - f(n) = 7log(n)³ + 15n² + 2n³ + 8
  - 0(f(n)) = 0(n³)
  cause n³ is the biggest most dominant figure in the exporession
