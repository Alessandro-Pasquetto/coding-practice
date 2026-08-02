#include <iostream>

using namespace std;

// Greatest Common Divisor
int gcd(int x, int y) {
    while (y != 0) {
        int tmp = y;
        y = x % y;
        x = tmp;
    }
    return x;
}

// GCD of an array
int gcdArray(int values[], int size) {
    int result = values[0];

    for (int i = 1; i < size; i++)
        result = gcd(result, values[i]);

    return result;
}

// LCM of an array
int lcmArray(int values[], int size) {
    int result = values[0];

    for (int i = 1; i < size; i++)
        result = (result * values[i]) / gcd(result, values[i]);

    return result;
}

int main() {
    int numbers[] = {33, 54, 27};

    cout << "gcd: " << gcdArray(numbers, 3) << endl
         << "lcm: " << lcmArray(numbers, 3);

    return 0;
}