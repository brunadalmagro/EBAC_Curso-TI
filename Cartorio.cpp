#include <stdio.h>	//biblioteca de comunicação de usuário
#include <stdlib.h> // biblioteca alocar espaços na memória
#include <locale.h> // biblioteca de alocações de texto por região
#include <string.h> // Biblioteca responsável por cuidar das Strings

int registro() // funcão registro
{
	char arquivo[40];
	char cpf[40];
	char nome[40];
	char sobrenome[40];
	char cargo[40];

	printf("Digite o CPF a ser cadastrado: ");
	scanf("%s", cpf);

	strcpy(arquivo, "BD.txt"); // copia valor das strings

	FILE *file; // criando arquivo
	file = fopen(arquivo, "a");
	fprintf(file, cpf); // f(file) printf - salva o valor da variável
	fclose(file);		// fecha o arquivo

	file = fopen(arquivo, "a"); // A "AUTER" ATUALIZAR
	fprintf(file, ",");
	fclose(file);

	printf("Digite o nome que deseja cadastrar: ");
	scanf("%s", nome);

	file = fopen(arquivo, "a");
	fprintf(file, nome);
	fclose(file);

	file = fopen(arquivo, "a");
	fprintf(file, ",");
	fclose(file);

	printf("Digite o sobrenome que deseja cadastrar: ");
	scanf("%s", sobrenome);

	file = fopen(arquivo, "a");
	fprintf(file, sobrenome);
	fclose(file);

	file = fopen(arquivo, "a");
	fprintf(file, ",");
	fclose(file);

	printf("Digite o cargo desejado: ");
	scanf("%s", cargo);

	file = fopen(arquivo, "a");
	fprintf(file, cargo);
	fprintf(file, "\n");
	fclose(file);

	system("pause");
}

int consulta()
{
	setlocale(LC_ALL, "Portuguese"); // Definindo linguagen

	char conteudo[50]; // armazena cada linha do arquivo
	char cpf[40];	   // ponteiros para cada campo do registro

	printf("Digite o CPF completo para verificar: ");
	scanf("%s", cpf);

	FILE *file;
	file = fopen("BD.txt", "r");

	if (file == NULL) // verifica se o arquivo existe
	{
		printf("O arquivo não foi encontrado.\n");
	}

	while (fgets != NULL) // Lê uma linha do arquivo até o final
	{
		printf("\nEssas são as informações do usuário");
		printf("%s", conteudo, cpf);
		printf("\n\n");

		system("pause");
	}
}

void deleta()
{
	char nome[40];
	char sobrenome[40];
	char arquivo[40];
	char linha[150];
	char cpf[40];
	int encontrado = 0; // variável para indicar se o registro foi encontrado

	printf("Digite o CPF do registro a ser excluído: ");
	scanf("%s", cpf);

	system("cls"); // limpar a tela

	FILE *file;
	file = fopen(arquivo, "r");
	if (file == NULL)
	{
		printf("O arquivo não foi encontrado.\n");
		return;
	}

	fclose(file);

	{
		remove(arquivo);			 // remove o arquivo original
		rename("temp.txt", arquivo); // renomeia o arquivo temporário para o nome original
		printf("O registro foi excluído com sucesso.\n");
	}
}

void sair()
{
	printf("Saindo do sistema...\n");
	exit(0); // Encerra o programa
}

int main()
{
	int opcao = 0; // Definindo variáveis
	int laco = 1;

	for (laco = 1; laco = 1;)
	{

		system("cls");

		setlocale(LC_ALL, "Portuguese"); // Definindo linguagens

		printf("### Cartório da EBAC ###\n\n"); // Início do menu
		printf("Escolha a opção desejada do menu:\n\n");
		printf("\t1 - Registrar nomes\n");
		printf("\t2 - Consultar nomes\n");
		printf("\t3 - Deletar nomes\n");
		printf("\t4 - Sair\n");
		printf("Opção: "); // Fim do menu

		scanf("%d", &opcao); // Armazenamento da escolha do usuário

		system("cls");

		switch (opcao) //Chama as funões desejadas
		{
		case 1:
			printf("Voce escolheu registro de nome!\n");
			registro();
			system("pause");
			break;

		case 2:
			printf("Você escolheu consultar os nomes!\n");
			consulta();
			system("pause");
			break;

		case 3:
			printf("Você escolheu deletar nomes!\n");
			deleta();
			system("pause");
			break;

		case 4:
			sair(); 
			break;

		default:
			printf("Essa opçãoo não está disponível.\n");
			system("pause");
			break;

		} // Fim da seleção
	}
}
