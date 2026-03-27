using namespace std;

struct Aluno {
    int ra;
    char nome[50];
    float media;
};

int main() {
    Aluno alunos1;

    cout << "Digite o RA do aluno: ";
    cin >> alunos1.ra;

    cout << "Digite o nome do aluno: ";
    cin >> alunos1.nome;

    cout << "Digite a média do aluno: ";
    cin >> alunos1.media;
    
    cout << "\n -- Dados do Aluno -- \n";
    cout << "RA: " << alunos1.ra << endl
    cout << "Nome: " << alunos1.nome << endl
    cout << "Média: " << alunos1.media << endl;

    return 0;
}