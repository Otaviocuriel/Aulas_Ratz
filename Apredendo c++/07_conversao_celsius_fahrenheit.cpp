#include <iostream>
using namespace std;

int main() {
    float celsius, fahrenheit;

    cout << "Digite a temperatura em Celsius: ";
    cin >> celsius;

    fahrenheit = (celsius * 9.0f / 5.0f) + 32.0f;

    cout << "Temperatura em Fahrenheit: " << fahrenheit << endl;

    return 0;
}
