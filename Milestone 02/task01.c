//E/19/169
//JAYAWARDHANA HDSM

#include <stdio.h>
#include <stdbool.h>

// Define the maximum Fibonacci number to be calculated

#define MAX_FIB 50

// Array to store memoized Fibonacci numbers

int memo[MAX_FIB];

// Function to calculate the Fibonacci number using memoization

int fibonacci(int n) {
    if (n <= 1)
        return n;
    if (memo[n] != -1)
        return memo[n];
    memo[n] = fibonacci(n - 1) + fibonacci(n - 2);
    return memo[n];
}

// Check if the Fibonacci number matches either of the other two numbers

bool fibonacci_matches(int num1, int num2, int num3) {

    // Calculate the Fibonacci number of num1

    int fib_num = fibonacci(num1);

    // Check if the Fibonacci number matches num2 or num3
    return (fib_num == num2 || fib_num == num3);
}

int main() {
    for (int i = 0; i < MAX_FIB; ++i)
        memo[i] = -1;

    int num1, num2, num3;

    //Input

    scanf("%d %d %d", &num1, &num2, &num3);

    // Call the function
    bool result = fibonacci_matches(num1, num2, num3);
    if (result)
        printf("TRUE\n");
    else
        printf("FALSE\n");

    return 0;
}
