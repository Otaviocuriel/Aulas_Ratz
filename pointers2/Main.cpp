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




int main() {
   Estoque estoque[0];

   int opcao;

   while (true)
   {
      system("cls");
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
      
      case 2:
         cout << "Teste2";
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