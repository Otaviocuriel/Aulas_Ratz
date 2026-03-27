#include <iostream>
#include <cstdio>

using namespace std;

struct Produto {
    int codigo;
    char nome[50];
    float preco;
};


void exibir(Produto p) {
    printf("Codigo: %d | Nome: %s | Preco: %.2f\n", p.codigo, p.nome, p.preco);
}


void aplicarDesconto(Produto &p) {
    p.preco = p.preco * 0.90;
}


int main() {

    Produto prod = {101, "Teclado", 100.00};

    printf("Antes do desconto:\n");
    exibir(prod);

    
    aplicarDesconto(prod);

    printf("\nDepois do desconto:\n");
    exibir(prod);

    return 0;
}