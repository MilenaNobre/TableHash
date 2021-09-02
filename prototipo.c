#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <locale.h>// use setlocale
#include <unistd.h> // devido a função sleep
#define MAX 500 //tamanho do CORE
#include "prototipo.h"

double PCFreq = 0.0;
__int64 CounterStart = 0;

CORE* inicializarCORE(){
	CORE *novo;

	novo = (CORE*)malloc(sizeof(CORE));
	novo->endereco = NULL;
	novo->qtd = 0;

	return(novo);
}

processo * inicializarProcesso(){
	processo *novo;

	novo = (processo*)malloc(sizeof(processo));

	novo->ant = NULL;
	novo->prox = NULL;
	novo->AcaoCobranca = NULL;
	novo->AcaoDevolucao = NULL;
	novo->numProcesso = 0;

	return(novo);
}

long geracaoChave(long chave){
    return (chave & 0x7F0FFFFFF) % MAX;
}

int inserirHash(CORE* CORE_HASH, int chave,processo * novoProcesso){

	if(CORE_HASH->endereco[chave].dados->numProcesso == 0){  //Nao tem nenhum processo vinculado
	    CORE_HASH->endereco[chave].dados = novoProcesso;
        CORE_HASH->qtd++; //quantidade de processos
        return 1;
	} else{
		CORE_HASH->qtd++; //incrementa quantidade de processos
        CORE_HASH->endereco[chave].qtdColisao++; //quantidade de colisões da chave
        novoProcesso->prox = CORE_HASH->endereco[chave].dados; //novoProcesso->prox receve o primeiro elemento da lista (tornado o segundo da lista)
        CORE_HASH->endereco[chave].dados = novoProcesso; //Ponteiro da tabela hash (dados) recebe o novo elemento como primeiro da lista
        novoProcesso->prox->ant = novoProcesso; //segundo da lista->ant recebe o novo elemento da lista (tornando primeiro da lista)
		return 1;
	}
	return 0;
}

void buscaProcesso(CORE* CORE_HASH, long chave, long numprocesso){
    struct processo * lista;
	lista = CORE_HASH->endereco[chave].dados;
	int flag = 1;

    if(lista->numProcesso == 0){
        printf("\n================================================\n\n");
        printf("Não há registros com esse número de processo!\n");
        printf("\n================================================\n\n");
    } else{
    	printf("\n=========== Dados CORE_HASH %ld =================\n\n",chave);
    	while(lista != NULL){
			if(lista->numProcesso == numprocesso){
    			printf("===========================================================\n");
				printf("Processo: %ld\n",lista->numProcesso);
				printf("Nome Beneficiario: %s\n",lista->nome_beneficiario);
				printf("CPF: %s\n",lista->cpf);
				printf("Especie beneficio: %s\n",lista->especie_beneficio);
				if(lista->AcaoDevolucao != NULL){
					printf("Nº ação: %ld\n",lista->AcaoDevolucao->num_acao);
					printf("Tipo Ação: %s\n",lista->AcaoDevolucao->tipo_acao);
					printf("tipo_situacao: %s\n",lista->AcaoDevolucao->tipo_situacao);
					printf("Valor: %.2f\n",lista->AcaoDevolucao->valor);
					printf("Tipo Pagamento: %s\n",lista->AcaoDevolucao->tipoPagamento);
				} else{
					printf("Nº ação: %ld\n",lista->AcaoCobranca->num_acao);
					printf("Tipo Ação: %s\n",lista->AcaoCobranca->tipo_acao);
					printf("tipo_situacao: %s\n",lista->AcaoCobranca->tipo_situacao);
					printf("Valor: %.2f\n",lista->AcaoCobranca->valor);
					printf("Atualizacao Monetaria: %.2f\n",lista->AcaoCobranca->atualizacaoMonetaria);
					printf("Multa: %.2f\n",lista->AcaoCobranca->multa);
					printf("Jutos: %.2f\n",lista->AcaoCobranca->juros);
				}
				flag = 0;
				printf("===========================================================\n");

			}
		lista = lista->prox;
		}
		if(flag==1){
				printf("Não há registros com esse número de processo!\n");
                printf("\n================================================\n\n");
		}
		else{
            printf("\nQuantidade de colisão: %d\n",CORE_HASH->endereco[chave].qtdColisao);
            printf("\n===========================================================\n\n");
		}
    }
}
int ExcluirProcesso(CORE* CORE_HASH, long chave, long numprocesso){
    struct processo * lista;
	lista = CORE_HASH->endereco[chave].dados;
	int excluir;

    if(lista == NULL){
        printf("Não há registros com esse número de processo!\n");
    } else{
    	while(lista != NULL){
    		if(lista->numProcesso == numprocesso){
	    		printf("Deseja realmente excluir o processo? 1- SIM  2-NÃO\n");
	    		scanf("%d",&excluir);
	    		do{
	    			switch(excluir){
	    			case 1:
	    				if (lista->ant == NULL){ // se for o primeiro da lista
						    CORE_HASH->qtd--; //decrementa quantidade de processos
						    CORE_HASH->endereco[chave].qtdColisao--;
							CORE_HASH->endereco[chave].dados =  lista->prox;
							free(lista);
							return 1;
						} else{
							CORE_HASH->qtd--;
							CORE_HASH->endereco[chave].qtdColisao--;
							if(lista->prox != NULL){
								lista->ant->prox = lista->prox;
								lista->prox->ant = lista->ant;
								free(lista);
							} else{
								lista->ant->prox = lista->prox;
								free(lista);
							}
							return 1;
						}

	    			break;
	    			case 2:
	    				return 0;
	    			break;
					default:
						printf("Opção inválida!\n");
						system("pause");
						excluir = 0;
					break;
					}
				} while(excluir == 0);
			}
			lista = lista->prox;
		}
		return 0;
    }
}
int existenciaProcesso(CORE* CORE_HASH, long chave,long num){
    struct processo * lista;
    lista = CORE_HASH->endereco[chave].dados;

    if(lista->numProcesso != 0){
        if(lista->numProcesso == num){
            return 0;
        }
        else{
           while(lista->numProcesso != 0){
            if(lista->numProcesso == num){
                return 0;
            }
            else{
                if(lista->prox != NULL){
                    lista = lista->prox;
                }
                else{
                   return 1;
                }
             }
           }
        }
    }
    else{
        return 1;
    }
}


int extrai_linha(char * linha,int tamanho_linha,CORE * CORE_HASH){
    int i,j;
	long chave;
    int qtd_palavras=0;
    int total_palavras=0;
    char palavras[10][100];
    char auxiliarAcao[100];

    struct processo * aux;
    struct acaoDevolucao *aux2;
    struct acaoCobranca *aux3;

    aux = inicializarProcesso();

    for(i=0,j=0;i<tamanho_linha;i++) {
        if (linha[i]=='\n'){
            break;
        }
        if (linha[i] == ';'){
            palavras[qtd_palavras][j] = '\0';
            qtd_palavras++;
            j=0;
        } else {
            palavras[qtd_palavras][j] = linha[i];
            j++;
        }
    }

    palavras[qtd_palavras][j] = '\0';
    total_palavras = qtd_palavras+1;

	aux->numProcesso = atoi(palavras[0]);
	chave = geracaoChave(aux->numProcesso);
	strcpy(aux->nome_beneficiario,palavras[1]);
	strcpy(aux->cpf,palavras[2]);
	strcpy(aux->especie_beneficio,palavras[3]);
	strcpy(auxiliarAcao,palavras[4]);

	if(strcmp(auxiliarAcao,"Devolução") == 0){
    	aux2 = (acaoDevolucao*)malloc(sizeof(acaoDevolucao));
		strcpy(aux2->tipo_acao, auxiliarAcao);
		strcpy(aux2->tipoPagamento,palavras[5]);
		strcpy(aux2->tipo_situacao,palavras[6]);

		srand(time(NULL));
		aux2->num_acao = rand() % MAX;
		aux2->valor = rand() % 500;

		aux->AcaoDevolucao = aux2;
		aux->AcaoCobranca = NULL;

	} else{
		aux3 = (acaoCobranca*)malloc(sizeof(acaoCobranca));

		strcpy(aux3->tipo_acao, auxiliarAcao);
		strcpy(aux3->tipo_situacao,palavras[5]);

		srand(time(NULL));
		aux3->valor = rand() % 500;
		aux3->atualizacaoMonetaria = rand() % 50;
		aux3->multa = rand() % 200;
		aux3->juros = rand() % 100;

		aux->AcaoCobranca = aux3;
		aux->AcaoDevolucao = NULL;
	}

	if(existenciaProcesso(CORE_HASH,chave,aux->numProcesso) == 0){
		system("cls");
		printf("==============================\n\n");
		printf("Número do processo já existe!\n\n");
		printf("==============================\n\n");
		system("pause");
		return 0;
	} else{
		if(CORE_HASH->endereco[chave].dados->numProcesso == 0){  //Nao tem nenhum processo vinculado
		    CORE_HASH->endereco[chave].dados = aux;
        	CORE_HASH->qtd++; //quantidade de processos
        	return 1;
		}else{
            CORE_HASH->qtd++; //incrementa quantidade de processos
            CORE_HASH->endereco[chave].qtdColisao++; //quantidade de colisões da chave
            aux->prox = CORE_HASH->endereco[chave].dados; //novoProcesso->prox receve o primeiro elemento da lista (tornado o segundo da lista)
            CORE_HASH->endereco[chave].dados = aux; //Ponteiro da tabela hash (dados) recebe o novo elemento como primeiro da lista
            aux->prox->ant = aux; //segundo da lista->ant recebe o novo elemento da lista (tornando primeiro da lista)
            return 1;
		}
	}
}
void StartCounter(){
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        printf("QueryPerformanceFrequency Failed.\n");
    PCFreq = (double)(li.QuadPart) / 1000.0;
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter(){
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return (double)(li.QuadPart - CounterStart) / PCFreq;
}
