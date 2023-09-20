#include "selection.h"
/*
uint C      = 4;
uint type[] = {FLTR_PRIX, COND4, COND4, COND4};
//
uint y[]    = {        8,     4,     2,     1};
uint n[]    = {	       8,     2,     2,     2};
*/
//
uint C      = 3;
uint type[] = {FLTR_PRIX, COND4, COND4};
//
uint y[]    = {        4,     2,     1};
uint n[]    = {	       6,     2,     2};
//
Env_t env = {
	//  Le gagant ne muteras jamais
	.MUTP_cst           =0.30,  .COEF_G_cst           =0.60,
	.MUTP_p             =0.40,	.COEF_G_p             =0.80,
	//
	.MUTP_ema_int       =0.30,  .COEF_G_ema_int       =0.70,

	//  Longeure
	.l=3
};

void score(Mdl_t * mdl) {
//	printf("score : %f %f %f %f\n", gain(mdl, env.l), prediction(mdl, env.l), investissement(mdl, env.l), gain_168H(mdl, env.l));
};

__attribute__ ((optimize(0)))
int main_qlq_tests() {
	srand(2);
	charger_les_prixs();

	Mdl_t * mdl = cree_mdl(C, y, n, type);
	plume_mdl(mdl);

	ptr("%f\n", f(mdl, 10));
};

int main_petits_tests() {
	
	//recherche avec les poids (sans ema, voire comment faire mieux pour les poids)


/*	srand(0);
	charger_les_prixs();

	Mdl_t * mdl = cree_mdl(C, y, n, type);
	
	uint ft_G=1, ft_P=1, ft_T = 15;
	uint pt_G=1, pt_P=3, pt_T = 20;
	uint ei_G=1, ei_P=1, ei_T = 15;
	
	mdl = sel2_ei(
		mdl, env,
		ft_G, ft_P, ft_T,
		pt_G, pt_P, pt_T,
		ei_G, ei_P, ei_T);
	plume_mdl(mdl);
	score(mdl);

	ecrire_mdl(mdl, "mdl.bin");*/
};

int main() {
	main_qlq_tests();
	//main_petits_tests();
}