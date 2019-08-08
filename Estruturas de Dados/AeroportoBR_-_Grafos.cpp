#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include<string.h>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#define MAXN 10100
#define INFINITO 1000000
#define quant_capital 27

using namespace std;
typedef pair<int, int> pii;

//colocar aqui as variaveis de todo o sistema


int processados[MAXN],processado[MAXN],a = 0;
int pontos[MAXN],z = 0;
int Sdist[MAXN];
vector<pii> viajens[MAXN];

//BANCO DE DADOS

int voos[quant_capital][quant_capital];
float valores[quant_capital][quant_capital];

char cidades[quant_capital][20] = {"RIO BRANCO","MACEIO","MACAPA","MANAUS","SALVADOR","FORTALEZA","BRASILIA","VITORIA","GOIANIA","SAO LUIS","CUIABA","CAMPO GRANDE",
	"BELO HORIZONTE","BELEM","JOAO PESSOA","CURITIBA","RECIFE","TERESINA","RIO DE JANEIRO","NATAL","PORTO ALEGRE","BOA VISTA","FLORIANOPOLIS","SAO PAULO",
	"ARACAJU","PALMAS","PORTO VELHO"};
	
int distancia[quant_capital][quant_capital] = {              
	0,	3518,	2164,	1153,	3523,	3307,	1601,	3163,	2141,	2727,	1416,	1833,	2789,	2340,	3634,	3664,	3626,	2812,	2990,	3625,	2820,	1630,	2815,	2710,	3366,	2136,	452,	
	3518,	0,	2014,	2784,	479,	728,	1487,	1283,	1664,	1235,	2310,	2359,	1445,	1683,	297,	2265,	200,	933,	1677,	434,	2782,	3097,	2409,	1934,	208,	1384,	3098,	
	2164,	2014,	0,	1056,	2005,	1457,	1796,	2549,	1872,	808,	1826,	2315,	2354,	332,	1969,	2840,	2009,	1082,	2693,	1878,	3347,	1113,	3087,	2668,	1973,	1184,	1727,	
	1153,	2784,	1056,	0,	2610,	2389,	1938,	2870,	1914,	1751,	1454,	2018,	2559,	1296,	2825,	2736,	2837,	1924,	2854,	2769,	3136,	665,	2985,	2692,	2678,	1516,	761,
	3523,	479,	2005,	2610,	0,	1028,	1059,	837,	1229,	1324,	1920,	1908,	967,	1690,	765,	1787,	676,	996,	1212,	879,	2306,	3015,	1934,	1457,	274,	1113,	2814,	
	3307,	728,	1457,	2389,	1028,	0,	1688,	1854,	1859,	653,	2334,	2552,	1895,	1136,	555,	2673,	628,	498,	2193,	434,	3218,	2569,	2861,	2372,	819,	1302,	2861,	
	1601,	1487,	1796,	1938,	1059,	1688,	0,	946,	178,	1527,	880,	882,	621,	1597,	1717,	1081,	1657,	1314,	933,	1777,	1621,	2505,	1315,	873,	1288,	619,	1908,	
	3163,	1283,	2549,	2870,	837,	1854,	946,	0,	1028,	2023,	1752,	1494,	383,	2278,	1580,	1082,	1483,	1714,	417,	1707,	1542,	3402,	1167,	748,	1096,	1411,	2843,	
	2141,	1664,	1872,	1914,	1229,	1859,	178,	1028,	0,	1666,	740,	704,	668,	1697,	1895,	972,	1834,	1470,	940,	1955,	1499,	2508,	1216,	812,	1464,	724,	1816,	
	2727,	1235,	808,	1751,	1324,	653,	1527,	2023,	1666,	0,	1947,	2289,	1935,	483,	1164,	2602,	1209,	328,	2270,	1071,	3146,	1919,	2825,	2352,	1229,	967,	2279,	
	1416,	2310,	1826,	1454,	1920,	2334,	880,	1752,	740,	1947,	0,	564,	1375,	1782,	2501,	1304,	2457,	1865,	1580,	2530,	1682,	2112,	1545,	1329,	2124,	1032,	1140,	
	1833,	2359,	2315,	2018,	1908,	2552,	882,	1494,	704,	2289,	564,	0,	1117,	2218,	2598,	777,	2534,	2136,	1213,	2659,	1118,	2675,	1004,	892,	2155,	1322,	1641,	
	2789,	1445,	2354,	2559,	967,	1895,	621,	383,	668,	1935,	1375,	1117,	0,	2114,	1730,	821,	1643,	1655,	341,	1836,	1343,	3123,	974,	491,	1240,	1175,	2481,	
	2340,	1683,	332,	1296,	1690,	1136,	1597,	2278,	1697,	483,	1782,	2218,	2114,	0,	1640,	2668,	1678,	750,	2456,	1552,	3194,	1437,	2909,	2467,	1645,	979,	1891,	
	3634,	297,	1969,	2825,	765,	555,	1717,	1580,	1895,	1164,	2501,	2598,	1730,	1640,	0,	2549,	103,	909,	1972,	154,	3071,	3075,	2698,	2221,	491,	1523,	3207,	
	3664,	2265,	2840,	2736,	1787,	2673,	1081,	1082,	972,	2602,	1304,	777,	821,	2668,	2549,	0,	2463,	2365,	677,	2650,	548,	3376,	252,	338,	2060,	1691,	2416,	
	3626,	200,	2009,	2837,	676,	628,	1657,	1483,	1834,	1209,	2457,	2534,	1643,	1678,	103,	2463,	0,	936,	1978,	255,	2982,	3109,	2608,	2133,	403,	1498,	3196,	
	2812,	933,	1082,	1924,	996,	498,	1314,	1714,	1470,	328,	1865,	2136,	1655,	750,	909,	2365,	936,	0,	1984,	846,	2913,	2174,	2577,	2095,	907,	837,	2366,	
	2990,	1677,	2693,	2854,	1212,	2193,	933,	417,	940,	2270,	1580,	1213,	341,	2456,	1972,	677,	1878,	1984,	0,	2091,	1125,	3436,	750,	359,	1482,	1511,	2713,	
	3625,	434,	1878,	2769,	879,	434,	1777,	1707,	1955,	1071,	2530,	1259,	1836,	1552,	154,	2650,	255,	846,	2091,	0,	3179,	2989,	2808,	2326,	611,	1529,	3185,	
	2820,	2782,	3347,	3136,	2306,	3218,	1621,	1542,	1499,	3146,	1682,	1118,	1343,	3194,	3071,	548,	2982,	2913,	1125,	3179,	0,	3793,	376,	853,	2580,	2222,	2711,	
	1630,	3097,	1113,	665,	3015,	2569,	2505,	3402,	2508,	1919,	2112,	2675,	3123,	1437,	3075,	3376,	3109,	2174,	3436,	2989,	3793,	0,	3626,	3306,	3030,	1997,	1338,	
	2815,	2409,	3087,	2985,	1934,	2861,	1315,	1167,	1216,	2825,	1545,	1004,	974,	2909,	2698,	252,	2608,	2577,	750,	2808,	376,	3626,	0,	489,	2207,	1931,	2645,	
	2710,	1934,	2668,	2692,	1457,	2372,	873,	748,	812,	2352,	1329,	892,	491,	2467,	2221,	338,	2133,	2095,	359,	2326,	853,	3306,	489,	0,	1730,	1491,	2468,	
	3366,	208,	1973,	2678,	274,	819,	1288,	1096,	1464,	1229,	2124,	2155,	1240,	1645,	491,	2060,	403,	907,	1482,	611,	2580,	3030,	2207,	1730,	0,	1233,	2951,	
	2136,	1384,	1184,	1516,	1113,	1302,	619,	1411,	724,	967,	1032,	1322,	1175,	979,	1523,	1691,	1498,	837,	1511,	1529,	2222,	1997,	1931,	1491,	1233,	0,	1717,	
	452,	3098,	1727,	761,	2814,	2861,	1908,	2843,	1816,	2279,	1140,	1641,	2481,	1891,	3207,	2416,	3196,	2366,	2713,	3185,	2711,	1338,	2645,	2468,	2951,	1717,	0
	};
//_________________________________________________________________

//lista de todas as funcoes
void Mapa();
void Menu(int *opcao);
void Menu1();
void Menu2();
void Menu3();
void Menu4();
void Menu5();
void continuar();
void inserir();
void boizao();
void Mapa();
void ordem();
void Dijkstra();
//______________________________
void Menu(int *opcao){
	system("cls");
	printf("       _______________________________________________________________________\n");
	printf("      |                                                                       |\n");       
	printf("      |      ___________________________________________________________      |\n");
	printf("      |     |                     CONTROLE DE VOO                       |     |\n");
	printf("      |     |___________________________________________________________|     |\n");
	printf("      |                                                                       |\n");
	printf("      |                                                                       |\n");
	printf("      |                      |--------->MENU<--------|                        |\n");
	printf("      |                      |_______________________|                        |\n");
	printf("      |                      | 1 - INSERIR VOO(s)    |                        |\n");
	printf("      |                      | 2 - EDITAR VOO        |                        |\n");
	printf("      |                      | 3 - MOSTRAR MAPA      |                        |\n");
	printf("      |                      | 4 - LISTAR VOOS       |                        |\n");
	printf("      |                      | 5 - ESCOLHA DE VOO    |                        |\n");
	printf("      |                      | 0 - FINALIZAR         |                        |\n");              
	printf("      |                      |_______________________|                        |\n");
	printf("      |                                                                       |\n");
	printf("      |                                                                       |\n");
	printf("      |                                                                       |\n");
	printf("      |_______________________________________________________________________|\n");              
	printf("                             INFORME A SUA OPCAO: ");
	scanf("%d",opcao);//recebe o numero para a opcao
}
void Menu_1(){
	system("cls");
    printf("\n _____________________________________________________________________________");
    printf("\n|                   VOCE ESCOLHEU INSERIR UMA ROTA DE VOO                     |");
    printf("\n|_____________________________________________________________________________|\n\n");
    Mapa();
}
void Menu_2(){
	system("cls");
	printf("\n _____________________________________________________________________________");
	printf("\n|                   VOCE ESCOLHEU EDITAR UMA ROTA DE VOO!                     |");
	printf("\n|_____________________________________________________________________________|\n\n");
}
void Menu_3(){
	system("cls");
	printf("\n _____________________________________________________________________________");
	printf("\n|                       VOCE ESCOLHEU VISUALIZAR O MAPA!                      |");
	printf("\n|_____________________________________________________________________________|\n\n");
}
void Menu_4(){
	system("cls");
	printf("\n _____________________________________________________________________________");
	printf("\n|                      VOCE ESCOLHEU VISUALIZAR OS VOOS!                      |");
	printf("\n|_____________________________________________________________________________|\n\n");
}
void Menu_5(){
	system("cls");
	printf("\n _____________________________________________________________________________");
	printf("\n|                  ESCOLHA OS PONTO DE PARTIDA E DE CHEGADA                   |");
	printf("\n|_____________________________________________________________________________|\n\n");
	Mapa();
}
void continuar(){
	
	printf("\n|                   PRESSIONE QUALQUER TECLA PARA CONTINUAR                   |");
	printf("\n|_____________________________________________________________________________|\n");
	getch();
}
void inserir(){
	int i,quant,destino,partida;
	float valor;
	printf("Quantidades de voos a serem inseridos: ");
	scanf("%d",&quant);	
	//colocar todo o trabalho aqui
	
	for(i = 0;i < quant;i++){
		printf("Qual a Cidade de Partida?\n");
		scanf("%d",&partida);
		printf("Qual a Cidade Destino?\n");
		scanf("%d",&destino);	
		printf("Qual o valor da viajem?\n");	
		scanf("%f",&valor);
		
		viajens[partida-1].push_back( pii(distancia[partida-1][destino-1], destino-1) );
		
		voos[partida-1][destino-1] = 1;
		valores[partida-1][destino-1] = valor;
		
		if(quant > 1){
			system("cls");
			printf("\n _____________________________________________________________________________");
			printf("\n|                   VOCE ESCOLHEU INSERIR UMA ROTA DE VOO                     |");
			printf("\n|_____________________________________________________________________________|\n\n");
			Mapa();
		}
	}
	
	//____________________________________
	printf("\n _____________________________________________________________________________");
    printf("\n|                     ROTA DE VOO CADASTRADA COM SUCESSO                      |");
	continuar();
}
void boizao(){//editar valor do voo
	//VARIAVEIS
	int p1,p2;//numero das capitais
	//________
	//mostra os voos e o Mapa
	Mapa();
	ordem();	
	//________________________
	//edita
	printf("\nDigite a Partida do Voo:");
	scanf("%d",&p1);
	printf("\nDigite a Chegada do Voo:");
	scanf("%d",&p2);
	if(voos[p1-1][p2-1] != 1){
		printf("\n _____________________________________________________________________________");
	    printf("\n|                           ROTA DE VOO NAO ENCONTRADA                        |");
	}else{
		system("cls");
		printf("\n _____________________________________________________________________________");
		printf("\n                   VOCE ESCOLHEU EDITAR [%s - %s]    ",cidades[p1-1],cidades[p2-1]);
		printf("\n_____________________________________________________________________________\n\n");
		printf("\nO Valor Atual da Passagem : %.2f",valores[p1-1][p2-1]);
		printf("\nNovo Valor:");
		scanf("%f",&valores[p1-1][p2-1]);
		
		printf("\n");		
		//________________________
		//fim
	
		printf("\n _____________________________________________________________________________");
	    printf("\n|                      ROTA DE VOO EDITADA COM SUCESSO                        |");
	}
	
	//______________
}
void Mapa(){
    printf("________________________________________________________________________________________________________________________\n\n");
	printf("\n\n\t\t                        LISTA DAS CAPITAIS BRASILEIRAS\n");
    printf("________________________________________________________________________________________________________________________\n\n");
    printf("\n");
	printf("\t1 - RIO BRANCO         2 - MACEIO             3 - MACAPA               4 - MANAUS               5 - SALVADOR       \n\n");
	printf("\t6 - FORTALEZA          7 - BRASILIA           8 - VITORIA              9 - GOIANIA              10 - SAO LUIS       \n\n");
	printf("\t11 - CUIABA            12 - CAMPO GRANDE      13 - BELO HORIZONTE      14 - BELEM               15 - JOAO PESSOA   \n\n");
	printf("\t16 - CURITUBA          17 - RECIFE            18 - TERESINA            19 - RIO DE JANEIRO      20 - NATAL          \n\n");
	printf("\t21 - PORTO ALEGRE      22 - BOA VISTA         23 - FLORIANOPOLIS       24 - SAO PAULO           25 - ARACAJU        \n\n");	
	printf("\t26 - PALMAS            27 - PORTO VELHO\n\n");
    printf("________________________________________________________________________________________________________________________\n\n");
    printf("\n");	
}
void ordem(){
	int i,j;
	//MOSTRAR TODOS OS VOOS
	for(i = 0;i < quant_capital;i++){
		for(j = 0;j < quant_capital;j++){
			if(voos[i][j] == 1){
				printf("%s",cidades[i]);
				printf("     PARA     ");
				printf("%s",cidades[j]);
				printf("   R$%.2f\n\n",valores[i][j]);
			}
		}
	}
}
void Dijkstra(){
	//variaveis saudaveis
	int i;
	int resposta = 0;
	int atual = 0;
	int cidade_inicio;
	int cidade_fim;
	//codigo de procura de menor caminho aqui
	printf("\nDiga qual a cidade de partida : ");
	scanf("%d",&cidade_inicio);
	printf("Diga qual a cidade de chegada : ");
	scanf("%d",&cidade_fim);
	
	cidade_inicio = cidade_inicio -1;
	cidade_fim = cidade_fim -1;
	
	for(i = 0;i < quant_capital;i++){
		Sdist[i+1] = INFINITO;
	}
	
	Sdist[cidade_inicio] = 0;
	
	priority_queue< pii, vector<pii>, greater<pii> > fila; //Fila de prioridade onde o menor fica no topo
	fila.push( pii(Sdist[cidade_inicio],cidade_inicio) ); // primeiro elemento com a distancia do S e o proprio S
	
	while(true){
		int da_vez = -1;  //nao existe vertice -1 nesse sistema
		
		while(!fila.empty()){//ate a fila ficar vazia
			
			atual = fila.top().second;//atual recebe o vertice de cima da fila de prioridade
			fila.pop();
			
			if(!processado[atual]){//vertice ainda n processado
				da_vez = atual;
				processados[a] = da_vez;//com isso, tenho um vetor com os numeros do processado, para que no futuro possa negativar
				a++;
				break;
			}
		}
		if(da_vez == -1){ // se nao achou ngm, eh o fim do algoritmo
			break;
		}
		
		processado[da_vez] = true; //marcando pra n voltar neste vertice
		
		for(i = 0;i < (int)viajens[da_vez].size();i++){
			
			int dist = viajens[da_vez][i].first;
			int atual = viajens[da_vez][i].second;
			
			if(Sdist[atual] > Sdist[da_vez] + dist){
				Sdist[atual] = Sdist[da_vez] + dist;
				fila.push( pii(Sdist[atual], atual) );
				pontos[z] = da_vez;
			}
		}
		for(i = 0;i < a;i++){
			processado[processados[i]] = false;	
		}
	}
	
	resposta = Sdist[cidade_fim];
	//printando rota de voo
	if(resposta == 0){//se n encontrou
		printf("\n _____________________________________________________________________________");
		printf("\n|                        ROTA DE VOO NAO ENCONTRADA                           |");
	}else{//se encontrou
		printf("\nMenor tempo : %d\n",resposta);
		printf("\n\n");//mostrar rota de voo e menor caminho
		printf("\n _____________________________________________________________________________");
		printf("\n|                     ROTA DE VOO ENCONTRADA COM SUCESSO                      |");	
	}
	//___________________________________
	//zeranco o priority queue
	fila = priority_queue< pii, vector<pii>, greater<pii> >();
	//__________________________________
}
void exit(){
	printf("\n _____________________________________________________________________________");
	printf("\n|                     VOCE OPTOU POR FINALIZAR O PROGRAMA!                    |");
	printf("\n|                      PRESSIONE QUALQUER TECLA PARA SAIR                     |");
	printf("\n|_____________________________________________________________________________|\n");
	getch();
}
void false_option(){
	printf("\n _____________________________________________________________________________");
	printf("\n|                       OPCAO INVALIDA! TENTE NOVAMENTE                       |");
	printf("\n|                   PRESSIONE QUALQUER TECLA PARA CONTINUAR                   |");
	printf("\n|_____________________________________________________________________________|\n");
	getch();
}
int main(){
	
	int fim;
	int opcao;
	fim = 0;
	opcao = 0;

	//inicializando os voos
	for(int i = 0;i < quant_capital;i++){
		for(int j = 0;j < quant_capital;j++){
			voos[i][j] = 0;
		}
	}
	
	//{colocar aqui a funcao de load()}
	
	while(fim == 0){
		Menu(&opcao);
		
		if(opcao > 6){
			false_option();
		}
		
		switch(opcao){
			case 1://adicionar voo
				Menu_1();
				inserir();				
				break;
			
			case 2://editar voo
				Menu_2();
				boizao();
				continuar();
				break;
			
			case 3://mostrar o mapa
				Menu_3();
				Mapa();
				printf("\n _____________________________________________________________________________");
    			printf("\n|                     VISUALIZACAO DO MAPA COM SUCESSO                        |");
				continuar();
				break;
				
			case 4://listar voo
				Menu_4();
				ordem();
				printf("\n _____________________________________________________________________________");
				printf("\n|                   OS VOOS FORAM VISUALIZADOS COM SUCESSO!                   |");
				continuar();
				break;
				
			case 5://escolha de voo
				Menu_5();
				Dijkstra();
				continuar();
				break;				
								
			case 0://Fechar software
				exit();
				fim = 1;
				break;				
		}		
	}
}
