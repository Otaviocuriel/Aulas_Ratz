#include <iostream>
using namespace std;

int main() {
    int a, b;

    cout << "Digite o primeiro numero: ";
    cin >> a;
    cout << "Digite o segundo numero: ";
    cin >> b;

    if (a > b) {
        cout << "O maior numero e: " << a << endl;
    } else if (b > a) {
        cout << "O maior numero e: " << b << endl;
    } else {
        cout << "Os dois numeros sao iguais." << endl;
    }

    return 0;
}
