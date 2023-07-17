#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

typedef struct
{
    char username[40];
    char password[40];
} Usuario;

void cadastro_usuario(Usuario *usuario)
{
    printf("Digite o nome de usu�rio: ");
    fgets(usuario->username, sizeof(usuario->username), stdin);
    usuario->username[strcspn(usuario->username, "\n")] = '\0';

    printf("Digite a senha: ");
    fgets(usuario->password, sizeof(usuario->password), stdin);
    usuario->password[strcspn(usuario->password, "\n")] = '\0';

    FILE *file;
    file = fopen("usuarios.txt", "a");

    if (file == NULL)
    {
        printf("O arquivo n�o foi encontrado ou n�o pode ser aberto.\n");
        return;
    }

    fprintf(file, "%s,", usuario->username);
    fprintf(file, "%s\n", usuario->password);
    fclose(file);

    printf("Usu�rio cadastrado com sucesso!\n");
}

int login(Usuario *usuario)
{
    char nome[40];
    char senha[40];

    printf("Usu�rio: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Senha: ");
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
        else
        {
            senha[i] = ch;
            printf("*");
            i++;
        }
    }
    senha[i] = '\0';

    FILE *file;
    file = fopen("usuarios.txt", "r");

    if (file == NULL)
    {
        printf("\nO arquivo n�o foi encontrado ou n�o pode ser aberto.\n");
        return 0;
    }

    char linha[80];
    while (fgets(linha, sizeof(linha), file) != NULL)
    {
        char *saved_username = strtok(linha, ",");
        char *saved_password = strtok(NULL, "\n");

        if (strcmp(saved_username, nome) == 0 && strcmp(saved_password, senha) == 0)
        {
            fclose(file);
            return 1; // Login bem-sucedido
        }
    }

    fclose(file);
    return 0; // Nome de usu�rio ou senha incorretos
}


void registro()
{
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];

    int cpfValido = 0; // Vari�vel para controlar a validade do CPF

    while (!cpfValido)
    {
        printf("Digite o CPF a ser cadastrado (somente n�meros): ");
        scanf("%s", cpf);
        getchar(); // Limpar o buffer de entrada

        // Valida��o do CPF
        cpfValido = 1; // Assumir que o CPF � v�lido
        for (int i = 0; cpf[i] != '\0'; i++)
        {
            if (!isdigit(cpf[i]))
            {
                printf("CPF inv�lido. Digite apenas n�meros.\n");
                cpfValido = 0; // CPF inv�lido, solicitar novamente
                break;
            }
        }
    }

    printf("Digite o nome que deseja cadastrar: ");
    scanf(" %39[^\n]", nome);
    getchar(); // Limpar o buffer de entrada

    printf("Digite o sobrenome que deseja cadastrar: ");
    fgets(sobrenome, sizeof(sobrenome), stdin);
    sobrenome[strcspn(sobrenome, "\n")] = '\0'; // Remover o caractere de nova linha

    printf("Digite o cargo desejado: ");
    fgets(cargo, sizeof(cargo), stdin);
    cargo[strcspn(cargo, "\n")] = '\0'; // Remover o caractere de nova linha

    // Criar o nome do arquivo usando o CPF
    char arquivo[50];
    sprintf(arquivo, "%s.txt", cpf);

    FILE *file;
    file = fopen(arquivo, "w");

    if (file == NULL)
    {
        printf("O arquivo n�o foi encontrado ou n�o pode ser aberto.\n");
        return;
    }

    fprintf(file, "CPF: %s\n", cpf);
    fprintf(file, "Nome: %s\n", nome);
    fprintf(file, "Sobrenome: %s\n", sobrenome);
    fprintf(file, "Cargo: %s\n", cargo);
    fclose(file);

    printf("Cadastro realizado com sucesso!\n");
    printf("Pressione Enter para sair.");
    getchar();
}

void consulta()
{
    setlocale(LC_ALL, "Portuguese");

    char cpf[40];

    printf("Digite o CPF para verificar: ");
    scanf("%s", cpf);
    getchar(); // Limpar o buffer de entrada

    // Criar o nome do arquivo usando o CPF
    char arquivo[50];
    sprintf(arquivo, "%s.txt", cpf);

    FILE *file;
    file = fopen(arquivo, "r");

    if (file == NULL)
    {
        printf("O arquivo n�o foi encontrado.\n");
        printf("Pressione Enter para sair.");
        getchar();
        return;
    }

    char linha[150];
    while (fgets(linha, sizeof(linha), file) != NULL)
    {
        printf("%s", linha);
    }

    fclose(file);

    printf("Pressione Enter para sair.");
    getchar();
}

void deleta()
{
    char cpf[40];

    printf("Digite o CPF do registro a ser exclu�do: ");
    scanf("%s", cpf);
    getchar(); // Limpar o buffer de entrada

    // Criar o nome do arquivo usando o CPF
    char arquivo[50];
    sprintf(arquivo, "%s.txt", cpf);

    FILE *file;
    file = fopen(arquivo, "r");

    if (file == NULL)
    {
        printf("O arquivo n�o foi encontrado.\n");
        printf("Pressione Enter para sair.");
        getchar();
        return;
    }

    fclose(file);

    int removido = remove(arquivo);

    if (removido == 0)
    {
        printf("O registro foi exclu�do com sucesso.\n");
    }
    else
    {
        printf("N�o foi poss�vel excluir o registro.\n");
    }

    printf("Pressione Enter para sair.");
    getchar();
}

void sair()
{
    printf("Obrigade, volte sempre!\n");
    exit(0);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao = 0;
    int laco = 1;
    Usuario usuario;

    printf("### Cart�rio da EBAC ###\n\n");

    printf("Deseja cadastrar um novo usu�rio? (S/N): ");
    char resposta;
    do
    {
        scanf(" %c", &resposta);
        getchar();
        if (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n')
        {
            printf("Resposta inv�lida. Digite S ou N: ");
        }
    } while (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n');

    if (resposta == 'S' || resposta == 's')
    {
        cadastro_usuario(&usuario);
    }

    printf("Fa�a o login:\n");

    while (!login(&usuario))
    {
        printf("Falha no login. Tente novamente.\n");
    }

    for (laco = 1; laco == 1;)
    {
        system("cls");

        setlocale(LC_ALL, "Portuguese");

        printf("### Cart�rio da EBAC ###\n\n");
        printf("Escolha a op��o desejada do menu:\n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n");
        printf("\t4 - Sair do sistema\n");
        printf("Op��o: ");

        scanf("%d", &opcao);
        getchar(); // Limpar o buffer de entrada

        system("cls");

        switch (opcao)
        {
        case 1:
            printf("Voc� escolheu registrar um nome!\n");
            registro();
            break;

        case 2:
            printf("Voc� escolheu consultar nomes!\n");
            consulta();
            break;

        case 3:
            printf("Voc� escolheu deletar nomes!\n");
            deleta();
            break;

        case 4:
            printf("Voc� escolheu Sair do sistema.\n");
            sair();
            break;

        default:
            printf("Essa op��o n�o est� dispon�vel.\n");
            break;
        }

        printf("Pressione Enter para continuar.");
        getchar();
    }

    printf("Pressione Enter para sair.");
    getchar();
    return 0;
}
