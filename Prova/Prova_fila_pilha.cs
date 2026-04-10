using System;

// ============================================================
// ESTRUTURAS (classes = equivalente a struct com ponteiro)
// ============================================================

// Representa uma ação registrada
class Acao
{
    public int Codigo;     
    public string Descricao;  
}


class NoPilha
{
    public Acao    Info;        // Acao info
    public NoPilha Prox;       // NoPilha* prox  ← referência = ponteiro em C#
}

// Pilha dinâmica (LIFO) — equivalente a:
// struct Pilha { NoPilha* topo; }
class Pilha
{
    public NoPilha Topo = null; // NoPilha* topo = NULL

    // Verifica se a pilha está vazia
    public bool Vazia()
    {
        return Topo == null;    // topo == NULL
    }

    // Empilha — equivalente ao new NoPilha do C++
    public void Empilhar(Acao a)
    {
        NoPilha novo = new NoPilha(); // new NoPilha
        novo.Info = a;                // novo->info = a
        novo.Prox = Topo;            // novo->prox = topo
        Topo = novo;                  // topo = novo

        Console.WriteLine($"  [Pilha] Ação \"{a.Descricao}\" registrada.");
    }

    // Desempilha — equivalente ao delete do C++
    public bool Desempilhar()
    {
        if (Vazia())
        {
            Console.WriteLine("  [Pilha] Nenhuma ação para desfazer.");
            return false;
        }

        NoPilha temp = Topo;         // NoPilha* temp = topo
        Console.WriteLine($"  [Pilha] Ação desfeita: \"{temp.Info.Descricao}\"");
        Topo = temp.Prox;            // topo = temp->prox
        temp = null;                  // delete temp (GC libera a memória)
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

        NoPilha atual = Topo;        // NoPilha* atual = topo
        int i = 1;
        while (atual != null)        // while (atual != NULL)
        {
            Console.WriteLine($"  {i++}. [Cod: {atual.Info.Codigo}] {atual.Info.Descricao}");
            atual = atual.Prox;      // atual = atual->prox
        }
    }
}

// Representa um chamado técnico
class Chamado
{
    public int    Numero;
    public string Nome;
    public string Descricao;
    public Pilha  Historico = new Pilha(); // pilha de ações do chamado
}

// Nó da fila — equivalente a:
// struct NoFila { Chamado info; NoFila* prox; }
class NoFila
{
    public Chamado Info;             // Chamado info
    public NoFila  Prox;            // NoFila* prox  ← referência = ponteiro
}

// Fila dinâmica (FIFO) — equivalente a:
// struct Fila { NoFila* inicio; NoFila* fim; }
class Fila
{
    public NoFila Inicio = null;    // NoFila* inicio = NULL
    public NoFila Fim    = null;    // NoFila* fim    = NULL

    // Verifica se a fila está vazia
    public bool Vazia()
    {
        return Inicio == null;      // inicio == NULL
    }

    // Retorna o chamado da frente sem remover
    public Chamado Frente()
    {
        if (Vazia()) return null;
        return Inicio.Info;         // inicio->info
    }

    // Enfileira novo chamado no fim
    public void Enfileirar(Chamado c)
    {
        NoFila novo = new NoFila(); // new NoFila
        novo.Info = c;              // novo->info = c
        novo.Prox = null;           // novo->prox = NULL

        if (Vazia())
        {
            Inicio = novo;          // inicio = novo
            Fim    = novo;          // fim    = novo
        }
        else
        {
            Fim.Prox = novo;        // fim->prox = novo
            Fim      = novo;        // fim = novo
        }

        Console.WriteLine($"  [Fila] Chamado #{c.Numero} aberto por \"{c.Nome}\".");
    }

    // Remove o primeiro chamado da fila (atendimento)
    public bool Desenfileirar()
    {
        if (Vazia())
        {
            Console.WriteLine("  [Fila] Nenhum chamado na fila.");
            return false;
        }

        NoFila temp = Inicio;       // NoFila* temp = inicio
        Console.WriteLine($"  [Fila] Atendendo chamado #{temp.Info.Numero} de \"{temp.Info.Nome}\".");
        Inicio = temp.Prox;         // inicio = temp->prox
        if (Inicio == null)
            Fim = null;
        temp = null;                // delete temp
        return true;
    }

    // Lista todos os chamados na fila
    public void Listar()
    {
        if (Vazia())
        {
            Console.WriteLine("  [Fila] Nenhum chamado na fila.");
            return;
        }

        NoFila atual = Inicio;      // NoFila* atual = inicio
        int pos = 1;
        while (atual != null)       // while (atual != NULL)
        {
            Console.WriteLine($"  {pos++}. Chamado #{atual.Info.Numero} | {atual.Info.Nome} | {atual.Info.Descricao}");
            atual = atual.Prox;     // atual = atual->prox
        }
    }
}

// ============================================================
// MENU E PROGRAMA PRINCIPAL
// ============================================================

class Program
{
    static void ExibirMenu()
    {
        Console.WriteLine("\n========================================");
        Console.WriteLine("   SISTEMA DE CHAMADOS TÉCNICOS");
        Console.WriteLine("========================================");
        Console.WriteLine("  1 - Abrir novo chamado");
        Console.WriteLine("  2 - Atender próximo chamado");
        Console.WriteLine("  3 - Registrar ação");
        Console.WriteLine("  4 - Desfazer ação");
        Console.WriteLine("  5 - Exibir histórico");
        Console.WriteLine("  6 - Listar fila");
        Console.WriteLine("  0 - Sair");
        Console.WriteLine("========================================");
        Console.Write("  Opção: ");
    }

    static void Main()
    {
        Fila fila            = new Fila();
        int contadorChamados = 1;
        int contadorAcoes    = 1;
        int opcao;

        do
        {
            ExibirMenu();

            if (!int.TryParse(Console.ReadLine(), out opcao))
            {
                Console.WriteLine("\n  [Erro] Digite um número válido.");
                continue;
            }

            switch (opcao)
            {
                // ----- 1: Abrir novo chamado -----
                case 1:
                {
                    Chamado novo   = new Chamado();
                    novo.Numero    = contadorChamados++;

                    Console.Write("\n  Nome do solicitante: ");
                    novo.Nome = Console.ReadLine();

                    Console.Write("  Descrição do chamado: ");
                    novo.Descricao = Console.ReadLine();

                    fila.Enfileirar(novo);
                    break;
                }

                // ----- 2: Atender próximo chamado -----
                case 2:
                    Console.WriteLine();
                    fila.Desenfileirar();
                    break;

                // ----- 3: Registrar ação -----
                case 3:
                {
                    Chamado atual = fila.Frente();  // ponteiro para o primeiro
                    if (atual == null)
                    {
                        Console.WriteLine("\n  [Erro] Nenhum chamado na fila.");
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

                // ----- 4: Desfazer última ação -----
                case 4:
                {
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

                // ----- 5: Exibir histórico -----
                case 5:
                {
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

                // ----- 6: Listar fila -----
                case 6:
                    Console.WriteLine("\n  Chamados na fila:");
                    fila.Listar();
                    break;

                // ----- 0: Sair -----
                case 0:
                    Console.WriteLine("\n  Encerrando sistema. Até logo!");
                    break;

                default:
                    Console.WriteLine("\n  [Erro] Opção inválida.");
                    break;
            }

        } while (opcao != 0);
    }
}