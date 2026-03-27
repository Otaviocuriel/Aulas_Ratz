#include <iostream>
#include <cstring>
using namespace std;
 
struct Projeto {
    int id;
    char nome[100];
    char aluno[100];
    char area[50];
    char semestre[20];
    char status[20]; 
};
 
const int MAX = 20;
Projeto projetos[MAX];
int total = 0;
 
 
void cadastrar(Projeto projetos[], int &total) {
    if (total >= MAX) {
        cout << "\nLimite de projetos atingido!\n";
        return;
    }
 
    cout << "\n--- Cadastro de Projeto ---\n";
 
    cout << "ID: ";
    cin >> projetos[total].id;
    cin.ignore();
 
    cout << "Nome do projeto: ";
    cin.getline(projetos[total].nome, 100);
 
    cout << "Nome do aluno: ";
    cin.getline(projetos[total].aluno, 100);
 
    cout << "Area (programacao/banco de dados/inteligencia artificial/desenvolvimento web): ";
    cin.getline(projetos[total].area, 50);
 
    cout << "Semestre (ex: 1/2025): ";
    cin.getline(projetos[total].semestre, 20);
 
    cout << "Status (em andamento/concluido): ";
    cin.getline(projetos[total].status, 20);
 
    total++;
    cout << "Projeto cadastrado com sucesso!\n";
}
 
void alterar(Projeto projetos[], int total) {
    int id;
    cout << "\nDigite o ID do projeto para alterar: ";
    cin >> id;
    cin.ignore();
 
    for (int i = 0; i < total; i++) {
        if (projetos[i].id == id) {
            cout << "Novo nome do projeto: ";
            cin.getline(projetos[i].nome, 100);
 
            cout << "Novo nome do aluno: ";
            cin.getline(projetos[i].aluno, 100);
 
            cout << "Nova area: ";
            cin.getline(projetos[i].area, 50);
 
            cout << "Novo semestre: ";
            cin.getline(projetos[i].semestre, 20);
 
            cout << "Novo status (em andamento/concluido): ";
            cin.getline(projetos[i].status, 20);
 
            cout << "Projeto atualizado com sucesso!\n";
            return;
        }
    }
 
    cout << "Projeto nao encontrado!\n";
}
 
void exibir(Projeto projetos[], int total) {
    if (total == 0) {
        cout << "\nNenhum projeto cadastrado.\n";
        return;
    }
 
    cout << "\n--- Lista de Projetos ---\n";
    for (int i = 0; i < total; i++) {
        cout << "\nID:       " << projetos[i].id << endl;
        cout << "Nome:     " << projetos[i].nome << endl;
        cout << "Aluno:    " << projetos[i].aluno << endl;
        cout << "Area:     " << projetos[i].area << endl;
        cout << "Semestre: " << projetos[i].semestre << endl;
        cout << "Status:   " << projetos[i].status << endl;
    }
}
 
void excluir(Projeto projetos[], int &total) {
    int id;
    cout << "\nDigite o ID do projeto para excluir: ";
    cin >> id;
    cin.ignore();
 
    for (int i = 0; i < total; i++) {
        if (projetos[i].id == id) {
            for (int j = i; j < total - 1; j++) {
                projetos[j] = projetos[j + 1];
            }
            total--;
            cout << "Projeto excluido com sucesso!\n";
            return;
        }
    }
 
    cout << "Projeto nao encontrado!\n";
}
 
int main() {
    int opcao;
 
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Cadastrar projeto\n";
        cout << "2. Alterar projeto\n";
        cout << "3. Exibir projetos\n";
        cout << "4. Excluir projeto\n";
        cout << "5. Sair\n";
        cout << "Escolha: ";
        cin >> opcao;
        cin.ignore();
 
        switch (opcao) {
            case 1: cadastrar(projetos, total); break;
            case 2: alterar(projetos, total);   break;
            case 3: exibir(projetos, total);    break;
            case 4: excluir(projetos, total);   break;
            case 5: cout << "Encerrando...\n";  break;
            default: cout << "Opcao invalida!\n";
        }
 
    } while (opcao != 5);
 
    return 0;
}