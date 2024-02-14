#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#include <conio.h>

#define ARQ "imobi.in"
#define ID_FILE "id.in"

typedef struct {
    int id;
    char endereco[101];
    char aluguel[15];
    char compra[15];
    int numero;
    double preco;
    int cep;
    int contador;
} Imoveis;

typedef struct {
    long long int cpf;
    char nome[101];
    char endereco[101];
    char email[101];
    char tel[12];  
} Cliente;

typedef struct {
    char login[15];
    char senha[15];
} Usuario;

void TirarEspaco(char texto[]) {
     int i;
     for (i=0;i<strlen(texto);i++)
     if (texto[i]==' ')
     texto[i]='+';
}

void ColocarEspaco(char texto[]) {
     int i;
     for (i=0;i<strlen(texto);i++)
     if (texto[i]=='+')
     texto[i]=' ';
}

void limparTela() {
    system("cls");
}

void colocaTraco() {
    printf("----------------------------------- \n----------------------------------- \n");
}

void salvarUsuario(Usuario* usuario) {
    FILE* user = fopen("usuarios.in", "a");
    if (user == NULL) {
        printf("N�o foi poss�vel abrir o arquivo.\n");
        return;
    }
    fprintf(user, "%s %s\n", usuario->login, usuario->senha);
    fclose(user);
}

int verificarUsuario(Usuario* usuario) {
    FILE* user = fopen("usuarios.in", "r");
    if (user == NULL) {
        printf("N�o foi poss�vel abrir o arquivo.\n");
        return 0;
    }
    Usuario usuarioArquivo;
    while (fscanf(user, "%s %s\n", usuarioArquivo.login, usuarioArquivo.senha) != EOF) {
        if (strcmp(usuario->login, usuarioArquivo.login) == 0 && strcmp(usuario->senha, usuarioArquivo.senha) == 0) {
            fclose(user);
            return 1;
        }
    }
    fclose(user);
    return 0;
}

void excluirUsuario(Usuario* usuario) {
    FILE* arquivo = fopen("usuarios.in", "r");
    FILE* temp = fopen("temp.in", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("N�o foi poss�vel abrir o arquivo.\n");
        return;
    }
    Usuario usuarioArquivo;
    while (fscanf(arquivo, "%s %s\n", usuarioArquivo.login, usuarioArquivo.senha) != EOF) {
        if (strcmp(usuario->login, usuarioArquivo.login) != 0 || strcmp(usuario->senha, usuarioArquivo.senha) != 0) {
            fprintf(temp, "%s %s\n", usuarioArquivo.login, usuarioArquivo.senha);
        }
    }
    fclose(arquivo);
    fclose(temp);
    remove("usuarios.in");
    rename("temp.in", "usuarios.in");
}

void caseUsuario() {
    int opcao;
    Usuario usuario;
    do {
        printf("1. Novo usu�rio\n");
        printf("2. Excluir usu�rio\n");
        printf("3. Voltar ao menu principal\n");
        printf("9. Sair do aplicativo\n");

        printf("Digite a op��o desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
            	limparTela();
            	printf ("======== Cadastrar novo usu�rio ========\n\n");
                printf("Digite o Login: ");
                scanf("%s", usuario.login);
                printf("Digite a Senha: ");
                scanf("%s", usuario.senha);
                salvarUsuario(&usuario);
                printf ("\n======== Usu�rio cadastrado! ========\n\n");
                break;

            case 2:
            	limparTela();
            	printf ("======== Excluir usu�rio ========\n\n");
                printf("Digite o Login do usu�rio a ser exclu�do: ");
                scanf("%s", usuario.login);
                printf("Digite a Senha do usu�rio a ser exclu�do: ");
                scanf("%s", usuario.senha);
                excluirUsuario(&usuario);
                printf ("\n======== Usu�rio excluido! ========\n\n");
                break;

            case 3:
                printf("Voltando ao menu principal.\n");
                break;

            case 9:
                limparTela ();
                printf("Saindo do programa. At� logo!\n");
                sleep(2);
                limparTela();
                printf ("Pressione qualquer tecla para terminar!");
                exit(0);
                break;

            default:
                printf("Op��o inv�lida. Tente novamente\n");
        }
    } while (opcao != 3 && opcao != 9);
    printf ("\n\n");
}


void login() {
    Usuario usuario;
    int loginEfetuado = 0;
    while (!loginEfetuado) {
    	
    	printf ("==================================");
		printf ("\n\n====Bem Vindo(a) a imobili�ria====\n\n");
		printf ("==================================\n\n");

        printf("Digite o Login: ");
        scanf("%s", usuario.login);
        printf("Digite a Senha: ");
        
        int i = 0;
        char ch;
        while ((ch = getch()) != 13 && i < sizeof(usuario.senha) - 1) { //O valor 13 � referente � quando da enter no Windows
            usuario.senha[i++] = ch;
            printf("*");
        }
        usuario.senha[i] = '\0';
        
        if (verificarUsuario(&usuario)) {
            printf("\nLogin efetuado com sucesso!\n\n");
            loginEfetuado = 1;
            sleep(1);
            limparTela();
        } else {
            printf("\nDados inv�lidos!\n");
            sleep(1);
            limparTela();
        }
    }
}

void caseMenu() {
	int escolha = 0;
	
	
	while (escolha != 9) {
        
		limparTela();
		printf("======== Menu ========\n\n");
    	printf("1. Clientes\n");
   	 	printf("2. Im�veis\n");
    	printf("3. Simula��es\n");
    	printf("4. Usu�rios\n");
    	printf("9. Sair\n");
    	printf("Escolha uma op��o: ");
        scanf("%i", &escolha);
        getchar();

        switch (escolha) {
            
			case 1:
            	limparTela();
            	printf("======== Clientes ========\n\n");
            	caseMenuCliente();
                break;
            
			case 2:
            	limparTela();
                printf("======== Im�veis ========\n\n");
                caseImoveis ();
                break;
            
			case 3:
                limparTela();
				printf("======== Simula��o ========\n\n");
				caseMenuSimulacao();
                break;
            
			case 4:
				limparTela();
				printf("======== Usu�rios ========\n\n");
				caseUsuario();
                break;
            
			case 9:
            	limparTela ();
                printf("Saindo do programa. At� logo!\n\n");
                sleep(2);
                limparTela();
                break;
            
			default:
        		limparTela();
                printf("Op��o inv�lida. Tente novamente.\n");
        		sleep (1);
        		
		}
	}
}

void tabelaSac() {
	
    float principal, taxaJuros, saldoDevedor, entrada = 0.0;
    int numParcelas, i;

    printf("Informe o valor do im�vel: R$ ");
    scanf("%f", &principal);

    printf("Informe a taxa de juros ao ano (em porcentagem): ");
    scanf("%f", &taxaJuros);

    printf("Informe o n�mero de parcelas: ");
    scanf("%d", &numParcelas);
	getchar();
	
    printf("Deseja incluir uma entrada? (s/n): ");
    char incluirEntrada;
    scanf("%c", &incluirEntrada);

    if (incluirEntrada == 's') {
        printf("Informe o valor da entrada: R$ ");
        scanf("%f", &entrada);
        principal -= entrada;
    }

    taxaJuros /= 100.0;
    float taxaMensal = taxaJuros / 12.0;
    float amortizacao = principal / numParcelas;

    printf("\nTabela SAC:\n");
    printf("----------------------------\n\n");

    saldoDevedor = principal;

    for (i = 1; i <= numParcelas; i++) {
        float juros = saldoDevedor * taxaMensal;
        float valorParcela = amortizacao + juros;

        printf("-------- %d� PARCELA --------\n", i);
        printf("Presta��o: R$ %.2f\n", valorParcela);
        printf("Juros: R$ %.2f\n", juros);
        printf("Amortiza��o: R$ %.2f\n", amortizacao);
        printf("Saldo Devedor: R$ %.2f\n", saldoDevedor);
        printf("----------------------------\n\n");

        saldoDevedor -= amortizacao;
    }
}

void tabelaPrice() {
	
    float principal, taxaJuros, valorParcela, saldoDevedor, entrada = 0.0;
    int numParcelas, i;

    printf("Informe o valor do im�vel: R$ ");
    scanf("%f", &principal);

    printf("Informe a taxa de juros ao ano (em porcentagem): ");
    scanf("%f", &taxaJuros);

    printf("Informe o n�mero de parcelas: ");
    scanf("%d", &numParcelas);
	getchar();
	
    printf("Deseja incluir uma entrada? (s/n): ");
    char incluirEntrada;
    scanf("%c", &incluirEntrada);

    if (incluirEntrada == 's') {
        printf("Informe o valor da entrada: R$ ");
        scanf("%f", &entrada);
        principal -= entrada;
    }

    taxaJuros /= 100.0;
    float taxaMensal = taxaJuros / 12.0;
    valorParcela = principal * (taxaMensal) / (1 - pow(1 + taxaMensal, -numParcelas));

    printf("\nTabela Price:\n");
    printf("----------------------------\n\n");

    saldoDevedor = principal;

    for (i = 1; i <= numParcelas; i++) {
        float juros = saldoDevedor * taxaMensal;
        float amortizacao = valorParcela - juros;

        printf("-------- %d� PARCELA --------\n", i);
        printf("Presta��o: R$ %.2f\n", valorParcela);
        printf("Juros: R$ %.2f\n", juros);
        printf("Amortiza��o: R$ %.2f\n", amortizacao);
        printf("Saldo Devedor: R$ %.2f\n", saldoDevedor);
        printf("----------------------------\n\n");

        saldoDevedor -= amortizacao;
    }
}

void caseMenuSimulacao() {
	
	int escolha = 0;
	while (escolha != 3) {
        
		printf("1. Tabela SAC\n");
    	printf("2. Tabela Price\n");
   		printf("3. Voltar para o menu iniciar\n");
   		printf("9. Sair do aplicativo\n");
       	printf("Escolha uma op��o: ");
		scanf("%i", &escolha);
       	getchar();

        	switch (escolha) {
        		
            	case 1:
            		limparTela();
                	printf("Voc� escolheu a op��o Tabela SAC.\n");
                	tabelaSac();
                	break;
                	
    	        case 2:
        	    	limparTela();
            	    printf("Voc� escolheu a op��o Tabela Price.\n");
            	    tabelaPrice();
                	break;
                	
				case 9:
                	limparTela();
                	printf ("Saindo...\n");
                	sleep(2);
                	limparTela();
                	printf ("Pressione qualquer tecla para terminar!");
                	exit(0) ;
                	break;
				
			 	default:
                	printf("Op��o inv�lida. Tente novamente.\n");
                	
			}
			
	}
}

int leituraIdContador() {
    FILE *file = fopen(ID_FILE, "r");
    if (file == NULL) {
        return 0;
    }
    int idContador;
    fscanf(file, "%d", &idContador);
    fclose(file);
    return idContador;
}

void escreveIdContador(int idContador) {
    FILE *file = fopen(ID_FILE, "w");
    fprintf(file, "%d", idContador);
    fclose(file);
}

Imoveis cadastrarImoveis() {
    Imoveis novo;
    FILE *file = fopen(ARQ, "a");

    int idContador = leituraIdContador();

    novo.id = idContador++;
    fprintf(file, "%d - ", novo.id);
    fflush(file);

    escreveIdContador(idContador);

    printf("Digite o cep do im�vel: \n");
    scanf("%d", &novo.cep);
    getchar();
    fprintf(file, "%d - ", novo.cep);
    fflush(file);

    printf("Digite o endere�o do im�vel: \n");
    fgets(novo.endereco, sizeof(novo.endereco), stdin);
    novo.endereco[strcspn(novo.endereco, "\n")] = 0;
    TirarEspaco(novo.endereco);
    fprintf(file, "%s - ", novo.endereco);
    fflush(file);

    printf("Digite o n�mero do im�vel: \n");
    scanf("%d", &novo.numero);
    getchar();
    fprintf(file, "%d - ", novo.numero);
    fflush(file);

    printf("Digite o pre�o do im�vel: \n");
    scanf("%lf", &novo.preco); 
	getchar();
    fprintf(file, "%.2lf - ", novo.preco); 
    fflush(file);

    printf("O im�vel est� dispon�vel para aluguel?:(Disponivel/Indisponivel) \n");
    fgets(novo.aluguel, sizeof(novo.aluguel), stdin);
    novo.aluguel[strcspn(novo.aluguel, "\n")] = 0;
    TirarEspaco(novo.aluguel);
    fprintf(file, "%s - ", novo.aluguel);
    fflush(file);

    printf("O im�vel est� dispon�vel para compra?:(Disponivel/Indisponivel) \n");
    fgets(novo.compra, sizeof(novo.compra), stdin);
    novo.compra[strcspn(novo.compra, "\n")] = 0;
    TirarEspaco(novo.compra);
    fprintf(file, "%s \n", novo.compra);
    fflush(file);

    printf("Im�vel registrado com sucesso!!\n");

    fclose(file);
    
	colocaTraco();
	
    return novo;
}

void procurarImovelPorId(int idProcurado) {
	
    FILE *file = fopen(ARQ, "r");

    Imoveis imovel;
    int encontrou = 0;

    while (fscanf(file, "%d - %d - %s - %d - %lf - %s - %s\n",&imovel.id, &imovel.cep, imovel.endereco, &imovel.numero, &imovel.preco, imovel.aluguel, imovel.compra) != EOF) {
        ColocarEspaco(imovel.endereco);
        ColocarEspaco(imovel.aluguel);
        ColocarEspaco(imovel.compra);

        if (imovel.id == idProcurado) {
            printf("Id: %d\n", imovel.id);
            printf("CEP: %d\n", imovel.cep);
            printf("Endere�o: %s\n", imovel.endereco);
            printf("N�mero do im�vel: %d\n", imovel.numero);
            printf("Pre�o: %.2f\n", imovel.preco);
            printf("Dispon�vel para aluguel: %s\n", imovel.aluguel);
            printf("Dispon�vel para compra: %s\n", imovel.compra);

            colocaTraco();
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum im�vel encontrado com o ID %d.\n", idProcurado);
    }

    fclose(file);
}

void listarImoveis() {
    FILE *file = fopen(ARQ, "r");

	Imoveis imovel;
    printf("Lista de todos im�veis cadastrados:\n");

    while (fscanf(file, "%d - %d - %s - %d - %lf - %s - %s\n", &imovel.id, &imovel.cep, imovel.endereco, &imovel.numero,&imovel.preco, imovel.aluguel, imovel.compra) != EOF) {
    	
        ColocarEspaco(imovel.endereco);
        ColocarEspaco(imovel.aluguel);
        ColocarEspaco(imovel.compra);

        printf("id: %d\n", imovel.id);
        printf("CEP: %d\n", imovel.cep);
        printf("Endere�o: %s\n", imovel.endereco);
        printf("N�mero do im�vel: %d\n", imovel.numero);
        printf("Pre�o: %.2f\n", imovel.preco);
        printf("Dispon�vel para aluguel: %s\n", imovel.aluguel);
        printf("Dispon�vel para compra: %s\n", imovel.compra);

        colocaTraco();
    }

    fclose(file);
}

void procurarImoveisPorCEP(int cepProcurado) {
    FILE *file = fopen(ARQ, "r");

    Imoveis imovel;
    int encontrou = 0;

    printf("Lista de im�veis com o CEP %d:\n", cepProcurado);

    while (fscanf(file, "%d - %d - %s - %d - %lf - %s - %s\n",&imovel.id, &imovel.cep, imovel.endereco, &imovel.numero, &imovel.preco, imovel.aluguel, imovel.compra) != EOF) {
        ColocarEspaco(imovel.endereco);
        ColocarEspaco(imovel.aluguel);
        ColocarEspaco(imovel.compra);

        if (imovel.cep == cepProcurado) {
            printf("Id: %d\n", imovel.id);
            printf("CEP: %d\n", imovel.cep);
            printf("Endere�o: %s\n", imovel.endereco);
            printf("N�mero do im�vel: %d\n", imovel.numero);
            printf("Pre�o: %.2f\n", imovel.preco);
            printf("Dispon�vel para aluguel: %s\n", imovel.aluguel);
            printf("Dispon�vel para compra: %s\n", imovel.compra);

            colocaTraco();
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum im�vel encontrado com o CEP %d.\n", cepProcurado);
    }

    fclose(file);
}

void removerImovel(int id) {
    FILE *file = fopen(ARQ, "r");
    FILE *tempFile = fopen("temp.in", "w");
    int idArq;
    int cep;
    char endereco[101];
    double preco; 
    char aluguel[15];
    char compra[15];
    int numero;
    int encontrado = 0;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }	
	else {
    	
		while (fscanf(file, "%d - %d - %s - %d - %lf - %s - %s", &idArq, &cep, endereco, &numero, &preco, aluguel, compra) != EOF) { 
        
			if (id == idArq) {
				
				ColocarEspaco(endereco);
            	encontrado = 1;
            	printf("Im�vel removido:\n");
            	printf("ID: %d\n", idArq);
           		printf("CEP: %d\n", cep);
            	printf("Endere�o: %s\n", endereco);
	            printf("N�mero do im�vel: %d\n", numero);
	            printf("Pre�o: %.2f\n", preco);
            	printf("Dispon�vel para aluguel: %s\n", aluguel);
            	printf("Dispon�vel para compra: %s\n", compra);
            	break;
        	}
         
			else {
				fprintf(tempFile, "%d - %d - %s - %d - %.2f - %s - %s\n", idArq, cep, endereco, numero, preco, aluguel, compra);
			}
    	}
	}
    fclose(file);
    fclose(tempFile);

    if (!encontrado) {
        printf("Im�vel n�o encontrado.\n");
    } else {
        remove(ARQ);
        rename("temp.in", ARQ);
    }
    colocaTraco();
}

void atualizarImovel(int id) {
	
	limparTela();
    FILE *file = fopen(ARQ, "r");
    FILE *tempFile = fopen("temp.in", "w");
    Imoveis imovel;
    int encontrado = 0;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        
    }

    while (fscanf(file, "%d - %d - %s - %d - %lf - %s - %s", &imovel.id, &imovel.cep, imovel.endereco, &imovel.numero, &imovel.preco, imovel.aluguel, imovel.compra) != EOF) {
        
		if (id == imovel.id) {
            encontrado = 1;
            printf("Im�vel encontrado.\n\n");
			sleep(1);
            int opcao;
            do {
            	limparTela();
                printf("Escolha o campo a ser atualizado:\n");
                printf("1. CEP\n");
                printf("2. Endere�o\n");
                printf("3. N�mero do im�vel\n");
                printf("4. Pre�o\n");
                printf("5. Dispon�vel para aluguel\n");
                printf("6. Dispon�vel para compra\n");
                printf("7. Voltar\n");
                printf("9. Sair do aplicativo\n");
                printf("Op��o: ");
                scanf("%d", &opcao);
                getchar();

                switch (opcao) {
                    
					case 1:
                        printf("Novo CEP: ");
                        scanf("%d", &imovel.cep);
                        getchar();
                        printf("Atualizado com sucesso \n");
                        sleep(1);
                        break;
                    
					case 2:
                        printf("Novo Endere�o: ");
                        fgets(imovel.endereco, sizeof(imovel.endereco), stdin);
                        imovel.endereco[strcspn(imovel.endereco, "\n")] = 0;
                        printf("Atualizado com sucesso \n");
						sleep(1);
                        break;
                    
					case 3:
                        printf("Novo N�mero do im�vel: ");
                        scanf("%d", &imovel.numero);
                        getchar();
                        printf("Atualizado com sucesso \n");
                        sleep(1);
                        break;
                    
					case 4:
                        printf("Novo Pre�o: ");
                        scanf("%lf", &imovel.preco); 
                        getchar();
                        printf("Atualizado com sucesso \n");
                        sleep(1);
                        break;
                    
					case 5:
                        printf("Dispon�vel para novo aluguel? (Disponivel/Indisponivel): ");
                        fgets(imovel.aluguel, sizeof(imovel.aluguel), stdin);
                        imovel.aluguel[strcspn(imovel.aluguel, "\n")] = 0;
                        printf("Atualizado com sucesso \n");
						sleep(1);
                        break;
                    
					case 6:
                        printf("Dispon�vel para nova compra? (Disponivel/Indisponivel): ");
                        fgets(imovel.compra, sizeof(imovel.compra), stdin);
                        imovel.compra[strcspn(imovel.compra, "\n")] = 0;
                        printf("Atualizado com sucesso \n");
						sleep(1);
                        break;
                    
					case 7:
                        break;
                    
					case 9:
                		limparTela();
                		printf ("Saindo...\n");
                		sleep(2);
                		limparTela();
                		printf ("Pressione qualquer tecla para terminar!");
                		exit(0) ;
                		break;
                    
					default:
                        printf("Op��o inv�lida. Tente novamente.\n");
                        
                }
            } 
			while (opcao != 7);
			
            fprintf(tempFile, "%d - %d - %s - %d - %.2f - %s - %s\n", imovel.id, imovel.cep, imovel.endereco, imovel.numero, imovel.preco, imovel.aluguel, imovel.compra);

            printf("Im�vel atualizado com sucesso!\n");
        } 
		else {
            fprintf(tempFile, "%d - %d - %s - %d - %.2f - %s - %s\n",imovel.id, imovel.cep, imovel.endereco, imovel.numero, imovel.preco, imovel.aluguel, imovel.compra);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!encontrado) {
        printf("Im�vel n�o encontrado.\n");
    } else {
        remove(ARQ);
        rename("temp.in", ARQ);
    }
}

void caseImoveis () {
	
    int opcao, cepProcurado, id;
    
    while (opcao != 7) {
    	printf ("1. Cadastrar im�veis \n");
    	printf ("2. Listar im�veis \n");
    	printf ("3. Procurar im�veis por CEP \n");
    	printf ("4. Procurar im�veis por ID \n");
    	printf ("5. Remover im�veis \n");
    	printf ("6. Atualizar im�veis \n");
    	printf ("7. Voltar ao menu principal \n");
    	printf ("9. Sair do aplicativo \n");
    
		printf ("Escolha uma op��o: ");
		scanf("%i", &opcao);
		getchar();

		switch (opcao) {
	
			case 1:
				limparTela();
				printf ("Voc� escolheu a op��o cadastrar im�vel \n\n");
				cadastrarImoveis();
				break;
		
			case 2:
				limparTela();
				printf ("Voc� escolheu a op��o listar im�veis \n\n");
				listarImoveis ();
				break;
			
			case 3:
				limparTela();
				printf ("Voc� escolheu a op��o procurar im�veis por CEP \n\n");
				printf("Digite o CEP do(s) im�vel(is) que deseja consultar: ");
				scanf ("%d", &cepProcurado);
        		procurarImoveisPorCEP(cepProcurado);
        		break;
        		
        	case 4:
        		limparTela();
        		printf ("Voc� escolheu a op��o procurar im�ceis por ID \n\n");
				printf("Digite o ID do im�vel que deseja consultar: ");
        		scanf ("%d", &id);
        		procurarImovelPorId(id);
        		break;
			
			case 5:
				limparTela();
				printf ("Voc� escolheu a op��o remover im�vel \n\n");
				printf("Digite o id do im�vel que deseja remover: ");
        		scanf ("%d", &id);
				removerImovel(id);
				break;
			
			case 6:
				limparTela();
				printf ("Voc� escolheu a op��o atualizar im�vel \n\n");
				printf("Digite o id do im�vel que deseja atualizar: ");
				scanf ("%d", &id);
        		atualizarImovel(id);
				break;
				
			case 7:
				break;
				
			case 9:
                limparTela();
                printf ("Saindo...\n");
                sleep(2);
                limparTela();
                printf ("Pressione qualquer tecla para terminar!");
                exit(0) ;
                break;
		
			default:
				printf ("Valor indisponivel, Digite outro valor \n");
				sleep(1);
				limparTela();
		}
	}

}

int cpfExistente(long long int cpf) {
    Cliente c;
    FILE *file = fopen("clientes.in", "r");
    if (file == NULL) {
        return 0;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%lld - %[^\n] - %[^\n] - %[^\n] - %s", &c.cpf, c.nome, c.endereco, c.email, c.tel);
        if (c.cpf == cpf) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}


Cliente cadastraCliente() {
    Cliente c;
    FILE *file = fopen("clientes.in", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return c;
    }

    printf("Digite o CPF do cliente: ");
    scanf("%lld", &c.cpf);
    getchar();
    if (cpfExistente(c.cpf)) {
        printf("CPF j� cadastrado.\n");
        return c;
    }
    else {
    fprintf(file, "%lld - ", c.cpf);
	fflush(file);
	}
    printf("Digite o nome do cliente: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = 0;
    TirarEspaco(c.nome);
    fprintf(file, "%s - ", c.nome);
    fflush(file);

    printf("Digite o endereco do cliente: ");
    fgets(c.endereco, sizeof(c.endereco), stdin);
    c.endereco[strcspn(c.endereco, "\n")] = 0;
    TirarEspaco(c.endereco);
    fprintf(file, "%s - ", c.endereco);
    fflush(file);

    printf("Digite o email do cliente: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;
    TirarEspaco(c.email);
    fprintf(file, "%s - ", c.email);
    fflush(file);

    printf("Digite o telefone do cliente: ");
    fgets(c.tel, sizeof(c.tel), stdin);
    c.tel[strcspn(c.tel, "\n")] = 0;
    fprintf(file, "%s \n", c.tel);
    fflush(file);
	
    fclose(file);
    printf("========Cadastro realizado!========\n\n");

    return c;
}

void mostrarCliente (int cpf) {
    FILE *file = fopen("clientes.in", "r");
    char nome[101];
    char endereco[101];
    char email[101];
    char tel[13];  
    int cpfArquivo;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fscanf(file, "%lld - %[^-] - %[^-] - %[^-] - %[^-] - ", &cpfArquivo, nome, endereco, email, tel) != EOF) {
        if (cpf == cpfArquivo) {
            ColocarEspaco(nome);  
            ColocarEspaco(endereco);  
            ColocarEspaco(email);  
            printf("Nome: %s\n", nome);
            printf("Endereco: %s\n", endereco);
            printf("Email: %s\n", email);
            printf("Telefone: %s\n", tel); 
            fclose(file);
            printf("----------------------------------- \n----------------------------------- \n\n");
            return;
        }
    }

    printf("Cliente nao encontrado.\n");
    fclose(file);
}


void atualizarCliente() {
    
	Cliente cliente;
    long long cpf;
    FILE *file = fopen("clientes.in", "r+");
    FILE *temp = fopen("temp.in", "w");
    int found = 0;

    printf("Digite o CPF do cliente que deseja alterar: ");
    scanf("%lld", &cpf);
    getchar();

    while (fscanf(file, "%lld - %[^-] - %[^-] - %[^-] - %[^\n]\n", &cliente.cpf, cliente.nome, cliente.endereco, cliente.email, cliente.tel) != EOF) {
        if (cliente.cpf == cpf) {
            printf("Digite o novo nome do cliente: ");
            fgets(cliente.nome, sizeof(cliente.nome), stdin);
            cliente.nome[strcspn(cliente.nome, "\n")] = 0;
            TirarEspaco(cliente.nome);

            printf("Digite o novo endereco do cliente: ");
            fgets(cliente.endereco, sizeof(cliente.endereco), stdin);
            cliente.endereco[strcspn(cliente.endereco, "\n")] = 0;
            TirarEspaco(cliente.endereco);

            printf("Digite o novo email do cliente: ");
            fgets(cliente.email, sizeof(cliente.email), stdin);
            cliente.email[strcspn(cliente.email, "\n")] = 0;
            TirarEspaco(cliente.email);

            printf("Digite o novo telefone do cliente: ");
            fgets(cliente.tel, sizeof(cliente.tel), stdin);
            cliente.tel[strcspn(cliente.tel, "\n")] = 0;

            found = 1;
        }
        fprintf(temp, "%lld - %s - %s - %s - %s\n", cliente.cpf, cliente.nome, cliente.endereco, cliente.email, cliente.tel);
    }

    fclose(file);
    fclose(temp);

    remove("clientes.in");
    rename("temp.in", "clientes.in");

    if (found == 0) {
        printf("CPF n�o encontrado.\n");
    } else {
        printf("======== Dados do cliente atualizados com sucesso. ========\n\n");
    }
}



void excluirCliente() {
    Cliente cliente;
    long long cpf;
    FILE *file = fopen("clientes.in", "r");
    FILE *temp = fopen("temp.in", "w");
    int found = 0;

    printf("Digite o CPF do cliente que deseja excluir: ");
    scanf("%lld", &cpf);
    getchar();

    while (fscanf(file, "%lld - %[^-] - %[^-] - %[^-] - %[^\n]\n", &cliente.cpf, cliente.nome, cliente.endereco, cliente.email, cliente.tel) != EOF) {
        if (cliente.cpf != cpf) {
            fprintf(temp, "%lld - %s - %s - %s - %s\n", cliente.cpf, cliente.nome, cliente.endereco, cliente.email, cliente.tel);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove("clientes.in");
    rename("temp.in", "clientes.in");

    if (found == 0) {
        printf("CPF n�o encontrado.\n");
    } else {
        printf("========Cliente exclu�do com sucesso.========\n\n");
    }
}

void caseMenuCliente () {
    int cpf;
    int escolha = 0;

    while (escolha != 5){
        printf("1. Cadastrar novo cliente\n");
        printf("2. Mostrar dados do cliente\n");
        printf("3. Alterar dados do cliente\n");
        printf("4. Excluir dados do cliente\n");
        printf("5. Voltar ao menu iniciar\n");
        printf("9. Sair do aplicativo\n");
        printf("Escolha uma op��o: ");
        
        scanf("%d", &escolha);
        getchar();

        switch (escolha){
            
			case 1:
                limparTela();
                printf ("Voce escolheu a op�ao de cadastro \n\n");
                cadastraCliente();
                break;
            
			case 2:
                limparTela();
                printf ("Voce escolheu a op�ao de mostrar os dados \n\n");
                printf("Digite o CPF do cliente que deseja procurar: ");
                scanf("%d", &cpf);
                getchar();
                mostrarCliente(cpf);
                break;
            
			case 3:
                limparTela();
                printf("Voc� escolheu a op��o de alterar dados \n\n");
                atualizarCliente();
                break;
      
            case 4:
                limparTela();
                printf("Voc� escolheu a op��o de excluir cliente \n\n");
                excluirCliente();
                break;
                
			case 9:
                limparTela();
                printf ("Saindo...\n");
                sleep(2);
                limparTela();
                printf ("Pressione qualquer tecla para terminar!");
                exit(0) ;
                break;
                
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    }
}

int main() {
	
	setlocale(LC_ALL, "");
	
	login();

	caseMenu();
	printf ("Pressione qualquer tecla para terminar!");
    return 0;
}
