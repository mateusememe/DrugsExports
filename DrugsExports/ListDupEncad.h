#include "ListSimpEncad.h"

struct TpPais{
	char nomePais[200];
	TpPais *ant, *prox;
	TpMedicamentos *med;
};

struct TpDescritor{
	TpPais	*inicio, *fim;
};
//estrutura para armazenar de forma temporaria os dados do documento.csv
struct TpArq{
	char User[200], Sexo, Medic[200], UltCompra[200], Pais[200];
};

TpPais *NovaCaixaPais(TpPais p){
    TpPais *BoxCountry = new TpPais;
    strcpy(BoxCountry->nomePais,p.nomePais);
	BoxCountry->med = NULL;
    BoxCountry->prox = NULL;
    BoxCountry->ant = NULL;

    return BoxCountry;
}

void InicializarDescri(TpDescritor &Descritor){
	Descritor.inicio = Descritor.fim = NULL;
}

TpPais *verificaLista(TpDescritor descritor, char NomePais[]){
    TpPais *P;

    P = descritor.inicio;

    while (P != NULL && stricmp(P->nomePais,NomePais) != 0){
        P = P->prox;
    }   

    return P;
}

