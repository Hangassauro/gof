#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_PADRAO 50
#define TAMANHO_MAX 100

#define GERACOES 4

//Hangai feio

#define TRUE 1
#define FALSE 0

int main()
{
	char opcaomenu, opcao;
    int i, j, t = 0, x=0, k, fim = FALSE;
    int tamanho = TAMANHO_MAX, validar = 0;
    int m1[tamanho][tamanho], m2[tamanho][tamanho];
    int n_geracoes=GERACOES;
    
    for (i=0;i<tamanho;i++){
        for (j=0;j<tamanho;j++){

            m1[i][j] = m2[i][j] = 0;
        }
    }
    
    m1[0][0]=1;
    m1[0][1]=1;
    m1[0][2]=1;

	do{
	fflush(stdin);
	printf("\n(C)onfig\n(J)ogar\n(S)air\n\nForneca a opcao: ");
	scanf("%c", &opcaomenu);
	
	
    
    switch(opcaomenu){
			case 'C':
			case 'c':

    do{
        if(validar  == TRUE){
            printf("Digite um tamanho valido... Min: 50 - Max: 100");
            printf("\n");
        }

        fflush(stdin);
        printf("Digite o tamanho: ");
        scanf("%d",&tamanho);

        validar = TRUE;

    }while(tamanho < TAMANHO_PADRAO || tamanho > TAMANHO_MAX);
    
    validar = FALSE;
    
    do{
        if(validar  == TRUE){
            printf("Digite uma quantidade valida... Min: 1");
            printf("\n");
        }

        fflush(stdin);
        printf("Digite a quantidade de geracoes a partir da primeira: ");
        scanf("%d",&n_geracoes);

        validar = TRUE;

    }while(n_geracoes< 1);
    
    
    /* para atribuir os valores que o usuario deseja que tenha vida*/
    while (!fim){

        printf("Digite i: "); /*linhas*/
        scanf("%d", &i);

        printf("Digite j: "); /*colunas*/
        scanf("%d", &j);

        m1[i][j]=1;
        x++;
        

        printf("Deseja continuar (S/N)?");
        opcao = getch();
        printf("\nSeres vivos: %d", x);
        printf("\n");
        if(opcao == 'N'  || opcao == 'n')
		fim=TRUE;
    }

    printf("\n");
    
    break;
    
    case 'J':
    case 'j':
    	
	


    

    /* exibindo a matriz inicial*/

    for(i=0;i<tamanho;i++){
        for(j=0;j<tamanho;j++){

            printf("%d", m1[i][j]);
        }

        printf("\n");
    }


    for(k = 1; k <= n_geracoes; k++){ /* Numero de gerações a serem exibidas*/
        for(i=0;i<tamanho;i++){
            for (j=0;j<tamanho;j++){

                t=0;

                /* Série de testes sobre os 6 vizinhos possivéis*/
                if (m1[(i-1+tamanho)%tamanho][(j-1+tamanho)%tamanho]==1)
                    t++;
                if (m1[(i-1+tamanho)%tamanho][j]==1)
                    t++;
                if (m1[(i-1+tamanho)%tamanho][(j+1)%tamanho]==1)
                    t++;
                if (m1[i][(j-1+tamanho)%tamanho]==1)
                    t++;
                if (m1[i][(j+1)%tamanho]==1)
                    t++;
                if (m1[(i+1)%tamanho][(j-1+tamanho)%tamanho]==1)
                    t++;
                if (m1[(i+1)%tamanho][j]==1)
                    t++;
                if (m1[(i+1)%tamanho][(j+1)%tamanho]==1)
                    t++;

                /* Atribuir o valores atualizadoos*/
                if ((t==0)||(t==1)||(t>=4)){
                    m2[i][j]=0;
                }
                else {
                    if (t==3){
                        m2[i][j]=1;
                    }
                    else {
                        m2[i][j]=m1[i][j];
                    }
                }
            }
        }

        /* Atribuindo a matriz real(m2) na matriz de teste(m1)*/
        for(i=0;i<tamanho;i++){
            for(j=0;j<tamanho;j++){
                m1[i][j]=m2[i][j];
            }
        }

        /* Exibindo a matriz*/
        printf("\n\n");

        for(i = 0;i < tamanho; i++){
            for(j = 0;j < tamanho; j++){
                printf("%d", m2[i][j]);
            }
            printf("\n");
        }

        printf("\n\n");
        
		
    }
    printf("\nDeseja limpar? (S/N)");
        opcao = getch();
        printf("\n");
        if(opcao == 'S'  || opcao == 's'){
			 for (i=0;i<tamanho;i++){
        		for (j=0;j<tamanho;j++){

            m1[i][j] = m2[i][j] = 0;
        }
    }
		}
    break;}
	} while (opcao != 'S' && opcao != 's');

}
