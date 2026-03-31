#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

struct Produto {
    int codigo;
    string nome;
    double preco;
    int quantidade;
};

void limparEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int buscarProdutoPorCodigo(Produto produtos[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrarProduto(Produto produtos[], int &total, const int MAX_PRODUTOS) {
    if (total >= MAX_PRODUTOS) {
        cout << "Limite de produtos atingido." << endl;
        return;
    }

    Produto novo;

    cout << "Codigo do produto: ";
    cin >> novo.codigo;
    if (cin.fail()) {
        cout << "Codigo invalido." << endl;
        limparEntrada();
        return;
    }

    if (buscarProdutoPorCodigo(produtos, total, novo.codigo) != -1) {
        cout << "Ja existe produto com esse codigo." << endl;
        return;
    }

    limparEntrada();
    cout << "Nome do produto: ";
    getline(cin, novo.nome);

    cout << "Preco do produto: ";
    cin >> novo.preco;
    if (cin.fail() || novo.preco < 0) {
        cout << "Preco invalido." << endl;
        limparEntrada();
        return;
    }

    cout << "Quantidade inicial: ";
    cin >> novo.quantidade;
    if (cin.fail() || novo.quantidade < 0) {
        cout << "Quantidade invalida." << endl;
        limparEntrada();
        return;
    }

    produtos[total] = novo;
    total++;
    cout << "Produto cadastrado com sucesso." << endl;
}

void listarProdutos(Produto produtos[], int total) {
    if (total == 0) {
        cout << "Nenhum produto cadastrado." << endl;
        return;
    }

    cout << "\n===== LISTA DE PRODUTOS =====" << endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < total; i++) {
        cout << "Codigo: " << produtos[i].codigo << endl;
        cout << "Nome: " << produtos[i].nome << endl;
        cout << "Preco: R$ " << produtos[i].preco << endl;
        cout << "Quantidade: " << produtos[i].quantidade << endl;
        cout << "-----------------------------" << endl;
    }
}

void venderProduto(Produto produtos[], int total) {
    if (total == 0) {
        cout << "Nao ha produtos para vender." << endl;
        return;
    }

    int codigo;
    int qtdVenda;

    cout << "Codigo do produto para venda: ";
    cin >> codigo;
    if (cin.fail()) {
        cout << "Codigo invalido." << endl;
        limparEntrada();
        return;
    }

    int indice = buscarProdutoPorCodigo(produtos, total, codigo);
    if (indice == -1) {
        cout << "Produto nao encontrado." << endl;
        return;
    }

    cout << "Quantidade para vender: ";
    cin >> qtdVenda;
    if (cin.fail() || qtdVenda <= 0) {
        cout << "Quantidade de venda invalida." << endl;
        limparEntrada();
        return;
    }

    if (qtdVenda > produtos[indice].quantidade) {
        cout << "Estoque insuficiente." << endl;
        return;
    }

    produtos[indice].quantidade -= qtdVenda;
    double totalVenda = qtdVenda * produtos[indice].preco;

    cout << fixed << setprecision(2);
    cout << "Venda realizada. Total: R$ " << totalVenda << endl;
}

void relatorioEstoque(Produto produtos[], int total) {
    if (total == 0) {
        cout << "Nenhum dado para relatorio." << endl;
        return;
    }

    double valorTotalEstoque = 0.0;
    int indiceMaisCaro = 0;
    int indiceMaisBarato = 0;

    for (int i = 0; i < total; i++) {
        valorTotalEstoque += produtos[i].preco * produtos[i].quantidade;

        if (produtos[i].preco > produtos[indiceMaisCaro].preco) {
            indiceMaisCaro = i;
        }
        if (produtos[i].preco < produtos[indiceMaisBarato].preco) {
            indiceMaisBarato = i;
        }
    }

    cout << fixed << setprecision(2);
    cout << "\n===== RELATORIO DE ESTOQUE =====" << endl;
    cout << "Valor total em estoque: R$ " << valorTotalEstoque << endl;
    cout << "Produto mais caro: " << produtos[indiceMaisCaro].nome
         << " (R$ " << produtos[indiceMaisCaro].preco << ")" << endl;
    cout << "Produto mais barato: " << produtos[indiceMaisBarato].nome
         << " (R$ " << produtos[indiceMaisBarato].preco << ")" << endl;
}

int main() {
    const int MAX_PRODUTOS = 100;
    Produto produtos[MAX_PRODUTOS];
    int totalProdutos = 0;
    int opcao;

    do {
        cout << "\n===== MENU ESTOQUE =====" << endl;
        cout << "1 - Cadastrar produto" << endl;
        cout << "2 - Listar produtos" << endl;
        cout << "3 - Vender produto" << endl;
        cout << "4 - Relatorio de estoque" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (cin.fail()) {
            cout << "Opcao invalida." << endl;
            limparEntrada();
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, totalProdutos, MAX_PRODUTOS);
                break;
            case 2:
                listarProdutos(produtos, totalProdutos);
                break;
            case 3:
                venderProduto(produtos, totalProdutos);
                break;
            case 4:
                relatorioEstoque(produtos, totalProdutos);
                break;
            case 0:
                cout << "Encerrando programa." << endl;
                break;
            default:
                cout << "Opcao inexistente." << endl;
                break;
        }
    } while (opcao != 0);

    return 0;
}
