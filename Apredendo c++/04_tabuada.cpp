#include <iostream>
using namespace std;

int main() {
    int numero;

    cout << "Digite um numero para ver a tabuada: ";
    cin >> numero;

    cout << "Tabuada do " << numero << ":" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << numero << " x " << i << " = " << (numero * i) << endl;
    }

    return 0;
}
