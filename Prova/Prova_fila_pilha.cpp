#include <iostream>
#include <cstring>

using namespace std;

struct Acao {
	int codigo;
	char descricao[100];
};

struct NoPilha {
	Acao info;
	NoPilha* prox;
};

struct Pilha {
	NoPilha* topo;
};

struct Chamado {
	int numero;
	char nome[100];
	char descricao[200];
	Pilha historico;
};

struct NoFila {
	Chamado info;
	NoFila* prox;
};

struct Fila {
	NoFila* inicio;
	NoFila* fim;
};

void limparBufferEntrada() {
	cin.clear();
	cin.ignore(10000, '\n');
}

int lerInteiro(const char* mensagem) {
	int valor;

	while (true) {
		cout << mensagem;
		if (cin >> valor) {
			limparBufferEntrada();
			return valor;
		}

		cout << "Entrada invalida. Digite um numero inteiro.\n";
		limparBufferEntrada();
	}
}

void lerTexto(const char* mensagem, char* destino, int tamanho) {
	cout << mensagem;
	cin.getline(destino, tamanho);
}

void inicializarPilha(Pilha& p) {
	p.topo = NULL;
}

bool pilhaVazia(const Pilha& p) {
	return p.topo == NULL;
}

void empilhar(Pilha& p, const Acao& a) {
	NoPilha* novo = new NoPilha;
	novo->info = a;
	novo->prox = p.topo;
	p.topo = novo;
}

bool desempilhar(Pilha& p, Acao& removida) {
	if (pilhaVazia(p)) {
		return false;
	}

	NoPilha* aux = p.topo;
	removida = aux->info;
	p.topo = aux->prox;
	delete aux;
	return true;
}

void liberarPilha(Pilha& p) {
	Acao descartada;
	while (desempilhar(p, descartada)) {
	}
}

void exibirPilha(const Pilha& p) {
	if (pilhaVazia(p)) {
		cout << "Sem acoes registradas.\n";
		return;
	}

	NoPilha* atual = p.topo;
	cout << "Historico de acoes (do topo para a base):\n";
	while (atual != NULL) {
		cout << "- Codigo: " << atual->info.codigo
			 << " | Descricao: " << atual->info.descricao << "\n";
		atual = atual->prox;
	}
}

void inicializarFila(Fila& f) {
	f.inicio = NULL;
	f.fim = NULL;
}

bool filaVazia(const Fila& f) {
	return f.inicio == NULL;
}

void enfileirar(Fila& f, const Chamado& c) {
	NoFila* novo = new NoFila;
	novo->info = c;
	novo->prox = NULL;

	if (filaVazia(f)) {
		f.inicio = novo;
		f.fim = novo;
	} else {
		f.fim->prox = novo;
		f.fim = novo;
	}
}

bool desenfileirar(Fila& f, Chamado& removido) {
	if (filaVazia(f)) {
		return false;
	}

	NoFila* aux = f.inicio;
	removido = aux->info;
	f.inicio = aux->prox;

	if (f.inicio == NULL) {
		f.fim = NULL;
	}

	delete aux;
	return true;
}

void liberarFilaChamados(Fila& f) {
	Chamado c;
	while (desenfileirar(f, c)) {
		liberarPilha(c.historico);
	}
}

Chamado* buscarChamadoNaFila(Fila& f, int numero) {
	NoFila* atual = f.inicio;

	while (atual != NULL) {
		if (atual->info.numero == numero) {
			return &atual->info;
		}
		atual = atual->prox;
	}

	return NULL;
}

void exibirDadosChamado(const Chamado& c) {
	cout << "Numero: " << c.numero << "\n";
	cout << "Solicitante: " << c.nome << "\n";
	cout << "Descricao: " << c.descricao << "\n";
}

void listarFila(const Fila& f) {
	if (filaVazia(f)) {
		cout << "Fila vazia.\n";
		return;
	}

	cout << "Fila de chamados aguardando atendimento:\n";
	NoFila* atual = f.inicio;
	while (atual != NULL) {
		cout << "- Chamado " << atual->info.numero
			 << " | " << atual->info.nome << "\n";
		atual = atual->prox;
	}
}

int main() {
	Fila filaAguardando;
	Fila filaFinalizados;
	inicializarFila(filaAguardando);
	inicializarFila(filaFinalizados);

	Chamado chamadoAtual;
	bool existeChamadoAtual = false;

	int opcao;
	do {
		cout << "\n=== SISTEMA DE CHAMADOS ===\n";
		cout << "1 - Abrir novo chamado\n";
		cout << "2 - Atender proximo chamado\n";
		cout << "3 - Registrar acao\n";
		cout << "4 - Desfazer acao\n";
		cout << "5 - Exibir historico\n";
		cout << "6 - Listar fila\n";
		cout << "0 - Sair\n";

		opcao = lerInteiro("Escolha uma opcao: ");

		switch (opcao) {
			case 1: {
				Chamado novo;
				novo.numero = lerInteiro("Numero do chamado: ");
				lerTexto("Nome do solicitante: ", novo.nome, 100);
				lerTexto("Descricao do chamado: ", novo.descricao, 200);
				inicializarPilha(novo.historico);

				enfileirar(filaAguardando, novo);
				cout << "Chamado aberto e inserido na fila com sucesso.\n";
				break;
			}

			case 2: {
				if (existeChamadoAtual) {
					enfileirar(filaFinalizados, chamadoAtual);
					existeChamadoAtual = false;
					cout << "Chamado anterior finalizado e movido para o historico geral.\n";
				}

				if (desenfileirar(filaAguardando, chamadoAtual)) {
					existeChamadoAtual = true;
					cout << "Proximo chamado em atendimento:\n";
					exibirDadosChamado(chamadoAtual);
				} else {
					cout << "Nao ha chamados aguardando atendimento.\n";
				}
				break;
			}

			case 3: {
				if (!existeChamadoAtual) {
					cout << "Nao ha chamado em atendimento para registrar acao.\n";
					break;
				}

				Acao a;
				a.codigo = lerInteiro("Codigo da acao: ");
				lerTexto("Descricao da acao: ", a.descricao, 100);
				empilhar(chamadoAtual.historico, a);
				cout << "Acao registrada no chamado " << chamadoAtual.numero << ".\n";
				break;
			}

			case 4: {
				if (!existeChamadoAtual) {
					cout << "Nao ha chamado em atendimento para desfazer acao.\n";
					break;
				}

				Acao removida;
				if (desempilhar(chamadoAtual.historico, removida)) {
					cout << "Acao desfeita: [" << removida.codigo
						 << "] " << removida.descricao << "\n";
				} else {
					cout << "Nao ha acoes para desfazer neste chamado.\n";
				}
				break;
			}

			case 5: {
				int numeroBusca = lerInteiro("Informe o numero do chamado: ");
				bool encontrado = false;

				if (existeChamadoAtual && chamadoAtual.numero == numeroBusca) {
					cout << "Chamado em atendimento encontrado:\n";
					exibirDadosChamado(chamadoAtual);
					exibirPilha(chamadoAtual.historico);
					encontrado = true;
				}

				if (!encontrado) {
					Chamado* emEspera = buscarChamadoNaFila(filaAguardando, numeroBusca);
					if (emEspera != NULL) {
						cout << "Chamado encontrado na fila de espera:\n";
						exibirDadosChamado(*emEspera);
						exibirPilha(emEspera->historico);
						encontrado = true;
					}
				}

				if (!encontrado) {
					Chamado* finalizado = buscarChamadoNaFila(filaFinalizados, numeroBusca);
					if (finalizado != NULL) {
						cout << "Chamado encontrado no historico de finalizados:\n";
						exibirDadosChamado(*finalizado);
						exibirPilha(finalizado->historico);
						encontrado = true;
					}
				}

				if (!encontrado) {
					cout << "Chamado nao encontrado.\n";
				}
				break;
			}

			case 6: {
				if (existeChamadoAtual) {
					cout << "Chamado atualmente em atendimento: "
						 << chamadoAtual.numero << " | "
						 << chamadoAtual.nome << "\n";
				} else {
					cout << "Nenhum chamado em atendimento no momento.\n";
				}

				listarFila(filaAguardando);
				break;
			}

			case 0:
				cout << "Encerrando sistema...\n";
				break;

			default:
				cout << "Opcao invalida. Tente novamente.\n";
		}
	} while (opcao != 0);

	if (existeChamadoAtual) {
		liberarPilha(chamadoAtual.historico);
	}
	liberarFilaChamados(filaAguardando);
	liberarFilaChamados(filaFinalizados);

	return 0;
}
