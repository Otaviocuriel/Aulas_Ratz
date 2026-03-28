#include <iostream> // Biblioteca padrão para entrada e saída
using namespace std; // Permite usar nomes como "cout" e "endl" sem o prefixo "std::"

// Estrutura que representa um nó da lista
struct Nodo {
    int dado;           // Armazena o valor inteiro do nó
    Nodo* proximo;      // Ponteiro para o próximo nó na lista encadeada
};

// Função para inserir um elemento no início da lista
void inserirInicio(Nodo* &inicio, int valor) {
    Nodo* novo = new Nodo;     // Aloca dinamicamente um novo nó
    novo->dado = valor;        // Atribui o valor ao campo 'dado' do novo nó
    novo->proximo = inicio;    // Faz o novo nó apontar para o nó atualmente no início
    inicio = novo;             // Atualiza o ponteiro de início para apontar para o novo nó
}

// Função para inserir um elemento no final da lista
void inserirFim(Nodo* &inicio, int valor) {
    Nodo* novo = new Nodo;     // Cria um novo nó dinamicamente
    novo->dado = valor;        // Atribui o valor ao campo 'dado'
    novo->proximo = NULL;   // Define o campo 'proximo' como nulo (fim da lista)

    if (inicio == NULL) {   // Verifica se a lista está vazia
        inicio = novo;         // Se vazia, o novo nó é o primeiro da lista
    } else {
        Nodo* temp = inicio;           // Cria ponteiro temporário para percorrer a lista
        while (temp->proximo != NULL) { // Encontra o último nó
            temp = temp->proximo;      // Avança para o próximo nó
        }
        temp->proximo = novo;          // O último nó agora aponta para o novo nó
    }
}

// Função para remover o primeiro elemento da lista
void removerInicio(Nodo* &inicio) {
    if (inicio != NULL) {           // Verifica se a lista não está vazia
        Nodo* temp = inicio;           // Salva o ponteiro para o nó atual
        inicio = inicio->proximo;      // Atualiza o início para o próximo nó
        delete temp;                   // Libera a memória do nó anterior
    } else {
        cout << "Lista vazia.\n";      // Mensagem de erro se a lista estiver vazia
    }
}

// Função para imprimir todos os elementos da lista
void imprimirLista(Nodo* inicio) {
    Nodo* temp = inicio;               // Ponteiro temporário para percorrer a lista
    while (temp != NULL) {          // Percorre até o fim da lista
        cout << temp->dado << " -> ";  // Imprime o valor do nó atual
        temp = temp->proximo;          // Vai para o próximo nó
    }
    cout << "NULL\n";                  // Indica o fim da lista
}

// Função para liberar toda a memória da lista
void liberarLista(Nodo* &inicio) {
    Nodo* temp;                        // Ponteiro temporário
    while (inicio != NULL) {        // Percorre enquanto houver nós na lista
        temp = inicio;                 // Salva o ponteiro para o nó atual
        inicio = inicio->proximo;      // Avança para o próximo nó
        delete temp;                   // Libera a memória do nó atual
    }
}

// Função principal
int main() {
    Nodo* lista = NULL;   // Inicializa a lista como vazia (ponteiro nulo)

    // Inserções no início e fim da lista
    inserirInicio(lista, 10); // Insere 10 no início
    inserirInicio(lista, 5);  // Insere 5 no início
    inserirFim(lista, 15);    // Insere 15 no final
    inserirFim(lista, 20);    // Insere 20 no final

    // Imprime a lista atual
    cout << "Lista após inserções:\n";
    imprimirLista(lista);

    // Remove o primeiro elemento da lista
    removerInicio(lista);
    cout << "Lista após remover o primeiro elemento:\n";
    imprimirLista(lista);

    // Libera toda a memória alocada para a lista
    liberarLista(lista);

    return 0; // Indica que o programa terminou corretamente
}