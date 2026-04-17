using System;

class Acao
{
    public int Codigo;     
    public string Descricao;  
}


class NoPilha
{
    public Acao    Info;        
    public NoPilha Prox;       
}

class Pilha
{
    public NoPilha Topo = null; 

    // Verifica se a pilha ta vazia
    public bool Vazia()
    {
        return Topo == null;    
    }

    
    public void Empilhar(Acao a)
    {
        NoPilha novo = new NoPilha(); 
        novo.Info = a;                
        novo.Prox = Topo;            
        Topo = novo;                 

        Console.WriteLine($" [Pilha] Ação \"{a.Descricao}\" registrada.");
    }

    public bool Desempilhar()
    {
        if (Vazia())
        {
            Console.WriteLine("Nenhuma ação para desfazer.");
            return false;
        }

        NoPilha temp = Topo;         
        Console.WriteLine($"Ação desfeita: \"{temp.Info.Descricao}\"");
        Topo = temp.Prox;            
        temp = null;                 
        return true;
    }

    // Exibe histórico do topo até a base
    public void Exibir()
    {
        if (Vazia())
        {
            Console.WriteLine("  [Histórico] Nenhuma ação registrada.");
            return;
        }

        NoPilha atual = Topo;        
        int i = 1;
        while (atual != null)        
        {
            Console.WriteLine($"  {i++}. [Cod: {atual.Info.Codigo}] {atual.Info.Descricao}");
            atual = atual.Prox;      
        }
    }
}

// Representa um chamado 
class Chamado
{
    public int    Numero;
    public string Nome;
    public string Descricao;
    public Pilha  Historico = new Pilha(); // pilha de ações do chamado
}

// Nó da fila
class NoFila
{
    public Chamado Info;             // Chamado info
    public NoFila  Prox;            // NoFila* prox  ← referência = ponteiro
}

// Fila dinâmica
class Fila
{
    public NoFila Inicio = null;    
    public NoFila Fim    = null;    

    // Verifica se a fila está vazia
    public bool Vazia()
    {
        return Inicio == null;      
    }

    // Retorna o chamado da frente sem remover
    public Chamado Frente()
    {
        if (Vazia()) return null;
        return Inicio.Info;         
    }

    // Enfileira novo chamado no fim
    public void Enfileirar(Chamado c)
    {
        NoFila novo = new NoFila(); 
        novo.Info = c;              
        novo.Prox = null;           

        if (Vazia())
        {
            Inicio = novo;          
            Fim  = novo;          
        }
        else
        {
            Fim.Prox = novo;        
            Fim = novo;        
        }

        Console.WriteLine($" Chamado #{c.Numero} aberto por \"{c.Nome}\".");
    }

    // Remove o primeiro chamado da fila (atendimento)
    public bool Desenfileirar()
    {
        if (Vazia())
        {
            Console.WriteLine("  [Fila] Nenhum chamado na fila.");
            return false;
        }

        NoFila temp = Inicio;       
        Console.WriteLine($"[Fila] Atendendo chamado #{temp.Info.Numero} de \"{temp.Info.Nome}\".");
        Inicio = temp.Prox;         
        if (Inicio == null)
            Fim = null;
        temp = null;                
        return true;
    }

    // Lista todos os chamados na fila
    public void Listar()
    {
        if (Vazia())
        {
            Console.WriteLine("Nenhum chamado na fila.");
            return;
        }

        NoFila atual = Inicio;   
        int pos = 1;
        while (atual != null)       
        {
            Console.WriteLine($"  {pos++}. Chamado #{atual.Info.Numero} | {atual.Info.Nome} | {atual.Info.Descricao}");
            atual = atual.Prox;     
        }
    }
}




// MENU PRICIPAL



class Program
{
    static void ExibirMenu()
    {
        Console.WriteLine("SISTEMA DE CHAMADOS TÉCNICOS");
        Console.WriteLine("  1 - Abrir novo chamado");
        Console.WriteLine("  2 - Atender próximo chamado");
        Console.WriteLine("  3 - Registrar ação");
        Console.WriteLine("  4 - Desfazer ação");
        Console.WriteLine("  5 - Exibir histórico");
        Console.WriteLine("  6 - Listar fila");
        Console.WriteLine("  0 - Sair");
        Console.Write("  Opção: ");
    }

    static void Main()
    {
        Console.Clear();
        Fila fila  = new Fila();
        int contadorChamados = 1;
        int contadorAcoes  = 1;
        int opcao;

        do
        {
            ExibirMenu();

            if (!int.TryParse(Console.ReadLine(), out opcao))
            {
                Console.WriteLine("\n Digite umA opcao valido.");
                continue;
            }

            switch (opcao)
            {
                case 1:
                {
                    Console.Clear();
                    Chamado novo  = new Chamado();
                    novo.Numero = contadorChamados++;

                    Console.Write("\nNome do solicitante: ");
                    novo.Nome = Console.ReadLine();

                    Console.Write("Descrição do chamado: ");
                    novo.Descricao = Console.ReadLine();

                    fila.Enfileirar(novo);
                    break;
                }

                // ----- 2: Atender próximo chamado -----
                case 2:
                    Console.Clear();
                    Console.WriteLine();
                    fila.Desenfileirar();
                    break;

                // ----- 3: Registrar ação -----
                case 3:
                {
                    Console.Clear();
                    Chamado atual = fila.Frente();  // ponteiro para o primeiro
                    if (atual == null)
                    {
                        Console.WriteLine("\n Nenhum chamado na fila.");
                        break;
                    }

                    Acao a    = new Acao();
                    a.Codigo  = contadorAcoes++;

                    Console.WriteLine($"\n  Chamado atual: #{atual.Numero} ({atual.Nome})");
                    Console.Write("  Descrição da ação: ");
                    a.Descricao = Console.ReadLine();

                    atual.Historico.Empilhar(a);
                    break;
                }

                case 4:
                {
                    Console.Clear();
                    Chamado atual = fila.Frente();
                    if (atual == null)
                    {
                        Console.WriteLine("\n  [Erro] Nenhum chamado na fila.");
                        break;
                    }
                    Console.WriteLine($"\n  Chamado atual: #{atual.Numero} ({atual.Nome})");
                    atual.Historico.Desempilhar();
                    break;
                }


                case 5:
                {
                    Console.Clear();
                    Chamado atual = fila.Frente();
                    if (atual == null)
                    {
                        Console.WriteLine("\n  [Erro] Nenhum chamado na fila.");
                        break;
                    }
                    Console.WriteLine($"\n  Histórico do Chamado #{atual.Numero} ({atual.Nome}):");
                    atual.Historico.Exibir();
                    break;
                }

                case 6:
                    Console.Clear();
                    Console.WriteLine("\n  Chamados na fila:");
                    fila.Listar();
                    Console.Write("Digite qualquer coisa para voltar ao menu");
                    Console.ReadKey();
                    Console.Clear();
                    break;

                default:
                    Console.WriteLine("\n  Opção inválida.");
                    break;
            }

        } while (opcao != 0);
    }
}