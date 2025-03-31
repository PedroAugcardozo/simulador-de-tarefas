#define MAXFILA 20
#include<string.h>
struct tpTarefas{
	char descr[100];
	int tempoDeConclusao, prioridade;
};

// Estrutura para a fila de tarefas
struct tpFila {
    int FIM;
    struct tpTarefas FILA[MAXFILA]; // Agora armazenamos tarefas completas
};

// Funções da fila
void Iniciar(tpFila &F);
void Inserir(tpFila &F, tpTarefas Elemento);
tpTarefas Retirar(tpFila &F);
char FilaVazia(tpFila &F);
char FilaCheia(tpFila &F);
void Exibir(tpFila F);
void esvaziarFila(tpFila &F);

void Iniciar(tpFila &F) {
    F.FIM = -1;
}

void Inserir(tpFila &F, tpTarefas E) {
    tpTarefas aux;
    for (int i = F.FIM; i > 0 && F.FILA[i].prioridade < F.FILA[i - 1].prioridade; i--)
    {
        aux = F.FILA[i - 1];
        F.FILA[i - 1] = F.FILA[i];
        F.FILA[i] = aux;
    }
    F.FIM++;
    F.FILA[F.FIM] = E;
}

tpTarefas Retirar(tpFila &F) {
    tpTarefas aux = F.FILA[0];

    for (int i = 0; i < F.FIM; i++) {
        F.FILA[i] = F.FILA[i + 1];
    }

    F.FIM--;
    return aux;
}

char FilaVazia(int fim) {
    return fim <= -1;
}
char FilaCheia(int fim) {
    return fim >= MAXFILA - 1;
}
// Exibe os elementos da fila sem removê-los
void Exibir(tpFila F) {
    if (!FilaVazia(F.FIM)) {
		for (int i = 0; i <= F.FIM; i++) {
        	printf("Tipo: %s | Tempo: %d | Descrição: %s\n", F.FILA[i].prioridade, F.FILA[i].tempoDeConclusao, F.FILA[i].descr);
    	}
    }
}

void esvaziarFila(tpFila &F){
	while(!FilaVazia(F.FIM))
	{
		Retirar(F);
	}
}


//funções moldura
void limparLinha(int pos){
	for(int j=13; j< 70; j++){
		gotoxy(j, pos+1);
		printf(" ");
	}
}

void limparTelaBaixo()
{
	int i;
	for(i = 2; i < 80; i++)
	{
		gotoxy(i,24);
		printf("%c", ' ');
	}
}
void limparTela()
{
	int i,j;
	for(i = 2; i < 80; i++)
	{
		for(j=2; j< 23; j++)
		{
			gotoxy(i,j);
			printf("%c", ' ');
		}
	}
}
