#include <iostream>
using namespace std;

int main() {
    float n1, n2, n3, media;

    cout << "Digite a primeira nota: ";
    cin >> n1;
    cout << "Digite a segunda nota: ";
    cin >> n2;
    cout << "Digite a terceira nota: ";
    cin >> n3;

    media = (n1 + n2 + n3) / 3.0f;

    cout << "Media = " << media << endl;

    if (media >= 6.0f) {
        cout << "Aprovado" << endl;
    } else {
        cout << "Reprovado" << endl;
    }

    return 0;
}
