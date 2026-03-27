using namespace std;

struct Produto {
    int codigo;
    char nome[40];
    float preco;
};

int main() {
    Produto produto[3];

    for(int i = 0; i < 3; i++) {
        cout << "\nProduto " << i + 1 << endl;
        cout << "Digite o código do produto: ";
        cin >> produto[i].codigo;

        cout << "Digite o nome do produto: ";
        cin >> produto[i].nome;

        cout << "Digite o preço do produto: ";
        cin >> produto[i].preco;
    }

    cout << "\n -- Dados dos Produtos -- \n";
    for(int i = 0; i < 3; i++) {
        cout << produto[i].codigo << " - " 
        << produto[i].nome << " - R$ " 
        << produto[i].preco << endl;
    }
    return 0;
}