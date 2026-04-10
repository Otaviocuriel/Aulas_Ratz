struct Acao { 
    int codigo; 
    string descricao; 
};

struct Chamados
{
    int ID;
    string nome;
    string descricao;
    Acao historico;

};

struct Fila
{
    string[] fila = new string[100]; 
}

