#include <iostream>
using namespace std;

int main() {
    int numero;
    long long fatorial = 1;

    cout << "Digite um numero inteiro positivo: ";
    cin >> numero;

    if (numero < 0) {
        cout << "Nao existe fatorial de numero negativo." << endl;
    } else {
        for (int i = 1; i <= numero; i++) {
            fatorial = fatorial * i;
        }

        cout << "Fatorial de " << numero << " = " << fatorial << endl;
    }

    return 0;
}
