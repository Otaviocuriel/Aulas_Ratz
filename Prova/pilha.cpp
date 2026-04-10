#include <iostream>
#include <limits>

using namespace std;

const int MAX_PILHA = 10;

struct Pilha {
    int dados[MAX_PILHA];
    int topo;
};

void limparEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void inicializarPilha(Pilha &p) {
    p.topo = -1;
}

bool pilhaVazia(const Pilha &p) {
    return p.topo == -1;
}

bool pilhaCheia(const Pilha &p) {
    return p.topo == MAX_PILHA - 1;
}

void empilhar(Pilha &p, int valor) {
    if (pilhaCheia(p)) {
        cout << "Pilha cheia. Nao foi possivel empilhar." << endl;
        return;
    }

    p.topo++;
    p.dados[p.topo] = valor;
    cout << "Valor empilhado com sucesso." << endl;
}

void desempilhar(Pilha &p) {
    if (pilhaVazia(p)) {
        cout << "Pilha vazia. Nada para desempilhar." << endl;
        return;
    }

    int removido = p.dados[p.topo];
    p.topo--;
    cout << "Valor removido: " << removido << endl;
}

void mostrarTopo(const Pilha &p) {
    if (pilhaVazia(p)) {
        cout << "Pilha vazia." << endl;
        return;
    }

    cout << "Topo da pilha: " << p.dados[p.topo] << endl;
}

void listarPilha(const Pilha &p) {
    if (pilhaVazia(p)) {
        cout << "Pilha vazia." << endl;
        return;
    }

    cout << "Elementos da pilha (topo para base):" << endl;
    for (int i = p.topo; i >= 0; i--) {
        cout << p.dados[i] << endl;
    }
}

int main() {
    Pilha pilha;
    inicializarPilha(pilha);

    int opcao;

    do {
        cout << "\n===== EXERCICIO DE PILHA =====" << endl;
        cout << "1 - Empilhar" << endl;
        cout << "2 - Desempilhar" << endl;
        cout << "3 - Mostrar topo" << endl;
        cout << "4 - Listar pilha" << endl;
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
                cout << "Digite o valor para empilhar: ";
                cin >> valor;

                if (cin.fail()) {
                    cout << "Valor invalido." << endl;
                    limparEntrada();
                    break;
                }

                empilhar(pilha, valor);
                break;
            }
            case 2:
                desempilhar(pilha);
                break;
            case 3:
                mostrarTopo(pilha);
                break;
            case 4:
                listarPilha(pilha);
                break;
            case 5:
                cout << "Quantidade de elementos: " << (pilha.topo + 1) << endl;
                break;
            case 0:
                cout << "Encerrando exercicio de pilha." << endl;
                break;
            default:
                cout << "Opcao inexistente." << endl;
                break;
        }
    } while (opcao != 0);

    return 0;
}
