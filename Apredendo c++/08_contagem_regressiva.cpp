#include <iostream>
using namespace std;

int main() {
    int inicio;

    cout << "Digite um numero para iniciar a contagem regressiva: ";
    cin >> inicio;

    for (int i = inicio; i >= 0; i--) {
        cout << i << endl;
    }

    return 0;
}
