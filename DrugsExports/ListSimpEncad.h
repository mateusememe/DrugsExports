struct TpUsuario{
	char user[200], data[200], sexo;
	TpUsuario *prox;
};
struct TpMedicamentos{
	char nomeMed[200];
	TpMedicamentos *prox;
	TpUsuario *usuario;
};


TpUsuario *NovaCaixaUsuarios(TpUsuario u){
    TpUsuario *BoxUser = new TpUsuario;
    strcpy(BoxUser->user,u.user);
    strcpy(BoxUser->data,u.data);
    BoxUser->sexo = u.sexo;
    BoxUser->prox = NULL;

    return BoxUser;
}

TpMedicamentos *NovaCaixaMedicamentos(TpMedicamentos m){
    TpMedicamentos *BoxDrugs = new TpMedicamentos;    
    strcpy(BoxDrugs->nomeMed,m.nomeMed);
    BoxDrugs->prox = NULL;
	BoxDrugs->usuario = NULL;
    return BoxDrugs;
}

TpUsuario *InsereUsuario(TpUsuario *ListUsu,TpUsuario User){
	TpUsuario *U;
	U = NovaCaixaUsuarios(User);
	
	U->prox = ListUsu;
	ListUsu = U;
	
	return ListUsu;
}

TpMedicamentos *InsereRemedio(TpMedicamentos *ListMed, TpMedicamentos Med,TpUsuario User){
	TpMedicamentos *M;
	M = NovaCaixaMedicamentos(Med);
	
	M->prox = ListMed;
	ListMed = M;
	ListMed->usuario = InsereUsuario(ListMed->usuario,User);
    
    return ListMed;
}

TpMedicamentos *verificaMedicamento(TpMedicamentos *Medic, char NomeMedic[]){
    TpMedicamentos *M;

    M = Medic;

    while (M != NULL && stricmp(M->nomeMed, NomeMedic) != 0)
        M = M->prox;

    return M;
}
TpMedicamentos *BuscaMed(TpMedicamentos *Medic, char NomeMedic[]){
	if(Medic == NULL)
		return NULL;
	if(stricmp(Medic->nomeMed,NomeMedic) == 0)
		return Medic;

	return BuscaMed(Medic->prox,NomeMedic);
}
