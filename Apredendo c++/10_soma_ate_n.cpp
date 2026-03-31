#include <iostream>
using namespace std;

int main() {
    int n;
    int soma = 0;

    cout << "Digite um numero inteiro positivo: ";
    cin >> n;

    if (n < 1) {
        cout << "Digite um valor maior que zero." << endl;
    } else {
        for (int i = 1; i <= n; i++) {
            soma += i;
        }

        cout << "A soma de 1 ate " << n << " = " << soma << endl;
    }

    return 0;
}
