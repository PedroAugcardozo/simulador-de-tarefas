#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>
#include<time.h>

#include "TADFIlaTrab.h"

//Pedro Augusto de Lima Cardozo RA: 262318989
//Mateus Alberto Bilar Moreira RA: 262318563
//Ian Carlos Pinheiro Libanio da Silva RA:262318636

struct tpOperador{
	int pos, tempo, tipo;
};

void entrada(tpFila &fila)
{
	FILE *PtrArq = fopen("tarefas.txt", "r");
	char tipo[15], string[15];
	tpTarefas tarefas;
	if(PtrArq == NULL)
	{
		printf("erro ao abrir o arquivo!!!!");
	}
	else
	{
		while(!feof(PtrArq))
		{
			fscanf(PtrArq,"%[^,],%d,%[^\n]\n",tipo, &tarefas.tempoDeConclusao, &tarefas.descr);
			if(strcmp(tipo, "Urgente")==0)
			{
				tarefas.prioridade=1;
			}
			if(strcmp(tipo, "Normal")==0)
			{
				tarefas.prioridade=2;
			}
			if(strcmp(tipo, "Opcional")==0)
			{
				tarefas.prioridade=3;
			}
			Inserir(fila, tarefas);
		}
	}
	fclose(PtrArq);
}
void preencherOp(int numOperadores,tpOperador op[10])
{
	int i;
	for(i = 0; i < numOperadores; i++)
	{
		op[i].pos = i + 1;
	}
}

int tarefasNaoConcluidas(tpFila &fila)
{
	int cont=0;
	while(!FilaVazia(fila.FIM))
	{
		Retirar(fila);
		cont++;
	}
	if(cont > 0)
		return cont;
	else
		return 0;
}
void atendimento(tpFila &fila)
{
	limparTela();
	
	int tempo, operadores,i=0, j, tipo1=0, tipo2=0, tipo3=0, soma1=0, soma2=0, soma3=0, cont=0, naoConcluidas=0;
	float media1, media2, media3;
	tpTarefas tarefa;
	tpOperador op[10];
	
	limparTelaBaixo();
	gotoxy(3,24);
	textcolor(3);
	printf("Digite tempo de simulacao[em segundos]: ");
	scanf("%d",&tempo);
	limparTelaBaixo();
	gotoxy(3,24);
	printf("Digite o numero de operadores [MAX 10]: ");
	scanf("%d",&operadores);
	
	if(operadores > 10 || tempo <= 0 || operadores <= 0 || tempo > 100)
	{
		gotoxy(15,13);
		textcolor(4);
		printf("NUMERO INVALIDO DE OPERADORES OU TEMPO DE SIMULACAO");
		gotoxy(18,14);
		printf("[MAX DE 100 segundos] [MAX de 10 operacoes]");
	}
	else
	{
		limparTelaBaixo();
		gotoxy(23,24);
		printf("SIMULADOR FABRICA DE BRINQUEDOS");
		//coloca os operadores no lugar
		preencherOp(operadores, op);
		for(j = 0; j < operadores; j++){
			gotoxy(2, j+2);
			printf("Operador %d", op[j].pos);
			tarefa = Retirar(fila);
			op[j].tempo=tarefa.tempoDeConclusao;
			op[j].tipo=tarefa.prioridade;
			gotoxy(13, j+2);
			printf("%s",tarefa.descr);
			printf("%d",tarefa.prioridade);
		}
		i=0;
		while(i <= tempo && cont < operadores)
		{
			for(j =0; j <operadores; j++){
				
				//aqui no ultima vez na repetição ele vai ver quem tem tempo zero e adiciona os tipos tbm
				if(i + 1 == tempo){
					if(op[j].tempo - 1 <= 0 && FilaVazia(fila.FIM)){
						if(op[j].tipo == 1){
							tipo1++;
						}
						if(op[j].tipo == 2){
							tipo2++;
						}
						if(op[j].tipo == 3){
							tipo3++;
						}
					}
				}
				//se o tempo acabar, ele adiciona uma tarefa nova ao operador e adiciona o tempo e o tipo a ele (e encrenta a tarefa realizda no tipo)
				if(op[j].tempo == 0 && !FilaVazia(fila.FIM)){
					if(op[j].tipo == 1){
						tipo1++;
					}
					if(op[j].tipo == 2){
						tipo2++;
					}
					if(op[j].tipo == 3){
						tipo3++;
					}
					tarefa = Retirar(fila);
					limparLinha(op[j].pos);
					op[j].tempo=tarefa.tempoDeConclusao;
					op[j].tipo=tarefa.prioridade;
					gotoxy(13, j+2);
					printf("%s", tarefa.descr);
					printf("%d", tarefa.prioridade);
				}
				gotoxy(70,j+2);
				printf("tempo:%d ", op[j].tempo);
			}
			cont=0;
			//diminui o tempo de execusao de cada tarefa
			for(j=0; j< operadores; j++){
				if(op[j].tempo > 0){
					op[j].tempo--;
					if(op[j].tipo == 1){
						soma1++;
					} 
					else{
						if(op[j].tipo==2){
							soma2++;
						} 
						else{
							soma3++;
						}
					}
				} 
				else{
					cont++;	
				}
				
				if(i + 1 == tempo){
					if(op[j].tempo - 1 != 0){
						naoConcluidas++;
					}
				}
			}
			i++;
			Sleep(1000);
		}
		
		//aqui eu garanto que nao ocorra uma divisao por 0, já que pode acontecer de nenhuma tarefa de um tipo ser feita
		if(soma1 > 0 && tipo1 > 0){
			media1 = soma1/tipo1;
		}else{
			media1=0;
		}
		if(soma2 > 0 && tipo2 > 0){
			media2 = soma2/tipo2;
		} else{
			media2=0;
		}
		if(soma3 > 0 && tipo3 > 0){
			media3 = soma3/tipo3;
		} else{
			media3=0;
		}
		
		//aqui é as saidas das tarefas realizadas
		naoConcluidas+=tarefasNaoConcluidas(fila);
		limparTela();
		gotoxy(2,2);
		printf("numero de tarefas nao concluidas: %d", naoConcluidas);
		gotoxy(2,3);
		printf("numero de tarefas realizadas URGENTES:%d",tipo1);
		gotoxy(2,4);
		printf("numero de tarefas realizadas NORMAIS:%d",tipo2);
		gotoxy(2, 5);
		printf("numero de tarefas realizadas OPCIONAIS:%d",tipo3);
		
		//aqui é as saidas das medias
		gotoxy(2,10);
		printf("a media de tempo do tipo URGENTE e:%.1f",media1);
		gotoxy(2,11);
		printf("a media de tempo do tipo NORMAL e:%.1f",media2);
		gotoxy(2,12);
		printf("a media de tempo do tipo OPCIONAL e:%.1f",media3);
	}
}
void moldura(void){
	int i,j,CF=80, CI=1, LI=1, LF=25;
	gotoxy(1,1);
	printf("%c", 201);
	gotoxy(80,1);
	printf("%c", 187);
	gotoxy(1,25);
	printf("%c", 200);
	gotoxy(80,25);
	printf("%c", 188);
	for(i=CI+1;i<CF;i++){
		gotoxy(i,1);
		printf("%c",205);
		gotoxy(i,25);
		printf("%c",205);
		Sleep(10);
	}
	for(i=LI+1;i<LF;i++){
		gotoxy(1,i);
		printf("%c",186);
		gotoxy(80,i);
		printf("%c",186);
		Sleep(10);
	}
	gotoxy(1,23);
	printf("%c", 204);
	gotoxy(80,23);
	printf("%c", 185);
	for(i=CI+1;i<CF;i++){
		gotoxy(i,23);
		printf("%c",205);
		Sleep(10);
	}
	textcolor(1);
	gotoxy(2,27);
	printf("Pedro Augusto de Lima Cardozo RA:262318989");
	gotoxy(2,28);
	printf("Mateus Alberto Bilar Moreira RA: 262318563");
	gotoxy(2,29);
	printf("Ian Carlos Pinheiro Libanio da Silva RA:262318636");
}
int main()
{
	int op;
	
	moldura();
	
	tpFila fila;
	Iniciar(fila);
	do
	{
		esvaziarFila(fila);
		entrada(fila);
		atendimento(fila);
		limparTelaBaixo();
		gotoxy(2,24);
		printf("deseja fazer uma nova simulacao [S/N]");
		op=getch();
	}while(toupper(op) == 'S');
	
	gotoxy(10,15);
}

