#include <iostream>
using namespace std;



struct Produto{
        int codigoProduto;
        char nomePoduto[100];
        char quantidade[100];
        char unidadeDeMedida[100];
    };

    struct Estoque {
        int codigo;
        char nomeEstoque[100];
        char dataVencimento[100];
        char descricao[100];
        Produto produto;
    };

Estoque adicionarEstoque(){
      Estoque estoque;
            
      estoque.codigo = 1;

      cout << "=== Criar Novo Estoque ===" << endl;
        
      cout << "Digite o nome do estoque: ";
      cin >> estoque.nomeEstoque;
        
      cout << "Digite a data de vencimento (DD/MM/YYYY): ";
      cin >> estoque.dataVencimento;
        
      cout << "Digite a descricao do estoque (opcional): ";
      cin >> estoque.descricao;
        
      cout << "\nEstoque adicionado com sucesso!\n" << endl;
        
      return estoque;
    }

void adicionarProduto(Estoque estoques[]) {

   Produto p;
   cout << "=== Adicionar Produto ===\n";

   // leitura do código do produto (validação simples)
   cout << "Codigo do produto: ";
   while (!(cin >> p.codigoProduto)) {
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "Codigo invalido. Digite novamente: ";
   }

   // descarta o '\n' deixado por >> antes de usar getline/getline-like
   cin.ignore(10000, '\n');

   // leitura de strings (aceita espaços)
   cout << "Nome do produto: ";
   cin.getline(p.nomePoduto, sizeof(p.nomePoduto));

   cout << "Quantidade: ";
   cin.getline(p.quantidade, sizeof(p.quantidade));

   cout << "Unidade de medida: ";
   cin.getline(p.unidadeDeMedida, sizeof(p.unidadeDeMedida));

   // grava o produto no primeiro estoque (índice 0)
   estoques[0].produto = p;

   cout << "Produto adicionado ao estoque \"" << estoques[0].nomeEstoque << "\"\n";
}


int main() {
   Estoque estoque[10];

   int opcao;

   while (true)
   {
      cout << "----Gerenciador de estoque----" ;
      cout << "\n1. Criar estoque";
      cout << "\n2. Adicionar produto ao um estoque";
      cout << "\n3. Ver histórico";
      cout << "\n4. Sair";
      cout << "\nOpção:";
      cin >> opcao;

      switch (opcao)
      {
      case 1:
         adicionarEstoque();
         break;
      
      case 2:
         adicionarProduto(estoque);
         break;
      
      case 3:
         cout << "Teste3";
         break;
      
      case 4:
         cout << "Saindo...";
         exit(0);
      
      default:
         cout << "Opcao inválida";
         break;
      }




   }
   
   



}