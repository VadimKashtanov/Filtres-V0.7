#include "mdl.h"

//	Le gagant se conserve, le perdant copie le gagant
//	puis mute selon des regles definie dans `Env_t`
//GG=1
//GP=1
typedef struct  {
	//  %[0;1] de chance que P mute
	float MUTP_cst;		//% filtres
	float MUTP_p;		//% poids
	float MUTP_ema_int;		//% ema
	//float MUTP_int;		//% intervalles

	//	%[0;1] d'influence de la valeure du G, quand P mute
	float COEF_G_cst;
	float COEF_G_p;
	float COEF_G_ema_int;
	//float COEF_G_int;
	
	//  u += u*f*levier*( prix[i+l]/prix[i]-1 )
	uint l; //=2;
} Env_t;

//  Fonctions de score
float gain(Mdl_t * mdl, uint l);			//	le gain exacte sur tout le `prix`
float prediction(Mdl_t * mdl, uint l);		//	% de prediction de tendance
float investissement(Mdl_t * mdl, uint l);	//	% de bon placement (donc ignorance de f(x)=0)
float gain_168H(Mdl_t * mdl, uint l);		//	gain dernier semaine avex x25
float gain_JUSQUE_PRIXS(Mdl_t * mdl, uint l, float __LEVIER);

extern uint SESSIONS;		// = 10
extern uint TAILLE_SESSION;	// = 500 ~= 3 semaines
void gain_pred_invest(Mdl_t * mdl, uint l, float * _gain, float * _pred, float * _invest, float * _gain_170H);  //Moyenne sur qlq sessions

//  Fonctions de Mutation
void muter_filtres(Mdl_t * G, Mdl_t * P, float proba, float COEF_G);
void muter_poids(Mdl_t * G, Mdl_t * P, float proba, float COEF_G);
void muter_ema_intervalle(Mdl_t * G, Mdl_t * P, Env_t env);

//	score[i] -> prediction(mdl[i])
//	cintu[i] -> #rang du i-eme mdl

extern uint MODE_DE_SCORE;// = 5
/*Valeur du rang dans les points
	0 : 1*pred + 1*gain
	1 : 1*pred
	2 : 	     1*gain
	3 : 2*pred + 1*gain
	4 : 1*pred + 2*gain
	5 : 1*pred + 1*gain + 1*invest + 1*gain_168H
*/

Mdl_t * sel2_filtres(
	Mdl_t * depart, Env_t env,
	uint flt_Gs, uint flt_Ps, uint flt_T);

Mdl_t * sel2_poids(
	Mdl_t * depart, Env_t env,
	//
	uint flt_Gs, uint flt_Ps,
	uint flt_T,
	//
	uint p_Gs, uint p_Ps,
	uint p_T);

Mdl_t * sel2_ei(
	Mdl_t * depart, Env_t env,
	//
	uint flt_Gs, uint flt_Ps,
	uint flt_T,
	//
	uint p_Gs, uint p_Ps,
	uint p_T,
	//
	uint ei_Gs, uint ei_Ps,
	uint ei_T);
	

