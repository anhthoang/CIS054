#include <iostream>
using namespace std;

//function to calculate the power of a number using recursion
double power (double x,double n){
    //base case: if n = 0, x^n = 1
    if(n == 0) return 1;

    //Recursive case: x^n = x * x^(n-1)
    return x * power(x, n - 1);

}

//main function tto run the program
int main(){
    return 0;
}
