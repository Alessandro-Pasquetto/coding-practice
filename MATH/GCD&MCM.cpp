#include <iostream>

using namespace std;

// Massimo comune divisore
int GCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Massimo comune divisore per array
int GCD_Array(int arr[], int n) {
    int result = arr[0];
    for (int i = 1; i < n; ++i)
        result = GCD(result, arr[i]);
    return result;
}

// Minimo comune multiplo per array
int MCM_Array(int arr[], int n) {
    int result = arr[0];
    for (int i = 1; i < n; ++i)
        result = (result * arr[i]) / GCD(result, arr[i]);
    return result;
}

int main(){

    int array[3] = {33, 54, 27};
    cout<<GCD_Array(array, 3);

    return 0;
}