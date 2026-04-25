// feito por Bruno de Oliveira Ribeiro, Matheus Maia Rangel, Otavio vichin curiel, Jõao Rafael Alves Recco


#include <iostream>
using namespace std;

// ====== ESTRUTURAS ======

struct Produto {
    int codigoProduto;
    char nomePoduto[100];
    char quantidade[100];
    char unidadeDeMedida[100];
};

struct Estoque {
    int codigo;
    char nomeEstoque[100];
    char descricao[100];
    Produto produto;
    Produto historicoProdutos[50];
    int totalProdutos;
};

// ====== NÓ PARA PILHA ======

struct NoPilha {
    Produto dados;
    NoPilha* proximo;
};

struct Pilha {
    NoPilha* topo;
    
    Pilha() : topo(NULL) {}
};




void pushPilha(Pilha* pilha, Produto p) {
    NoPilha* novoNo = new NoPilha();
    novoNo->dados = p;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
    cout << "Produto adicionado à pilha (stack)!\n" << endl;
}

Produto popPilha(Pilha* pilha) {
    if (pilha->topo == NULL) {
        Produto vazio;
        vazio.codigoProduto = -1;
        cout << "Pilha vazia!\n" << endl;
        return vazio;
    }
    
    NoPilha* temp = pilha->topo;
    Produto resultado = temp->dados;
    pilha->topo = pilha->topo->proximo;
    delete temp;
    cout << "Produto removido da pilha!\n" << endl;
    return resultado;
}

Produto peekPilha(Pilha* pilha) {
    if (pilha->topo == NULL) {
        Produto vazio;
        vazio.codigoProduto = -1;
        cout << "Pilha vazia!\n" << endl;
        return vazio;
    }
    return pilha->topo->dados;
}

bool isPilhaVazia(Pilha* pilha) {
    return pilha->topo == NULL;
}

void exibirPilha(Pilha* pilha) {
    if (pilha->topo == NULL) {
        cout << "Pilha vazia!\n" << endl;
        return;
    }
    
    int contador = 1;
    NoPilha* atual = pilha->topo;
    while (atual != NULL) {
        cout << "\n[Produto " << contador << " - Topo]\n";
        cout << "  Código: " << atual->dados.codigoProduto << endl;
        cout << "  Nome: " << atual->dados.nomePoduto << endl;
        cout << "  Quantidade: " << atual->dados.quantidade << endl;
        cout << "  Unidade: " << atual->dados.unidadeDeMedida << endl;
        atual = atual->proximo;
        contador++;
    }
    cout << endl;
}

void destruirPilha(Pilha* pilha) {
    while (!isPilhaVazia(pilha)) {
        popPilha(pilha);
    }
}


struct EstoqueCompleto {
    Estoque* dados;
    Pilha* historicoProducts;
};

// FUNÇÕES 

Estoque* adicionarEstoque() {
    Estoque* novoEstoque = new Estoque();
    
    novoEstoque->codigo = 1;
    novoEstoque->totalProdutos = 0;
    
    cout << "=== Criar Novo Estoque ===" << endl;
    
    cout << "Digite o nome do estoque: ";
    cin >> novoEstoque->nomeEstoque;
    
    cout << "Digite a descricao do estoque (opcional): ";
    cin >> novoEstoque->descricao;
    
    cout << "\nEstoque adicionado com sucesso!\n" << endl;
    
    return novoEstoque;
}

void verHistorico(EstoqueCompleto* estoques[], int totalEstoques) {
    int codigoEstoque;
    
    cout << "\n=== Ver Histórico de Estoque ===" << endl;
    
    if (totalEstoques == 0) {
        cout << "Nenhum estoque criado ainda!\n" << endl;
        return;
    }
    
    cout << "Estoques disponíveis:\n";
    for (int i = 0; i < totalEstoques; i++) {
        cout << i + 1 << ". " << estoques[i]->dados->nomeEstoque << " (Código: " << estoques[i]->dados->codigo << ")\n";
    }
    
    cout << "Digite o número do estoque para ver histórico: ";
    cin >> codigoEstoque;
    cin.ignore(10000, '\n');
    
    if (codigoEstoque < 1 || codigoEstoque > totalEstoques) {
        cout << "Estoque inválido!\n" << endl;
        return;
    }
    
    int indiceEstoque = codigoEstoque - 1;
    
    cout << "\n--- Histórico do Estoque: " << estoques[indiceEstoque]->dados->nomeEstoque << " ---" << endl;
    cout << "Descrição: " << estoques[indiceEstoque]->dados->descricao << endl;
    cout << "\n[Pilha de Produtos - Ordem LIFO]\n";
    exibirPilha(estoques[indiceEstoque]->historicoProducts);
}

void adicionarProduto(EstoqueCompleto* estoques[], int totalEstoques) {
    Produto p;
    int escolhaEstoque;
    
    cout << "=== Adicionar Produto ===\n";
    
    cout << "Estoques disponíveis:\n";
    for (int i = 0; i < totalEstoques; i++) {
        cout << i + 1 << ". " << estoques[i]->dados->nomeEstoque << endl;
    }
    
    cout << "Escolha o estoque (número): ";
    cin >> escolhaEstoque;
    cin.ignore(10000, '\n');
    
    if (escolhaEstoque < 1 || escolhaEstoque > totalEstoques) {
        cout << "Estoque inválido!\n" << endl;
        return;
    }
    
    int indiceEstoque = escolhaEstoque - 1;
    
    if (estoques[indiceEstoque]->dados->totalProdutos >= 50) {
        cout << "Limite de produtos para este estoque atingido!\n" << endl;
        return;
    }
    
    cout << "Codigo do produto: ";
    while (!(cin >> p.codigoProduto)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Codigo invalido. Digite novamente: ";
    }
    
    cin.ignore(10000, '\n');
    
    cout << "Nome do produto: ";
    cin.getline(p.nomePoduto, sizeof(p.nomePoduto));
    
    cout << "Quantidade: ";
    cin.getline(p.quantidade, sizeof(p.quantidade));
    
    cout << "Unidade de medida: ";
    cin.getline(p.unidadeDeMedida, sizeof(p.unidadeDeMedida));
    
    // adiciona ao histórico (array)
    estoques[indiceEstoque]->dados->historicoProdutos[estoques[indiceEstoque]->dados->totalProdutos] = p;
    estoques[indiceEstoque]->dados->totalProdutos++;

    // adiciona à pilha
    pushPilha(estoques[indiceEstoque]->historicoProducts, p);
    
    cout << "Produto adicionado ao estoque \"" << estoques[indiceEstoque]->dados->nomeEstoque << "\"\n" << endl;
}

int main() {
    EstoqueCompleto* estoques[10];
    int totalEstoques = 0;
    int opcao;
    
    while (true) {
        cout << "----Gerenciador de Estoque com Ponteiros e Pilha----" << endl;
        cout << "1. Criar estoque\n";
        cout << "2. Adicionar produto ao estoque\n";
        cout << "3. Ver histórico\n";
        cout << "4. Sair\n";
        cout << "Opção: ";
        cin >> opcao;
        cin.ignore(10000, '\n');
        
        switch (opcao) {
        case 1:
            if (totalEstoques < 10) {
                estoques[totalEstoques] = new EstoqueCompleto();
                estoques[totalEstoques]->dados = adicionarEstoque();
                estoques[totalEstoques]->historicoProducts = new Pilha();
                totalEstoques++;
            } else {
                cout << "Limite de estoques atingido!\n" << endl;
            }
            break;
        case 2:
            if (totalEstoques > 0) {
                adicionarProduto(estoques, totalEstoques);
            } else {
                cout << "Crie um estoque primeiro!\n" << endl;
            }
            break;
        case 3:
            verHistorico(estoques, totalEstoques);
            break;
        case 4:
            cout << "Liberando memória...\n";
            for (int i = 0; i < totalEstoques; i++) {
                destruirPilha(estoques[i]->historicoProducts);
                delete estoques[i]->historicoProducts;
                delete estoques[i]->dados;
                delete estoques[i];
            }
            cout << "Saindo...\n";
            exit(0);
        default:
            cout << "Opção inválida!\n" << endl;
        }
    }
    
    return 0;
}