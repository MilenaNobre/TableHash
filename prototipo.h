/* prototipo.h armazena a estrutura e os prototipos das funções*/
typedef struct hash{ //tabela HASH
	int qtdColisao; //quantidade de colisões
	struct processo *dados; //endereço
}hash;

typedef struct CORE{ //strutura que aponta para a tabela hash
	int qtd; //quantidade de processos
	struct hash *endereco;
}CORE;

typedef struct processo{
	long numProcesso;                           //Número do Processo
    char nome_beneficiario[100];       //Nome do Beneficiário
	char cpf[100];                      //CPF do Beneficiário 000.000.000.00
	char especie_beneficio[100];        //Espécie do benefício (faremos um switch case para escolha)     	struct processo *ant;
	struct processo *prox;                      //Ponteiro para o próximo processo da lista
	struct processo *ant;                       //Ponteiro para o processo anterior da lista
	struct acaoDevolucao *AcaoDevolucao;      //(será um ponteiro, guardando o endereço da ação referente ao processo)
	struct acaoCobranca  *AcaoCobranca;

}processo;

typedef struct acaoDevolucao{
	long num_acao;             //Número da Ação
	char tipo_acao[100];          //Tipo Ação (Devolução ou Cobrança)
	char tipo_situacao[100];      //Situação: Quitado, não-quitado, quitado-parcialmente
	float valor;
	char tipoPagamento[100];     //Procedimento do pagamento (Banco ou MOB)
}acaoDevolucao;

typedef struct acaoCobranca{
	long num_acao;                //Número da Ação
	char tipo_acao[100];          	//Tipo Ação (Devolução ou Cobrança)
	char tipo_situacao[100];      	//Situação: Quitado, não-quitado, quitado-parcialmente
	float valor;					//Valor total
	float atualizacaoMonetaria;     //Valor da atualização Monetária
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
