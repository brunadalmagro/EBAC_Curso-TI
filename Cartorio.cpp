#include <stdio.h> // biblioteca de comunicação do usuário
#include <stdlib.h> // biblioteca para alocação de memória
#include <locale.h> // biblioteca para alocação de texto por região
#include <string.h> // biblioteca responsável por manipular strings
#include <ctype.h> // biblioteca resposável pela validação de caracteres de entrada

void registro()
{
    char arquivo[40];
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];

    printf("Digite o CPF a ser cadastrado (somente números): ");
    scanf("%s", cpf);

    // Validação do CPF
    for (int i = 0; cpf[i] != '\0'; i++)
    {
        if (!isdigit(cpf[i]))
        {
            printf("CPF inválido. Digite apenas números.\n");
            getchar();
            return;
        }
    }

    strcpy(arquivo, "BD.txt");

    FILE *file;
    file = fopen(arquivo, "a");
    fprintf(file, "%s", cpf);
    fclose(file);

    file = fopen(arquivo, "a");
    fprintf(file, ",");
    fclose(file);

    printf("Digite o nome que deseja cadastrar: ");
    scanf("%s", nome);

    file = fopen(arquivo, "a");
    fprintf(file, "%s", nome);
    fclose(file);

    file = fopen(arquivo, "a");
    fprintf(file, ",");
    fclose(file);

    printf("Digite o sobrenome que deseja cadastrar: ");
    scanf("%s", sobrenome);

    file = fopen(arquivo, "a");
    fprintf(file, "%s", sobrenome);
    fclose(file);

    file = fopen(arquivo, "a");
    fprintf(file, ",");
    fclose(file);

    printf("Digite o cargo desejado: ");
    scanf("%s", cargo);

    file = fopen(arquivo, "a");
    fprintf(file, "%s", cargo);
    fprintf(file, "\n");
    fclose(file);

    printf("Pressione Enter para sair.");
    getchar();
}


void consulta()
{
    setlocale(LC_ALL, "Portuguese"); // Definindo idioma

    char cpf[40]; // CPF a ser consultado
    int encontrado = 0; // Variável para indicar se o usuário foi encontrado

    printf("Digite o CPF ou nome completo para verificar: ");
    scanf("%s", cpf);

    FILE *file;
    file = fopen("BD.txt", "r");

    if (file == NULL) // verifica se o arquivo existe
    {
        printf("O arquivo não foi encontrado.\n");
        return;
    }

    char linha[150];
    while (fgets(linha, 150, file) != NULL)
    {
        if (strstr(linha, cpf) != NULL)
        {
            printf("\nEssas são as informações do usuário: %s\n\n", linha);
            encontrado = 1;
            break;
        }
    }

    fclose(file);

    if (!encontrado)
    {
        printf("Usuário não cadastrado.\n");
    }

    printf("Pressione Enter para sair.");
    getchar();
}

void deleta()
{
    char arquivo[40];
    char cpf[40];
    int encontrado = 0; // variável para indicar se o registro foi encontrado

    printf("Digite o CPF do registro a ser excluído: ");
    scanf("%s", cpf);

    strcpy(arquivo, "BD.txt");

    FILE *file, *temp;
    file = fopen(arquivo, "r");
    temp = fopen("temp.txt", "w");

    if (file == NULL)
    {
        printf("O arquivo não foi encontrado.\n");
        return;
    }

    char linha[150];
    while (fgets(linha, 150, file) != NULL)
    {
        if (strstr(linha, cpf) == NULL)
        {
            fputs(linha, temp);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(file);
    fclose(temp);

    if (encontrado == 1)
    {
        remove(arquivo); // remove o arquivo original
        rename("temp.txt", arquivo); // renomeia o arquivo temporário para o nome original
        printf("O registro foi excluído com sucesso.\n");
    }
    else
    {
        remove("temp.txt"); // remove o arquivo temporário
        printf("A exclusão foi cancelada pelo usuário.\n");
    }

    printf("Pressione Enter para sair.");
    getchar();
}

void sair()
{
    printf("Você escolheu Sair do sistema. \n");
    exit(0);
}

int main()
{
    int opcao = 0; // Definindo variáveis
    int laco = 1;

    for (laco = 1; laco == 1;)
    {
        system("cls");

        setlocale(LC_ALL, "Portuguese"); // Definindo idioma

        printf("### Cartório da EBAC ###\n\n"); // Início do menu
        printf("Escolha a opção desejada do menu:\n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n");
        printf("\t4 - Sair do sistema\n");
        printf("Opção: "); // Fim do menu

        scanf("%d", &opcao); // Armazenamento da escolha do usuário

        system("cls");

        switch (opcao)
        {
        case 1:
            printf("Você escolheu registrar um nome!\n");
            registro();
            getchar();
            break;

        case 2:
            printf("Você escolheu consultar nomes!\n");
            consulta();
            getchar();
            break;

        case 3:
            printf("Você escolheu deletar nomes!\n");
            deleta();
            getchar();
            break;

        case 4:
            printf("Obrigad@, volte sempre!\n");
            sair();
            break;

        default:
            printf("Essa opção não está disponível.\n");
            getchar();
            break;
        } // Fim da seleção
    }

    printf("Pressione Enter para sair.");
    getchar();
    return 0;

}
