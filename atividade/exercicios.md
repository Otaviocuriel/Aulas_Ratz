1. Qual é a entidade principal do sistema?
A entidade principal é o Projeto, pois é o objeto central que o sistema precisa registrar e gerenciar.


2. Quais atributos devem compor essa entidade?

id — identificação única do projeto (inteiro)
nome — nome do projeto (texto)
aluno — nome do aluno responsável (texto)
area — área do projeto: programação, eletrônica, IA ou desenvolvimento web (texto)
semestre — semestre em que foi desenvolvido (texto, ex: 1/2025)
status — situação do projeto: em andamento ou concluído (texto)


3. Como será definida a struct?
cppstruct Projeto {
    int  id;
    char nome[100];
    char aluno[100];
    char area[50];
    char semestre[20];
    char status[20];
};


4. Qual será o tipo do vetor que armazenará os registros?
Um vetor do tipo Projeto com tamanho fixo de 20 posições, declarado como:
cppProjeto projetos[20];


5. Quais funções devem ser criadas?

cadastrar() — insere um novo projeto no vetor
alterar() — modifica os dados de um projeto pelo ID
exibir() — lista todos os projetos cadastrados
excluir() — remove um projeto e reorganiza o vetor