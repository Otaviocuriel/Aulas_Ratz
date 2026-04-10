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
        Console.WriteLine("========================================  ");
        Console.Write("  Opção: ");
    }

    static void Main()
    {
        Fila fila = new Fila();
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
                
                case 1:
                {
                    Chamado novo = new Chamado();
                    novo.Numero = contadorChamados++;

                    Console.Write("\n  Nome do solicitante: ");
                    novo.Nome = Console.ReadLine();

                    Console.Write("  Descrição do chamado: ");
                    novo.Descricao = Console.ReadLine();

                    fila.Enfileirar(novo);
                    break;
                }

                
                case 2:
                    Console.WriteLine();
                    fila.Desenfileirar();
                    break;

                case 3:
                {
                    Chamado atual = fila.Frente();
                    if (atual == null)
                    {
                        Console.WriteLine("\n  [Erro] Nenhum chamado na fila.");
                        break;
                    }

                    Acao a = new Acao();
                    a.Codigo = contadorAcoes++;

                    Console.WriteLine($"\n  Chamado atual: #{atual.Numero} ({atual.Nome})");
                    Console.Write("  Descrição da ação: ");
                    a.Descricao = Console.ReadLine();

                    atual.Historico.Empilhar(a);
                    break;
                }

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

                case 6:
                    Console.WriteLine("\n  Chamados na fila:");
                    fila.Listar();
                    break;

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