// ============================================================
//  Sistema de Gerenciamento de Atendimentos - Clínica Escola
//  Estrutura de Dados: Lista Encadeada
//  Linguagem: C++ Estruturado (sem STL)
// ============================================================
 
#include <iostream>
#include <cstring>
#include <cctype>
 
using namespace std;
 
// ============================================================
//  DEFINIÇÃO DA ESTRUTURA DE DADOS
// ============================================================
 
const int TAM_NOME   = 100;
const int TAM_CURSO  = 60;
const int TAM_DATA   = 11;   // dd/mm/aaaa + '\0'
const int TAM_STATUS = 30;
 
struct Atendimento {
    int  codigo;
    char nomePaciente[TAM_NOME];
    char curso[TAM_CURSO];
    char data[TAM_DATA];
    char status[TAM_STATUS];
    Atendimento* proximo;
};
 
// ============================================================
//  CABEÇA DA LISTA (ponteiro global para o primeiro nó)
// ============================================================
 
Atendimento* lista = nullptr;
 
// ============================================================
//  FUNÇÕES AUXILIARES
// ============================================================
 
// Limpa o buffer de entrada após leitura
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
 
// Lê uma string com espaços, limitada a 'tam-1' caracteres
void lerString(const char* prompt, char* destino, int tam) {
    cout << prompt;
    cin.getline(destino, tam);
    // Se getline falhou (buffer cheio), limpa o restante
    if (cin.fail()) {
        cin.clear();
        limparBuffer();
    }
}
 
// Lê um inteiro com validação básica
int lerInteiro(const char* prompt) {
    int valor;
    while (true) {
        cout << prompt;
        if (cin >> valor) {
            limparBuffer();
            return valor;
        }
        cin.clear();
        limparBuffer();
        cout << "  [!] Entrada invalida. Digite um numero inteiro.\n";
    }
}
 
// Verifica se já existe um atendimento com o código informado
bool codigoExiste(int codigo) {
    Atendimento* atual = lista;
    while (atual != nullptr) {
        if (atual->codigo == codigo)
            return true;
        atual = atual->proximo;
    }
    return false;
}
 
// Busca e retorna ponteiro para o nó com o código informado (ou nullptr)
Atendimento* buscarPorCodigo(int codigo) {
    Atendimento* atual = lista;
    while (atual != nullptr) {
        if (atual->codigo == codigo)
            return atual;
        atual = atual->proximo;
    }
    return nullptr;
}
 
// Exibe os dados de um único atendimento formatado
void exibirAtendimento(const Atendimento* a) {
    cout << "  +------------------------------------------+\n";
    cout << "  | Codigo   : " << a->codigo            << "\n";
    cout << "  | Paciente : " << a->nomePaciente       << "\n";
    cout << "  | Curso    : " << a->curso              << "\n";
    cout << "  | Data     : " << a->data               << "\n";
    cout << "  | Status   : " << a->status             << "\n";
    cout << "  +------------------------------------------+\n";
}
 
// ============================================================
//  OPERAÇÃO 1 — INCLUIR ATENDIMENTO
// ============================================================
 
void incluirAtendimento() {
    cout << "\n  === INCLUIR ATENDIMENTO ===\n";
 
    int codigo = lerInteiro("  Codigo do atendimento: ");
    if (codigoExiste(codigo)) {
        cout << "  [!] Codigo " << codigo << " ja cadastrado. Operacao cancelada.\n";
        return;
    }
 
    // Aloca novo nó
    Atendimento* novo = new Atendimento;
    novo->codigo    = codigo;
    novo->proximo   = nullptr;
 
    lerString("  Nome do paciente : ", novo->nomePaciente, TAM_NOME);
    lerString("  Curso responsavel: ", novo->curso,        TAM_CURSO);
    lerString("  Data (dd/mm/aaaa): ", novo->data,         TAM_DATA);
    lerString("  Status           : ", novo->status,       TAM_STATUS);
 
    // Pergunta onde inserir
    cout << "  Inserir no (1) Inicio  ou  (2) Final? ";
    int opcao;
    cin >> opcao;
    limparBuffer();
 
    if (opcao == 1 || lista == nullptr) {
        // Insercao no inicio
        novo->proximo = lista;
        lista = novo;
    } else {
        // Insercao no final
        Atendimento* atual = lista;
        while (atual->proximo != nullptr)
            atual = atual->proximo;
        atual->proximo = novo;
    }
 
    cout << "  [OK] Atendimento " << codigo << " cadastrado com sucesso.\n";
}
 
// ============================================================
//  OPERAÇÃO 2 — EXCLUIR ATENDIMENTO
// ============================================================
 
void excluirAtendimento() {
    cout << "\n  === EXCLUIR ATENDIMENTO ===\n";
 
    if (lista == nullptr) {
        cout << "  [!] Nenhum atendimento cadastrado.\n";
        return;
    }
 
    int codigo = lerInteiro("  Codigo do atendimento a excluir: ");
 
    Atendimento* atual    = lista;
    Atendimento* anterior = nullptr;
 
    while (atual != nullptr && atual->codigo != codigo) {
        anterior = atual;
        atual    = atual->proximo;
    }
 
    if (atual == nullptr) {
        cout << "  [!] Atendimento com codigo " << codigo << " nao encontrado.\n";
        return;
    }
 
    // Confirmar exclusao
    cout << "  Atendimento encontrado:\n";
    exibirAtendimento(atual);
    cout << "  Confirma a exclusao? (s/n): ";
    char conf;
    cin >> conf;
    limparBuffer();
 
    if (tolower(conf) != 's') {
        cout << "  Operacao cancelada.\n";
        return;
    }
 
    // Remove o no da lista
    if (anterior == nullptr)
        lista = atual->proximo;       // era o primeiro nó
    else
        anterior->proximo = atual->proximo;
 
    delete atual;
    cout << "  [OK] Atendimento " << codigo << " excluido com sucesso.\n";
}
 
// ============================================================
//  OPERAÇÃO 3 — LISTAR ATENDIMENTOS
// ============================================================
 
void listarAtendimentos() {
    cout << "\n  === LISTA DE ATENDIMENTOS ===\n";
 
    if (lista == nullptr) {
        cout << "  [!] Nenhum atendimento cadastrado.\n";
        return;
    }
 
    int contador = 0;
    Atendimento* atual = lista;
    while (atual != nullptr) {
        contador++;
        cout << "\n  # " << contador << "\n";
        exibirAtendimento(atual);
        atual = atual->proximo;
    }
    cout << "\n  Total de atendimentos: " << contador << "\n";
}
 
// ============================================================
//  OPERAÇÃO 4 — ALTERAR ATENDIMENTO
// ============================================================
 
void alterarAtendimento() {
    cout << "\n  === ALTERAR ATENDIMENTO ===\n";
 
    if (lista == nullptr) {
        cout << "  [!] Nenhum atendimento cadastrado.\n";
        return;
    }
 
    int codigo = lerInteiro("  Codigo do atendimento a alterar: ");
    Atendimento* alvo = buscarPorCodigo(codigo);
 
    if (alvo == nullptr) {
        cout << "  [!] Atendimento com codigo " << codigo << " nao encontrado.\n";
        return;
    }
 
    cout << "  Dados atuais:\n";
    exibirAtendimento(alvo);
    cout << "  (Deixe em branco para manter o valor atual)\n\n";
 
    // Buffers temporarios para nao sobrescrever com vazio
    char temp[TAM_NOME];
 
    lerString("  Novo nome do paciente : ", temp, TAM_NOME);
    if (strlen(temp) > 0) strncpy(alvo->nomePaciente, temp, TAM_NOME);
 
    lerString("  Novo curso responsavel: ", temp, TAM_CURSO);
    if (strlen(temp) > 0) strncpy(alvo->curso, temp, TAM_CURSO);
 
    lerString("  Nova data (dd/mm/aaaa): ", temp, TAM_DATA);
    if (strlen(temp) > 0) strncpy(alvo->data, temp, TAM_DATA);
 
    lerString("  Novo status           : ", temp, TAM_STATUS);
    if (strlen(temp) > 0) strncpy(alvo->status, temp, TAM_STATUS);
 
    cout << "  [OK] Atendimento " << codigo << " atualizado com sucesso.\n";
}
 
// ============================================================
//  OPERAÇÃO 5 — BUSCAR ATENDIMENTO (bônus)
// ============================================================
 
void buscarAtendimento() {
    cout << "\n  === BUSCAR ATENDIMENTO ===\n";
 
    int codigo = lerInteiro("  Codigo do atendimento: ");
    Atendimento* alvo = buscarPorCodigo(codigo);
 
    if (alvo == nullptr) {
        cout << "  [!] Atendimento com codigo " << codigo << " nao encontrado.\n";
    } else {
        exibirAtendimento(alvo);
    }
}
 
// ============================================================
//  LIBERAR TODA A MEMÓRIA DA LISTA
// ============================================================
 
void liberarLista() {
    Atendimento* atual = lista;
    while (atual != nullptr) {
        Atendimento* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    lista = nullptr;
}
 
// ============================================================
//  MENU PRINCIPAL
// ============================================================
 
void exibirMenu() {
    cout << "\n  ==========================================\n";
    cout << "   CLINICA ESCOLA - GESTAO DE ATENDIMENTOS\n";
    cout << "  ==========================================\n";
    cout << "   1. Incluir atendimento\n";
    cout << "   2. Excluir atendimento\n";
    cout << "   3. Listar atendimentos\n";
    cout << "   4. Alterar atendimento\n";
    cout << "   5. Buscar atendimento\n";
    cout << "   0. Sair\n";
    cout << "  Opcao: ";
}
 
// ============================================================
//  MAIN
// ============================================================
 
int main() {
    int opcao;
 
    do {
        exibirMenu();
        if (!(cin >> opcao)) {
            cin.clear();
            limparBuffer();
            opcao = -1;
        } else {
            limparBuffer();
        }
 
        switch (opcao) {
            case 1: incluirAtendimento(); break;
            case 2: excluirAtendimento(); break;
            case 3: listarAtendimentos(); break;
            case 4: alterarAtendimento(); break;
            case 5: buscarAtendimento();  break;
            case 0:
                liberarLista();
                cout << "\n  Sistema encerrado. Memoria liberada. Ate logo!\n\n";
                break;
            default:
                cout << "  [!] Opcao invalida. Tente novamente.\n";
        }
 
    } while (opcao != 0);
 
    return 0;
}