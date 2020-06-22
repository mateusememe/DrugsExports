/*
	@author: "Mateus Mendonça Monteiro"
	@author: "Ariel Araujo Oliveira Menezes "
	@author: "Christian Ferreira dos Santos"
	
*/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include "ListDupEncad.h"
#include "visual.h"

#define F "\tFeminino\n"
#define Man "\tMasculino\n"
//protótipo da função de execução geral do código
void execute(TpDescritor Descritor, FILE *ptr);
//Função feita para Mostrar os dados de forma ordenada
void InserirOrdenadoPais(TpDescritor &Descritor, FILE *PtrArq){
	TpPais P, *List, *aux, *Country;
	TpMedicamentos M, *auxMed;
	TpUsuario U;
	
	fscanf(PtrArq,"%[^;];%c;%[^;];%[^;];%[^\n]\n",&U.user,&U.sexo,&M.nomeMed,&U.data,&P.nomePais);
	clear();
	clsInside(WHITE,"| Insercao Ordenada |");
	LoadingInput();
	while (!feof(PtrArq)){
		List = NovaCaixaPais(P);
		
		//Inserindo o primeiro elem
		if(Descritor.inicio == NULL){
			List->med = InsereRemedio(List->med, M, U);
			Descritor.inicio = List;
			Descritor.fim = List;
		}
		//Inserindo o primeiro elem
	    else{
	    	aux = verificaLista(Descritor, List->nomePais);
			if(aux == NULL){ 
				//se o nome do pais nï¿½o existe na lista, entÃ£o busca uma forma de inserir
				
				//Inserido ela no Inicio
				if(stricmp(P.nomePais,Descritor.inicio->nomePais) < 0)
				{
					List->med = InsereRemedio(List->med, M, U);
					List->prox = Descritor.inicio;
					Descritor.inicio->ant = List;
					Descritor.inicio = List;	
				}
				else
				{
					//Inserido No Fim
					if(stricmp(P.nomePais,Descritor.fim->nomePais) > 0)
					{
						List->med = InsereRemedio(List->med, M, U);
						List->ant = Descritor.fim;
						Descritor.fim->prox = List;
						Descritor.fim = List;
					}
					else
					{
						//Inserido no meio
						aux = Descritor.inicio->prox;
						while(stricmp(P.nomePais, aux->nomePais) > 0)
							aux = aux->prox;
						
						aux->ant->prox = List;
						List->ant = aux->ant;
						List->prox = aux;
						aux->ant = List;
						List->med = InsereRemedio(List->med,M,U);

					}
				}
			}
			else // se o nome do pais ja existe na lista..... se atualiza as informaÃ§Ãµes dele.
			{
				auxMed = verificaMedicamento(aux->med,M.nomeMed);
				//Caso em que paÃ­s existe e med existe
				if(auxMed != NULL)
					auxMed->usuario = InsereUsuario(auxMed->usuario,U);
				//Caso em que paÃ­s existe e med nn existe
				else
					aux->med = InsereRemedio(aux->med, M, U);	
			}
		}
		fscanf(PtrArq,"%[^;];%c;%[^;];%[^;];%[^\n]\n",&U.user,&U.sexo,&M.nomeMed,&U.data,&P.nomePais);
	}
	clear();
	drawScreen(WHITE);
	clsInside(WHITE,"| Insercao Ordenada |");
	put_on_xy(30,12,"Insercao Concluida :)");
	infoExitScreen();
	getch();
}

//Função que exibe um relatório de todos os paises existentes na lista
void RelatPaises(TpDescritor Desc){
	TpPais *P = Desc.inicio;
	int y = 4, x = 5;
	char aux[250];
	clsInside(WHITE,"| Relatorio Paises |");
	strcpy(aux,"\t");
	if(P == NULL)
		put_on_xy(30,12,"Lista Vazia :c");
	else
	{
		while (P != NULL){
			textcolor(YELLOW);
			put_on_xy(5,3,"Lista de Paises:");
			textcolor(BROWN);
			if(x < 51){
				strcat(aux,P->nomePais);
				put_on_xy(x,y,aux);
				x+=15;
				strcpy(aux,"\t\0");
			}
			else if (x >= 51){
				//clsInside(WHITE,"| Relatorio Paises |");
				textcolor(BROWN);
				y++;
				x=5;
			}
			P = P->prox;
		}
	}
	put_on_xy(1,24,"\r");
	textcolor(YELLOW);
	put_on_xy(34,24,"Aperte qualquer botao para voltar ao menu[\*]"); gotoxy(79,24);
	getch();
}
//Sobrecarga de funções que exclui um pais existente na lista
void ExcluiPais(TpDescritor &Desc){
	char NomePais[100];
	TpPais *P;
	clsInside(WHITE,"| Exclusao de Paises |");
	if(Desc.inicio == NULL){
		put_on_xy(30,12,"Lista Vazia :c");
		put_on_xy(34,24,"Aperte qualquer botao para voltar ao menu[\*]"); gotoxy(79,24);
		getch();
	}
	else{
		put_on_xy(7,24,"Aperte [Enter] para voltar ao menu, caso nao queira mais excluir paises"); gotoxy(79,24);
		put_on_xy(20,12,"Digite o nome do pais que deseja deletar: ");
		gotoxy(20,13);
		getStr(NomePais);
		clear();
		while(strcmp(NomePais,"\0") != 0){
			P = verificaLista(Desc,NomePais);
			if(P != NULL){
				//se for o primeiro elem
				if(P->ant == NULL){
					//se for o primeiro e unico elem
					if(P->prox == NULL){
						Desc.inicio = NULL;
						Desc.fim = NULL;
						delete(P);
					}
					//se for somente primeiro elem
					else{
						P->prox->ant = NULL;
						Desc.inicio = P->prox;
						delete(P);
					}
				}
				//se for o ultimo elem
				else if(P->prox == NULL){
					P->ant->prox = NULL;
					Desc.fim = P->ant;
					delete(P);
				}
				//se for um elem qualquer
				else{
					P->ant->prox = P->prox;
					P->prox->ant = P->ant;
					delete(P);
				}
				clsInside(WHITE,"| Exclusao de Paises |");
				gotoxy(20,13); printf("Pais \"%s\" deletado!",NomePais);
				put_on_xy(24,23,"Aperte [Enter] duas vezes para voltar ao menu ou aperte");
				put_on_xy(36,24,"qualquer botao para excluir mais paises[\*]"); gotoxy(79,24);
				getch();	
			}
			else{
				clsInside(WHITE,"| Exclusao de Paises |");
				put_on_xy(30,13,"PAIS NAO ENCONTRADO!");
				put_on_xy(32,23,"Aperte [Enter] duas vezes para voltar ao menu"); gotoxy(79,24);
				put_on_xy(28,24,"ou aperte qualquer botao para excluir um pais[\*]"); gotoxy(79,24);
				getch();
			}
			clsInside(WHITE,"| Exclusao de Paises |");
			put_on_xy(7,24,"Aperte [Enter] para voltar ao menu, caso nao queira mais excluir paises"); gotoxy(79,24);
			
			put_on_xy(20,12,"Digite o nome do pais que deseja deletar: "); gotoxy(20,13);
			getStr(NomePais);
		}
		
	}

}

void ExcluiPais(TpDescritor &Desc, char NomePais[]){
	TpPais *P;

	P = verificaLista(Desc,NomePais);
	if(P != NULL){
		//se for o primeiro elem
		if(P->ant == NULL){
			//se for o primeiro e unico elem
			if(P->prox == NULL){
				Desc.inicio = NULL;
				Desc.fim = NULL;
				delete(P);
			}
			//se for somente primeiro elem
			else{
				P->prox->ant = NULL;
				Desc.inicio = P->prox;
				delete(P);
			}
		}
		//se for o ultimo elem
		else if(P->prox == NULL){
			P->ant->prox = NULL;
			Desc.fim = P->ant;
			delete(P);
		}
		//se for um elem qualquer
		else{
			P->ant->prox = P->prox;
			P->prox->ant = P->ant;
			delete(P);
		}
	}
}
//Função dedicada a excluir um medicamento determinado pelo usuario de todos os paises, caso ao excluir o mesmo, e algum dos paises ficar sem medicamentos, o mesmo é excluido
void ExcluiMedicamento(TpDescritor &Desc){
	char NomeMed[200], DelPais[200];
	TpPais *P;
	TpMedicamentos *M, *mAtual, *mAnt;
	clsInside(WHITE,"| Exclusao de Medicamentos |");
	if(Desc.inicio == NULL){
		put_on_xy(30,12,"Lista Vazia :c");
		put_on_xy(34,24,"Aperte qualquer botao para voltar ao menu[\*]"); gotoxy(79,24);
		getch();
	}
	else{
		put_on_xy(2,24,"Aperte [Enter] para voltar ao menu, caso nao queira mais excluir Medicamentos");
		put_on_xy(16,12,"Digite o nome do Medicamento que deseja deletar: "); gotoxy(20,13);
		getStr(NomeMed);
		while(strcmp(NomeMed,"\0") != 0){
			P = Desc.inicio;
			while(P != NULL){
				M = P->med;
				mAnt = NULL;
				if(M != NULL){
					if(stricmp(M->nomeMed,NomeMed) == 0){
						clsInside(WHITE,"| Exclusao de Medicamentos |");
						gotoxy(15,12); printf("Medicamento \"%s\" Excluido de \"%s\" :) ",NomeMed,P->nomePais);
						P->med = M->prox;
						delete(M);
						put_on_xy(24,23,"Aperte [Enter] duas vezes para voltar ao menu ou aperte");
						put_on_xy(30,24,"qualquer botao para excluir mais Medicamentos[\*]"); gotoxy(79,24);
						getch();
					}
					else{
						mAtual = M;
						while(stricmp(mAtual->nomeMed,NomeMed) != 0 && mAtual->prox != NULL){
							mAnt = mAtual;
							mAtual = mAtual->prox;
						}
						if(stricmp(mAtual->nomeMed,NomeMed) == 0){
							clsInside(WHITE,"| Exclusao de Medicamentos |");
							gotoxy(15,12); printf("Medicamento \"%s\" Excluido de \"%s\" :) ",NomeMed,P->nomePais);
							mAnt->prox = mAtual->prox;
							delete(mAtual);
							put_on_xy(32,23,"Aperte [Enter] duas vezes para voltar ao menu"); gotoxy(79,24);
							put_on_xy(16,24,"ou aperte qualquer botao para excluir mais um Medicamento[\*]"); gotoxy(79,24);
							getch();
						}
					}
					if(P->med == NULL){
						strcpy(DelPais,P->nomePais);
						ExcluiPais(Desc,P->nomePais);
						clsInside(WHITE,"| Exclusao de Medicamentos |");
						put_on_xy(18,12,"Lista de Medicamentos vazia, excluindo pais...");
						gotoxy(20,13);printf("* * * Pais \"%s\" excluido! * * *",DelPais);
						put_on_xy(32,23,"Aperte [Enter] duas vezes para voltar ao menu"); gotoxy(79,24);
						put_on_xy(18,24,"ou aperte qualquer botao para excluir mais um Medicamento[\*]"); gotoxy(79,24);
						getch();
					}
				}
				else if(P->prox == NULL){
					clsInside(WHITE,"| Exclusao de Medicamentos |");
					put_on_xy(20,13,"MEDICAMENTO NAO ENCONTRADO! :c");
					put_on_xy(32,23,"Aperte [Enter] duas vezes para voltar ao menu"); gotoxy(79,24);
					put_on_xy(30,24,"ou aperte qualquer botao para Consultar[\*]"); gotoxy(79,24);
					getch();
				}
				P = P->prox;
			}
			clsInside(WHITE,"| Exclusao de Medicamentos |");
			put_on_xy(2,24,"Aperte [Enter] para voltar ao menu, caso nao queira mais excluir Medicamentos"); gotoxy(79,24);
			put_on_xy(20,12,"Digite o nome do Medicamento que deseja deletar: ");
			gotoxy(20,13);
			getStr(NomeMed);
		}
	}
}
//Função Feita para gerar um arquivo texto com os dados das listas
void GeraArqTxt(TpDescritor Descritor){
	TpPais *P;
	TpMedicamentos *M;
	TpUsuario *U;
	
	FILE *ptr = fopen("Relatorio.txt","w+");

	P = Descritor.inicio;
	if(P == NULL){
		clsInside(WHITE,"| Gerador de Arquivo .txt |");
		put_on_xy(30,12,"Lista Vazia :c");
		infoExitScreen(); gotoxy(79,24);
		getch();
	}else{
		clsInside(WHITE,"| Gerador de Arquivo .txt |");
		LoadingCreateArchive();
		
		while (P != NULL){
			strcat(P->nomePais,"\n");
			fprintf(ptr,P->nomePais);
			M = P->med;
			fprintf(ptr,F);
			while (M != NULL){
				U = M->usuario;
				while (U != NULL){
					if(U->sexo == 'F'){
						strcat(U->user,"\n");
						fprintf(ptr,"\t\tUsuÃ¡rio: ");
						fprintf(ptr,U->user);	
					}
					U = U->prox;
				}
				M = M->prox;
			}
			fprintf(ptr,"\n");
			M = P->med;
			fprintf(ptr,Man);
			while (M != NULL){
				U = M->usuario;
				while (U != NULL){
					if(U->sexo == 'M'){
						strcat(U->user,"\n");
						fprintf(ptr,"\t\tUsuÃ¡rio: ");
						fprintf(ptr,U->user);	
					}
					U = U->prox;
				}
				M = M->prox;
			}
			P = P->prox;
			fprintf(ptr,"\n");
		}
		clsInside(WHITE,"| Gerador de Arquivo .txt |");
		put_on_xy(10,12,"Arquivo texto Gerado na pasta do programa :)");
		put_on_xy(10,13,"voce pode conferir o resultado em \"Relatorio.txt\" ");
		
		infoExitScreen();
		getch();
		fclose(ptr);

	}
	
}
//Função feita para consultar a lista de medicamentos de um determinado pais
void ConsultaPais(TpDescritor Desc){

	char NomePais[200];
	TpPais *Lista;
	TpMedicamentos *Med;
	Lista = Desc.inicio;
	int x = 9;
	clsInside(WHITE,"| Consulta Paises |");
	if(Lista == NULL){
		put_on_xy(30,12,"Lista Vazia :c");
		put_on_xy(32,23,"Aperte [Enter] duas vezes para voltar ao menu");
		put_on_xy(27,24,"ou aperte qualquer botao para consultar um pais[\*]"); gotoxy(79,24);
		getch();
	}
	else{
		put_on_xy(6,24,"Aperte [Enter] para voltar ao menu, caso nao queira mais Consultar Paises"); gotoxy(79,24);
		put_on_xy(10,6,"Digite o Pais para consultar os Medicamentos: "); gotoxy(10,7);
		getStr(NomePais);
		while(strcmp(NomePais,"\0") != 0){
			Lista = verificaLista(Desc,NomePais);
			if(Lista != NULL){
				clsInside(WHITE,"| Consulta Paises |");
				put_on_xy(11,6,"DADOS Encontrados: ");
				gotoxy(15,7); printf("\tNome do Pais: %s",Lista->nomePais);
				Med = Lista->med;
				gotoxy(15,8); printf("\tMedicamentos: ");
				while(Med != NULL){		
					gotoxy(15,x); printf("\t\t%s",Med->nomeMed);
					Med = Med->prox;
					x++;						
				}
				put_on_xy(32,23,"Aperte [Enter] duas vezes para voltar ao menu");
				put_on_xy(27,24,"ou aperte qualquer botao para consultar um pais[\*]"); gotoxy(79,24);
				getch();
				x = 9;
			}
			else{
				clsInside(WHITE,"| Consulta Paises |");
				put_on_xy(30,13,"PAIS NAO ENCONTRADO!");
				put_on_xy(32,23,"Aperte [Enter] duas vezes para voltar ao menu");
				put_on_xy(27,24,"ou aperte qualquer botao para consultar um pais[\*]"); gotoxy(79,24);
				getch();
			}
			
			clsInside(WHITE,"| Consulta Paises |");
			put_on_xy(6,24,"Aperte [Enter] para voltar ao menu, caso nao queira mais Consultar paises");
			put_on_xy(10,6,"Digite o Pais para consultar os Medicamentos: "); gotoxy(10,7);
			getStr(NomePais);		
		}	
	}
}
//Função feita para consultar a lista de usuários de um determinado medicamento por paises.
void ConsultaMed(TpDescritor Desc){
	
	char NomeMed[200];
	TpPais *P, *aux;
	TpUsuario *U;
	TpMedicamentos *Med;
	int x = 7;
	clsInside(WHITE,"| Consulta Medicamentos |");
	if(Desc.inicio == NULL){
		put_on_xy(30,12,"Lista Vazia :c");
		put_on_xy(32,23,"Aperte [Enter] duas vezes para voltar ao menu");
		put_on_xy(21,24,"ou aperte qualquer botao para consultar um Medicamento[\*]"); gotoxy(79,24);
		getch();
	}
	else{	
		clsInside(WHITE,"| Consulta Medicamentos |");
		put_on_xy(12,24,"Aperte [Enter] para voltar ao menu, caso nao queira mais Consultar"); gotoxy(79,24);
		put_on_xy(10,3,"Digite o Medicamento para consultar os Usuarios: "); gotoxy(12,4);
		getStr(NomeMed);
		while (strcmp(NomeMed,"\0") != 0){
			P = Desc.inicio;
			while(P != NULL){
				Med = BuscaMed(P->med,NomeMed);
				if(Med != NULL){
					clsInside(WHITE,"| Consulta Medicamentos |");
					U = Med->usuario;
					put_on_xy(26,23,"Para vizualizar o proximo Pais que contenha usuarios");
					put_on_xy(32,24,"deste Medicamento Pressione qualquer botao [\*]"); gotoxy(79,24);
					gotoxy(10,6); printf("Usuarios de [%s] encontrados no Pais [%s]:",NomeMed,P->nomePais);
					while (U != NULL){
						gotoxy(15,x++); printf("Usuario: %s",U->user);	
						U = U->prox;
					}
					getch();
					x = 7;
				}
				P = P->prox;
			}
			if(P == NULL && Med == NULL){
				clsInside(WHITE,"| Consulta Medicamentos |");
				put_on_xy(15,11,"Medicamento nao encontrado em mais nenhum pais :c");
				put_on_xy(15,12,"ou nao encontrado em nenhum dos paises");
				put_on_xy(24,23,"Aperte [Enter] duas vezes para voltar ao menu ou aperte");
				put_on_xy(31,24,"qualquer botao para consultar um Medicamento[\*]"); gotoxy(79,24);
				getch();
			}
			clsInside(WHITE,"| Consulta Medicamentos |");
			put_on_xy(25,24,"Pressione qualquer botao para consultar novamente[\*]");
			put_on_xy(10,3,"Digite o Medicamento para consultar os Usuarios: "); gotoxy(12,4);
			getStr(NomeMed);
		}
		
	}
}
//Função do menu de opções
char Menu(){
	
	clear();
	drawScreen(WHITE);
	lilScreenTitle();
	
	put_on_xy(20,10,"[A] Inserir Dados");
	
	put_on_xy(20,11,"[B] Relatorios de Paises");
	
	put_on_xy(20,12,"[C] Excluir Pais");
	
	put_on_xy(20,13,"[D] Excluir Medicamento"); 
	
	put_on_xy(20,14,"[E] Gerar Relatorio em Arquivo Texto"); 
	
	put_on_xy(20,15,"[F] Consulta Pais");
	
	put_on_xy(20,16,"[G] Consulta Medicamento");

	put_on_xy(20,17,"[H] Informacoes Extras");
	
	put_on_xy(20,18,"[Esc] Fechar Programa");

	put_on_xy(20,20,"Digite uma opcao > "); gotoxy(41,20);
	
	return toupper(getch());
}
//Função de execução geral do código
void execute(TpDescritor Descritor, FILE *ptr){
	char opc;
	do{
		opc = Menu();
		switch(opc)
		{
			case 'A':
				clear();
				InserirOrdenadoPais(Descritor,ptr);
				break;		
			case 'B':
				clear();
				RelatPaises(Descritor);
				break;
	
			case 'C':
				clear();
				ExcluiPais(Descritor);
				break;
	
			case 'D':
				clear();
				ExcluiMedicamento(Descritor);
				break;
			
			case 'E':
				clear();
				GeraArqTxt(Descritor);
				break;
			
			case 'F':
				clear();
				ConsultaPais(Descritor);
				break;
			
			case 'G':
				clear();
				ConsultaMed(Descritor);
				break;
			case 'H':
				clear();
				Sobre();
				break;
	
			default:
				system("cls");
				put_on_xy(40,12,"Fechando o programa...");
				gotoxy(40,25); clear();
				break;
		}
	}while(opc != 27);
	
}

int main(){
    FILE *ptrArq = fopen("DadosMedicamentos.csv", "r");
	TpDescritor Descritor;
	rewind(ptrArq);
	InicializarDescri(Descritor);
	execute(Descritor,ptrArq);
	fclose(ptrArq);
    return 0;
}
