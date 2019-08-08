//MELHORIAS FULTURAS : Layout, Banco de Dados
# include <windows.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <conio.h>

FILE *arquivo;
struct arvore{ // Aqui crio o struct pra arvore e coloco oq quero q ela tenha
	char Nome[100],Marca[100];
	int ano, km_andado, quantidade;
	float valor;
	struct arvore *left;
	struct arvore *right;
};

typedef struct arvore Arvore;

void inserir(Arvore **raiz, char string[], char string1[]);
void inserir_vendas(Arvore **vendas,Arvore **estoque,int quantidade);
void ordem(Arvore *raiz);
void busca(Arvore *raiz, char string[]);
void Altera( Arvore **raiz, char *string);
void excluir(Arvore **raiz,char string[],int quant);
void criar_arquivo(Arvore **raiz);
void esc_arquivo(Arvore **raiz);
Arvore** menor_right(Arvore *raiz);
Arvore** maior_left (Arvore *raiz);
void ler_string(char string[]);
void ler_string(char string1[]);
void ler_ano(int *ano);
void ler_km(int *km_andado);
void ler_valor(float *valor);
void ler_quantidade(int *quantidade);
void maiuscula(char string[]);
void opcao(char op[]);
void posicao(int x, int y);
void Menu(int *num);
void Menu_1();
void Menu_2();
void Menu_3();
void Menu_4();
void Menu_5();

void inserir(Arvore **raiz, char string[], char string1[]){//cria o no dependendo se a maior ou menor q o no pai
	int ano, km_andado, quantidade;
	float valor;
	if(*raiz == NULL){ // se a arvore ainda nao existir
		*raiz = (Arvore*) malloc (sizeof(Arvore)); //aloco dinamicamente
		strcpy((*raiz)->Nome,string);//Copia a string para o Nome.
		strcpy((*raiz)->Marca,string1);
		//recebe as informacoes
		ler_ano(&ano);
		(*raiz)->ano = ano;
		ler_km(&km_andado);
		(*raiz)->km_andado = km_andado;
		ler_valor(&valor);
		(*raiz)->valor = valor;
		ler_quantidade(&quantidade);
		(*raiz)->quantidade = quantidade;
		
		(*raiz)->left = NULL;
		(*raiz)->right = NULL;
	}else{
		if(strcasecmp((*raiz)->Nome,string) > 0){ //compara as strings sem diferenciar maiusculo e minusculo. se for >0, quer dizer que a string eh menor q o Nome ja existente naquele No
			inserir(&(*raiz)->left,string,string1); // como eh menor, eh colocado no lado esquerdo
		}else{
			if(strcasecmp((*raiz)->Nome,string) < 0){ //como eh maior (na ordem alfabetica no caso), vai para o lado direito 
				inserir(&(*raiz)->right,string,string1);
			}else{
				if(strcmp((*raiz)->Nome,string) == 0){ // se forem iguais, a quantidade do tal carro aumenta em 1
					printf("\nVEICULO JA CADASTRADO\n");
					printf("Para aumentar estoque:");
					ler_quantidade(&quantidade);
					printf("\nMais %d adicionado a concessionaria\n",quantidade);
					(*raiz)->quantidade = (*raiz)->quantidade + quantidade;
					getch();
				}
			}
		}
	}

}
void ordem(Arvore *raiz){//printa ordenado
	if(raiz != NULL){ //se tiver no
		ordem((raiz)->left); //continua ate acabar os nos esquerdos
		printf("\n\n%d",(raiz)->quantidade);
		printf(" %s ",(raiz)->Marca);
		printf("%s",(raiz)->Nome);
		printf(" %d",(raiz)->ano);
		printf(", R$ %.2f",(raiz)->valor);
		ordem((raiz)->right); //continua ate acabar os nos direitos
	}
}
void busca(Arvore *raiz, char string[]){ //busca o no pedido, e apresenta suas informacoes
	if(raiz!= NULL){ //fica buscando ate acabar todos os nos
		if(strcasecmp((raiz)->Nome,string) > 0){ //se true, no alfabeto, eh menor, logo nao eh igual
			busca((raiz)->left,string); //continua indo pelo lado esquerdo ate ou achar ou ir pro lado direito
		}else{
			if(strcasecmp((raiz)->Nome,string) < 0){ //se true, no alfabeto, eh maior, logo nao eh igual
				busca((raiz)->right,string); //continua indo pelo lado direito ate ou achar ou ir pro lado esquerdo
			}else{
				if(strcmp((raiz)-> Nome,string) == 0){ //quer dizer que achou
					system("cls"); //limpa a tela
					//mostra as informacoes
					posicao(25,1);printf("CARRO ENCONTRADO!!\n");
					printf("\n\nMarca : %s ",(raiz)->Marca);
					printf("\nNome : ");
					printf("%s",(raiz)->Nome);
					printf("\nValor : ");
					printf("R$ %.2f",(raiz)->valor);
					printf("\nKm Andados : ");
					printf("%d",(raiz)->km_andado);
					printf("\nAno : ");
					printf("%d",(raiz)->ano);
					printf("\nQuantidade : ");
					printf("%d", (raiz)->quantidade);
				}
			}
		}
	}else{//mostra q n tem 
		system("cls");//limpa a tela
		posicao(25,1);printf("*__________________________*\n");
        posicao(25,2);printf("|   Nome nao encontrado!!  |\n");
        posicao(25,3);printf("*__________________________*\n");
        getch();
	}
}
void Altera( Arvore **raiz, char *string){ // alterar informacoes do carro
	if((*raiz) != NULL){//se tiver no
		if(strcasecmp((*raiz)->Nome,string) > 0){//se true, no alfabeto, eh menor, logo nao eh igual
			Altera(&(*raiz)->left,string);//anda um pra esquerda e continua procurando
		}else{
			if(strcasecmp((*raiz)->Nome,string) < 0){//se true, no alfabeto, eh maior, logo nao eh igual
				Altera(&(*raiz)->right,string);//anda um pra direita e continua procurando
			}else{
				if(strcmp((*raiz)->Nome,string) == 0){//se igual, foi encontrado
					
					//pede pra modificar
					system("cls");
					int km_andado,ano,quantidade;
					float valor;
					posicao(25,1);printf("*______________________________*\n");
					posicao(25,2);printf("| REGISTRO DO CARRO ENCONTRADO |\n");
					posicao(25,3);printf("*______________________________*\n");
					printf("\n\nNome : ");
					printf("%s\n",(*raiz)->Nome);
					printf("\nNovo valor : ");
					scanf("%f",&valor);
					printf("\nKm andados : ");
					scanf("%d",&km_andado);
					printf("\nAno : ");
					scanf("%d",&ano);
					printf("\nQuantidade : ");
					scanf("%d",&quantidade);
					(*raiz)->valor = valor;
					(*raiz)->km_andado = km_andado;
					(*raiz)->ano = ano;
					(*raiz)->quantidade = quantidade;
					system("cls");
					
					posicao(25,1); printf("*_________________*\n");
           			posicao(25,2); printf("| Dado Alterado!! |\n");
          			posicao(25,3); printf("*_________________*\n");
           			getch();
				}
			}
		}
	}else{//se nao ha mais no para procurar para poder alterar
		system("cls");
        	posicao(25,1);printf("*________________________*\n");
         	posicao(25,2);printf("| Carro nao encontrado!! |\n");
         	posicao(25,3);printf("*________________________*\n");
         	getch();
	}
}
void excluir(Arvore **estoque, Arvore **vendas, char string[]){//VENDA DE VEICULO
	int quant;
	Arvore **aux2, *aux3; //variaveis para futura "troca"
	if((*estoque) !=NULL){//se ainda tiver no pra procurar para excluir/vender
		if(strcasecmp((*estoque)->Nome,string) == 0){//se achar, exclui
			printf("Quantos veiculos serao vendidos?\n");
			scanf("%d",&quant);
			if((*estoque)->quantidade - quant > 0){//se tiver mais de um carro pra vender, soh tira um carro
				inserir_vendas(&(*vendas),&(*estoque), quant);
				(*estoque)->quantidade = ((*estoque)->quantidade) - quant;
			}else if((*estoque)->quantidade == quant){//se tiver a quantia exata, vende e tira da arvore
				inserir_vendas(&(*vendas),&(*estoque), quant);
				if((*estoque)->left == (*estoque)->right){//esse no n tem filhos, logo pode ser excluido sem se importar com ramificacoes dele
					free(*estoque);
					(*estoque) = NULL;
				}else{
					if((*estoque)->left != NULL){//se existir filhos do no que sera excluido
						aux2 = maior_left(*estoque);
						aux3 = *aux2;
						(*aux2) = (*aux2)->left;
					}else{
						aux2 = menor_right(*estoque);
						aux3 = *aux2;
						(*aux2) = (*aux2)->right;
					}
					strcpy((*estoque)->Nome,aux3->Nome);//copia o nome de aux3 na raiz
					free(aux3);//limpa o aux3
					aux3 = NULL;
				}
			}else if((*estoque)->quantidade < quant){
				system("cls");//nao foi encontrado o veiculo solicitado
		        posicao(25,1); printf("*________________________________*\n");
		       	posicao(25,2); printf("| Nao ha essa quantia em estoque |\n");
		      	posicao(25,3); printf("*________________________________*\n");
		       	getch();
			}
			
		}else{
			if(strcasecmp(string,(*estoque)->Nome) < 0){//menor, logo lado esquerdo
				excluir(&(*estoque)->left,&(*vendas),string);//continua a procurar pelo lado esquerdo o arquivo pra deletar
			}else{//maior, logo lado direito
				excluir(&(*estoque)->right,&(*vendas),string);//continua a procurar pelo lado direito o arquivo pra deletar
			}
		}
	}else{
		system("cls");//nao foi encontrado o veiculo solicitado
        posicao(25,1); printf("*________________________*\n");
       	posicao(25,2); printf("| Carro nao encontrado!! |\n");
      	posicao(25,3); printf("*________________________*\n");
       	getch();
    }
}
void inserir_vendas(Arvore **vendas,Arvore **estoque, int quantidade){
	if(*vendas == NULL){ // se a arvore ainda nao existir
		*vendas = (Arvore*) malloc (sizeof(Arvore)); //aloco dinamicamente
		strcpy((*vendas)->Nome , (*estoque)->Nome);//Copia a string para o Nome.
		strcpy((*vendas)->Marca , (*estoque)->Marca);
		//recebe as informacoes
		(*vendas)->ano = (*estoque)->ano;
		(*vendas)->km_andado = (*estoque)->km_andado;
		(*vendas)->valor = (*estoque)->valor;
		(*vendas)->quantidade = quantidade;
		
		(*vendas)->left = NULL;
		(*vendas)->right = NULL;
	}else{
		if(strcasecmp((*vendas)->Nome,(*estoque)->Nome) > 0){ //compara as strings sem diferenciar maiusculo e minusculo. se for >0, quer dizer que a string eh menor q o Nome ja existente naquele No
		//	inserir_vendas(&(*vendas)->left,&estoque,quantidade); // como eh menor, eh colocado no lado esquerdo
			inserir_vendas(&(*vendas)->left,&(*estoque),quantidade); 
		}else{
			if(strcasecmp((*vendas)->Nome,(*estoque)->Nome) < 0){ //como eh maior (na ordem alfabetica no caso), vai para o lado direito 
				inserir_vendas(&(*vendas)->right,&(*estoque),quantidade);
			}else{
				if(strcmp((*vendas)->Nome,(*estoque)->Nome) == 0){ // se forem iguais, a quantidade do tal carro aumenta em 1
					printf("ADICIONANDO MAIS VENDAS NESSE CARRO \n");
					(*vendas)->quantidade = (*vendas)->quantidade + quantidade;
				}
			}
		}
	}
}
void criar_arquivo(FILE *arquivo,char string[],int trigger){//cria o arquivo
	arquivo = fopen(string,"rt");//abre leitura	
	if(arquivo == NULL){//colocar aqui (se arquivo nao tiver sido feito)
			if(trigger == 1){
			fclose(arquivo);//fecha leitura
			arquivo = fopen(string,"wt");//abre escrita
			fprintf(arquivo,"ESTOQUE : \n\n| QUANTIDADE / VEICULO / KM RODADOS / VALOR UNITARIO |\n\n");//colocar no arquivo recem criado como primeira linha
		}else if(trigger == 2){
			fclose(arquivo);//fecha leitura
			arquivo = fopen(string,"wt");//abre escrita
			fprintf(arquivo,"VENDIDOS : \n\n| QUANTIDADE / VEICULO / VALOR TOTAL POR CARRO |\n\n");//colocar no arquivo recem criado como primeira linha
		}
	}else{
		printf("\nARQUIVO JA EXISTENTE\n");
	}
	fclose(arquivo);//fecha escrita
	
}
void esc_arquivo(Arvore *raiz,FILE *arquivo,char string[]){//escreve dentro do arquivo
	if(raiz != NULL){ //se tiver noh
		//continua ate acabar os nos esquerdos
		esc_arquivo((raiz)->left,arquivo,string);
		//escrever no arquivo
		arquivo = fopen(string,"a");//abre escrita apartir do ultimo ponto
		fprintf(arquivo,"\n| %d /",(raiz)->quantidade);
		fprintf(arquivo," %s ",(raiz)->Marca);
		fprintf(arquivo,"%s ",(raiz)->Nome);
		fprintf(arquivo,"%d /",(raiz)->ano);
		fprintf(arquivo," %dkm /",(raiz)->km_andado);
		fprintf(arquivo, "R$ %.2f |\n",(raiz)->valor);
		fclose(arquivo);//fecha escrita
		//continua ate acabar os nos direitos
		esc_arquivo((raiz)->right,arquivo,string);			
	}
}
Arvore** menor_right(Arvore *raiz){//olha menor do lado direito
	Arvore **aux = &(raiz);//recebe endereco da raiz, pra n mexer com a propria
	if((*aux)->right != NULL){//enquanto tiver na direita, vai procurando
		aux = &(*aux)->right;
		while((*aux)->left != NULL){//olha se tem lado esquerdo nos nos da direita
			aux = &(*aux)->left;
		}
	}
	return aux;//retorna o ultimo da direita
}
Arvore** maior_left (Arvore *raiz){//olha maior do lado esquero
	Arvore **aux = &(raiz);//recebe endereco da raiz, pra n mexer com a propria
	if((*aux)->left != NULL){//enquanto tiver na esquerda, vai procurando
		aux = &(*aux)->left;
		while((*aux)->right != NULL){//olha se tem lado direito nos nos da esquerda
			aux = &(*aux)->right;
		}
	}
	return aux;
}
void ler_string(char string[]){//recebe o nome do veiculo e o deixa maiusculo
	printf("\nDigite o Nome do Veiculo : ");
	fflush(stdin);
	
	gets(string);
	maiuscula(string);
}
void ler_marca(char string1[]){
	printf("\nDigite a Marca do Veiculo : ");
	fflush(stdin);
	
	gets(string1);
	maiuscula(string1);
}
void ler_ano(int *ano){//recebe o ano para o veiculo
	printf("\nDigite o Ano do Veiculo : ");
	scanf("%d",ano);
}
void ler_km(int *km_andado){//recebe os km_andados
	printf("\nDigite os Km andados : ");
	scanf("%d",km_andado);
}
void ler_valor(float *valor){//recebe o valor
	printf("\nDigite o Valor do Veiculo : ");
	scanf("%f",valor);
}
void ler_quantidade(int *quantidade){//recebe a quantidade
	printf("\nDigite quantos Veiculos serao guardados : ");
	scanf("%d",quantidade);
}
void maiuscula(char string[]){//coloca uma string em maiusculo
	int i;
	for(i = 0;i < strlen(string);i++){
		if((string[i] >= 'a') && (string[i] <= 'z')){
			string[i]-=32;
		}
	}
}
void opcao(char op[]){//soh mostra opcoes
	printf("\n\nDeseja continuar sim = s ou nao = n\n");
	fflush(stdin); //limpar buffer do teclado
	gets(op);
}
void posicao(int x, int y){//muda posicao do q vai ser printado na tela, para ficar "bonito"
	HANDLE SaidaSTD = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(SaidaSTD, coord);
}
void Menu(int *num){//menu geral
	posicao(33,2);printf("CONCESSIONARIA");
	posicao(25,2);printf("|");posicao(53,2);printf("|");
	posicao(25,1);printf("*___________________________*\n");
	posicao(25,3);printf("|___________________________|\n");
	posicao(25,4);printf("| 1 - CADASTRO DE VEICULO   |\n");
	posicao(25,5);printf("|___________________________|\n");
	posicao(25,6);printf("| 2 - CATALOGO DE VEICULOS  |\n");
	posicao(25,7);printf("|___________________________|\n");
	posicao(25,8);printf("| 3 - BUSCA DE VEICULO      |\n");
	posicao(25,9);printf("|___________________________|\n");
	posicao(25,10);printf("| 4 - VENDER VEICULO        |\n");
	posicao(25,11);printf("|___________________________|\n");
	posicao(25,12);printf("| 5 - EDITAR CADASTRO       |\n");
	posicao(25,13);printf("|___________________________|\n");
	posicao(25,14);printf("| 6 - CRIAR ARQUIVO         |\n");
	posicao(25,15);printf("|___________________________|\n");
	posicao(25,16);printf("| 7 - SAIR                  |\n");
	posicao(25,17);printf("*___________________________*\n");
	
	posicao(1,1);printf("\nDigite uma opcao : ");
	scanf("%d",num);//recebe o numero para a opcao
	getchar();
}
void Menu_1(){//menu do cadastro
	system("cls");
	posicao(28,1);printf("*__________________*\n");
 	posicao(28,2);printf("| INSERIR CADASTRO |\n");
 	posicao(28,3);printf("*__________________*\n");
	
}
void Menu_2(){//menu de visualizacao
	system("cls");
	posicao(28,1);printf("*_____________________*\n");
	posicao(28,2);printf("| VIZUALIZAR VEICULOS |\n");
	posicao(28,3);printf("*_____________________*\n");
	printf("\n\n| QUANTIDADE / VEICULO / VALOR UNITARIO |\n\n");
}
void Menu_3(){//menu de pesquisa
	system("cls");
	posicao(28,1);printf("*____________________*\n");
	posicao(28,2);printf("| PESQUISAR VEICULOS |\n");
	posicao(28,3);printf("*____________________*\n");
}
void Menu_4(){//menu de venda/excluir
	system("cls");
	posicao(28,1);printf("*__________________*\n");
	posicao(28,2);printf("| VENDA DE VEICULO |\n");
	posicao(28,3);printf("*__________________*\n");
}
void Menu_5(){//menu de edicao
	system("cls");
	posicao(48,1);printf("*__________________*\n");
	posicao(48,2);printf("| ALTERAR CADASTRO |\n");
	posicao(48,3);printf("*__________________*\n");
}
void Menu_6(){//menu de criacao de arquivo
	system("cls");
	posicao(32,2);printf("Criar Arquivo");
	posicao(25,2);printf("|");posicao(50,2);printf("|");
	posicao(25,1);printf("*________________________*\n");
	posicao(25,3);printf("|________________________|\n");
	posicao(25,4);printf("| 1 - CADASTRADOS        |\n");
	posicao(25,5);printf("|________________________|\n");
	posicao(25,6);printf("| 2 - VENDAS             |\n");
	posicao(25,7);printf("|________________________|\n");
}
int main(){
	system("color a");//muda a cor da letras do console
	int num,trigger,flag;
	char Nome[100],Marca[100],op[2],name_arquivo[100];//o nome do carro e a operacao

	char txt[] = ".txt";
	char endereco1[] = "Estoque\\";
	char endereco2[] = "Vendas\\";
	char end1[100];
	char end2[100];
	
	Arvore *estoque;//cria a raiz	
	estoque = NULL;//faz a raiz ficar vazia pra n estar pre-selecao
	Arvore *vendas;
	vendas = NULL;	
	trigger = 0;
	
	while(num != 7){//se for 7, acaba o programa
		Menu(&num);//recebe a instrucao do usuario
		switch(num){
			case 1://cadastro
				do{
					Menu_1();
					ler_string(Nome);//recebe o nome do veiculo e coloca nos parametros desejados	
					ler_marca(Marca);//recebe nome da marca
					inserir(&estoque,Nome,Marca);//cria um noh
					opcao(op);
				}while((*op == 's') || (*op =='S'));//fica rodando ate o usuario digitar algo q n seja s ou S
				break;
			case 2://lista de carros
				Menu_2();
				ordem(estoque);//chama a fucnao ordem q printa todos os nos em ordem crescente
				getch();
				break;
			case 3://busca de certo carro				
				do{
					Menu_3();
					ler_string(Nome);//recebe o nome do veiculo e coloca nos parametros desejados
					busca(estoque,Nome);//busca o "Nome" na arvore
					opcao(op);
				}while((*op == 's') || (*op =='S'));//fica rodando ate o usuario digitar algo q n seja s ou S
				break;
			case 4://excluir/vender carro
				do{
           			Menu_4();
           			ler_string(Nome);//recebe o nome do veiculo e coloca nos parametros desejados
           			opcao(op);
          			if(*op == 'n' || *op =='N'){//se for nao, nao tera a venda
          				break;
					}
            		excluir(&estoque,&vendas,Nome);//caso seja sim, tera a venda
					break;
           		}while(*op =='s' || *op =='S');
            	break;
    		case 5://editar cadastro de carro
           		Menu_5();
           		ler_string(Nome);//recebe o nome do veiculo e coloca nos parametros desejados
           		Altera(&estoque,Nome);//chama a funcao que edita o cadastro
           		break;
			case 6://criar arquivos de vendas e cadastros				
				do{
					Menu_6();
					scanf("%d",&trigger);
					printf("\nEscreva o nome para o Arquivo :\n");
					scanf("%s",&name_arquivo);
					fflush(stdin);
					
					//Ajeitando endereco
					strcat(end1,endereco1);
					strcat(end1,name_arquivo);
					strcat(end1,txt);
					strcat(end2,endereco2);
					strcat(end2,name_arquivo);
					strcat(end2,txt);
					if(trigger == 1){//estoque
						criar_arquivo(arquivo,end1,trigger);						
						esc_arquivo(estoque,arquivo,end1);
					}else if(trigger == 2){//vendas
						criar_arquivo(arquivo,end2,trigger);
						esc_arquivo(vendas,arquivo,end2);
					}
					//necessario resetar a string end1 e end2				
					strcpy(end1,"");
					strcpy(end2,"");
					trigger = 0;//reseta o trigger para neutralizar problemas futuros
					opcao(op);
				}while((*op == 's') || (*op =='S'));//fica rodando ate o usuario digitar algo q n seja s ou S
				break;		
		}
		system("cls");		
	}	
	free(vendas);
	free(estoque);
}
