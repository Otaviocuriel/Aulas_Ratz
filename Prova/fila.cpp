#include <iostream>
#include <limits>

using namespace std;

const int MAX_FILA = 10;

struct Fila {
    int dados[MAX_FILA];
    int inicio;
    int fim;
    int quantidade;
};

void limparEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void inicializarFila(Fila &f) {
    f.inicio = 0;
    f.fim = -1;
    f.quantidade = 0;
}

bool filaVazia(const Fila &f) {
    return f.quantidade == 0;
}

bool filaCheia(const Fila &f) {
    return f.quantidade == MAX_FILA;
}

void enfileirar(Fila &f, int valor) {
    if (filaCheia(f)) {
        cout << "Fila cheia. Nao foi possivel enfileirar." << endl;
        return;
    }

    f.fim = (f.fim + 1) % MAX_FILA;
    f.dados[f.fim] = valor;
    f.quantidade++;
    cout << "Valor enfileirado com sucesso." << endl;
}

void desenfileirar(Fila &f) {
    if (filaVazia(f)) {
        cout << "Fila vazia. Nada para desenfileirar." << endl;
        return;
    }

    int removido = f.dados[f.inicio];
    f.inicio = (f.inicio + 1) % MAX_FILA;
    f.quantidade--;
    cout << "Valor removido: " << removido << endl;
}

void mostrarInicio(const Fila &f) {
    if (filaVazia(f)) {
        cout << "Fila vazia." << endl;
        return;
    }

    cout << "Inicio da fila: " << f.dados[f.inicio] << endl;
}

void listarFila(const Fila &f) {
    if (filaVazia(f)) {
        cout << "Fila vazia." << endl;
        return;
    }

    cout << "Elementos da fila (inicio para fim):" << endl;
    int indice = f.inicio;
    for (int i = 0; i < f.quantidade; i++) {
        cout << f.dados[indice] << endl;
        indice = (indice + 1) % MAX_FILA;
    }
}

int main() {
    Fila fila;
    inicializarFila(fila);

    int opcao;

    do {
        cout << "\n===== EXERCICIO DE FILA =====" << endl;
        cout << "1 - Enfileirar" << endl;
        cout << "2 - Desenfileirar" << endl;
        cout << "3 - Mostrar inicio" << endl;
        cout << "4 - Listar fila" << endl;
        cout << "5 - Quantidade de elementos" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (cin.fail()) {
            cout << "Opcao invalida." << endl;
            limparEntrada();
            continue;
        }

        switch (opcao) {
            case 1: {
                int valor;
                cout << "Digite o valor para enfileirar: ";
                cin >> valor;

                if (cin.fail()) {
                    cout << "Valor invalido." << endl;
                    limparEntrada();
                    break;
                }

                enfileirar(fila, valor);
                break;
            }
            case 2:
                desenfileirar(fila);
                break;
            case 3:
                mostrarInicio(fila);
                break;
            case 4:
                listarFila(fila);
                break;
            case 5:
                cout << "Quantidade de elementos: " << fila.quantidade << endl;
                break;
            case 0:
                cout << "Encerrando exercicio de fila." << endl;
                break;
            default:
                cout << "Opcao inexistente." << endl;
                break;
        }
    } while (opcao != 0);

    return 0;
}
