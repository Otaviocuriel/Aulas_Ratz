#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

struct Aluno {
    string nome;
    double nota1;
    double nota2;
    double nota3;
    double media;
};

void limparEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double calcularMedia(double n1, double n2, double n3) {
    return (n1 + n2 + n3) / 3.0;
}

void cadastrarAluno(Aluno alunos[], int &total, const int MAX_ALUNOS) {
    if (total >= MAX_ALUNOS) {
        cout << "Limite de alunos atingido." << endl;
        return;
    }

    Aluno novo;

    limparEntrada();
    cout << "Nome do aluno: ";
    getline(cin, novo.nome);

    cout << "Nota 1: ";
    cin >> novo.nota1;
    cout << "Nota 2: ";
    cin >> novo.nota2;
    cout << "Nota 3: ";
    cin >> novo.nota3;

    if (cin.fail() || novo.nota1 < 0 || novo.nota1 > 10 ||
        novo.nota2 < 0 || novo.nota2 > 10 ||
        novo.nota3 < 0 || novo.nota3 > 10) {
        cout << "Notas invalidas. Digite valores entre 0 e 10." << endl;
        limparEntrada();
        return;
    }

    novo.media = calcularMedia(novo.nota1, novo.nota2, novo.nota3);
    alunos[total] = novo;
    total++;

    cout << "Aluno cadastrado com sucesso." << endl;
}

void listarAlunos(Aluno alunos[], int total) {
    if (total == 0) {
        cout << "Nenhum aluno cadastrado." << endl;
        return;
    }

    cout << "\n===== BOLETIM DA TURMA =====" << endl;
    cout << fixed << setprecision(2);

    for (int i = 0; i < total; i++) {
        cout << "Nome: " << alunos[i].nome << endl;
        cout << "Notas: " << alunos[i].nota1 << ", " << alunos[i].nota2 << ", " << alunos[i].nota3 << endl;
        cout << "Media: " << alunos[i].media << endl;

        if (alunos[i].media >= 7.0) {
            cout << "Situacao: Aprovado" << endl;
        } else if (alunos[i].media >= 5.0) {
            cout << "Situacao: Recuperacao" << endl;
        } else {
            cout << "Situacao: Reprovado" << endl;
        }

        cout << "-----------------------------" << endl;
    }
}

void buscarAluno(Aluno alunos[], int total) {
    if (total == 0) {
        cout << "Nenhum aluno cadastrado." << endl;
        return;
    }

    string nomeBusca;
    bool encontrou = false;

    limparEntrada();
    cout << "Digite o nome para busca: ";
    getline(cin, nomeBusca);

    cout << fixed << setprecision(2);
    for (int i = 0; i < total; i++) {
        if (alunos[i].nome == nomeBusca) {
            cout << "Aluno encontrado." << endl;
            cout << "Notas: " << alunos[i].nota1 << ", " << alunos[i].nota2 << ", " << alunos[i].nota3 << endl;
            cout << "Media: " << alunos[i].media << endl;
            encontrou = true;
            break;
        }
    }

    if (!encontrou) {
        cout << "Aluno nao encontrado." << endl;
    }
}

void estatisticasTurma(Aluno alunos[], int total) {
    if (total == 0) {
        cout << "Nenhum aluno cadastrado." << endl;
        return;
    }

    double somaMedias = 0.0;
    int indiceMaior = 0;
    int indiceMenor = 0;
    int aprovados = 0;
    int recuperacao = 0;
    int reprovados = 0;

    for (int i = 0; i < total; i++) {
        somaMedias += alunos[i].media;

        if (alunos[i].media > alunos[indiceMaior].media) {
            indiceMaior = i;
        }
        if (alunos[i].media < alunos[indiceMenor].media) {
            indiceMenor = i;
        }

        if (alunos[i].media >= 7.0) {
            aprovados++;
        } else if (alunos[i].media >= 5.0) {
            recuperacao++;
        } else {
            reprovados++;
        }
    }

    cout << fixed << setprecision(2);
    cout << "\n===== ESTATISTICAS DA TURMA =====" << endl;
    cout << "Media geral da turma: " << (somaMedias / total) << endl;
    cout << "Maior media: " << alunos[indiceMaior].media << " (" << alunos[indiceMaior].nome << ")" << endl;
    cout << "Menor media: " << alunos[indiceMenor].media << " (" << alunos[indiceMenor].nome << ")" << endl;
    cout << "Aprovados: " << aprovados << endl;
    cout << "Recuperacao: " << recuperacao << endl;
    cout << "Reprovados: " << reprovados << endl;
}

int main() {
    const int MAX_ALUNOS = 60;
    Aluno alunos[MAX_ALUNOS];
    int totalAlunos = 0;
    int opcao;

    do {
        cout << "\n===== MENU BOLETIM =====" << endl;
        cout << "1 - Cadastrar aluno" << endl;
        cout << "2 - Listar boletim" << endl;
        cout << "3 - Buscar aluno por nome" << endl;
        cout << "4 - Estatisticas da turma" << endl;
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
                cadastrarAluno(alunos, totalAlunos, MAX_ALUNOS);
                break;
            case 2:
                listarAlunos(alunos, totalAlunos);
                break;
            case 3:
                buscarAluno(alunos, totalAlunos);
                break;
            case 4:
                estatisticasTurma(alunos, totalAlunos);
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
