#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct dados{ // estrutura dos dados pessoais

    float salario;
    float despesa;
    float credito;
    char nome[50];
    char cpf[15];
    char identidade[10];

};

void crasa(){ //Cabeçalho do sistema
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

    printf("   ______            ____  ___   _____ ___ \n");
    printf("  / ____/           / __ \\/   | / ___//   |\n");
    printf(" / /      ______   / /_/ / /| | \\__ \\/ /| |\n");
    printf("/ /___   /_____/  / _, _/ ___ |___/ / ___ |\n");
    printf("\\____/           /_/ |_/_/  |_|____/_/  |_|\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);


}

void limpar(){ //Limpar tela
    system("cls");
}
void cabecalho(){ //cabeçalho de boas vindas
    limpar();

    printf("+--------------------------------------------------------+\n");
    printf("+                                                        +\n");
    printf("+        Bem-Vindo a sua analise de credito!             +\n");
    printf("+                                                        +\n");
    printf("+--------------------------------------------------------+\n");
}
void cabecalho_dados(){ //cabeçalho para a solicitação de dados

    printf("+--------------------------------------------------------+\n");
    printf("+                                                        +\n");
    printf("+           Preencha o que se pede a seguir!             +\n");
    printf("+                                                        +\n");
    printf("+--------------------------------------------------------+\n");
}
void dados_pessoais(){ //cabeçalho para a coleta de dados

    printf("+--------------------------------------------------------+\n");
    printf("+                                                        +\n");
    printf("+             Insira os seus dados abaixo!               +\n");
    printf("+                                                        +\n");
    printf("+--------------------------------------------------------+\n");
}


void dados_financa() { //cabeçalho para a financeira

    printf("+--------------------------------------------------------+\n");
    printf("+                                                        +\n");
    printf("+              Insira o seu os seus dados                +\n");
    printf("+                 financeiros abaixo!                    +\n");
    printf("+                                                        +\n");
    printf("+--------------------------------------------------------+\n");
}

void analise_credito() { //cabeçalho para o analise de credito

    printf("+--------------------------------------------------------+\n");
    printf("+                                                        +\n");
    printf("+                 Analise de Credito!                    +\n");
    printf("+                                                        +\n");
    printf("+--------------------------------------------------------+\n");
}
void imprimirPositivo(struct dados* pessoa, int tamanho){

    for (int i = 0; i < tamanho; i++){
        if (pessoa[i].credito > 0) {
            printf("Nome: %s\n", pessoa[i].nome);
            printf("Valor do Credito: %.2f\n", pessoa[i].credito);
            printf("\n");
        }
    }
}

void imprimirNegativo(struct dados* pessoa, int tamanho){ //Imprimir as pessoas com crédito negativo dentro do arquivo

    for (int i = 0; i < tamanho; i++){
        if (pessoa[i].credito <= 0) {
            printf("Nome: %s\n", pessoa[i].nome);
            printf("Valor do Credito: %.2f\n", pessoa[i].credito);
            // imprimir outros campos, se necessário
            printf("\n");
        }
    }
}

void salvarCSV(struct dados pessoa[], int tamanho){ //Abrir o arquivo

    FILE* arquivo = fopen("Dados.csv", "w");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    //Escrever os dados no arquivo
    fprintf(arquivo, "Nome, CPF, Identidade, Salario, Despesa, Credito\n");

    int i;
    for(i = 0; i < tamanho; i++){
        fprintf(arquivo, "%s, %s, %s, %.2f, %.2f, %2.f\n", pessoa[i].nome, pessoa[i].cpf, pessoa[i].identidade, pessoa[i].salario, pessoa[i].despesa, pessoa[i].credito);
    }

    //Fechar arquivo
    fclose(arquivo);

    printf("Arquivo CSV criado com sucsso.\n");
}

void lerCSV(struct dados pessoa[], int* tamanho){//Ler dados do arquivo

    FILE *arquivo = fopen("Dados.csv", "r+");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    char linha[200];
    *tamanho = 0;

    //Ignora a primeira linha, pois é o cabeçalho]

    fgets(linha, 200, arquivo);

    while(fgets(linha, 200, arquivo) != NULL){
        char *token = strtok(linha, ",");

        if(token == NULL){
            continue;
        }

        strcpy(pessoa[*tamanho].nome, token);
        token = strtok(NULL, ",");

        if(token == NULL){
            continue;
        }

        strcpy(pessoa[*tamanho].cpf, token);

        token = strtok(NULL, ",");

        if(token == NULL){
            continue;
        }

        strcpy(pessoa[*tamanho].identidade, token);
        token = strtok(NULL, ",");

        if(token == NULL){
            continue;
        }

        pessoa[*tamanho].salario = atof(token);

        token = strtok(NULL, ",");

        if(token == NULL){
            continue;
        }

        pessoa[*tamanho].despesa = atof(token);

        token = strtok(NULL, ",");

        if(token == NULL){
            continue;
        }

        pessoa[*tamanho].credito = atof(token);

        (*tamanho)++;
    }
    fclose(arquivo);
}

void imprimirDados(const struct dados pessoa[], int tamanho){//Imprimi na tela todos os dados do arquivo
    int i;

    for (i = 0; i < tamanho; i++) {
            printf("Nome: %s\n", pessoa[i].nome);
            printf("CPF: %s\n", pessoa[i].cpf);
            printf("IDENTIDADE: %s\n", pessoa[i].identidade);
            printf("SALARIO: %.2f\n", pessoa[i].salario);
            printf("DESPESAS: %.2f\n", pessoa[i].despesa);
            printf("CREDITO: %.2f\n\n", pessoa[i].credito);

    }

}

float analise_pronta(float salario, float despesa, float credito){ //função de analise de credito

    credito = salario - despesa;

    if(credito <= 0){
        printf("Desculpe, mas sua analise nao foi aprovada.\n");
    }
    else if(credito > 0){
        despesa = despesa * 2;
        if(salario > despesa){
            printf("Parabens! Sua analise de credito foi aprovada.\n");
            printf("Voce consegue um credito no valor de ate %.2f.\n", credito * 2);
        }
        if(salario <= despesa){
            printf("Parabens! Sua analise de credito foi aprovada. \n");
            printf("Voce consegue um credito no valor de ate %.2f.\n", credito);
        }
    }

    return credito;
}
void alterarDados(struct dados* pessoa, int tamanho) {
    int i;
    int num1, num2;
    char cpfPesquisado[15];

    printf("Insira o CPF do titular: ");
    fgets(cpfPesquisado, sizeof(cpfPesquisado), stdin);
    cpfPesquisado[strcspn(cpfPesquisado, "\n")] = '\0';

    for (i = 0; i < tamanho; i++) {
        num1 = atoi(cpfPesquisado);
        num2 = atoi(pessoa[i].cpf);

        if (num1 == num2) {
            printf("Corrigir Nome: ");
            fgets(pessoa[i].nome, sizeof(pessoa[i].nome), stdin);
            pessoa[i].nome[strcspn(pessoa[i].nome, "\n")] = '\0';

            /*printf("Corrigir CPF: ");
            fgets(pessoa[i].cpf, sizeof(pessoa[i].cpf), stdin);
            pessoa[i].cpf[strcspn(pessoa[i].cpf, "\n")] = '\0';*/
            const char *nomeArquivo = "Dados.csv";

                int num1,num2,repeat=0;
                do{
                    printf("Insira o seu CPF: \n");
                    fgets(pessoa[tamanho].cpf, sizeof(pessoa[tamanho].cpf), stdin);

                    int vazio = verificarArquivoVazio(nomeArquivo);

                     if (vazio == -1) {
                        printf("\nPor favor salve esses dados pelo menos 1 vez para funcionar corretamente\n");
                        repeat = 1;  // Sai do loop se ocorreu um erro ao abrir o arquivo
                        break;
                    }

                    for(int i=0;i<tamanho;i++){
                        num1 = atoi (pessoa[tamanho].cpf);
                        num2 = atoi (pessoa[i].cpf);
                        if (vazio == -1) {
                        repeat=0;
                        break;
                    }
                        if(num1==num2){
                            printf("\no CPF ja existe,digite outro.\n");
                            repeat=0;
                            break;
                        }
                        else{
                            repeat=1;
                        }

                    }

                }while(repeat==0);
            printf("Corrigir Identidade: ");
            fgets(pessoa[i].identidade, sizeof(pessoa[i].identidade), stdin);
            pessoa[i].identidade[strcspn(pessoa[i].identidade, "\n")] = '\0';

            printf("Corrigir Salario: ");
            scanf("%f", &pessoa[i].salario);
            getchar(); // Limpar o buffer de entrada

            printf("Corrigir Despesas: ");
            scanf("%f", &pessoa[i].despesa);
            getchar(); // Limpar o buffer de entrada


            pessoa[i].credito = analise_pronta(pessoa[i].salario, pessoa[i].despesa, pessoa[i].credito);

            printf("Dados alterados com sucesso!\n");
            return;
        }
    }

    printf("CPF nao encontrado.\n\n");
}
int verificarArquivoVazio(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {

        return -1;
    }

    fseek(arquivo, 0, SEEK_END); // Move o cursor para o final do arquivo
    long tamanho = ftell(arquivo); // Obtém a posição atual do cursor
    fclose(arquivo);

    if (tamanho == 0) {
        return 1;  // Arquivo está vazio
    }

    return 0;  // Arquivo não está vazio
}

int main(){

    struct dados pessoa[100]; //Chamada da estrutura
    const char *nomeArquivo = "Dados.csv";

    cabecalho();
    cabecalho_dados();
    printf("TECLE ENTER PARA CONTINUAR:\n");
    while (getchar() != '\n');

    limpar();

    int op, op2;
    int tamanho = 0;
    lerCSV(pessoa, &tamanho); //Chamado da função da leitura do arquivo

    do {

        printf("\n\n");
        crasa();

        printf("\nEscolha:\n\n 1 - Efetuar Analise\n 2 - Listar Cadastros\n 3 - Ler os Dados\n 4 - Corrigir Dados\n 5 - Imprimir creditos positivos\n 6 - Imprimir creditos negativos\n 7 - Sair\n\n");
        printf("Selecione a opcao que deseja: ");
        scanf("%d", &op2);
        fflush(stdin);
        limpar();

        switch (op2) {//Menu de seleção do sistema de análise

            case 1:


                crasa();
                dados_pessoais();
                printf("Insira o seu nome: \n");
                fgets(pessoa[tamanho].nome, sizeof(pessoa[tamanho].nome), stdin);


                size_t newlinePos = strcspn(pessoa[tamanho].nome, "\n");//retira a quebra de linha do final da string
                if (pessoa[tamanho].nome[newlinePos] == '\n') {
                    pessoa[tamanho].nome[newlinePos] = '\0';
                }

                const char *nomeArquivo = "Dados.csv";

                int num1,num2,repeat=0;
                do{
                    printf("Insira o seu CPF: \n");
                    fgets(pessoa[tamanho].cpf, sizeof(pessoa[tamanho].cpf), stdin);

                    int vazio = verificarArquivoVazio(nomeArquivo);

                     if (vazio == -1) {
                        printf("\nPor favor salve esses dados pelo menos 1 vez para funcionar corretamente\n");
                        repeat = 1;  // Sai do loop se ocorreu um erro ao abrir o arquivo
                        break;
                    }

                    for(int i=0;i<tamanho;i++){
                        num1 = atoi (pessoa[tamanho].cpf);
                        num2 = atoi (pessoa[i].cpf);
                        if (vazio == -1) {
                        repeat=0;
                        break;
                    }
                        if(num1==num2){
                            printf("\no CPF ja existe,digite outro.\n");
                            repeat=0;
                            break;
                        }
                        else{
                            repeat=1;
                        }

                    }

                }while(repeat==0);
                newlinePos = strcspn(pessoa[tamanho].cpf, "\n");
                if (pessoa[tamanho].cpf[newlinePos] == '\n') {
                    pessoa[tamanho].cpf[newlinePos] = '\0';
                }
                newlinePos = strcspn(pessoa[tamanho].cpf, "\n");
                if (pessoa[tamanho].cpf[newlinePos] == '\n') {
                    pessoa[tamanho].cpf[newlinePos] = '\0';
                }



                printf("Insira a sua identidade: \n");
                fgets(pessoa[tamanho].identidade, sizeof(pessoa[tamanho].identidade), stdin);

                newlinePos = strcspn(pessoa[tamanho].identidade, "\n");
                if (pessoa[tamanho].identidade[newlinePos] == '\n') {
                    pessoa[tamanho].identidade[newlinePos] = '\0';
                }


                printf("TECLE ENTER PARA CONTINUAR:\n");
                while (getchar() != '\n');

                limpar();

                crasa();
                analise_credito();

                printf("TECLE ENTER PARA CONTINUAR:\n");
                while (getchar() != '\n'); //Linha para ir para a proxima linha apenas apos pressionar o enter
                limpar();

                crasa();
                dados_financa();

                printf("Insira o seu salario abaixo: \n");
                scanf("%f", &pessoa[tamanho].salario);
                fflush(stdin);

                printf("Insira as suas despesas mensais: \n");
                scanf("%f", &pessoa[tamanho].despesa);
                fflush(stdin);


                printf("Se tiver interesse em fazer uma analise de credito, selecione [0] para NAO e [1] para SIM: \n");
                scanf("%d", &op);
                fflush(stdin);
                limpar();


                while (op != 1 && op != 0) {//Loop da seleção para selecionar a analise

                    switch (op) {

                        case 0:
                            printf("Que bom!! Espero ter ajudado!");

                            break;

                        case 1:

                            limpar();
                            crasa();
                            analise_credito();
                            printf("Otimo, vamos para a ánalise\n");

                            while (getchar() != '\n');

                            limpar();

                            crasa();
                            analise_credito();

                            pessoa[tamanho].credito = analise_pronta(pessoa[tamanho].salario, pessoa[tamanho].despesa, pessoa[tamanho].credito);

                            break;

                        default:
                            printf("Insira o valor valido. [0] NAO [1] SIM. \n");
                            scanf("%d", &op);

                            break;


                    }
                }

                if (op == 1) {//Chama a função do calculo do crédito
                    crasa();
                    pessoa[tamanho].credito = analise_pronta(pessoa[tamanho].salario, pessoa[tamanho].despesa, pessoa[tamanho].credito);

                    if (pessoa[tamanho].credito <= 0) {

                        printf("O usuario %s esta com score negativo.\n", pessoa[tamanho].nome);

                        tamanho++;

                        printf("TECLE ENTER PARA CONTINUAR:\n");
                        while (getchar() != '\n');

                        limpar();

                        break;

                    } else {

                        printf("O usuario %s esta com score positivo.\n", pessoa[tamanho].nome);

                        tamanho++;

                        printf("TECLE ENTER PARA CONTINUAR:\n");
                        while (getchar() != '\n');

                        limpar();

                        break;
                    }
                }

                if (op == 0) {//Caso nao queira a analise, o credito fica zero
                    printf("Que bom!! Espero ter ajudado!\n");

                    pessoa[tamanho].credito = 0;

                    tamanho++;


                    printf("TECLE ENTER PARA CONTINUAR:\n");
                    while (getchar() != '\n');

                    limpar();
                    break;
                }

                break;

            case 2: //Chama a função para imprimir os dados inseridos

                limpar();
                imprimirDados(pessoa, tamanho);
                printf("\n\n");
                printf("TECLE ENTER PARA CONTINUAR:\n");
                while (getchar() != '\n');
                limpar();

                break;

            case 3://Exerce o mesmo do case anterior, mas com o intuito somente para abertura do arquivo

                imprimirDados(pessoa,tamanho);

                printf("TECLE ENTER PARA CONTINUAR:\n");
                while (getchar() != '\n');
                limpar();

                break;

            case 4: //Chama a função para alterar os dados do arquivo

                alterarDados(pessoa, tamanho);
                system("pause");
                printf("TECLE ENTER PARA CONTINUAR:\n");
                while (getchar() != '\n');
                limpar();

                break;

            case 5: //Imprimi apenas as pessoas com credito positivo

                imprimirPositivo(pessoa, tamanho);

                printf("TECLE ENTER PARA CONTINUAR:\n");
                while (getchar() != '\n');
                limpar();

                break;

            case 6://Imprimi apenas as pessoas com credito negativo ou que nao fizeram a analise

                imprimirNegativo(pessoa, tamanho);
                printf("TECLE ENTER PARA CONTINUAR:\n");
                while (getchar() != '\n');
                limpar();

                break;

            case 7://finaliza o sistema e cria o arquivo e grava os dados dentro dele

                limpar();
                salvarCSV(pessoa, tamanho);
                printf("\n\n");
                printf("TECLE ENTER PARA CONTINUAR:\n");
                while (getchar() != '\n');
                limpar();

                break;
        }

    }while(op2 != 7);

    return 0;
}
