#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio2.h>
/*
	TAD dedicada a funções para manipular e gerar a interface da aplicação
	e funções de leitura de dados.
*/

void getStr(char str[]){
	fflush(stdin);
	gets(str);
}
void put_on_xy(int x, int y, char charstring[])
{
    gotoxy(x,y);
    puts(charstring);
}

void put_on_xy(char c, int x, int y)
{
    gotoxy(x,y);
    printf("%c",c);
}
void clear(){
    system("cls");
}
void drawScreen(int cor)
{
	int i, CI = 1,LI = 1,CF = 80,LF = 25; 
	textcolor(cor);
	put_on_xy(201,CI,LI);
	put_on_xy(188,CF,LF);
	put_on_xy(187,CF,LI); 
	put_on_xy(200,CI,LF); 
	
	for(i=CI+1;i<CF;i++)
	{
		put_on_xy(205,i,LI); 
		Sleep(1);
		put_on_xy(205,i,LF);
	}
	
	for(i=LI+1;i<LF;i++)
	{
		put_on_xy(186,CI,i); 
		Sleep(1);
		put_on_xy(186,CF,i);
		
	}
}
void clsInside(int cor, char str[]){
    system("cls");
    drawScreen(cor);    
    int y = (80 - strlen(str))/2;
    put_on_xy(y,1,str);
    textcolor(WHITE);
}

void infoExitScreen(){
    textcolor(YELLOW);
    put_on_xy(33,24,"Aperte qualquer tecla para voltar ao menu [\*]");
    textcolor(WHITE);
    gotoxy(79,24);
}


void LoadingInput(){
    int i = 20;
    gotoxy(30,12);
    for (int i = 0; i < 20; i++) {
        // 16
        gotoxy(20,12); printf("Inserindo Dados de Forma Ordenada");
        for (int j = 53; j < 60; j++) {
            put_on_xy('.',j,12); gotoxy(60,12);
            Sleep(50);
        }
        put_on_xy(53,12,"        ");
    }
    
}
void UserCls(){
    for (int i = 6; i < 22; i++)
        for (int j = 15; i < 40; i++)        
            put_on_xy(i,j," ");
    gotoxy(79,24);
}
void MedCls(){
    for(int i = 30; i < 80; i++){
        put_on_xy(' ',i,5);
    }
    gotoxy(79,24);
}
void CountryCls(){
    for(int i = 27; i < 80; i++){
        put_on_xy(' ',i,4);
    }
    gotoxy(79,24);
}
void LoadingCreateArchive(){
    int i = 20;
    gotoxy(30,12);
    for (int i = 0; i < 20; i++) {
        put_on_xy(21,12,"Gerando arquivo texto com os dados da Lista");
        for (int j = 64; j < 70; j++) {
            put_on_xy('.',j,12); gotoxy(70,12);
            Sleep(50);
        }
        put_on_xy(64,12,"      ");
    }
}

void lilScreenTitle(){
    textcolor(RED);
    put_on_xy(20,7," DRUGS EXPORT'S ");
    textcolor(WHITE);
    //Canto inferior esquerdo
    put_on_xy(192,19,8);
    //Canto Superior esquerdo
    put_on_xy(218,19,6);
    //Canto superior direito
    put_on_xy(191,37,6);
    //Canto inferior direito
    put_on_xy(217,37,8);
    //Lateral Esquerda 
    put_on_xy(179,19,7);
    //Lateral Direita
    put_on_xy(179,37,7);
    for(int i = 20; i < 37; i++){
        put_on_xy(196,i,6);
        put_on_xy(196,i,8);
    }

}
//  Funcao para exibir a tela sobre
void Sobre(void)
{
    clrscr();
    drawScreen(WHITE);
    put_on_xy(31,1,"/* * * SOBRE * * * \\");
    put_on_xy(5,5,"Trabalho sobre Estruturas de Dados Dinamicas:");
    put_on_xy(5,6,"Listas Simplesmente Encadeadas, e Listas Duplamente Encadeadas");
    gotoxy(5,7); printf("com descritores e Recursividade 1%c Semestre de 2020",248);
    textcolor(BLUE);
    gotoxy(5,9); printf("Desenvolvido pelos alunos de BCC do 3%c termo:",248);
    textcolor(WHITE);
    put_on_xy(5,10,"\tAriel Araujo Menezes");
    put_on_xy(5,11,"\tChristian Ferreira de Souza");
    put_on_xy(5,12,"\tMateus Mendonca Monteiro");
    textcolor(LIGHTCYAN);
    put_on_xy(5,14,"Professores:");
    textcolor(WHITE);
    put_on_xy(5,15,"\tLeandro Luiz de Almeida");
    put_on_xy(5,16,"\tMario Augusto Pazzoti");
    infoExitScreen();
    getch();
}

