/* prototipo.h armazena a estrutura e os prototipos das fun��es*/
typedef struct hash{ //tabela HASH
	int qtdColisao; //quantidade de colis�es
	struct processo *dados; //endere�o
}hash;

typedef struct CORE{ //strutura que aponta para a tabela hash
	int qtd; //quantidade de processos
	struct hash *endereco;
}CORE;

typedef struct processo{
	long numProcesso;                           //N�mero do Processo
    char nome_beneficiario[100];       //Nome do Benefici�rio
	char cpf[100];                      //CPF do Benefici�rio 000.000.000.00
	char especie_beneficio[100];        //Esp�cie do benef�cio (faremos um switch case para escolha)     	struct processo *ant;
	struct processo *prox;                      //Ponteiro para o pr�ximo processo da lista
	struct processo *ant;                       //Ponteiro para o processo anterior da lista
	struct acaoDevolucao *AcaoDevolucao;      //(ser� um ponteiro, guardando o endere�o da a��o referente ao processo)
	struct acaoCobranca  *AcaoCobranca;

}processo;

typedef struct acaoDevolucao{
	long num_acao;             //N�mero da A��o
	char tipo_acao[100];          //Tipo A��o (Devolu��o ou Cobran�a)
	char tipo_situacao[100];      //Situa��o: Quitado, n�o-quitado, quitado-parcialmente
	float valor;
	char tipoPagamento[100];     //Procedimento do pagamento (Banco ou MOB)
}acaoDevolucao;

typedef struct acaoCobranca{
	long num_acao;                //N�mero da A��o
	char tipo_acao[100];          	//Tipo A��o (Devolu��o ou Cobran�a)
	char tipo_situacao[100];      	//Situa��o: Quitado, n�o-quitado, quitado-parcialmente
	float valor;					//Valor total
	float atualizacaoMonetaria;     //Valor da atualiza��o Monet�ria
	float multa;					//Valor da Multa
	float juros; 					//Valor do juros
}acaoCobranca;

CORE* inicializarCORE();
processo * inicializarProcesso();
long geracaoChave(long chave);
int inserirHash(CORE* CORE_HASH, int chave,processo * novoProcesso);
void buscaProcesso(CORE* CORE_HASH, long chave, long numprocesso);
int ExcluirProcesso(CORE* CORE_HASH, long chave, long numprocesso);
int existenciaProcesso(CORE* CORE_HASH, long chave, long processo);
int extrai_linha(char * linha,int tamanho_linha,CORE * CORE_HASH);
void StartCounter();
double GetCounter();
