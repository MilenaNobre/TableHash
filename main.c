/* elaboração da função principal
	TABELA HASH
		Implementação utilizando uma estrutura similar a da "lista sequencial Estática"
		Utiliza um "array" para armazenar os elementos
		DESVANTAGEM: necessita que se defina o tamanho do array previamente,
            isso limita o número de elementos que podemos armazenar
*/
#include "prototipo.c"

int main(){
	setlocale(LC_ALL,"Portuguese");

    CORE * CORE_HASH; //Estrutura que aponta para a Tabela hash
	hash TAB_HASH[MAX]; // Tabela Hash

	int i, importar, tipoAcao, chave, op, tipoEscolhido,situacao,tipoPg;
	long processoBusca, processoExcluir;
	struct processo * auxiliar;
    struct processo * aux;
    struct acaoDevolucao *aux2;
    struct acaoCobranca *aux3;

    double tempoEmMilissegundo = 0.0000000;

    char * linha;
    int tamanho_linha=5000;
    FILE * arq = NULL;

	CORE_HASH = inicializarCORE(); //cria a Strutur que aponta para a Tabela hash
	CORE_HASH->endereco = TAB_HASH;

	for(i=0;i<MAX;i++){	// inicializar a Tabela Hash
		TAB_HASH[i].qtdColisao = 0;
		aux = inicializarProcesso();
		TAB_HASH[i].dados = aux;
	}

	do{
        printf("=============MENU===============\n");
        printf(" 1 - Inserir processo\n");
        printf(" 2 - Buscar processo\n");
        printf(" 3 - Excluir processo\n");
        printf(" 4 - Listar \n");
        printf(" 5 - Sair do Programa\n");
        printf("================================\n\n");

		printf("--> ");
		op = 0;
		fflush(stdin);
        scanf("%d", &op);

        switch(op){
			case 1:
				aux=inicializarProcesso();
				int qtdProcessos = 0;
				do{
					system("cls");
				 	printf("Deseja importar os dados? 1-SIM 2-NÃO 3-CANCELAR \n");
				 	fflush(stdin);
				 	scanf("%d", &importar);

					switch(importar){
						case 1:
							linha=(char*)malloc(sizeof(char)*tamanho_linha);

		    				arq = fopen("Dados_teste - 50.txt","r");
		\
							if(arq==NULL){
		        				printf("Problema abertura de arquivo\n");
		    				} else {
		    					printf("\t\tImportando dados...\n");
								i=0;
								StartCounter();
						        while(fgets(linha,tamanho_linha,arq)!=NULL){
						            if (linha[0] == '\n' || linha[0] == ' '){
						                break;
						            }
						            //printf("\n%s",linha);
						            if(extrai_linha(linha,tamanho_linha,CORE_HASH)){
                                         qtdProcessos++;
                                    }
						        }
								tempoEmMilissegundo = GetCounter();
						        fclose(arq);
							}
							printf("\n\t\t=======================================\n");
                            printf("\t\t%d Processos importados com sucesso!\n\n",qtdProcessos);
							printf("\t\tTempo = %.7lf milissegundos\n", tempoEmMilissegundo);
							printf("\t\t=======================================\n\n\n\n\n");
							system("pause");
		                    system("cls");
						break;
						case 2:
							printf("Informe o processo: ");
							fflush(stdin);
		                	scanf("%ld", &aux->numProcesso);

							chave = geracaoChave(aux->numProcesso);

		                    if(existenciaProcesso(CORE_HASH,chave,aux->numProcesso) == 0){
								system("cls");
								printf("==============================\n\n");
								printf("Número do processo já existe!\n\n");
								printf("==============================\n\n");
								system("pause");
								system("cls");
							} else{

								system("cls");
								printf("============= Formulário do Processo Nº %d na chave %d =============\n",aux->numProcesso,chave);

								fflush(stdin);
								printf("\tInforme o nome do beneficiário: ");
				                scanf(" %[^\n]s",aux->nome_beneficiario);

								fflush(stdin);
				                printf("\tInforme o CPF do beneficiário -> (Formato: 000.000.000-00): ");
								scanf(" %[^\n]s",aux->cpf);

				                do{
				                	system("cls");
									printf("\tInforme a Espécie do benefício:\n");
									printf("\t1- Pensão por morte do trabalhador rural \n");
									printf("\t2- Pensão por morte do empregador rural\n");
									printf("\t3- Pensão por morte previdenciária\n");
									printf("\t4- Pensão por morte de ex-combatente\n");
									printf("\t5- Pensão por morte de servidor público federal com dupla aposentadoria\n");
									printf("\t6- Pensão por morte do Regime Geral (Decreto nº 20.465/31)\n");
									printf("\t7- Pensão por morte de ex-combatente marítimo (Lei nº 1.756/52)\n");
									printf("\t8- Pensão por morte (Extinto Plano Básico)\n");
									printf("\t9- Pensão por morte (Ex-SASSE)\n\n");

									printf("\t--> "); 	fflush(stdin); scanf("%d",&tipoEscolhido);

									switch(tipoEscolhido){
										case 1:
											strcpy(aux->especie_beneficio, "Pensão por morte do trabalhador rural");
										break;
										case 2:
											strcpy(aux->especie_beneficio, "Pensão por morte do empregador rural");
										break;
										case 3:
											strcpy(aux->especie_beneficio, "Pensão por morte previdenciária");
										break;
										case 4:
											strcpy(aux->especie_beneficio, "Pensão por morte de ex-combatente");
										break;
										case 5:
											strcpy(aux->especie_beneficio, "Pensão por morte de servidor público federal com dupla aposentadoria");
											break;
										case 6:
											strcpy(aux->especie_beneficio, "Pensão por morte do Regime Geral (Decreto nº 20.465/31)");
										break;
										case 7:
											strcpy(aux->especie_beneficio, "Pensão por morte de ex-combatente marítimo (Lei nº 1.756/52)");
										break;
										case 8:
											strcpy(aux->especie_beneficio, "Pensão por morte (Extinto Plano Básico)");
										break;
										case 9:
											strcpy(aux->especie_beneficio, "Pensão por morte (Ex-SASSE)");
										break;
										default:
											printf("\t Tipo da espécie do benefício inválida!\n");
											system("pause");
											tipoEscolhido = 0;
										break;
									}
				                } while(tipoEscolhido == 0);

									do{
										system("cls");
										printf("========Para continuar informe o tipo da Ação do Processo!========\n");
										printf("==================== 1-DEVOLUÇÃO     2-COBRANÇA ==================\n");
										printf("--> "); 	fflush(stdin); scanf("%d",&tipoAcao);

										switch(tipoAcao){
										case 1://DEVOLUÇÃO
											aux2 = (acaoDevolucao*)malloc(sizeof(acaoDevolucao));
											printf("============= Formulário de Devolução =============\n");
											fflush(stdin);
											printf("\tInforme o número da Ação:");
			                				scanf("%ld", &aux2->num_acao);

											fflush(stdin);
											printf("\tInforme o valor:");
			                				scanf("%f", &aux2->valor);
											do{
												system("cls");
												printf("\tInforme o tipo de pagamento: 1-BANCO  2-MOB\n"); int tipoPg;
												printf("\t--> "); 	fflush(stdin); scanf("%d",&tipoPg);

			                					switch(tipoPg){
				                					case 1:
				                						strcpy(aux2->tipoPagamento, "Banco");
													break;
													case 2:
														strcpy(aux2->tipoPagamento,"MOB");
													break;
													default:
														printf("opção inválida!\n");
														system("pause");
														tipoPg = 0;
													break;
												}
											} while(tipoPg == 0);
											do{
												system("cls");
				                				printf("\t Informe a Situação do pagamento: 1-Quitado 2-não-quitado  3-quitado-parcialmente\n");
				                				printf("\t--> "); 	fflush(stdin); scanf("%d", &situacao);

				                					switch(situacao){
					                					case 1:
					                						strcpy(aux2->tipo_situacao,"Quitado");
														break;
														case 2:
															strcpy(aux2->tipo_situacao,"Não-Quitado");
														break;
														case 3:
															strcpy(aux2->tipo_situacao,"Quitado-Parcialmente");
														break;
														default:
															printf("opção inválida!\n");
															system("pause");
															situacao = 0;
														break;
													}
											} while(situacao == 0);

			                				strcpy(aux2->tipo_acao, "Devolução");
											aux->AcaoDevolucao = aux2;
										break;
										case 2: //COBRANÇA
										aux3 = (acaoCobranca*)malloc(sizeof(acaoCobranca));
											printf("============= Formulário de Cobrança =============\n");

											fflush(stdin);
											printf("\tInforme o número da Ação:");
			                				scanf("%ld", &aux3->num_acao);

											fflush(stdin);
											printf("\tInforme o valor total:");
			                				scanf("%f", &aux3->valor);
											do{
												system("cls");
												fflush(stdin);
												printf("\tInforme a Situação do pagamento: 1-Quitado 2-não-quitado  3-quitado-parcialmente\n ");
				                				printf("\t--> ");scanf("%d", &situacao);

				                					switch(situacao){
					                					case 1:
					                						strcpy(aux3->tipo_situacao,"Quitado");
														break;
														case 2:
															strcpy(aux3->tipo_situacao,"Não-Quitado");
														break;
														case 3:
															strcpy(aux3->tipo_situacao, "Quitado-Parcialmente");
														break;
														default:
															printf("opção inválida!\n");
															system("pause");
															situacao = 0;
														break;
													}
											} while(situacao == 0);

											fflush(stdin);
											printf("\tInforme a atualização Monetária: ");
											scanf("%f",&aux3->atualizacaoMonetaria);

											fflush(stdin);
											printf("\tInforme a Multa: ");
											scanf("%f",&aux3->multa);

											fflush(stdin);
											printf("\tInforme o Juros: ");
											scanf("%f",&aux3->juros);

			               					strcpy(aux3->tipo_acao,"Cobrança");
											aux->AcaoCobranca = aux3;
										break;
										default:
											printf("Opção inválida!\n");
											system("pause");
											tipoAcao = 0;
										break;
										}
									} while(tipoAcao == 0);

								if(inserirHash(CORE_HASH,chave,aux)){
					                system("cls");
									printf("==============================\n");
									printf("\nProcesso %d inserido com sucesso!\n", aux->numProcesso);
									printf("\n==============================\n\n");
									system("pause");
									system("cls");
								} else{
									system("cls");
									printf("==============================\n");
								    printf("\nErro na inserção do processo!\n");
								    printf("\n==============================\n\n");
								    system("pause");
							    	system("cls");
								}
							}
						break;
						case 3:
							printf("Cancelando...\n");
							system("pause");
							system("cls");
						break;
						default:
							printf("Informe uma opção válida!\n\n");
							system("pause");
							importar = 0;
						break;
						}// FIM ELSE
				} while(importar == 0);

        	break;
         	case 2:
         		system("cls");
         		fflush(stdin);
                printf("Digite o número do processo: ");
                scanf("%ld", &processoBusca);

				tempoEmMilissegundo	= 0.0000000;

				StartCounter();
                chave = geracaoChave(processoBusca);
                buscaProcesso(CORE_HASH, chave, processoBusca);
                tempoEmMilissegundo = GetCounter();

				printf("\Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
				printf("===========================================================\n\n\n");
				system("pause");
				system("cls");
         	break;
         	case 3:
         		system("cls");
         		fflush(stdin);
				printf("Digite o número do processo que deseja excluir: ");
                scanf("%ld", &processoExcluir);

				tempoEmMilissegundo	= 0.0000000;
				StartCounter();
                chave = geracaoChave(processoExcluir);

                if(ExcluirProcesso(CORE_HASH, chave, processoExcluir)){
	                system("cls");
					printf("=================================\n");
					printf("\nProcesso %d excluído com sucesso!\n", processoExcluir);
					printf("\n=================================\n\n");
				} else{
					system("cls");
					printf("=======================================================\n");
				    printf("\nERRO ao excluir processo OU usuário CANCELOU exclusão!\n");
				    printf("\n=======================================================\n\n");
				}
				tempoEmMilissegundo = GetCounter();

				printf("\t\t==========================================\n");
				printf("\t\tTempo = %.7lf milissegundos\n", tempoEmMilissegundo);
				printf("\t\t==========================================\n\n\n\n\n");
				system("pause");
				system("cls");

         		break;
         	case 4:
         		system("cls");
				int cont;
				printf("=========== Dados CORE_HASH =================\n");
				printf("Quantidade de processos: %d\n", CORE_HASH->qtd);

				for(cont=0;cont<MAX;cont++){
					if(TAB_HASH[cont].dados->numProcesso == 0){

					} else{
						auxiliar = TAB_HASH[cont].dados;
							printf("\n=========================== %ld ===========================\n",cont);
						while(auxiliar != NULL && auxiliar->numProcesso != 0){
							printf("===========================================================\n");
							printf("Processo: %ld\n",auxiliar->numProcesso);
							printf("Nome Beneficiario: %s\n",auxiliar->nome_beneficiario);
							printf("CPF: %s\n",auxiliar->cpf);
							printf("Especie beneficio: %s\n",auxiliar->especie_beneficio);

							if(auxiliar->AcaoDevolucao != NULL){
								printf("Nº ação: %ld\n",auxiliar->AcaoDevolucao->num_acao);
								printf("Tipo Ação: %s\n",auxiliar->AcaoDevolucao->tipo_acao);
								printf("tipo_situacao: %s\n",auxiliar->AcaoDevolucao->tipo_situacao);
								printf("Valor: %.2f\n",auxiliar->AcaoDevolucao->valor);
								printf("Tipo Pagamento: %s\n",auxiliar->AcaoDevolucao->tipoPagamento);
							} else{
								printf("Nº ação: %ld\n",auxiliar->AcaoCobranca->num_acao);
								printf("Tipo Ação: %s\n",auxiliar->AcaoCobranca->tipo_acao);
								printf("tipo_situacao: %s\n",auxiliar->AcaoCobranca->tipo_situacao);
								printf("Valor: %.2f\n",auxiliar->AcaoCobranca->valor);
								printf("Atualizacao Monetaria: %.2f\n",auxiliar->AcaoCobranca->atualizacaoMonetaria);
								printf("Multa: %.2f\n",auxiliar->AcaoCobranca->multa);
								printf("Juros: %.2f\n",auxiliar->AcaoCobranca->juros);
							}
							printf("===========================================================\n");
							auxiliar = auxiliar->prox;
						}
					}
				}
				system("pause");
				system("cls");
         	break;
         	case 5:
         		system("cls");
         		printf("\n===========================\n");
         		printf("\n Saindo do programa!\n");
         		printf("\n===========================\n\n");
				system("pause");
			break;
			default:
         		system("cls");
         		printf("===========================\n");
         		printf("\n Opcao invalida!\n");
         		printf("\n===========================\n\n");
				system("pause");
				system("cls");
         	break;
		} //FIM SWITCH OP
	}while(op != 5); //MENU PRINCIPAL

	return 0;

} //MAIN
