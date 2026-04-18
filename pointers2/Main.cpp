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





int main() {
   Estoque estoque[0];

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
         system("cls");
         cout << "Teste";
         break;
      
      case 2:
         system("cls");
         cout << "Teste2";
         break;
      
      case 3:
         system("cls");
         cout << "Teste3";
         break;
      
      case 4:
         system("cls");
         cout << "\nTeste 4";
         break;
      
      default:
         system("cls");
         cout << "Saindo...";
         exit(0);
      }



   }
   
   



}