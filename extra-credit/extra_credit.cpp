#include <iostream>
using namespace std;

// function to calculate the power of a number using recursion
double power(double x, double n)
{
    // base case: if n = 0, x^n = 1
    if (n == 0)
        return 1;

    // Recursive case: x^n = x * x^(n-1)
    return x * power(x, n - 1);
}

// main function to run the program
int main()
{

    // Declare value of x, n
    double x;
    int n;

    // reading base number and exponent from user
    cout << "Enter a floating point number (x) " << endl;
    cin >> x;
    cout << "Enter a non-negative whole number (n) " << endl;
    cin >> n;

    // Check if n is non-negative number
    while (n < 0)
    {
        cout << "Please enter a non-negative number" << endl;
        cin >> n;
    }
    double result = power(x, n);
    cout << x << " raised to the power of " << n << " is " << result << endl;
    return 0;
}
